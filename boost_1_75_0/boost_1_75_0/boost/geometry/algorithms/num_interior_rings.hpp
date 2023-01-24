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
0kkfteUnF8Yaaxmabpzvl2M9eLIzvVfQWD9pNcz18Ddpf8lbrTxsDJp5WuIr2I/5KkvuLcR8BaTvk4fNrBpiQm8maCQtNFYzD74mmmbOlf69s4iv9OqYQunf+yi9s/lJOnx4srYvDqXepJe3fyAO1u/oEBaHZnFIi8OgOKwQh6/RwbyW26sDq6faGIPLaM5q6MDvcPlTWAV/isQy7f9CJ8uXKf+XZQ5hu4T63mgM8VXKB2aKT9b2ZUqfdQWd7KH2g2VTcBlMq4p3luN7t9P90AvU/VUz627kHynNxJh1r7fZekWpALJ8lWlbE+qblO32TQ3z7+jE+2dK/nPBLHxAdlsRfhGr5Tmt2wxVldJtpunx75AgkB6gk7OpXfZnhRjHva5o1J3xj5+qIvx42WGR94hv2fpnDh1N/ydxKL6GR7jRaxKrtNT7oWH1mLvYoD9qJ/zDhKsbCFdGCGeuYXNFbOGI8O+0ZEyL+K791FfzM3R4m5rP9+YjnI2lvkedbvgrOrTi+jE6bX+ODjzDfcVzzYZorqvpQOyzjPMkvkLEuLvHTsr/cjyiJcdjkB7/hRiPU+lkB7W/GZoaX6xUTrsVCyfG5VLewU+VzmMTMEBKkXHnUGFsYLG5dU78Ao+xkJst1q3cXGfQgjJi3lW+ao93qbGZDdqNgaydZpsCNo1U3hIeJLYR8olkCPBvsIvyALw/pGha1Sn1rJZa/BSJ
*/