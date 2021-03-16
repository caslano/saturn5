// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_UNIQUED_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_UNIQUED_HPP


#include <boost/range/adaptor/uniqued.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{

namespace traits
{

template<typename Geometry>
#if BOOST_VERSION > 104500
struct tag<boost::uniqued_range<Geometry> >
#else
struct tag<boost::range_detail::unique_range<Geometry> >
#endif
{
    typedef typename geometry::tag<Geometry>::type type;
};

}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_UNIQUED_HPP


/* uniqued.hpp
X2aZzK5mVs6sgtlLzF5m1sBsB7MvmZ1kFmCmqhbrqlqsB7MbmN3E7HZmE5nNYFbJ7DFmTzB7ntlLzBqY7WB2klk7swS7xTQ764rZ1cxuYpbPrIJZFTMvs2pmTzF7htkuZnuYJUVZrFuUxTKYDWQ2ktloZiXMypgtZraU2fPMXmL2GrPNzPYy28/sKLNjzNAhqmTR0RbrzuwCZv2YXcZsMLMhzG5kdjOzscwmMJvOzMNsHrP7mS1l9gdmLzF7mdk=
*/