/*-----------------------------------------------------------------------------+
Author: Joachim Faulhaber
Copyright (c) 2009-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------+
Template parameters of major itl class templates can be designed as
template template parameters or
template type parameter
by setting defines in this file.
+-----------------------------------------------------------------------------*/
#ifndef  BOOST_ICL_DESIGN_CONFIG_HPP_JOFA_090214
#define  BOOST_ICL_DESIGN_CONFIG_HPP_JOFA_090214

// If this macro is defined, right_open_interval with static interval borders
// will be used as default for all interval containers. 
// BOOST_ICL_USE_STATIC_BOUNDED_INTERVALS should be defined in the application
// before other includes from the ITL
//#define BOOST_ICL_USE_STATIC_BOUNDED_INTERVALS
// If BOOST_ICL_USE_STATIC_BOUNDED_INTERVALS is NOT defined, ITL uses intervals
// with dynamic borders as default.


//------------------------------------------------------------------------------
// Auxiliary macros for denoting template signatures.
// Purpose:
// (1) Shorten the lenthy and redundant template signatures.
// (2) Name anonymous template types according to their meaning ...
// (3) Making easier to refactor by redefinitin of the macros
// (4) Being able to check template template parameter variants against
//     template type parameter variants.

#define ICL_USE_COMPARE_TEMPLATE_TEMPLATE
#define ICL_USE_COMBINE_TEMPLATE_TEMPLATE
#define ICL_USE_SECTION_TEMPLATE_TEMPLATE
//      ICL_USE_INTERVAL_TEMPLATE_TYPE

//------------------------------------------------------------------------------
// template parameter Compare can not be a template type parameter as long as
// Compare<Interval<DomainT,Compare> >() is called in std::lexicographical_compare
// implementing operator< for interval_base_{set,map}. see NOTE DESIGN TTP
#ifdef ICL_USE_COMPARE_TEMPLATE_TEMPLATE
#   define ICL_COMPARE template<class>class
#   define ICL_COMPARE_DOMAIN(itl_compare, domain_type) itl_compare<domain_type> 
#   define ICL_COMPARE_INSTANCE(compare_instance, domain_type) compare_instance
#   define ICL_EXCLUSIVE_LESS(interval_type) exclusive_less_than
#else//ICL_USE_COMPARE_TEMPLATE_TYPE
#   define ICL_COMPARE class
#   define ICL_COMPARE_DOMAIN(itl_compare, domain_type) itl_compare 
#   define ICL_COMPARE_INSTANCE(compare_instance, domain_type) compare_instance<domain_type> 
#   define ICL_EXCLUSIVE_LESS(interval_type) exclusive_less_than<interval_type>
#endif

//------------------------------------------------------------------------------
// template parameter Combine could be a template type parameter.
#ifdef ICL_USE_COMBINE_TEMPLATE_TEMPLATE
#   define ICL_COMBINE template<class>class
#   define ICL_COMBINE_CODOMAIN(itl_combine, codomain_type) itl_combine<codomain_type> 
#   define ICL_COMBINE_INSTANCE(combine_instance,codomain_type) combine_instance
#else//ICL_USE_COMBINE_TEMPLATE_TYPE
#   define ICL_COMBINE class
#   define ICL_COMBINE_CODOMAIN(itl_combine, codomain_type) itl_combine 
#   define ICL_COMBINE_INSTANCE(combine_instance,codomain_type) combine_instance<codomain_type>
#endif

//------------------------------------------------------------------------------
// template parameter Section could be a template type parameter.
#ifdef ICL_USE_SECTION_TEMPLATE_TEMPLATE
#   define ICL_SECTION template<class>class
#   define ICL_SECTION_CODOMAIN(itl_intersect, codomain_type) itl_intersect<codomain_type> 
#   define ICL_SECTION_INSTANCE(section_instance,codomain_type) section_instance
#else//ICL_USE_SECTION_TEMPLATE_TYPE
#   define ICL_SECTION class
#   define ICL_SECTION_CODOMAIN(itl_intersect, codomain_type) itl_intersect 
#   define ICL_SECTION_INSTANCE(section_instance,codomain_type) section_instance<codomain_type>
#endif


//------------------------------------------------------------------------------
// template parameter Interval could be a template type parameter.
#ifdef ICL_USE_INTERVAL_TEMPLATE_TEMPLATE
#   define ICL_INTERVAL(itl_compare) template<class,itl_compare>class
#   define ICL_INTERVAL2(itl_compare) template<class DomT2,itl_compare>class
#   define ICL_INTERVAL_TYPE(itl_interval, domain_type, itl_compare) itl_interval<domain_type,itl_compare> 
#   define ICL_INTERVAL_INSTANCE(interval_instance,domain_type,itl_compare) interval_instance
#else//ICL_USE_INTERVAL_TEMPLATE_TYPE
#   define ICL_INTERVAL(itl_compare) class
#   define ICL_INTERVAL2(itl_compare) class
#   define ICL_INTERVAL_TYPE(itl_interval, domain_type, itl_compare) itl_interval  
#   define ICL_INTERVAL_INSTANCE(interval_instance,domain_type,itl_compare) typename interval_instance<domain_type,itl_compare>::type
#endif


//------------------------------------------------------------------------------
#define ICL_ALLOC    template<class>class

//------------------------------------------------------------------------------
#define ICL_INTERVAL_DEFAULT boost::icl::interval_type_default

#ifndef BOOST_ICL_USE_COMPARE_STD_GREATER
#   define ICL_COMPARE_DEFAULT std::less
#else
#   define ICL_COMPARE_DEFAULT std::greater
#endif

//------------------------------------------------------------------------------

#endif // BOOST_ICL_DESIGN_CONFIG_HPP_JOFA_090214



/* design_config.hpp
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
*/