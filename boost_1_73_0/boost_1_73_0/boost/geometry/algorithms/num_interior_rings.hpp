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
LauwaCGV7nnLRm87wGo+zNHJn/KXC3Qq0FT+EK6OkQ1h7NTNLOGiiz57XEYr4DDFBW5i0vJyFVVCZU91i8XAWZiInS+UtD9QT+2E73Aeo0unXmiXAvEQmG0d420cD3kA1/OQy1jyOul39Dxck9qTRqgdlWTFsYmZ42pOmGnjDkvCkyC08ZfZBucBH5MjIqU8wU0eXZ6+tC5sTl5+5PJN6nxgLzfQ7kZh6gUgXTQbsXNQgsHGNLdNOVK3hHSjZWUKmsu+oneTtpknzXhEeXBEmhB9G+WfQD7eKZMVnm5no2WUD4yA0K7DmESQ4IQWAkZ9lUntL59xDISF7NDDY00IAoPpPC+aGpROr0Q25J3DEr56ADsn8JPNfVr/8wO+KPhHp9PWuOFUcyhfAgGFTEcMSdoq5dshbx7W5xXDu3Un51XljsC5UCNsE6hpJIaxZktN4xn6ouZsAmPFADr5ZahIkWadIpnAsTo+M+Qvc4eCTxrPML+52DB40K2AxdWbdmGOhk3KtRJK4/YIy96a5sB0oVF0S0JGNi98F9ucpDUWD5yiEonwWkNdDRt/XM9B8iJhVOggvksyHxDrYZoxW63Rb868e6zFTgrxNseB0fFaV2wh8MtiUa24NM+Uy++Rw+IIXVomUlqrcCLTtWeg
*/