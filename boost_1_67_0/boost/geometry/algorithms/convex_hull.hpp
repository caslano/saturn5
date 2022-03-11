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
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
*/