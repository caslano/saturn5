//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_BINARY_SEARCH_HPP
#define BOOST_COMPUTE_ALGORITHM_BINARY_SEARCH_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/lower_bound.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns \c true if \p value is in the sorted range [\p first,
/// \p last).
///
/// Space complexity: \Omega(1)
template<class InputIterator, class T>
inline bool binary_search(InputIterator first,
                          InputIterator last,
                          const T &value,
                          command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    InputIterator position = lower_bound(first, last, value, queue);

    return position != last && position.read(queue) == value;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_BINARY_SEARCH_HPP

/* binary_search.hpp
KuC6fi2fkuPHBenWnwFuiZuXMeNvqg9eWE4fPqHgQ4CZ01eC66qHccvw3Q+E/yfA3Ozj5bk2+I5MY+xyP2NjUV5ea4NvNnxfXM9MHyt8eGb+DsBtGuDlmTb4/hm+fxiojQ9vYg6fz9i/buTl6Tb4MLtv2FQbH96Qng9wS75R6meFrwjfUYB5X8AdZ4PPDfiUCxi7XuVlO/rehu8HAPPChbw8wwbfhSAHa0GAdsZ5eY4NPgd8x4eY6WOF7w34Xg8=
*/