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
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
*/