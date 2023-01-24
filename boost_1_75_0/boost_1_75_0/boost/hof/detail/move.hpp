/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    move.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_MOVE_H
#define BOOST_HOF_GUARD_MOVE_H

#include <utility>

namespace boost { namespace hof {

template<typename T>
constexpr typename std::remove_reference<T>::type&&
move(T&& x) noexcept
{ 
    return static_cast<typename std::remove_reference<T>::type&&>(x); 
}

}} // namespace boost::hof

#endif

/* move.hpp
ROYxv+6PKx4A+zbnd9CgjW9NHi7+A1nSYiLBKRtMOlpfaZjNpN1mUpET1JR9sCS9ZAc/ltAKZ3b9q9kqC0t2TLXi53vYYc3x6UXFcDQjfUjR9/X+1rXAg/rWGcVvKrpdTLM+8MHKpFXUEZCuuYd9/u8MovV1iHeCs2wcjelnWq95pgk7S/46GzKuOnTxeUq9nMUQzSydwVNkEPEHlQIriulwI3J2qc3+KuubVFuzKdLUhknRKD2xDfpen+/czWi2skzQZ05LM5qL+3z75eKMRd+NvRJZP+v01Up0wAVjGsfsE0100gGe6VONjD+4sofqeXg1+49FUrlYXJ4VpD0fN9iKbAsg3ZmBn7zn+EuErRE9KSsWbUU3rVRVkcNMC8+kgXX98j87OdrYsHK5p4mG/hD6aEQ1i3p0plV+1lT6yV4WT57sJyX1CBH4OWFIH2Wu/C3SL9nqvXlr3Z6yXeiejkqf5PBHpik5+HfFmt+IQGkHHPM7HJVsn5L7RaGELz1aFP5mQSJHaeVBxWsmQY+JVptHVOvwX6k8xpitAjaNnibvbgSQ1ClyTJaywi/yvWGMTcJeo12e4JN0u5/+ji7OvRQGw/yrfjvQ1SNbWR6b2oAHr1VjtyJqO2jiwno901djwzauUCE05R6LxWNGF5rFOTQzGankwNygrhAnkckIndZtsyPh7cSTmfaZa8Uoj+LJ7qXZj1yT3UCJWBXS
*/