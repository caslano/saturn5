#ifndef GREG_DURATION_HPP___
#define GREG_DURATION_HPP___

/* Copyright (c) 2002,2003, 2020 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst 
 * $Date$
 */

#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/date_duration.hpp>
#include <boost/date_time/int_adapter.hpp>
#include <boost/date_time/special_defs.hpp>

namespace boost {
namespace gregorian {

  //!An internal date representation that includes infinities, not a date
  typedef boost::date_time::duration_traits_adapted date_duration_rep;

  //! Durations in days for gregorian system
  /*! \ingroup date_basics
   */
  class BOOST_SYMBOL_VISIBLE date_duration :
    public boost::date_time::date_duration< date_duration_rep >
  {
    typedef boost::date_time::date_duration< date_duration_rep > base_type;

  public:
    typedef base_type::duration_rep duration_rep;

    //! Construct from a day count
    BOOST_CXX14_CONSTEXPR explicit
    date_duration(duration_rep day_count = 0) : base_type(day_count) {}

    //! construct from special_values
    BOOST_CXX14_CONSTEXPR
    date_duration(date_time::special_values sv) : base_type(sv) {}

    //! Construct from another date_duration
    BOOST_CXX14_CONSTEXPR
    date_duration(const base_type& other) : base_type(other)
    {}

    //  Relational operators
    //  NOTE: Because of date_time::date_duration< T > design choice we don't use Boost.Operators here,
    //  because we need the class to be a direct base. Either lose EBO, or define operators by hand.
    //  The latter is more effecient.
    BOOST_CXX14_CONSTEXPR bool operator== (const date_duration& rhs) const
    {
      return base_type::operator== (rhs);
    }
    BOOST_CXX14_CONSTEXPR bool operator!= (const date_duration& rhs) const
    {
      return !operator== (rhs);
    }
    BOOST_CXX14_CONSTEXPR bool operator< (const date_duration& rhs) const
    {
      return base_type::operator< (rhs);
    }
    BOOST_CXX14_CONSTEXPR bool operator> (const date_duration& rhs) const
    {
      return !(base_type::operator< (rhs) || base_type::operator== (rhs));
    }
    BOOST_CXX14_CONSTEXPR bool operator<= (const date_duration& rhs) const
    {
      return (base_type::operator< (rhs) || base_type::operator== (rhs));
    }
    BOOST_CXX14_CONSTEXPR bool operator>= (const date_duration& rhs) const
    {
      return !base_type::operator< (rhs);
    }

    //! Subtract another duration -- result is signed
    BOOST_CXX14_CONSTEXPR date_duration& operator-= (const date_duration& rhs)
    {
      base_type::operator-= (rhs);
      return *this;
    }
    
    BOOST_CXX14_CONSTEXPR friend
    date_duration operator- (date_duration rhs, date_duration const& lhs);

    //! Add a duration -- result is signed
    BOOST_CXX14_CONSTEXPR date_duration& operator+= (const date_duration& rhs)
    {
      base_type::operator+= (rhs);
      return *this;
    }
    
    BOOST_CXX14_CONSTEXPR friend
    date_duration operator+ (date_duration rhs, date_duration const& lhs);

    //! unary- Allows for dd = -date_duration(2); -> dd == -2
    BOOST_CXX14_CONSTEXPR date_duration operator- ()const
    {
      return date_duration(get_rep() * (-1));
    }

    //! Division operations on a duration with an integer.
    BOOST_CXX14_CONSTEXPR date_duration& operator/= (int divisor)
    {
      base_type::operator/= (divisor);
      return *this;
    }
    
    BOOST_CXX14_CONSTEXPR friend date_duration operator/ (date_duration rhs, int lhs);

    //! Returns the smallest duration -- used by to calculate 'end'
    static BOOST_CXX14_CONSTEXPR date_duration unit()
    {
      return date_duration(base_type::unit().get_rep());
    }
  };      

  inline BOOST_CXX14_CONSTEXPR 
  date_duration operator- (date_duration rhs, date_duration const& lhs)
    {
      rhs -= lhs;
      return rhs;
    }

  inline BOOST_CXX14_CONSTEXPR 
  date_duration operator+ (date_duration rhs, date_duration const& lhs)
    {
      rhs += lhs;
      return rhs;
    }

  inline BOOST_CXX14_CONSTEXPR date_duration operator/ (date_duration rhs, int lhs)
    {
      rhs /= lhs;
      return rhs;
    }

  //! Shorthand for date_duration
  typedef date_duration days;

} } //namespace gregorian

#if defined(BOOST_DATE_TIME_OPTIONAL_GREGORIAN_TYPES)
#include <boost/date_time/date_duration_types.hpp>
#endif

#endif

/* greg_duration.hpp
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
*/