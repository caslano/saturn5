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