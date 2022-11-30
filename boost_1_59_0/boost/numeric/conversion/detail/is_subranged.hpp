//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_DETAIL_IS_SUBRANGED_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_DETAIL_IS_SUBRANGED_FLC_12NOV2002_HPP

#include "boost/config.hpp"
#include "boost/limits.hpp"

#include "boost/mpl/int.hpp"
#include "boost/mpl/multiplies.hpp"
#include "boost/mpl/less.hpp"
#include "boost/mpl/equal_to.hpp"

#include "boost/type_traits/is_same.hpp"

#include "boost/numeric/conversion/detail/meta.hpp"
#include "boost/numeric/conversion/detail/int_float_mixture.hpp"
#include "boost/numeric/conversion/detail/sign_mixture.hpp"
#include "boost/numeric/conversion/detail/udt_builtin_mixture.hpp"

namespace boost { namespace numeric { namespace convdetail
{
  //---------------------------------------------------------------
  // Implementations of the compile time predicate "T is subranged"
  //---------------------------------------------------------------

    // for integral to integral conversions
    template<class T,class S>
    struct subranged_Sig2Unsig
    {
      // Signed to unsigned conversions are 'subranged' because of possible loose
      // of negative values.
      typedef mpl::true_ type ;
    } ;

    // for unsigned integral to signed integral conversions
    template<class T,class S>
    struct subranged_Unsig2Sig
    {
       // IMPORTANT NOTE:
       //
       // This code assumes that signed/unsigned integral values are represented
       // such that:
       //
       //  numeric_limits<signed T>::digits + 1 == numeric_limits<unsigned T>::digits
       //
       // The '+1' is required since numeric_limits<>::digits gives 1 bit less for signed integral types.
       //
       // This fact is used by the following logic:
       //
       //  if ( (numeric_limits<T>::digits+1) < (2*numeric_limits<S>::digits) )
       //    then the conversion is subranged.
       //

       typedef mpl::int_< ::std::numeric_limits<S>::digits > S_digits ;
       typedef mpl::int_< ::std::numeric_limits<T>::digits > T_digits ;

       // T is signed, so take digits+1
       typedef typename T_digits::next u_T_digits ;

       typedef mpl::int_<2> Two ;

       typedef typename mpl::multiplies<S_digits,Two>::type S_digits_times_2 ;

       typedef typename mpl::less<u_T_digits,S_digits_times_2>::type type ;
    } ;

    // for integral to integral conversions of the same sign.
    template<class T,class S>
    struct subranged_SameSign
    {
       // An integral conversion of the same sign is subranged if digits(T) < digits(S).

       typedef mpl::int_< ::std::numeric_limits<S>::digits > S_digits ;
       typedef mpl::int_< ::std::numeric_limits<T>::digits > T_digits ;

       typedef typename mpl::less<T_digits,S_digits>::type type ;
    } ;

    // for integral to float conversions
    template<class T,class S>
    struct subranged_Int2Float
    {
      typedef mpl::false_ type ;
    } ;

    // for float to integral conversions
    template<class T,class S>
    struct subranged_Float2Int
    {
      typedef mpl::true_ type ;
    } ;

    // for float to float conversions
    template<class T,class S>
    struct subranged_Float2Float
    {
      // If both T and S are floats,
      // compare exponent bits and if they match, mantisa bits.

      typedef mpl::int_< ::std::numeric_limits<S>::digits > S_mantisa ;
      typedef mpl::int_< ::std::numeric_limits<T>::digits > T_mantisa ;

      typedef mpl::int_< ::std::numeric_limits<S>::max_exponent > S_exponent ;
      typedef mpl::int_< ::std::numeric_limits<T>::max_exponent > T_exponent ;

      typedef typename mpl::less<T_exponent,S_exponent>::type T_smaller_exponent ;

      typedef typename mpl::equal_to<T_exponent,S_exponent>::type equal_exponents ;

      typedef mpl::less<T_mantisa,S_mantisa> T_smaller_mantisa ;

      typedef mpl::eval_if<equal_exponents,T_smaller_mantisa,mpl::false_> not_bigger_exponent_case ;

      typedef typename
        mpl::eval_if<T_smaller_exponent,mpl::true_,not_bigger_exponent_case>::type
          type ;
    } ;

    // for Udt to built-in conversions
    template<class T,class S>
    struct subranged_Udt2BuiltIn
    {
      typedef mpl::true_ type ;
    } ;

    // for built-in to Udt conversions
    template<class T,class S>
    struct subranged_BuiltIn2Udt
    {
      typedef mpl::false_ type ;
    } ;

    // for Udt to Udt conversions
    template<class T,class S>
    struct subranged_Udt2Udt
    {
      typedef mpl::false_ type ;
    } ;

  //-------------------------------------------------------------------
  // Selectors for the implementations of the subranged predicate
  //-------------------------------------------------------------------

    template<class T,class S>
    struct get_subranged_Int2Int
    {
      typedef subranged_SameSign<T,S>  Sig2Sig     ;
      typedef subranged_Sig2Unsig<T,S> Sig2Unsig   ;
      typedef subranged_Unsig2Sig<T,S> Unsig2Sig   ;
      typedef Sig2Sig                  Unsig2Unsig ;

      typedef typename get_sign_mixture<T,S>::type sign_mixture ;

      typedef typename
        for_sign_mixture<sign_mixture, Sig2Sig, Sig2Unsig, Unsig2Sig, Unsig2Unsig>::type
           type ;
    } ;

    template<class T,class S>
    struct get_subranged_BuiltIn2BuiltIn
    {
      typedef get_subranged_Int2Int<T,S> Int2IntQ ;

      typedef subranged_Int2Float  <T,S> Int2Float   ;
      typedef subranged_Float2Int  <T,S> Float2Int   ;
      typedef subranged_Float2Float<T,S> Float2Float ;

      typedef mpl::identity<Int2Float  > Int2FloatQ   ;
      typedef mpl::identity<Float2Int  > Float2IntQ   ;
      typedef mpl::identity<Float2Float> Float2FloatQ ;

      typedef typename get_int_float_mixture<T,S>::type int_float_mixture ;

      typedef for_int_float_mixture<int_float_mixture, Int2IntQ, Int2FloatQ, Float2IntQ, Float2FloatQ> for_ ;

      typedef typename for_::type selected ;

      typedef typename selected::type type ;
    } ;

    template<class T,class S>
    struct get_subranged
    {
      typedef get_subranged_BuiltIn2BuiltIn<T,S> BuiltIn2BuiltInQ ;

      typedef subranged_BuiltIn2Udt<T,S> BuiltIn2Udt ;
      typedef subranged_Udt2BuiltIn<T,S> Udt2BuiltIn ;
      typedef subranged_Udt2Udt<T,S>     Udt2Udt ;

      typedef mpl::identity<BuiltIn2Udt> BuiltIn2UdtQ ;
      typedef mpl::identity<Udt2BuiltIn> Udt2BuiltInQ ;
      typedef mpl::identity<Udt2Udt    > Udt2UdtQ     ;

      typedef typename get_udt_builtin_mixture<T,S>::type udt_builtin_mixture ;
      
      typedef typename
        for_udt_builtin_mixture<udt_builtin_mixture, BuiltIn2BuiltInQ, BuiltIn2UdtQ, Udt2BuiltInQ, Udt2UdtQ>::type
          selected ;

      typedef typename selected::type selected2 ;
 
      typedef typename selected2::type type ;
    } ;


  //-------------------------------------------------------------------
  // Top level implementation selector.
  //-------------------------------------------------------------------
  template<class T, class S>
  struct get_is_subranged
  {
    typedef get_subranged<T,S>         non_trivial_case ;
    typedef mpl::identity<mpl::false_> trivial_case ;

    typedef is_same<T,S> is_trivial ;
   
    typedef typename mpl::if_<is_trivial,trivial_case,non_trivial_case>::type selected ;
    
    typedef typename selected::type type ;
  } ;

} } } // namespace boost::numeric::convdetail

#endif



/* is_subranged.hpp
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
*/