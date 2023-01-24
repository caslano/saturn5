//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_DETAIL_UDT_BUILTIN_MIXTURE_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_DETAIL_UDT_BUILTIN_MIXTURE_FLC_12NOV2002_HPP

#include "boost/type_traits/is_arithmetic.hpp"

#include "boost/numeric/conversion/udt_builtin_mixture_enum.hpp"
#include "boost/numeric/conversion/detail/meta.hpp"

#include "boost/mpl/integral_c.hpp"

namespace boost { namespace numeric { namespace convdetail
{
  // Integral Constants for 'UdtMixture'
  typedef mpl::integral_c<udt_builtin_mixture_enum, builtin_to_builtin> builtin2builtin_c ;
  typedef mpl::integral_c<udt_builtin_mixture_enum, builtin_to_udt>     builtin2udt_c ;
  typedef mpl::integral_c<udt_builtin_mixture_enum, udt_to_builtin>     udt2builtin_c ;
  typedef mpl::integral_c<udt_builtin_mixture_enum, udt_to_udt>         udt2udt_c ;

  // Metafunction:
  //
  //   for_udt_mixture<UdtMixture,BuiltIn2BuiltIn,BuiltIn2Udt,Udt2BuiltIn,Udt2Udt>::type
  //
  // {UdtMixture} is one of the Integral Constants for UdMixture, declared above.
  // {BuiltIn2BuiltIn,BuiltIn2Udt,Udt2BuiltIn,Udt2Udt} are aribtrary types. (not metafunctions)
  //
  // According to the value of 'UdtMixture', selects the corresponding type.
  //
  template<class UdtMixture, class BuiltIn2BuiltIn, class BuiltIn2Udt, class Udt2BuiltIn, class Udt2Udt>
  struct for_udt_builtin_mixture
  {
    typedef typename
      ct_switch4<UdtMixture
                 , builtin2builtin_c, builtin2udt_c, udt2builtin_c // default
                 , BuiltIn2BuiltIn  , BuiltIn2Udt  , Udt2BuiltIn  , Udt2Udt
                >::type
        type ;
  } ;

  // Metafunction:
  //
  //   get_udt_mixture<T,S>::type
  //
  // Selects the appropriate UdtMixture Integral Constant for the combination T,S.
  //
  template<class T,class S>
  struct get_udt_builtin_mixture
  {
    typedef is_arithmetic<S> S_builtin ;
    typedef is_arithmetic<T> T_builtin ;

    typedef typename
      for_both<S_builtin, T_builtin, builtin2builtin_c, builtin2udt_c, udt2builtin_c, udt2udt_c>::type
        type ;
  } ;

} } } // namespace boost::numeric::convdetail

#endif



/* udt_builtin_mixture.hpp
Pdm1CrGh6CDJyj2kQG2PkoDtUn8cqhNY0S9VPICZjVFtjQl8YL570QA7Sogy8ZFlmtnAIkuLuaEa3wkvrYdUtmKlj8gz7LK7cZe1DvWrQ/1HpKF+WiR1Euohh/JkIkuYEJRmIp+ErTwPCzqXefdr1uHvmonRpJQ4o0mUwEKMDZr1sk+J7OX6VbGqr4HyZ+U65L3KJMDoLZ8xFabcSKSvO5evMIDDe4QinZs0a9pu0hRWntGPv4+hR8oLvYvPP4jrtguRpZ9HcTUrBQbNOoCgKC5DdWsoXrNeB58K3P6ZILuOBNEm522mVEfTm7SCLL1UJD5nJTvpaThjShOrbnY1VvPCmnaBhfsFJKw48QGf4xTY0k/6U7jIy1wgoQ/pWV+phOdb1cwb4rVqTSeid32MZDKHSChO7HvY4CznRwE82aFZP8cbWAlHvfZjvVEN3FPjGlhnhdVRNo+oPHbfvh3JYxepFQkL/g25QgDl/A+z9L1njNd1ONZRs3WzWQqcqfKpgGZZ6IY2j/E2aVJxvVP8IA7bbn/eyGOaHRbsCOvu8EQ32MGOLzWNB8ruPoASYOhfFBAabtCITBWgwgN4wj18RNPQX4mevNtMZvspRBCBD4bFdgfjeQw8UpqIIoEntNt3RaeEdgTe7pv0gFjDJnZajQYoshPq549idZp2dgqteSusV8iio5CGm0a6zSRSLah548jZh+5vMJOi+ElA
*/