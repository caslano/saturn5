// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DISPATCH_IS_SIMPLE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DISPATCH_IS_SIMPLE_HPP

#include <boost/geometry/core/tag.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct is_simple
    : not_implemented<Geometry>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DISPATCH_IS_SIMPLE_HPP

/* is_simple.hpp
24/i6B87e30FXUnMiHten+Il7JQZrQ71DRRymXI1N2arA3hy4btVxwZFP82JeGH24p8+W0tJu6KYc2r/xgGVspyxFSzAZGD68BwfFOtRHeyM++Hfzo9RJDjxnY93xVURrQbQMFnU5s46IShWJR+uMfj9fv7cnZ3suk3kw7W7D+c/eiFtHgON41P3OrmcuNnH+VGWU17/tXs4OAEftpecHxSX0by5K1pJTphe9QrQKENUCV9N
*/