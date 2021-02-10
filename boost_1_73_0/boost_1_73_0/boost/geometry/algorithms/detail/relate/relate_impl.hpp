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
VTtMk75KSpnOSh/V/6d92n/Tnzj2D13b7tm9+qJJzBdRwu9VNRnbnVH3tfOqAzF7LZ9mUdxU1csWy9U2Nf/IiTj0KmNhOk7JnlJRtPRQYwv5pyKyXDurhcXUgwPNkZc8tuVZJrZ/YdT31tdE0lIiyoZO9Zp6K5PQuVepumF+1FehulFT6g3omKbcsueTXafTo5QS1s5TOweJXxZB5BNVncVHTsDDzeSnA/BCzblLMGBeWMM13RH2UCoGUREIq0FYFWp6oblu26WCkLFUo74WfEFFfmpbt7yqKhFVeCOzVJRxh8alqN1meIaIWMpHgIWZAL80VVmr5DVpc5TM25Ps1NzqnvbtweTdqD+xnZfD3nuIANSukkZvQEdqvsotbgmfyaXiZoe0rFbHxDXM+XyiiSGbtisafPt3GluD8hbHD0zyFjSr3RIH32TqdsD+loKu7bKaR7cls5LaIGGYF3ixqDYwaKxTkLx9Th9XzyDwTRc8NlhiWL/So5yt3ogY8WayAHv91g1WnO3jJhVRMICIbFsDmFnpDQYtpTBn1/CpqSLwDCk1Jgl8pR2L+Bzc9+dbuio7p+ivdjYsZUhmyYjutA/koWkhr5C3AiHqxFHJDUKzW1zESIXyaUMQozY/+j+nzdrMz9xwkS33mMZJ
*/