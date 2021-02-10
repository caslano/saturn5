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
txusciULkGlK3DXBucd3IDr0FcLNDfSuv0ZXYDME15Pu0DNWhCR7N1KnXkfM+S8C9uN2iOn877jrKi/mjwnfS7Ip5aVcI3ecEJYQHqB7N18m00ULbPI9UdP05Evj2BPJXR3BOQpyZbFqZWWyhmdEDRd1ZuwFE7sGSxTkkDXKFEN2fv93lMK5DaghTG3j9/AB+0l2h6M1CY1BbauCd58mj8vpfBawhcsnHPuGzY2O4R6xDEdFvkPXcreTBN5a85kKRkphSY8v+aX/elpDBH91ibc/nD9QSwMECgAAAAgALWdKUhafP1WSAQAAYQMAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMjMxVVQFAAG2SCRgrVNha9swEP0u8H84GvKl4MjuYAOjZZRSlrKyhMTtd1c+195snZEuCfn3k+wm2WhhFArC9p2f3r13JylGx7pwOBeqMRX512887MmWbi4Web4aHvD9NhclsV9gsaNd0Qolz0Alx71iIiawQbtDG7umRKEs9u3BA8qCi5FQprMUrpIElj/EDRlGw/E9mmeuM/gcMgY1N2Qy0C05FCKuiGJfYqQYqdL/c315k0sTtUeyNAh/ETgov2mbwDAq10PgIW7wMxc1c+83HENQpuhw1AEP63vY
*/