// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_VIEWS_DETAIL_BOUNDARY_VIEW_INTERFACE_HPP
#define BOOST_GEOMETRY_VIEWS_DETAIL_BOUNDARY_VIEW_INTERFACE_HPP

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace detail_dispatch
{

template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct boundary_view
    : not_implemented<Tag>
{};

} // namespace detail_dispatch
#endif // DOXYGEN_NO_DISPATCH


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename Geometry>
struct boundary_view
    : detail_dispatch::boundary_view<Geometry>
{
    explicit boundary_view(Geometry& geometry)
        : detail_dispatch::boundary_view<Geometry>(geometry)
    {}
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{

template <typename Geometry>
struct tag< geometry::detail::boundary_view<Geometry> >
{
    typedef typename detail_dispatch::boundary_view
        <
            Geometry
        >::tag_type type;
};

} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_VIEWS_DETAIL_BOUNDARY_VIEW_INTERFACE_HPP

/* interface.hpp
tq7CHwVnPZnL1Ap8UmD9clMD2wXZi131aBT+2zrkLTbBC+8zVvz8fdPgo2XMgfltgJYW3odfjX82+0fm+yq642xDnHYmsmI2fI49G9UDGZMIvTUFVzvgS779yXR8F+i5+d+QDcDwO+IAX2HHdAOOu+Czr6DfnNPxZ5GLbfBhqrLw57G/Dq0E7hdhO77NmhC6vANzj3gF+cjcU0dK+1KIY/hEnWdhZ0DfxT9gS6CHkkqIAWQS
*/