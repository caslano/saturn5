//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_DETAIL_INT_FLOAT_MIXTURE_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_DETAIL_INT_FLOAT_MIXTURE_FLC_12NOV2002_HPP

#include "boost/config.hpp"
#include "boost/limits.hpp"

#include "boost/numeric/conversion/int_float_mixture_enum.hpp"
#include "boost/numeric/conversion/detail/meta.hpp"

#include "boost/mpl/integral_c.hpp"

namespace boost { namespace numeric { namespace convdetail
{
  // Integral Constants for 'IntFloatMixture'
  typedef mpl::integral_c<int_float_mixture_enum, integral_to_integral> int2int_c ;
  typedef mpl::integral_c<int_float_mixture_enum, integral_to_float>    int2float_c ;
  typedef mpl::integral_c<int_float_mixture_enum, float_to_integral>    float2int_c ;
  typedef mpl::integral_c<int_float_mixture_enum, float_to_float>       float2float_c ;

  // Metafunction:
  //
  //   get_int_float_mixture<T,S>::type
  //
  // Selects the appropriate Int-Float Mixture Integral Constant for the combination T,S.
  //
  template<class T,class S>
  struct get_int_float_mixture
  {
    typedef mpl::bool_< ::std::numeric_limits<S>::is_integer > S_int ;
    typedef mpl::bool_< ::std::numeric_limits<T>::is_integer > T_int ;

    typedef typename
      for_both<S_int, T_int, int2int_c, int2float_c, float2int_c, float2float_c>::type
        type ;
  } ;

  // Metafunction:
  //
  //   for_int_float_mixture<Mixture,int_int,int_float,float_int,float_float>::type
  //
  // {Mixture} is one of the Integral Constants for Mixture, declared above.
  // {int_int,int_float,float_int,float_float} are aribtrary types. (not metafunctions)
  //
  // According to the value of 'IntFloatMixture', selects the corresponding type.
  //
  template<class IntFloatMixture, class Int2Int, class Int2Float, class Float2Int, class Float2Float>
  struct for_int_float_mixture
  {
    typedef typename
      ct_switch4<IntFloatMixture
                 ,int2int_c, int2float_c, float2int_c  // default
                 ,Int2Int  , Int2Float  , Float2Int  , Float2Float
                >::type
        type ;
  } ;

} } } // namespace boost::numeric::convdetail

#endif
//
///////////////////////////////////////////////////////////////////////////////////////////////



/* int_float_mixture.hpp
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
*/