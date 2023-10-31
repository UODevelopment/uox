//Copyright © 2023 Charles Kerr. All rights reserved.

#ifndef typedef_hpp
#define typedef_hpp

#include <chrono>
#include <cstdint>
#include <limits>
#include "utility/nettype.hpp"
//======================================================================
using sec_t = int ;
using packetid_t = int ;

using serial_t = std::uint32_t ;

using uoid_t = std::uint16_t ;
using color_t = std::uint16_t ;

// Some time
using sec_t = int ;
using milli_t = int ;
using minute_t = int ;
using day_t = int ;

using timepoint_t = std::chrono::steady_clock::time_point ;
using walltime_t = std::chrono::system_clock::time_point ;

enum class systemstate_t {SHUTDOWN,PAUSE,RUN};

constexpr auto INVALIDSERIAL = std::numeric_limits<serial_t>::max() ;

constexpr auto INVALIDID = std::numeric_limits<uoid_t>::max() ;


#endif /* typedef_hpp */
