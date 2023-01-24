// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2014 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_HPP

namespace boost { namespace geometry
{

namespace strategy { namespace buffer
{

/*

   A Buffer-join strategy gets 4 input points.
   On the two consecutive segments s1 and s2 (joining at vertex v):

   The lines from parallel at s1, s2 (at buffer-distance) end/start
   in two points perpendicular to the segments: p1 and p2.
   These parallel lines interesct in point ip

             (s2)
              |
              |
              ^
              |
        (p2)  |(v)
        *     +----<--- (s1)

        x(ip) *(p1)


    So, in clockwise order:
        v : vertex point
        p1: perpendicular on left side of segment1<1> (perp1)
        ip: intersection point
        p2: perpendicular on left side of segment2<0> (perp2)
*/



/*!
\brief Enumerates options for side of buffer (left/right w.r.t. directed
    segment)
\ingroup enum
\details Around a linestring, a buffer can be defined left or right.
    Around a polygon, assumed clockwise internally,
    a buffer is either on the left side (inflates the polygon), or on the
    right side (deflates the polygon)
*/
enum buffer_side_selector { buffer_side_left, buffer_side_right };

/*!
\brief Enumerates types of pieces (parts of buffer) around geometries
\ingroup enum
*/
enum piece_type
{
    buffered_segment,
    buffered_join,
    buffered_round_end,
    buffered_flat_end,
    buffered_point,
    buffered_concave,   // always on the inside
    piece_type_unknown
};


/*!
\brief Enumerates types of joins
\ingroup enum
*/
enum join_selector
{
    join_convex,
    join_concave,
    join_continue, // collinear, next segment touches previous segment
    join_spike     // collinear, with overlap, next segment goes back
};

/*!
\brief Enumerates types of result codes from buffer strategies
\ingroup enum
*/
enum result_code
{
    result_normal,
    result_error_numerical,
    result_no_output
};


}} // namespace strategy::buffer


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_HPP

/* buffer.hpp
SK0HjlTm3dkbiAjLpi/R+nJsvDqD7w+OIDQMdWCVaYIh3FBIF3jRYSCAIe/+E1Y7xLzj5Q3Nq8JQ4kz3YFWGXrM1q0WLilN78gHXs43LQJ9VvAOFuw+ueSn8tY37d47sRDObONzTDGkhPx2OR1sWJI/qJed/O9kFV7ykhnB263bcdTwD7fMAasYbBmojNJrJp1C5Wg/okIfknST0swNfCZtDjSrVtkw18s5LWsMm8WbfL9uLnoTMt0icGddGQXbR5C0m15YT93/2QiT8d9JAK9Jw8UOsvD8ARBLyvHDaeQ+e44VC8QPxUkvBXak/7qgLn9/Fz7yVryiel2KbIH4I5w6Rdb8LUdCExrgPlzTfFty0eOWeDgGu+w0TXRHKiq41BaOYCZmpordB6JPy4dQFkiWSRQxP3GpTsl6EjY/Yk2NH03Wf1xSD40BjWECinkh17bg1VpXkmeX9Exg+jGuDhSa9NJC05BFn5N7FH/eL91SApr7CWTH4QMnQofQWqt24E35/ppdw9XHk5mXuhAaUF6YPYzcCzAXCsC2APJKeHR0dmE2Xn+C4JbpLJrXjnKPoRzuu+67MB3ue5HY4T1QbZwc4sPcfEApw5tmeMEQ2SPYkMwYIDy6sm9I/cIR5wzGBRBzG++Z/KuWr9Luq4j1G1/UiV6iv1BYlMLNXASmPVEdKIw23y/tQ8pxC9Q6nfMX3V3C+0RQiQ2sko/CI
*/