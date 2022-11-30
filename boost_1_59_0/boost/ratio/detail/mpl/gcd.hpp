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
#ifndef BOOST_MPL_GCD_HPP_INCLUDED
#define BOOST_MPL_GCD_HPP_INCLUDED

#include <boost/mpl/integral_c.hpp>
#include <boost/ratio/detail/mpl/abs.hpp>
#include <boost/mpl/aux_/largest_int.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/integral.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>
#include <boost/mpl/aux_/config/dependent_nttp.hpp>
#include <boost/cstdint.hpp>

#if    !defined(BOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC_2) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && !defined(__CUDACC__) \
    && ( defined(BOOST_MSVC) \
        || BOOST_WORKAROUND(__EDG_VERSION__, <= 238) \
        )

#   define BOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC_2

#endif

namespace boost { namespace mpl {

template< typename Tag1, typename Tag2 > struct gcd_impl;

template< typename T > struct gcd_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct gcd
    : gcd_impl<
          typename gcd_tag<N1>::type
        , typename gcd_tag<N2>::type
        >::template apply<N1, N2>::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, gcd, (N1, N2))
};

BOOST_MPL_AUX_NA_SPEC(2, gcd)

template<
      typename T
    , T n1
    , T n2
    >
struct gcd_c
    : gcd<integral_c<T,n1>,integral_c<T,n2> >
{
};

namespace aux {

  // Workaround for error: the type of partial specialization template parameter constant "n2"
    // depends on another template parameter
    // Note: this solution could be wrong for n1 or n2 = [2**63 .. 2**64-1]
#if defined(BOOST_MPL_CFG_NO_DEPENDENT_NONTYPE_PARAMETER_IN_PARTIAL_SPEC)

  template< typename T1, boost::intmax_t n1, bool n1_is_0
                  , typename T2, boost::intmax_t n2, bool n2_is_0 >
      struct gcd_aux
          : gcd_aux<T2, n2, n2==0, T1, (n1 % n2), (n1 % n2)==0>
      {};

      template <typename T1, boost::intmax_t n1, typename T2, boost::intmax_t n2>
      struct gcd_aux<T1, n1, false, T2, n2, true> : integral_c<T1, n1>
      {};

      template <typename T1, boost::intmax_t n1, typename T2, boost::intmax_t n2, bool C>
      struct gcd_aux<T1, n1, true, T2, n2, C> : integral_c<T2, n2>
      {};

#else // defined(BOOST_MPL_CFG_NO_DEPENDENT_NONTYPE_PARAMETER_IN_PARTIAL_SPEC)

    template< typename T1, T1 n1, bool n1_is_0, typename T2, T2 n2, bool n2_is_0 >
    struct gcd_aux

        : gcd_aux<T2, n2, n2==0,
                    typename aux::largest_int<T1, T2>::type,
                    //~ T1,
                    (n1 % n2), (n1 % n2)==0>
    {};

    template <typename T1, T1 n1, typename T2, T2 n2>
    struct gcd_aux<T1, n1, false, T2, n2, true> : integral_c<T1, n1>
    {};

    template <typename T1, T1 n1, typename T2, T2 n2, bool C>
    struct gcd_aux<T1, n1, true, T2, n2, C> : integral_c<T2, n2>
    {};
#endif // defined(BOOST_MPL_CFG_NO_DEPENDENT_NONTYPE_PARAMETER_IN_PARTIAL_SPEC)
}

template<>
struct gcd_impl<integral_c_tag, integral_c_tag>
{
    template< typename N1, typename N2 > struct apply
        : abs<aux::gcd_aux< typename N1::value_type, N1::value, N1::value==0,
                        typename N2::value_type, N2::value, N2::value==0  > >
    {
    };
};

}}

#endif // BOOST_MPL_GCD_HPP_INCLUDED

/* gcd.hpp
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
*/