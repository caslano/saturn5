// Boost.Geometry

// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_AREA_RESULT_HPP
#define BOOST_GEOMETRY_STRATEGIES_AREA_RESULT_HPP


#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/cs.hpp>

#include <boost/geometry/strategies/area.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>

#include <boost/geometry/util/select_most_precise.hpp>
#include <boost/geometry/util/select_sequence_element.hpp>


#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/variant/variant_fwd.hpp>


namespace boost { namespace geometry
{


/*!
\brief Meta-function defining return type of area function
\ingroup area
\note The return-type is defined by Geometry and Strategy
 */
template
<
    typename Geometry,
    typename Strategy = default_strategy
>
struct area_result
    : Strategy::template result_type<Geometry>
{};

template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Strategy>
struct area_result<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Strategy>
    : geometry::area_result
        <
            typename geometry::util::select_sequence_element
                <
                    typename boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>::types
                >::type,
            Strategy
        >
{};

template <typename Geometry>
struct area_result<Geometry, default_strategy>
    : geometry::area_result
        <
            Geometry,
            typename geometry::strategy::area::services::default_strategy
                <
                    typename cs_tag<Geometry>::type
                >::type
        >
{};

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace area
{

template <typename Curr, typename Next>
struct pred_more_precise_default_area_result
{
    typedef typename geometry::area_result<Curr, default_strategy>::type curr_result_t;
    typedef typename geometry::area_result<Next, default_strategy>::type next_result_t;

    typedef typename boost::mpl::if_c
        <
            boost::is_same
                <
                    curr_result_t,
                    typename geometry::select_most_precise
                        <
                            curr_result_t,
                            next_result_t
                        >::type
                >::value,
            Curr,
            Next
        >::type type;
};

}} // namespace detail::area
#endif //DOXYGEN_NO_DETAIL

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct area_result<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>, default_strategy>
    : geometry::area_result
        <
            typename geometry::util::select_sequence_element
                <
                    typename boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>::types,
                    geometry::detail::area::pred_more_precise_default_area_result
                >::type,
            default_strategy
        >
{};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_AREA_RESULT_HPP

/* area_result.hpp
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
*/