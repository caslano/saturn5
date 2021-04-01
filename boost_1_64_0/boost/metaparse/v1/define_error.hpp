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
2lJSzmI9wuUdxYRIG38CLsR2d3m26jASPOCDX1I6/v1yRITA/9Ut7c2LIpzoZk/TZijkUYf6SzclGYl4Qge23DYXdc8n01y4elEWDeo5GVc0bihRWQtvy4R3UUNy/aDvr1BB/ela3qSrIjPyoN4VrAUFSkiLKy43r+fLrLb3bZ1Nuw5Vfg7qkJ+cLzYKrS677KmqpwBXmYxekcDRcumE3m2p3UEJp14mzufv7QDPC/JG9pmIgzukiUnD0LUzCSycjpYKBTJQxHS4Q8ccvuyLm/ihDUrgosKN3g514evy0NIU9QXV/FH0mX0MXvjtglsqx6xc4BT9yi/1mWOktQ5jS+rmIpyJ+wyAEh4IY94cdoGDyFgixwKgVVysEsANHzDA7INvr9G/kwKfGdg1qV8tbF6nfMVwesreYWpGz8qZzJQcKocmVTLYBoZbGSfWj5hqk3P0CUJywvesQugyglPBdPD1u3N7IlkP/ztaS13I075z56iVMIrjLsrEz20yh0b7a0YQ0tixlGKHc7Nr573tWHAGoGaggaM98YXQn3igF2DJmvTij//xKj438Q==
*/