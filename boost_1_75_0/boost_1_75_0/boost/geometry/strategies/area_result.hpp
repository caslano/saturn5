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
lzmtt41quDiwKoV6iovrl6xx6XmD1NYk8zxXerL5+6rscISdsm5WnrJzsJO2blN9KaU6Ors7bU2jah1Nq3frTuLSsCM3ax2/TfnV9p1LrKOiWOtqqUf+h2uZb6j8eulmDRx+a7gLHRQI9uVgQxB1+Y69MdPD6/NYYmcXc/T2RvvunRCbHM6tb3OO9iwWrhJn4P3cgPjLM9XU2/3u2yJEpi3FfVAeUnWXF6aejWTLR7pqIbIn6T4yjBEeHii3E+2QprMRpsdWyXkXMWl+reuj5Jw3TWAjTK1UPc0El3NBRewHFQQ3V6WkO7H93T6afZNPaCDxph4kFYS6zK6HLTqlnOm/EbCXqmnIdyle5l+r3vc9QOkh1xwhgR0U4sOOSgWnNSdwJc/C1Hs1JAuQZTSWQWaYiThp7/u4BvBxRZINTwosmIQ+5j63zdH+XuJO9/VFWVj2jSr9GGuXemv521WQg4YnMIDp62hPkwZFeVg2mhndKuiZ2Rg6LmiRXJN+LrQYo4i8oSI0q95kqZGi4IaGdG3nS6aDc9sVo86H9ApStKXN9iqtiejPc9hihHeqOjF+RSazcUbO5Vfv1CNXBsZ3hHBQ5mOvi5QttcM+CaKUlz2P9quY8THFUfm5GCDcbhkQZWLXlbqakq1yeKCEyQtiUKnaxpfhSvPJw90km/iD21txjbp1nk9Am8uVbwNZuo0TsCMGGn5/8V+HTeV6
*/