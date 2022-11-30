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
Xap81T6/MgiT2GSv+HSxv0evNqfh7q+k1vfUcMBXdZL6SdWiIgLZcWZIdpMEN2bUkrDwPSuxTF7ud/jLsKnBsJk+XxjeelJsrGKyzKdjeWLbZH0VnEahYthftIHAgZkBu0jFsF0U9cOvJc+JKIgNGJAf+g4BoyzxzwOjLga5vt+dTj/196JqGXXqA98FiKzzzX/+IJ4vY3XZDiFnfW2eh6xWdm756hozkloW3AxMXyQTz878xQ4vbunW/fjjS5UxFzxyI6sxxNRQSF/2PC/F4bR2EVc0zZ6VlK7GwiVC44P3iP6LVzPsPy28C3KohwWtDlSSf1jk6/9SWGGjXCwZYxQPUwjVFAJcFi+IDlPmUlwV91P0UxzZO5m2Uo/ZlnVcW3a8RwR4h+rEI5syLDYGnCuSs9jybyFnUhoOP8N1oIojVQlfCHALLlyr0p9ukrCeYm6+ig9SHorwcgDFkQrXwySJZB6Jz0onw8N1/mlnaGYY6aMq3iepLIMa1ZbknQVP3BjK7ZhV6jw4PsUTxfuK3axPL2o6268afxcWs8zIqeYVpDDeE6rb8gjcvvAdocjOy6kaama9rii+s6GaI2E28nXI1xhnD1ATpktnv/hEpEfEE3amCNg9ay7DaU1gIsCJEDkWZvft+KzJPFuWVjth7v7zObflaxMCTtYU0wSqhE5k2g9xFp9vOyUrx9waTUroegVtkv9GjWltHyQv3KaoXwbtEI4sKgX14/6p48plb30dr0Ck3/59w2rHuz/JSNaJGDpWkpqeFJrClFQcKbm8VqfzmaCKTLb4dQymZLpHOqGsF9W7Vh5Le7CboI4h+M1Lik9VC4tJQdwf9RqVKii/qZtKVlDnqQR4bFSrjw5FSEpNv7QvrPqRqcbjVOgbE1uPd8ORFFSXaLk/3W5SHjdAYZl3/Mi9wH/x0speNWX9k5mueITplJi0jsmOhwuU3yAJI8mJA1IPe/weTbxMbMC2wo6n9br8qgaWD10c/TnKoiWsFRhsk7ku8OiEt0zZKeR3meIqkKGqmjhWvcE4JChDvZ7V4sPwd2Y2HJIlH758/66CvrxFGLK318T50wDVIKPpyl6oaXctZczgAAQs+9PUyYcRyGxv/spmodcxgSHQ3W05mFKsHwWbeuNCOb2nyr/JgpKT2b0Cq9SOGNJAzpmiiR9Cdgisvf+p/atUA0c8/WFruSxJnOhz5DUJPuf5SHkxy6uR+gon4F/1VBNj/m4jSt24PnydU8igiQ73uL34WbmqSZHbme083jcHXQOrJ55rzdJummGLQo1RQ3KfF6fWaF0cIqJo65D5wlqNqTHrn7tbAXriryCta7BQBbhDjvqh5fVzV7sJrcM1aC30AIoqKthtUhJnShurrVzP471bAO2FQqGOv8MNI9zjuRyVUz7t4rZIP2jYCQxiN/lCmfDsrrkkjAPRxaClk763r0DKgOMexWHObvXq8vfUSUHQzF1u/xAxu9xh9egGyNcI+i5uY/2pi6rpcl11M/0X8pyXltrj6uX5Gb2kSG8TRTguVWuea+rqoKYGYX/DNrlRMMEy8uepX5Kn8gNFCTen1N68391u/hs5NI73IY4LndiA3XYeefwAU2RViKtUbl9dFl9xg2l/XtX4h3f33/bvlcQQTMmB9O+qH4zdzLLCeKJ4rz6qPSoZsmhN28dZO7OHsVFri5aQpfhymqo3snuwmxSY3CbW8EBbk8OSPZOp+0cF0t/iupJlvKPHcm1Ua+Zu4y6u66rrrCuFjsHNRCvkalvWn+fsjlSNV4xXrqkcK9drVjDyZREmE/imL10x+bdnJAdv+NnFyNt6NBEafJXc/TUayyO5OzOq0f/N/tx66fKzP2o2Rt76sz+58mKh4X16d4SWBd0ao1UdRj41rnGwzza0EcUXyCu/NGzL1omz535qk4SraF1WGFeZT0rYMWG9zczXmIeyqT540NwLP72l77+G4akEasEXRAyGmifWrVrFPPywbl7foNy0MBeWFJRU7kmeDDUuotZXZlQIVwZWPnT+M2u8WKgyuLUXq71er6JxsFRpfqBF0TypeiBTOfKdHKko1KLRDjAcEH6xEHG3m198bKJ7mfTs+X18OOe3hJZ/ZxVmvLLikgnerZiaYhXG9FSJMeGSjSrXSozBMbWXzLHTDxaZaSYOJkbqARUPi1UD08kLn4tiUddsN/9dzx+2WFQZa1HJZIV90bh0wfchQHfpzGR07u9feulCQHjdYpAyVlVdsWESEA7UVG4MdNhZfmmO28rX6PGSFkO+zkTVhBg/MVy25HCcMP7R3qym3vzHkRz7LPWLrU1jMGt9CAcht+FwFdz6qK6KWRDZwMdg/63sih7mMX3kN2WpPGXOPcfr5Yw6LckgDIdoqw2Pnz0iH87PWbeoVIsK2WxtGNNm5m+bTi0O/3mK7r9VE4J/XaYjh6oJh8vt43iw+hthNxmv+SoXpySQEPv6JCCXKWIYnDkFSI79tSkroSAzPUp0EE7icU514KAaiIUvN3ln0ukT4Ob1K8Q5r/DHOtA4PdquzjtAT9yauYiDHdibOjOnVknqOD1XBx3QhqHGVcXDDyWfqwLLPJuSHSotK7ORYC9zHUSar22P0jZLKLcJR5skCl/6lcrBkzofWqLpyt1XTTgSPHcXoWcOfi3ZsXPnow4gLV8HwcwptSKRYh4D85ajwGaXv98zX4j7O37B/OdBJ8arKDP1zcv+hR5umqhNpU6kL44yBxpkN5gW1mMcJL5zDnXUev+wpCW0d1qBl0ijP73B9mLFcchXCHYRj1feuWzOXQ60a7dvJ+AJO8ndhBc2URkVWIp3/3jiJtT7jSRr2o5ugMnu/V1Zp87hmJ6EN/aEhbRWkZjbfXPy+YMTR1qoy7e6Z6Yjup9sOkfG0p6z97LVnkTBuAuO0Qm5Ww9uXrrE/UJ+1RqVNW8e5GHmdPOTNLxvRlaXukfF3KTMeUL8K8nx9+lVsXvDY51jLnvdsRuJccyhMtYm8Jd0IG7NYN5gIXMesyGqrdUCR1G7tuIq3ORt9nHlT0uPusybn07R6g+TLxdtdmbJU71sEw5LYqS2u5hLS8LV1IamZ28VpCZuMqzc/cIW1NjmWnvr+Cfl+fbtxGvu8/fOyH0mII08dsp2nXY68yWLXVp+vVjb/u9UH1cCl76x83XPknx4nR6axBOu0GAVQq41wUim2BqU0/QW5fvbgE6T9q/zi5OianZGR1GSvsOzrwSbbdio1BRk8/jr+F8ow/rsXwsaYtvKNnaq9S2QLC4sNH0gVkiW0/0Ur2EQfbbaNBzaRg6SqyBZxcfKWw8NH0lrPtqsON2n3Ri8tkdvJLXlih4N+4ydJU+aa4/U2L04unTW9Y40l/T4D9Ec2RxVebvabUfghwDDp4cHgX9cfDG88NWGlpEq1pLyT0NNVNEieKfe1tazk5PZGKizR5RH2vOycwOLuwsO1XY1InF4/9aOYHFN4ugOeok2RfgN3+c6tNUuF5gWixkm/J7ZGLOHLQg9q4JUfBrqJh+cxkpOU3nZ24be5NNxysE5Yh3vlnFphV5z+thm8s9xXoyx6kjNwghje8FjvVNYuhcstjSSr606MjXcWDxamJKBBvJpsb0brhL40VyOb+48ae0ML94ICXW7ZPgcKcYYzTh+ICi2rV8n1ZnXZdBTRbqYuqDzm0SF60OpDl32P7t/XvTC1/TCndg+WdyTJRGST/EP+J8p2/I50K5pFiEqP7aDCVJkjdj25k2cyhw/294p8H98U2W88KbzV8Wvzl81dFV0JsA/+X+5tjgD0pwRQjUmz8j3+DgSla8YzPYHX3P2FEa6O89QGbVIbzhiOr6fTiim1+4UPiZdJr8Pt5cOcax/+XdvLzisKayQNxTieGD5seWF1whj3h+LvtIouhnFhFcKrPbb3nxrTnECUQKTTv7FM+Vv637m/az7mX9xMohPPsUwME45ViSt968gbJ/LqtwrvlADU750pnYGOzoGO1rlTy3A68uP/lbvn3lSsSMnevRFdDqXRbnBjN4/Ed29f5VKCm06Lz7b2xzTK9/Z6mF9PnYQfc+Y6BXHeqhalnTlyszUKY1M3m2f9If1MFqC11iW9ZCptsIgGhKvxafOeviIpcAks/nPdVsmxSm5V+nwoiSdI7g7ByPjKsPeQuarWKnaH5pdnxCXul6oVKKqxpvZ1M+8+7ekQSX9JcxIzTYyGp6EbtULZgkVJXEVypbKq8+18BkqMthYu8fb1JoPo0u8MrscyW3g9vJYPDLYLw1reAPGez3kkZoPS0tElJ/U1hTk81hCi0KivlO/zks71NL61VACybifwMlYz9ARIOXtjpR7ozv2mYKSPEeNDS1vOW+ZIPlO0y59d4uo3hETXy5cyk3pUs6B4XSFiOE18gpkwnJC/2bzDVJbvc/3Jy837M9XOEOCTR9K+MA1/0of/6G/VMwia179N9vLEq5Mmn71ZjxemfmHsTXRC2njn6nVLc2Yed7ji0WrJ/Axh06ArFpMpkMNVJevzjrTNDOJXWFBDK4GlsLwssEi029V6qFZsAL62j4v+Tf9qE1IZ5xzdYHLQKD6G37jwfX4DgaHby2xS7R6+GiV9kBX2S9V455c3tqFXX4Nx6P2YlP5oxhq3kiVmXp/kUNfN+qUeTeJTRerIVKR/RMla2ZZ49dLFycx7VfjLR0hAXC7RLmedbrV/JW3H6b6cHY4LkMvnYe6RTxmRDuC9vKdxJdaP5fK0wQq9KtJcQ65lx6qYJDMupYfDDIPF4nonK69YjLazjYT2S6zJMdquLKw/Vfy4zmPsaHaWHc3jzULFQjd/DDUDYuPd87VhtLMKMDrWZBPJxlEJJbuX0TDKRgf0J8/ZZN6Bn6bhqDkO6ktTbCu3bdYOiraVjrauR+FLYTxq6wW8Oc2bTUNnVycGJ1YrxRTHVJlU9Xg9Ezuc/q7isAEsSWWSi/1jW2w7CM+f2Ds6jTAGdUf19cVIoWSdlfzBscdlRBfcXPnsjGHrCYsQwPHJJCnE2aheD/duop/FLcVRxwP+jMHz458JdP31S+TXXmz98Qk3W3SN+87Js+Z+zfhlPrhPKpkNzUlk/PWIMyAVzMB86iPH6KWGVhT79mzWYSg5LGWO3HxQR2xuQYcVXSJTrcVzccJfxGOGT3KkKFtAKoW3JgNOl9iP5upeqL/MaM3mxFEZKjA36y1xGZTRS8ugQO356T1B9i5zd4p31Yb9Ns5OK1v+hYlX0cvoPumfCMNXtiusraBQQYkGLzKrjMXcg2cGjfsAiSvH1RLFp80a0Dz6wenikX1qrP7wQg7d7zmQ1vrqPExNIexFcPPTcIbViPmldwVXkcvcx87/debvjYVNHE66KzC7SmK+U3kG4sbI17tLKi9HIiXiYTgtHzxK68qryp2UF2Nb6pXeXlLIvMR6Wck5onSBvdue48WwfSNzSrTyRmyE1MiU/Ubtz2264gtrlULTeYBy7D4T0m9KjGzr/uMtNuzvAZOCc7YlrUa7W6rY72euuxMFws9px1XHDdPF05jiYKC9n7RWYgXnehfFNzX8hAe67ezJx9YNCkwaLBZqNVLfbCSO+YkMhs8wtgl9/cb2TEaHmi39Wqk9f/2nNRapttv8ag95sQ39y036neOqEuhOt6oAdPFUCMd41reqM+KhWFMDXvdLTQqfS9pVGTzAnwfRdWfK+YZ2pmsVcun4U4UXVzEKXlw/hIkfcVTFM4vI7jPRz9N/Zs6QjFWsFWYkMdYY9hB1abG8Ruejp++H9b97m6859sHjt+vOstaTBU21FHhylZxav0Om5uBZU+oETMu6QRMK88IygVL9p4PXJ40c0s9pp5I4BJUAgrDKkPyxdtPhO/iki7LrV5KENDoaIUVw25mYoSo0KleUH3ou9M+vxm5gYzo3UGTqrb+7LTOxoqQaByDNPEGs2bLf8YPst4MPvdp7osdIG09Vn0Hyj/WfyKYpvtnuovkwCKuOJx+sLQw895FnuiSbDANy8py1ZvnQHDtC2S3etv7G/KZfvbMaIyqcLX7MLfk0D5Vqq7LH2fDunMeqaHomHZNZ8EfqheYCBH6MN5zmXeYoBHj7DNmx8yOnGTNjuxAnpQS6IL/5OdGCgvJZle2dx91rTzJN/+whkzFi9WciLU6DYrPBjidPeYJ1DX/vK3aIAxuzSbL9sh2yG4XwXeHr/lUuuVpzFtOWy6eLHeWP3YA7t9FxuSGBuOt+s4N3/u2Tqc4goIfot8R4GbaT/uUXUY9d++avUfy2YBt3qXE+1nmXfrvL2IObH9+WHrzSZMDQq/FpjWXUIxS/xw0oD7IOshQtDIgLC/SL/0+X/nwTV7XLpW0EZZxwrT2erG61tEP6QB6is3o6v92cqgIywIP96J6qZrLeepH+qf55PXG1soKnCPbw5XVa6lFMla/s55u9gtCP/mLKB60bDyHuUHz5cPivKPraoain/FKmTIGFzwB8mmEjGvhRqoTlEfVBkZ11RhGFdWl623rD+vMKxP3fybEBjP9+nmbI+fXotSnxdr9kJYNsdfX+DtaP5QIea1JUsXhSxsQJLm2P7UztC2OUNMzObvoMsguds4tdSke79wXtbf4+XkFeBnc2q2zZEneppyysUSBH5hhIpxBEpj/CE8oH1VLdpYgvZM/wR3Wy7/P+7jbhl88ZDZ+gGQ7Y0DyHpcd19cVvQyObzae9k5vPU2OD60Gl/GXrSo9p+SbltmWNYTFwsaJfsMNFePCu0W8b8PWe9eL20WKmUy95k5R1bWdZNg6EnqdJMf8dFnQ29k9BezOupWlNZrV/RgcuXm8zmA1DmlnSedeJhtPfvgH5f9srJiYZbfFarbTzlJOtE8Dvze8x7Mbv09izWRAF5v1668Yl5uE5uj4jftS+vr7Bvv9JVO0kJegs857/8e/N8ELmTkREq51tqY+nThXH/FDNIckpG/bOdw0tMVSVDpN6ssn7l3ARcEXy8qVSOEYC4bzOi1+WxBeZVHodSA5qvKief/dVKfYMrLj1HIOl29XIdqgX1FRbWhGw77rlDIjwYYM/S/ttZ6nLvkZniYWb9WrHIvPFmtJylER3mLg6duV7dohDeDG+VYJi0THdkA2xbZ7XKaOVqFyzp7Nsp6yLSup+bAqucOjPq691DnWYuq1qM7uQRrmcfmKRqznGoUS7aOBk6GwMH9UAmoU7Q3pLeVmu8NZTGf7bRdT5qvf65eHOd03sPbb+c4Uv0WZHa7Tey2KbnXOBpKryF85X8Q+/cibtPK0MXu9NLYuYgJ/V0IuhaYm7pSnrez/CkPxl/FQZ/zz/oAzNs7nWNeQZE/vUiXkG+wbkj9fGHCphFYKtIqSXiwTWBVsTtOvV8lzFLaovP2oP/Vz/fF+g+YW3qQz0T+P+9Gwk4XmuLPzNsdQ6ON3FxXi4E4Uv2/5uD6RObn1phLUZ0+xWbmHDT8qxzEe904MRse3dXmfArl2ztyW9judjrr2Aoye9RqMOKEO55+oTa6SdnJZmix0qcNmuebCBGVENWWNjl64EP0bNDWPavtt/QBbfKkvYBw2yVvt4u+zKUWfuTQTDk3cZP9z+ui9OR/gSrfkZbbZnDRlJBTjVM4UxfAJ5f6V/+1jl18/tNfHt3h5uCqu2cl/c9bY+Az2JSLw
*/