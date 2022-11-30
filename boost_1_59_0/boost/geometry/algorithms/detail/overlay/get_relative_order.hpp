// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017.
// Modifications copyright (c) 2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_RELATIVE_ORDER_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_RELATIVE_ORDER_HPP


#include <boost/geometry/strategies/intersection_strategies.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


/*!
    \brief Get relative order
    \details Can indicate which of two segments R and S,
        both crossing a common segment P, comes first.
        If the two segments cross P very close (e.g. in a spike),
        the distance between the intersection points can be zero,
        but we still need to know which comes first.
        Therefore, it is useful that using sides we are able to discover this.
 */
struct get_relative_order
{
    template <typename Point, typename SideStrategy>
    static inline int value_via_product(Point const& ti, Point const& tj,
                                        Point const& ui, Point const& uj, int factor,
                                        SideStrategy const& strategy)
    {
        int const side_ti_u = strategy.apply(ti, tj, ui);
        int const side_tj_u = strategy.apply(ti, tj, uj);

#ifdef BOOST_GEOMETRY_DEBUG_RELATIVE_ORDER
        std::cout << (factor == 1  ? " r//s " :  " s//r ")
            << side_ti_u << " / " << side_tj_u;
#endif

        return side_ti_u * side_tj_u >= 0
            ? factor * (side_ti_u != 0 ? side_ti_u : side_tj_u)
            : 0;
    }


    template <typename Point1, typename SideStrategy>
    static inline int apply(
                Point1 const& pi, Point1 const& pj,
                Point1 const& ri, Point1 const& rj,
                Point1 const& si, Point1 const& sj,
                SideStrategy const& strategy)
    {
        int const side_ri_p = strategy.apply(pi, pj, ri);
        int const side_si_p = strategy.apply(pi, pj, si);

#ifdef BOOST_GEOMETRY_DEBUG_RELATIVE_ORDER
        int const side_rj_p = strategy::apply(pi, pj, rj);
        int const side_sj_p = strategy::apply(pi, pj, sj);
        std::cout << "r//p: " << side_ri_p << " / " << side_rj_p;
        std::cout << " s//p: " << side_si_p << " / " << side_sj_p;
#endif

        int value = value_via_product(si, sj, ri, rj, 1, strategy);
        if (value == 0)
        {
            value = value_via_product(ri, rj, si, sj, -1, strategy);
        }

        int const order = side_ri_p * side_ri_p * side_si_p * value;

#ifdef BOOST_GEOMETRY_DEBUG_RELATIVE_ORDER
        std::cout
            << " o: " << order
            << std::endl << std::endl;
#endif

        return order;
    }
};


}} // namespace detail::overlay
#endif //DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_RELATIVE_ORDER_HPP

/* get_relative_order.hpp
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
*/