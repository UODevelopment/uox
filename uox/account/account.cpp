//Copyright © 2023 Charles Kerr. All rights reserved.

#include "account.hpp"

#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <vector>

#include "utility/strutil.hpp"

using namespace std::string_literals ;

//======================================================================
const std::filesystem::path Account::ACCOUNTFILE = std::filesystem::path("account.cfg");
//======================================================================
Account::Account():autoCreate(true) {
    // We default to an admin and guest
    auto entry = AccountEntry(0) ;
    entry.setKeyValue("USERNAME", "admin");
    entry.setKeyValue("PASSWORD", "admin");
    entry.setInfo(UserInfo::infotype_t::ADMIN, true);
    accounts.push_back(entry) ;
    entry = AccountEntry(1) ;
    entry.setKeyValue("USERNAME", "guest1");
    entry.setKeyValue("PASSWORD", "guest1");
    entry.setInfo(UserInfo::infotype_t::ADMIN, false);
    accounts.push_back(entry) ;
}
//======================================================================
Account::Account(const std::filesystem::path &path):Account() {
    load(path) ;
}
//======================================================================
auto Account::load(const std::filesystem::path &path) -> bool {
    auto input = std::ifstream(path.string()) ;
    if (!input.is_open()){
        return false ;
    }
    accounts.clear();
    auto buffer = std::vector<char>(4096,0) ;
    auto entry = AccountEntry() ;
    while (input.good() && !input.eof()){
        input.getline(buffer.data(),buffer.size()-1);
        if (input.gcount()>0){
            buffer[input.gcount()] = 0 ;
            std::string line = buffer.data();
            line = util::trim(util::strip(line,"//"));
            if (!line.empty()){
                if (line[0]=='[' && line[line.size()-1] == ']'){
                    // This is a section header
                    auto [value,key] = util::split(util::contentsOf(line, "[",  "]"),":") ;
                    if (util::upper(key) == "ACCOUNT"){
                        entry = AccountEntry(std::stoi(value,nullptr,0)) ;
                    }
                }
                else if (line[0] != '}' && line[0] != '{'){
                    auto [key,value] = util::split(line,"=");
                    entry.setKeyValue(util::upper(key), value);
                }
                else if (line[0] == '}' && entry.number()>=0){
                    // we can save the account, but need to ensure not two usernames and not same account#
                    auto name = util::upper(entry.user());
                    auto iter = std::find_if(accounts.begin(),accounts.end(),[name](const AccountEntry &value){
                        return name == util::upper(value.user());
                    });
                    if (iter == accounts.end() && !entry.user().empty()){
                        auto number = entry.number();
                        // This doesnt exist, check one!
                        iter = std::find_if(accounts.begin(),accounts.end(),[number](const AccountEntry &value){
                            return value.number() == number ;
                        });
                        if (iter == accounts.end()){
                            // Not a repeat on account number!  Check two!
                            //===============================================================
                            // Now, we should should check to ensure the players exist?
                            auto todelete  = std::vector< int>();
                            for (size_t i = 0 ; i< entry.allCharacter().size();i++){
                                if (entry.allCharacter().at(i).serialNumber != INVALIDSERIAL){
                                    // Do something here?
                                }
                            }
                            for (const auto &slot:todelete){
                                entry.deleteCharacter(slot);
                            }
                            //==================================================================
                            accounts.push_back(entry);
                        }
                        else {
                            std::cerr <<"Duplicate account number: " << entry.number()<<std::endl;
                        }
                    }
                    else {
                        std::cerr <<"Duplicate/Empty username in account file, skipping: " << entry.user()<<std::endl;
                    }
                    entry = AccountEntry();
                }
            }
        }
    }
    std::sort(accounts.begin(),accounts.end(),[](const AccountEntry &lhs, const AccountEntry &rhs){
        return lhs.number() < rhs.number();
    });
    return true ;
}

//======================================================================
auto Account::update(const std::filesystem::path &path) -> int {
    auto input = std::ifstream(path.string()) ;
    if (!input.is_open()){
        return 0 ;
    }
    int count = 0 ;
    auto buffer = std::vector<char>(4096,0) ;
    auto entry = AccountEntry() ;
    while (input.good() && !input.eof()){
        input.getline(buffer.data(),buffer.size()-1);
        if (input.gcount()>0){
            buffer[input.gcount()] = 0 ;
            std::string line = buffer.data();
            line = util::trim(util::strip(line,"//"));
            if (!line.empty()){
                if (line[0]=='[' && line[line.size()-1] == ']'){
                    // This is a section header
                    auto sec = util::upper(util::trim(util::contentsOf(line, "[",  "]"))) ;
                    if (sec == "ACCOUNT"){
                        int newnumber = 0 ;
                        if (!accounts.empty()){
                            auto iter = accounts.rbegin() ;
                            newnumber = iter->number() + 1;
                        }
                        entry = AccountEntry(newnumber) ;
                    }
                    else if (line[0] == '}' && entry.number()>=0){
                        // we can save the account, but need to ensure not two usernames and not same account#
                        auto name = util::upper(entry.user());
                        auto iter = std::find_if(accounts.begin(),accounts.end(),[name](const AccountEntry &value){
                            return name == util::upper(value.user());
                        });
                        if (iter == accounts.end() && !entry.user().empty()){
                            auto number = entry.number();
                            // This doesnt exist, check one!
                            iter = std::find_if(accounts.begin(),accounts.end(),[number](const AccountEntry &value){
                                return value.number() == number ;
                            });
                            if (iter == accounts.end()){
                                // Not a repeat on account number!  Check two!
                                count++;
                                accounts.push_back(entry);
                                std::sort(accounts.begin(),accounts.end(),[](const AccountEntry &lhs, const AccountEntry &rhs){
                                    return lhs.number() < rhs.number();
                                });
                            }
                            else {
                                std::cerr <<"Duplicate account number: " << entry.number()<<std::endl;
                            }
                        }
                        else {
                            std::cerr <<"Duplicate/Empty username in account file, skipping: " << entry.user()<<std::endl;
                        }
                        entry = AccountEntry();
                    }
                }
            }
        }
    }
    std::filesystem::remove(path) ;
    return count ;
}
//======================================================================
auto Account::size() const -> size_t {
    return accounts.size();
}
//======================================================================
auto Account::save(const std::filesystem::path &filepath) -> bool {
    auto output = std::ofstream(filepath.string()) ;
    if (!output.is_open()){
        return false ;
    }
    // BANNED,SUSPENDED,SEER,COUNSELOR,ADMIN
    output << "// ================================================================================================================================\n";
    output << "// Format:\n";
    output << "//       [account#:ACCOUNT]   where account# is the number of the account (used as reference, can not duplicate)\n";
    output << "//       {\n";
    output << "//          USERNAME = username   User name is not case sensitve, and can not duplicate\n" ;
    output << "//          PASSWORD = password\n";
    output << "//          INFORMATION = 0x0000\n";
    output << "//                       where the number represents information about the account as follows:\n";
    output << "//                       Bit:  0x0001) Banned           0x0002) Suspended       0x0004) Unused         0x0008) Unused\n";
    output << "//                             0x0010) Unused           0x0020) Unused          0x0040) Unused         0x0080) Unused \n";
    output << "//                             0x0100) Unused           0x0200) Unused          0x0400) Unused         0x0800) Unused \n";
    output << "//                             0x1000) Unused           0x2000) Seer            0x4000) Counselor      0x8000) GM Account\n";
    output << "//\n";
    output << "//           LASTIP = ip4address    The last ip used (or *.*.*.* if never logged in)\n";
    output << "//           FIRSTLOGIN = datetime  The date time of the first login, or blank if never logged in\n";
    output << "//           LASTLOGIN = datetime   The date time of the last login\n";
    output << "//\n";
    output << "//           CHARACTER = serial#, name, creationdate    (Repeated for each character slot) \n";
    output << "//                                               serial is the serial number of the character (or 0xFFFFFFFF if not present),\n";
    output << "//                                               name is the name of the character (or blank)\n";
    output << "//                                               creationdate is the date the character is created \n";
    output << "// ================================================================================================================================\n";
    for (const auto &entry:accounts){
        output <<"["<<entry.number()<<":ACCOUNT]\n{\n";
        entry.save(output) ;
        output<<"}\n\n";
    }
    return true ;
}

//======================================================================
auto Account::accountFor(int accountNumber) -> AccountEntry* {
    auto iter = std::find_if(accounts.begin(),accounts.end(),[accountNumber](const AccountEntry &entry) {
        return entry.number() == accountNumber;
    });
    if (iter != accounts.end()){
        return &(*iter) ;
    }
    return nullptr;
}
//======================================================================
auto Account::accountFor(const std::string &user) -> AccountEntry* {
    auto iter = std::find_if(accounts.begin(),accounts.end(),[user](const AccountEntry &entry) {
        return util::upper(entry.user()) == util::upper(user);
    });
    if (iter != accounts.end()){
        return &(*iter) ;
    }
    return nullptr;

}

//======================================================================
auto Account::createAccount(const std::string &user, const std::string &password) -> AccountEntry* {
    // First make sure there is no account all ready with user name
    auto account = this->accountFor(user) ;
    if (account != nullptr){
        return nullptr ;
    }
    auto iter = accounts.rbegin() ;
    auto number = iter->number() ;
    auto act = AccountEntry() ;
    act.username = user ;
    act.password = password ;
    act.accountNumber = number+1 ;
    accounts.push_back(act) ;
    iter = accounts.rbegin() ;
    return &(*iter);
}

