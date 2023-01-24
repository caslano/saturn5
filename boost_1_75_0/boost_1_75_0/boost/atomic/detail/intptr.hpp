/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/intptr.hpp
 *
 * This header defines (u)intptr_t types.
 */

#ifndef BOOST_ATOMIC_DETAIL_INTPTR_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_INTPTR_HPP_INCLUDED_

#include <boost/cstdint.hpp>
#if defined(BOOST_HAS_INTPTR_T)
#include <cstddef>
#endif
#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_HAS_INTPTR_T)
using boost::uintptr_t;
using boost::intptr_t;
#else
typedef std::size_t uintptr_t;
typedef std::ptrdiff_t intptr_t;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_INTPTR_HPP_INCLUDED_

/* intptr.hpp
vNIvzh+/vl/piO8B2Ny5uuH6+0Jt59Wm/eFHc3w6VqfszW9cX9IrerzTT39XbD5M6jmY3k4I/iF8CWtf+X2aQb4dtntw87ROqwdKWoWiQuE+uytK8J9l/hcZsJjV+2j4w9riWH49uAW1CBCPKVv9WYa62IYndaMN1tb/vGuG++4WJiFaH1d1uUN3KvpWThJU7mqetBqy/Cn31/cPF2pZJlYHqkw3nwwFTQT9hX2xs0gXgCCQIEpjNu3qDV0GpQAfl5qa6kNVnFf+NSGLWHIrlfDchpGGO2Vo7V9OTcJ0Tv9ibC5r8VKj0eqeC4CThYOhKonNsg7XJwUF7K5zlrXyLmfdnIo9vDyZzeqi8KLxDLt8a1VbvgZuiz7zXPwLzFLMsi2/bRQhzyaS4AC+06Z4FHL0825TQ5n6f73dP/KSV8uY3nAwrIoS4XWMYAsh14qd/M7ec2tqscjvYMynqan8yBX6ujgvTKePqn3WG7hzikGc4W0pPaIzqp1ZLqpGorHhi9eWMmK9Kx0R//5aPYyCp7Sk9lkfwXCEv/wX0A2ssLBvjvTg0vncW8oykBJhUa0vT+omUbofPYR6WntFZnsd/+PypvTYkdDjjpuQ8wbwXYXj9mn9VhRFmE0rIXwaHKgKp9fPVLXNQaq9Y0nKFe9NRnnMMICO4ScwS+pE7oxTT5afq3h1fg/R70nAwdCLh7jxHrNCOL92GcVsefvT
*/