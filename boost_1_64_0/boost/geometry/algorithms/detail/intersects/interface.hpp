// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2013-2017.
// Modifications copyright (c) 2013-2017, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTS_INTERFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTS_INTERFACE_HPP


#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/algorithms/detail/disjoint/interface.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace intersects
{

// Forward declaration
template <typename Geometry>
struct self_intersects;

}} // namespace detail::intersects
#endif // DOXYGEN_NO_DETAIL


/*!
\brief \brief_check{has at least one intersection (crossing or self-tangency)}
\note This function can be called for one geometry (self-intersection) and
    also for two geometries (intersection)
\ingroup intersects
\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\return \return_check{is self-intersecting}

\qbk{distinguish,one geometry}
\qbk{[def __one_parameter__]}
\qbk{[include reference/algorithms/intersects.qbk]}
*/
template <typename Geometry>
inline bool intersects(Geometry const& geometry)
{
    return detail::intersects::self_intersects<Geometry>::apply(geometry);
}


/*!
\brief \brief_check2{have at least one intersection}
\ingroup intersects
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam Strategy \tparam_strategy{Intersects}
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param strategy \param_strategy{intersects}
\return \return_check2{intersect each other}

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/intersects.qbk]}
 */
template <typename Geometry1, typename Geometry2, typename Strategy>
inline bool intersects(Geometry1 const& geometry1,
                       Geometry2 const& geometry2,
                       Strategy const& strategy)
{
    concepts::check<Geometry1 const>();
    concepts::check<Geometry2 const>();

    return ! geometry::disjoint(geometry1, geometry2, strategy);
}


/*!
\brief \brief_check2{have at least one intersection}
\ingroup intersects
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\return \return_check2{intersect each other}

\qbk{distinguish,two geometries}
\qbk{[include reference/algorithms/intersects.qbk]}
 */
template <typename Geometry1, typename Geometry2>
inline bool intersects(Geometry1 const& geometry1, Geometry2 const& geometry2)
{
    concepts::check<Geometry1 const>();
    concepts::check<Geometry2 const>();

    return ! geometry::disjoint(geometry1, geometry2);
}



}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTS_INTERFACE_HPP

/* interface.hpp
QrhapjcxppbpzYSrZfp1wtQy/SZjapl+m3G1TL/LuFqm32dcLdMfEK6W6W2MqWV6O+OZZfoT5qhl+jPG1TK9g3FZprnWlHn+VZxW3lA4XvuG/IXSL9BtdLxG+CvHKe4uF/eYyXOlVJnjuz/vdHi9fOF8uZH4IkwEsh/+rcLB/cBleSby9ykO3YNsvJJsnz9GHGxUE+V7F+ONWXoriP02EqPvGJ/2XyMsOc803xBx/11yEitx+LsjLMmcPJODwos4lZJ8qynGZ+t4m7tYxocn7JTNS6wAbeuBX/kAyavBf2O4PeYweKUoy+ZeEY+yLjkHOY65GHy6TKkSje9LAqexRzb78P6t+zEuqlv4TumhKqe9+7e4HZTr8XrqhuNb+1KQunOm5NxnINJciM9ubOI0RXkfjryGfTO1CsRQQB/g7XaEyjM0ttuRMYeWZgxNpHlUzENRUpoYS3yaR6o80MS980dncvi9Msd9cCaX3yxbmyveYh0b4vkMO7d5hU8dgGwTyxC3rKDS4LKtHhvzDM3bZ3mIs7FFmRwXcgJDU1pqXN7QLp6HKDgbmdM7QeGxgWGv1vE54/q0VypcNizbdRV4cswODcvtbLXCMzTZ15yS4rBx2SZrU5zQuNlxuQzIOtGtctjAjter8tjAa3PE5wws01+n8NnIXG4b1sZjtTSztOHDdG5gw80Kh03N6Z4W86K63JUdpze5i+8RKkeanNN+VMyN6vXafPF607u4H63y9fq9xXHHi8Xy7JwfKhup79p+z4NH2VzkXpyfq01OBr6jQcuhkZiKsFqrFoM3VtbKORfB8rt+yOPY5mlhh231WH16KHVP5va12jyMwlPawB1n3pzU31vEFsnALzUCnNx8HNbZdJTG777+/sHR0cLA4Gj/yNDOsaEdw7xu7G16dhaXpg38norljQ73mAIf7B/jyBzn3IgT3x94fsShhBKfKrBPwt/5IPDe3La/c7dylnZGHfOfKNq6ufuMbLgbu+7Cu/4nBE+7g7yYwmlChl1V9l6Azoz0oOrcrMDLKTw9Dk6l8SrF7+w+reHUB/s4ZiJO6KOppXCa96OCijgutBxg1RIgk02pZyONV0M7zEc46eDq7b7/knYl8HEWVTzg7Q+xlFqxYMQIpRRsc/RCREnblAZ6hCQtVNB1s9m0a5PdZb/dNEUR8cYTFC9UVBBRFBXxQgEVQRHBAxVRRPFCwAsUvMDjP9+bmffmm7fpLv5+JCnz/8+8mTdv5ntzM17H0bsZ38DtareUNQMubgMGZpSJpbNysad931S78/6MQ9S3Nyhvfh5avlP+UoeZ0QaGE9k7+M4IcGz7EuvbZ1oMYfSmrxKOl4AaxVoK+zTPcjgpAb0E7SN7FcLvs/swLmy7DVVr8ZrBa6U+eM42871E1OB9nNcBD+ceieDs7WypEzuIwR9qfxEHfWANBxoq5ZSyMIOznXA6Uv/ngjdeweZ07CTvpSGF1/PbXT9q8gFdUy45D++KxlPhnanvifBHOk5KatOR7s9Vdf/eJcGcMZpKvUD7hXQ8KZpvb3pj3R44NNB3nPcr30ioKfATP6BwqBbYVj8UcoJ32C5iO+cb+EVZP+xwHOlFl2E5PC7ry35LS6h+e25uYTMOpRX5FxdHPJYpy3xJZHe0k0f6kx9Vx9DxN/NSnWe+iW3ON01P7I7s50Oq/XwirA+6iFzgn8zowTH8fUKuzZBfZNzV7fnMW5eXh5zSuHjr64oQo+5NyP+cxf2ifjn8Ln9BwbHg7m3qSotTw7DpC5v5ssNRvqwM1y9ftYTfwkJf33pdTPflzN/YF7lM/a5c/xSaPzZxrBvnsVPm0jykwHz+bnqKwWp+/1tnJpx8Q3I=
*/