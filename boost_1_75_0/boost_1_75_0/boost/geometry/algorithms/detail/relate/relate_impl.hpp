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
fG2xc+/JQOgviYfUoek8yBbY7HPTDlgZ7jikBNhvuOW70P48YUceun0v5nT7zJdYp4RdQtujjM3lD/DEYzAgq3GPraUyA+Xsebb94W2qzwmdnRK2M3esij2QMhVe1Z28c37ZDQ4mfAdKnuKe7wuOXQ7QZkJn2HYMpJa1zq+TQqPEqWFIL4VtHQDRxfDjdUsfCvOPLjJKfGxKd8oJmK7lbQAbeUmfbE5iogxuEPq+G6J/qKQpPwaM3FzOnP1ko9PSF3wUiswm3cFyVr/8jpGWkRRkXZoHuDoL/W66YHjIV2GaumuC/At1P9DCfGhUjXZ0BpWJ0tY50oHh5ZsuZgbYYuw952DhgDlo++yhpDckb/MhSMw7UkATOl93IuWUvtCcHXJ6oQfpyCgCkWLTM+bPCf9Vpbls6CFnoaPo/Muc/U9Ad5V004eONbawY+i5IXH820+bMoesVW1bitkM8+/mofIIZU4qfnbRkBcFw5OmXG10iqxVVSL55h2ic+2IT6T1tpVmK+sFM8+zCVlzX6xsStO9Ux16efmP4JUk9ArEkQX3TupYeLAZ/oTUo2okk5H0THACLbLhGi6xjHGiZwu7MxAZfF4VFTp5h7LP4piVywhkg3nGJWQHDkx8vsUvpkKXgBQS8pfNLsz+4m6+/vxmgOsuktQc3RogP3pPrW0YghztY0RVx2fsSMjKsoQ3Fqpo1Tp2X0DnybFs4Mv2
*/