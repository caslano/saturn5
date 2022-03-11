// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014, 2015.
// Modifications copyright (c) 2014-2015 Oracle and/or its affiliates.

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
#include <boost/range.hpp>
#include <boost/throw_exception.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/exception.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/algorithms/detail/interior_iterator.hpp>
#include <boost/geometry/algorithms/detail/point_on_border.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/strategies/centroid.hpp>
#include <boost/geometry/strategies/concepts/centroid_concept.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/views/closeable_view.hpp>

#include <boost/geometry/util/for_each_coordinate.hpp>
#include <boost/geometry/util/select_coordinate_type.hpp>

#include <boost/geometry/algorithms/is_empty.hpp>

#include <boost/geometry/algorithms/detail/centroid/translating_transformer.hpp>


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

template
<
    typename Indexed,
    typename Point,
    std::size_t Dimension = 0,
    std::size_t DimensionCount = dimension<Indexed>::type::value
>
struct centroid_indexed_calculator
{
    typedef typename select_coordinate_type
        <
            Indexed, Point
        >::type coordinate_type;
    static inline void apply(Indexed const& indexed, Point& centroid)
    {
        coordinate_type const c1 = get<min_corner, Dimension>(indexed);
        coordinate_type const c2 = get<max_corner, Dimension>(indexed);
        coordinate_type m = c1 + c2;
        coordinate_type const two = 2;
        m /= two;

        set<Dimension>(centroid, m);

        centroid_indexed_calculator
            <
                Indexed, Point, Dimension + 1
            >::apply(indexed, centroid);
    }
};


template<typename Indexed, typename Point, std::size_t DimensionCount>
struct centroid_indexed_calculator<Indexed, Point, DimensionCount, DimensionCount>
{
    static inline void apply(Indexed const& , Point& )
    {
    }
};


struct centroid_indexed
{
    template<typename Indexed, typename Point, typename Strategy>
    static inline void apply(Indexed const& indexed, Point& centroid,
            Strategy const&)
    {
        centroid_indexed_calculator
            <
                Indexed, Point
            >::apply(indexed, centroid);
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
template <closure_selector Closure>
struct centroid_range_state
{
    template<typename Ring, typename PointTransformer, typename Strategy>
    static inline void apply(Ring const& ring,
                             PointTransformer const& transformer,
                             Strategy const& strategy,
                             typename Strategy::state_type& state)
    {
        boost::ignore_unused(strategy);

        typedef typename geometry::point_type<Ring const>::type point_type;
        typedef typename closeable_view<Ring const, Closure>::type view_type;

        typedef typename boost::range_iterator<view_type const>::type iterator_type;

        view_type view(ring);
        iterator_type it = boost::begin(view);
        iterator_type end = boost::end(view);

        if (it != end)
        {
            typename PointTransformer::result_type
                previous_pt = transformer.apply(*it);

            for ( ++it ; it != end ; ++it)
            {
                typename PointTransformer::result_type
                    pt = transformer.apply(*it);

                strategy.apply(static_cast<point_type const&>(previous_pt),
                               static_cast<point_type const&>(pt),
                               state);

                previous_pt = pt;
            }
        }
    }
};

template <closure_selector Closure>
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
            
            typename Strategy::state_type state;
            centroid_range_state<Closure>::apply(range, transformer,
                                                 strategy, state);
            
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
    template<typename Polygon, typename PointTransformer, typename Strategy>
    static inline void apply(Polygon const& poly,
                             PointTransformer const& transformer,
                             Strategy const& strategy,
                             typename Strategy::state_type& state)
    {
        typedef typename ring_type<Polygon>::type ring_type;
        typedef centroid_range_state<geometry::closure<ring_type>::value> per_ring;

        per_ring::apply(exterior_ring(poly), transformer, strategy, state);

        typename interior_return_type<Polygon const>::type
            rings = interior_rings(poly);

        for (typename detail::interior_iterator<Polygon const>::type
                it = boost::begin(rings); it != boost::end(rings); ++it)
        {
            per_ring::apply(*it, transformer, strategy, state);
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
            
            typename Strategy::state_type state;
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
    template <typename Point, typename PointTransformer, typename Strategy>
    static inline void apply(Point const& point,
                             PointTransformer const& transformer,
                             Strategy const& strategy,
                             typename Strategy::state_type& state)
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

        typename Strategy::state_type state;

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
    template <typename Geometry, typename Point, typename Strategy>
    static inline void apply(Geometry const& geom,
                             Point& centroid,
                             Strategy const& strategy)
    {
        if ( ! Algorithm::apply(geom, centroid, strategy) )
        {
            geometry::point_on_border(centroid, geom);
        }
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
            detail::centroid::centroid_range<geometry::closure<Ring>::value>
        >
{};

template <typename Linestring>
struct centroid<Linestring, linestring_tag>
    : detail::centroid::centroid_linear_areal
        <
            detail::centroid::centroid_range<closed>
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
                detail::centroid::centroid_range_state<closed>
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
    : detail::centroid::centroid_multi
        <
            detail::centroid::centroid_multi_point_state
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_strategy {

template <typename Geometry>
struct centroid
{
    template <typename Point, typename Strategy>
    static inline void apply(Geometry const& geometry, Point& out, Strategy const& strategy)
    {
        dispatch::centroid<Geometry>::apply(geometry, out, strategy);
    }

    template <typename Point>
    static inline void apply(Geometry const& geometry, Point& out, default_strategy)
    {
        typedef typename strategy::centroid::services::default_strategy
        <
            typename cs_tag<Geometry>::type,
            typename tag_cast
                <
                    typename tag<Geometry>::type,
                    pointlike_tag,
                    linear_tag,
                    areal_tag
                >::type,
            dimension<Geometry>::type::value,
            Point,
            Geometry
        >::type strategy_type;

        dispatch::centroid<Geometry>::apply(geometry, out, strategy_type());
    }
};

} // namespace resolve_strategy


namespace resolve_variant {

template <typename Geometry>
struct centroid
{
    template <typename Point, typename Strategy>
    static inline void apply(Geometry const& geometry, Point& out, Strategy const& strategy)
    {
        concepts::check_concepts_and_equal_dimensions<Point, Geometry const>();
        resolve_strategy::centroid<Geometry>::apply(geometry, out, strategy);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct centroid<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename Point, typename Strategy>
    struct visitor: boost::static_visitor<void>
    {
        Point& m_out;
        Strategy const& m_strategy;

        visitor(Point& out, Strategy const& strategy)
        : m_out(out), m_strategy(strategy)
        {}

        template <typename Geometry>
        void operator()(Geometry const& geometry) const
        {
            centroid<Geometry>::apply(geometry, m_out, m_strategy);
        }
    };

    template <typename Point, typename Strategy>
    static inline void
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry,
          Point& out,
          Strategy const& strategy)
    {
        boost::apply_visitor(visitor<Point, Strategy>(out, strategy), geometry);
    }
};

} // namespace resolve_variant


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
inline void centroid(Geometry const& geometry, Point& c,
        Strategy const& strategy)
{
    resolve_variant::centroid<Geometry>::apply(geometry, c, strategy);
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