// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2017, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_ALWAYS_SIMPLE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_ALWAYS_SIMPLE_HPP

#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/dispatch/is_simple.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_simple
{


template <typename Geometry>
struct always_simple
{
    template <typename Strategy>
    static inline bool apply(Geometry const&, Strategy const&)
    {
        return true;
    }
};


}} // namespace detail::is_simple
#endif // DOXYGEN_NO_DETAIL




#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// A point is always simple
template <typename Point>
struct is_simple<Point, point_tag>
    : detail::is_simple::always_simple<Point>
{};


// A valid segment is always simple.
// A segment is a curve.
// A curve is simple if it does not pass through the same point twice,
// with the possible exception of its two endpoints
//
// Reference: OGC 06-103r4 (6.1.6.1)
template <typename Segment>
struct is_simple<Segment, segment_tag>
    : detail::is_simple::always_simple<Segment>
{};


// A valid box is always simple
// A box is a Polygon, and it satisfies the conditions for Polygon validity.
//
// Reference (for polygon validity): OGC 06-103r4 (6.1.11.1)
template <typename Box>
struct is_simple<Box, box_tag>
    : detail::is_simple::always_simple<Box>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_ALWAYS_SIMPLE_HPP

/* always_simple.hpp
fKleFBz9amlcjwt5ae2ocTk/elzsUpouFYrmqDvFpXvUOF64jlrfT2Lh2t2bkW5C+pF54jcimvu66KaZd20zHnXXLdUvXnc2P2ZjrrJP5yp1Tus6yB0a2Jie6TBP1g3RQ3snmL64swknN7RlNe6972iG2wf9+Oy+xAfWDJ0wxM/wOc4NIUdkA+1K59hs8DjwRolvGhgdWdM/NJA6RLkR4wVsWjPg6/RmyTUPm65ku/6uxEiIz+ctEhsO9dWUk97AzWWJObFOfyRwauVYQBHxb4twfNqFPf1U4sbdXqvlVedxmXWOqGMv72cZTraeHe/nCk/WdVdzns0Wj+XvzHCa1bl/cyfDd/Xu8N9EOAl0eb8rg2frvzkvtIGuprxY93dnONIWHOdelQN7kHvhu4izCxMcRbxdaeuvKT5DBF6/WRLgQcH9+k3I4cKIb+PWZ2U4JMfr+D6ZRsaIpI/zlwxP67ceyHBcdpz9/C3AdeOR35d/SL41HifrXxKzgmR+Hw7wYVV/HUsFJzQan87eIUfV8aMlhw3G44+NcRgLy9BxKOgk5hwf2AuMjm1qVs5Mpr4fL2XFHZXnPVHjKXoelfYVdlZ+/mmfKK3YzpzcfRWu1o/OUXgue72WMzfi6DYXnJGO4pDdObnzI5yEyjIcEHGGVR0vUHlsg453UMxT66Iz4rEtOs7BEYftceEeOWSTrn12LaX7P+kgT5IP3jWQWLGAf3G8hRKrJflWx8bO39L3Y/93z2uIKJRdQmz5znon0wxDYx9+70O18dSRpD/SmtmMQCd4+SyzihtFM6c7y+Ha8H1gLzjJTqZk72/ry+A82uS8row4jSnZHo7K4DQSZfzoDE7uc2v37jjd6vvc95G65XcXSC80YWzUJrDnC4zUxX1wv8BYlYyvIRxzHvVi4uuD8UXPIHy8iNty4fCP5cOx0MBSh+9MbUVigw6ruEllrqMTLIamkD5wtWZwaP3AcKpK7zs/ZhFxsPGgQG8087j0RIpPqpDvvYtwmpflOFtk+xb6Oynb7oWcJU/t6KDhOWpMnDvYhjhp26J7IDzX1Cvxk8bERGmm3fZWqWv3z3aq7e0UUbe+wC3uEXDyqjtXKfKeqdrgC0kej2VW8ZgoF2G5oeHBrTnzbll2X1I+U0fEZ3+7EOFaepyvoqw/IvtvzfYY4y+SfPN8Np7Zri+4OyVXy5xcb5BcUViXVkXHZR69Xk6LuFo+mZ9EfD2vXWJcgjmYKFVjVY7z3SacCXHGowG54xVjWtXg+7dLhFMUyBZ6wBzPrLK3E0eTzW+36xxohlqH45Wa85Bee/24KU38jVypttndwrbZlQWuzQkovvtLM21DpuE4Z2Q5wTyIPgbVZJ0p7UcQ2OfT/ELdvz0r4oXp9bbAM489j5fMNab5yXb71aSkvb29+lD9fXnKA78vz9irljKWvWv4NQJLr7Rt0x+YgTMR5/E4NY+vI1k8L9Mh1ouy9U8477WPxl1inlH1gdssR74xE5djY9Qe1HLk+reczLaslIU5nVp5mEBpaGXynDbKNb1zYkq9d2XkUO1+mbdC5pjpJ7eeYCR6n+YcG67NI5wbYeSLRXGVeT6KyxhFZX/l7RYfT5KObJgZivh7yU3YZGXMLTX79T+Ek1+D+8eA0bhHvNGdxWvhuOi9wOklhRxUSWtwTub76bsAVdGNzy7OB3w4+48y78CQffHGpQ8L9XahDUexXEI+nQ8TVuod43Q+4sNMOsz9KMIRaDLk9XUphwVjlPkUHtVlhMv6kndpA6c3copjck/xJzl83Dy/Kv3bTwMjGzeVw+GfceGUmE/rsxxOiYk4n/cYKtLeNfUlhB2CBfUu4JfvRWHX2rD5Iuw=
*/