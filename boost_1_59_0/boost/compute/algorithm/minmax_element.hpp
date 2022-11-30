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
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
*/