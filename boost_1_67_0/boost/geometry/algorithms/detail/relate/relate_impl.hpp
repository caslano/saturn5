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
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
*/