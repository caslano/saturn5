
#ifndef BOOST_MPL_AUX_TRAITS_LAMBDA_SPEC_HPP_INCLUDED
#define BOOST_MPL_AUX_TRAITS_LAMBDA_SPEC_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/sequence_tag_fwd.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/preprocessor/params.hpp>
#include <boost/mpl/aux_/config/lambda.hpp>

#if !defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)

#   define BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC_IMPL(i, trait) /**/

#elif !defined(BOOST_MPL_CFG_MSVC_ETI_BUG)

#   define BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC_IMPL(i, trait) \
template<> struct trait<void_> \
{ \
    template< BOOST_MPL_PP_PARAMS(i, typename T) > struct apply \
    { \
    }; \
}; \
/**/

#else

#   define BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC_IMPL(i, trait) \
template<> struct trait<void_> \
{ \
    template< BOOST_MPL_PP_PARAMS(i, typename T) > struct apply \
    { \
    }; \
}; \
template<> struct trait<int> \
{ \
    template< BOOST_MPL_PP_PARAMS(i, typename T) > struct apply \
    { \
        typedef int type; \
    }; \
}; \
/**/

#endif // BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT


#define BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(i, trait) \
    BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC_IMPL(i, trait) \
    template<> struct trait<non_sequence_tag> {}; \
/**/

#endif // BOOST_MPL_AUX_TRAITS_LAMBDA_SPEC_HPP_INCLUDED

/* traits_lambda_spec.hpp
NFVUBQABtkgkYGWRy2rDMBBF9/qKIVkb0b0wlMSLQoiMH6W7oFpjLGprgjRJm7+v7LwKXUlX92h0Z6QYI3cmYi6U8z2l5Qsv3xRszEWWHQMxZRZ7cxpZKPn0lLziYi3WsBkdes6isyhUt4hE9Gj4FDDBnnwy5PNARQxnDA/nLpU3U4ryyozTkYEJIjIYuCWAJU9HI/BgGCxhBE8M+OPiHO96W3U0Tcbbfw3AVhf1XjfFx1vdJPzBpe0t9NLOOwbXX8AaNmB6xpCeQ5gnBYOJ8InoYRUH4pVQ54XN5yG01a44tPu6LUtdNcX2UFa60Ru9AxcBQ6AAHVmEF6EWNYtcJCX/SCXvFZV8/s0vUEsDBAoAAAAIAC1nSlK+lSaMkQIAAO0EAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MjA0NVVUBQABtkgkYHVUbWvbMBD+rl9xSylsMMdtYTCKMZQuI2GFBCdtGBSKKp9jE1kyktws/34nyW7Tjn0I8r0999xbMofWCW4xZ1mjKk3PHo8HbUqbs5+bFUuSzminkxIr3kvHsvTNnqUxhLEzdgZrNC9oEtuUyDKDnTySx6ckYZsaoetNpy2CrsDVjQWfFvyroeV7BNsbJAvCh3ygO9doBZRxbxmZ
*/