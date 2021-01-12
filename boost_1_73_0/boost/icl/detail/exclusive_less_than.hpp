/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_DETAIL_EXCLUSIVE_LESS_THAN_HPP_JOFA_100929
#define BOOST_ICL_DETAIL_EXCLUSIVE_LESS_THAN_HPP_JOFA_100929

#include <boost/icl/concept/interval.hpp>

namespace boost{ namespace icl
{

/// Comparison functor on intervals implementing an overlap free less 
template <class IntervalT>
struct exclusive_less_than 
{
    /** Operator <tt>operator()</tt> implements a strict weak ordering on intervals. */
    bool operator()(const IntervalT& left, const IntervalT& right)const
    { 
        return icl::non_empty::exclusive_less(left, right); 
    }
};

}} // namespace boost icl

#endif



/* exclusive_less_than.hpp
RMFg+2E9oXi7cPQ95aufKQ6rdZSKCVm7iZJUlzU6yG56QV15eiLwm/6iuP8r9JpqEff/pVt63duWTa8jbS+dtT7zGTZ7Zqtj1xTMyMSp2ByWgqzVKNt937uRy0GId48zGMKIGIMRsBxhXHDJX6eRa/+enV+M6V4MMsxAA3GOnFzIc+RliDXbOIiHWV1K6Z0l8h3vNIA0zufRXQrpflMphPk/rcWCssyljsH8Hc+n6VUk+t/P
*/