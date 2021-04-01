/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009, 2011 Helge Bahmann
 * Copyright (c) 2009 Phil Endecott
 * Copyright (c) 2013 Tim Blechmann
 * Linux-specific code by Phil Endecott
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/caps_linux_arm.hpp
 *
 * This header defines feature capabilities macros
 */

#ifndef BOOST_ATOMIC_DETAIL_CAPS_LINUX_ARM_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CAPS_LINUX_ARM_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#define BOOST_ATOMIC_INT8_LOCK_FREE 2
#define BOOST_ATOMIC_INT16_LOCK_FREE 2
#define BOOST_ATOMIC_INT32_LOCK_FREE 2
#define BOOST_ATOMIC_POINTER_LOCK_FREE 2

#define BOOST_ATOMIC_THREAD_FENCE 2
#define BOOST_ATOMIC_SIGNAL_FENCE 2

#endif // BOOST_ATOMIC_DETAIL_CAPS_LINUX_ARM_HPP_INCLUDED_

/* caps_linux_arm.hpp
beReWAbJYXAmCAFefDFylKN6/1JQiqI2ohUvZu3hPpOL/bgVv/6V7rk+GVaV6vhfyhjcOz2eB6Nr2UC7D7Z4X7DB55hFB4FYFMoPD/S1Bmmel4ShdH3HOtCibNeeLPDOFyzlEJbYs04Awol+hQjE2XCjBhi/FmoU1vHRkTEedUzOT46aJ9u/yI3rkmEQE8kHMacqyKMb5sS5S6pk3Xdbc9Vb6G69680vbcHoKeAGNRGEk0Vr7X3BvtC0+U1auN+gSfu+kgFxs3RzfFhFOHM1PR68zI+POJlqM2gjOpqSuazrCPDxMl8yMnYu4gDvpNk1XqZ2EEYZsGwPCnEGdXsSzRs3DqMqxOMyqDouWMus91ljoGkuyoeCNo4lbrFCrFcprm5cgv2MsPEzUPCJu79hlkzljbic/WQTWxQHySrkWE0/pB96bME8lFTeF7ANerQSySsAHLGv+HyZX7H0JiNpYibOFS7Sw+uAQ9Ba+GitFXZHgC+lKmB0h63F5RbfAXtZ65eourNBeK+HCUocUBic9yV/FyIwWSWF0xAuCMh66KIoYBVljY2uxodcdw==
*/