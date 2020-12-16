#ifndef GREG_DURATION_TYPES_HPP___
#define GREG_DURATION_TYPES_HPP___

/* Copyright (c) 2004 CrystalClear Software, Inc.
 * Subject to Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */


#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/gregorian/greg_date.hpp>
#include <boost/date_time/int_adapter.hpp>
#include <boost/date_time/adjust_functors.hpp>
#include <boost/date_time/date_duration_types.hpp>
#include <boost/date_time/gregorian/greg_duration.hpp>

namespace boost {
namespace gregorian {

  //! config struct for additional duration types (ie months_duration<> & years_duration<>)
  struct BOOST_SYMBOL_VISIBLE greg_durations_config {
    typedef date date_type;
    typedef date_time::int_adapter<int> int_rep;
    typedef date_time::month_functor<date_type> month_adjustor_type; 
  };

  typedef date_time::months_duration<greg_durations_config> months;
  typedef date_time::years_duration<greg_durations_config> years;

  class BOOST_SYMBOL_VISIBLE weeks_duration : public date_duration {
  public:
    BOOST_CXX14_CONSTEXPR weeks_duration(duration_rep w) 
      : date_duration(w * 7) {}
    BOOST_CXX14_CONSTEXPR weeks_duration(date_time::special_values sv) 
      : date_duration(sv) {}
  };

  typedef weeks_duration weeks;

}} // namespace boost::gregorian

#endif // GREG_DURATION_TYPES_HPP___

/* greg_duration_types.hpp
vKgZw5zVjmHeI4UIn7x3Kfcpa45M6MAgRWCyzkxhHlyh6bSbS1cHRQzNODuFO8m0E8hO4XXvcD4rKGyx1PZAj4caTiEkaw1kUXghCuXWuoQU5hPuU44pRLlTeEEKvWZI4UUthY0j6W9qR9Lf1EzofFA7ofMhKUT45L1LuU9ZcxNCBwYpApP1gSnMgys0jXFz6eqgiKGZPKcQErWcyXMKr/0xdlj6+bZYav+gx0MNpxCStQayKPxGFMqtdQkpzCfcpxxTiHKnEObw7DVDCr+ppbBxWnFbO624rZndvlE7u/0xKUT45L1LuU9ZY0Khs9UcBZN1wxTmwRUaPt5cujooYmgGxSncSaadQHYKr3sLNCz9fFsstcHQ46GGUwjJWgNZFG5Fodxal5DCfMJ9yjGFKHcKt6TQa4YUbmspbFxjuaxdY7msWepb1y71bUghwifvXcp9ynrQFjqXGhsyWWtTmAdX6JmcNTalIsfQyNUphEQtR64BhfFboNcFhS2W2l7o8VDDKYRkrYEsCi9Fodxal5DCfMJ9yjGFKHcKL0mh1wwpvKylsHHB+cfaBecfjcKbGvcZ3hEYhU+ZpBDhk/cu5T5lPeIIHRikCEzWuSnMgyv0NHRz6eqgiKHxgFMIiVqOBwIK47dEnxcUtlhq/6HHQw2nEJK1BrIo/FEUyq11CSnMJ9ynHFOIcqcQ5vDsNUMKf6yl8Kb2XdeNoP5cC+rPBurNjXsV7wiMwkcAgorwyXuXcp+y7j+iCwYpAvP5jSnMgyt0q2KNbanIMfSw5qBCopYPawGo8YumYenn22KpPYweDzUcVEjWGsgC9WeCam6hVG5lwhSy0yPcUArc6JaUerVoAw/KqzfwNN60D26rvGkfDCoul5e1l8sfSSHCJ+89ygPKesm80IFBisBkXZrCPLiiw4vEzaWrThFDt0mnEBK1vE0GFMZvk74MKGy0FIWI463B+XiNnrcGMimEL+DibqFUbmXCFLLTIwpRKgphm93iXxYFFKK8lsLGAczwtsoBzHBQ8ej4c+2j48GdKL8Kn7z3KA8oq0PvJDowSBGYLESiwj24Qn0/LF11ihhDXn2cQkjU8uoTUBi/TRqWfr4tlqDQmzmkb6cQkrUGsigckkJzC6VyKxOlMMkhhUOjELZ0a9UaKBxWU9g4mXN4W+VkzuGgYhg9vLNyGH1IChE+yT3KA8odykLnUD3LZA1NYR5c0aFiWLrqFDGU96HnHVLWTiA7hde9KhqWfr4tltqr6PFQwymEZK2BLAoPSaG5hVK5lYlSmOSQwkOjELZ0a9UaKDysprBxYvue2yontu8ZVEwp3nNn5ZTiiBQifKrYozygrB+GJzo7AyqGNDSFeXAF+340LF11ihjM+z1O4U4y7QSyU8gamS33B0s/3zZLUMg43hqncCcVrRGF8AVc3C2Uyq1MlMIkBxSi1CmELdx6tYhClFdT2LjIN7qtcpFvNKhYXhnfWbm8ckQKET55Vy8PKOv3uoUODFIEJmtsCvPgCvb90bB01SliMO9jpxAStdypGFA4ymy5v3FBYYuldip6PNRwCiFZayCLwhEpNLdQKrcyUQqTHFI4MgphS7dWrYHCUTWFjRsexrdVbngYDyqWmo/vrFxqnpJChE/exdCAsn5rWejAIEVgso5NYR5cwb6fDktXnSIG837sFEKilhsVAwrHmS33d1xQ2GIJCr2Z+kw4hZCsNZBF4ZgUmlsolVuZKIVJDikcG4WwpVur1kDhuJrCm5soPCKFbhRfvQYV225md1ZuuzkhhQifvPcoDyjrd3CFDgxSBCZrZgrz4Ar2/cmwdNUpYjDvM6cQUtYi77OAwqPMlvubFRS2WGqfosc=
*/