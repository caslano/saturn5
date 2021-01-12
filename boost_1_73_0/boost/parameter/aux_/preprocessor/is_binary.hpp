// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IS_BINARY_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IS_BINARY_HPP

#include <boost/config.hpp>
#include <boost/config/workaround.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
// From Paul Mensonides
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/detail/split.hpp>
#define BOOST_PARAMETER_IS_BINARY(x) \
    BOOST_PP_SPLIT(1, BOOST_PARAMETER_IS_BINARY_C x BOOST_PP_COMMA() 0)
/**/
#include <boost/preprocessor/punctuation/paren.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#define BOOST_PARAMETER_IS_BINARY_C(x,y) \
    ~, 1 BOOST_PP_RPAREN() \
    BOOST_PP_TUPLE_EAT(2) BOOST_PP_LPAREN() ~
/**/
#else
#include <boost/preprocessor/detail/is_binary.hpp>
#define BOOST_PARAMETER_IS_BINARY(x) BOOST_PP_IS_BINARY(x)
#endif

#endif  // include guard


/* is_binary.hpp
cRtrT7aNtfG25Jn21SbaEem5rI21I2TLeVrpHaTDCj8PujXxOneIDksMJ/rTKVu/vHadP8A7jE3bxTNBMfiP91VYV9ptO8R60m7bINqynbc/tGW7bXv4zLZybR/VztqKrRuKYZugutGObcDarZ3qsmlz7by8sS9qJ7uY57PRDwnap53KVMdpbmc2tm2tnZeRkd3K46WNHVe2y3Kw+WlTHMvA5qdd2jxu+Sq0YSaVTnFbH6r4
*/