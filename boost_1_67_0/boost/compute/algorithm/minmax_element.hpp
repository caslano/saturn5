//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_MINMAX_ELEMENT_HPP
#define BOOST_COMPUTE_ALGORITHM_MINMAX_ELEMENT_HPP

#include <utility>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/max_element.hpp>
#include <boost/compute/algorithm/min_element.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns a pair of iterators with the first pointing to the minimum
/// element and the second pointing to the maximum element in the range
/// [\p first, \p last).
///
/// \param first first element in the input range
/// \param last last element in the input range
/// \param compare comparison function object which returns true if the first
///        argument is less than (i.e. is ordered before) the second.
/// \param queue command queue to perform the operation
///
/// Space complexity on CPUs: \Omega(1)<br>
/// Space complexity on GPUs: \Omega(N)
///
/// \see max_element(), min_element()
template<class InputIterator, class Compare>
inline std::pair<InputIterator, InputIterator>
minmax_element(InputIterator first,
               InputIterator last,
               Compare compare,
               command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    if(first == last){
        // empty range
        return std::make_pair(first, first);
    }

    return std::make_pair(min_element(first, last, compare, queue),
                          max_element(first, last, compare, queue));
}

///\overload
template<class InputIterator>
inline std::pair<InputIterator, InputIterator>
minmax_element(InputIterator first,
               InputIterator last,
               command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    if(first == last){
        // empty range
        return std::make_pair(first, first);
    }

    return std::make_pair(min_element(first, last, queue),
                          max_element(first, last, queue));
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_MINMAX_ELEMENT_HPP

/* minmax_element.hpp
+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
*/