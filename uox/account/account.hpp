//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef account_hpp
#define account_hpp

#include <cstdint>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "accountentry.hpp"

class PlayerFactory ;
//======================================================================
class Account {
    
    std::vector<AccountEntry> accounts ;

public:
    static const std::filesystem::path ACCOUNTFILE ;
    bool autoCreate ;
    Account() ;
    Account(const std::filesystem::path &path) ;
    
    [[maybe_unused]] auto load(const std::filesystem::path &path) -> bool ;
    [[maybe_unused]] auto update(const std::filesystem::path &path) -> int ;
    
    auto size() const -> size_t ;
    auto save(const std::filesystem::path &filepath) -> bool ;
    
    auto accountFor(int accountNumber) -> AccountEntry* ;
    auto accountFor(const std::string &user) -> AccountEntry* ;
    auto createAccount(const std::string &user, const std::string &password) -> AccountEntry* ;
    
};

#endif /* account_hpp */
