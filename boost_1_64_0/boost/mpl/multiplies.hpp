
#ifndef BOOST_MPL_MULTIPLIES_HPP_INCLUDED
#define BOOST_MPL_MULTIPLIES_HPP_INCLUDED

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

#include <boost/mpl/times.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/preprocessor/default_params.hpp>
#include <boost/mpl/aux_/preprocessor/params.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

// backward compatibility header, deprecated

namespace boost { namespace mpl {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#   define AUX778076_OP_ARITY BOOST_MPL_LIMIT_METAFUNCTION_ARITY
#else
#   define AUX778076_OP_ARITY 2
#endif

template<
      BOOST_MPL_PP_DEFAULT_PARAMS(AUX778076_OP_ARITY, typename N, na)
    >
struct multiplies
    : times< BOOST_MPL_PP_PARAMS(AUX778076_OP_ARITY, N) >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          AUX778076_OP_ARITY
        , multiplies
        , ( BOOST_MPL_PP_PARAMS(AUX778076_OP_ARITY, N) )
        )
};

BOOST_MPL_AUX_NA_SPEC(AUX778076_OP_ARITY, multiplies)

#undef AUX778076_OP_ARITY

}}

#endif // BOOST_MPL_MULTIPLIES_HPP_INCLUDED

/* multiplies.hpp
7lPbsXEwDmqrAlT+HrExKcla3Gl3r2Q5hu+hCeuS8yNlBm5ProqgfSYVDDHUxT7Wixy6wz2+Ch557ps/j9gvCnfImkta3RtIDI7eUbHNx8sVlwD3nHXEpysPqwn96wfmJFkD/vwwvdGQ5rSPQrycgTCCYE9gouAoQZ8gLXGLXgFjlcAbCyIPozIWqXdZSILnYnJE9ggyNTBAhB4I9YTcNyNRVBVPng5ps01nCIbSJWutMrvE120z4g0hrsrlg8vwoFyoz9j9SPhc1RxY9Wnl4QX2GYMx3WVIL7ERLQs+wZnHtSP0iy+RbkNiwuAkUyGrmDKhhPkgeJSXJ+ptvvyUqgsgCA0zIxzlkD5dVVQDXhjMbu3hYNPl5qMJTYcnKhWaR5G/5OyH8cHG0ncnbOEfzm2rnCO5XSEzpCsulq30iDbDAlIiaMyvFwNf+8Lvtq0BX7rWIoEq9eZkuy97DRi1t1YsB6h5HUQkkLz+GfapPFkRQsM/BsLns/ZAzjACGIT+M/r+o7C4MXx7PdZEX39VML/cUq2ENPNFnN1rpF7Av0JszL6AM9c/1UaIoA==
*/