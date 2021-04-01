
#ifndef BOOST_CONTRACT_DETAIL_NONE_HPP_
#define BOOST_CONTRACT_DETAIL_NONE_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

namespace boost { namespace contract { namespace detail {

// Tag for "no type".
struct none {
    // Some lib code use this to avoid unused local var warnings on #if, etc.
    static none& value() {
        static none none_value;
        return none_value;
    }
};

// Transform `void` to `none` type (for convenience, instead of using MPL).
template<typename T> struct none_if_void { typedef T type; };
template<> struct none_if_void<void> { typedef none type; };

} } } // namespace

#endif // #include guard


/* none.hpp
iiTLaQFOrb0hto1xfU/+2eI71VNs5SMkORGST79ZsEH3wPbbGGSuLdEn5v+4m+OLruF9RQlyCzGMSAgeCZoTaK2WfxzksOTgG37bkNu7QYBF3KZXfrjXGiLK5mrLcLwNdk7hC4sVUlP5Q/7w4u3qMfg4XtLAs5aDjW5z88s/9vMy/d/GLsKCkiUYqmIpd7XBxvXEgSSVuWZcZOuDGyyU4PNgXsuJaPkfN/fA1JT4B0Hnf9uN8SmCK1QcugsLAWNw27NuSGLwuleD/UVuce9hAK5FYafP4X6dzktXWRRTOZFhljcPjMEnRZct4ciLdQOeYMufUMBK0mtkSfBnKQ19Z6luc1yca+FNE96/F56sMA46pttAXeBOkjRtEc1FhOx3btGFF/Lrc62Ai2g/Nb0s7a/zS3q2Smpb5TU/oayDoLHoTUNG4bLRspxQwk3hhLbrUdzOfb6EWxCrKe6/Na8MWjee9BMIW6taZumWoXBfhlh41WjdoF97V4iGeIyp623I6jGoALa7y1DpQL/RtFYdLTdOl3UNCrFVKh1fZNgEwEba9tlRZm7cioaJTw==
*/