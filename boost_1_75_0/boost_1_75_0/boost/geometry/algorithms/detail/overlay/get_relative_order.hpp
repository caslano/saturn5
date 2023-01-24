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
1JvnskuwpYhWkzUtqCZrELYWFhkMI58G/ilGUEXnyQthbEmY9hpz3Q94dgKcf0C0DjDozD/TZJaJM4isGMmO4tBrq5F02xFoAugJe126bZa8sAKtcmFyexh90jI4xqpeDmKM8UWaJbRCC6VHlbfiuFBpv8a0lVV2HoLdOohjuPiB2PwA5ydEawQgJJ2J0INynPqxC7gODSploQuqDxJnhXFOsrNlaLTVYRy5uhI7DgORQFFs3ZGOwbkFlisMy11jcYgk2gBUWmaOxjIBsRAYBM3qtTE7EkYlswcb4lqrG4tZpSy/KZPOdfc7rQYR5xvDfivrsecQJ8FRTwfeMxpQYbAL3A7WEikbnoFSGc+ZlekilShnhu2rgH1ZD+Q0L0yxutcF2EbsDvoqbYV/J+dPKA0kSePGjX8DdaAGObLDw7ORXE9ME12D6j5/Wg3bEwF6xExjC83eBEPHab1O3ETfFXw6DAMhX2VztCc/DA8cxZhIFs152XDeoQaEvTwHkhdpbxrOoE5TD+gtYqO7zesrTTj/GKav9EszXZKpFoPhE2Xri34/CB7IJJHY42GN6IqICZhRjihV14aT/TXRR5k4L82cJNmfzHMKnihb+4F9PPaOOvvahWORak98qDcjz3Ux4iM2STNJr1u7R/oK1kPu63QnLP0gyQ02pWTWflxnuOl0V7nP/8RaV+2gzkkvyPwIzs1G1Laj1mXui/Se
*/