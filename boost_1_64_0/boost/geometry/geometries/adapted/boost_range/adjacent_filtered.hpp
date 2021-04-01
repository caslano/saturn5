// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_ADJACENT_FILTERED_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_ADJACENT_FILTERED_HPP


#include <boost/range/adaptor/adjacent_filtered.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{

namespace traits
{

template<typename Filter, typename Geometry, bool DefaultPass>
#if BOOST_VERSION > 104500
struct tag<boost::adjacent_filtered_range<Filter, Geometry, DefaultPass> >
#else
struct tag<boost::range_detail::adjacent_filter_range<Filter, Geometry, DefaultPass> >
#endif
{
    typedef typename geometry::tag<Geometry>::type type;
};

}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_RANGE_ADJACENT_FILTERED_HPP


/* adjacent_filtered.hpp
VKaR9obByJWh0sbCPWGUBPjTsLoShc2V7To2r2OR4GHcDAgpPuRC5YgG5JCzPpD4khX/vz8z3shM3SBbkmCilfkNHCpUNsM3yxp/VltEc6VY6oacFwEKZi7yd8IyL2s5pQ1wgdqo9yFy5USiCWnTHyl8D9FAjzIoZMlWA+W5BBCHAVWbjs2DMT7KVtuUClZ1BMx9XJuVUpxhwrXuWSDmW9MndSqBDBoa8EdnI1nlO1aCOZssw9Um0eEGg3UJeYF9Se13swUhlxufEhOzbaCs5uOpiimWrAy1Lkj7A/sryBx6vfIfgeaq5kRnGlgHkpkGaTBvAUGFgl2qi/Qep7wwyXAIlksPEk2umJvy5IyvknbycxSMKUPHMaAXfjWx5IEmiMpg4L/b1qNnb5xwfvDDbUQ/kROhr3Mg9KezM6Kbw/as+6p/iMkuDBgCdtl//zEDaM8gVxYSeA0JN0yEQHyN3iJmE7nDIp/LC1X/zNSXC4wTS4SJA54a87qzzaxNbAPO6q2bHK2QG0QOzGwQ/bXqWOJ/6t33DMjVvYS4NZBegWzgfJ0ChXcRx+ZkpA==
*/