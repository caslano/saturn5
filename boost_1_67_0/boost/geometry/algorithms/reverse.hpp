// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_REVERSE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_REVERSE_HPP

#include <algorithm>

#include <boost/range.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/detail/interior_iterator.hpp>
#include <boost/geometry/algorithms/detail/multi_modify.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace reverse
{


struct range_reverse
{
    template <typename Range>
    static inline void apply(Range& range)
    {
        std::reverse(boost::begin(range), boost::end(range));
    }
};


struct polygon_reverse: private range_reverse
{
    template <typename Polygon>
    static inline void apply(Polygon& polygon)
    {
        range_reverse::apply(exterior_ring(polygon));

        typename interior_return_type<Polygon>::type
            rings = interior_rings(polygon);

        for (typename detail::interior_iterator<Polygon>::type
                it = boost::begin(rings); it != boost::end(rings); ++it)
        {
            range_reverse::apply(*it);
        }
    }
};


}} // namespace detail::reverse
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct reverse
{
    static inline void apply(Geometry&)
    {}
};


template <typename Ring>
struct reverse<Ring, ring_tag>
    : detail::reverse::range_reverse
{};


template <typename LineString>
struct reverse<LineString, linestring_tag>
    : detail::reverse::range_reverse
{};


template <typename Polygon>
struct reverse<Polygon, polygon_tag>
    : detail::reverse::polygon_reverse
{};


template <typename Geometry>
struct reverse<Geometry, multi_linestring_tag>
    : detail::multi_modify
        <
            Geometry,
            detail::reverse::range_reverse
        >
{};


template <typename Geometry>
struct reverse<Geometry, multi_polygon_tag>
    : detail::multi_modify
        <
            Geometry,
            detail::reverse::polygon_reverse
        >
{};



} // namespace dispatch
#endif


namespace resolve_variant
{

template <typename Geometry>
struct reverse
{
    static void apply(Geometry& geometry)
    {
        concepts::check<Geometry>();
        dispatch::reverse<Geometry>::apply(geometry);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct reverse<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    struct visitor: boost::static_visitor<void>
    {
        template <typename Geometry>
        void operator()(Geometry& geometry) const
        {
            reverse<Geometry>::apply(geometry);
        }
    };

    static inline void apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>& geometry)
    {
        boost::apply_visitor(visitor(), geometry);
    }
};

} // namespace resolve_variant


/*!
\brief Reverses the points within a geometry
\details Generic function to reverse a geometry. It resembles the std::reverse
   functionality, but it takes the geometry type into account. Only for a ring
   or for a linestring it is the same as the std::reverse.
\ingroup reverse
\tparam Geometry \tparam_geometry
\param geometry \param_geometry which will be reversed

\qbk{[include reference/algorithms/reverse.qbk]}
*/
template <typename Geometry>
inline void reverse(Geometry& geometry)
{
    resolve_variant::reverse<Geometry>::apply(geometry);
}

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_REVERSE_HPP

/* reverse.hpp
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
*/