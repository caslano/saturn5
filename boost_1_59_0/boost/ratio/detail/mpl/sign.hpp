////////////////////////////////////////////////////////////////////
//
// Copyright Vicente J. Botet Escriba 2010
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.
//
////////////////////////////////////////////////////////////////////
#ifndef BOOST_MPL_SIGN_HPP_INCLUDED
#define BOOST_MPL_SIGN_HPP_INCLUDED

#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/integral.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

#if    !defined(BOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC_2) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && !defined(__CUDACC__) \
    && ( defined(BOOST_MSVC) \
        || BOOST_WORKAROUND(__EDG_VERSION__, <= 238) \
        )

#   define BOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC_2

#endif

namespace boost { namespace mpl {

template< typename Tag > struct sign_impl;

template< typename T > struct sign_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N)
    >
struct sign
    : sign_impl<
          typename sign_tag<N>::type
        >::template apply<N>::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1, sign, (N))
};

BOOST_MPL_AUX_NA_SPEC(1, sign)

template<
      typename T
    , T n1
    >
struct sign_c
    : sign<integral_c<T,n1> >
{
};

#if defined(BOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC_2)
namespace aux {
template< typename T, T n > struct sign_wknd
{
    BOOST_STATIC_CONSTANT(T, value = (n == 0 ? 0 : (n < 0 ? -1 : 1)));
    typedef integral_c<T,value> type;
};
}
#endif

template<>
struct sign_impl<integral_c_tag>
{
#if defined(BOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC_2)
    template< typename N > struct apply
        : aux::sign_wknd< typename N::value_type, N::value >
#else
    template< typename N > struct apply
        : integral_c< typename N::value_type, (N::value == 0 ? 0 : (N::value < 0 ? -1 : 1)) >
#endif
    {
    };
};

}}

#endif // BOOST_MPL_SIGN_HPP_INCLUDED

/* sign.hpp
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
*/