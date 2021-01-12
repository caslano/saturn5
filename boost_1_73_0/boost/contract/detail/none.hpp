
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
Y+Gt8GC1T1L7I0SyEj4Gb4NPwvvhW3AV3AbvhJ/BNTCH690NC+A9sBW8DxbB++HzuvYxlHqrwZSv/OV7R3f23dLxHXe+37Oqk9nzqfsj4/d+lnT++fs/f629nw37Pn98fWb7PZ8/vtfT3eeJ7NSfttdzIxvvt+T976/f/Jbj//Lq6Q3D/1+49u+8a7QooKyn0Z9ZfEeoulb1BozJOI2+qLu++2/R4k6xuQ5MhjlZ1GOC++5P
*/