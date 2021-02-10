#ifndef DATE_TIME_GREG_YMD_HPP__
#define DATE_TIME_GREG_YMD_HPP__

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland 
 * $Date$
 */

#include "boost/date_time/year_month_day.hpp"
#include "boost/date_time/special_defs.hpp"
#include "boost/date_time/gregorian/greg_day.hpp"
#include "boost/date_time/gregorian/greg_year.hpp"
#include "boost/date_time/gregorian/greg_month.hpp"

namespace boost {
namespace gregorian {
  
  typedef date_time::year_month_day_base<greg_year, 
                                         greg_month, 
                                         greg_day> greg_year_month_day;
  
  
  
} } //namespace gregorian




#endif
  

/* greg_ymd.hpp
UG4anAfTYOpfggvdFguHZLFHsDbS+1vKR4aBE+WO4yyW3TZknhgI2W1RdSCmDcSFl+oWhUa484xywxToKGEQjsfBYO5Hv5u8Lw8DmUzDX6/8atF4ew+w/iW+HYAVnV3q3GVtJZFPpcue33wCiA2xF8LsIJiOZ+L1Dst/GoGMukfV3EQ30rRIdc3D6taIvjjgVWL88KrR7gvYdtGlq53X5jHYc3t6vTbwdPUAbMDa2OSECHSvbyY/LDl/8kMEDuWJUBR876u3H549GAAGlFtXrc6gI6dINKmtPeseXl18lnjclGzJFaben7ByV9utrtvY3VF4dB7wrFundu7eAe7bluqWFxM4ut8ckDD4xVCBDiwhN8BSveJ8pnCcdDokdAchWPeAcVcO6TtX8Mj1Rdnwi+YQ7AyOmm6Pt7panygUiAcsVRfLNPc9fy0w9V7ky2FxV2pRAbOezaEzAW9htxMnBxGeh6NReDkKB31edn2Y9aLidlEmCzD4MUm0uxP7LOreN9XKsNuIol1pp41Nt7awHjA+L22aHXOlcDutcXCwWcX9p00zWE27Fbms+I3D7SbuZubGxz3PrNZI78xi8jLa4NuL3nff957eY/R6AsdujOKSdctud/oVrJfq94jR/bLTblFpCQsryQqbIh/6
*/