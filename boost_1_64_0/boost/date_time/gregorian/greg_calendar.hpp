#ifndef GREGORIAN_GREGORIAN_CALENDAR_HPP__
#define GREGORIAN_GREGORIAN_CALENDAR_HPP__

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland
 * $Date$
 */

#include <boost/cstdint.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/gregorian/greg_weekday.hpp>
#include <boost/date_time/gregorian/greg_day_of_year.hpp>
#include <boost/date_time/gregorian_calendar.hpp>
#include <boost/date_time/gregorian/greg_ymd.hpp>
#include <boost/date_time/int_adapter.hpp>

namespace boost {
namespace gregorian {

  //!An internal date representation that includes infinities, not a date
  typedef date_time::int_adapter<uint32_t> fancy_date_rep;

  //! Gregorian calendar for this implementation, hard work in the base
  class BOOST_SYMBOL_VISIBLE gregorian_calendar :
    public date_time::gregorian_calendar_base<greg_year_month_day, fancy_date_rep::int_type> {
  public:
    //! Type to hold a weekday (eg: Sunday, Monday,...)
    typedef greg_weekday         day_of_week_type;
    //! Counter type from 1 to 366 for gregorian dates.
    typedef greg_day_of_year_rep day_of_year_type;
    //! Internal date representation that handles infinity, not a date
    typedef fancy_date_rep       date_rep_type;
    //! Date rep implements the traits stuff as well
    typedef fancy_date_rep       date_traits_type;


  private:
  };

} } //namespace gregorian




#endif


/* greg_calendar.hpp
1NXT2eZdb6uC+kk9W1d/D38o49bC6ioR0/Kgsad9pKfdlSd7lkBKcvA5x9PuPp2u5pauZrc7NYJCrrnBZyYv1nETTLTdTJEHDfE1fhauXmu04mtM9UPn8Z0mPZ3YcMb35g/+41tNulqpIeIb/6lLfMdsy/Fx/5yT6rc/adBaQ4U+/FZwX1T3mC4xKx5Zm+yIE5UtfkORvWYS8y8McWfZiMNdEZEV0Surecl3348eWTtoLkRsaXmhuaAt3zuxUO2jbe1f7aOFvih+rxlYwgP/spNjlkuwZURdVbP5tspc9SFtm6L3x1h9mCw7+1k/+aTP/FoYv9t+tMeP5xzMVviLLpQOH+iL7LUUbsv2bcqWYpiythB3JdxlcVf+qI/nf57zPpp+rPLvlBGdjkVWhwUGoYRBKDbL39pjNuFCtQ+eoI4UlSKtxsIetg9uJaltXx5aJZm3kgdPakuGCknk9aNxdrNUQmrV33nwdXaricw49UOgvOyIpsuQl5o3fzOW8BLJYb8s5CKNRZ1wZ+enGbOcnC11wlUarQDS6Pty5nsA+X7ke/q9HJEetAfy2PSw+tsaxoPmYjml9gilRKElpPSTkCxbo5wmWyqmhtR/yNrc6vdHSUiP1oZG0N549OOSXpUDyvMG0ZY7KFqpTo71z+5KjtxzuUzmXM6ugJ+LzkauNcdUYj+MQltoLeUgU8un++0KWpRjUU4BMhOZ7Igh9EJ1ebTOc0SOWulvFQ6vJalPyjVc9NMn/jyTZJUQU0zSLrB9Fos5K7L3xFjsFW38TGTf0u+NphdrVvZV+GBHLA3ZYQEOOeytC0krrkx4PI9ZVusckBv4OyHXER6R3+ai32o8nkHwoXRfoItZDAFSRWhaWA3kwpGD5saMsp+yWv24SapbzBRZtrqNKty5J86nxOH7A/UMVfDaUI0EQMFYb2aSY9hbXCm5cUpzgVvntDvAZ60AJK0+BA1Wnq2nxZVY7tlPkK05YYysghZZLLIQAoNNRTRaR1yEqIieWAsMngIDRMnnZoBUILQgrBDYLLa30ECJwFYeA1uZwEZT2xjYijbYOFIMNv0Kh8cgpQfwXbVSauHr0IcG/zVnUlY4BnOACWTPfmWDTJ2vuQJxHDTDstWlkffjpq5uNlNEcbw5N58pMjr1QgfNGVmoxlaHAB71RCSCcctAMnSErTm88TOWFAfH1Y8sqZfIxxKEElGbuQnGxpMDC/Pqbs9e5TRn5yWJu4j9o1Y39sLkd24vILfSGT+CU3CW3bP9lJLhSk7Pw8TN1ON7qihron8qlCV1KEtyKEv+rsFoJ6GUxkIp6dWIWyhR11BifyqUgg6lQKEQL9NuOwnF+NtzCyXmGkr8T4Wygg5lBQ5lhd81GO8klP6xUPo5lH63UOJ/CEXPsofXFL2ke5ppWYZ7nnRYNix+ec3EMa27Dyo/j47yL3WyI2aI/tXfoqWHyuKhsv78b7EyNlQVHqqK/9+iGKqkYaiShqFKOoZqtM4j9ZI6B2kH+6+arP+Dl3G9vcEnrfUNT2WYVmJ02BPpiuw9znq0NqquDw6Mi0espXgZb/wU9lpG5Y+2SZTrfrX/0/rxPd+w8q1V3z7qmfZKxH6mvbuB/UzbZUM807bYB8+0KqayuZUPuGTUcNU9ZmIJrSbFudTxmqjtaK+Y0TIZo3HG3JhmfEtzh92gvTl1SnrQln2ozhJbE2uv0t0gu6PbakRdGBMeDlqnqL0ie3FTNegkK7ANl1CGe49rmeI3+tFUCz2nDb7bK23RLxf/m+x6uSdQtstZvcjPiHHh5ZLso15IYVE5f+u5e38jZd3BJnoQZn0Wg3D/BykMRF653zf20ZKtLozWdX8se6bgxrg=
*/