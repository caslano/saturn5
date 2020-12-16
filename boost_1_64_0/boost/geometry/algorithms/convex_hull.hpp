// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014, 2015.
// Modifications copyright (c) 2014-2015 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_CONVEX_HULL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_CONVEX_HULL_HPP

#include <boost/array.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/exterior_ring.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/strategies/convex_hull.hpp>
#include <boost/geometry/strategies/concepts/convex_hull_concept.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>

#include <boost/geometry/util/condition.hpp>

#include <boost/geometry/views/detail/range_type.hpp>

#include <boost/geometry/algorithms/is_empty.hpp>
#include <boost/geometry/algorithms/detail/as_range.hpp>
#include <boost/geometry/algorithms/detail/assign_box_corners.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace convex_hull
{

template <order_selector Order, closure_selector Closure>
struct hull_insert
{

    // Member template function (to avoid inconvenient declaration
    // of output-iterator-type, from hull_to_geometry)
    template <typename Geometry, typename OutputIterator, typename Strategy>
    static inline OutputIterator apply(Geometry const& geometry,
            OutputIterator out, Strategy const& strategy)
    {
        typename Strategy::state_type state;

        strategy.apply(geometry, state);
        strategy.result(state, out, Order == clockwise, Closure != open);
        return out;
    }
};

struct hull_to_geometry
{
    template <typename Geometry, typename OutputGeometry, typename Strategy>
    static inline void apply(Geometry const& geometry, OutputGeometry& out,
            Strategy const& strategy)
    {
        hull_insert
            <
                geometry::point_order<OutputGeometry>::value,
                geometry::closure<OutputGeometry>::value
            >::apply(geometry,
                range::back_inserter(
                    // Handle linestring, ring and polygon the same:
                    detail::as_range
                        <
                            typename range_type<OutputGeometry>::type
                        >(out)), strategy);
    }
};

}} // namespace detail::convex_hull
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Geometry,
    typename Tag = typename tag<Geometry>::type
>
struct convex_hull
    : detail::convex_hull::hull_to_geometry
{};

template <typename Box>
struct convex_hull<Box, box_tag>
{
    template <typename OutputGeometry, typename Strategy>
    static inline void apply(Box const& box, OutputGeometry& out,
            Strategy const& )
    {
        static bool const Close
            = geometry::closure<OutputGeometry>::value == closed;
        static bool const Reverse
            = geometry::point_order<OutputGeometry>::value == counterclockwise;

        // A hull for boxes is trivial. Any strategy is (currently) skipped.
        boost::array<typename point_type<Box>::type, 4> range;
        geometry::detail::assign_box_corners_oriented<Reverse>(box, range);
        geometry::append(out, range);
        if (BOOST_GEOMETRY_CONDITION(Close))
        {
            geometry::append(out, *boost::begin(range));
        }
    }
};



template <order_selector Order, closure_selector Closure>
struct convex_hull_insert
    : detail::convex_hull::hull_insert<Order, Closure>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_strategy {

struct convex_hull
{
    template <typename Geometry, typename OutputGeometry, typename Strategy>
    static inline void apply(Geometry const& geometry,
                             OutputGeometry& out,
                             Strategy const& strategy)
    {
        BOOST_CONCEPT_ASSERT( (geometry::concepts::ConvexHullStrategy<Strategy>) );
        dispatch::convex_hull<Geometry>::apply(geometry, out, strategy);
    }

    template <typename Geometry, typename OutputGeometry>
    static inline void apply(Geometry const& geometry,
                             OutputGeometry& out,
                             default_strategy)
    {
        typedef typename strategy_convex_hull<
            Geometry,
            typename point_type<Geometry>::type
        >::type strategy_type;

        apply(geometry, out, strategy_type());
    }
};

struct convex_hull_insert
{
    template <typename Geometry, typename OutputIterator, typename Strategy>
    static inline OutputIterator apply(Geometry const& geometry,
                                       OutputIterator& out,
                                       Strategy const& strategy)
    {
        BOOST_CONCEPT_ASSERT( (geometry::concepts::ConvexHullStrategy<Strategy>) );

        return dispatch::convex_hull_insert<
                   geometry::point_order<Geometry>::value,
                   geometry::closure<Geometry>::value
               >::apply(geometry, out, strategy);
    }

    template <typename Geometry, typename OutputIterator>
    static inline OutputIterator apply(Geometry const& geometry,
                                       OutputIterator& out,
                                       default_strategy)
    {
        typedef typename strategy_convex_hull<
            Geometry,
            typename point_type<Geometry>::type
        >::type strategy_type;

        return apply(geometry, out, strategy_type());
    }
};

} // namespace resolve_strategy


namespace resolve_variant {

template <typename Geometry>
struct convex_hull
{
    template <typename OutputGeometry, typename Strategy>
    static inline void apply(Geometry const& geometry, OutputGeometry& out, Strategy const& strategy)
    {
        concepts::check_concepts_and_equal_dimensions<
            const Geometry,
            OutputGeometry
        >();

        resolve_strategy::convex_hull::apply(geometry, out, strategy);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct convex_hull<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename OutputGeometry, typename Strategy>
    struct visitor: boost::static_visitor<void>
    {
        OutputGeometry& m_out;
        Strategy const& m_strategy;

        visitor(OutputGeometry& out, Strategy const& strategy)
        : m_out(out), m_strategy(strategy)
        {}

        template <typename Geometry>
        void operator()(Geometry const& geometry) const
        {
            convex_hull<Geometry>::apply(geometry, m_out, m_strategy);
        }
    };

    template <typename OutputGeometry, typename Strategy>
    static inline void
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry,
          OutputGeometry& out,
          Strategy const& strategy)
    {
        boost::apply_visitor(visitor<OutputGeometry, Strategy>(out, strategy), geometry);
    }
};

template <typename Geometry>
struct convex_hull_insert
{
    template <typename OutputIterator, typename Strategy>
    static inline OutputIterator apply(Geometry const& geometry, OutputIterator& out, Strategy const& strategy)
    {
        // Concept: output point type = point type of input geometry
        concepts::check<Geometry const>();
        concepts::check<typename point_type<Geometry>::type>();

        return resolve_strategy::convex_hull_insert::apply(geometry, out, strategy);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct convex_hull_insert<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename OutputIterator, typename Strategy>
    struct visitor: boost::static_visitor<OutputIterator>
    {
        OutputIterator& m_out;
        Strategy const& m_strategy;

        visitor(OutputIterator& out, Strategy const& strategy)
        : m_out(out), m_strategy(strategy)
        {}

        template <typename Geometry>
        OutputIterator operator()(Geometry const& geometry) const
        {
            return convex_hull_insert<Geometry>::apply(geometry, m_out, m_strategy);
        }
    };

    template <typename OutputIterator, typename Strategy>
    static inline OutputIterator
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry,
          OutputIterator& out,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<OutputIterator, Strategy>(out, strategy), geometry);
    }
};

} // namespace resolve_variant


template<typename Geometry, typename OutputGeometry, typename Strategy>
inline void convex_hull(Geometry const& geometry,
            OutputGeometry& out, Strategy const& strategy)
{
    if (geometry::is_empty(geometry))
    {
        // Leave output empty
        return;
    }

    resolve_variant::convex_hull<Geometry>::apply(geometry, out, strategy);
}


/*!
\brief \brief_calc{convex hull}
\ingroup convex_hull
\details \details_calc{convex_hull,convex hull}.
\tparam Geometry the input geometry type
\tparam OutputGeometry the output geometry type
\param geometry \param_geometry,  input geometry
\param hull \param_geometry \param_set{convex hull}

\qbk{[include reference/algorithms/convex_hull.qbk]}
 */
template<typename Geometry, typename OutputGeometry>
inline void convex_hull(Geometry const& geometry,
            OutputGeometry& hull)
{
    geometry::convex_hull(geometry, hull, default_strategy());
}

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace convex_hull
{


template<typename Geometry, typename OutputIterator, typename Strategy>
inline OutputIterator convex_hull_insert(Geometry const& geometry,
            OutputIterator out, Strategy const& strategy)
{
    return resolve_variant::convex_hull_insert<Geometry>
                          ::apply(geometry, out, strategy);
}


/*!
\brief Calculate the convex hull of a geometry, output-iterator version
\ingroup convex_hull
\tparam Geometry the input geometry type
\tparam OutputIterator: an output-iterator
\param geometry the geometry to calculate convex hull from
\param out an output iterator outputing points of the convex hull
\note This overloaded version outputs to an output iterator.
In this case, nothing is known about its point-type or
    about its clockwise order. Therefore, the input point-type
    and order are copied

 */
template<typename Geometry, typename OutputIterator>
inline OutputIterator convex_hull_insert(Geometry const& geometry,
            OutputIterator out)
{
    return convex_hull_insert(geometry, out, default_strategy());
}


}} // namespace detail::convex_hull
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_CONVEX_HULL_HPP

/* convex_hull.hpp
zd7M2W5MtqexRZHhfNn8eb7EepayJrmbRrDFkWEeLvy0QOpMUvbHzWoXtlQyzNGeCdOfZssgwzk/4aUwiWc2WUMo99Da+39ky1d1xvxnQCxbMdk9YM3675/IZrM55+Eb909+YQsjCwa7uvydCBkDmTfYmmn1JNaFZDG3riv3kj3/yoDObKHNpT2H9R85JJ4tobmM3WGdp752QuJJlnqrzoFkc3ybN2QLbCF7lsNeXdD3Jls4WXC92nKDyPrdeVpiVtxS9kiHNfJZeI2tlKwR2MpuZ6+wVZI1BPvwteJIthqyJmDnBxfmsVk95PrnsEfm3R8keSBzBes3o+IfNg9l9X8NP8DmRWaF9oJKT3/I5kPmAuUmT6gYw+ZLhuObv+7pjmzBZI3BLqe4DmELI8OYnYoo3MQWSeYFtvXkrH2SW7LWYM88kfc3WzpZO7AmHh//ly2fDGP9+7Dy3WxFZA1gfFv775nOdkpZz+9GFUpuVZ0e3591ldyqfp7Zt20hm6uncx6eG730jOSWzBPKHdnS+06JNVkzsEOpv7/NFkrmB/bHisfHs8WT3QHtdQs915otUdneC81Hsa0jw7GvPPBBDFuKGsPcGw9tYEslcwFr92PVCckRGc6zme8cDmTLJmsE9pjV058tD/oZSnb0Ulg/tkKo819b/tMMGV8JWWDtWcphx+NWXmKL85LzhMPGpjf7kC2JzAb2xIDtZ2UMZC3Btry2YRBbLpkb9PPxlaN82PLJXMHuOPfVPTIGsqZQ581xj74qYyDD8fV0/T2DrVyNof2aPqFsVWQNoL0bH8cfZash84dyKfuH3WQLbONcbsfKN2exBZO1hXJ9St56jC2SrB3Ys7b1iyWeZG84rDYPE05Yb7BFt3W2uPyHf5b22smZ3WEt2mQ+LPkj6wPm2usD6UsuWQjYBJ+YR2XsZH3B3kt4qkra86ZrHJjd75KfjIHMBeISfenTcrZ1ZJjbla38+rGlkvGzhMFk0x4P92LLaC91Omxnz0f6smW2l7w77P1dvyXK+MhagD3bavQ2tmJV53/GHn2JrYQsAModbntsB5utg5ul9FY/h5D1vvORk2weHWVOOCzls+wINm9lzRpdbsfm21H2LIfN3D9ZLJTMCvbXo/1+Yxuj6ty5uOswtkiyhlAu4rrfYLZZqlzp+eyBbLFkbmCtyjd8zZZA1gjq/OBI/3i2ZNXP6fe/fpotnawF2PtRnYslR6o9r/eXf8GWr8qFHAvdIzkiaw72+pNvX2WrJLOB7Xp15l1sFrtzrFfUrzeCzYsM62y2ucVLbIFkNuxLo63n2MLIsJ9N+nv/zhat6vTb/c5TEk+ypmBD076JlniSNQHr3Tpqh8RT1fn7Jycfk3iSuYPVfBE0j62QrCFY1IjoGxJPMszfaZfT7dnKVT/33/VcU7Yq1c/SeqUVEutOzuVWx0fEs9nIsNyExLIwNjtZAFiXspWT2CLJeE8eSnY+9mIDtlSyRmDv/7n4V7ZMZY0fb9ifLaeTXDcd1mmp72i2PDI3sPotEgtr7W2XQjL7rb9FMaw+/b3yaQ1GsCV1kXs8h03d0PsFtnSyhmDDD77twZZN1hhs49rXK9nylT3d/YP5bMWqTo+pX05lKyVrAuabl7KYrZLMCtZvx/MBbDVkzcD2r+rzJZutK8UT7HzRP23Y7GRY54prB6UvgWQ4hq5H919kCyXDfq561HUdW7hqb8D9LfqzRSvrfq1pd7Y4sgCMy+nvVkusu8o+6LCgYR/vY8sla479fC9lEVsRmSuUq/5qY7zkQY3vxT6rdkoe1Pj8PJOqJQ9kTcFy7okvkjyQuYP5x6x4ns3azdnG2e53Y/MiwzFc33/5uuQ=
*/