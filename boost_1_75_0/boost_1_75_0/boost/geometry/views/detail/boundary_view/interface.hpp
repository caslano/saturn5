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
XFkm0xeDcJG7ht5I7vmu8BgDZ/GAe7qFR5XTihUDYkIShHIPS7+fI7BfHt0Mf17kcqZFdJJuHxYSzgBlAOBxCx/vztp2IlMt18/pVAYkI1QGW4HlQGHmR8TXp+ytMcVbY1MGDGy4kxyIBHas5Q9juNWRQBLKCCcentfkGTAaEbLrZwX4GWN8ayHW0Sk1torcR+Znd2waV2xRMf25YWpgRPL45sy9+dEAI4BGMx9yUBVwFoPA0H48+8LsP0jwrQzUkM39stMK7bDChD0HyUo0iZNrfNKVP208dCYbMNdW6WlQLubXBCqEoDhIwYmtFrVzkeJEkLHn8NhwEBVscclKKwC6UxCus4ms4jmHOuHsQWaJHOkOsJ2wwjFe55+y65LIruQ0zire5pitP+D8+YgxLpLHj9mD+67P+ge2kv0H+LGeO8ITlffkDPQAX+zO0tUpsPuxYlTtQnIH+Hr/bg/594Y9GReTBsP7v0jNL/QfGzbS6Z8N27X2TUSyhVzjYr2yQiPzZac8k7QS03lG7IKwvpx6PHOa/nrFcENs09x6Nqu+i/+XAhGV8WFXRpY3rp+xZQ7xf9Frdfa8W2N4hwy8+5uq6dbew3tsVl59iGOI3j725a/zHWX03iI8xMfgw8/5nZUmfD7e7n1teW6JvKQT8r/X8aRF6Ggn4dVg3Nm0hAm2jLwLLvb4Ss2AtGkxbIwcBSnmlNxghmLuO0Rm
*/