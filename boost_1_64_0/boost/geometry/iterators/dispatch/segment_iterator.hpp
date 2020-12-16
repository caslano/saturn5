// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_DISPATCH_SEGMENT_ITERATOR_HPP
#define BOOST_GEOMETRY_ITERATORS_DISPATCH_SEGMENT_ITERATOR_HPP

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// dispatch for segments_begin
template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct segments_begin
    : not_implemented<Geometry>
{};



// dispatch for segments_end
template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct segments_end
    : not_implemented<Geometry>
{};



} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ITERATORS_DISPATCH_SEGMENT_ITERATOR_HPP

/* segment_iterator.hpp
sXp5BG3SvteVz3Ns92muOTQnIpsUzT3SfMmbR4jGZKRbu/7PudqvcWOsZrLC9SHpdfOGa2V5uDQJ+cSufzPfsb0sGq6a21G5OFzfsHB5EtbPcrXvkXZtc+2yylqWlUiKtm3/nKe1Ob3a4ZqyyMfBoOcMuWXSBmm29sZvebi+JFweHpKEOLbjX8+X9Wa6ySgj3LhdK80mrybzKPmXl8PX5qrluUNyhiVHO+MCx3ZdjDZpqaqqsrSEWjwJYW3X/5N2la92bt7IJGgrfdnNkqZ7tUvD9cbLi8uqg45r2/8r3Sl+umXB6w5353pId5GfLsFs6no13IJ+hjy3vr9IbalDPUNusPp2/qP0x/voJyN/u7pVFzu2xzTXzT0zKW0P2/8t3eHNdclayUzjF5Y4tnN8dJOZxvdKd4GP7ieVxhcsUDvI5xk+iTS+B31z7KOfjLRmxz+UOravjdEtL3faRsGOCXA1d0hzVTNNtYkC1XTDd+RC1Zdbopqa8xnpnEnaWKkt0q3y6s5mqVqjGqym69c+ZXoX9bbpi1ktPEnrELt+XS/dpi3NdJPQr+j6NbNcfo3XDDckcV3LddJd66ebW9JQVR9padM9VV67tLIm2Hxk3//DStMbfZ+hYErA8Wzbf9Kt8tEta2RYeGT5/YbkfOdJX+TY3hQX7mbE/+JwDUNNAh7LZL9/SHtrIu2Av3/Y9Z+lO+CuZrpmpGekXgp+PWL7/X+x8nTzuE5C/7Kbt/ZL89q4cK5mwWuWjHfCmzEmdYF/0xvk+rtCe5bE+ZuwNqks+G9Btv0n7QcSaAftZzv/oVJ9FXc2160MfHyLXf9Sml+Ni+vFn1g5OucSx/aKO32eIScymSpYv7tpbLd0r/TXnTihhN8Bh7ud/7FEbbAtftrB1x22/8/VbZ62k/DtyPb/VWlf9v+wdyXAURRRdBJQg6ISDxIVYkSl8MIQYsQLCQlCNIQ1Bgka3Wx2J8lC9nCPEPBCREVFRURFQY1CMEDEqKh4R8Sz8KY8UVHxxhsVqyj1Te+fzswexKPbq/pXdSbT29Ovf3fP8X///j+BV93PAJxe4fuyzX7uIOzbUmCLfobkE26ej96TCf3s0bE5T495vNZ10b6SzD5v9xHfKfBlPj8P8NN7Oim2PHvfFsL9sT0RV/Y8yw5QDJAk2DLn2XzCvTLhGeYOBKd2vahF2znz7/8g6fYT8F34VKgX/q7k+18Jd0ZbIq5/CHuIYrTrhO9b4Prfs+idlRSfLJ8iYmVp/v1P2HMS7i+yO5DwvcD1vyH6NozHlmTzwPW/hHtdPK4kuwce/4RwFybFhfM3wToEvv4Zpv3drRbcsSWGRC38+cnXPwmzIA4T2gPhmGb/OiJkxx6HWQvfz5Ml6C3Me2gt4R67xIYr1Qcw938WpRh2rYnYsLLWRb8rzPFdRbgz7LhS/N5y/59NZE+dBNMnaU/3YsK80o4pzdepidtvCq0bJJlTeFII13Hy/S/AZcck/LKvAF2sfzuu/2omt2TJcYX7njBxZxLu59ZvrVGxz/nxQfF+h0zcrYS7MQmuYdUoq58jUyk+YhJcQ40ty5ZgE+HeaB3fErYuwbpZtN2EieuZRj4K7kjANTT3paL1izz+BeG2tybFlbJOwfd/nE17yRKxaWqJxR1ovgcJt649AVd4P/P33zkULzeRV9bHsu6jhwn3pURcKWPL/T+dS+urtj4Wv77H33+EV2u7f3Tpz8d+59GeVzuu9OfjPMJtsONKfz72Pp/sIqzv+2K2hirlnuX2n8Blx1Yrrvi1W77+QXh5Nj5LHWNGVbDIm426vz7SIJZXEzsynXTirYnY3iaCljS+mwh7RCK2FPnA5LnhArIbTMQ=
*/