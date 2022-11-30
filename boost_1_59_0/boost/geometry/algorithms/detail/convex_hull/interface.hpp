// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014-2021.
// Modifications copyright (c) 2014-2021 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_CONVEX_HULL_INTERFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_CONVEX_HULL_INTERFACE_HPP

#include <array>

#include <boost/geometry/algorithms/detail/assign_box_corners.hpp>
#include <boost/geometry/algorithms/detail/convex_hull/graham_andrew.hpp>
#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/detail/for_each_range.hpp>
#include <boost/geometry/algorithms/detail/select_geometry_type.hpp>
#include <boost/geometry/algorithms/detail/visit.hpp>
#include <boost/geometry/algorithms/is_empty.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/geometry_types.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/visit.hpp>

#include <boost/geometry/geometries/adapted/boost_variant.hpp> // For backward compatibility
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/geometries/ring.hpp>

#include <boost/geometry/strategies/convex_hull/cartesian.hpp>
#include <boost/geometry/strategies/convex_hull/geographic.hpp>
#include <boost/geometry/strategies/convex_hull/spherical.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>

#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/range.hpp>
#include <boost/geometry/util/sequence.hpp>
#include <boost/geometry/util/type_traits.hpp>


namespace boost { namespace geometry
{

// TODO: This file is named interface.hpp but the code below is not the interface.
//       It's the implementation of the algorithm.

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace convex_hull
{

// Abstraction representing ranges/rings of a geometry
template <typename Geometry>
struct input_geometry_proxy
{
    input_geometry_proxy(Geometry const& geometry)
        : m_geometry(geometry)
    {}

    template <typename UnaryFunction>
    inline void for_each_range(UnaryFunction fun) const
    {
        geometry::detail::for_each_range(m_geometry, fun);
    }

    Geometry const& m_geometry;
};

// Abstraction representing ranges/rings of subgeometries of geometry collection
// with boxes converted to rings
template <typename Geometry, typename BoxRings>
struct input_geometry_collection_proxy
{
    input_geometry_collection_proxy(Geometry const& geometry, BoxRings const& box_rings)
        : m_geometry(geometry)
        , m_box_rings(box_rings)
    {}

    template <typename UnaryFunction>
    inline void for_each_range(UnaryFunction fun) const
    {
        detail::visit_breadth_first([&](auto const& g)
        {
            input_geometry_collection_proxy::call_for_non_boxes(g, fun);
            return true;
        }, m_geometry);

        for (auto const& r : m_box_rings)
        {
            geometry::detail::for_each_range(r, fun);
        }
    }

private:
    template <typename G, typename F, std::enable_if_t<! util::is_box<G>::value, int> = 0>
    static inline void call_for_non_boxes(G const& g, F & f)
    {
        geometry::detail::for_each_range(g, f);
    }
    template <typename G, typename F, std::enable_if_t<util::is_box<G>::value, int> = 0>
    static inline void call_for_non_boxes(G const&, F &)
    {}

    Geometry const& m_geometry;
    BoxRings const& m_box_rings;
};


// TODO: Or just implement point_type<> for GeometryCollection
//   and enforce the same point_type used in the whole sequence in check().
template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct default_strategy
{
    using type = typename strategies::convex_hull::services::default_strategy
        <
            Geometry
        >::type;
};

template <typename Geometry>
struct default_strategy<Geometry, geometry_collection_tag>
    : default_strategy<typename detail::first_geometry_type<Geometry>::type>
{};


// Utilities for output GC and DG
template <typename G1, typename G2>
struct output_polygonal_less
{
    template <typename G>
    using priority = std::integral_constant
        <
            int,
            (util::is_ring<G>::value ? 0 :
             util::is_polygon<G>::value ? 1 :
             util::is_multi_polygon<G>::value ? 2 : 3)
        >;

    static const bool value = priority<G1>::value < priority<G2>::value;
};

template <typename G1, typename G2>
struct output_linear_less
{
    template <typename G>
    using priority = std::integral_constant
        <
            int,
            (util::is_segment<G>::value ? 0 :
             util::is_linestring<G>::value ? 1 :
             util::is_multi_linestring<G>::value ? 2 : 3)
        >;

    static const bool value = priority<G1>::value < priority<G2>::value;
};

template <typename G1, typename G2>
struct output_pointlike_less
{
    template <typename G>
    using priority = std::integral_constant
        <
            int,
            (util::is_point<G>::value ? 0 :
             util::is_multi_point<G>::value ? 1 : 2)
        >;

    static const bool value = priority<G1>::value < priority<G2>::value;
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
{
    template <typename OutputGeometry, typename Strategy>
    static inline void apply(Geometry const& geometry,
                             OutputGeometry& out,
                             Strategy const& strategy)
    {
        detail::convex_hull::input_geometry_proxy<Geometry> in_proxy(geometry);        
        detail::convex_hull::graham_andrew
            <
                typename point_type<Geometry>::type
            >::apply(in_proxy, out, strategy);
    }
};


// A hull for boxes is trivial. Any strategy is (currently) skipped.
// TODO: This is not correct in spherical and geographic CS.
template <typename Box>
struct convex_hull<Box, box_tag>
{
    template <typename OutputGeometry, typename Strategy>
    static inline void apply(Box const& box,
                             OutputGeometry& out,
                             Strategy const& strategy)
    {
        static bool const Close
            = geometry::closure<OutputGeometry>::value == closed;
        static bool const Reverse
            = geometry::point_order<OutputGeometry>::value == counterclockwise;

        std::array<typename point_type<OutputGeometry>::type, 4> arr;
        // TODO: This assigns only 2d cooridnates!
        //       And it is also used in box_view<>!
        geometry::detail::assign_box_corners_oriented<Reverse>(box, arr);

        std::move(arr.begin(), arr.end(), range::back_inserter(out));
        if (BOOST_GEOMETRY_CONDITION(Close))
        {
            range::push_back(out, range::front(out));
        }
    }
};


template <typename GeometryCollection>
struct convex_hull<GeometryCollection, geometry_collection_tag>
{
    template <typename OutputGeometry, typename Strategy>
    static inline void apply(GeometryCollection const& geometry,
                             OutputGeometry& out,
                             Strategy const& strategy)
    {
        // Assuming that single point_type is used by the GeometryCollection
        using subgeometry_type = typename detail::first_geometry_type<GeometryCollection>::type;
        using point_type = typename geometry::point_type<subgeometry_type>::type;
        using ring_type = model::ring<point_type, true, false>;

        // Calculate box rings once
        std::vector<ring_type> box_rings;
        detail::visit_breadth_first([&](auto const& g)
        {
            convex_hull::add_ring_for_box(box_rings, g, strategy);
            return true;
        }, geometry);

        detail::convex_hull::input_geometry_collection_proxy
            <
                GeometryCollection, std::vector<ring_type>
            > in_proxy(geometry, box_rings);

        detail::convex_hull::graham_andrew
            <
                point_type
            >::apply(in_proxy, out, strategy);
    }

private:
    template
    <
        typename Ring, typename SubGeometry, typename Strategy,
        std::enable_if_t<util::is_box<SubGeometry>::value, int> = 0
    >
    static inline void add_ring_for_box(std::vector<Ring> & rings, SubGeometry const& box,
                                        Strategy const& strategy)
    {
        Ring ring;
        convex_hull<SubGeometry>::apply(box, ring, strategy);
        rings.push_back(std::move(ring));
    }
    template
    <
        typename Ring, typename SubGeometry, typename Strategy,
        std::enable_if_t<! util::is_box<SubGeometry>::value, int> = 0
    >
    static inline void add_ring_for_box(std::vector<Ring> & , SubGeometry const& ,
                                        Strategy const& )
    {}
};


template <typename OutputGeometry, typename Tag = typename tag<OutputGeometry>::type>
struct convex_hull_out
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE("This OutputGeometry is not supported.", OutputGeometry, Tag);
};

template <typename OutputGeometry>
struct convex_hull_out<OutputGeometry, ring_tag>
{
    template <typename Geometry, typename Strategies>
    static inline void apply(Geometry const& geometry,
                             OutputGeometry& out,
                             Strategies const& strategies)
    {
        dispatch::convex_hull<Geometry>::apply(geometry, out, strategies);
    }
};

template <typename OutputGeometry>
struct convex_hull_out<OutputGeometry, polygon_tag>
{
    template <typename Geometry, typename Strategies>
    static inline void apply(Geometry const& geometry,
                             OutputGeometry& out,
                             Strategies const& strategies)
    {
        auto&& ring = exterior_ring(out);
        dispatch::convex_hull<Geometry>::apply(geometry, ring, strategies);
    }
};

template <typename OutputGeometry>
struct convex_hull_out<OutputGeometry, multi_polygon_tag>
{
    template <typename Geometry, typename Strategies>
    static inline void apply(Geometry const& geometry,
                             OutputGeometry& out,
                             Strategies const& strategies)
    {
        typename boost::range_value<OutputGeometry>::type polygon;
        auto&& ring = exterior_ring(polygon);
        dispatch::convex_hull<Geometry>::apply(geometry, ring, strategies);
        // Empty input is checked so the output shouldn't be empty
        range::push_back(out, std::move(polygon));
    }
};

template <typename OutputGeometry>
struct convex_hull_out<OutputGeometry, geometry_collection_tag>
{
    using polygonal_t = typename util::sequence_min_element
        <
            typename traits::geometry_types<OutputGeometry>::type,
            detail::convex_hull::output_polygonal_less
        >::type;
    using linear_t = typename util::sequence_min_element
        <
            typename traits::geometry_types<OutputGeometry>::type,
            detail::convex_hull::output_linear_less
        >::type;
    using pointlike_t = typename util::sequence_min_element
        <
            typename traits::geometry_types<OutputGeometry>::type,
            detail::convex_hull::output_pointlike_less
        >::type;

    // select_element may define different kind of geometry than the one that is desired
    BOOST_GEOMETRY_STATIC_ASSERT(util::is_polygonal<polygonal_t>::value,
        "It must be possible to store polygonal geometry in OutputGeometry.", polygonal_t);
    BOOST_GEOMETRY_STATIC_ASSERT(util::is_linear<linear_t>::value,
        "It must be possible to store linear geometry in OutputGeometry.", linear_t);
    BOOST_GEOMETRY_STATIC_ASSERT(util::is_pointlike<pointlike_t>::value,
        "It must be possible to store pointlike geometry in OutputGeometry.", pointlike_t);

    template <typename Geometry, typename Strategies>
    static inline void apply(Geometry const& geometry,
                             OutputGeometry& out,
                             Strategies const& strategies)
    {
        polygonal_t polygonal;
        convex_hull_out<polygonal_t>::apply(geometry, polygonal, strategies);
        // Empty input is checked so the output shouldn't be empty
        auto&& out_ring = ring(polygonal);

        if (boost::size(out_ring) == detail::minimum_ring_size<polygonal_t>::value)
        {
            using detail::equals::equals_point_point;
            if (equals_point_point(range::front(out_ring), range::at(out_ring, 1), strategies))
            {
                pointlike_t pointlike;
                move_to_pointlike(out_ring, pointlike);
                move_to_out(pointlike, out);
                return;
            }
            if (equals_point_point(range::front(out_ring), range::at(out_ring, 2), strategies))
            {
                linear_t linear;
                move_to_linear(out_ring, linear);
                move_to_out(linear, out);
                return;
            }
        }

        move_to_out(polygonal, out);
    }

private:
    template <typename Polygonal, util::enable_if_ring_t<Polygonal, int> = 0>
    static decltype(auto) ring(Polygonal const& polygonal)
    {
        return polygonal;
    }
    template <typename Polygonal, util::enable_if_polygon_t<Polygonal, int> = 0>
    static decltype(auto) ring(Polygonal const& polygonal)
    {
        return exterior_ring(polygonal);
    }
    template <typename Polygonal, util::enable_if_multi_polygon_t<Polygonal, int> = 0>
    static decltype(auto) ring(Polygonal const& polygonal)
    {
        return exterior_ring(range::front(polygonal));
    }

    template <typename Range, typename Linear, util::enable_if_segment_t<Linear, int> = 0>
    static void move_to_linear(Range & out_range, Linear & seg)
    {
        detail::assign_point_to_index<0>(range::front(out_range), seg);
        detail::assign_point_to_index<1>(range::at(out_range, 1), seg);
    }
    template <typename Range, typename Linear, util::enable_if_linestring_t<Linear, int> = 0>
    static void move_to_linear(Range & out_range, Linear & ls)
    {
        std::move(boost::begin(out_range), boost::begin(out_range) + 2, range::back_inserter(ls));
    }
    template <typename Range, typename Linear, util::enable_if_multi_linestring_t<Linear, int> = 0>
    static void move_to_linear(Range & out_range, Linear & mls)
    {
        typename boost::range_value<Linear>::type ls;
        std::move(boost::begin(out_range), boost::begin(out_range) + 2, range::back_inserter(ls));
        range::push_back(mls, std::move(ls));
    }

    template <typename Range, typename PointLike, util::enable_if_point_t<PointLike, int> = 0>
    static void move_to_pointlike(Range & out_range, PointLike & pt)
    {
        pt = range::front(out_range);
    }
    template <typename Range, typename PointLike, util::enable_if_multi_point_t<PointLike, int> = 0>
    static void move_to_pointlike(Range & out_range, PointLike & mpt)
    {
        range::push_back(mpt, std::move(range::front(out_range)));
    }

    template
    <
        typename Geometry, typename OutputGeometry_,
        util::enable_if_geometry_collection_t<OutputGeometry_, int> = 0
    >
    static void move_to_out(Geometry & g, OutputGeometry_ & out)
    {
        range::emplace_back(out, std::move(g));
    }
    template
    <
        typename Geometry, typename OutputGeometry_,
        util::enable_if_dynamic_geometry_t<OutputGeometry_, int> = 0
    >
    static void move_to_out(Geometry & g, OutputGeometry_ & out)
    {
        out = std::move(g);
    }
};

template <typename OutputGeometry>
struct convex_hull_out<OutputGeometry, dynamic_geometry_tag>
    : convex_hull_out<OutputGeometry, geometry_collection_tag>
{};


// For backward compatibility
template <typename OutputGeometry>
struct convex_hull_out<OutputGeometry, linestring_tag>
    : convex_hull_out<OutputGeometry, ring_tag>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_strategy {

template <typename Strategies>
struct convex_hull
{
    template <typename Geometry, typename OutputGeometry>
    static inline void apply(Geometry const& geometry,
                             OutputGeometry& out,
                             Strategies const& strategies)
    {
        dispatch::convex_hull_out<OutputGeometry>::apply(geometry, out, strategies);
    }
};

template <>
struct convex_hull<default_strategy>
{
    template <typename Geometry, typename OutputGeometry>
    static inline void apply(Geometry const& geometry,
                             OutputGeometry& out,
                             default_strategy const&)
    {
        using strategy_type = typename detail::convex_hull::default_strategy
            <
                Geometry
            >::type;

        dispatch::convex_hull_out<OutputGeometry>::apply(geometry, out, strategy_type());
    }
};


} // namespace resolve_strategy


namespace resolve_dynamic {

template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct convex_hull
{
    template <typename OutputGeometry, typename Strategy>
    static inline void apply(Geometry const& geometry,
                             OutputGeometry& out,
                             Strategy const& strategy)
    {
        concepts::check_concepts_and_equal_dimensions<
            const Geometry,
            OutputGeometry
        >();

        resolve_strategy::convex_hull<Strategy>::apply(geometry, out, strategy);
    }
};

template <typename Geometry>
struct convex_hull<Geometry, dynamic_geometry_tag>
{
    template <typename OutputGeometry, typename Strategy>
    static inline void apply(Geometry const& geometry,
                             OutputGeometry& out,
                             Strategy const& strategy)
    {
        traits::visit<Geometry>::apply([&](auto const& g)
        {
            convex_hull<util::remove_cref_t<decltype(g)>>::apply(g, out, strategy);
        }, geometry);
    }
};


} // namespace resolve_dynamic


/*!
\brief \brief_calc{convex hull} \brief_strategy
\ingroup convex_hull
\details \details_calc{convex_hull,convex hull} \brief_strategy.
\tparam Geometry the input geometry type
\tparam OutputGeometry the output geometry type
\tparam Strategy the strategy type
\param geometry \param_geometry,  input geometry
\param out \param_geometry \param_set{convex hull}
\param strategy \param_strategy{area}

\qbk{distinguish,with strategy}

\qbk{[include reference/algorithms/convex_hull.qbk]}
 */
template<typename Geometry, typename OutputGeometry, typename Strategy>
inline void convex_hull(Geometry const& geometry, OutputGeometry& out, Strategy const& strategy)
{
    if (geometry::is_empty(geometry))
    {
        // Leave output empty
        return;
    }

    resolve_dynamic::convex_hull<Geometry>::apply(geometry, out, strategy);
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
inline void convex_hull(Geometry const& geometry, OutputGeometry& hull)
{
    geometry::convex_hull(geometry, hull, default_strategy());
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_CONVEX_HULL_INTERFACE_HPP

/* interface.hpp
r5Kmcbltaaaa33LnlccRoSuYrr5oyxyOQHKYYYyRmrE+mTw5GdY6AbY3Exqfs7MSPvJPF4DRIe0qtJMkvw2EH6sMai1rkaxxnhNO/Kip2/G1J6tC+5gRRxneoOGwXNXlqIqq6yLdmkyXPvs10MpIGgqwaDLp3RS7oPXAXGHqDDztecVmKL2l5yXSQu2WVNd9nt4M8OqX1KRF37tj7Pf1ctqD3W7HuyNeSaN0Q3aZUdpDcmu2n5/nqeOOst+S2tVp5V0/00r1dyrpp9QSkm7vM5UUxOiOnNJx2dHd4v0rO5wev3rNTye0KrXOfksdvE5Njluo6sXKlnAkThSDEg38pnR+0PyETWmJoTMR+2IgI1dyVgV8sx2ApmXVhR+PRDgyKlpLIqhAmUYyEIGZILXHuChByLwmk6YUWldqe7y1EDpsaKrTIKPkYqTtXxGSzn+XTSTQip/pQZPjbI+hE51CJj2FNLk2p9ApX3+S316yUPzyKGT1b5Cav7/pR/YaCyW7Fa0nbEamNtZjiY9lxCW52fbtnAAStEeBOFJ8eVK0EO6bkskNbFKSpxnwnfQf0LOGJpdtAEOLYkfFINs2Q2kv54La3HzcxSAZEDeMmve9LIZfLMEbD+CIFF7pf5gtI/rYMVNfewrrcRlrK9GY41jNk/4u5oow69t0tof4WiBPHuSKVOlrR7vi6kixbipfDRz0pYfu42nbfS+ZIiYixJffHJNIbjmIVaugj/hvYxWxdoY0i67fXTrZjo4eP4VzNnmwjQI+vPcM6IByzQgHEHb0b+lENLt/UQv+NGU+Mu8inTvYQQ5PtYnPg31bQ16YMXFheGbKw+QKkAvLMUeRcQGZwVQt7IVrtPRkQnojo+GGiDJR8pYWZpON96XZ6pDYGgs2hEc+42MFnXvsXKz98TVwYaI6gZjVGYPxIVYKT5EXBWa1RcpB4avbm1W9C3tWqvLwoSfawaC71s7VKUuGDG24nA6BG0uNp0r4VwyOiF7lql0uY/D9tafQCP0OeNlYKhMhmfgN7HB6i58oglnz7sovb0RBPgHe7KMqYN6UOD/urRgsNUz4VPRvl/RUyIcrsW7OxTkZTqcbc9gKmxJo3M0J01buJkbwnSoJZYObrzXvCyWYJw8FP8qfQfDEqENEgOoLDRkbNCS4mdgLy0Dgr3OWEAdancjwtOWXbSDkw7BkPfS3KaKZKVJGo3uYrCQbMUYhdZPWY9gX9VWF4l8GSKHUeF46qmGgL//OTAXi0ZmGQirwwWHW1QMY85r0i+lXI9LmpTisrfLMs1cwLtG0WF/6mfZvHpdLbIykbhp0t9CsiBKEwTGCuWdvsOiQZpSvcM+C3MJvgAVBTMO7WGOCBJpNnYJbNMpMSDVMZ7QfzcCHZiiRK8wbfnwdXOXbXNnTk1qY9LnKMixLLcAUmpDqCf/8gDnnfjRWx746zUQ7NNTQQmcGLry9MaLMlWwOYpaCcm4MhDDY8l5wg29nbjcwvP5YPnFTylqcQpNKVh2xrg7dHhDho9Hbf+czGBmGEpATFhQQN5gDcwqQ5ww/2Y93DoZTfbS9Q63zPG2Nohls4ojExqufWif6BKBfQQhxNUQrSkaQb3wjUhAQ3IK9gKAJ6PkOca1yZcdcMrrUVkMf1b1NbBktRW87Al8KHd0E6pU+1GVQT95XWcYr/mp4W4dgbAjS+jLujCt5WmZXDrpUlJwJlmrkyZAnZCozFgAFLPrTivmSYSm6BrjyFbZwj84diazdVQNOVm6JCMTE+YyNV+3V/Q1AFEaqQJuyWVSJBWVuIAij0dzbHTFdBLQnR2wLDc3Cbjq9nF1JrPpvDydW0bHwJjq65qHcjzEs/THqevpnGIP3UCtod3zr2ScxDmL564eK3ZSwpBvSFPOXAFvY2PWQrVOH6Wb3upNs3aF910wgtE8599rHTFyS0dKGRd2Qt09n+qr68NvETeDIJY7t/SN6xDClbAiBkmw0xngYJtOOsxDnGhWItcktySzPW7HMjkTUAP6gzXQfKaiA4pLNi8DO28GtMs5SJMYvU0JZftAh5aJaOmsHrTDGBkeYjXFAS153PQJPHKzpunV8if/Ma3rJze2ba51Ow0ONYF8/LaJ0yxfZ5ypJtFv4The4+8fZv6jzSk0JOOlEXkhCPBcUvnxOJUY7sZ2FleA+lsK7CYJpYuFu9vQDzZVtrAvKTgF82mAXUZoEWgt0yb3kCnIhK5la/U7D+e3UpTS5b3eLe6LUaAOxm738f9BosekP8ykzq1G6kqPVAdTDtRbZfUBok92GIqTBwhVW3wm2OrQtwx3B0KnwiaE+dj0FEzdC/bGMZ7DQyRNbxPfTU79FFWOBbgfp6f2jNguti97GmMtZHH/qbIzCS2QeVuyfSAcR/8k+IQPSGjCc1ls9frHLhtQx7P5AdSjCa34Ja0k1cp63pP1jRfkWDnTIysxxrIsb/REIxnfJZq/bjUizq5nu/hbJdvY3iXpCOczh8lGtwLRvnqQGyXvdxw+Xi+6HIXgoRfC/uyFGGYEtzu0aOno+XSIzJHSXe2j5qaocMyFlsS0MQ9nxVSgWw1H5mOhuAeWc5e0AkZ+OoS9aRLSkzW8ptfgnGNWEk5fOXvDCPOoaQN6GMCFxyshIDxR6whRt+/J2oMR1kpxfYormun+jp12C3MEKvHMWK1dZJeLD2lhOre8Zy6rvgsm15zbNySBn5bAYJ09C9Y/Y849X3Gc6kTdTnd3ADIm7sjZHGh9L5HMPC1Qt4RhD5J0lsu/Nfp5+H9IbvG6rJLFzrI2YALr2zDHmOkol9HHgB9HymYgLJgdU1Gn9oAfXwNrzqbZxtafmk+N322wdE3isXDe9BTsA3Ok6YVA+gmyJNrrFCkFmj6h3cO86Dxd7Jat9rXZNguLO/Yc96F1hYIV90iqMu3OzVX2RjA4L9ZtaVTC3adjdD/zb7A+ziGWclS+KCutCWIUlBCgUyJa9EnGDeh3Uj7MvDMA3fyBq1sDuwLIwd/9l7oJAxnbnXFEhphscQc0bl0FhMh1RB1l9ybNGv/QeprWnbS/vIrdMsEpla9bWbX2njiUyY188fTdDiAt3K/ETKb3BB0KG2qna7Ud1j27KjUJV9CU4ECZfWuQYQ+X3ck191blICur6hVd30TmXRCwgv/LNB3EYHW/1GVwfbh5NiE79Hb1edH+Y/DSGgXJfyNZs46B1/AeAs745KkaAmOODRVvJsCg3zcvpWgZiEB1O7anfc2eF0KHMUzywmjsJXX3Nd7ZpCeyLyehyNkccRh2D/vVX2Azl+AGDIP/SvUg9OTlE2QTGXEL3/XsCNUxVWmSvXdufF+0UkbZBY2olcXswKRBu+8JOaJcBqrgSoXGhAiSWKVTqpuTGOZcbqMc3Abp3Y+efD8AKYNWs1dklCz7XVlrJYq1lB2HX9je91mIJGgs0y3Gcu8yC19jCCk1RhtgWw0V5Biioxkh5A/+WTp3u90mQ/UuUNR4uPysNyMjffox2iyO5RkBWB6SjIoOuBJiBPJUoYIJPg4mglCC0cGMuUxW0BDQKS0hnd3xjB2pnL/gVPVpI+lHBSFajaIyfX5PDCT+qW0IZjQI1s450IB1oBITgegNKC/xUdZ7yWS9G8PFA+EDEzj69HQrDTIMDxB+pUGZK4ErvupQrCzcEt4oHTjR1LlEpv7++ZCGVfHeFyCpEYoRaG8QMYS5WaOkOjYmxN4rigC0ljcm5RCcGIrfAJvZjdTwbpshCeYjUtsqAQhw3BLPqffQljwm+9wojutnn/8PFT/BcFjhXUSrn5vYEDmzMni9YExNXjWiabYuWFZX2BROA9ro1XTl+FdYNMfOJXDMuqkPklmRjjsoyJsU9p7dPBwiJ26/PxB9tPyusLVv9R1ofob7XLYdlm4igiwbj+BjC3E0T8fnopBrxvM5ho8OV3UwnE3NoM4aGhfUzeWo1ZrFmrxcrhBp06pnanXHqWv3HXsdGMuhffhkVrPgdRGuM1FPpLWu7cxjxn80p8CR5edwD+YNmH5C8z3Wqzk8HzXl+ubpG9CcmRyvFFd7IKUW5if1/rwKM9HdDCQhItNpTXtna/X6Usc+aMXPG0NHvqdGx0cYrUMESkfuXwKdcMkX5VjLybGPZOFFMlrAC90+cG6sxClFKn6yUC51Bf3rOpf8MsZrk9OtlFzL1ZBme4ir39DAQOLOBC/GU2P7pAi5fG8WRf770xbhzdvmnA4NeySeVe/qYqRRivZzjUwtQJJBCIEcM/tQw71p1R93uM9LFe/CFSyW5Sb04m/OYgEnEScgBeoE+e2+Nkmqqi4nEONSv+nxcwDYWUI9ccJUUxolIFEXDrk3MYDFpsJAtii69cX5bvIxh0Pg2k+mA1G10l74MmYE2hIFKLlB7fen0ZHllvYT+cDpxVkUDDRb04pPHKRNLZTQ9fVy6T31cKpIGWGPDa4HzwFdMryDIeEVln11nK3SS9UIgM6FmHaXyxmuDlGOELpmS2fQpJzG+0OGhivs7QePxNoKw0ZCx5J/so7LWG1CWxMl7gpZsUvhEL3hRbMucucRVxF+XPFpKQpNcAEryy57BPn6TSfKLWuCX4HeGm8KIQpZF7EaBetmTN2EV7fcMrarEIQdLX8EOqbxG/gDoVqj5rE95jO8xrxjH0yf+GV7SPi1nVPUb6jYjPvUKRjmzE/OuP8SsKr7uZ7zn3dVWWOblEP7mIlWLlw9L5BDovcK+hIqtS375x/H8qPgOUfJBsQ1m4QIfC8/liu8jNXcQljx0d9dFKXF58mkn3yfsgOXEjnDytvsvciRqs/tuVD7GKEigajsczUZUWT1HAXyZzAhUlthTr4C9En5hPzQldx3NutE7rxaersyOof5i982NXkeBV9HjqOedIlyFcSDkJ29eFmBBTKzJyaYojAtQIL+KEHAyuhps2YFYdnc3Haf3xC0aHUdUrMpb6ZG2Lno1vqYBwH/8Kwdw4l0PvVuDhN8J22HmsIv6YK4HiFO0diqT5E2v5SQGriAm7w9YtvkooB2Sll2Z+2GEP5vmZ9YpafJxEaXTBOmhzY/1MQmlu5mEhIV+Eq6P092llbyoKgA/POQxk+8gOQeZhGYIxoKZeMi+Dp8P0+8LtkpMCUfXkM2gzXVokcUKnKyoyx9E8TT+m0lEBu1EM2yNr09340W7x2kwLJfDXJS/aT8SaFOokS+yK8aS2FD5mF0O5yOR1YLQmiWFEeuFvwaUNOCoHP72EZabEC0xRQBeIrNsTasGZLTyM2LlUTHgEW0w8ed62hnIBoY7yeehcwRgJeHauI5yZXTKFWEJ5QgeQSjqfq3uwBuXijG5woJu4oLQAh8DXzp9rKsCMz4zUUzy1r518fuzzhT/7xvc2JxGXv0YyTT+wjvRu6ZvpNyzLH8QJ58C2iRNtTp854eRA9eUsK1+gvupsi4/xZKCzLNTADRlgOpKx88rAyNHS/0lhEJt2QMyAD0arGf0yS+gNpVvjWkKSsicbLLo88YaxkFY0O3lso9MgjidIVW4OWOvyWe/6WL+Ly0g/9Z9tq4Tm8Qf0JbOUh9A97/8Whqe1iZPtL0ga9YcqAqsptmYHSN22PP/aMcXxkQzGPEUAmZO/1TVbl0JWxUf2oqhLFhNbMuW37/XoPieVEOi5w2dhIDx+0n7XqIpG6b5xZLpwW87Yi4WfWnTjw4Ofhg1ogyI6FjKBfycHvCjfm+C7M59Xm+PH7tBy5CKXxcHG+F5MBf91f4IrlC0sEBZiAT5cf/hOkCx4+lG+4QuXIeuGVccUrF8aiesVZz/V8rsxrw3t1pvJoH2eqgaLS3gwVPPJwOlq5fblRHFzhYWb3bvLtb3KvcvB8rV2KOPhdghHMwF2FadnSYdlOAPeOOyL895ZvmruigHjMQODcEfZsA21uzBqkIku7i1i0DSeMwri330I1Ax5LcJM0EnIZWO8Xc4FXPbWcnkT+EJ8XsbDkQdfPKQmdtSEtjXLAXxPdwj8kg43E4cBdBt/3cJLSqXhdv3kGm2q6DxDmFJ99ECzjGDLbmPxsSSb7/R7fhmPLacjlxXUaNYeU7ZgZhTGbqAGR4e9HHgOvqupiU/BDQD/BlkKyUss3jLaVHke0i2jLkKERdIKQqTsJQr5+c2lgvQt0dcDNlgHJ6/3DO6NtfmAr+ZgqKUehnMZbbenItESESQ1vGsN/AFT8uUapbvJDTGwtGbRm5axya+xr+BjXNB3lYIUYmQOveDXYP053KVn/eMOfEhL6/wt12io6hvN74uJjU7TY4ezKJDvfhyS18CFDHAU0zQDOM/DtVMK831HaH+FqtJqyD3u5n1Dg3vh0jbohdJbkOo1jQLuGNRSQAJPGDJyREw0MuQzAgiIbravbQx4akyz6suhBmn0MeItrzzDY6cNbWoIdP3HD/EYBJsd/R20PDA759Cqm6RIAwCKbzfmkQl+7yJ1ObQn7VBxoyOgX0rBB5JExeabfHJPUdQG/VpwB0z/FLg0R7539nsuXUG5Wq0W90n6qIM0kSrkioSiKuSxCiTxGirNfhBX55DAMWCWVF6l5B257xFLTJfnHPzmZkeZl3NdwoskYwJrNH1WZIWs01EYMgHSPie2/fFqKKKJhBkFVYIw0Zt94BJlQPhvdEtbhjmcn8138zwyUfSB5OTCUr8yx0eJPN13waSNozRsL9owdDptaW4poX2IVMEQtzNhXYHdHtD+R6PD9Ewug80ahK6jhyQpr158j5JOgYPqt7HvKg2/FOIF6YVc5W1RcWpQ8kVLtWM/xWp6imkiU0OSjZ5bSDrBtSeqGIcajlRR1td2qrq6zflQpMhT7XeVrL6l1czr1Tt9E07KWOoPZm80JCHyC4wCUH/BaWUDJGoqL/ddZNLSI5EkWGfNrLme47Sxd/1Ib7sgw5PnmnKvTEE11scj1pqIfuuTyZKsCjy+PJDgka/di/qMOhqp4vfZTYysnd0lbLAUzwLEh3ChoKpVdz5XKVE0jIKNnlVFuqBjqmCA6X2oFyCeOGaul3w+chdu1CKAp+g9ju0ufNwxgNWYAAHnCnI5V+JbAjFR1suVED8QVSWMhUew9BzEaFQTw7j10mFyVuBEd/5GeVvdxAXMAC5BH/dpa86b9M4NafpD6X+mbK6ggwm2vV4IDnD7462PZ9rInYzk44cMwt+F/+5cnRWFmmZKFadp5yCyhFVnoxp/BJ62vxW2Iv71+wCoVFdG8Mb++IxpB1EXkQevMVVhUnQS0eP40p4vY7M12vnOVa5N1gKwqTvryGm6m6a79AnUhgvXsnew2twwcXy1Valiw2WUlr/chryMdP39/PnvYbFYLT+EUyxLDJntJa7T+ao4W34PBxH5TS+d09l+Tl4kRVgwxMIlum+AUuVxJKreFONbB9WSWQW/EwDUu77W0SF9AbwWuDAKd2gdgCCJIbeUJN+oU7/d8iXk3cqB+ttCu6tzokDo34lhzYKK+9s9aafb0vOrp6eSeIo5Dzgg9G83mOlH5I+1xcixkoiE9SLBi7lCLgR9M2Z6MOu/eGZrKsV1ClCb9HbPF112qiLuZWaguo7IzrH2Vu6fcwLRY15N3h/VfBSL3ETmZbve4Po6BZlD/yB/pyMkYd8dzoc/fCPj3eGROln6OfeYUb8B869j7Sn7rFdZLHg
*/