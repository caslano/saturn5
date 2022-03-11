// Boost.Geometry

// Copyright (c) 2017-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DENSIFY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DENSIFY_HPP


#include <boost/geometry/algorithms/clear.hpp>
#include <boost/geometry/algorithms/detail/convert_point_to_point.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/exception.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/densify.hpp>
#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/range.hpp>

#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>

#include <boost/throw_exception.hpp>


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
    template <typename FwdRng, typename MutRng, typename T, typename Strategy>
    static inline void apply(FwdRng const& rng, MutRng & rng_out,
                             T const& len, Strategy const& strategy)
    {
        typedef typename boost::range_iterator<FwdRng const>::type iterator_t;
        typedef typename boost::range_value<FwdRng>::type point_t;

        iterator_t it = boost::begin(rng);
        iterator_t end = boost::end(rng);

        if (it == end) // empty(rng)
        {
            return;
        }
            
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
    template <typename Geometry, typename GeometryOut, typename T, typename Strategy>
    static inline void apply(Geometry const& ring, GeometryOut & ring_out,
                             T const& len, Strategy const& strategy)
    {
        geometry::detail::densify::densify_range<true>
            ::apply(ring, ring_out, len, strategy);

        if (boost::size(ring) <= 1)
            return;

        typedef typename point_type<Geometry>::type point_t;
        point_t const& p0 = range::back(ring);
        point_t const& p1 = range::front(ring);

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

struct densify
{
    template <typename Geometry, typename Distance, typename Strategy>
    static inline void apply(Geometry const& geometry,
                             Geometry& out,
                             Distance const& max_distance,
                             Strategy const& strategy)
    {
        dispatch::densify<Geometry, Geometry>
            ::apply(geometry, out, max_distance, strategy);
    }

    template <typename Geometry, typename Distance>
    static inline void apply(Geometry const& geometry,
                             Geometry& out,
                             Distance const& max_distance,
                             default_strategy)
    {
        typedef typename strategy::densify::services::default_strategy
            <
                typename cs_tag<Geometry>::type
            >::type strategy_type;
        
        /*BOOST_CONCEPT_ASSERT(
            (concepts::DensifyStrategy<strategy_type>)
        );*/

        apply(geometry, out, max_distance, strategy_type());
    }
};

} // namespace resolve_strategy


namespace resolve_variant {

template <typename Geometry>
struct densify
{
    template <typename Distance, typename Strategy>
    static inline void apply(Geometry const& geometry,
                             Geometry& out,
                             Distance const& max_distance,
                             Strategy const& strategy)
    {
        resolve_strategy::densify::apply(geometry, out, max_distance, strategy);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct densify<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename Distance, typename Strategy>
    struct visitor: boost::static_visitor<void>
    {
        Distance const& m_max_distance;
        Strategy const& m_strategy;

        visitor(Distance const& max_distance, Strategy const& strategy)
            : m_max_distance(max_distance)
            , m_strategy(strategy)
        {}

        template <typename Geometry>
        void operator()(Geometry const& geometry, Geometry& out) const
        {
            densify<Geometry>::apply(geometry, out, m_max_distance, m_strategy);
        }
    };

    template <typename Distance, typename Strategy>
    static inline void
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry,
          boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>& out,
          Distance const& max_distance,
          Strategy const& strategy)
    {
        boost::apply_visitor(
            visitor<Distance, Strategy>(max_distance, strategy),
            geometry,
            out
        );
    }
};

} // namespace resolve_variant


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

    resolve_variant::densify
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