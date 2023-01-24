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
3ShcfDZnC/K0IDR/wbQeatv3/tH64Sy8gEL72xYWiH1tQ4IJj55of+89XAM81uSZ6fF86hyGnvyFm2hugXFlIDUZHbd0UuHVlMB3do/iHWRv2J3xsjt5ad9n45I8gvp7EjnfgFJnJ4qnhfuF2LYz0CXdTc4san9IMwa6DyFecRL3rIj/e8306sbTnP9Zkcpx+RIWWdKxxcJ4HMpytUwFq1AOWksTgoIVblm7YUaXyW+jot+4cF5sd5i86CLJ/wnVG0eU5oy9OYc9N0r8FS4KlFGQ2cVbqw66TimvP5rT4ZJoPtKaS79I6UL/wxrN2pcoOMnrZxubHrL+Ra8z+s0Q2AlkcXF6nglxOzbCjNRgbnVHGiTu7ivZqOiCLUJcL4U7+huNlp3AYXhZ6bbzyJ3IhYmoB4V3cFx8pPEtRzsmbk9eL+icxUfTGihj9yve1duHOyxlSuKWy9JkDNe2oH+TsErAYa87E2VM/im4UKe/yEpDi0Pp6zy7pQ/ryrrbowux9ybw5OO3C12359OYDTHRghrMw6rrReFdzW5pFTxCvVGjKnLKDkrBqC8XA8+SI9rTnKBEFIwojyMoj9xwpVcg2afoyvoCasms6TPte6bf9y8Z4a/rKdg9Xx+Powynb+a/fvLv/+726VHMZK3L3vdcTVPkd7nBhd0m18BTMxBYrHrHKPXOddAmqni4eFTEtW5b7B7vLsYM/GYR/yTF
*/