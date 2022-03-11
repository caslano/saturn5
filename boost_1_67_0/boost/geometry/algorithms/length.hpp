// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014, 2015.
// Modifications copyright (c) 2014-2015, Oracle and/or its affiliates.

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

#include <boost/concept_check.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/greater.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/set.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/value_type.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/detail/calculate_null.hpp>
#include <boost/geometry/algorithms/detail/multi_sum.hpp>
// #include <boost/geometry/algorithms/detail/throw_on_empty_input.hpp>
#include <boost/geometry/views/closeable_view.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/default_length_result.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace length
{


template<typename Segment>
struct segment_length
{
    template <typename Strategy>
    static inline typename default_length_result<Segment>::type apply(
            Segment const& segment, Strategy const& strategy)
    {
        boost::ignore_unused(strategy);
        typedef typename point_type<Segment>::type point_type;
        point_type p1, p2;
        geometry::detail::assign_point_from_index<0>(segment, p1);
        geometry::detail::assign_point_from_index<1>(segment, p2);
        return strategy.apply(p1, p2);
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

    template <typename Strategy>
    static inline return_type apply(
            Range const& range, Strategy const& strategy)
    {
        boost::ignore_unused(strategy);
        typedef typename closeable_view<Range const, Closure>::type view_type;
        typedef typename boost::range_iterator
            <
                view_type const
            >::type iterator_type;

        return_type sum = return_type();
        view_type view(range);
        iterator_type it = boost::begin(view), end = boost::end(view);
        if(it != end)
        {
            for(iterator_type previous = it++;
                    it != end;
                    ++previous, ++it)
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

struct length
{
    template <typename Geometry, typename Strategy>
    static inline typename default_length_result<Geometry>::type
    apply(Geometry const& geometry, Strategy const& strategy)
    {
        return dispatch::length<Geometry>::apply(geometry, strategy);
    }

    template <typename Geometry>
    static inline typename default_length_result<Geometry>::type
    apply(Geometry const& geometry, default_strategy)
    {
        typedef typename strategy::distance::services::default_strategy
            <
                point_tag, point_tag, typename point_type<Geometry>::type
            >::type strategy_type;

        return dispatch::length<Geometry>::apply(geometry, strategy_type());
    }
};

} // namespace resolve_strategy


namespace resolve_variant {

template <typename Geometry>
struct length
{
    template <typename Strategy>
    static inline typename default_length_result<Geometry>::type
    apply(Geometry const& geometry, Strategy const& strategy)
    {
        return resolve_strategy::length::apply(geometry, strategy);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct length<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    typedef typename default_length_result
        <
            boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>
        >::type result_type;

    template <typename Strategy>
    struct visitor
        : static_visitor<result_type>
    {
        Strategy const& m_strategy;

        visitor(Strategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Geometry>
        inline typename default_length_result<Geometry>::type
        operator()(Geometry const& geometry) const
        {
            return length<Geometry>::apply(geometry, m_strategy);
        }
    };

    template <typename Strategy>
    static inline result_type apply(
        variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry,
        Strategy const& strategy
    )
    {
        return boost::apply_visitor(visitor<Strategy>(strategy), geometry);
    }
};

} // namespace resolve_variant


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

    return resolve_variant::length<Geometry>::apply(geometry, default_strategy());
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

    return resolve_variant::length<Geometry>::apply(geometry, strategy);
}


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_LENGTH_HPP

/* length.hpp
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
*/