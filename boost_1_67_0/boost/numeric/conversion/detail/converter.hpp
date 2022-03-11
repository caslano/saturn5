//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
//
#ifndef BOOST_NUMERIC_CONVERSION_DETAIL_CONVERTER_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_DETAIL_CONVERTER_FLC_12NOV2002_HPP

#include <functional>

#include "boost/numeric/conversion/detail/meta.hpp"
#include "boost/numeric/conversion/detail/conversion_traits.hpp"
#include "boost/numeric/conversion/bounds.hpp"

#include "boost/type_traits/is_same.hpp"

#include "boost/mpl/integral_c.hpp"

namespace boost { namespace numeric { namespace convdetail
{
  // Integral Constants representing rounding modes
  typedef mpl::integral_c<std::float_round_style, std::round_toward_zero>         round2zero_c ;
  typedef mpl::integral_c<std::float_round_style, std::round_to_nearest>          round2nearest_c ;
  typedef mpl::integral_c<std::float_round_style, std::round_toward_infinity>     round2inf_c ;
  typedef mpl::integral_c<std::float_round_style, std::round_toward_neg_infinity> round2neg_inf_c ;

  // Metafunction:
  //
  //   for_round_style<RoundStyle,RoundToZero,RoundToNearest,RoundToInf,RoundToNegInf>::type
  //
  // {RoundStyle} Integral Constant specifying a round style as declared above.
  // {RoundToZero,RoundToNearest,RoundToInf,RoundToNegInf} arbitrary types.
  //
  // Selects one of the 4 types according to the value of RoundStyle.
  //
  template<class RoundStyle,class RoundToZero,class RoundToNearest,class RoundToInf,class RoundToNegInf>
  struct for_round_style
  {
    typedef ct_switch4<RoundStyle
                       , round2zero_c, round2nearest_c, round2inf_c // round2neg_inf_c
                       , RoundToZero , RoundToNearest , RoundToInf , RoundToNegInf
                      > selector ;

    typedef typename selector::type type ;
  } ;


















//--------------------------------------------------------------------------
//                             Range Checking Logic.
//
// The range checking logic is built up by combining 1 or 2 predicates.
// Each predicate is encapsulated in a template class and exposes
// the static member function 'apply'.
//
//--------------------------------------------------------------------------


  // Because a particular logic can combine either 1 or two predicates, the following
  // tags are used to allow the predicate applier to receive 2 preds, but optimize away
  // one of them if it is 'non-applicable'
  struct non_applicable { typedef mpl::false_ do_apply ; } ;
  struct applicable     { typedef mpl::true_  do_apply ; } ;


  //--------------------------------------------------------------------------
  //
  //                      Range Checking Logic implementations.
  //
  // The following classes, collectivelly named 'Predicates', are instantiated within
  // the corresponding range checkers.
  // Their static member function 'apply' is called to perform the actual range checking logic.
  //--------------------------------------------------------------------------

    // s < Lowest(T) ? cNegOverflow : cInRange
    //
    template<class Traits>
    struct LT_LoT : applicable
    {
      typedef typename Traits::target_type T ;
      typedef typename Traits::source_type S ;
      typedef typename Traits::argument_type argument_type ;

      static range_check_result apply ( argument_type s )
      {
        return s < static_cast<S>(bounds<T>::lowest()) ? cNegOverflow : cInRange ;
      }
    } ;

    // s < 0 ? cNegOverflow : cInRange
    //
    template<class Traits>
    struct LT_Zero : applicable
    {
      typedef typename Traits::source_type S ;
      typedef typename Traits::argument_type argument_type ;

      static range_check_result apply ( argument_type s )
      {
        return s < static_cast<S>(0) ? cNegOverflow : cInRange ;
      }
    } ;

    // s <= Lowest(T)-1 ? cNegOverflow : cInRange
    //
    template<class Traits>
    struct LE_PrevLoT : applicable
    {
      typedef typename Traits::target_type T ;
      typedef typename Traits::source_type S ;
      typedef typename Traits::argument_type argument_type ;

      static range_check_result apply ( argument_type s )
      {
        return s <= static_cast<S>(bounds<T>::lowest()) - static_cast<S>(1.0)
                 ? cNegOverflow : cInRange ;
      }
    } ;

    // s < Lowest(T)-0.5 ? cNegOverflow : cInRange
    //
    template<class Traits>
    struct LT_HalfPrevLoT : applicable
    {
      typedef typename Traits::target_type T ;
      typedef typename Traits::source_type S ;
      typedef typename Traits::argument_type argument_type ;

      static range_check_result apply ( argument_type s )
      {
        return s < static_cast<S>(bounds<T>::lowest()) - static_cast<S>(0.5)
                 ? cNegOverflow : cInRange ;
      }
    } ;

    // s > Highest(T) ? cPosOverflow : cInRange
    //
    template<class Traits>
    struct GT_HiT : applicable
    {
      typedef typename Traits::target_type T ;
      typedef typename Traits::source_type S ;
      typedef typename Traits::argument_type argument_type ;

      static range_check_result apply ( argument_type s )
      {
        return s > static_cast<S>(bounds<T>::highest())
                 ? cPosOverflow : cInRange ;
      }
    } ;

    // s >= Lowest(T) + 1 ? cPosOverflow : cInRange
    //
    template<class Traits>
    struct GE_SuccHiT : applicable
    {
      typedef typename Traits::target_type T ;
      typedef typename Traits::source_type S ;
      typedef typename Traits::argument_type argument_type ;

      static range_check_result apply ( argument_type s )
      {
        return s >= static_cast<S>(bounds<T>::highest()) + static_cast<S>(1.0)
                 ? cPosOverflow : cInRange ;
      }
    } ;

    // s >= Lowest(T) + 0.5 ? cPosgOverflow : cInRange
    //
    template<class Traits>
    struct GT_HalfSuccHiT : applicable
    {
      typedef typename Traits::target_type T ;
      typedef typename Traits::source_type S ;
      typedef typename Traits::argument_type argument_type ;

      static range_check_result apply ( argument_type s )
      {
        return s >= static_cast<S>(bounds<T>::highest()) + static_cast<S>(0.5)
                 ? cPosOverflow : cInRange ;
      }
    } ;


  //--------------------------------------------------------------------------
  //
  // Predicate Combiner.
  //
  // This helper classes are used to possibly combine the range checking logic
  // individually performed by the predicates
  //
  //--------------------------------------------------------------------------


    // Applies both predicates: first 'PredA', and if it equals 'cInRange', 'PredB'
    template<class PredA, class PredB>
    struct applyBoth
    {
      typedef typename PredA::argument_type argument_type ;

      static range_check_result apply ( argument_type s )
      {
        range_check_result r = PredA::apply(s) ;
        if ( r == cInRange )
          r = PredB::apply(s);
        return r ;
      }
    } ;

    template<class PredA, class PredB>
    struct combine
    {
      typedef applyBoth<PredA,PredB> Both ;
      typedef void                   NNone ; // 'None' is defined as a macro in (/usr/X11R6/include/X11/X.h)

      typedef typename PredA::do_apply do_applyA ;
      typedef typename PredB::do_apply do_applyB ;

      typedef typename for_both<do_applyA, do_applyB, Both, PredA, PredB, NNone>::type type ;
    } ;












//--------------------------------------------------------------------------
//                             Range Checker classes.
//
// The following classes are VISIBLE base classes of the user-level converter<> class.
// They supply the optimized 'out_of_range()' and 'validate_range()' static member functions
// visible in the user interface.
//
//--------------------------------------------------------------------------

  // Dummy range checker.
  template<class Traits>
  struct dummy_range_checker
  {
    typedef typename Traits::argument_type argument_type ;

    static range_check_result out_of_range ( argument_type ) { return cInRange ; }
    static void validate_range ( argument_type ) {}
  } ;

  // Generic range checker.
  //
  // All the range checking logic for all possible combinations of source and target
  // can be arranged in terms of one or two predicates, which test overflow on both neg/pos 'sides'
  // of the ranges.
  //
  // These predicates are given here as IsNegOverflow and IsPosOverflow.
  //
  template<class Traits, class IsNegOverflow, class IsPosOverflow, class OverflowHandler>
  struct generic_range_checker
  {
    typedef OverflowHandler overflow_handler ;

    typedef typename Traits::argument_type argument_type ;

    static range_check_result out_of_range ( argument_type s )
    {
      typedef typename combine<IsNegOverflow,IsPosOverflow>::type Predicate ;

      return Predicate::apply(s);
    }

    static void validate_range ( argument_type s )
      { OverflowHandler()( out_of_range(s) ) ; }
  } ;



//--------------------------------------------------------------------------
//
// Selectors for the optimized Range Checker class.
//
//--------------------------------------------------------------------------

  template<class Traits,class OverflowHandler>
  struct GetRC_Sig2Sig_or_Unsig2Unsig
  {
    typedef dummy_range_checker<Traits> Dummy ;

    typedef LT_LoT<Traits> Pred1 ;
    typedef GT_HiT<Traits> Pred2 ;

    typedef generic_range_checker<Traits,Pred1,Pred2,OverflowHandler> Normal ;

    typedef typename Traits::subranged subranged ;

    typedef typename mpl::if_<subranged,Normal,Dummy>::type type ;
  } ;

  template<class Traits, class OverflowHandler>
  struct GetRC_Sig2Unsig
  {
    typedef LT_Zero<Traits> Pred1 ;
    typedef GT_HiT <Traits> Pred2 ;

    typedef generic_range_checker<Traits,Pred1,Pred2,OverflowHandler> ChoiceA ;

    typedef generic_range_checker<Traits,Pred1,non_applicable,OverflowHandler> ChoiceB ;

    typedef typename Traits::target_type T ;
    typedef typename Traits::source_type S ;

    typedef typename subranged_Unsig2Sig<S,T>::type oposite_subranged ;

    typedef typename mpl::not_<oposite_subranged>::type positively_subranged ;

    typedef typename mpl::if_<positively_subranged,ChoiceA,ChoiceB>::type type ;
  } ;

  template<class Traits, class OverflowHandler>
  struct GetRC_Unsig2Sig
  {
    typedef GT_HiT<Traits> Pred1 ;

    typedef generic_range_checker<Traits,non_applicable,Pred1,OverflowHandler> type ;
  } ;

  template<class Traits,class OverflowHandler>
  struct GetRC_Int2Int
  {
    typedef GetRC_Sig2Sig_or_Unsig2Unsig<Traits,OverflowHandler> Sig2SigQ     ;
    typedef GetRC_Sig2Unsig             <Traits,OverflowHandler> Sig2UnsigQ   ;
    typedef GetRC_Unsig2Sig             <Traits,OverflowHandler> Unsig2SigQ   ;
    typedef Sig2SigQ                                             Unsig2UnsigQ ;

    typedef typename Traits::sign_mixture sign_mixture ;

    typedef typename
      for_sign_mixture<sign_mixture,Sig2SigQ,Sig2UnsigQ,Unsig2SigQ,Unsig2UnsigQ>::type
        selector ;

    typedef typename selector::type type ;
  } ;

  template<class Traits>
  struct GetRC_Int2Float
  {
    typedef dummy_range_checker<Traits> type ;
  } ;

  template<class Traits, class OverflowHandler, class Float2IntRounder>
  struct GetRC_Float2Int
  {
    typedef LE_PrevLoT    <Traits> Pred1 ;
    typedef GE_SuccHiT    <Traits> Pred2 ;
    typedef LT_HalfPrevLoT<Traits> Pred3 ;
    typedef GT_HalfSuccHiT<Traits> Pred4 ;
    typedef GT_HiT        <Traits> Pred5 ;
    typedef LT_LoT        <Traits> Pred6 ;

    typedef generic_range_checker<Traits,Pred1,Pred2,OverflowHandler> ToZero    ;
    typedef generic_range_checker<Traits,Pred3,Pred4,OverflowHandler> ToNearest ;
    typedef generic_range_checker<Traits,Pred1,Pred5,OverflowHandler> ToInf     ;
    typedef generic_range_checker<Traits,Pred6,Pred2,OverflowHandler> ToNegInf  ;

    typedef typename Float2IntRounder::round_style round_style ;

    typedef typename for_round_style<round_style,ToZero,ToNearest,ToInf,ToNegInf>::type type ;
  } ;

  template<class Traits, class OverflowHandler>
  struct GetRC_Float2Float
  {
    typedef dummy_range_checker<Traits> Dummy ;

    typedef LT_LoT<Traits> Pred1 ;
    typedef GT_HiT<Traits> Pred2 ;

    typedef generic_range_checker<Traits,Pred1,Pred2,OverflowHandler> Normal ;

    typedef typename Traits::subranged subranged ;

    typedef typename mpl::if_<subranged,Normal,Dummy>::type type ;
  } ;

  template<class Traits, class OverflowHandler, class Float2IntRounder>
  struct GetRC_BuiltIn2BuiltIn
  {
    typedef GetRC_Int2Int<Traits,OverflowHandler>                    Int2IntQ ;
    typedef GetRC_Int2Float<Traits>                                  Int2FloatQ ;
    typedef GetRC_Float2Int<Traits,OverflowHandler,Float2IntRounder> Float2IntQ ;
    typedef GetRC_Float2Float<Traits,OverflowHandler>                Float2FloatQ ;

    typedef typename Traits::int_float_mixture int_float_mixture ;

    typedef typename for_int_float_mixture<int_float_mixture, Int2IntQ, Int2FloatQ, Float2IntQ, Float2FloatQ>::type selector ;

    typedef typename selector::type type ;
  } ;

  template<class Traits, class OverflowHandler, class Float2IntRounder>
  struct GetRC
  {
    typedef GetRC_BuiltIn2BuiltIn<Traits,OverflowHandler,Float2IntRounder> BuiltIn2BuiltInQ ;

    typedef dummy_range_checker<Traits> Dummy ;

    typedef mpl::identity<Dummy> DummyQ ;

    typedef typename Traits::udt_builtin_mixture udt_builtin_mixture ;

    typedef typename for_udt_builtin_mixture<udt_builtin_mixture,BuiltIn2BuiltInQ,DummyQ,DummyQ,DummyQ>::type selector ;

    typedef typename selector::type type ;
  } ;




//--------------------------------------------------------------------------
//                             Converter classes.
//
// The following classes are VISIBLE base classes of the user-level converter<> class.
// They supply the optimized 'nearbyint()' and 'convert()' static member functions
// visible in the user interface.
//
//--------------------------------------------------------------------------

  //
  // Trivial Converter : used when (cv-unqualified) T == (cv-unqualified)  S
  //
  template<class Traits>
  struct trivial_converter_impl : public dummy_range_checker<Traits>
  {
    typedef Traits traits ;
    
    typedef typename Traits::source_type   source_type   ;
    typedef typename Traits::argument_type argument_type ;
    typedef typename Traits::result_type   result_type   ;

    static result_type low_level_convert ( argument_type s ) { return s ; }
    static source_type nearbyint         ( argument_type s ) { return s ; }
    static result_type convert           ( argument_type s ) { return s ; }
  } ;


  //
  // Rounding Converter : used for float to integral conversions.
  //
  template<class Traits,class RangeChecker,class RawConverter,class Float2IntRounder>
  struct rounding_converter : public RangeChecker
                             ,public Float2IntRounder
                             ,public RawConverter
  {
    typedef RangeChecker     RangeCheckerBase ;
    typedef Float2IntRounder Float2IntRounderBase ;
    typedef RawConverter     RawConverterBase ;

    typedef Traits traits ;

    typedef typename Traits::source_type   source_type   ;
    typedef typename Traits::argument_type argument_type ;
    typedef typename Traits::result_type   result_type   ;

    static result_type convert ( argument_type s )
    {
      RangeCheckerBase::validate_range(s);
      source_type s1 = Float2IntRounderBase::nearbyint(s);
      return RawConverterBase::low_level_convert(s1);
    }
  } ;


  //
  // Non-Rounding Converter : used for all other conversions.
  //
  template<class Traits,class RangeChecker,class RawConverter>
  struct non_rounding_converter : public RangeChecker
                                 ,public RawConverter
  {
    typedef RangeChecker RangeCheckerBase ;
    typedef RawConverter RawConverterBase ;

    typedef Traits traits ;

    typedef typename Traits::source_type   source_type   ;
    typedef typename Traits::argument_type argument_type ;
    typedef typename Traits::result_type   result_type   ;

    static source_type nearbyint ( argument_type s ) { return s ; }

    static result_type convert ( argument_type s )
    {
      RangeCheckerBase::validate_range(s);
      return RawConverterBase::low_level_convert(s);
    }
  } ;




//--------------------------------------------------------------------------
//
// Selectors for the optimized Converter class.
//
//--------------------------------------------------------------------------

  template<class Traits,class OverflowHandler,class Float2IntRounder,class RawConverter, class UserRangeChecker>
  struct get_non_trivial_converter
  {
    typedef GetRC<Traits,OverflowHandler,Float2IntRounder> InternalRangeCheckerQ ;

    typedef is_same<UserRangeChecker,UseInternalRangeChecker> use_internal_RC ;

    typedef mpl::identity<UserRangeChecker> UserRangeCheckerQ ;

    typedef typename
      mpl::eval_if<use_internal_RC,InternalRangeCheckerQ,UserRangeCheckerQ>::type
        RangeChecker ;

    typedef non_rounding_converter<Traits,RangeChecker,RawConverter>              NonRounding ;
    typedef rounding_converter<Traits,RangeChecker,RawConverter,Float2IntRounder> Rounding ;

    typedef mpl::identity<NonRounding> NonRoundingQ ;
    typedef mpl::identity<Rounding>    RoundingQ    ;

    typedef typename Traits::int_float_mixture int_float_mixture ;

    typedef typename
      for_int_float_mixture<int_float_mixture, NonRoundingQ, NonRoundingQ, RoundingQ, NonRoundingQ>::type
        selector ;

    typedef typename selector::type type ;
  } ;

  template< class Traits
           ,class OverflowHandler
           ,class Float2IntRounder
           ,class RawConverter
           ,class UserRangeChecker
          >
  struct get_converter_impl
  {
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT( 0x0561 ) )
    // bcc55 prefers sometimes template parameters to be explicit local types.
    // (notice that is is illegal to reuse the names like this)
    typedef Traits           Traits ;
    typedef OverflowHandler  OverflowHandler ;
    typedef Float2IntRounder Float2IntRounder ;
    typedef RawConverter     RawConverter ;
    typedef UserRangeChecker UserRangeChecker ;
#endif

    typedef trivial_converter_impl<Traits> Trivial ;
    typedef mpl::identity        <Trivial> TrivialQ ;

    typedef get_non_trivial_converter< Traits
                                      ,OverflowHandler
                                      ,Float2IntRounder
                                      ,RawConverter
                                      ,UserRangeChecker
                                     > NonTrivialQ ;

    typedef typename Traits::trivial trivial ;

    typedef typename mpl::eval_if<trivial,TrivialQ,NonTrivialQ>::type type ;
  } ;

} } } // namespace boost::numeric::convdetail

#endif



/* converter.hpp
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
*/