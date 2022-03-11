// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_NUM_INTERIOR_RINGS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_NUM_INTERIOR_RINGS_HPP

#include <cstddef>

#include <boost/range.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/core/interior_rings.hpp>

#include <boost/geometry/algorithms/detail/counting.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct num_interior_rings
    : detail::counting::other_count<0>
{};



template <typename Polygon>
struct num_interior_rings<Polygon, polygon_tag>
{
    static inline std::size_t apply(Polygon const& polygon)
    {
        return boost::size(geometry::interior_rings(polygon));
    }

};


template <typename MultiPolygon>
struct num_interior_rings<MultiPolygon, multi_polygon_tag>
    : detail::counting::multi_count
        <
            num_interior_rings
                <
                    typename boost::range_value<MultiPolygon const>::type
                >
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_variant
{

template <typename Geometry>
struct num_interior_rings
{
    static inline std::size_t apply(Geometry const& geometry)
    {
        concepts::check<Geometry const>();

        return dispatch::num_interior_rings<Geometry>::apply(geometry);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct num_interior_rings<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    struct visitor: boost::static_visitor<std::size_t>
    {
        template <typename Geometry>
        inline std::size_t operator()(Geometry const& geometry) const
        {
            return num_interior_rings<Geometry>::apply(geometry);
        }
    };

    static inline std::size_t
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry)
    {
        return boost::apply_visitor(visitor(), geometry);
    }
};

} // namespace resolve_variant


/*!
\brief \brief_calc{number of interior rings}
\ingroup num_interior_rings
\details \details_calc{num_interior_rings, number of interior rings}.
\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\return \return_calc{number of interior rings}

\qbk{[include reference/algorithms/num_interior_rings.qbk]}

\note Defined by OGC as "numInteriorRing". To be consistent with "numPoints"
    letter "s" is appended
*/
template <typename Geometry>
inline std::size_t num_interior_rings(Geometry const& geometry)
{
    return resolve_variant::num_interior_rings<Geometry>::apply(geometry);
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_NUM_INTERIOR_RINGS_HPP

/* num_interior_rings.hpp
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
*/