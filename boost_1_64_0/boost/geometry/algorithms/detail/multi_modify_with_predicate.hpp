// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_MODIFY_WITH_PREDICATE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_MODIFY_WITH_PREDICATE_HPP


#include <boost/range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename MultiGeometry, typename Predicate, typename Policy>
struct multi_modify_with_predicate
{
    static inline void apply(MultiGeometry& multi, Predicate const& predicate)
    {
        typedef typename boost::range_iterator<MultiGeometry>::type iterator_type;
        for (iterator_type it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            Policy::apply(*it, predicate);
        }
    }
};


} // namespace detail
#endif


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_MODIFY_WITH_PREDICATE_HPP

/* multi_modify_with_predicate.hpp
gMAelXOLkBmMgiI43j9ybIo+Oi4zOuZ8eLMLFFirbYURuyIgX5NM3SDMTMW9CzZIRuaH02m9KsHO4/rZuTuHvaxYXhNLHBg4dVegD6epvhf/QVSHOYrIgPuQcqW0S9mN1TZ88E3n7XFH+w6umbrfAy3kBUMFs1Gw7WTDy1UrYIUzVNx1u5eQNJBhchlE+bml4gtxAhZPXMHBeYNNorFpmOw6mdMpD6ia8PjkDeDg5to2jwaZ5gzc7dN0koL/97rSy7/kZkAJYA4kGCnKNVsBVTn292NH4jTo/3G//4SzCeLjCayVkY1R/lZWgOyAiZEwTQq4Ua655f9N62iCBQKNbT7LCYriC0ZdozdmwAnMYBzsIQyT5P73VsPeO6aOjrewDkyRyceLnaXh0oZyh3Vt/mjuja16KzpfMaHlc7LIx8ReL5gkx6mU96Pkeiwu8rH/pTjaGIN4UHn3TzCSvHXc68x2tvyf23iYbLTz6KTJ5paf9D8ifO7p6TuZakdwQw4KumLGpQb8fERZUZQBwiCU+C+WncmYRZklueM5253ct6s4G7IhsZYpzJQzIg==
*/