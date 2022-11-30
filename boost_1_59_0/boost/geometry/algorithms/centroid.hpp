// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014-2021.
// Modifications copyright (c) 2014-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_CENTROID_HPP
#define BOOST_GEOMETRY_ALGORITHMS_CENTROID_HPP


#include <cstddef>

#include <boost/core/ignore_unused.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>
#include <boost/throw_exception.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/exception.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/visit.hpp>

#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/algorithms/detail/centroid/translating_transformer.hpp>
#include <boost/geometry/algorithms/detail/interior_iterator.hpp>
#include <boost/geometry/algorithms/detail/point_on_border.hpp>
#include <boost/geometry/algorithms/detail/visit.hpp>
#include <boost/geometry/algorithms/is_empty.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/geometries/adapted/boost_variant.hpp> // For backward compatibility
#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/strategies/centroid/cartesian.hpp>
#include <boost/geometry/strategies/centroid/geographic.hpp>
#include <boost/geometry/strategies/centroid/spherical.hpp>
#include <boost/geometry/strategies/concepts/centroid_concept.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/detail.hpp>

#include <boost/geometry/util/algorithm.hpp>
#include <boost/geometry/util/select_coordinate_type.hpp>
#include <boost/geometry/util/type_traits_std.hpp>

#include <boost/geometry/views/closeable_view.hpp>


namespace boost { namespace geometry
{


#if ! defined(BOOST_GEOMETRY_CENTROID_NO_THROW)

/*!
\brief Centroid Exception
\ingroup centroid
\details The centroid_exception is thrown if the free centroid function is called with
    geometries for which the centroid cannot be calculated. For example: a linestring
    without points, a polygon without points, an empty multi-geometry.
\qbk{
[heading See also]
\* [link geometry.reference.algorithms.centroid the centroid function]
}

 */
class centroid_exception : public geometry::exception
{
public:

    /*!
    \brief The default constructor
    */
    inline centroid_exception() {}

    /*!
    \brief Returns the explanatory string.
    \return Pointer to a null-terminated string with explanatory information.
    */
    virtual char const* what() const throw()
    {
        return "Boost.Geometry Centroid calculation exception";
    }
};

#endif


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace centroid
{

struct centroid_point
{
    template<typename Point, typename PointCentroid, typename Strategy>
    static inline void apply(Point const& point, PointCentroid& centroid,
            Strategy const&)
    {
        geometry::convert(point, centroid);
    }
};

struct centroid_indexed
{
    template<typename Indexed, typename Point, typename Strategy>
    static inline void apply(Indexed const& indexed, Point& centroid,
            Strategy const&)
    {
        typedef typename select_coordinate_type
            <
                Indexed, Point
            >::type coordinate_type;

        detail::for_each_dimension<Indexed>([&](auto dimension)
        {
            coordinate_type const c1 = get<min_corner, dimension>(indexed);
            coordinate_type const c2 = get<max_corner, dimension>(indexed);
            coordinate_type const two = 2;
            set<dimension>(centroid, (c1 + c2) / two);
        });
    }
};


// There is one thing where centroid is different from e.g. within.
// If the ring has only one point, it might make sense that
// that point is the centroid.
template<typename Point, typename Range>
inline bool range_ok(Range const& range, Point& centroid)
{
    std::size_t const n = boost::size(range);
    if (n > 1)
    {
        return true;
    }
    else if (n <= 0)
    {
#if ! defined(BOOST_GEOMETRY_CENTROID_NO_THROW)
        BOOST_THROW_EXCEPTION(centroid_exception());
#else
        return false;
#endif
    }
    else // if (n == 1)
    {
        // Take over the first point in a "coordinate neutral way"
        geometry::convert(*boost::begin(range), centroid);
        return false;
    }
    //return true; // unreachable
}

/*!
    \brief Calculate the centroid of a Ring or a Linestring.
*/
struct centroid_range_state
{
    template<typename Ring, typename PointTransformer, typename Strategy, typename State>
    static inline void apply(Ring const& ring,
                             PointTransformer const& transformer,
                             Strategy const& strategy,
                             State& state)
    {
        boost::ignore_unused(strategy);

        detail::closed_view<Ring const> const view(ring);
        auto it = boost::begin(view);
        auto const end = boost::end(view);

        if (it != end)
        {
            typename PointTransformer::result_type
                previous_pt = transformer.apply(*it);

            for ( ++it ; it != end ; ++it)
            {
                typename PointTransformer::result_type
                    pt = transformer.apply(*it);

                using point_type = typename geometry::point_type<Ring const>::type;
                strategy.apply(static_cast<point_type const&>(previous_pt),
                               static_cast<point_type const&>(pt),
                               state);

                previous_pt = pt;
            }
        }
    }
};

struct centroid_range
{
    template<typename Range, typename Point, typename Strategy>
    static inline bool apply(Range const& range, Point& centroid,
                             Strategy const& strategy)
    {
        if (range_ok(range, centroid))
        {
            // prepare translation transformer
            translating_transformer<Range> transformer(*boost::begin(range));
            
            typename Strategy::template state_type
                <
                    typename geometry::point_type<Range>::type,
                    Point
                >::type state;

            centroid_range_state::apply(range, transformer, strategy, state);
            
            if ( strategy.result(state, centroid) )
            {
                // translate the result back
                transformer.apply_reverse(centroid);
                return true;
            }
        }

        return false;
    }
};


/*!
    \brief Centroid of a polygon.
    \note Because outer ring is clockwise, inners are counter clockwise,
    triangle approach is OK and works for polygons with rings.
*/
struct centroid_polygon_state
{
    template<typename Polygon, typename PointTransformer, typename Strategy, typename State>
    static inline void apply(Polygon const& poly,
                             PointTransformer const& transformer,
                             Strategy const& strategy,
                             State& state)
    {
        centroid_range_state::apply(exterior_ring(poly), transformer, strategy, state);

        typename interior_return_type<Polygon const>::type
            rings = interior_rings(poly);

        for (typename detail::interior_iterator<Polygon const>::type
                it = boost::begin(rings); it != boost::end(rings); ++it)
        {
            centroid_range_state::apply(*it, transformer, strategy, state);
        }
    }
};

struct centroid_polygon
{
    template<typename Polygon, typename Point, typename Strategy>
    static inline bool apply(Polygon const& poly, Point& centroid,
                             Strategy const& strategy)
    {
        if (range_ok(exterior_ring(poly), centroid))
        {
            // prepare translation transformer
            translating_transformer<Polygon>
                transformer(*boost::begin(exterior_ring(poly)));
            
            typename Strategy::template state_type
                <
                    typename geometry::point_type<Polygon>::type,
                    Point
                >::type state;

            centroid_polygon_state::apply(poly, transformer, strategy, state);
            
            if ( strategy.result(state, centroid) )
            {
                // translate the result back
                transformer.apply_reverse(centroid);
                return true;
            }
        }

        return false;
    }
};


/*!
    \brief Building block of a multi-point, to be used as Policy in the
        more generec centroid_multi
*/
struct centroid_multi_point_state
{
    template <typename Point, typename PointTransformer, typename Strategy, typename State>
    static inline void apply(Point const& point,
                             PointTransformer const& transformer,
                             Strategy const& strategy,
                             State& state)
    {
        boost::ignore_unused(strategy);
        strategy.apply(static_cast<Point const&>(transformer.apply(point)),
                       state);
    }
};


/*!
    \brief Generic implementation which calls a policy to calculate the
        centroid of the total of its single-geometries
    \details The Policy is, in general, the single-version, with state. So
        detail::centroid::centroid_polygon_state is used as a policy for this
        detail::centroid::centroid_multi

*/
template <typename Policy>
struct centroid_multi
{
    template <typename Multi, typename Point, typename Strategy>
    static inline bool apply(Multi const& multi,
                             Point& centroid,
                             Strategy const& strategy)
    {
#if ! defined(BOOST_GEOMETRY_CENTROID_NO_THROW)
        // If there is nothing in any of the ranges, it is not possible
        // to calculate the centroid
        if (geometry::is_empty(multi))
        {
            BOOST_THROW_EXCEPTION(centroid_exception());
        }
#endif

        // prepare translation transformer
        translating_transformer<Multi> transformer(multi);

        typename Strategy::template state_type
            <
                typename geometry::point_type<Multi>::type,
                Point
            >::type state;

        for (typename boost::range_iterator<Multi const>::type
                it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            Policy::apply(*it, transformer, strategy, state);
        }

        if ( strategy.result(state, centroid) )
        {
            // translate the result back
            transformer.apply_reverse(centroid);
            return true;
        }
        
        return false;
    }
};


template <typename Algorithm>
struct centroid_linear_areal
{
    template <typename Geometry, typename Point, typename Strategies>
    static inline void apply(Geometry const& geom,
                             Point& centroid,
                             Strategies const& strategies)
    {
        if ( ! Algorithm::apply(geom, centroid, strategies.centroid(geom)) )
        {
            geometry::point_on_border(centroid, geom);
        }
    }
};

template <typename Algorithm>
struct centroid_pointlike
{
    template <typename Geometry, typename Point, typename Strategies>
    static inline void apply(Geometry const& geom,
                             Point& centroid,
                             Strategies const& strategies)
    {
        Algorithm::apply(geom, centroid, strategies.centroid(geom));
    }
};


}} // namespace detail::centroid
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Geometry,
    typename Tag = typename tag<Geometry>::type
>
struct centroid: not_implemented<Tag>
{};

template <typename Geometry>
struct centroid<Geometry, point_tag>
    : detail::centroid::centroid_point
{};

template <typename Box>
struct centroid<Box, box_tag>
    : detail::centroid::centroid_indexed
{};

template <typename Segment>
struct centroid<Segment, segment_tag>
    : detail::centroid::centroid_indexed
{};

template <typename Ring>
struct centroid<Ring, ring_tag>
    : detail::centroid::centroid_linear_areal
        <
            detail::centroid::centroid_range
        >
{};

template <typename Linestring>
struct centroid<Linestring, linestring_tag>
    : detail::centroid::centroid_linear_areal
        <
            detail::centroid::centroid_range
        >
{};

template <typename Polygon>
struct centroid<Polygon, polygon_tag>
    : detail::centroid::centroid_linear_areal
        <
            detail::centroid::centroid_polygon
        >
{};

template <typename MultiLinestring>
struct centroid<MultiLinestring, multi_linestring_tag>
    : detail::centroid::centroid_linear_areal
        <
            detail::centroid::centroid_multi
            <
                detail::centroid::centroid_range_state
            >
        >
{};

template <typename MultiPolygon>
struct centroid<MultiPolygon, multi_polygon_tag>
    : detail::centroid::centroid_linear_areal
        <
            detail::centroid::centroid_multi
            <
                detail::centroid::centroid_polygon_state
            >
        >
{};

template <typename MultiPoint>
struct centroid<MultiPoint, multi_point_tag>
    : detail::centroid::centroid_pointlike
        <
            detail::centroid::centroid_multi
            <
                detail::centroid::centroid_multi_point_state
            >
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_strategy {

template
<
    typename Strategies,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategies>::value
>
struct centroid
{
    template <typename Geometry, typename Point>
    static inline void apply(Geometry const& geometry, Point& out, Strategies const& strategies)
    {
        dispatch::centroid<Geometry>::apply(geometry, out, strategies);
    }
};

template <typename Strategy>
struct centroid<Strategy, false>
{
    template <typename Geometry, typename Point>
    static inline void apply(Geometry const& geometry, Point& out, Strategy const& strategy)
    {
        using strategies::centroid::services::strategy_converter;
        dispatch::centroid
            <
                Geometry
            >::apply(geometry, out, strategy_converter<Strategy>::get(strategy));
    }
};

template <>
struct centroid<default_strategy, false>
{
    template <typename Geometry, typename Point>
    static inline void apply(Geometry const& geometry, Point& out, default_strategy)
    {
        typedef typename strategies::centroid::services::default_strategy
            <
                Geometry
            >::type strategies_type;

        dispatch::centroid<Geometry>::apply(geometry, out, strategies_type());
    }
};

} // namespace resolve_strategy


namespace resolve_dynamic {

template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct centroid
{
    template <typename Point, typename Strategy>
    static inline void apply(Geometry const& geometry, Point& out, Strategy const& strategy)
    {
        concepts::check_concepts_and_equal_dimensions<Point, Geometry const>();
        resolve_strategy::centroid<Strategy>::apply(geometry, out, strategy);
    }
};

template <typename Geometry>
struct centroid<Geometry, dynamic_geometry_tag>
{
    template <typename Point, typename Strategy>
    static inline void apply(Geometry const& geometry,
                             Point& out,
                             Strategy const& strategy)
    {
        traits::visit<Geometry>::apply([&](auto const& g)
        {
            centroid<util::remove_cref_t<decltype(g)>>::apply(g, out, strategy);
        }, geometry);
    }
};

} // namespace resolve_dynamic


/*!
\brief \brief_calc{centroid} \brief_strategy
\ingroup centroid
\details \details_calc{centroid,geometric center (or: center of mass)}. \details_strategy_reasons
\tparam Geometry \tparam_geometry
\tparam Point \tparam_point
\tparam Strategy \tparam_strategy{Centroid}
\param geometry \param_geometry
\param c \param_point \param_set{centroid}
\param strategy \param_strategy{centroid}

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/centroid.qbk]}
\qbk{[include reference/algorithms/centroid_strategies.qbk]}
}

*/
template<typename Geometry, typename Point, typename Strategy>
inline void centroid(Geometry const& geometry, Point& c, Strategy const& strategy)
{
    resolve_dynamic::centroid<Geometry>::apply(geometry, c, strategy);
}


/*!
\brief \brief_calc{centroid}
\ingroup centroid
\details \details_calc{centroid,geometric center (or: center of mass)}. \details_default_strategy
\tparam Geometry \tparam_geometry
\tparam Point \tparam_point
\param geometry \param_geometry
\param c The calculated centroid will be assigned to this point reference

\qbk{[include reference/algorithms/centroid.qbk]}
\qbk{
[heading Example]
[centroid]
[centroid_output]
}
 */
template<typename Geometry, typename Point>
inline void centroid(Geometry const& geometry, Point& c)
{
    geometry::centroid(geometry, c, default_strategy());
}


/*!
\brief \brief_calc{centroid}
\ingroup centroid
\details \details_calc{centroid,geometric center (or: center of mass)}. \details_return{centroid}.
\tparam Point \tparam_point
\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\return \return_calc{centroid}

\qbk{[include reference/algorithms/centroid.qbk]}
 */
template<typename Point, typename Geometry>
inline Point return_centroid(Geometry const& geometry)
{
    Point c;
    geometry::centroid(geometry, c);
    return c;
}

/*!
\brief \brief_calc{centroid} \brief_strategy
\ingroup centroid
\details \details_calc{centroid,geometric center (or: center of mass)}. \details_return{centroid}. \details_strategy_reasons
\tparam Point \tparam_point
\tparam Geometry \tparam_geometry
\tparam Strategy \tparam_strategy{centroid}
\param geometry \param_geometry
\param strategy \param_strategy{centroid}
\return \return_calc{centroid}

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/centroid.qbk]}
\qbk{[include reference/algorithms/centroid_strategies.qbk]}
 */
template<typename Point, typename Geometry, typename Strategy>
inline Point return_centroid(Geometry const& geometry, Strategy const& strategy)
{
    Point c;
    geometry::centroid(geometry, c, strategy);
    return c;
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_CENTROID_HPP

/* centroid.hpp
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
*/