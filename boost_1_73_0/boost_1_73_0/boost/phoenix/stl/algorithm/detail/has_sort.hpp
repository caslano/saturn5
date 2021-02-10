// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// has_sort.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_HAS_SORT_EN_14_12_2004
#define BOOST_PHOENIX_HAS_SORT_EN_14_12_2004

#include "./is_std_list.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_sort
        : is_std_list<T>
    {
    };
}

#endif

/* has_sort.hpp
IgpE5hd/lKJS/UAqsKz9WeNyP2GAsUMr5G6UL2rSIvOIXpuKAo+H93C4/wVQSwMECgAAAAgALWdKUqrGPOheBAAAgQwAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy90ZnRwc2VydmVyLnBsVVQFAAG2SCRgrVZhT+M4EP2eXzEbkJrehYSuVnsLXVZwwHLVSQW1HAhd96o0cRovqZ21nQJa2N++49hpGw4OdGoRjTN+b+Z5PB53401YShFOKAsJm0NBRO5s/LK+j7MBL37G1f8YP/jUhDPBv5JYPQ0ej+/B/CFphM8XQoSwZNyP2/Ai4x68ijG2MT7q8Xj8QpiRFqa/Qk0cjfUQLc4G8g55cSfoNFPgHbahs7PzAbbg7fbbbR+OIkZJDkNF2ISIqQ8fk8qyn0W3t4Ekn3wgCqI8qBydZ1SC5Km6iQQBHOc0JkySBCIJCZGxoBN8oQxURiClOYHD07OrXv/Eh5uMxhn6uOMlyIyXeQJZNCcgSEzo3LgoIqGAp8hG3wmVCv2VinIWYGgCioiZRBc6eJRLDtE8onk0wTCRgkypQu6GYVyKHJWHCY9lGNdLDzI1s6u4QgWz6A54oUBxKCXxQeN8mPGEpvqJqUBjUU5yKjN/KQUDsSTkAiTJsVA1jRJpJBMY2sz4
*/