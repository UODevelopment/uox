//Copyright © 2023 Charles Kerr. All rights reserved.

#include "language.hpp"
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <vector>

#include "utility/strutil.hpp"
using namespace std::string_literals ;

const std::string Language::EMPTY_STRING = std::string();

//=============================================================================
auto Language::shared() ->Language& {
    static Language instance ;
    return instance ;
}
//=============================================================================
auto Language::findLanguage(const std::string &name)  ->DistinctLanguage{
    auto iter = std::find_if(LANGUAGE_MAPPING.begin(),LANGUAGE_MAPPING.end(),[name](const std::pair<DistinctLanguage,std::string> &entry){
        return entry.second == name;
    });
    if (iter != LANGUAGE_MAPPING.end()){
        return iter->first ;
    }
    return DistinctLanguage::DEFAULT ;
}
//=============================================================================
auto Language::nameForLanguage(DistinctLanguage language)  -> const std::string&{
    auto iter =  LANGUAGE_MAPPING.find(language);
    if (iter != LANGUAGE_MAPPING.end()){
        return iter->second ;
    }
    return EMPTY_STRING ;
}
//=============================================================================
auto Language::messageFor(int id, const std::string &unicode) const -> const std::string& {
    auto language = UNICODE_LANGUAGE.at(UNICODE_CODE.at(unicode)) ;
    if (language == DistinctLanguage::DEFAULT) {
        language = languageDefault ;
    }
    auto iter = messages.find(language) ;
    if (iter == messages.end()) {
        language = languageDefault ;
        iter = messages.find(language);
    }
    try{
        if (iter != messages.end()){
            return iter->second.at(id) ;
        }
        else {
            std::cerr <<"Language requested: "<<unicode<<" not found\n" ;
        }
    }
    catch(...) {
        std::cerr <<"Message id: "<<id<< " For language: "<<Language::nameForLanguage(language)<<" Not found\n" ;
    }
    return  EMPTY_STRING;
    
}
//=============================================================================
auto Language::operator[](int id) const -> const std::string& {
    return this->messageFor(id);
}

//=============================================================================
auto Language::load(const std::filesystem::path &directory,bool log) -> void {
    messages.clear() ;
    auto buffer = std::vector<char>(4096,0) ;
    if(log){
        std::clog<<"\tLoading languages:\n";
    }
    for (const auto &[lang,name]:LANGUAGE_MAPPING){
        auto filepath = std::filesystem::path(name+".lang"s) ;
        auto input = std::ifstream((directory/filepath).string()) ;
        if (!input.is_open()){
            if (log){
                std::clog <<"\t\tLoading: Failure opening: "s<<(directory/filepath).string()<<"\n";
            }
        }
        else {
            if (log){
                std::clog <<"\t\tLoading: "s<<(directory/filepath).string()<<" ";
            }
            bool lookSection = true ;
            auto language = DistinctLanguage::DEFAULT ;
            auto count = 0 ;
            while(input.good() && !input.eof()){
                input.getline(buffer.data(),buffer.size()-1) ;
                if (input.gcount()>0){
                    buffer[input.gcount()] = 0 ;
                    std::string line = buffer.data();
                    line = util::trim(util::strip(line,"//"));
                    if (!line.empty()){
                        if (lookSection) {
                            if (line[0]=='['){
                                auto section = util::contentsOf(line, "[", "]") ;
                                auto [name,sec] = util::split(section,":");
                                if (util::lower(sec) == "language"){
                                    language = findLanguage(name);
                                }
                            }
                            if (line[0] == '{' && language != DistinctLanguage::DEFAULT){
                                lookSection = false ;
                            }
                        }
                        else {
                            if (line[0] == '}'){
                                language = DistinctLanguage::DEFAULT ;
                                lookSection = true ;
                            }
                            else {
                                auto [number,msg] = util::split(line, "=") ;
                                try {
                                    auto msgid = std::stoi(number) ;
                                    messages[language][msgid]=msg ;
                                    count++ ;
                                }
                                catch(...){
                                    // We coud give an error here, to help them maintain the language file
                                }
                            }
                         }
                    }
                }
            }
            if (log){
                std::clog<<"Entries processed: "<<count<<"\n";
            }
        }
        
    }
}

//=============================================================================
const std::map<DistinctLanguage,std::string> Language::LANGUAGE_MAPPING{
    {DistinctLanguage::ENGLISH,"english"s},
    {DistinctLanguage::GERMAN,"german"s},
    {DistinctLanguage::SPANISH,"spanish"s},
    {DistinctLanguage::FRENCH,"french"s},
    {DistinctLanguage::PORTUGUESE,"portuguese"s},
    {DistinctLanguage::ITALIAN,"italian"s},
    {DistinctLanguage::CZECH,"czech"s},
    {DistinctLanguage::POLISH,"polish"s}
};


//==========================================================================
const std::map<std::string,Language::UnicodeType> Language::UNICODE_CODE{
    {"ZRO"s,Language::UnicodeType::ZERO},
    {"ARA"s,Language::UnicodeType::ARA},
    {"ARI"s,Language::UnicodeType::ARI},
    {"ARE"s,Language::UnicodeType::ARE},
    {"ARL"s,Language::UnicodeType::ARL},
    {"ARG"s,Language::UnicodeType::ARG},
    {"ARM"s,Language::UnicodeType::ARM},
    {"ART"s,Language::UnicodeType::ART},
    {"ARO"s,Language::UnicodeType::ARO},
    {"ARY"s,Language::UnicodeType::ARY},
    {"ARS"s,Language::UnicodeType::ARS},
    {"ARJ"s,Language::UnicodeType::ARJ},
    {"ARB"s,Language::UnicodeType::ARB},
    {"ARK"s,Language::UnicodeType::ARK},
    {"ARU"s,Language::UnicodeType::ARU},
    {"ARH"s,Language::UnicodeType::ARH},
    {"ARQ"s,Language::UnicodeType::ARQ},
    {"BGR"s,Language::UnicodeType::BGR},
    {"CAT"s,Language::UnicodeType::CAT},
    {"CHT"s,Language::UnicodeType::CHT},
    {"CHS"s,Language::UnicodeType::CHS},
    {"ZHH"s,Language::UnicodeType::ZHH},
    {"ZHI"s,Language::UnicodeType::ZHI},
    {"ZHM"s,Language::UnicodeType::ZHM},
    {"CSY"s,Language::UnicodeType::CSY},
    {"DAN"s,Language::UnicodeType::DAN},
    {"DEU"s,Language::UnicodeType::DEU},
    {"DES"s,Language::UnicodeType::DES},
    {"DEA"s,Language::UnicodeType::DEA},
    {"DEL"s,Language::UnicodeType::DEL},
    {"DEC"s,Language::UnicodeType::DEC},
    {"ELL"s,Language::UnicodeType::ELL},
    {"ENU"s,Language::UnicodeType::ENU},
    {"ENG"s,Language::UnicodeType::ENG},
    {"ENA"s,Language::UnicodeType::ENA},
    {"ENC"s,Language::UnicodeType::ENC},
    {"ENZ"s,Language::UnicodeType::ENZ},
    {"ENI"s,Language::UnicodeType::ENI},
    {"ENS"s,Language::UnicodeType::ENS},
    {"ENJ"s,Language::UnicodeType::ENJ},
    {"ENB"s,Language::UnicodeType::ENB},
    {"ENL"s,Language::UnicodeType::ENL},
    {"ENT"s,Language::UnicodeType::ENT},
    {"ENW"s,Language::UnicodeType::ENW},
    {"ENP"s,Language::UnicodeType::ENP},
    {"ESP"s,Language::UnicodeType::ESP},
    {"ESM"s,Language::UnicodeType::ESM},
    {"ESN"s,Language::UnicodeType::ESN},
    {"ESG"s,Language::UnicodeType::ESG},
    {"ESC"s,Language::UnicodeType::ESC},
    {"ESA"s,Language::UnicodeType::ESA},
    {"ESD"s,Language::UnicodeType::ESD},
    {"ESV"s,Language::UnicodeType::ESV},
    {"ESO"s,Language::UnicodeType::ESO},
    {"ESR"s,Language::UnicodeType::ESR},
    {"ESS"s,Language::UnicodeType::ESS},
    {"ESF"s,Language::UnicodeType::ESF},
    {"ESL"s,Language::UnicodeType::ESL},
    {"ESY"s,Language::UnicodeType::ESY},
    {"ESZ"s,Language::UnicodeType::ESZ},
    {"ESB"s,Language::UnicodeType::ESB},
    {"ESE"s,Language::UnicodeType::ESE},
    {"ESH"s,Language::UnicodeType::ESH},
    {"ESI"s,Language::UnicodeType::ESI},
    {"ESU"s,Language::UnicodeType::ESU},
    {"FIN"s,Language::UnicodeType::FIN},
    {"FRA"s,Language::UnicodeType::FRA},
    {"FRB"s,Language::UnicodeType::FRB},
    {"FRC"s,Language::UnicodeType::FRC},
    {"FRS"s,Language::UnicodeType::FRS},
    {"FRL"s,Language::UnicodeType::FRL},
    {"FRM"s,Language::UnicodeType::FRM},
    {"HEB"s,Language::UnicodeType::HEB},
    {"HUN"s,Language::UnicodeType::HUN},
    {"ISL"s,Language::UnicodeType::ISL},
    {"ITA"s,Language::UnicodeType::ITA},
    {"ITS"s,Language::UnicodeType::ITS},
    {"JPN"s,Language::UnicodeType::JPN},
    {"KOR"s,Language::UnicodeType::KOR},
    {"NLD"s,Language::UnicodeType::NLD},
    {"NLB"s,Language::UnicodeType::NLB},
    {"NOR"s,Language::UnicodeType::NOR},
    {"NON"s,Language::UnicodeType::NON},
    {"PLK"s,Language::UnicodeType::PLK},
    {"PTB"s,Language::UnicodeType::PTB},
    {"PTG"s,Language::UnicodeType::PTG},
    {"ROM"s,Language::UnicodeType::ROM},
    {"RUS"s,Language::UnicodeType::RUS},
    {"HRV"s,Language::UnicodeType::HRV},
    {"SRL"s,Language::UnicodeType::SRL},
    {"SRB"s,Language::UnicodeType::SRB},
    {"SKY"s,Language::UnicodeType::SKY},
    {"SQI"s,Language::UnicodeType::SQI},
    {"SVE"s,Language::UnicodeType::SVE},
    {"SVF"s,Language::UnicodeType::SVF},
    {"THA"s,Language::UnicodeType::THA},
    {"TRK"s,Language::UnicodeType::TRK},
    {"URP"s,Language::UnicodeType::URP},
    {"IND"s,Language::UnicodeType::IND},
    {"UKR"s,Language::UnicodeType::UKR},
    {"BEL"s,Language::UnicodeType::BEL},
    {"SLV"s,Language::UnicodeType::SLV},
    {"ETI"s,Language::UnicodeType::ETI},
    {"LVI"s,Language::UnicodeType::LVI},
    {"LTH"s,Language::UnicodeType::LTH},
    {"LTC"s,Language::UnicodeType::LTC},
    {"FAR"s,Language::UnicodeType::uFAR},
    {"VIT"s,Language::UnicodeType::VIT},
    {"HYE"s,Language::UnicodeType::HYE},
    {"AZE"s,Language::UnicodeType::AZE},
    {"EUQ"s,Language::UnicodeType::EUQ},
    {"MKI"s,Language::UnicodeType::MKI},
    {"AFK"s,Language::UnicodeType::AFK},
    {"KAT"s,Language::UnicodeType::KAT},
    {"FOS"s,Language::UnicodeType::FOS},
    {"HIN"s,Language::UnicodeType::HIN},
    {"MSL"s,Language::UnicodeType::MSL},
    {"MSB"s,Language::UnicodeType::MSB},
    {"KAZ"s,Language::UnicodeType::KAZ},
    {"SWK"s,Language::UnicodeType::SWK},
    {"UZB"s,Language::UnicodeType::UZB},
    {"TAT"s,Language::UnicodeType::TAT},
    {"BEN"s,Language::UnicodeType::BEN},
    {"PAN"s,Language::UnicodeType::PAN},
    {"GUJ"s,Language::UnicodeType::GUJ},
    {"ORI"s,Language::UnicodeType::ORI},
    {"TAM"s,Language::UnicodeType::TAM},
    {"TEL"s,Language::UnicodeType::TEL},
    {"KAN"s,Language::UnicodeType::KAN},
    {"MAL"s,Language::UnicodeType::MAL},
    {"ASM"s,Language::UnicodeType::ASM},
    {"MAR"s,Language::UnicodeType::MAR},
    {"SAN"s,Language::UnicodeType::SAN},
    {"KOK"s,Language::UnicodeType::KOK}
};
//=======================================================================================================
const std::map<Language::UnicodeType,DistinctLanguage> Language::UNICODE_LANGUAGE{
    {Language::UnicodeType::ZERO,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::ARA,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::ARI,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::ARE,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::ARL,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::ARG,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::ARM,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::ART,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::ARO,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::ARY,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::ARS,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::ARJ,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::ARB,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::ARK,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::ARU,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::ARH,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::ARQ,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::BGR,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::CAT,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::CHT,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::CHS,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::ZHH,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::ZHI,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::ZHM,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::CSY,DistinctLanguage::CZECH},
    {Language::UnicodeType::DAN,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::DEU,DistinctLanguage::GERMAN},
    {Language::UnicodeType::DES,DistinctLanguage::GERMAN},
    {Language::UnicodeType::DEA,DistinctLanguage::GERMAN},
    {Language::UnicodeType::DEL,DistinctLanguage::GERMAN},
    {Language::UnicodeType::DEC,DistinctLanguage::GERMAN},
    {Language::UnicodeType::ELL,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::ENU,DistinctLanguage::ENGLISH},
    {Language::UnicodeType::ENG,DistinctLanguage::ENGLISH},
    {Language::UnicodeType::ENA,DistinctLanguage::ENGLISH},
    {Language::UnicodeType::ENC,DistinctLanguage::ENGLISH},
    {Language::UnicodeType::ENZ,DistinctLanguage::ENGLISH},
    {Language::UnicodeType::ENI,DistinctLanguage::ENGLISH},
    {Language::UnicodeType::ENS,DistinctLanguage::ENGLISH},
    {Language::UnicodeType::ENJ,DistinctLanguage::ENGLISH},
    {Language::UnicodeType::ENB,DistinctLanguage::ENGLISH},
    {Language::UnicodeType::ENL,DistinctLanguage::ENGLISH},
    {Language::UnicodeType::ENT,DistinctLanguage::ENGLISH},
    {Language::UnicodeType::ENW,DistinctLanguage::ENGLISH},
    {Language::UnicodeType::ENP,DistinctLanguage::ENGLISH},
    {Language::UnicodeType::ESP,DistinctLanguage::SPANISH},
    {Language::UnicodeType::ESM,DistinctLanguage::SPANISH},
    {Language::UnicodeType::ESN,DistinctLanguage::SPANISH},
    {Language::UnicodeType::ESG,DistinctLanguage::SPANISH},
    {Language::UnicodeType::ESC,DistinctLanguage::SPANISH},
    {Language::UnicodeType::ESA,DistinctLanguage::SPANISH},
    {Language::UnicodeType::ESD,DistinctLanguage::SPANISH},
    {Language::UnicodeType::ESV,DistinctLanguage::SPANISH},
    {Language::UnicodeType::ESO,DistinctLanguage::SPANISH},
    {Language::UnicodeType::ESR,DistinctLanguage::SPANISH},
    {Language::UnicodeType::ESS,DistinctLanguage::SPANISH},
    {Language::UnicodeType::ESF,DistinctLanguage::SPANISH},
    {Language::UnicodeType::ESL,DistinctLanguage::SPANISH},
    {Language::UnicodeType::ESY,DistinctLanguage::SPANISH},
    {Language::UnicodeType::ESZ,DistinctLanguage::SPANISH},
    {Language::UnicodeType::ESB,DistinctLanguage::SPANISH},
    {Language::UnicodeType::ESE,DistinctLanguage::SPANISH},
    {Language::UnicodeType::ESH,DistinctLanguage::SPANISH},
    {Language::UnicodeType::ESI,DistinctLanguage::SPANISH},
    {Language::UnicodeType::ESU,DistinctLanguage::SPANISH},
    {Language::UnicodeType::FIN,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::FRA,DistinctLanguage::FRENCH},
    {Language::UnicodeType::FRB,DistinctLanguage::FRENCH},
    {Language::UnicodeType::FRC,DistinctLanguage::FRENCH},
    {Language::UnicodeType::FRS,DistinctLanguage::FRENCH},
    {Language::UnicodeType::FRL,DistinctLanguage::FRENCH},
    {Language::UnicodeType::FRM,DistinctLanguage::FRENCH},
    {Language::UnicodeType::HEB,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::HUN,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::ISL,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::ITA,DistinctLanguage::ITALIAN},
    {Language::UnicodeType::ITS,DistinctLanguage::ITALIAN},
    {Language::UnicodeType::JPN,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::KOR,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::NLD,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::NLB,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::NOR,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::NON,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::PLK,DistinctLanguage::POLISH},
    {Language::UnicodeType::PTB,DistinctLanguage::PORTUGUESE},
    {Language::UnicodeType::PTG,DistinctLanguage::PORTUGUESE},
    {Language::UnicodeType::ROM,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::RUS,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::HRV,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::SRL,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::SRB,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::SKY,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::SQI,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::SVE,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::SVF,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::THA,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::TRK,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::URP,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::IND,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::UKR,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::BEL,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::SLV,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::ETI,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::LVI,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::LTH,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::LTC,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::uFAR,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::VIT,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::HYE,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::AZE,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::EUQ,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::MKI,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::AFK,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::KAT,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::FOS,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::HIN,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::MSL,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::MSB,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::KAZ,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::SWK,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::UZB,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::TAT,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::BEN,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::PAN,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::GUJ,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::ORI,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::TAM,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::TEL,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::KAN,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::MAL,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::ASM,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::MAR,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::SAN,DistinctLanguage::DEFAULT},
    {Language::UnicodeType::KOK,DistinctLanguage::DEFAULT},
};

