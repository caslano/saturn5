/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_IS_COMBINABLE_HPP_JOFA_090115
#define BOOST_ICL_IS_COMBINABLE_HPP_JOFA_090115

#include <boost/mpl/bool.hpp> 
#include <boost/mpl/if.hpp> 
#include <boost/mpl/and.hpp> 
#include <boost/mpl/or.hpp> 
#include <boost/mpl/not.hpp> 
#include <boost/type_traits/is_same.hpp>
#include <boost/icl/type_traits/is_concept_equivalent.hpp>
#include <boost/icl/type_traits/is_interval_container.hpp>

namespace boost{namespace icl
{

template<class Type>
struct is_overloadable
{
    typedef is_overloadable<Type> type;
    BOOST_STATIC_CONSTANT(bool, value = 
        (boost::is_same<Type, typename Type::overloadable_type>::value)
        );
};


//------------------------------------------------------------------------------
template<class LeftT, class RightT>
struct is_codomain_equal
{
    typedef is_codomain_equal<LeftT, RightT> type;
    BOOST_STATIC_CONSTANT(bool, value =
        (boost::is_same<typename LeftT::codomain_type, 
                        typename RightT::codomain_type>::value)
        );
};

//NOTE: Equality of compare order implies the equality of the domain_types
template<class LeftT, class RightT>
struct is_key_compare_equal
{
    typedef is_key_compare_equal<LeftT, RightT> type;
    BOOST_STATIC_CONSTANT(bool, value =
        (boost::is_same<typename LeftT::key_compare, 
                        typename RightT::key_compare>::value)
        );
};

template<class LeftT, class RightT>
struct is_codomain_type_equal
{
    typedef is_codomain_type_equal<LeftT, RightT> type;
    BOOST_STATIC_CONSTANT(bool, value =
        (mpl::and_<is_key_compare_equal<LeftT, RightT>, 
                   is_codomain_equal<LeftT, RightT> >::value)
        );
};


// For equal containers concepts, domain order and codomain type must match.
template<template<class>class IsConcept, class LeftT, class RightT>
struct is_concept_compatible
{
    typedef is_concept_compatible<IsConcept, LeftT, RightT> type;
    BOOST_STATIC_CONSTANT(bool, value =
        (mpl::and_<
            IsConcept<LeftT>
          , IsConcept<RightT>
          , is_codomain_type_equal<LeftT, RightT>
        >::value)
        );
};

template<template<class>class LeftConcept, 
         template<class>class RightConcept,         
         class LeftT, class RightT>
struct is_concept_combinable
{
    typedef is_concept_combinable<LeftConcept, RightConcept, LeftT, RightT> type;
    BOOST_STATIC_CONSTANT(bool, value =
        (mpl::and_<
            LeftConcept<LeftT>
          , RightConcept<RightT>
          , is_key_compare_equal<LeftT, RightT>
        >::value)
        );
};

template<class LeftT, class RightT>
struct is_intra_combinable
{
    typedef is_intra_combinable<LeftT, RightT> type;
    BOOST_STATIC_CONSTANT(bool, value =
        (mpl::or_<
            is_concept_compatible<is_interval_set, LeftT, RightT>
          , is_concept_compatible<is_interval_map, LeftT, RightT>
        >::value)
        );
};

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
template<class LeftT, class RightT>
struct is_cross_combinable
{
    typedef is_cross_combinable<LeftT, RightT> type;
    BOOST_STATIC_CONSTANT(bool, value =
        (mpl::or_<
            is_concept_combinable<is_interval_set, is_interval_map, LeftT, RightT>
          , is_concept_combinable<is_interval_map, is_interval_set, LeftT, RightT>
        >::value)
        );
};

template<class LeftT, class RightT>
struct is_inter_combinable
{
    typedef is_inter_combinable<LeftT, RightT> type;
    BOOST_STATIC_CONSTANT(bool, value =
        (mpl::or_<is_intra_combinable<LeftT,RightT>, 
                  is_cross_combinable<LeftT,RightT> >::value)
        );
};

//------------------------------------------------------------------------------
// is_fragment_of
//------------------------------------------------------------------------------
template<class FragmentT, class Type>
struct is_fragment_of
{
    typedef is_fragment_of type;
    BOOST_STATIC_CONSTANT(bool, value = false);
};

template<class Type>
struct is_fragment_of<typename Type::element_type, Type>
{
    typedef is_fragment_of type;
    BOOST_STATIC_CONSTANT(bool, value = true);
};

template<class Type>
struct is_fragment_of<typename Type::segment_type, Type>
{
    typedef is_fragment_of type;
    BOOST_STATIC_CONSTANT(bool, value = true);
};

//------------------------------------------------------------------------------
// is_key_of
//------------------------------------------------------------------------------
template<class KeyT, class Type>
struct is_key_of
{
    typedef is_key_of type;
    BOOST_STATIC_CONSTANT(bool, value = false);
};

template<class Type>
struct is_key_of<typename Type::domain_type, Type>
{
    typedef is_key_of type;
    BOOST_STATIC_CONSTANT(bool, value = true);
};

template<class Type>
struct is_key_of<typename Type::interval_type, Type>
{
    typedef is_key_of type;
    BOOST_STATIC_CONSTANT(bool, value = true);
};

//------------------------------------------------------------------------------
// is_interval_set_derivative
//------------------------------------------------------------------------------
template<class Type, class AssociateT>
struct is_interval_set_derivative;

template<class Type>
struct is_interval_set_derivative<Type, typename Type::domain_type>
{ 
    typedef is_interval_set_derivative type;
    BOOST_STATIC_CONSTANT(bool, value = (is_interval_container<Type>::value)); 
};

template<class Type>
struct is_interval_set_derivative<Type, typename Type::interval_type>
{ 
    typedef is_interval_set_derivative type;
    BOOST_STATIC_CONSTANT(bool, value = (is_interval_container<Type>::value)); 
};

template<class Type, class AssociateT>
struct is_interval_set_derivative
{
    typedef is_interval_set_derivative<Type, AssociateT> type;
    BOOST_STATIC_CONSTANT(bool, value = false);
};

//------------------------------------------------------------------------------
// is_interval_map_derivative
//------------------------------------------------------------------------------
template<class Type, class AssociateT>
struct is_interval_map_derivative;

template<class Type>
struct is_interval_map_derivative<Type, typename Type::domain_mapping_type>
{
    typedef is_interval_map_derivative type;
    BOOST_STATIC_CONSTANT(bool, value = (is_interval_container<Type>::value));
};

template<class Type>
struct is_interval_map_derivative<Type, typename Type::interval_mapping_type>
{
    typedef is_interval_map_derivative type;
    BOOST_STATIC_CONSTANT(bool, value = (is_interval_container<Type>::value));
};

template<class Type>
struct is_interval_map_derivative<Type, typename Type::value_type>
{
    typedef is_interval_map_derivative type;
    BOOST_STATIC_CONSTANT(bool, value = (is_interval_container<Type>::value));
};

template<class Type, class AssociateT>
struct is_interval_map_derivative
{
    typedef is_interval_map_derivative<Type, AssociateT> type;
    BOOST_STATIC_CONSTANT(bool, value = false);
};

//------------------------------------------------------------------------------
// is_intra_derivative
//------------------------------------------------------------------------------
template<class Type, class AssociateT>
struct is_intra_derivative
{
    typedef is_intra_derivative<Type, AssociateT> type;
    BOOST_STATIC_CONSTANT(bool, value =
        (mpl::or_
        <     
            mpl::and_<is_interval_set<Type>, 
                      is_interval_set_derivative<Type, AssociateT> >
          , mpl::and_<is_interval_map<Type>, 
                      is_interval_map_derivative<Type, AssociateT> >
        >::value)
        );
};

template<class Type, class AssociateT>
struct is_cross_derivative
{
    typedef is_cross_derivative<Type, AssociateT> type;
    BOOST_STATIC_CONSTANT(bool, value =
        (mpl::and_<
            is_interval_map<Type>
          , is_interval_set_derivative<Type, AssociateT>
        >::value)
        );
};

template<class Type, class AssociateT>
struct is_inter_derivative
{
    typedef is_inter_derivative<Type, AssociateT> type;
    BOOST_STATIC_CONSTANT(bool, value = 
        (mpl::or_<
            is_intra_derivative<Type, AssociateT> 
          , is_cross_derivative<Type, AssociateT>
        >::value)
        );
};

//------------------------------------------------------------------------------
//- right combinable
//------------------------------------------------------------------------------

template<class GuideT, class CompanionT>
struct is_interval_set_right_combinable
{
    typedef is_interval_set_right_combinable<GuideT, CompanionT> type;
    BOOST_STATIC_CONSTANT(bool, value = 
        (mpl::and_
        <
            is_interval_set<GuideT>
          , mpl::or_
            <
                is_interval_set_derivative<GuideT, CompanionT> 
              , is_concept_compatible<is_interval_set, GuideT, CompanionT>
            >
        >::value)
        );
};

template<class GuideT, class CompanionT>
struct is_interval_map_right_intra_combinable //NOTE equivalent to is_fragment_type_of
{
    typedef is_interval_map_right_intra_combinable<GuideT, CompanionT> type;
    BOOST_STATIC_CONSTANT(bool, value = 
        (mpl::and_
        <
            is_interval_map<GuideT>
          , mpl::or_
            <
                is_interval_map_derivative<GuideT, CompanionT> 
              , is_concept_compatible<is_interval_map, GuideT, CompanionT>
            >
        >::value)
        );
};

template<class GuideT, class CompanionT>
struct is_interval_map_right_cross_combinable //NOTE equivalent to key_type_of<Comp, Guide>
{
    typedef is_interval_map_right_cross_combinable<GuideT, CompanionT> type;
    BOOST_STATIC_CONSTANT(bool, value = 
        (mpl::and_
        <
            is_interval_map<GuideT>
          , mpl::or_
            <
                is_cross_derivative<GuideT, CompanionT> 
              , is_concept_combinable<is_interval_map, is_interval_set, GuideT, CompanionT>
            >
        >::value)
        );
};

template<class GuideT, class CompanionT>
struct is_interval_map_right_inter_combinable
{
    typedef is_interval_map_right_inter_combinable<GuideT, CompanionT> type;
    BOOST_STATIC_CONSTANT(bool, value = 
        (mpl::or_<
            is_interval_map_right_intra_combinable<GuideT, CompanionT> 
          , is_interval_map_right_cross_combinable<GuideT, CompanionT> 
        >::value)
        );
};


template<class GuideT, class CompanionT>
struct is_right_intra_combinable
{
    typedef is_right_intra_combinable<GuideT, CompanionT> type;
    BOOST_STATIC_CONSTANT(bool, value = 
        (mpl::or_
        <
            is_interval_set_right_combinable<GuideT, CompanionT> 
          , is_interval_map_right_intra_combinable<GuideT, CompanionT> 
        >::value)
        );
};

template<class GuideT, class CompanionT>
struct is_right_inter_combinable
{
    typedef is_right_inter_combinable<GuideT, CompanionT> type;
    BOOST_STATIC_CONSTANT(bool, value = 
        (mpl::or_
        <
            is_interval_set_right_combinable<GuideT, CompanionT> 
          , is_interval_map_right_inter_combinable<GuideT, CompanionT> 
        >::value)
        );
};

template<class GuideT, class IntervalSetT>
struct combines_right_to_interval_set
{
    typedef combines_right_to_interval_set<GuideT, IntervalSetT> type;
    BOOST_STATIC_CONSTANT(bool, value = 
        (is_concept_combinable<is_interval_container, is_interval_set, 
                               GuideT, IntervalSetT>::value)
        );
};

template<class GuideT, class IntervalMapT>
struct combines_right_to_interval_map
{
    typedef combines_right_to_interval_map<GuideT, IntervalMapT> type;
    BOOST_STATIC_CONSTANT(bool, value = 
        (is_concept_compatible<is_interval_map, GuideT, IntervalMapT>::value) );
};

template<class GuideT, class IntervalContainerT>
struct combines_right_to_interval_container
{
    typedef combines_right_to_interval_container<GuideT, IntervalContainerT> type;
    BOOST_STATIC_CONSTANT(bool, value = 
        (mpl::or_<combines_right_to_interval_set<GuideT, IntervalContainerT>,
                  combines_right_to_interval_map<GuideT, IntervalContainerT> >::value)
        );
};



//------------------------------------------------------------------------------
//- segmentational_fineness
//------------------------------------------------------------------------------
template<class Type> struct unknown_fineness
{
    typedef unknown_fineness<Type> type;
    static const int value = 0;
};

template<class Type> struct known_fineness
{
    typedef known_fineness<Type> type;
    static const int value = Type::fineness;
};

template<class Type>struct segmentational_fineness
{
    typedef segmentational_fineness<Type> type;
    static const int value = 
        mpl::if_<is_interval_container<Type>, 
                        known_fineness<Type>,
                      unknown_fineness<Type>
                >::type::value;
};


//------------------------------------------------------------------------------
// is_interval_set_companion
//------------------------------------------------------------------------------

// CompanionT is either an interval_set or a derivative of set level: 
// element_type=domain_type, segment_type=interval_type
template<class GuideT, class CompanionT> struct is_interval_set_companion
{ 
    typedef is_interval_set_companion<GuideT,CompanionT> type;
    BOOST_STATIC_CONSTANT(bool, value = 
        (mpl::or_
        <
            combines_right_to_interval_set<GuideT,CompanionT>
          , is_interval_set_derivative<GuideT,CompanionT>
        >::value)
        );
};


//------------------------------------------------------------------------------
// is_interval_map_companion
//------------------------------------------------------------------------------

template<class GuideT, class CompanionT> struct is_interval_map_companion
{ 
    typedef is_interval_map_companion<GuideT,CompanionT> type;
    BOOST_STATIC_CONSTANT(bool, value = 
        (mpl::or_
        <
            combines_right_to_interval_map<GuideT,CompanionT>
          , is_interval_map_derivative<GuideT,CompanionT>
        >::value)
        );
};


//------------------------------------------------------------------------------
//- is_coarser_interval_{set,map}_companion
//------------------------------------------------------------------------------
template<class GuideT, class CompanionT> 
struct is_coarser_interval_set_companion
{
    typedef is_coarser_interval_set_companion<GuideT, CompanionT> type;
    BOOST_STATIC_CONSTANT(bool, value =
        (mpl::and_
        <
           is_interval_set_companion<GuideT, CompanionT>
         , mpl::bool_<(  segmentational_fineness<GuideT>::value 
                       > segmentational_fineness<CompanionT>::value)>
        >::value)
        );
};

template<class GuideT, class CompanionT> 
struct is_coarser_interval_map_companion
{
    typedef is_coarser_interval_map_companion<GuideT, CompanionT> type;
    BOOST_STATIC_CONSTANT(bool, value =
        (mpl::and_
        <
           is_interval_map_companion<GuideT, CompanionT>
         , mpl::bool_<(  segmentational_fineness<GuideT>::value 
                       > segmentational_fineness<CompanionT>::value)>
        >::value)
        );
};

//------------------------------------------------------------------------------
// is_binary_interval_{set,map}_combinable
//------------------------------------------------------------------------------
template<class GuideT, class CompanionT>
struct is_binary_interval_set_combinable
{ 
    typedef is_binary_interval_set_combinable<GuideT,CompanionT> type;
    static const int value =
        mpl::and_<  is_interval_set<GuideT>
                  , is_coarser_interval_set_companion<GuideT, CompanionT> 
                 >::value;
};

template<class GuideT, class CompanionT>
struct is_binary_interval_map_combinable
{ 
    typedef is_binary_interval_map_combinable<GuideT,CompanionT> type;
    static const int value =
        mpl::and_<  is_interval_map<GuideT>
                  , is_coarser_interval_map_companion<GuideT, CompanionT> 
                 >::value;
};

template<class GuideT, class CompanionT>
struct is_binary_intra_combinable
{ 
    typedef is_binary_intra_combinable<GuideT,CompanionT> type;
    BOOST_STATIC_CONSTANT(bool, value =
        (mpl::or_<is_binary_interval_set_combinable<GuideT, CompanionT>,
                 is_binary_interval_map_combinable<GuideT, CompanionT> 
                >::value)
        );
};

template<class GuideT, class CompanionT>
struct is_binary_cross_combinable
{ 
    typedef is_binary_cross_combinable<GuideT,CompanionT> type;
    BOOST_STATIC_CONSTANT(bool, value =
        (mpl::and_
        <     is_interval_map<GuideT>
            , mpl::or_<  is_coarser_interval_map_companion<GuideT, CompanionT>
                       ,         is_interval_set_companion<GuideT, CompanionT> > 
        >::value)
        );
};

template<class GuideT, class CompanionT>
struct is_binary_inter_combinable
{ 
    typedef is_binary_inter_combinable<GuideT,CompanionT> type;
    BOOST_STATIC_CONSTANT(bool, value =
        (mpl::or_
        <     
            mpl::and_<is_interval_map<GuideT>, 
                      is_binary_cross_combinable<GuideT, CompanionT> >
          , mpl::and_<is_interval_set<GuideT>, 
                      is_binary_intra_combinable<GuideT, CompanionT> >
        >::value)
        );
};


}} // namespace icl boost

#endif



/* is_combinable.hpp
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
*/