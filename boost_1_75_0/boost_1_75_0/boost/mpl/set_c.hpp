
#ifndef BOOST_MPL_SET_C_HPP_INCLUDED
#define BOOST_MPL_SET_C_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/limits/set.hpp>
#   include <boost/mpl/aux_/nttp_decl.hpp>
#   include <boost/mpl/aux_/config/preprocessor.hpp>

#   include <boost/preprocessor/inc.hpp>
#   include <boost/preprocessor/cat.hpp>
#   include <boost/preprocessor/stringize.hpp>

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_SET_C_HEADER \
    BOOST_PP_CAT(BOOST_PP_CAT(set,BOOST_MPL_LIMIT_SET_SIZE),_c).hpp \
    /**/
#else
#   define AUX778076_SET_C_HEADER \
    BOOST_PP_CAT(BOOST_PP_CAT(set,BOOST_MPL_LIMIT_SET_SIZE),_c)##.hpp \
    /**/
#endif

#   include BOOST_PP_STRINGIZE(boost/mpl/set/AUX778076_SET_C_HEADER)
#   undef AUX778076_SET_C_HEADER
#   include <climits>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER set_c.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/set.hpp>

#   define AUX778076_SEQUENCE_NAME set_c
#   define AUX778076_SEQUENCE_LIMIT BOOST_MPL_LIMIT_SET_SIZE
#   define AUX778076_SEQUENCE_NAME_N(n) BOOST_PP_CAT(BOOST_PP_CAT(set,n),_c)
#   define AUX778076_SEQUENCE_INTEGRAL_WRAPPER
#   include <boost/mpl/aux_/sequence_wrapper.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_SET_C_HPP_INCLUDED

/* set_c.hpp
6vOrEjSavH4OP/SjB+ISX8PX+VsOAcNDINMlPrqU6Nd3DjXRSBhxJAxZzllH7HUi5noJDbTj2eCPJiC0FwZTf4c7nijCoxksyWpjTKRtVbmlq0pPu6at/P5hVjHbput3aMDJz6RbnsJe+oxH9GNjvSes0utqvbkI0FaFRJSc1MNrIEnrQkJGdw1c9bslXp8GuREW0E6rK8m5s7EjXtS73/2YIlnhQ1Ig605rv+tRRaH8EU76ZAAfPw9C0s96JzLdB1P44Ulq3GyKvyqYVmzaMZDDVa1vM908fs7n0SbEoxdQBWyDDMWbPBIM3hQO2dA0m1vmXfWzaNgEcQs1kh4Sj8TX7GTXRjc9ydUM4fM7bot2XBv40gLDGWeCRa5K7OkWRaPBM11K3a/H/W4/Lj3XUK65toPqSNP9EI9gQvxhuKDnn+qZ+bXwrrCs6hk6CAqEtnI3LQ8qXMy2DzZhRutC6bChDBgL0OX7Sh/1qr6IGqDPl6L0hAPVMCv/aI46aEmEk2ynwEnj7WfGkD0mOD9Nbwkpq/P3qGeL80dd3SLQnsW5AK3vX8h+S2wjArU1VnjbkekNLQVvY3CmMZvKf/uY6iKMPmcBdSLxlRXl0xtx+P6VW+zuGq8y9ajHhMnEfATfddnEVbI3ZxKvVk5r7KiBeOXu867ewmgzB3nee7ykk0lQu8z2VGD3SJ9n/bU2wloDkY2yy+bvnKsRyz6I
*/