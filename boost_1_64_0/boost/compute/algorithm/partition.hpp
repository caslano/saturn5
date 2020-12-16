//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_PARTITION_HPP
#define BOOST_COMPUTE_ALGORITHM_PARTITION_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/stable_partition.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

///
/// Partitions the elements in the range [\p first, \p last) according to
/// \p predicate. Order of the elements need not be preserved.
///
/// Space complexity: \Omega(3n)
///
/// \see is_partitioned() and stable_partition()
///
template<class Iterator, class UnaryPredicate>
inline Iterator partition(Iterator first,
                          Iterator last,
                          UnaryPredicate predicate,
                          command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator>::value);
    return stable_partition(first, last, predicate, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_PARTITION_HPP

/* partition.hpp
M3inhr9Xwz8I/fAN1S/4profhNWWynnCpZrvBFim+d6j+X4RtoYvwcHwZTgU7tVx/ArMh6/BQvgGLINvwvnwLbhIw6t+RZVxpN30uka/ourBC/AD6If7Yarq0WsPD8DgfSFP07nAeV8w+h+bwlEwCY6GOXAM7A8nwMEwH46H47Q9jodV6r8Mjodr1L5W7Qd1rjmg179Pr++HF+v15xLOD8tgS1gOB8B5cBBcCofBCjgBVsJFcAFcrP41cBFcBavgtXAx3KT+N8JquFXt28Rut6/IrcHNLu07mXAZcBrMgkWwB5wOj1N7IZwFZ8KTYQk8BVbDU+FyOBv+BBYb/Zkq0wTnuLRvrV53JcyEq2AePEOv9wNNZ52lsjVwu6bTLGRN8jHhmsODsB38RNP5FI6G/4QF8As4G34J58K/wXXwK3ihhlsPv4ZXw290XP0D3qn+B2U8qDyKys5UqCzGTs3PE5qPp7U+d8E+8BmYDZ+F/eBz2v6/gaPgb+FkuAdOhS/A+fBF7Qcva/u/Dq+Db8Ad8H34JPwA/hr+GT4P34Z/gO/A9+A++Cn8I/wcvgf/Bv+i5bKMjAbyJVqutoF6xFiqL7IVbK/12VH763A4S92Xw07wbNhZ67WLzlvd4JWwl85Tg+FzcAh8CQ7V/A6D+zQ9xppcZxIcDulz4j4XdoCV6r9Q/c+Ax8GfwL7wCpgDN8L+8Ho4AG6BA+HNcBC8S+NrPeh3afq0Sz1QBrlfXg3bwmvgcHgtHAmf1nlwk86D18GZ8HpYBG+As+GNcC7cAqvhz+EyeAs8XdM5E26F6+AdcD28E14O74M3wPvhNvgA/AV8CD4LH4b74SPwI03vU/gr+BV8Av4T7oQzKeNTsAgSTvXD6ndEmeuwh+mHLfbWjdu5sAQugFVwIdwIF8G71T+FuGUwFc6DmXA+HA0rgusG8z2COU6vl1XXn+R3rqdu3v8x7AV/AofD9XAsvBweD6+AlfBKnb+v0vlzg/bPa+FquFH76Sadz7foPPozeDP8ufbTh+Ez8BH4AnwUvg4f0/76S/gXeKv2n9vgV/B2GO+h/WAivAO2gnfBjnAb7AXvhaPhdjgO3qf9/X44DT4AZ8AH4anwF7AYcl2zbuFdueo/rr9ueVbXy8/BjnA37KL2gzDTvAem62u9d5D1g0QXPeMxcDaMhyUwCc6BGbBM78flsAecB7Ph6XAgXAlzYaWuFxbAMXAhHK/hpmq4aXARPAEuhSVwGVwCa+AqWAvXaLzzNN46uAr+GJ6h4+RMuAmug7fB8+Adar8bngu3q/0Xav+l2g/CC3WcXAy1nvUdIGVwqecluq6tgXmwFhbB5dq/+VvfL7EG0fhxcBJGvHS9MxVGwekwAZ4Am8OZMBOeqPV5EhwFZ8EDR6B/t1OHBGsHHAtD9fCWYa+FK/Pij6k+3rVc51A6eff3iz5qenm3dEj4r9fNu7NDwvdOP+8i9O2uxzyIeQMT9ccEqxumAFOBWYfZhnkF8yUm8z38MIsw6zHbMS9iPsWk/CnBysWUYNZitmJ2Y/ZjEt+n7JixmDLMWsxGzCPvN+r7bfw1/hp/jb/G33/nLwqz+Njr/8spK55XLSoAj4IOwBv8PE/rd/tXVG/dB7r3+XeY2MD58wOMDg+5+pzKJfI99bUkC3dc7O+9Gra72Gdgf0bsj0r4a/x6Tr39vVfDdzTnOz8u9odUJsDWV1VowvYV+0nYnxf73a56uxbj/5T4PxaiG2qx+e77svj5zFnVr4r9Oledg/0H6nnPxm+B+KXx1wsSb3uYrAgyZOYa94pftfjNMfujPha/qy3du2DkyjapKW3A3oXgd33age/K0g5Gnoy6xk3rWuXJyJ8=
*/