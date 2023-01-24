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
l7jikwtuhVfVra33BkjWW4guSOVXqHO9JjYts6V3HTXcRhG1yt/0ByInjNJpUjPIjTw8aFgYiD3BDyJ8UzSeOAlGRDwJF4BY2zN8UyzmfuvD1xd3j1yIRxpBllfFTpMR9/HFEHdESOJA+OiEZU/mOqIL211YzH1+ItNX0nznB0m5hLXH/EdYPvl9MzOeNqFEdMlT0n4fT2VDlRSgHHQNAceqcx4ZGdHQMhDwXKuLg9l7eaHoUM9Rx5P18sae94dF75bvvfgY9ytKfeMB+ac0rsER1JHW48ceGMe10PA1LZYM1KdUsqMXnhMagn1ez2a9InQ9VU1MLPOxBCz/KP80xxxNeg4Jo4/y9fP/GL/ALSh7hEDZ1Tnz8sUhEuvDSfkqP6iyzJHpwbjbI49IE+zJODrRvUf57N000af3h5DKqxLX0WcUawO9v2alhv5c2OCYzHFhr0wh6hivsRxB6iGgonTSFuWx/AU2QAQCgV5/5aRP1rLL9WaFgHrAYv7HUtf9Lrjaez285fYBAHxYwebELj/R+8tAWu4IHDmte14skYmRanPFR6JVx8/vK+3IzqrwQ9cKxFvcBdgRCJJ6Q4OgVFmioOfrp75UufL3h+rYjpxPhgJEku/aFo9Xg8j5TgDPB69fr9/klQeDgS/6IgLL8vkDNPi7e8PlLqJAtQd5MtdQbVD3dLRACxv/HVLUoswPjn/kmRbfe41R3l5s
*/