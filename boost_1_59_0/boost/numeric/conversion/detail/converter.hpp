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
#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT( 0x0561 ) )
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