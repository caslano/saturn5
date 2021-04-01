// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_DISPATCH_POINT_ITERATOR_HPP
#define BOOST_GEOMETRY_ITERATORS_DISPATCH_POINT_ITERATOR_HPP

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// dispatch for points_begin
template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct points_begin
    : not_implemented<Geometry>
{};



// dispatch for points_end
template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct points_end
    : not_implemented<Geometry>
{};



} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ITERATORS_DISPATCH_POINT_ITERATOR_HPP

/* point_iterator.hpp
9J1vvH/93RKkFAiy/H99RkMyM18l9dsEEYGe2AbDemW6P5YZzSKDLlDiyuKcaK980tK8wqe0AtXFBZ45ML3Ux9vZlXCxmp19h1Hz/eDCUgw9t5VtRxdeEg1+blMR5sPw4qMM63D/x32t/BwuCKZ1bf7KG8XdLOLEFp5D4K1fhT7qTSm6JZGPAjoD23+MqGSguqzGZg+cMaBWttkAqz1k4dL5ZWADqobvFcq8CKn5YTBFUo4otO5e+bO3BbyMbAV8smzxjBqgVM5gVE0XUzpukDO2HNvLBkmc0FapnV1QMSrhDLQnHK8HvdFW1dqS+HJHc0hJnGcK0qyKs/LEk+6cFH6Scw9VfxJIS+ErPUljpbtwgcEFLUxVHZ9L9Y24bOmxme9yp73DoNk4zv59RZFfC+z4ylhZ5XlaQ5fpk6Na1DEz/ATqS6kLdtIsiYhupB6L29Ez8xaNbgD1jYeqnbn+FbELpHbbHg1dJql9tS96Y1eXZ7ab6ImTJMvwXZo3ef+nYdwU8PUN/b0/6R+jVa96J32YmcXGx5VOyORgYOELF1R0mXyFyjhpmZ+LJQ==
*/