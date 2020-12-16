/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/memory_order_utils.hpp
 *
 * This header contains utilities related to memory order constants.
 */

#ifndef BOOST_ATOMIC_DETAIL_MEMORY_ORDER_UTILS_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_MEMORY_ORDER_UTILS_HPP_INCLUDED_

#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

BOOST_FORCEINLINE BOOST_CONSTEXPR memory_order deduce_failure_order(memory_order order) BOOST_NOEXCEPT
{
    return order == memory_order_acq_rel ? memory_order_acquire : (order == memory_order_release ? memory_order_relaxed : order);
}

BOOST_FORCEINLINE BOOST_CONSTEXPR bool cas_failure_order_must_not_be_stronger_than_success_order(memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
{
    // 15 == (memory_order_seq_cst | memory_order_consume), see memory_order.hpp
    // Given the enum values we can test the strength of memory order requirements with this single condition.
    return (static_cast< unsigned int >(failure_order) & 15u) <= (static_cast< unsigned int >(success_order) & 15u);
}

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_MEMORY_ORDER_UTILS_HPP_INCLUDED_

/* memory_order_utils.hpp
/zV5vIcK2fCo//8kXd/Igk84DgSujbj/r69YSgGkUCULxle1PQsoTnfEWWBtWa3aeITSfVr275D9PDkI+zjS/RONfc43JL4Ki2Lb1zao2KQZJ/HziH9V4oNj2ilXmTQZEl9E/HMSL5RjTJFyyUKuxv74Xtk/zGW7o3lIuaZiC+KqmznuqssaFkba8CBj7Gc2qv1MMMllP6P1LrjOkZurtjtmrT9jR9hL9i+UfIrUFog1QPnVmPL8Qo61R9tB85BmMH5izbq71+rzlGWELhlhGzf149quzUypWU9P+tr4b9wh25z+7ZxtzRRJTz/oto1GVttV13R228d007QJbcfhGO5nO+H683zH6PgNpHd+znvwwfAy+H0668B1UTpeNX5BSUW16Hlb350TreOabpKxO03e6MSn2zF0XuUnmL5PFPmLNM6q99c78R6++v8p5AMif4qu/R3Kb3xM/e8F/yoysyRNlUmTp/ropJGpxK3vyHh978fWc2S9eq56XEUxkNVxdYmUvYT14PoYnTT+kxmDbp3vLrLDbD2u5EWtjM3ohbI/2djFlkj8lxoPt+NJ6HyaFX5muJ7Em6H+bcZCmca7ZHRsLDjPFd/baJ4rmrFxzn9gbNBHbKeP2hkbhWZs0Oae9e6LUyz5fY3CDoR3wQGOr9TrI9Z1uayiRJQ91nyu8mOMf/WXJH4Tz48G6DZWupVt5awhPzLWmi+az0gzZl6Q+DV2LB3Ogs+KTJ3ocKXJY5hrTWvqrfLnmv1DzDo0T0v8eqNPjjxHMGNk8SZnf617DJBH9BhYLe0i/reNL/AJm0UX3WOCtJFjQuqWFEqrddP2yJX0/dx2naSPZStaUc3Z18gWemS3qWxaD/MdgZlrXhe5K2y3zb6uFxHz3POytrvPecU88x+1Wb8/COmFtOWndD8aI/szjY58IHnOt3Os3vZ4xmeqU6/MtnE4KgfCN+mUEviXbMYjHJoLYaL6pSw8ytg8bbMZm37nrU6tu4Ce6fjSsWlkRZfM2ERHdM2FsJ9y+l63OZJem1DpUzmf5YfzjL+X+ATeS6yQ9xLvvL4j65qyWRPTzv9iWZ+taS/H30t8lPcS5npZ7y0qCcepnju/89mdAS+GF8L5sAGWwBWwAa6B1fCLcBl8CNbAVvhZ+ENYC38H6+A/YD3koJLeKUdr6FoFrtFy9OTvPS5fcnlwPZwEr4FnwmthObwdLoZ3wFp4PbwOboJb4Ga4R+UeUbn98CZ4GDapT7hb4FDoyI2BjlwB3AJPhVthEbwVlsDb4GXwTq1Hsjm/cU7XevTn7w+1Hn2cfGFfyDA16+3mwslwILwUDtJ65cHr4XC4C46EX4Zj4QtwHHwF5sPX4QkwwDFPhD3hBNgLngQHw4lwODxF63cqnAonw/PhafBCeDosh4WwEk6DDXAqvBJOh2vgmXATnAFvhEVwK5wVt3P8j71P+l97lxS3c/zo75C28Q6plXAo/i4p/ov/4r/4L/6L/+K/+C/+i//iv/jP/fsE3/+X19Z/TP7/luRZ5j3RgUBbPX5EyNbnYh/w0Kdmlfs9UdmCBSUsyafvRI+0rZkpi0TqeyKV72PeE22W+H08H0vS9Y4i1+OfZdIUGFuAeyS+BWsA2/VOG/8hVQucB+jGx9PdIrfNrKdu6XrqobUp728rO99Wp7rycZaYlWyML5/Pi9wXJJ+apJBM+B3Pt2V/T7Pu7NMSP07fm5iyGfnfeuQ/kHiq+aahmnZfRriUUEMoIXyWMEu/acj1V7GZofcbfa90vd/Q9wZHZL016QvPuk+0tfqsKDLvF0xbet6ba9t43iHW6yOBpwiDCQ8R7ALKfqVXN8jXiqkbKp9n3mffKvHbRP4=
*/