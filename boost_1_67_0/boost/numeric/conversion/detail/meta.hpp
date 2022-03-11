//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_DETAIL_META_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_DETAIL_META_FLC_12NOV2002_HPP

#include "boost/type_traits/remove_cv.hpp"

#include "boost/mpl/if.hpp"
#include "boost/mpl/eval_if.hpp"
#include "boost/mpl/equal_to.hpp"
#include "boost/mpl/not.hpp"
#include "boost/mpl/and.hpp"
#include "boost/mpl/bool.hpp"
#include "boost/mpl/identity.hpp"

namespace boost { namespace numeric { namespace convdetail
{
   template< class T1, class T2>
   struct equal_to
   {
   #if !defined(__BORLANDC__)
   
       enum { x = ( BOOST_MPL_AUX_VALUE_WKND(T1)::value == BOOST_MPL_AUX_VALUE_WKND(T2)::value ) };
           
       BOOST_STATIC_CONSTANT(bool, value = x);
           
       typedef mpl::bool_<value> type;
       
   #else
   
       BOOST_STATIC_CONSTANT(bool, value = (
             BOOST_MPL_AUX_VALUE_WKND(T1)::value 
               == BOOST_MPL_AUX_VALUE_WKND(T2)::value
           ));
           
       typedef mpl::bool_<(
             BOOST_MPL_AUX_VALUE_WKND(T1)::value 
               == BOOST_MPL_AUX_VALUE_WKND(T2)::value
           )> type;
   #endif
   };
    
// Metafunction:
  //
  //   ct_switch4<Value,Case0Val,Case1Val,Case2Val,Case0Type,Case1Type,Case2Type,DefaultType>::type
  //
  // {Value,Case(X)Val} are Integral Constants (such as: mpl::int_<>)
  // {Case(X)Type,DefaultType} are arbitrary types. (not metafunctions)
  //
  // Returns Case(X)Type if Val==Case(X)Val; DefaultType otherwise.
  //
  template<class Value,
           class Case0Val,
           class Case1Val,
           class Case2Val,
           class Case0Type,
           class Case1Type,
           class Case2Type,
           class DefaultType
          >
  struct ct_switch4
  {
    typedef mpl::identity<Case0Type> Case0TypeQ ;
    typedef mpl::identity<Case1Type> Case1TypeQ ;

    typedef equal_to<Value,Case0Val> is_case0 ;
    typedef equal_to<Value,Case1Val> is_case1 ;
    typedef equal_to<Value,Case2Val> is_case2 ;

    typedef mpl::if_<is_case2,Case2Type,DefaultType> choose_2_3Q ;
    typedef mpl::eval_if<is_case1,Case1TypeQ,choose_2_3Q> choose_1_2_3Q ;

    typedef typename
      mpl::eval_if<is_case0,Case0TypeQ,choose_1_2_3Q>::type
        type ;
  } ;




  // Metafunction:
  //
  //   for_both<expr0,expr1,TT,TF,FT,FF>::type
  //
  // {exp0,expr1} are Boolean Integral Constants
  // {TT,TF,FT,FF} are aribtrary types. (not metafunctions)
  //
  // According to the combined boolean value of 'expr0 && expr1', selects the corresponding type.
  //
  template<class expr0, class expr1, class TT, class TF, class FT, class FF>
  struct for_both
  {
    typedef mpl::identity<TF> TF_Q ;
    typedef mpl::identity<TT> TT_Q ;

    typedef typename mpl::not_<expr0>::type not_expr0 ;
    typedef typename mpl::not_<expr1>::type not_expr1 ;

    typedef typename mpl::and_<expr0,expr1>::type     caseTT ;
    typedef typename mpl::and_<expr0,not_expr1>::type caseTF ;
    typedef typename mpl::and_<not_expr0,expr1>::type caseFT ;

    typedef mpl::if_<caseFT,FT,FF>                    choose_FT_FF_Q ;
    typedef mpl::eval_if<caseTF,TF_Q,choose_FT_FF_Q> choose_TF_FT_FF_Q ;

    typedef typename mpl::eval_if<caseTT,TT_Q,choose_TF_FT_FF_Q>::type type ;
  } ;

} } } // namespace boost::numeric::convdetail

#endif



/* meta.hpp
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
*/