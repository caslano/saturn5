// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_PERIMETER_HPP
#define BOOST_GEOMETRY_ALGORITHMS_PERIMETER_HPP

#include <boost/range/metafunctions.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/length.hpp>
#include <boost/geometry/algorithms/detail/calculate_null.hpp>
#include <boost/geometry/algorithms/detail/calculate_sum.hpp>
#include <boost/geometry/algorithms/detail/multi_sum.hpp>
// #include <boost/geometry/algorithms/detail/throw_on_empty_input.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/strategies/default_length_result.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

// Default perimeter is 0.0, specializations implement calculated values
template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct perimeter : detail::calculate_null
{
    typedef typename default_length_result<Geometry>::type return_type;

    template <typename Strategy>
    static inline return_type apply(Geometry const& geometry, Strategy const& strategy)
    {
        return calculate_null::apply<return_type>(geometry, strategy);
    }
};

template <typename Geometry>
struct perimeter<Geometry, ring_tag>
    : detail::length::range_length
        <
            Geometry,
            closure<Geometry>::value
        >
{};

template <typename Polygon>
struct perimeter<Polygon, polygon_tag> : detail::calculate_polygon_sum
{
    typedef typename default_length_result<Polygon>::type return_type;
    typedef detail::length::range_length
                <
                    typename ring_type<Polygon>::type,
                    closure<Polygon>::value
                > policy;

    template <typename Strategy>
    static inline return_type apply(Polygon const& polygon, Strategy const& strategy)
    {
        return calculate_polygon_sum::apply<return_type, policy>(polygon, strategy);
    }
};

template <typename MultiPolygon>
struct perimeter<MultiPolygon, multi_polygon_tag> : detail::multi_sum
{
    typedef typename default_length_result<MultiPolygon>::type return_type;

    template <typename Strategy>
    static inline return_type apply(MultiPolygon const& multi, Strategy const& strategy)
    {
        return multi_sum::apply
               <
                   return_type,
                   perimeter<typename boost::range_value<MultiPolygon>::type>
               >(multi, strategy);
    }
};


// box,n-sphere: to be implemented

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_strategy {

struct perimeter
{
    template <typename Geometry, typename Strategy>
    static inline typename default_length_result<Geometry>::type
    apply(Geometry const& geometry, Strategy const& strategy)
    {
        return dispatch::perimeter<Geometry>::apply(geometry, strategy);
    }

    template <typename Geometry>
    static inline typename default_length_result<Geometry>::type
    apply(Geometry const& geometry, default_strategy)
    {
        typedef typename strategy::distance::services::default_strategy
            <
                point_tag, point_tag, typename point_type<Geometry>::type
            >::type strategy_type;

        return dispatch::perimeter<Geometry>::apply(geometry, strategy_type());
    }
};

} // namespace resolve_strategy


namespace resolve_variant {

template <typename Geometry>
struct perimeter
{
    template <typename Strategy>
    static inline typename default_length_result<Geometry>::type
    apply(Geometry const& geometry, Strategy const& strategy)
    {
        concepts::check<Geometry const>();
        return resolve_strategy::perimeter::apply(geometry, strategy);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct perimeter<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    typedef typename default_length_result
        <
            boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>
        >::type result_type;

    template <typename Strategy>
    struct visitor: boost::static_visitor<result_type>
    {
        Strategy const& m_strategy;

        visitor(Strategy const& strategy): m_strategy(strategy) {}

        template <typename Geometry>
        typename default_length_result<Geometry>::type
        operator()(Geometry const& geometry) const
        {
            return perimeter<Geometry>::apply(geometry, m_strategy);
        }
    };

    template <typename Strategy>
    static inline result_type
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Strategy>(strategy), geometry);
    }
};

} // namespace resolve_variant


/*!
\brief \brief_calc{perimeter}
\ingroup perimeter
\details The function perimeter returns the perimeter of a geometry,
    using the default distance-calculation-strategy
\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\return \return_calc{perimeter}

\qbk{[include reference/algorithms/perimeter.qbk]}
\qbk{
[heading Example]
[perimeter]
[perimeter_output]
}
 */
template<typename Geometry>
inline typename default_length_result<Geometry>::type perimeter(
        Geometry const& geometry)
{
    // detail::throw_on_empty_input(geometry);
    return resolve_variant::perimeter<Geometry>::apply(geometry, default_strategy());
}

/*!
\brief \brief_calc{perimeter} \brief_strategy
\ingroup perimeter
\details The function perimeter returns the perimeter of a geometry,
    using specified strategy
\tparam Geometry \tparam_geometry
\tparam Strategy \tparam_strategy{distance}
\param geometry \param_geometry
\param strategy strategy to be used for distance calculations.
\return \return_calc{perimeter}

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/perimeter.qbk]}
 */
template<typename Geometry, typename Strategy>
inline typename default_length_result<Geometry>::type perimeter(
        Geometry const& geometry, Strategy const& strategy)
{
    // detail::throw_on_empty_input(geometry);
    return resolve_variant::perimeter<Geometry>::apply(geometry, strategy);
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_PERIMETER_HPP


/* perimeter.hpp
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
*/