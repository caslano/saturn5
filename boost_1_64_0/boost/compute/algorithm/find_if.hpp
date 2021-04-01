//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_FIND_IF_HPP
#define BOOST_COMPUTE_ALGORITHM_FIND_IF_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/detail/find_if_with_atomics.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns an iterator pointing to the first element in the range
/// [\p first, \p last) for which \p predicate returns \c true.
///
/// Space complexity: \Omega(1)
template<class InputIterator, class UnaryPredicate>
inline InputIterator find_if(InputIterator first,
                             InputIterator last,
                             UnaryPredicate predicate,
                             command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return detail::find_if_with_atomics(first, last, predicate, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_FIND_IF_HPP

/* find_if.hpp
8Cx2c4ivkJJDwYGi+6ZxiVjVL7ptGahwAQQxSfUW6lrHe1bMT5Jl1qfRpOZjO6BuZ7LGJbQYHk8bv47ZVMwuEHQOiJ2a4azGTyv/pYHwzWuhIHNVp8nPMzmOeKkyPtDs4XhvH/ux4gEOGIsFWTjRoJD5zdgxl9hqL0J5tBcYjVviBRG4B7EkrzLBbOBqUSJS5BzcjxHG51UgLr1++1jsbUP4uTUri85BWgIHtc+QutIVT8v+q9JmV7/d78v5o7L3jBwJxyzgAIxaAVDLEN4/dInEiReUJGoTcx5npahZas/5rPkMj5STBSoTDC1WQlJj9han0K2O3Nx8zOZHQf1y6HjqMoh/nPe9av+jsJM9J4yVIbkaybg2IZIlbmqldREYt52BNJvKHzawsYo5+d1rmJh6WBRWR2cC3wobK+KYrSSNgwqfG2R47kkuiubfERFmJdXjGVqHByKE5NXyQ7OJvkkqh8ZRKjLH1xJwTU7yWzdgpobyECMfxd5ev05ie9WXZ7hhWWkxdOcZBR2G8OmEyMnijArrxVtV5cD8akfpL0hU08Mw2aUdGgLN4w==
*/