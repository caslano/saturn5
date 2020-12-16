// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013, 2014, 2015, 2019.
// Modifications copyright (c) 2013-2019 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_RELATE_IMPL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_RELATE_IMPL_HPP

#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_base_of.hpp>

#include <boost/geometry/algorithms/detail/relate/interface.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/core/tag.hpp>

namespace boost { namespace geometry {


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace relate {

struct implemented_tag {};

template
<
    typename Geometry1,
    typename Geometry2
>
struct relate_impl_base
    : boost::mpl::if_c
        <
            boost::is_base_of
                <
                    nyi::not_implemented_tag,
                    dispatch::relate<Geometry1, Geometry2>
                >::value,
            not_implemented
                <
                    typename geometry::tag<Geometry1>::type,
                    typename geometry::tag<Geometry2>::type
                >,
            implemented_tag
        >::type
{};

template
<
    typename Geometry1,
    typename Geometry2,
    typename StaticMask
>
struct relate_impl_dispatch
    : relate_impl_base<Geometry1, Geometry2>
{
    template <typename Strategy>
    static inline bool apply(Geometry1 const& g1, Geometry2 const& g2, Strategy const& strategy)
    {
        typename detail::relate::result_handler_type
            <
                Geometry1,
                Geometry2,
                StaticMask
            >::type handler;

        dispatch::relate<Geometry1, Geometry2>::apply(g1, g2, handler, strategy);

        return handler.result();
    }
};

template <typename Geometry1, typename Geometry2>
struct relate_impl_dispatch<Geometry1, Geometry2, detail::relate::false_mask>
    : relate_impl_base<Geometry1, Geometry2>
{
    template <typename Strategy>
    static inline bool apply(Geometry1 const& , Geometry2 const& , Strategy const& )
    {
        return false;
    }
};

template
<
    template <typename, typename> class StaticMaskTrait,
    typename Geometry1,
    typename Geometry2
>
struct relate_impl
    : relate_impl_dispatch
        <
            Geometry1,
            Geometry2,
            typename StaticMaskTrait<Geometry1, Geometry2>::type
        >
{};

}} // namespace detail::relate
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_RELATE_IMPL_HPP

/* relate_impl.hpp
/swX28d3tcXv3to+fteJ8fgnO4jfbIvf39H32+JXdJA+aoufgfgvoYfKIfxZEj46uwUblMSjon5VX31uRuGeBixDw9E7C/dscHsqB2nWXjG8lgc+F+Wz4Kwl1W+OOV48slUeUKcsZxrnyRzeeHNwAZs72JMRKSLiGkZQboJCYQx9RTNlYOE4Z4ZO2q459C1IrAUPwyXyzu6L93UPphNNT4GGl+nNsxDvxPS/o8eYHjKyn4i8i5ETUHovrsXfPXLx/iNl7JEi9h7GZiHWGZwkt7tcEXdz1IfynyhTn5EFWF+0+POaJUrvwCdOR3TSDcbDL2jU22RtWs/NbrUp7k9kaP22hGzf8if3M9ccb8p3K9SU8EV+QqmOe8s8EJuWhOfjlneueh9SW2Zn8LjS7Dp/9QXny19J2Mgs2Wv46/Yn8b66zhjnd20xO0v48S1bnILQyLvXe4TmcGHrohQ44WI/hnMKxLsMP0FwNqTGl2O5Yn6D6mD/zTztdPON587jpFhF/bd8Di8xNXsZXYcjHA/s6fKufIZ8MDj7LKm0DdRzAdhluSAGP2CMel7S8N2ihDhBUBgAjEwE8ylDk13weYpnqhkldth9AvoEilyCLCZvbIXo9LMa/a7XkCzWYOzcrDkKWq5eKyg5SgreCY4vrvxz6DA/0mBBvCjm4hCxJ9vzMwoEWhw0QW5pDyIUupVkvxOAXabX277pH6xIsmP9MWNzRTWrt7PcN4T2no9445N/C0OCBVBcIaR+0EcKeyqWgcY02jmoUNpZGMeMFtQVRvglDObtqMyjcFEjU1VxNRQKYAQN98skEI1t1bfr9d9dr8zfpW89Z7T6NDXpoaqrpXC41Sud1klY92fsqcsMHi9E9GTLya3JIeltdsld4UFszmvOsSQz+4zbn9McQhQQ3x1P2FPnDo2KTneKJ/6JZUbh0WJPOVyl7pRqpp6agXiv8SOkbi71ittpVIeSOH/acNEBL4uWSUSFZcbeoTYaoNRUUaZX/uIkNkVklAFUuTFIa1ibLaI7PYZoIQfuBWPKJs063zcsxofz1wHJrvCLcfv9qiVuS3pTn2NvHgjuCZBK8xM+37pkzY7C937QLGvxGTdq8UarFn1Gv2e5K29DJIDvZjeYYTx9tCXli2pJVyoszyosVku+uJFYmh6T0ztHR7mxbCsrziCxzWVKRTS1ZqA3IeRHvJeh7nVOJCMEJEmBPtuiOcK1ybeG3012ra9rcXkjkBPUra7FXaXBxjtScpUXM3JnXJT3lik2I4U3nMzGNnqhGSWJ2XCrvbeiqPz+j5wssWrvwSguE/xZfTyKKycMVsP3rM+s7a+tVrnPRia2524yMZRJocT72zds149kk3zMJrnJ1rCFjWbDlnfQsM1DrIbtxuRfIDlbsrkw3lSPo2eZ8ftlfOfmTNFqrLy1LwjqI0CMJIQzRUCko0xXNjlRFuueeE2DrO15opM0T6D7Qri9kR9A2VpDie5B68aSS2d1htOvA70xpEn1CDwvZAObN9bZW90TORgvbtCsu+p/igK6wmlK1/d0oU7ZmDbCFKN12z6XFKO1dDApAc0Jkk95+6gqZl+pvkPtEZWQVZ9+YV8cn7hqeSveV+JUQiNrfiluKLQsOV+eZMgmzcP3RqdQZNMjxtwNYoA9Q1wkumVJBomZqRHbhkGNcqgpUfj7PgSCZPYZYha4xqXEhRgPlbguc3JfNwkRgcgjg+fLt5wnkXSt2DiUA8qudLwUgEzexFsejtqnNstdwXM87DMJBS9u2CAD17CAYXj8QMGbi1+xO7ziwjlwmIvESrs8vkZj9EbJLDFlo7mHMHIV1os0IryZNeoVOxl/xXoSbRGmSGUysQM=
*/