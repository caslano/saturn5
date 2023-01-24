//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_EQUAL_RANGE_HPP
#define BOOST_COMPUTE_ALGORITHM_EQUAL_RANGE_HPP

#include <utility>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/lower_bound.hpp>
#include <boost/compute/algorithm/upper_bound.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns a pair of iterators containing the range of values equal
/// to \p value in the sorted range [\p first, \p last).
///
/// Space complexity: \Omega(1)
template<class InputIterator, class T>
inline std::pair<InputIterator, InputIterator>
equal_range(InputIterator first,
            InputIterator last,
            const T &value,
            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return std::make_pair(
               ::boost::compute::lower_bound(first, last, value, queue),
               ::boost::compute::upper_bound(first, last, value, queue)
           );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_EQUAL_RANGE_HPP

/* equal_range.hpp
+vb6r/8/tL0JfBNl+jg+SZq2QEsKNFDkKlC0WsRqRVsD0kACE0mgXFqVo1ooVVErJFCV07RIHGaXXe91XfHW3XUXj5VTbKm0BQrlUCiwSnVdnRKQ4lEKAvN7nud9ZzJpi+t+//vn86GTmXnnPZ73eO7nyeGfT7eS5ihrPymONCTsIyIsDiMYG57eTGXdAhbeHXk8jB7HpOHjusjj/lhHkFGwyE+E/sgmbCAzYydb7qforccoDTyFVBJFacamcJ8hDnvlGgvln00KsQ0Du2SAPpxBWlRnwiesAFoKI/rjrVJohxh2Bhgocka5HeDalsdiGO7oASvK0GGObCJEnw2HhTeGd6uM71YZ3+nDjBJ69jMMMyZNG+bmYTjMOuMwU/Rh3mAcZnggqRcMQ8QiPbQihD+0OmyrPrT8wtD/90OOjQx5D7eqdlgi443Thlt3tYUm/3893M/M/2GmN5v/9zPtiQzbow/7drM2bDEy7M+Gcivh//GwfzD9wrBDkXL7OaVDuDb7YY7htDEntRlze3FdBAZJbWCwxkAA4fbFLUufaOplg2k7w1M7So0IVqtybVSVEVv5iFo6Qm7TB28ZPtDwo6b5iiKniOQAcuqh76LIqcx25BS3f7+eUTZL+dV8I9I9a4ezux9vIGv3eiV8AyOn/nUDUUf/ZJfP2GXPDURO1bBLBbtsZJf3bmA1/ZndjhtOlz+yu6fZ5Tr28HF2
*/