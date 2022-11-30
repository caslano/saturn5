// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014-2021.
// Modifications copyright (c) 2014-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_LENGTH_HPP
#define BOOST_GEOMETRY_ALGORITHMS_LENGTH_HPP

#include <iterator>

#include <boost/core/ignore_unused.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/detail/calculate_null.hpp>
#include <boost/geometry/algorithms/detail/dummy_geometries.hpp>
#include <boost/geometry/algorithms/detail/multi_sum.hpp>
// #include <boost/geometry/algorithms/detail/throw_on_empty_input.hpp>
#include <boost/geometry/algorithms/detail/visit.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/visit.hpp>

#include <boost/geometry/geometries/adapted/boost_variant.hpp> // For backward compatibility
#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/default_length_result.hpp> // TODO: Move to algorithms
#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/length/cartesian.hpp>
#include <boost/geometry/strategies/length/geographic.hpp>
#include <boost/geometry/strategies/length/spherical.hpp>

#include <boost/geometry/views/closeable_view.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace length
{


template<typename Segment>
struct segment_length
{
    template <typename Strategies>
    static inline typename default_length_result<Segment>::type
    apply(Segment const& segment, Strategies const& strategies)
    {
        typedef typename point_type<Segment>::type point_type;
        point_type p1, p2;
        geometry::detail::assign_point_from_index<0>(segment, p1);
        geometry::detail::assign_point_from_index<1>(segment, p2);
        return strategies.distance(p1, p2).apply(p1, p2);
    }
};

/*!
\brief Internal, calculates length of a linestring using iterator pairs and
    specified strategy
\note for_each could be used here, now that point_type is changed by boost
    range iterator
*/
template<typename Range, closure_selector Closure>
struct range_length
{
    typedef typename default_length_result<Range>::type return_type;

    template <typename Strategies>
    static inline return_type
    apply(Range const& range, Strategies const& strategies)
    {
        return_type sum = return_type();
        detail::closed_view<Range const> const view(range);
        auto it = boost::begin(view);
        auto const end = boost::end(view);
        if (it != end)
        {
            auto const strategy = strategies.distance(dummy_point(), dummy_point());

            for(auto previous = it++; it != end; ++previous, ++it)
            {
                // Add point-point distance using the return type belonging
                // to strategy
                sum += strategy.apply(*previous, *it);
            }
        }

        return sum;
    }
};


}} // namespace detail::length
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct length : detail::calculate_null
{
    typedef typename default_length_result<Geometry>::type return_type;

    template <typename Strategy>
    static inline return_type apply(Geometry const& geometry, Strategy const& strategy)
    {
        return calculate_null::apply<return_type>(geometry, strategy);
    }
};


template <typename Geometry>
struct length<Geometry, linestring_tag>
    : detail::length::range_length<Geometry, closed>
{};


// RING: length is currently 0; it might be argued that it is the "perimeter"


template <typename Geometry>
struct length<Geometry, segment_tag>
    : detail::length::segment_length<Geometry>
{};


template <typename MultiLinestring>
struct length<MultiLinestring, multi_linestring_tag> : detail::multi_sum
{
    template <typename Strategy>
    static inline typename default_length_result<MultiLinestring>::type
    apply(MultiLinestring const& multi, Strategy const& strategy)
    {
        return multi_sum::apply
               <
                   typename default_length_result<MultiLinestring>::type,
                   detail::length::range_length
                   <
                       typename boost::range_value<MultiLinestring>::type,
                       closed // no need to close it explicitly
                   >
               >(multi, strategy);

    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_strategy {

template
<
    typename Strategies,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategies>::value
>
struct length
{
    template <typename Geometry>
    static inline typename default_length_result<Geometry>::type
    apply(Geometry const& geometry, Strategies const& strategies)
    {
        return dispatch::length<Geometry>::apply(geometry, strategies);
    }
};

template <typename Strategy>
struct length<Strategy, false>
{
    template <typename Geometry>
    static inline typename default_length_result<Geometry>::type
    apply(Geometry const& geometry, Strategy const& strategy)
    {
        using strategies::length::services::strategy_converter;
        return dispatch::length<Geometry>::apply(
                geometry, strategy_converter<Strategy>::get(strategy));
    }
};

template <>
struct length<default_strategy, false>
{
    template <typename Geometry>
    static inline typename default_length_result<Geometry>::type
    apply(Geometry const& geometry, default_strategy const&)
    {
        typedef typename strategies::length::services::default_strategy
            <
                Geometry
            >::type strategies_type;

        return dispatch::length<Geometry>::apply(geometry, strategies_type());
    }
};

} // namespace resolve_strategy


namespace resolve_dynamic {

template <typename Geometry, typename Tag = typename geometry::tag<Geometry>::type>
struct length
{
    template <typename Strategy>
    static inline typename default_length_result<Geometry>::type
    apply(Geometry const& geometry, Strategy const& strategy)
    {
        return resolve_strategy::length<Strategy>::apply(geometry, strategy);
    }
};

template <typename Geometry>
struct length<Geometry, dynamic_geometry_tag>
{
    template <typename Strategy>
    static inline typename default_length_result<Geometry>::type
        apply(Geometry const& geometry, Strategy const& strategy)
    {
        typename default_length_result<Geometry>::type result = 0;
        traits::visit<Geometry>::apply([&](auto const& g)
        {
            result = length<util::remove_cref_t<decltype(g)>>::apply(g, strategy);
        }, geometry);
        return result;
    }
};

template <typename Geometry>
struct length<Geometry, geometry_collection_tag>
{
    template <typename Strategy>
    static inline typename default_length_result<Geometry>::type
        apply(Geometry const& geometry, Strategy const& strategy)
    {
        typename default_length_result<Geometry>::type result = 0;
        detail::visit_breadth_first([&](auto const& g)
        {
            result += length<util::remove_cref_t<decltype(g)>>::apply(g, strategy);
            return true;
        }, geometry);
        return result;
    }
};

} // namespace resolve_dynamic


/*!
\brief \brief_calc{length}
\ingroup length
\details \details_calc{length, length (the sum of distances between consecutive points)}. \details_default_strategy
\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\return \return_calc{length}

\qbk{[include reference/algorithms/length.qbk]}
\qbk{[length] [length_output]}
 */
template<typename Geometry>
inline typename default_length_result<Geometry>::type
length(Geometry const& geometry)
{
    concepts::check<Geometry const>();

    // detail::throw_on_empty_input(geometry);

    return resolve_dynamic::length<Geometry>::apply(geometry, default_strategy());
}


/*!
\brief \brief_calc{length} \brief_strategy
\ingroup length
\details \details_calc{length, length (the sum of distances between consecutive points)} \brief_strategy. \details_strategy_reasons
\tparam Geometry \tparam_geometry
\tparam Strategy \tparam_strategy{distance}
\param geometry \param_geometry
\param strategy \param_strategy{distance}
\return \return_calc{length}

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/length.qbk]}
\qbk{[length_with_strategy] [length_with_strategy_output]}
 */
template<typename Geometry, typename Strategy>
inline typename default_length_result<Geometry>::type
length(Geometry const& geometry, Strategy const& strategy)
{
    concepts::check<Geometry const>();

    // detail::throw_on_empty_input(geometry);

    return resolve_dynamic::length<Geometry>::apply(geometry, strategy);
}


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_LENGTH_HPP

/* length.hpp
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
*/