//  boost/chrono/utility/to_string.hpp
//
//  Copyright 2011 Vicente J. Botet Escriba
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_CHRONO_UTILITY_TO_STRING_HPP
#define BOOST_CHRONO_UTILITY_TO_STRING_HPP

#include <boost/chrono/config.hpp>
#include <string>
#include <sstream>

namespace boost
{
  namespace chrono
  {
    template <typename CharT, typename T>
    std::basic_string<CharT> to_basic_string(T const&v) {
      std::basic_stringstream<CharT> sstr;
      sstr << v;
      return sstr.str();
    }

    template <typename T>
    std::string to_string(T const&v) {
      return to_basic_string<char>(v);
    }
#ifndef BOOST_NO_STD_WSTRING
    template <typename T>
    std::wstring to_wstring(T const&v) {
      return to_basic_string<wchar_t>(v);
    }
#endif
#if BOOST_CHRONO_HAS_UNICODE_SUPPORT
    template <typename T>
    std::basic_string<char16_t> to_u16string(T const&v) {
      return to_basic_string<char16_t>(v);
    }
    template <typename T>
    std::basic_string<char32_t> to_u32string(T const&v) {
      return to_basic_string<char32_t>(v);
    }
#endif
  } // chrono

} // boost

#endif  // header

/* to_string.hpp
Q+kv22TAHmlFIBAq7cDnOCp5lhxNTptMXBiubfphS0u/NvYSEBxApxLU+515p40PWfqQG6OOwmulGeb0ZQ0s4VDKhs0qCC20BGc6cnNO0XZOD7rVtjlIQKOqtqHttmSdYoIILU3tyg3llsf+2tCqFEjkEU0+BqgApPPYcBdNtUF6Obc6JMGelAe/TRjSXlXyhiNrAfrhFcsyLe+2Z9NlwBVznIUoQ6rRHSAOqX4MpGxEe1/WSFhkWcMlQUER1OzGrCgIAZh4TNT8zbDcfEXPSZiE08H8dDqiP/rHp4OI5+ZgMf5AOwe7eCUDOjHODQqNjNcYJeYyDlL9R1rTngD1pbUgpkkRyYZvjCgZ3hvbmcyVRhv2WNJMmFYCe8HWtZC4iO20YizjyXwxmE7H08PTd+8G00608M8ECiPwy9Tj1shGYaiHQDdFFr5gGrQV+A5VoqGBfc3iss5Z1GFY3aSJmt8OSK7Z4M/+yeR4ECU6j5pXTRDzL3Rvwu6+ilS+w4u79G9EdPPGgrxe4fkBcF6Iqcscl5h63ceWvBb4AJBJaiq8ymANJ1shu+aGeNvu0xKdqlfd1n9RkquQSW82GFD/eDbGq/Fweg8/9VBJIHiAs9u4tWlGM5h587a9a7o1uLeMt0lws/U/UEsDBAoA
*/