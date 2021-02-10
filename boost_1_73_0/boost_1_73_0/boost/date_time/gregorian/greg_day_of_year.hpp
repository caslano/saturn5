#ifndef GREG_DAY_OF_YEAR_HPP___
#define GREG_DAY_OF_YEAR_HPP___

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland 
 * $Date$
 */

#include <boost/date_time/constrained_value.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <stdexcept>
#include <string>

namespace boost {
namespace gregorian {

  //! Exception type for day of year (1..366)
  struct BOOST_SYMBOL_VISIBLE bad_day_of_year : public std::out_of_range
  {
    bad_day_of_year() : 
      std::out_of_range(std::string("Day of year value is out of range 1..366")) 
    {}
  };

  //! A day of the year range (1..366)
  typedef CV::simple_exception_policy<unsigned short,1,366,bad_day_of_year> greg_day_of_year_policies;

  //! Define a range representation type for the day of the year 1..366
  typedef CV::constrained_value<greg_day_of_year_policies> greg_day_of_year_rep;


} } //namespace gregorian



#endif

/* greg_day_of_year.hpp
NiJ/2gbCgYRe/fTTuxol7PMiA7R2cYJdCmlfPAkW9shHniq3R00rja1zU2tLdqbSpZ1Ql2F40h52+fNCYsgAJWGI91B4Da7PlkbAmBsAvLwBgvvpGPc++0zgt4PY21wR1EqVrL6uDmr2AClegNPYg2klPuuoyHh1w4gs+Sl3SjQHy6n0Tp1g88rB4o7M5kA8Ns80UlhxgGrNrQAPXTfyqBegzgcLNuRxzX2zAuvnVPEIVwCyieFdzmvc95LmN8BBrtIw7DXpMq3GvZAT1g/DmpipTpbwE8znrMlyu0o3GXb6bdq9midSPLk+EzbBsUrUHZLrdpClTqea06ES4ALpPgCYh4vNMFde8apUKoFjXBGZY4310vXwUY8AHBcHUyW1OVGeS+ws8Sv41klmbUsdM80lxYjLFjlfhkoNeazeFs4r7B92YrUqU7Rgv5WWyWLCiBGiz2vUIS3NeDx5NyJs3uwywi4qx4F1+NtR8BS5t7tK6U6yMwl2Q1xyYJ4Tt5S6zHV8dGz3Q35HvKmpx/pIDC4NaJDScBB2v6KYqnApNysscgusRGzB1oDBVWTsm/M4ko5Kw+7l+cfeBbB5l4JRGVSYSlIz1o/A3bLA4mvshQYmLba2eKgPu5f9ds8vMG45PK6X20UFVoA6tz3z
*/