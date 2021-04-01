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
25PdQ/rhO6VXhGjYL9VA4OHSIKazLie+QcFcxLAAZ2IQbwCznbBpPQRXhTBPFTYmOU19bAVnls5Og4w6OI5BVu6g1p22IMAlgTssti+Za0ROP24wvGuxDSsUKHKNO6u+Qox1Cu8hi8Vf5DkZlMtxStmAC38i6Sp/A/yc1YKF4yq2g3+aMa0T4xwoUMLb6fDeai9MIdUMCaKouL9yGFMsiabDStIME+W9uMmkLvFWaDYPRPgQVJJwPGDDBCZ0hz+FNQ8k/yIcTKVhgwPhKtJ3VXvQQ4+EBYAE+DDldUjvnZw4mBvJMTrfD1NIztq0twFKJGBMGtXZ0jwR0FdbDAWXyhOhn2Hv4v9JTpur9DzHu6kbUsASC95WGwT0gE9Hc+w3ZaUs8q5WbfR5n0djFTWxCXemDbUCyIjILAOt8jvLXT+SG8rKGgD36dYuKqg0T4tYR0WBXwjS7Q8j0aO3jTfmcw8ryi/zOFV2FzDFTcuXjftpuzXSym9VuuYAcLmTKNDeoJUaCz5eOqXZfYXZEjZoi6FdYZJjEZYOxe0qgOWOUu9e47w3mJ4/SDep4A==
*/