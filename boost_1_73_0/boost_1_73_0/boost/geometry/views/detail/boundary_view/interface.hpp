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
pbLdKj04NbuAvtgi/wywZmByXaXKLmGrP/rIr4K32E1vKsbY7JZ+mZSlJ8P5ElBpMsFy7HQrVroEm2W+r06T8nFhvQgdasPfeHyWkf9AA0HXJIacRPc9eQCjnUbrLz0tUurXd6unRe6VMqX98FBWvUd159GQmMlMCYgeZ85tFusWS47ezjf6CuDjhs+LM6eM7hSZilewrituaDgctkFvsC039nGXiY4axYm6b8NtEPNzunDYg9rFXzHVj6Pvg5OmrxXdlau4eXlEvYzIiBppxIISEpvFlhSDJp4VVf7FM3nCdDnHZ314Sy+6feCNhxfdztuBIn9A3FhS8ew8/Ney1chFuMDzJcyZxvb+8mqHskbMUf1qd2q1SKu3QHKwFymwC6u3o57j2v4v7FIFlfDFRJNDzwZang66ruJI5wYUMgM2XkcfOGoBnhngB6GtfXCNg9e8iulojtSVRz176KRI4gUpX/Y3nX/DLLRptxPdlLpwPEzQk5DCIRTsoijZIBYJUvia8aQwLDokJfVQDSyBATTT0uz4mkAVPI11jp/wrIlvHi0a23j+5ibR4B2a4t7qjSV1HmH9BzaRzGo/5HrpxqNHqtllo166IY4zc+4KkaT0ZUIvEdGsM6diRL1fOr2huE1a6Krz4fhcCREn
*/