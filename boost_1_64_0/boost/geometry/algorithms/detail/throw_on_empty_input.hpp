// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2015.
// Modifications copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_THROW_ON_EMPTY_INPUT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_THROW_ON_EMPTY_INPUT_HPP


#include <boost/geometry/core/exception.hpp>
#include <boost/geometry/algorithms/is_empty.hpp>

#include <boost/throw_exception.hpp>


// BSG 2012-02-06: we use this currently only for distance.
// For other scalar results area,length,perimeter it is commented on purpose.
// Reason is that for distance there is no other choice. distance of two
// empty geometries (or one empty) should NOT return any value.
// But for area it is no problem to be 0.
// Suppose: area(intersection(a,b)). We (probably) don't want a throw there...

// So decided that at least for Boost 1.49 this is commented for
// scalar results, except distance.

#if defined(BOOST_GEOMETRY_EMPTY_INPUT_NO_THROW)
#include <boost/core/ignore_unused.hpp>
#endif

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename Geometry>
inline void throw_on_empty_input(Geometry const& geometry)
{
#if ! defined(BOOST_GEOMETRY_EMPTY_INPUT_NO_THROW)
    if (geometry::is_empty(geometry))
    {
        BOOST_THROW_EXCEPTION(empty_input_exception());
    }
#else
    boost::ignore_unused(geometry);
#endif
}

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_THROW_ON_EMPTY_INPUT_HPP


/* throw_on_empty_input.hpp
EcvmWeqTCifrHmNFoC6uiatk8KELH69xhW+11X0a9vOnGE9kC7rexicgnt9d1x+RHIcyfWUo4KL9fLmwApgM5P/ye+ISvwKuMKBDO6nlXMWOMoXAwPSrb2CIzlYTKH9SYZnB9KJmSZhQu6ziKTCD75RqYFeTGR5ls6s7EwRy1a9bDjRipEcpGua3NLmCwl/BySEN5hbSceIuwLs5aYrQIftkt2hCd52emHQVOnvGwF3vmJ24uBiBhi0Zpkvwtgjz2IOmM3CeZ3OGYWBYDCSnNtcj9gVcacas6WqH+pHq5rcytDgPWD41dalCZY9evBzXa42cHjK4G9EQw7uB45LrdgrdjQo/S4nLQXZE4WcKhcTtVQCJKa4wBH5zO2q97PRix6EbwI97FbViK4dcbfxUla0YXcgP1wQWUbLBeeowt38UpaG73ttUIQDIgsPAU5H4GyQxKjzeHzGRELbsV8CqkrpUlwdNeVfKldU9yteMLD/qkigN9+u89pjATVCEAYY27hLfNdpWJ8JBBytKYLPmJr6GkSNtJTnvzCLo9Otwl6RluWHtFFMgOmJ5KQ==
*/