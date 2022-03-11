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