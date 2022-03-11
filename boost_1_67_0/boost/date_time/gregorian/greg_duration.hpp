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

    //! Copy constructor
    BOOST_CXX14_CONSTEXPR
    date_duration(const date_duration& other) : base_type(static_cast< base_type const& >(other))
    {}

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
    date_duration operator- (date_duration rhs, date_duration const& lhs)
    {
      rhs -= lhs;
      return rhs;
    }

    //! Add a duration -- result is signed
    BOOST_CXX14_CONSTEXPR date_duration& operator+= (const date_duration& rhs)
    {
      base_type::operator+= (rhs);
      return *this;
    }
    BOOST_CXX14_CONSTEXPR friend
    date_duration operator+ (date_duration rhs, date_duration const& lhs)
    {
      rhs += lhs;
      return rhs;
    }

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
    BOOST_CXX14_CONSTEXPR friend date_duration operator/ (date_duration rhs, int lhs)
    {
      rhs /= lhs;
      return rhs;
    }

    //! Returns the smallest duration -- used by to calculate 'end'
    static BOOST_CXX14_CONSTEXPR date_duration unit()
    {
      return date_duration(base_type::unit().get_rep());
    }
  };      

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