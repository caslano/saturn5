/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_INTERVAL_TYPE_DEFAULT_HPP_JOFA_100403
#define BOOST_ICL_TYPE_TRAITS_INTERVAL_TYPE_DEFAULT_HPP_JOFA_100403

#include <boost/mpl/if.hpp>
#include <boost/icl/detail/design_config.hpp>
#include <boost/icl/continuous_interval.hpp>
#include <boost/icl/discrete_interval.hpp>
#include <boost/icl/right_open_interval.hpp>
#include <boost/icl/left_open_interval.hpp>
#include <boost/icl/closed_interval.hpp>
#include <boost/icl/open_interval.hpp>
#include <boost/icl/type_traits/is_continuous.hpp>
#include <boost/icl/type_traits/is_discrete.hpp>

namespace boost{ namespace icl
{

    template <class DomainT, ICL_COMPARE Compare = ICL_COMPARE_INSTANCE(ICL_COMPARE_DEFAULT, DomainT)> 
    struct interval_type_default
    {
#ifdef BOOST_ICL_USE_STATIC_BOUNDED_INTERVALS
        typedef
            typename mpl::if_< is_discrete<DomainT>
#  ifdef BOOST_ICL_DISCRETE_STATIC_INTERVAL_DEFAULT 
                             , BOOST_ICL_DISCRETE_STATIC_INTERVAL_DEFAULT<DomainT,Compare>
#  else
                             , right_open_interval<DomainT,Compare>
#  endif

#  ifdef BOOST_ICL_CONTINUOUS_STATIC_INTERVAL_DEFAULT 
                             , BOOST_ICL_CONTINUOUS_STATIC_INTERVAL_DEFAULT<DomainT,Compare> 
#  else
                             , right_open_interval<DomainT,Compare>
#  endif
                             >::type type;
#else
        typedef
            typename mpl::if_< is_discrete<DomainT>
                             ,   discrete_interval<DomainT,Compare>
                             , continuous_interval<DomainT,Compare> >::type type;
#endif
    };

}} // namespace boost icl

#endif



/* interval_type_default.hpp
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
*/