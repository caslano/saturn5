// Boost.Geometry

// Copyright (c) 2018-2019 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_INFINITE_LINE_HPP
#define BOOST_GEOMETRY_GEOMETRIES_INFINITE_LINE_HPP


namespace boost { namespace geometry
{

namespace model
{

//--------------------------------------------------------------------------
// Structure containing an infinite line.
// It is written using "General Form", a*x + b*y + c == 0
// Might be conceptized later. Therefore operations are implemented outside
// the structure itself.
template <typename Type = double>
struct infinite_line
{
    infinite_line()
        : a(0)
        , b(0)
        , c(0)
        , normalized(false)
    {}

    // Horizontal: a == 0, for example y-3=0, y==3
    // Vertical: b == 0, for example x-2=0, x==2
    // Through origin: c == 0
    Type a;
    Type b;
    Type c;
    bool normalized;
};


} // namespace model


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_GEOMETRIES_INFINITE_LINE_HPP

/* infinite_line.hpp
22E8DCYUb6fNr+Z4HCiMJZQrW+Q5xU+VYwaTu0Ebsv9v2JBkZNfuRl1jUdKLmS9h2GF2GKs+eKz+Y6/bbzsnrNtptU96bfa6e9p6z7LHqU1Ot7R+PiYt7XjSoKxOVzJ27WiRTlvBsH1ydA9++ewb6C9Qh/XPsHE7+JJBeNfjoQv24ySZjfCXONJ1h36RqG2+JvnXGppUi7t7AxznocB0YB4fPRtYhTY8gzywrIbmt8wTsG+KoZgFTj1vjZGixefCochhffd5ED3WHSF8AXKiicjqWJnFpAij/dWezcHy0I/W++bwpNcbyiP+R50enQUfNt/02+fs+KLb73Q7J+3haavf7NKIwc7zPfjbkX/P4W8X/n7W2vJ/uz/tiXlPjlQ9o/75/nnN1vvh69enp13Ab/im2e217wqo6AlXtOO76DAYhU5GPj7EbYRmFHaYSumKT7lAqk8mbp9hCXVrv/BcyxDn5wpA5cdRmvKsDwarg6mYproWH6I+NOWzVbwyUUoXVQFkQhMGrMyz3Ci/32TNrLr2uzInKUAq6qNzGrGLfisflG+lvf7Y3fsE4saM341VNJWKpPdsE+GUU90JoMsoKyHFCROsCc41qaXRDUxaPN/9eYc+v+f6HXMbzNvezt5Oded5dfdntrPToP8L
*/