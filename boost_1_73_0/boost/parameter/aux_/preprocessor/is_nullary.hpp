// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IS_NULLARY_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IS_NULLARY_HPP

#include <boost/config.hpp>
#include <boost/config/workaround.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
// From Paul Mensonides
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/detail/split.hpp>
#define BOOST_PARAMETER_IS_NULLARY(x) \
    BOOST_PP_SPLIT(1, BOOST_PARAMETER_IS_NULLARY_C x BOOST_PP_COMMA() 0)
/**/
#include <boost/preprocessor/punctuation/paren.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#define BOOST_PARAMETER_IS_NULLARY_C() \
    ~, 1 BOOST_PP_RPAREN() \
    BOOST_PP_TUPLE_EAT(2) BOOST_PP_LPAREN() ~
/**/
#else
#include <boost/preprocessor/detail/is_nullary.hpp>
#define BOOST_PARAMETER_IS_NULLARY(x) BOOST_PP_IS_NULLARY(x)
/**/
#endif

#endif  // include guard


/* is_nullary.hpp
wGDB+hKr27n/labz9J+iuO49+xJJLIPDFOv1oWKHK7YtnSxmjW3WGB0hYZOXI3R4H1TeQfSLkIGBs32D6USfKp885WetzQ84QLZeHkGM9fmrgKlqPZqhe2sVG0Jo2y8w43xmhvuyWN8UK4z0gnm0q0F90yq02XA/CMB6p9hIqghnECQh8nDa9vvIle3csKZVtj7HzbNyFa/Phi1ZZeuzuV66itvbsGWapbQlyM9AZttc7QXe
*/