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