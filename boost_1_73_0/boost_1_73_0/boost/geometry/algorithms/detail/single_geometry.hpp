// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013, 2014.
// Modifications copyright (c) 2013-2014, Oracle and/or its affiliates.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_SINGLE_GEOMETRY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_SINGLE_GEOMETRY_HPP

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_base_of.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/util/range.hpp>

namespace boost { namespace geometry {

#ifndef DOXYGEN_NO_DISPATCH
namespace detail_dispatch {

// Returns single geometry by Id
// for single geometries returns the geometry itself
template <typename Geometry,
          bool IsMulti = boost::is_base_of
                            <
                                multi_tag,
                                typename geometry::tag<Geometry>::type
                            >::value
>
struct single_geometry
{
    typedef Geometry & return_type;

    template <typename Id>
    static inline return_type apply(Geometry & g, Id const& ) { return g; }
};

// for multi geometries returns one of the stored single geometries
template <typename Geometry>
struct single_geometry<Geometry, true>
{
    typedef typename boost::range_reference<Geometry>::type return_type;

    template <typename Id>
    static inline return_type apply(Geometry & g, Id const& id)
    {
        BOOST_GEOMETRY_ASSERT(id.multi_index >= 0);
        typedef typename boost::range_size<Geometry>::type size_type;
        return range::at(g, static_cast<size_type>(id.multi_index));
    }
};

} // namespace detail_dispatch
#endif // DOXYGEN_NO_DISPATCH

#ifndef DOXYGEN_NO_DETAIL
namespace detail {

template <typename Geometry>
struct single_geometry_return_type
{
    typedef typename detail_dispatch::single_geometry<Geometry>::return_type type;
};

template <typename Geometry, typename Id>
inline
typename single_geometry_return_type<Geometry>::type
single_geometry(Geometry & geometry, Id const& id)
{
    return detail_dispatch::single_geometry<Geometry>::apply(geometry, id);
}

template <typename Geometry, typename Id>
inline
typename single_geometry_return_type<Geometry const>::type
single_geometry(Geometry const& geometry, Id const& id)
{
    return detail_dispatch::single_geometry<Geometry const>::apply(geometry, id);
}

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_SINGLE_GEOMETRY_HPP

/* single_geometry.hpp
BkYWQtu5YG2dLqUq43RqvI2GWbGO+cYgXpuYURyvDc0OejZjxgdZqWlyozgE8rUO8n2Sr7L7C37QViRTKQXYkNEM84XHpFYvYoPDUNp9piLlNDjfQccWetRrDUogKWtcP7KDuQUObfaMJmbMpB5hlBmLNesTomNwjnqrD7wcNnWpPzI1DYhf0PXPbjyGa0P3P4Cf4iiWRLFPVmUHX06JhVVx7gc3pKIFhJgMPfRnehDRJVZw0grvQd5TOsNtJsUFQQBDmtS6YZ/Z8RtkIUeNinwPEYBcpdNtn0rWFbvDg++WOmlYjbLNoHg6Pjv2zg6PDwdWECwWjlMFcDn+/Wo8nQ2MM8Mygxn9KjOsQv92fvzVkXPQlD1WAU8PIUFbQMkxfWOJpIxMoN8d+r1z69XtA+LY2RitDxUZWyWcyAGeAGFNnnPmyj00Cg+OQKh6DsyK0IEKpDZwiwwLdtjk/NhRWZ0POqbvaJj6Q06BD/b2sSyiq+Bf8JJ0FyWwBZ4arpXIpYHiwb6nLbwnQpOY6Ipaq8KeK4B1TOdgAojaStq+aggUHo5MUH1x/GUmdyGhAnOsi+YX0MjBR7nN7opEGuAx1K5lSCK1V82OrAse3MIlsrGTU0lhsPKYPGalNcImugXFItJEZ4+YbJU5iAcJ
*/