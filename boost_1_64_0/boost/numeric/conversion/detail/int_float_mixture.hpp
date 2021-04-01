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
z30oQ1l5dJRkCYfQC+ipXC/GQrd3cx8Fu1LixSzq+OJVsbTPR7pFClfCp6Lc6oFmTO20d0EvV0n1gKkjWGM6LDIQ5a8jif2juddM44RQM7ZLVeqISw3YUQi6FqUepQBSQ/+nmoXD2Bg/rYIItLPqUBwb4fHyYWCkfN4FH9i87JYZCLYMCBtL+61dSKXhvtuW1jf3S+r3bZRX6q0TtTbNyPrMExMG/YOOjrLAF8s5JLtuT44pfQS+hqt26Gm8TZlmkcR1TuGrotNOddnVf7vhp0FlDnlN4q8aw5y6G9QUklqI5KhvuRGzOnqYfaUN13S08RCIoBv9Hzf0MAM8ejT7HHBdZat9/qBxPdN8VxqrwqbOIqrUjK7F+XGRVX+gj12L2ecWjr4HVKGK+qfqhseajOQMkJ3Tqi/PE/kqNxnG6nxtXI1g5mQ/PNom2EimK5w7XihGJKk+UWP//KiCKL6uJ+AahgeYE5PerSOlP/KdyccNzBFjTuNjfuwjE0YdLz7p+gyyvx/2fl0nogC1JAemI+L7UhqX53FHosD4FgYWQ2TSBKCY3iaA3L8emw==
*/