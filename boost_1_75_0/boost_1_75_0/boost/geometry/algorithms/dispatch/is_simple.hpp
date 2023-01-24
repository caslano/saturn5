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
EnKkZyvQt38BMwSXdlg/KS1zDodiXu1j05XiYYGG+m3RUU5f8s++CYSqDKhgRkcpkTPUkmAZYc5mDnYuuXl8Ef3es+ZITvVrfgmdLJt7FnkwYXHTMaa0GXvJbrxGpnrh88n5XDD/2PVqh19+fHjFkUT9z+dlnyJWW1oR+Evtsps0kjmCx0ANDQmWM13yEm0S+8p5Yyc+9hrT4NV/oS1zlRDGhKdw3ltanzaO80YeV9EY8dux3bnF6VxrwTPaNz7l2A+v7igb26wRRMTxFb9Z3s7bbixFxhDv3GpuERg8pdMu03lDuMBkYtROtZ71Mew2j5oaSbn+lkqb6ywU4WXf9lHlkLKrVi43cDFSLR0BGYwvKhtImg8ZumfKX2oazQy4zQC5QRbGyn2e7+SIFob/ta4VpGOqNrevTEOnS7F6zNUUv52aTat1Tu54PSJYS9qfdA1y33azaioakJ8xt3kueX8Azx45XZaDKta2Txvmn+zWci63KNLfMpRqmMjOA+otu2m9kbDq/or+tM9odmAXEzia1nqk2gILViUUov1HBTxCuKtn+o0zIOlJ4ERoUWJJOcwQOZejNnD2LcKBkWqOOqCICJDgKtiSzdyTBVYFfRzWjKu13MdZ7a5nGjvps/kINvRmH3t+j5B/PRRPhleaGvIWMKkFNjAY5RjnXnsN3jIEh+tzm5gOsFX/+X5iQD+hxxrV42N97g3XzZFy
*/