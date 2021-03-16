#ifndef BOOST_METAPARSE_V1_DEFINE_ERROR_HPP
#define BOOST_METAPARSE_V1_DEFINE_ERROR_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>

#ifdef BOOST_METAPARSE_V1_DEFINE_ERROR
#  error BOOST_METAPARSE_V1_DEFINE_ERROR already defined
#endif
#define BOOST_METAPARSE_V1_DEFINE_ERROR(name, msg) \
  struct name \
  { \
    typedef name type; \
    static std::string get_value() \
    { \
      return msg; \
    } \
  }

#endif


/* define_error.hpp
tqO8j+oEkuPMZlvGf/EtxpwAsmy+SzNH42ohroME3aPWa5tcrrXzXRqd60Ticlp5+YmHfdzlSsx3aXQuyqDqGgXdoWfMu8flys93aXSuk5nawvMfHelzuT4036XRuVYR10JB980133rS5bp5vkujc51CXC2Cjg1NneVy/XC+SzOHHbrAzX2d9yDVfL+S+sRB3W738NZ4/9EsNu6JrtN9fNjV2dbZaT607Ora3LUZv5dHR2qVplT055v8EJOEpSE=
*/