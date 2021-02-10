/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    result_type.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_RESULT_TYPE_HPP
#define BOOST_HOF_GUARD_RESULT_TYPE_HPP

#include <boost/hof/detail/holder.hpp>
#include <utility>

namespace boost { namespace hof { namespace detail {

template<class F, class=void>
struct function_result_type
{};

template<class F>
struct function_result_type<F, typename holder<
    typename F::result_type
>::type>
{
    typedef typename F::result_type result_type;
};

template<class F, class G, class=void>
struct compose_function_result_type
: function_result_type<F>
{};

template<class F, class G>
struct compose_function_result_type<F, G, typename holder<
    decltype(std::declval<F>()(std::declval<typename G::result_type>()))
>::type>
{
    typedef decltype(std::declval<F>()(std::declval<typename G::result_type>())) result_type;
};

}}} // namespace boost::hof

#endif

/* result_type.hpp
mzDGzPZHt/hiXTtTZ/5Fm584c9cOAhMY5Hpk39vunIJbxukwu7Zp6ljXU5smns9QlvuFgjt75FjTAXj79mg+AET7BJWR5wb2vxeAgwyNrZl1w0R8rdq8asdurXngwa4P94LFdM5uTHxvRlMvYOa0CGzYsOYWayOGoBwMoGeDoM+8LVdTGs0dz2UFmJ77FvNw7Zupc2O7I5t1Pa0w93wILoJGYUCW7wRs1FvMGQcAnoYFjGvXoDr6HA9w0SxsH4GYWRp4cpyNNvuXfxl+quRQz4FP5knlX/3/fo25gJvnSqyjKkULaJ9CdDi6onVPyKdEZXIrZHlmjO2JhUgbb7Uuum38EJa7XGjJDRrwLjkzLBRL6Fozm8VqGd0jNFrdU88wrS8HB/0GL1l3xE2JCUHGvYEBzDKJG3GT1x3zHO2oEFeAExJzEWO4J+sapihCTEm0ryv68IHfy6isCry1A7VY26I1sVLJVG7PjBv3PuRlL/wF9d36AF57YVP8l2kdsfquEjQYLCI99I0crcP418z6xa6BRgt/ymg6JOYI9fkQFdwF0MjRRbEemIZG2WRoZWgGoXjmZtx6xP6uqlio13mirseLke23RPfSfz7RdokMl1HxO1GdOFOb4cNrK9jH9ljvT+fNtSBRcWHx/Umo
*/