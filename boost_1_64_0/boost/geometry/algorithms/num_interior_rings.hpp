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
ZlhEhjmzMywNzGrCchi7AoYVM8wNlmjCZjOxXMb4XMqw1YzPjYxdDcO+x/i8jbG7h7F7kGF7GPYko/c8mM2Evcaw3zM+2xn2IRPn3xi704xdWCbGABPmBEszYRPAzHxOZtgMMLM45zJ6qxm7aoZtY9gOJs7bweJM2ANgNhP2OKPXxLAXGXaAYb9nWDuThk8YdprxGZFlnvZEMLPyK8hi+jOGubOY/ozRWwmWY8JuAcswYbsZ9mswhwk7CmaWnx+DpZqwkEHmabeB2UyYA8xMbyixU9fdxoCJORhdd4vwPsr1OvcGIMrsJizSeC73MPy/XmFVkK8N/SqLwhYLpiGmL/HP8+ry47lalPezEPnZI/dGaTHez0LlZ8c+1YzjwuRnFaMsxmfh8rMl2eK4CPlZukV8Fik/2xMhPrPKz966Cu/0eOVnnuebQnYWI2ZEGIv5cYE2VhunzdSWazdod2tPage1P2sWS5qlyHKR5UrLty0PWJ61/N5yyhITkhsyOWRxyOqQHSEPh7wQcjTkdEha6NhQd+iFoStDbwqtD30m9FBoR2hU2NCworDZYWvCdoQ9GvZKWHvY6bDY8OHhReHTwq8M/074beGPhe8P/0P4p+FxEXkR50UsitgacXfEUxG/jfhLRFRkcqQrcnTkmMixkeMiz4mcE3l15PbIuyN/FvmbyOORpyOTrQXWr1lnWa+03mC907rX+or1Xevn1riooVETo+ZHXR1VE3VX1JNRr0d9EPVlVGS0M3p89Kzoyuh10TdHPxz9QnRb9Kno6JjBMV+PmRezOuY7MfUxz8QcivkoJsyWaSu2zbIttV1vu8l2q+1R22O2x217bY22fbYnbD+z/cr2O9t7tk9tobGRsdmx7thLY1fG1sTWx/4y9k+x4XED4kriZsatjtsW92DcK3En40LiY+PT4kfHz4ifH786fkf8o/GvxB+K/yQ+1J5kH22fZi+3X2W/zl5nf8j+lP2g/S37EfvH9k/toQnxCakJOQmFCeMSzkmYnHB+QlnCJQnlCVckrEjYkLAl4d6EpxNaE04m/D0hLnFE4nmJixKrEm9JfCSxOfFY4r8Tk5OcSeOTZietSdqadGfSz5MOJv05SUsekDwyeXzyxcmVyTck34ntseSXk99J/nvygBRXSmlKRUp1yo0p96fsT3kr5ZOUiNTc1Amp01MrUqtT61IbUn+Zejj1lNyiBmQPOHfA5QO2DNgxYPeAlgFtAz4fkOIY67jYUeW4xXG/4wXHUcdpR9rAkoHzB64feNvAxoEHB34w8D8DU9JGpk1PW5y2Je2utKa0V9I+SPs8LSI9JX1U+rnpl6avT78l/dH0X6W/k/7ndEtGesbwDHdGWcaKjBszHsj4ZcbrGR9mhGcOzpyUWZ65IfO2zL2ZBzJPZkZkObMmZn0zqzrr9qx9Wa9nncyyDsod5B50+aDNg24f9PigNwYdHfSPQXbnKGep83znDOcFzpnOC50rnTc5b3X+1PkrZ6vziPPPzk+dXzhTs7Ozx2efl70guyr7uuybsm/Nvif7kewnsvdnt2S3Z3+UjWWYHFfO9JwrclbkbM75Yc79Oc/mHMo5nhM6OGXwuMGzB68dfOvgxsEvDz4+WMuNzx2ROyN3ee723J/kvpD7du7nuUlDXEMuGnL1kNohDw15cci7Q04PGTi0eOj5Q5cP3T60fuj+oa8PPTz0H0MjhuUOmzxs4bAtw7477PZhe7A9PezNYR8P+/uwuLxheXl5w/Py80bkFeSdl7cgrzJvXd4P857Iez7vD3kdeafzUoaPGT5p+GXD1w2/efjDw5uHHxv+r+FJ+aPyL8hfmn99/o78O/Pvy38kf2/+0/kv5h8=
*/