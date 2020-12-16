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
nWG3l2nUfPAPjR61yAkYhZW3XGiwuhp9/Gv5wKgXsnw3Y4pLJ57qXi77jmmEjt5fKjaacLTAQeg9rUJtLztZZfuABe0Oy4KFgSxeoCZ3nqnBiQebuef2SVZH3xYv3PujxjRRNmn6AxqPzsvzuRqICiqUPVr3J474y6OdvJkwIweHo1sjJthavBzxD0PdtmHpm3toPDFNGqZrQkvBmTjYhctNQuSCx/UcU+/HtcbP6X1hpLSfXYWogmnCaPIwzMneD8enRzHx8SXWzR+IDjrnsG7Nfxie3Fd8EmOoei8YTZ/2ZojxQyQvssaQkqnIMDFDWtJ6sVUlnqYpA3FnYjgCh9wUvQdZY9RnA0GNfvzlFIFZHzbBxPod4fKMB1O/4kjHybiw+q7c8n4ZmByMIy29uNY8i+fuZtN36Ak6nhTwylkirLQk2u9qJnebjcGW9GucFnuIfnOO41R+BPO3xXDfodFMWFsh/xUewnfVAXDS34L0U14ImxXNkX62Iky7hgf1JoivqX0xItqNcQPG8W5NiJxj+AhRrkPkS211WjS1EG4689mv81lcGaqKY6+LOVNJ8L9TK2RlviMWPaiXc3S0+TSmuyh70MAm15PlolFNobqpP+4tmqJgMV+4N8UYa/9EcfbI9/B+Zijv5/qhzW8rMaYhCBPco0XI5hmYPm8kfcoPs5PLHhTubY6J39eKqFpneg/ogC2WTRBj2IGTzVbi7pID6K+Sy3V9Wou/ynuRF7APv+resn/P2cKrcCMS6ueISdmBnNmqo1jQtxlzJ+mJKZ7b8dn4E3oOdWZuD2/R7a6iB39Plo4rd8M9XA9fVC7SwOs4psqHTGmTANMvkRw4NkNWBhSjdm6ytBrWErG547GhaD36/OcrIry+wnvBeUTPuw+7e17IiIrHIJdE/EnvwMzXL2U/M1XU7t6Fj2VPeOahNn3OvaeNRx8x4GcbdpjlimGnlfHDby06VZii4Fskm6024l71GvlQvYH17X5yoU8NrjRL56+q4dSt2c4kryTOzOzFjL+7FTzkLPK9HuDXwA/C/cpcFhjc5XCfFZQ+hzDYvi3t2oTTriwXszrPEkemluFIl0KhFb0CPuHpcvtTG/Q5oozV2x6g5FKs8LjryFEmlWievJQx947DpfdVRm7TFW8W3oBItmWHvaeRda9BOltv478/tXzvuIXXgu/y5cFT6OAbJ8OEL+bEKXLG8/6MFIvkqjVT+TxwhXBrOxS31ZaIicOduXyTgl+ersT8DeFiWfwlpE79KnJ2neGx0e6ovGDAb41tmLBKsk/NDmkwOAnfF/eSW67GwjPfjBucjrLHGQmvFCNmLuzCCTsaEDB6k4g9kMI0ld/8ZxsHm3tt5JmcWdTtO1gsy0uG1vXe2JIWjieFzRBf+gyWw5fSVe8ara+U8Fy3Bkw/OodrdNNgM61Q2NjuUuzRF4jUuff50+m3OOO7kkkZN7Dl4lrYSUcGf5vMnj/3cGeCmyJXtpPFuV6ILFlLQ+VaJIXtR8CMHLZZ+Zr2rwT//RsiV8au4ephgSLX7jn3PSxm59n1bPMzWEydd5I/9MphvOAMvSdvldaHhjFuoy2GpQ6k2iVbHnbThvvtlZzwXwwenBGyZcJcJIpuDDj0kd1j3gi3Gge8ESv5MFvAqcluoTNiEL6UxvFUQxEzprWCq9UPvD4WxW/avizxnitv3W+KZbpafBDvS9d5C8W70W5cfD9SvjVZiM+djIVBSBcsaWovT7z8go8VoXA3CcLgE9Xoe3MCphxTsGbXBTR6eUKcqPxHbU8NOtgOROccO2HfeAAPjSywu+U0zFBOFf/uT4WGhw2DRBZabzIVdm32svHtDdHWMgWzj80=
*/