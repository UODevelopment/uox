//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef langauge_hpp
#define langauge_hpp

#include <cstdint>
#include <filesystem>
#include <iostream>
#include <map>
#include <string>

//======================================================================
//======================================================================
enum  class DistinctLanguage {
    DEFAULT,
    ENGLISH, GERMAN, SPANISH, FRENCH, PORTUGUESE, ITALIAN, CZECH, POLISH
};

//======================================================================
class Language {
    //======================================================================

    enum class UnicodeType {
        ZERO = 0,
        ARA, ARI, ARE, ARL, ARG, ARM, ART, ARO, ARY, ARS, ARJ, ARB, ARK, ARU, ARH, ARQ,
        BGR, CAT, CHT, CHS, ZHH, ZHI, ZHM, CSY, DAN, DEU, DES, DEA, DEL, DEC, ELL, ENU,
        ENG, ENA, ENC, ENZ, ENI, ENS, ENJ, ENB, ENL, ENT, ENW, ENP, ESP, ESM, ESN, ESG,
        ESC, ESA, ESD, ESV, ESO, ESR, ESS, ESF, ESL, ESY, ESZ, ESB, ESE, ESH, ESI, ESU,
        FIN, FRA, FRB, FRC, FRS, FRL, FRM, HEB, HUN, ISL, ITA, ITS, JPN, KOR, NLD, NLB,
        NOR, NON, PLK, PTB, PTG, ROM, RUS, HRV, SRL, SRB, SKY, SQI, SVE, SVF, THA, TRK,
        URP, IND, UKR, BEL, SLV, ETI, LVI, LTH, LTC, uFAR, VIT, HYE, AZE, EUQ, MKI, AFK,
        KAT, FOS, HIN, MSL, MSB, KAZ, SWK, UZB, TAT, BEN, PAN, GUJ, ORI, TAM, TEL, KAN,
        MAL, ASM, MAR, SAN, KOK
    };

    static const std::map<std::string,UnicodeType> UNICODE_CODE;
    static const std::map<UnicodeType,DistinctLanguage> UNICODE_LANGUAGE;
    static const std::map<DistinctLanguage,std::string> LANGUAGE_MAPPING ;
    static const std::string EMPTY_STRING;
    std::map<DistinctLanguage,std::map<int,std::string>> messages ;
    
    Language(){languageDefault=DistinctLanguage::ENGLISH;}

public:
    static auto findLanguage(const std::string &name)  ->DistinctLanguage ;
    static auto nameForLanguage(DistinctLanguage language)  -> const std::string& ;

    Language(const Language&) = delete ;
    Language(const Language&&) = delete ;
    auto operator=(const Language&)->Language& = delete ;
    auto operator=(Language&&)->Language& = delete ;
    static auto shared() ->Language& ;
    DistinctLanguage languageDefault ;
    auto load(const std::filesystem::path &directory,bool log = false) -> void ;
    auto messageFor(int id, const std::string &unicode="ZRO") const -> const std::string& ;
    auto operator[](int id) const -> const std::string& ;
};

#endif /* langauge_hpp */
