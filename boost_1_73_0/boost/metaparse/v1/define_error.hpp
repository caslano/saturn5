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
T2RNNmY9NuWFbM4+bMXH2JpPsx1XsD0/5Oncyg78gR2Zu0F3Zjd24fk8jwPZg1k8n6PYk9fyAk5gGqcxnXPZl4vYj8+xP1/kQO7gYH7PEexU0v2W7Mox7MccZvFPHMU/81peyQm8lg/wOj7Em/gWJ3E17+Z6Tufn/Ct3cCaLH+A+Sh7CWazCuWzOeWzD+ezIBezKRezBJczgc7yNS/kMX2LFUu6V4nFcwVO5ig/zPT7G9/kc
*/