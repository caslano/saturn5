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
IPXYKKx7kaQnqd64t2/7heI6HlLyMTsarllz7EhH7BdnA4XAYXtSOG/ywV5ctfwwLa+OiojcLgw61FtZ//r/rSfnSaqIqKy9R31ZZoIm9kwj+aDJ9xqlGEWdApfUi3KhMSx9AEuJIZDUjRHvJRc5zr1et/BOX22aUM2ZNu6j/xtVZYKjKG7/qg5Y+NSt+jiEUwmT/ZymydXu8NucACn8NPcNsPrmTGt9kNFiqlvSxI8h8Vq+4qUAvWkOSMQ/THvV8lwTNp5GlDqHzTiiEQPi1y1zSgd9/7bR3DEQD4aAw6Xby/OVflDUmFU5rHQywGtlyre2Nf64u0NDlPmeSV9SrPOtlrODrqN9obwY04HTzK6vtLf8Utq+AK6r4UiG2h3tnZ4/OoUpuhI57DFa1iJkV5f4nxAIUJEOEDevSLau35aJpHMPu5ncP4ZEA0Lt6ZQh/lwCQC9bRVFdvvd7XyHQGh7x25JpH6maOyBs6Rub9aoejy/XR+nQP2XTP9Mq7i+Xjm/pynSib0Ffnn+x1dBgM08zIq9PWuzRX4kIXroV7T5GwOPf9LIpvAUsKA==
*/