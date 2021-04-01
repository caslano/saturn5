// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_TRANSLATE_INT_TYPE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_TRANSLATE_INT_TYPE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace iostreams { namespace detail {

template<bool IsSame>
struct translate_int_type_impl;

//
// Template name: translate_char.
// Description: Translates a character or an end-of-file indicator from the 
//      int_type of one character traits type to the int_type of another.
//
template<typename SourceTr, typename TargetTr>
typename TargetTr::int_type 
translate_int_type(typename SourceTr::int_type c) 
{ 
    typedef translate_int_type_impl<is_same<SourceTr, TargetTr>::value> impl;
    return impl::template inner<SourceTr, TargetTr>::translate(c);
}

//----------------------------------------------------------------------------//

template<>
struct translate_int_type_impl<true> {
    template<typename SourceTr, typename TargetTr>
    struct inner {
        static typename TargetTr::int_type 
        translate(typename SourceTr::int_type c) { return c; }
    };
};

template<>
struct translate_int_type_impl<false> {
    template<typename SourceTr, typename TargetTr>
    struct inner {
        static typename TargetTr::int_type 
        translate(typename SourceTr::int_type c)
            { 
                return SourceTr::eq_int_type(SourceTr::eof()) ?
                           TargetTr::eof() :
                           TargetTr::to_int_type(SourceTr::to_char_type(c));
            }
    };
};

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_TRANSLATE_INT_TYPE_HPP_INCLUDED

/* translate_int_type.hpp
PUbMzgp5cp0TAnktxs+FM0LMAKR8Ai2zE/gZiAzTJVxtWKlwrjtpojqw9mS+aKCQPfE/5+3vS+UoM5h+Q5VZ/JviGujttw/6Ig+UHl5EttTiOao3pQPBSwniZrNHICezuNS92OOIaWDz7E6zXrXN8WF4/MojBSwXev1S+16uY1PskFOaldMqjOxU+D6JVxxLRXoMhL5IJb058Fx3YCcBdsK95QiHz15dH1jA400VYY7M406OcLTDmnaKAg+YDzVZO3SYjUji3LITmRZ/j3q4NbHen34vromsu9R9Q1EloEG6LPhKyOG617KyM1Lxv/G2Lq6Ny4JV3G1PDOjz4TQaJi8waftaxfY79HsChbEkFRamiFxfzR+gC3h80hsepbJ7EANNgCLG4AaiBE6oy72KaYCqqgGgYj2K/yzKtYD3yk7a6h9Bp04tYWEdYblx+LOQn2M7LUqL0RA2iTLuq+lTaCdSLn3LfihBlRvSIoijMJbkcy+5XH6s58ahgkQxbCJmiHNmm5QhGhRV0HwfuIjF27SJfSL6XYGyR7P5e+37xLdAYy4Y8qWYLJ/pcA==
*/