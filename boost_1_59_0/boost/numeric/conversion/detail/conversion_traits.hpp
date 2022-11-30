//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_DETAIL_CONVERSION_TRAITS_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_DETAIL_CONVERSION_TRAITS_FLC_12NOV2002_HPP

#include "boost/type_traits/is_arithmetic.hpp"
#include "boost/type_traits/is_same.hpp"
#include "boost/type_traits/remove_cv.hpp"

#include "boost/numeric/conversion/detail/meta.hpp"
#include "boost/numeric/conversion/detail/int_float_mixture.hpp"
#include "boost/numeric/conversion/detail/sign_mixture.hpp"
#include "boost/numeric/conversion/detail/udt_builtin_mixture.hpp"
#include "boost/numeric/conversion/detail/is_subranged.hpp"

namespace boost { namespace numeric { namespace convdetail
{
  //-------------------------------------------------------------------
  // Implementation of the Conversion Traits for T != S
  //
  // This is a VISIBLE base class of the user-level conversion_traits<> class.
  //-------------------------------------------------------------------
  template<class T,class S>
  struct non_trivial_traits_impl
  {
    typedef typename get_int_float_mixture   <T,S>::type int_float_mixture ;
    typedef typename get_sign_mixture        <T,S>::type sign_mixture ;
    typedef typename get_udt_builtin_mixture <T,S>::type udt_builtin_mixture ;

    typedef typename get_is_subranged<T,S>::type subranged ;

    typedef mpl::false_ trivial ;

    typedef T target_type ;
    typedef S source_type ;
    typedef T result_type ;

    typedef typename mpl::if_< is_arithmetic<S>, S, S const&>::type argument_type ;

    typedef typename mpl::if_<subranged,S,T>::type supertype ;
    typedef typename mpl::if_<subranged,T,S>::type subtype   ;
  } ;

  //-------------------------------------------------------------------
  // Implementation of the Conversion Traits for T == S
  //
  // This is a VISIBLE base class of the user-level conversion_traits<> class.
  //-------------------------------------------------------------------
  template<class N>
  struct trivial_traits_impl
  {
    typedef typename get_int_float_mixture  <N,N>::type int_float_mixture ;
    typedef typename get_sign_mixture       <N,N>::type sign_mixture ;
    typedef typename get_udt_builtin_mixture<N,N>::type udt_builtin_mixture ;

    typedef mpl::false_ subranged ;
    typedef mpl::true_  trivial ;

    typedef N        target_type ;
    typedef N        source_type ;
    typedef N const& result_type ;
    typedef N const& argument_type ;

    typedef N supertype ;
    typedef N subtype  ;

  } ;

  //-------------------------------------------------------------------
  // Top level implementation selector.
  //-------------------------------------------------------------------
  template<class T, class S>
  struct get_conversion_traits
  {
    typedef typename remove_cv<T>::type target_type ;
    typedef typename remove_cv<S>::type source_type ;

    typedef typename is_same<target_type,source_type>::type is_trivial ;

    typedef trivial_traits_impl    <target_type>             trivial_imp ;
    typedef non_trivial_traits_impl<target_type,source_type> non_trivial_imp ;

    typedef typename mpl::if_<is_trivial,trivial_imp,non_trivial_imp>::type type ;
  } ;

} } } // namespace boost::numeric::convdetail

#endif



/* conversion_traits.hpp
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
*/