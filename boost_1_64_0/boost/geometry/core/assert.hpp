// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2001, 2002 Peter Dimov and Multi Media Ltd.
// Copyright (c) 2007, 2014 Peter Dimov
// Copyright (c) Beman Dawes 2011
// Copyright (c) 2015 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_ASSERT_HPP
#define BOOST_GEOMETRY_CORE_ASSERT_HPP

#include <boost/assert.hpp>

#undef BOOST_GEOMETRY_ASSERT
#undef BOOST_GEOMETRY_ASSERT_MSG

#if defined(BOOST_GEOMETRY_ENABLE_ASSERT_HANDLER) || ( defined(BOOST_GEOMETRY_ENABLE_ASSERT_DEBUG_HANDLER) && !defined(NDEBUG) )

#include <boost/config.hpp> // for BOOST_LIKELY
#include <boost/current_function.hpp>

namespace boost { namespace geometry
{
    void assertion_failed(char const * expr, char const * function, char const * file, long line); // user defined
    void assertion_failed_msg(char const * expr, char const * msg, char const * function, char const * file, long line); // user defined
}} // namespace boost::geometry

#define BOOST_GEOMETRY_ASSERT(expr) (BOOST_LIKELY(!!(expr))? ((void)0): ::boost::geometry::assertion_failed(#expr, BOOST_CURRENT_FUNCTION, __FILE__, __LINE__))
#define BOOST_GEOMETRY_ASSERT_MSG(expr, msg) (BOOST_LIKELY(!!(expr))? ((void)0): ::boost::geometry::assertion_failed_msg(#expr, msg, BOOST_CURRENT_FUNCTION, __FILE__, __LINE__))

#else

#define BOOST_GEOMETRY_ASSERT(expr) BOOST_ASSERT(expr)
#define BOOST_GEOMETRY_ASSERT_MSG(expr, msg) BOOST_ASSERT_MSG(expr, msg)

#endif

#endif // BOOST_GEOMETRY_CORE_EXCEPTION_HPP

/* assert.hpp
1vfZHQihDRIxXV6fAYqyJuieoeQz6Uz4kOJaHxnqBjUvqBsNWvdSt/AeRwu0R1OXJcWJ57uJ0rcTde2Yv2NNbzQ3iN7oXY8EcuSgnpd+6DndRUC2+0wKp/7YGfq7UC9NXtHz3xq6SIsCZ5Ppb9fgGkbEPqr+ChnTZgIrGTPLMsnXmNF0rz43jQloGMIBmfsQ8sLAM2gsdv5RXJs7DH5wMP10Lnr9cJ4im9ZaRuDDAWTWaJIiANx8s9gc8df2AI/SqRajbXDjYoo4gSmPsR5zx48zS58DFfGjNsS94RmQKaXgI4yuAA/PrC7hzdQ9LsMd4PI5kvhL+y0v0UNCjxjtd4E4CYQ0Jb+3urb2FLAKYyoYtxXN02xv5Ra5QileBNyRfcv/Jkx++6qyfSa8rr+cbEaLJE1ZO4d+iAZ5un+X5TcejEKDZSAnkLfmxMy8rG72xq4zCOnfdiM2nxenQgk0rh0UrCI6MnAdGXbTHjky0rb2a/ZmWAnFBFn6IvRu/9fiKe+/B51ozpA+1VmrhPTechju2jA/F/80LhH69ImHCf3vIuJ5idrOxt5VEQ==
*/