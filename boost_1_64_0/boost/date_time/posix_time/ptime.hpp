#ifndef POSIX_PTIME_HPP___
#define POSIX_PTIME_HPP___

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland 
 * $Date$
 */

#include <boost/date_time/posix_time/posix_time_system.hpp>
#include <boost/date_time/time.hpp>
#include <boost/date_time/compiler_config.hpp>

namespace boost {

namespace posix_time {
 
  //bring special enum values into the namespace
  using date_time::special_values;
  using date_time::not_special;
  using date_time::neg_infin;
  using date_time::pos_infin;
  using date_time::not_a_date_time;
  using date_time::max_date_time;
  using date_time::min_date_time; 

  //! Time type with no timezone or other adjustments
  /*! \ingroup time_basics
   */
  class BOOST_SYMBOL_VISIBLE ptime : public date_time::base_time<ptime, posix_time_system>
  {
  public:
    typedef posix_time_system time_system_type;
    typedef time_system_type::time_rep_type time_rep_type;
    typedef time_system_type::time_duration_type time_duration_type;
    typedef ptime time_type;
    //! Construct with date and offset in day
    BOOST_CXX14_CONSTEXPR 
    ptime(gregorian::date d,time_duration_type td) :
      date_time::base_time<time_type,time_system_type>(d,td)
    {}
    //! Construct a time at start of the given day (midnight)
    BOOST_CXX14_CONSTEXPR 
    explicit ptime(gregorian::date d) :
      date_time::base_time<time_type,time_system_type>(d,time_duration_type(0,0,0))
    {}
    //! Copy from time_rep
    BOOST_CXX14_CONSTEXPR 
    ptime(const time_rep_type& rhs):
      date_time::base_time<time_type,time_system_type>(rhs)
    {}
    //! Construct from special value
    BOOST_CXX14_CONSTEXPR 
    ptime(const special_values sv) :
      date_time::base_time<time_type,time_system_type>(sv)
    {}
#if !defined(DATE_TIME_NO_DEFAULT_CONSTRUCTOR)
    // Default constructor constructs to not_a_date_time
    BOOST_CXX14_CONSTEXPR 
    ptime() :
      date_time::base_time<time_type,time_system_type>(gregorian::date(not_a_date_time),
                                                       time_duration_type(not_a_date_time))
    {}
#endif // DATE_TIME_NO_DEFAULT_CONSTRUCTOR

    friend BOOST_CXX14_CONSTEXPR
    bool operator==(const ptime& lhs, const ptime& rhs);

  };

  inline BOOST_CXX14_CONSTEXPR
  bool operator==(const ptime& lhs, const ptime& rhs)
  {
    return ptime::time_system_type::is_equal(lhs.time_,rhs.time_);
  }


} }//namespace posix_time


#endif


/* ptime.hpp
dpogPlv1E+Xcw3ucOy3HfCkMZhXkqKV/vyrMe8cVnnXvAb2ZlGSVPXD2+azoErrWDoHpFlXZHYPSYdVnViEfLx1CBGvjgODoswLFL+f0hmIDocDvNUmNOgSf+Afix5P7NRQ9+ozSVWKQJrXk+vR3fNor0ir8ZS5oeVHuVjsjVnySAo1wvCCGIhU4ojNEGnwMCnF5hC9pi6X1h5hu768nsZKBGrzfolBtFBp8B2nw2/eiBv/sKQ3+1O9N+Ktzja8seYDtFc9Dxl5pJ3vlWWOvLKVNE05m1btBzf+js9Fuwdlhogn9u4zdcuWM8nT6/few3YKGjHv4zi1wlOHlQsqRE3CFAkEbETGyW6jOuMfYbukoJLslRnbLs2ReHGC7pZ7sFjvezTuN3WK/wr9V/eXDkMn3A2kSMNktEtbIb6ftlmlU/oD0Yxq506A9B8tPZ7ulgf2YS9U3CnF3Ej4xroWk9GN+4XThxwy7+DHDffZj9tVrNtnNX+VeIDdTgQHuBWTbMvtSwyfS0L465l6PhuZlKuDN3BM+LHIiDe2rc/D1aKgvc0NzsMiJtCNjgex8sX3oqpy+94Qnmg1P9FYgJ3Nf+rHIiTQ0Y4GMPZGxwIBo34SZE1dlI8zCmX3r4RNpR8YCGRuasUBetG/SbnJXn+V+buauQjLDJ9KOjAUyNjRjgYwoMg7Xic/QAZn7Mg+LnEhDT7xARm3ixLnqxBfZPMe+JBN2/le0/d2EgVjrzgPTURjHr50prVT7JlWBqgxw2L4Oafs6ZLGv9/QK4jQAQdZtiK1b3he4/35tX0fRfa3t6xcxTe5C6e/N2u3reRKtbYtsh7avm6z4JAU9vgveRmcgOKo3SvZ1IxSi8j13yBpRz5X79WvKjTIs7esDuPm/StjX7WRfV38V7euuU/b1qd+pX59/jvZ/Au3/zxj7fyfZ/2TT4tENaf+HPSJZ2P/F08D+p2MPtB2Z8H/Z2P8fnVieTr//U2n7P+CV5yXgsmuxO3mLOjqfjA+iHHneY8Wn7PY/1xn3Nbb/Zw6y2f/HyEx/0W7/2/Fu3pad/f+LgVBJAkb7f4CENfKrafv/Pir/osX+H2Cz/4c52f8D2P4P1eweYLf/h70ucUz5mQoEMhUojGZjwLzekVAF0b6RmVG5mezQE9moeScYbJXROM/YjozKZn40GyvpBKOxMprWGTkzI+NlZN2M2miBvUCfebs/IsIytiNjgYy2d8bpc+KjkXECZlT9M3Z2xgL9ERmXsR0ZC2S0FzPO8YzDlZEjMkqJ7OysUGbzPnQiVGQskNE4zyhnMnZ2X8fTwXrP3FV5WOREbO+MczxjT/S1sx1M68wNDWCRExEkGadPxp7I6FINZG5HfvREpXZG1s3Y0IwKR37mdhRET1TeZeTMjA3NqHAUZG5HYfREZU1GxsvY0OzUBceYaGU9Pb0j7XoKo+vJxEeHlANn2Zi0A2dAD7/Rx1VlgMOup7B2PYXR9cQgxvYK4ssEwoRGS9fTmTt6up6ad9hdTyI6O5R2Pd072gVtGwQ+u7iewr25nu49LtfTAKvryZvPdhi6niz22opLhevpWXI97f40up4Sp1xPp36nfv+fP/d4/n9sZv/Yoa29xPOHbfH8EfCLlTvE8//lE2m/2DARz/+JTVnG81/9OeUXW+VziOd/+yYdpAchftZ4/oI72S92no/8YhVu8fzVLvH8TWvTfrEQ+8X4IDVeiFndqv4ln/U6xvPnS1i+T6f9Yvd6neL5sTgvUlWJuhz2i0U4nj+8MRFAia78YpGa3fkWv1hT4pYcW7R3Ey4j+gocAIYhlh3cX4G1EUzA24prH28SN5p0HjpXLy6dyfxoIX/TAtSQp9M=
*/