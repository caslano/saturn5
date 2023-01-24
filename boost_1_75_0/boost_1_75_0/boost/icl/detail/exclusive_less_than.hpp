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
/i+d5puYbVJwB3ZvhhSNwQBkFYfLbpgmB/snZkP5bMRC5FxRYD9dxqPj/cWVPMVeKCckVEq8VkoECDyoDCALTfUiOWdW71msqJB38z3MVeUxiM579RbYP+ufrxtZuYY+VoevB+2l67EFxim3DLzzTbbyPaqs2NALQfRwLC/OibIhNlSbieH9vhi1XDQ2Kjh0NKeoGwcZc+PF1h/FUlqH0aKlVSsssa5MvrYrFvDDyvh4ukSCL8aqZoN9j1WHRILSTNrLZr5AIPTvLdn0KtSmVI8HF8FeCkFrn59F2DZJVHJ47PGk18YHfx1tusSaOwT/mRQw+w4dvnekOxmPN8RuJcelR/worzBSCy2n5oCRuemHUUBm8m3huXM2fHUZcS3jFVRShkXjh04fJ82Qnh6/nsq+Yo10ec9MwpixYeDsc4hKWnDyKE6UPclNwK2WiQBDl38aRdk2XRpvOvjd5GHf+BF0XGJlMzVYS3HarwQt90RxQ4IAXq+6fh7MspIMVOXhy/X/KiTJ8gVE9idTEl5x8y6jsvmLmfsEccVmTcRQj8IovTPiMMHWeNPvIGS7dlpqVu3OqeNBZeVERoj8dpP/e3Cb8XFkIalIeUCMJzX5JH8u5mfYgi0jAQrYqoPhAHvJOli7hHnpEiQKhaZccMvOMOuCa0mSnwsfls2mL1tV3VMsCHrRTzWmDsuC7oQ6H/D1hH1JbvoA2dX1wAJb
*/