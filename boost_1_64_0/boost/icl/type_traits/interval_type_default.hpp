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
0DlpEVXxCvDliJHM2KMMFX6MDhPRb/X9qa6aIsClyRTxqybDXwcnOZ9Hn2d/lQawGO7BJmHgJSsLP1QRWucwaS4GVM5R4wM2Bkc3SVr7b7+XkcLiQdgCel9QwjGxjdldS3W2OieolOMoMOiFv+rgkhCn01eirnVmZINmnhSNy2g9/k+smkE8n6Qym4mHLGDvE4e7cBWd6lJvGGngL6y6Z4SrR3oUnizV1kAMaxjtYrjjcfXYAIOjzMD6fcZvzQ3SQWSP1UClLVPHY12KZUIsUjZkFkGIeg15/qt01DyAsOMmxfiIjWnCJKgiSAtTefTVxo1oOSDI2+32z90G11qY0KlT0slcDzN5o8AaSP/hnEJNcks5jpYrniUgWX3hveca4aKB0nTa1cI7FuJ3BFWKHYjnDszTiJU15MB1XJ3DzRFFxHsfqMrZv7BihyGoSSfM51ikdjd+e15ptZzZRTJ+fWAYsyQ1pntg8ogKjgW3ox58pm9VZNDZNrKZr7GpdE7tA6cyvBSyEbQC2MhwrZZB2YNt2+WGfpUpC41NE6aqzgU9YXxge3yUdz78Sg==
*/