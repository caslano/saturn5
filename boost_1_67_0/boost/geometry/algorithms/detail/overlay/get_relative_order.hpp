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