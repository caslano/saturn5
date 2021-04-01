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
zeXApadXJRq9OfYSMI9sP8uxWmpCSLeLumbaZgFVl7bFZnlvS2d4lnpEC2HkDwWPPGIKMpKtqp2KbM5wX5Cts4THvUKj39B1Ds0M0HAZGKm0WgQYymSlVRm3dsARMOVGK6mZ51G1GNTaEb8ZI+HvV9TOiYgmG3jd3Dyn1QionnTzObzHE0FxHZnMO75i0IxEw+cURXH5FHSugzAIZ4glbPZ0hHEbHvtXAR0ymHfoYt3PX+xFMlwmJkFJcGUTI+Fgc/bmQ0p/yGolEDKJT1+LYRpSqRZL6PtH5PeQaHLYDov5cKNpK7rTlEQEguD1jz5mnA3p49bGaTuExP6HUnxkSMkHFge4/zLFGwBml3wE0A78iJE32s+IIsc7FVPl8+Nfxwyfh9edZ96xrrl1VUTAF/joP3GUYz0j0hSzCPAtKkqf6WqTtqBQswaRM9Odo/zlx2JctSvmJXmDECd5b2LrRt3Vzv3balJefHpwxC9F7XfqsbBwuFL7luAEPLSV7HhNiEndiy+8psarmTTLwojCAS5Nm4s6wFG8OMNq4MIbnlB1ZTxeEO/PlpVmwA==
*/