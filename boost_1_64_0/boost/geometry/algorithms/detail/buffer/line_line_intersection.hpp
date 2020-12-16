// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2019 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_LINE_LINE_INTERSECTION_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_LINE_LINE_INTERSECTION_HPP


#include <boost/geometry/arithmetic/infinite_line_functions.hpp>
#include <boost/geometry/algorithms/detail/make/make.hpp>
#include <boost/geometry/strategies/buffer.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace buffer
{

// TODO: it might once be changed this to proper strategy
struct line_line_intersection
{
    template <typename Point>
    static inline strategy::buffer::join_selector
    apply(Point const& pi, Point const& pj,
          Point const& qi, Point const& qj,
          Point& ip)
    {
        typedef typename coordinate_type<Point>::type ct;
        typedef model::infinite_line<ct> line_type;

        line_type const p = detail::make::make_infinite_line<ct>(pi, pj);
        line_type const q = detail::make::make_infinite_line<ct>(qi, qj);

        if (arithmetic::intersection_point(p, q, ip))
        {
            return strategy::buffer::join_convex;
        }

        // The lines do not intersect.
        // Distinguish between continuing lines (having a similar direction)
        // and spikes (having the opposite direction).
        return arithmetic::similar_direction(p, q)
            ? strategy::buffer::join_continue
            : strategy::buffer::join_spike
            ;
    }
};


}} // namespace detail::buffer
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_LINE_LINE_INTERSECTION_HPP

/* line_line_intersection.hpp
5pCZ8wvDOV/n96KE+b04YX4vzTG/1+SY36cPML/PTZjfGxLm98UJ8/tJOeb3lTnm994c8/saO79j7lqf8K10A791hH53oel3o6TfVZh+d4mZtxLmrNg31Fdpn1AFe6Ka7DpnK1u8GuAdBTzYjOpbP5rsmg9Xhz9rM30ENI4BrrUbn4LvZbqhP4fesHdryozq0C9yCb2HMxO0Z1k5UIbPFc8G7hzgnmxtdTMf1/q+7tYo2O/IG+nzsn6NumrYOrCx9VyY6+8+P9vnZ8BmrzftVxy2n0PkjQZn6zj9j/mucRzVeV61/Ej381HnBUa/fzM0GojGx6rlRzQaQaPJtN8u1eorTvZHDmJO9N9myI4+oZp9rPguL/nR/vJniFnR4vQUwCfk88KxHsXcXurmjSE78k1iDrOOJvgnHX9ZC+y3Drd+6N7pkzR2TqymeFEuDb06Om9Vxb91tBL8DfJptinc01adCJ6Hpwzc+V5epfIrBB7J1gzZBM/L1kFlp1bHZTslLOv8QFrfLuor3UamVyFTj6FbWk1+RYGfCrpTjB7TvGc0dKW8L9cveegj4rtM7iOrQftZc65+LbXRadRGp6u8AjN854Dvp6rj73fdMRrfE+g7xKcj+YC3KeG88WeUluIk0vqcwVuXnxvvC5Yn7nHyXa6zovlxVDjmbd3HFYSwwoK4b/gc6MH9bDzFQsTuPlfgFrcgPzfu+RbXjO1hCbgXmnpLnsowlM5ff7k6fmb68AK0oZYL4Xvk474J0VVZSZ9fq47T4Ts9lxr4m6UOJ4RfjL7yDa2rg/ObM8BFXS8jXOGVE/cKwrU6ZNxvVUc6xb390mzdBQd8wp/V6XdNX5pcmHym/vuEk3Sm/iqjo2X7bN8WP6yO2xcvi3zR99kX/bel8L1SjflD8Xku8bYl5mnk7T/K+xj6l5m7fa6uxUHWRyn5+mb/tWYNLg33I3JBLRayiDNzx8naifJRPX/s+UfQ0JY4Jt/JIvtUf5jc3hOUvG65Wyp7ZX0nNYet2ABbsRz13FhtpFQ5WcRB7U9qm+rbF/Y1tsq3FF84CZCNSVMdj2OW8X1M9sBiDekdQC9ba7q+PY3iaf0OeqOzv3b4TXF6MN7Yb/b81E2+fH8Q+ZlvNnoYGTiJXXxNiaHeN3NlT0eb2s6JEOFzJvg8Mib8BpLO9Pa4z0nZ7yA93Z1r3ZnIrO9hT583szYWv8rnpXu6UurjAH74fUwMI+nUMxvnWR+ALyP9WGhH8S1vifl965uaFsmpTtnpNjWLj08eRo/qkwSR+uwobv6cugV1jS4g5qIZzlfoSeUCaptvqo5/L/q5l7E31dfVkRGfVVP/MuebSgeAic5Sa9o6+9sNSL9B3BprrwW18/2xBTm8WitVaIpqx/n6/c3E9pIJAX40uROmMRvjbYIvh+Z71W2xvb3ci5i7UIKELmmRd6PqZ0XsKXtAX8UH6HNOp7+qjsfqvR1jxkWPRtq989zeYWIA/jpnX08nsdRvKZjXdd80geb1O828vqZAfmTX3WXgr+aHPwu/B/P+hCgWWX4spqjek2Qb577qeOyPBw40b5FL3kGj6H5btYWHPwvfomtYyA/f2xFvJKzrg0oDOAoPaTwEmTZCpl8APo3Sl5i0xb8UujtK06HdOqIwa7f+EW0f05m5D+NoZfy5FrrTZuon/vvE+CVPR/sC4Fib8NnqeKyQ6UNxDibsG7DHwJvOwbygvB1u8l2/l1S3oEd3/f5M/Yzhr0Q8DJx5vEo4SXbK32kfsLYA/RFlct39e83YYnMKBtbHGyqHw03Wx5taX9Cj+v7LwOsT4P+OeBg48/iPxcmhj/dIH8cafdQPoI8hU7P62LSD/jF0KuQ=
*/