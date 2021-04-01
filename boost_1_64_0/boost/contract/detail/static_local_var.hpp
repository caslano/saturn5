
#ifndef BOOST_CONTRACT_DETAIL_STATIC_LOCAL_VAR_HPP_
#define BOOST_CONTRACT_DETAIL_STATIC_LOCAL_VAR_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

namespace boost { namespace contract { namespace detail {

// This is used to hold the state of this library (already checking assertions,
// failure handers, mutexes, etc.). Local static variables are used instead of
// global or class-level static variables to avoid ODR errors when this library
// is used as header-only.

// Use T's default constructor to init the local var.
template<typename Tag, typename T>
struct static_local_var {
    static T& ref() {
        static T data;
        return data;
    }
};

// Use `init` param to init local var (Init same as or convertible to T).
// NOTE: Template specializations could be used to program both this and the
// template above together but some pre-C++11 compilers give errors (e.g., Clang
// without -std=c++11), plus the `_init` postfix is more readable at call site.
template<typename Tag, typename T, typename Init, Init init>
struct static_local_var_init {
    static T& ref() {
        static T data = init;
        return data;
    }
};

} } } // namespace
       
#endif // #include guard


/* static_local_var.hpp
TPMhEx73FHBL7uXBiVXhZrcK2iznQ54F+KTiCV2DykZ8NdFbvQL7u4bYZhxfqndGzi4ubYU+5RqD//Ca1sdxoBPZOIteUi4uzSckxD3ASKHarIE+NqiCRUJV5GR8M4SUIi82iAni6Tf9AxVyfXHAnBr8io014h5kE0WVbJgAKVVqTpq0mYiem7FXVf+cy7/hlKvZjslypNz7X1DZ5Yc+Dkif9AfIRogJA1+VVARYLZrZ+m5r5Fb4fvxAiK8jntF+pAfInJBvf/OU3aAR5xSGtF9enxhsg1rU0VVsr5iPi2QcvXmeCIA6qBqgLXtRLTdiJylZfPJuK8XLR5WoqiOOEbzbNocEZA4/p4S2CyxzrtcCd47VwOE3p7w78ovJ9Qf0rx6VgonCiI+n6RA//7UoHWC5DsccUmdJp9y1tEI8P8rG1Q2s7s76Ij2JUHSxnm/A9CeezbmJVAwSCr54P3t3sQsMkczxoqhXKUqjkQ/CAG9azXs21kNioayj5z/itLpHJofe0LcCoTSet+mPQGcaQ6G9MRhggEFrjR6jYt7/DdLf/r92w9JyVZDyOg==
*/