/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2011 Helge Bahmann
 * Copyright (c) 2013 Tim Blechmann
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/fences.hpp
 *
 * This header contains definition of \c atomic_thread_fence and \c atomic_signal_fence functions.
 */

#ifndef BOOST_ATOMIC_FENCES_HPP_INCLUDED_
#define BOOST_ATOMIC_FENCES_HPP_INCLUDED_

#include <boost/memory_order.hpp>
#include <boost/atomic/capabilities.hpp>
#include <boost/atomic/detail/operations.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

/*
 * IMPLEMENTATION NOTE: All interface functions MUST be declared with BOOST_FORCEINLINE,
 *                      see comment for convert_memory_order_to_gcc in ops_gcc_atomic.hpp.
 */

namespace boost {

namespace atomics {

#if BOOST_ATOMIC_THREAD_FENCE > 0
BOOST_FORCEINLINE void atomic_thread_fence(memory_order order) BOOST_NOEXCEPT
{
    atomics::detail::thread_fence(order);
}
#else
BOOST_FORCEINLINE void atomic_thread_fence(memory_order) BOOST_NOEXCEPT
{
    atomics::detail::lock_pool::thread_fence();
}
#endif

#if BOOST_ATOMIC_SIGNAL_FENCE > 0
BOOST_FORCEINLINE void atomic_signal_fence(memory_order order) BOOST_NOEXCEPT
{
    atomics::detail::signal_fence(order);
}
#else
BOOST_FORCEINLINE void atomic_signal_fence(memory_order) BOOST_NOEXCEPT
{
    atomics::detail::lock_pool::signal_fence();
}
#endif

} // namespace atomics

using atomics::atomic_thread_fence;
using atomics::atomic_signal_fence;

} // namespace boost

#endif // BOOST_ATOMIC_FENCES_HPP_INCLUDED_

/* fences.hpp
dZJmHqt5bbzXnd5sH3sosh+7alu5S+y0LI/bO0K3d4Edf6fr9i6wQL1D3THn40tznyyrWtB8YGXLZXfOc3un6PaOtvPmUkSKATbGkGuJXJPqQt499ZJ3H4mwF0yCKbJ+BGbEyLkr1406mIcksN2wvKPMhAVwIKyBWfBqeAa8Dg6CN8HBcB0cAjfCYXAvzIa/gmfBQ/BsGOdh3zAJjoIpcDQ8B54LL4afhdPgGLgIng9XwPFwJZwA74MXwqfgJPgDqGKGwanwdXgRfBPmw6NwOjTr6IVD4OVwLJwLZ8Mvw1o4H66DC2EjLIebYAXcCSvhr2EV/Cesgf1j/e/mzoJXwk/DOjgDLoeLYD3/3whXwfVwNbwbXg+fhjfBffAb8DfwFvhb2ACPweHwL3AENK/7t8Mh8A6YDe+EufAueD5cD6fCDXAmvBtWwI1wCewLb4P94O2ynW/rRXyvJO+U/iNxTHjH82+NZbLtgY7HMylPjTdWpUbfk0SX6BJdokt0iS6G8R97/i9eWjXqpP3/hxHfb34GY4Pz440YFd9vxsQp3kLvxMsmXjoT17YlhbW1gTiAdenmRz8ln9fvjTuNR+3iZXXGINI3DcAGh3QpRZexRedRXkyBIlQZ47Alqyw0XReh8txDnoZAnkLvzJl2c9U7jXcsMQm5/1VLlrzTSEceN98b7JD3BlZjS5f5DHcfPtFJ1+81bmmHv1dbcwfuEvu6iVJXZDt5i5zsq6h193eXuQpptNFu9FtLzTaqrGbGPmr2febGOreJT/ZpbXyaxLU9fP+G9tgS69wejQ62Ua92t0dRWVh76GMkL07PGTfEd8XYZPp5yj5DTowFNWV+f8CN5PEYxdIegfz9dXssakcsy4A/IGXRHsU2u7bHObfFQWe7qFb728Nb4t4eQ+LD2+M+7Gt13m9V2ZWGrnNVO+ps3dczDvt6hH1lPSX70ie5bnrV9lvtbU/+E2/7rQ5tn9vFue29jnbRgh1o+8QF7m3f2CW8PR4yfUBD96ub/sTbvrFr+L7GmtdX/75KR1cU2q4/gbk4n82wtb3k7+/3QU/y+zHr96ch6cmGmY47t6SXS7q176rbcR0J9B22qL7T33BJMtfZf9CHHJrb2GfItWZjN+f6N9vqr683jnVvjlh30iPWnfRTXPdxgbp3D6/7NvMcD9Y95Dz39/0TIeddaxv1b22j/q0nUf8nRp9E/XuE1//75nXnaV1/+7kmx/6T9vqTP2L9SY9Yf9JPvP5PnkT9y3uG17+Y48nrr3/F6FLnc78w5Pj3Wuq3XNW/elmtrj/pIfW7uQP1Kww5vimfdcoPOY9zEpzrUq/rYjuPHetR30Y96v+N9Qj0yd8c6rHDvA/R9Qg7J53vQ9qoS9NJ1GXj6PbVZfdp4XV5Gt2Dui6h55fz7/rBNupy8CTqsrWNupwt8zIm9zLUcrmMiXqRZelcu7freRlqgCc4B4rnOaKkVTDZN03Nw5K8lNDXSGKMJF3VZ5Oqj49QW9wbyDyJ11W+SUYf/h2DSD1FP1np3av01D2H0vN67OWPJR/zrNT5f7qOhVZWR4gulb/AJX++mZ92jIHEHiO+WNtzHNLMttTzqnS9dZtSR7arOupr0r1qm7JfbcvXccSUjXqcbHvMv9+Hv6Pjah31pXceP3ObC+Du8/+gGj+rzbzxoxUFG+auHjn7nsTc7oc6/m0d53E7t/E59/G8lWoc8a1eSZfee3xl+Ws9PnhvUVztc4xRqf2ef2zE8FkfL7/h4YvmZhzuevO1PBvGm9tPb0lYs2DwLyf86encJ3svvri882K7dXQ8tVbVd9UDd+999/mcnBXPz6yr+Pr9h93mdHR8zoX2/TefmeQ=
*/