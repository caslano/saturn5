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
#ifndef BOOST_MPL_LCM_HPP_INCLUDED
#define BOOST_MPL_LCM_HPP_INCLUDED

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

template< typename Tag1, typename Tag2 > struct lcm_impl;

template< typename T > struct lcm_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct lcm
    : lcm_impl<
          typename lcm_tag<N1>::type
        , typename lcm_tag<N2>::type
        >::template apply<N1, N2>::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, lcm, (N1, N2))
};

BOOST_MPL_AUX_NA_SPEC(2, lcm)

template<
      typename T
    , T n1
    , T n2
    >
struct lcm_c
    : lcm<integral_c<T,n1>,integral_c<T,n2> >
{
};


namespace aux {
  // Workaround for error: the type of partial specialization template parameter constant "n2"
  // depends on another template parameter
  // Note: this solution could be wrong for n1 or n2 = [2**63 .. 2**64-1]
  #if defined(BOOST_MPL_CFG_NO_DEPENDENT_NONTYPE_PARAMETER_IN_PARTIAL_SPEC)
  template< typename T1, boost::intmax_t n1, bool n1_is_0
                          , typename T2, boost::intmax_t n2, bool n2_is_0 >
      struct lcm_aux
          : abs<integral_c< typename aux::largest_int<T1, T2>::type,
              ( n1 / gcd<integral_c<T1,n1>, integral_c<T2,n2> >::value * n2 )
          > >
      {};

      template <typename T1, boost::intmax_t n1, typename T2, boost::intmax_t n2>
      struct lcm_aux<T1, n1, false, T2, n2, true> : integral_c<T2, 0>
      {};

      template <typename T1, boost::intmax_t n1, typename T2, boost::intmax_t n2, bool C>
      struct lcm_aux<T1, n1, true, T2, n2, C> : integral_c<T1, 0>
      {};


#else // defined(BOOST_MPL_CFG_NO_DEPENDENT_NONTYPE_PARAMETER_IN_PARTIAL_SPEC)


    template< typename T1, T1 n1, bool n1_is_0, typename T2, T2 n2, bool n2_is_0 >
    struct lcm_aux

        : abs<integral_c< typename aux::largest_int<T1, T2>::type,
            ( n1 / gcd<integral_c<T1,n1>, integral_c<T2,n2> >::value * n2 )
        > >
    {};

    template <typename T1, T1 n1, typename T2, T2 n2>
    struct lcm_aux<T1, n1, false, T2, n2, true> : integral_c<T2, 0>
    {};

    template <typename T1, T1 n1, typename T2, T2 n2, bool C>
    struct lcm_aux<T1, n1, true, T2, n2, C> : integral_c<T1, 0>
    {};
#endif // defined(BOOST_MPL_CFG_NO_DEPENDENT_NONTYPE_PARAMETER_IN_PARTIAL_SPEC)
}

template<>
struct lcm_impl<integral_c_tag, integral_c_tag>
{
    template< typename N1, typename N2 > struct apply
        : abs<aux::lcm_aux< typename N1::value_type, N1::value, N1::value==0,
                        typename N2::value_type, N2::value, N2::value==0  > >
    {
    };
};

}}

#endif // BOOST_MPL_LCM_HPP_INCLUDED

/* lcm.hpp
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
*/