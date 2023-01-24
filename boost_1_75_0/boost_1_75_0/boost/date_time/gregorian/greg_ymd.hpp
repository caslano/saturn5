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
XjWss0cNritgnEaMqzZZR9xVnfyCtpBe5hROn6oQniPF3SPC16KFo3b6k9NVa2MLKOqSZa30YBXj9Jiw854YyroFRvib7y3iygGQgH9pWjIlRTwlwwU1yYtH7SZaT1/gQyyZ7PbB5fWlCzej52pfz42CBBeCbx//GjJUcJ5eddEeGmJvEsqyHY7kUW647qMrXTz7JMvVb2fOnRy9IA+9VmfY0WA9Asx90i1fGIikucBikrCUYprbK6dmFBm1ssGbzST8cb7RC8nN8L7c7rywrMuv4PdpGudqdbLZeyMm+OndbCm2LtfpKiPk96jCFg64002wr3luhsOtFJGa4Cf68r+5+AURRXDndg3QzhEvoeKmKgVWFZK/8H/moWKkiBEaDFcCc3GzvYuFI9MulwV4unX1HLUvuLmr9AgRkVd58TbBcs8cslQBPZrunT1EtXWilKCaTLuRVcSqmBsz+XOFHaqD/5xXlvS1oPHEs+wi42Wzjfwo7YHihbtSX1nm1IyZkXmKULE59b4RcwKpA0Zu274hVacHc8M6Bmrkv0oDE2aT7b1waE8KfdVv22ELYaSPXHKPSscty2TXxQ/gOxkQDhzCWbmH131ce5U4FOeX/IjWUtnAnidomZ9MXrDlJH2fxubGXaN84AOy31zLJ9EXfqwqQbSpDTeJNzQGx9fVOFnAnRGr5kXkGaSqZ5I+Iuz8oltuMHscxGJlt5Vi
*/