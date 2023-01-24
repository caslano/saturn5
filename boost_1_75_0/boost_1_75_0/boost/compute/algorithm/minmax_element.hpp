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
TwDaieDfuStzlNJmfAbQSC0yyoCa5Y5sfDOlw8p3F1TV0S8JGlowGVq0wY9wgiM/ZX7XjHw4JXLjsWunwuNRQJ4LSDChVulxEJFYA+Xk6EzU+e3dCDPpcF+RiLRdddiaBcixRo+xLTJDUTLVVvbtMOjNWZ+Qqkwh2+BMl239aWUy9E0a7j8RK2SpjosL5qIoxnr/CeqhiD0UtR76C8Mn9f4t+Kxt/zYmoTDI0RzoHunj5wloJhNOjjzZBU/UmvDTqLfSe0zenChYm8n73Tuq3wRG2/rDyhvn0TJgl4I6VKnWkfhdGCA6Ee33wh30FyA6Ru9v1adt+9sJMX1rpGfXsr5aN3xNei3dMJz16PFaVcfb09pL9RKeNUr1UIXKDPFReKfa9yQw1rFeYCxsOmkhaUtHaJ9NGXz1P0elH+7NqAvAHV3YN4gP0q87Gh6vOwGInBCamaBF0WfB3VLRwUbmkeqv3UdxMRTPKEqrcMsQlg9iJzx+30RfhQnxpsOd0YUA+bMnqgxSMnEFQzzFESkZYZ4/1qodrXskNg/70I70NNmeb0BmrUmlQe9Ui9B9r9UH0L+myJkj+K8EvCiqlfA7Rgy0FDmDi8WLN4nywybR5jq7kQxegqpFtI05S0axR/05UNTkz4p85mGfeS5O9yewH9f4LfQumDPd3xkv7IEXwwV6pQofgLYHfGn2J3qlbR5g0cfkxIwOtKDEq9gH
*/