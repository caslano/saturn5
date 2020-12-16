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
NcjYv9bmUfY+AVLv8T4BUieQcadkDyoCZBwI9wBl4wkQHXevPAGSoDE0gqwiQEa2cCiquYCs4htkrsu2Ab/LtgE/3OAVv9ygQSBD8/L7YrQydgCEsQSt7Z4S9IpDwdVZgfpohMwbQsquKcXwKE7NcgU7xSh7HwB5pcf7AMgrDDLZqZ4231lTD1A2HgDRcffKAyAJGkMjyAYEyMgWDkU1F5AN+AaZKwEd75eAjvezy9H0u8vx+Thi8whdflSecBzuYDiN56OVlKOmQ4G/DgWf9+pxuoo42qB0NzXguCGtzaPs93BHs8fv4Y4mgY+6KXuDeGSNmOwNym0Od0DJuWUTSiENuvGIhkYhJ4LdcjUXFI5nFHp+Vu+61zbod69tUKAw4YbC78cZjIyHOyaBHM3LT+HRiuNwxyR8IoMPxVGy0BIp2INTQWMfmdDpKuJoY0I6daZRyA1pbR5lv4c7vu/xe7jje0ah7OaEbb7gp96g3OZwB5ScWzahFNKgG49oaBRyItgtV3NB4aBvFCZM71l9bQkP+4XpsIDpBG4wTU5iMDIe7SCYovnfHWxIOI52MLZgYLdA2Uw6FPjrUFBy+iZ0uoo42iBgwDVlgBtibR5lv0c7khP6PdoBS4Ipd5N7g3hkjZjsDcptjnZAybllE0ohDboZb8Pi5QXlgj0ndHrMpzvavLz4jb1zB3GviML45qXxvY0g4iOiQsBmwWbTRVBJYbFlsNpGiNgEtIiFqGixooKFhaXlv1OsAlpEtNhCZEsL0ZRrZ6eFr3yz3zd+jufuHcVGyG12z5wz58yd88u9dx65ebnmnv1B7T37g5qr5T13VF4tR8QQ4ZP3LuU+ZfboSOzAIEVgtu4xhXlwBTt/xBqjUpFjMPH3OIY7ybQTyI7hdW9HhqWfb4uldt55PNRwDCFZayALww+EodxalxDDfMJ9yjGGKHcMYQ7PXjPCEOWVGDaOTz6sHZ98WPPoOL6j8tHxiBgifPLepdynzB49EjswSBGYrbEpzIMr2PlHrHFUKnIMJn7sGO4k004gO4bXvR55XGDYYqmNdx4PNRxDSNYayMLwQ2Eot9YlxDCfcJ9yjCHKHUOYw7PXjDBEeSWGjXMxN2rnYm7UDJOP76gcJk+JIcIn713Kfcrs0anYgUGKwGwdm8I8uIKdP2WNaanIMZj4Y8dwJ5l2AtkxvO79yccFhi2W2prn8VDDMYRkrYEsDG8IQ7m1LiGG+YT7lGMMUe4YwhyevWaEIcorMWycd/64dt7545opwdkdlVOCJ8QQ4ZP3LuU+ZfboidiBQYrAbM1MYR5cwc4/YY2TUpFjMPEzx3AnmXYC2TC89ncEZwWGLZbam+fxUMMxhGStgSwMPxaGcmtdQgzzCfcpxxii3DGEOTx7zQhDlFdiOGjCcH2rDSquw3Bds/wxv6Ny+eOUGCJ88t6l3KfMHj0VOzBIEZituSnMgyvY+aescVoqcgwmfu4Y7iTTTiAbhtf+KuG8wLDFUpv3PB5qOIaQrDWQheFaGMqtdQkxzCfcpxxjiHLHcE0MvWYDhut/guH1+6tuaiJ1c2tgFC6t1ZC6qCV1SVIRPnnvUu5TZqcvhRcMUgQmdGEK8+AK5mfJGstSkWOQjYWTupNMO4HspF73kuZFQWqLpTYAejzUcFIhWWsgi9QNSTW3UCq3MmEK2ekRbygnb/RMUr1muKK84Ypy63sSGq+X57XXy/Oa2/aq9rb9GilE+OS9S7lPWVO5QgcGKQKTtTKFeXCFZn1vLl0dFDGY95VTuJNMO4HsFF73iuZVQWGLpXb/eTzUcAohWWsgi8JzUSi31iWkMJ9wn3JMIcqdwnNS6DVDCs9rKWx8eLyofXg=
*/