// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014-2020.
// Modifications copyright (c) 2014-2020, Oracle and/or its affiliates.
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

#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>

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