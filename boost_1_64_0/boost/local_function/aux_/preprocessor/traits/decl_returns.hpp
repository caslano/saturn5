
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_/index.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

// PUBLIC //

// Expand: pp-list of result types (size <= 1 after validation).
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS(decl_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_MAX, \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_RETURNS, decl_traits)

#endif // #include guard


/* decl_returns.hpp
/GWqNMWySDV3ggbRSOl0mCP9n0GNLJH3T9xxttl5XOiW588efJq7BFYz93HUDuk3M/47+EnZrg6ZWp9hl6RNDdTCf0pIwGMJ/I/LG31XUNocp53Rr4BeVpDLYrF9RpmiOYuylcepGyK2yqx2INmnhX6IontsE33VfYwlT1nAwe5awSy9OGFvSpgW85HlnbvGWQEpCo53toeLeS2zYuOF5+xs1mOhDXhCQ6nDZdLlXk9M4N2u+5gdAOvMi961+PN0RyOHjigVuogki+ipVmDrwvaTJ6zLikMzZKK8BqAEMSNM0q4uxm6zTfPjTMckppBveaSOmmrdsdbK+K3jWEkAyEc3Jgcw3TMUyJiOcOu2s5/EfNNEUxPSp7qkTGFsccRZwxZCHuVsZPLe+w+yOrkpaMrRzydTChg53S3Vb/pk93UBEPNwVIPv37Xz+XHHrMz/UmggbZy5foNHro571KY+Dh1x/EPJiJ1vDaskptqM9eEAMA4nrsV2AHJdcnatyuHv5WmyDIi9D4WEbH/h1W02srNsDnXl93KK50z3v9Js3iincQGeDFF4bNgTIQ==
*/