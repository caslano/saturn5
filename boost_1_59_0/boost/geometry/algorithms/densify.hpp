// Boost.Geometry

// Copyright (c) 2017-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DENSIFY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DENSIFY_HPP


#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>
#include <boost/throw_exception.hpp>

#include <boost/geometry/algorithms/clear.hpp>
#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/algorithms/detail/convert_point_to_point.hpp>
#include <boost/geometry/algorithms/detail/visit.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/exception.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/visit.hpp>
#include <boost/geometry/geometries/adapted/boost_variant.hpp> // For backward compatibility
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/densify/cartesian.hpp>
#include <boost/geometry/strategies/densify/geographic.hpp>
#include <boost/geometry/strategies/densify/spherical.hpp>
#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace densify
{

template <typename Range>
struct push_back_policy
{
    typedef typename boost::range_value<Range>::type point_type;

    inline explicit push_back_policy(Range & rng)
        : m_rng(rng)
    {}

    inline void apply(point_type const& p)
    {
        range::push_back(m_rng, p);
    }

private:
    Range & m_rng;
};

template <typename Range, typename Point>
inline void convert_and_push_back(Range & range, Point const& p)
{
    typename boost::range_value<Range>::type p2;
    geometry::detail::conversion::convert_point_to_point(p, p2);
    range::push_back(range, p2);
}

template <bool AppendLastPoint = true>
struct densify_range
{
    template <typename FwdRng, typename MutRng, typename T, typename Strategies>
    static inline void apply(FwdRng const& rng, MutRng & rng_out,
                             T const& len, Strategies const& strategies)
    {
        typedef typename boost::range_iterator<FwdRng const>::type iterator_t;
        typedef typename boost::range_value<FwdRng>::type point_t;

        iterator_t it = boost::begin(rng);
        iterator_t end = boost::end(rng);

        if (it == end) // empty(rng)
        {
            return;
        }
            
        auto strategy = strategies.densify(rng);
        push_back_policy<MutRng> policy(rng_out);

        iterator_t prev = it;
        for ( ++it ; it != end ; prev = it++)
        {
            point_t const& p0 = *prev;
            point_t const& p1 = *it;

            convert_and_push_back(rng_out, p0);

            strategy.apply(p0, p1, policy, len);
        }

        if (BOOST_GEOMETRY_CONDITION(AppendLastPoint))
        {
            convert_and_push_back(rng_out, *prev); // back(rng)
        }
    }
};

template <bool IsClosed1, bool IsClosed2> // false, X
struct densify_ring
{
    template <typename Geometry, typename GeometryOut, typename T, typename Strategies>
    static inline void apply(Geometry const& ring, GeometryOut & ring_out,
                             T const& len, Strategies const& strategies)
    {
        geometry::detail::densify::densify_range<true>
            ::apply(ring, ring_out, len, strategies);

        if (boost::size(ring) <= 1)
            return;

        typedef typename point_type<Geometry>::type point_t;
        point_t const& p0 = range::back(ring);
        point_t const& p1 = range::front(ring);

        auto strategy = strategies.densify(ring);
        push_back_policy<GeometryOut> policy(ring_out);

        strategy.apply(p0, p1, policy, len);

        if (BOOST_GEOMETRY_CONDITION(IsClosed2))
        {
            convert_and_push_back(ring_out, p1);
        }
    }
};

template <>
struct densify_ring<true, true>
    : densify_range<true>
{};

template <>
struct densify_ring<true, false>
    : densify_range<false>
{};

struct densify_convert
{
    template <typename GeometryIn, typename GeometryOut, typename T, typename Strategy>
    static void apply(GeometryIn const& in, GeometryOut &out,
                      T const& , Strategy const& )
    {
        geometry::convert(in, out);
    }
};

}} // namespace detail::densify
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Geometry,
    typename GeometryOut,
    typename Tag1 = typename tag<Geometry>::type,
    typename Tag2 = typename tag<GeometryOut>::type
>
struct densify
    : not_implemented<Tag1, Tag2>
{};

template <typename Geometry, typename GeometryOut>
struct densify<Geometry, GeometryOut, point_tag, point_tag>
    : geometry::detail::densify::densify_convert
{};

template <typename Geometry, typename GeometryOut>
struct densify<Geometry, GeometryOut, segment_tag, segment_tag>
    : geometry::detail::densify::densify_convert
{};

template <typename Geometry, typename GeometryOut>
struct densify<Geometry, GeometryOut, box_tag, box_tag>
    : geometry::detail::densify::densify_convert
{};

template <typename Geometry, typename GeometryOut>
struct densify<Geometry, GeometryOut, multi_point_tag, multi_point_tag>
    : geometry::detail::densify::densify_convert
{};

template <typename Geometry, typename GeometryOut>
struct densify<Geometry, GeometryOut, linestring_tag, linestring_tag>
    : geometry::detail::densify::densify_range<>
{};

template <typename Geometry, typename GeometryOut>
struct densify<Geometry, GeometryOut, multi_linestring_tag, multi_linestring_tag>
{
    template <typename T, typename Strategy>
    static void apply(Geometry const& mls, GeometryOut & mls_out,
                      T const& len, Strategy const& strategy)
    {
        std::size_t count = boost::size(mls);
        range::resize(mls_out, count);

        for (std::size_t i = 0 ; i < count ; ++i)
        {
            geometry::detail::densify::densify_range<>
                ::apply(range::at(mls, i), range::at(mls_out, i),
                        len, strategy);
        }
    }
};

template <typename Geometry, typename GeometryOut>
struct densify<Geometry, GeometryOut, ring_tag, ring_tag>
    : geometry::detail::densify::densify_ring
        <
            geometry::closure<Geometry>::value != geometry::open,
            geometry::closure<GeometryOut>::value != geometry::open
        >
{};

template <typename Geometry, typename GeometryOut>
struct densify<Geometry, GeometryOut, polygon_tag, polygon_tag>
{
    template <typename T, typename Strategy>
    static void apply(Geometry const& poly, GeometryOut & poly_out,
                      T const& len, Strategy const& strategy)
    {
        apply_ring(exterior_ring(poly), exterior_ring(poly_out),
                   len, strategy);

        std::size_t count = boost::size(interior_rings(poly));
        range::resize(interior_rings(poly_out), count);

        for (std::size_t i = 0 ; i < count ; ++i)
        {
            apply_ring(range::at(interior_rings(poly), i),
                       range::at(interior_rings(poly_out), i),
                       len, strategy);
        }
    }

    template <typename Ring, typename RingOut, typename T, typename Strategy>
    static void apply_ring(Ring const& ring, RingOut & ring_out,
                           T const& len, Strategy const& strategy)
    {
        densify<Ring, RingOut, ring_tag, ring_tag>
            ::apply(ring, ring_out, len, strategy);
    }
};

template <typename Geometry, typename GeometryOut>
struct densify<Geometry, GeometryOut, multi_polygon_tag, multi_polygon_tag>
{
    template <typename T, typename Strategy>
    static void apply(Geometry const& mpoly, GeometryOut & mpoly_out,
                      T const& len, Strategy const& strategy)
    {
        std::size_t count = boost::size(mpoly);
        range::resize(mpoly_out, count);

        for (std::size_t i = 0 ; i < count ; ++i)
        {
            apply_poly(range::at(mpoly, i),
                       range::at(mpoly_out, i),
                       len, strategy);
        }
    }

    template <typename Poly, typename PolyOut, typename T, typename Strategy>
    static void apply_poly(Poly const& poly, PolyOut & poly_out,
                           T const& len, Strategy const& strategy)
    {
        densify<Poly, PolyOut, polygon_tag, polygon_tag>::
            apply(poly, poly_out, len, strategy);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_strategy
{

template
<
    typename Strategies,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategies>::value
>
struct densify
{
    template <typename Geometry, typename Distance>
    static inline void apply(Geometry const& geometry,
                             Geometry& out,
                             Distance const& max_distance,
                             Strategies const& strategies)
    {
        dispatch::densify
            <
                Geometry, Geometry
            >::apply(geometry, out, max_distance, strategies);
    }
};

template <typename Strategy>
struct densify<Strategy, false>
{
    template <typename Geometry, typename Distance>
    static inline void apply(Geometry const& geometry,
                             Geometry& out,
                             Distance const& max_distance,
                             Strategy const& strategy)
    {
        using strategies::densify::services::strategy_converter;

        dispatch::densify
            <
                Geometry, Geometry
            >::apply(geometry, out, max_distance,
                     strategy_converter<Strategy>::get(strategy));
    }
};

template <>
struct densify<default_strategy, false>
{
    template <typename Geometry, typename Distance>
    static inline void apply(Geometry const& geometry,
                             Geometry& out,
                             Distance const& max_distance,
                             default_strategy const&)
    {
        typedef typename strategies::densify::services::default_strategy
            <
                Geometry
            >::type strategies_type;
        
        dispatch::densify
            <
                Geometry, Geometry
            >::apply(geometry, out, max_distance, strategies_type());
    }
};

} // namespace resolve_strategy


namespace resolve_dynamic {

template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct densify
{
    template <typename Distance, typename Strategy>
    static inline void apply(Geometry const& geometry,
                             Geometry& out,
                             Distance const& max_distance,
                             Strategy const& strategy)
    {
        resolve_strategy::densify
            <
                Strategy
            >::apply(geometry, out, max_distance, strategy);
    }
};

template <typename Geometry>
struct densify<Geometry, dynamic_geometry_tag>
{
    template <typename Distance, typename Strategy>
    static inline void
    apply(Geometry const& geometry,
          Geometry& out,
          Distance const& max_distance,
          Strategy const& strategy)
    {
        traits::visit<Geometry>::apply([&](auto const& g)
        {
            using geom_t = util::remove_cref_t<decltype(g)>;
            geom_t o;
            densify<geom_t>::apply(g, o, max_distance, strategy);
            out = std::move(o);
        }, geometry);
    }
};

template <typename Geometry>
struct densify<Geometry, geometry_collection_tag>
{
    template <typename Distance, typename Strategy>
    static inline void
    apply(Geometry const& geometry,
          Geometry& out,
          Distance const& max_distance,
          Strategy const& strategy)
    {
        detail::visit_breadth_first([&](auto const& g)
        {
            using geom_t = util::remove_cref_t<decltype(g)>;
            geom_t o;
            densify<geom_t>::apply(g, o, max_distance, strategy);
            traits::emplace_back<Geometry>::apply(out, std::move(o));
            return true;
        }, geometry);
    }
};

} // namespace resolve_dynamic


/*!
\brief Densify a geometry using a specified strategy
\ingroup densify
\tparam Geometry \tparam_geometry
\tparam Distance A numerical distance measure
\tparam Strategy A type fulfilling a DensifyStrategy concept
\param geometry Input geometry, to be densified
\param out Output geometry, densified version of the input geometry
\param max_distance Distance threshold (in units depending on strategy)
\param strategy Densify strategy to be used for densification

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/densify.qbk]}

\qbk{
[heading Available Strategies]
\* [link geometry.reference.strategies.strategy_densify_cartesian Cartesian]
\* [link geometry.reference.strategies.strategy_densify_spherical Spherical]
\* [link geometry.reference.strategies.strategy_densify_geographic Geographic]

[heading Example]
[densify_strategy]
[densify_strategy_output]

[heading See also]
\* [link geometry.reference.algorithms.line_interpolate line_interpolate]
}
*/
template <typename Geometry, typename Distance, typename Strategy>
inline void densify(Geometry const& geometry,
                    Geometry& out,
                    Distance const& max_distance,
                    Strategy const& strategy)
{
    concepts::check<Geometry>();

    if (max_distance <= Distance(0))
    {
        BOOST_THROW_EXCEPTION(geometry::invalid_input_exception());
    }

    geometry::clear(out);

    resolve_dynamic::densify
        <
            Geometry
        >::apply(geometry, out, max_distance, strategy);
}


/*!
\brief Densify a geometry
\ingroup densify
\tparam Geometry \tparam_geometry
\tparam Distance A numerical distance measure
\param geometry Input geometry, to be densified
\param out Output geometry, densified version of the input geometry
\param max_distance Distance threshold (in units depending on coordinate system)

\qbk{[include reference/algorithms/densify.qbk]}

\qbk{
[heading Example]
[densify]
[densify_output]

[heading See also]
\* [link geometry.reference.algorithms.line_interpolate line_interpolate]
}
*/
template <typename Geometry, typename Distance>
inline void densify(Geometry const& geometry,
                    Geometry& out,
                    Distance const& max_distance)
{
    densify(geometry, out, max_distance, default_strategy());
}


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DENSIFY_HPP

/* densify.hpp
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
*/