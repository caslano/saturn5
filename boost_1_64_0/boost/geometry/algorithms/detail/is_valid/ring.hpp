// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Copyright (c) 2014-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_RING_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_RING_HPP

#include <deque>

#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/order_as_direction.hpp>
#include <boost/geometry/util/range.hpp>

#include <boost/geometry/views/closeable_view.hpp>

#include <boost/geometry/algorithms/area.hpp>
#include <boost/geometry/algorithms/intersects.hpp>
#include <boost/geometry/algorithms/validity_failure_type.hpp>
#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/detail/num_distinct_consecutive_points.hpp>
#include <boost/geometry/algorithms/detail/is_valid/has_duplicates.hpp>
#include <boost/geometry/algorithms/detail/is_valid/has_invalid_coordinate.hpp>
#include <boost/geometry/algorithms/detail/is_valid/has_spikes.hpp>
#include <boost/geometry/algorithms/detail/is_valid/has_valid_self_turns.hpp>
#include <boost/geometry/algorithms/dispatch/is_valid.hpp>

#include <boost/geometry/strategies/area.hpp>

#ifdef BOOST_GEOMETRY_TEST_DEBUG
#include <boost/geometry/io/dsv/write.hpp>
#endif

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_valid
{


// struct to check whether a ring is topologically closed
template <typename Ring, closure_selector Closure /* open */>
struct is_topologically_closed
{
    template <typename VisitPolicy, typename EqPPStrategy>
    static inline bool apply(Ring const&, VisitPolicy& visitor, EqPPStrategy const&)
    {
        boost::ignore_unused(visitor);

        return visitor.template apply<no_failure>();
    }
};

template <typename Ring>
struct is_topologically_closed<Ring, closed>
{
    template <typename VisitPolicy, typename EqPPStrategy>
    static inline bool apply(Ring const& ring, VisitPolicy& visitor, EqPPStrategy const&)
    {
        boost::ignore_unused(visitor);

        if (geometry::detail::equals::equals_point_point(range::front(ring),
                                                         range::back(ring),
                                                         EqPPStrategy()))
        {
            return visitor.template apply<no_failure>();
        }
        else
        {
            return visitor.template apply<failure_not_closed>();
        }
    }
};



template <typename ResultType, bool IsInteriorRing /* false */>
struct ring_area_predicate
{
    typedef std::greater<ResultType> type;
};

template <typename ResultType>
struct ring_area_predicate<ResultType, true>
{
    typedef std::less<ResultType> type;
};



template <typename Ring, bool IsInteriorRing>
struct is_properly_oriented
{
    template <typename VisitPolicy, typename Strategy>
    static inline bool apply(Ring const& ring, VisitPolicy& visitor,
                             Strategy const& strategy)
    {
        boost::ignore_unused(visitor);

        typedef detail::area::ring_area
            <
                order_as_direction<geometry::point_order<Ring>::value>::value,
                geometry::closure<Ring>::value
            > ring_area_type;

        typedef typename Strategy::template area_strategy
            <
                Ring
            >::type::template result_type<Ring>::type area_result_type;

        typename ring_area_predicate
            <
                area_result_type, IsInteriorRing
            >::type predicate;

        // Check area
        area_result_type const zero = 0;
        area_result_type const area
            = ring_area_type::apply(ring,
                                    strategy.template get_area_strategy<Ring>());
        if (predicate(area, zero))
        {
            return visitor.template apply<no_failure>();
        }
        else
        {
            return visitor.template apply<failure_wrong_orientation>();
        }
    }
};



template
<
    typename Ring,
    bool CheckSelfIntersections = true,
    bool IsInteriorRing = false
>
struct is_valid_ring
{
    template <typename VisitPolicy, typename Strategy>
    static inline bool apply(Ring const& ring, VisitPolicy& visitor,
                             Strategy const& strategy)
    {
        typedef typename Strategy::cs_tag cs_tag;

        // return invalid if any of the following condition holds:
        // (a) the ring's point coordinates are not invalid (e.g., NaN)
        // (b) the ring's size is below the minimal one
        // (c) the ring consists of at most two distinct points
        // (d) the ring is not topologically closed
        // (e) the ring has spikes
        // (f) the ring has duplicate points (if AllowDuplicates is false)
        // (g) the boundary of the ring has self-intersections
        // (h) the order of the points is inconsistent with the defined order
        //
        // Note: no need to check if the area is zero. If this is the
        // case, then the ring must have at least two spikes, which is
        // checked by condition (d).

        if (has_invalid_coordinate<Ring>::apply(ring, visitor))
        {
            return false;
        }

        closure_selector const closure = geometry::closure<Ring>::value;
        typedef typename closeable_view<Ring const, closure>::type view_type;

        if (boost::size(ring)
            < core_detail::closure::minimum_ring_size<closure>::value)
        {
            return visitor.template apply<failure_few_points>();
        }

        view_type const view(ring);
        if (detail::num_distinct_consecutive_points
                <
                    view_type, 4u, true,
                    not_equal_to
                        <
                            typename point_type<Ring>::type,
                            typename Strategy::equals_point_point_strategy_type
                        >
                >::apply(view)
            < 4u)
        {
            return
                visitor.template apply<failure_wrong_topological_dimension>();
        }

        return
            is_topologically_closed<Ring, closure>::apply(ring, visitor, strategy.get_equals_point_point_strategy())
            && ! has_duplicates<Ring, closure, cs_tag>::apply(ring, visitor)
            && ! has_spikes<Ring, closure>::apply(ring, visitor, strategy.get_side_strategy())
            && (! CheckSelfIntersections
                || has_valid_self_turns<Ring, typename Strategy::cs_tag>::apply(ring, visitor, strategy))
            && is_properly_oriented<Ring, IsInteriorRing>::apply(ring, visitor, strategy);
    }
};


}} // namespace detail::is_valid
#endif // DOXYGEN_NO_DETAIL



#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

// A Ring is a Polygon with exterior boundary only.
// The Ring's boundary must be a LinearRing (see OGC 06-103-r4,
// 6.1.7.1, for the definition of LinearRing)
//
// Reference (for polygon validity): OGC 06-103r4 (6.1.11.1)
template <typename Ring, bool AllowEmptyMultiGeometries>
struct is_valid
    <
        Ring, ring_tag, AllowEmptyMultiGeometries
    > : detail::is_valid::is_valid_ring<Ring>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_RING_HPP

/* ring.hpp
OFRcbtH4OnnnVRiiH/MPse/W6vrffHiq3mKdtnKqUjDqVjHkNPtfpa4sd+9pHHVL08Nt7FI8L7GA/0/WC+SfZdlJdzX/wQk+0dnY2WWcrC+9oBYxW64O+87RU7kpeg/b6ZAdFZDXHNgs5j+gtoujjumH76t5/DlWPcLalz6NfxZma2x3qntPJ7XfNN7kXoIy+o8wq5L41qanGszdeCU7/0EP9ZePxfkm1vJtNdHrYKXxdMgQh09dZ2xjnLIELFCrf5/PVV2Nb7ZSs1TPT1Hj2NjbuPWqRvRIvuwSTzshv1C/lyaHVPlFyyTfl0+dzS/HKYK3zlBD0PMrZ62enSV/o8ef+OA6unksHQ5aWp5n3B+QA+Rj8gn5B/mIrq624dvsM0NBtmhtG+LXXyaPmyOG4Qins9u70Qh3xuP+hg8UzEhff+BRM9WqjatgVtwSJ/6xqj5NQ/tTKsE8x7QkbchJ3GvIQhjQCefIQp9yxNrz2eAkNqbmOfRb91rB3uVdZ6eK5SPYamV8W53w4YvwQOwrPIpe5SFdh8DHAnqK+dmGWHA97t5hj7nPc0xPfezxeBYdz4rhxst4NV9o5bMvcNZv/H8OvtftCTmZcXWxfuvtVUjJDGPVvZ47LD9pak/EGHVPc6l5px5cV72Tf8jRR/DhrvztBjzcen80XDzyfqGeB/jtBBzH9U51i/7V3/h2n5jBx/ay14Pr6K64OMJOni5Gz48n6zTWho09yT9Ki82f6JW98xAeEiXCvnrW3TVWHeGr0/mhGHQzLMonf6nCtrbBp51/qo/LO9LPdSy9fmNu3w+TJ06EAz4bPEoMrqD/00y9pDmdV4BxX+Bbctfy02GlsfYvqdd+RG0tqP9csE7uv7aveLJW7i3mpc5ln2q4d+OnDX6UC2T3+TC2AF+nNdDLMJ4MAsXv8GiO+PnTMtwfLh5y7Y3m/KYxrT0gz4cdjeXYfZaKBWx78/24vPrplnL0dVjtU5+rx0aY7foDN7nObLkgnMlTGSYNhqG+nz8eDx2J8zpufn08W96xvzb9v2T/EQx5ZnAipFaSJ4hL2+FpblInVQ4E75J97yuufSFn8m/xw5I2uKwYXjgjGzHHlJ/h3xFjzeEa/HMXrHpumrgsh6/Jj/tux9nO6f/WkENkhG2l9YUzqZ+R9OR0N9yuob1aON54ON0+n5obnbyuL1EworOZ4ol6bo80uA9MmMKX8v4sz5+M67PTRmJ9Pp/feYbdjYNHrtmK/K52UrufY/X+yqvztW7Iln9iv8XVtnGr294U05PvCOaXOdlTH3i/VUxc1AVvYHd5fhMLe6uXr5SuDA0UJ3e9F9/7nu2rr9WXCyyEIb/hJx/PwAvo/p7e1gc+93T/vmTcH9bD/Wtu14eFX0vFmsuj5Od0dt8Rx+Q1ZmtcqxruuEwsYztvjONL8K5IXfsP9Bjvb+Odx8b8An08cZqNylNW9FHjF4fGq+O9/3gUbtjAntVFk+8MfeRJ47lf7fLv8JVPLjPWHRWsH/+pnU2uOkze83f1lBR5QnK/xQd0s5ndLbL+8u9kT3sS3Q1VZxlqbFkGeK6wK9wrCWv7w++jMO1hc7kJj8DVAj392II90F2u1rCErheqH47MT6c5YFta+JrDvPCfMXyrHt/cm5N/1xXP6+Pg/G/gaf23O2DTHD2ex/AhurhtmjhWBW7oRXY5A1uNqz8bO6k2/od9jTG7uIn9ly9iLJmsrf0Eo/oaE1x8awfuJCZemGWshdmm62R/j3/mZNv6LpMvqpMe8VlNedWzeAidjp4BE+VUDbKIqa53luwmJU7LU3aps7CX2XT8US85kbXvz+7qZvR7MfuzbmLvao6jesAJOJe/O84=
*/