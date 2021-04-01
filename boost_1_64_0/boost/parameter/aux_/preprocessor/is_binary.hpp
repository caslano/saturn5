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
m8OGcCer9MfoMwZ2E2qVAyWJeqcJttmXvcpZiIR8E5FrVHpn87So9NGk5HFidBDHLekEtYxgo248fWRStEgp52Scu0xo9RVlOua/arKnU7iSSH/GfWHBIelNKI1MajxpPhfeUUswyOglYnrPiAP/aw28NfHoyf6zwaw/2Goj0LkAqT3jkIvae4oLtVE1g8nkGSLtEdVEAvD2DWk5w1dHMckKA8GKXT88a3EFetZr55WXfYkfTg3vfQZf4cQR36ZuWQ3wplsxh9lIJ7qUtV+hTIQw11eMlYIz2EemxPuYvhoM94OCo1ife0lzTkme1Xo0lnEE8gwIm8g5PpHaJRxdnXwxT3XmhnL4/6swY0aosm9RGjjol+u4bldEL+T9j8L0Gs1ox6jIEUV92dmXrcrxP29QJuCppvDE7SyaCvAwgFUOCzTECmiWEwjM9B5Yx6gbkawA91Qh1lInYxhM9dJ+p/TWfnpjVFHY63u9/pOwxq+2dgGTaIDAYQXQGB9khgaE8ywT1cGrZUcYnjoCDe+GU79COpSMza5ayB8qulEljEJvTNd1U3+c6A24qA==
*/