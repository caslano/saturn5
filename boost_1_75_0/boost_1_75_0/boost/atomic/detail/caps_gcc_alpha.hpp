/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2013 Tim Blechmann
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/caps_gcc_alpha.hpp
 *
 * This header defines feature capabilities macros
 */

#ifndef BOOST_ATOMIC_DETAIL_CAPS_GCC_ALPHA_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CAPS_GCC_ALPHA_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#define BOOST_ATOMIC_INT8_LOCK_FREE 2
#define BOOST_ATOMIC_INT16_LOCK_FREE 2
#define BOOST_ATOMIC_INT32_LOCK_FREE 2
#define BOOST_ATOMIC_INT64_LOCK_FREE 2
#define BOOST_ATOMIC_POINTER_LOCK_FREE 2

#define BOOST_ATOMIC_THREAD_FENCE 2
#define BOOST_ATOMIC_SIGNAL_FENCE 2

#endif // BOOST_ATOMIC_DETAIL_CAPS_GCC_ALPHA_HPP_INCLUDED_

/* caps_gcc_alpha.hpp
5MEUgzpdYe6wsDP90wJ/n1H1r9NdCwhCUj/qURaVOdB9Wn2KsOook2x9caE3Z86obia61C1Dw7r0/asSc6i1XB+cfjzZTKFJsG2nLpmnu8vIaH0YnjILWTw3Af3+UTKk3qgYs4CBbJsbLfYWNGnlbem4nAoQ+QnG8W1xdJtV3gtDb8mj+JaWBxOZfsF3c6SDSDvyc/IH+Cb1j9G21YpYQ7OFU0CRjXhd5inNGn71SClySHHvSmo3QfVRgwtR5vawrDNlUpBha6ncDhCvRavM6YJsmsv/uMpY6Gv3yQ8qGho2ihk525vNko3p4zkqPH952psJAX4OOiHfs64hsIHpy0xBIpmZoBoeyGmh+7Dcf72Xb4QtZz12WymQRJq24+Z5+gM8YfUET3gAQiQPPIEarAQ9CINc/2U5JawUBoyCRmj3ex5nMIMj+t6Ka/TW5KQuXrZMZqQaxP+sWJCPc7zEWs1ngeC5HcM7ka2YPd32k5GlAfooWqRqvgaNB9Z5lBfrAP72eumngVWPeg5Zjwf6EdvRRvmf6bc/7hYeaY+53gkp7pgi5kbyA8p3iaOcYdS/Xod+tMxpKhjAlfwdKTW/irL1VRKj6ViEQtG442TSjqtgvJCIZfFBMZT5x6eLvqlC+QGJPz79yDbcMpqtV46CeCkenV5NhI+P10CLYH6a45kGAbC1ljnZRxoa9qat08o3hWuHVso1vnowFc2o
*/