//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_COUNT_IF_HPP
#define BOOST_COMPUTE_ALGORITHM_COUNT_IF_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/device.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/detail/count_if_with_ballot.hpp>
#include <boost/compute/algorithm/detail/count_if_with_reduce.hpp>
#include <boost/compute/algorithm/detail/count_if_with_threads.hpp>
#include <boost/compute/algorithm/detail/serial_count_if.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns the number of elements in the range [\p first, \p last)
/// for which \p predicate returns \c true.
///
/// Space complexity on CPUs: \Omega(1)<br>
/// Space complexity on GPUs: \Omega(n)
template<class InputIterator, class Predicate>
inline size_t count_if(InputIterator first,
                       InputIterator last,
                       Predicate predicate,
                       command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    const device &device = queue.get_device();

    size_t input_size = detail::iterator_range_size(first, last);
    if(input_size == 0){
        return 0;
    }

    if(device.type() & device::cpu){
        if(input_size < 1024){
            return detail::serial_count_if(first, last, predicate, queue);
        }
        else {
            return detail::count_if_with_threads(first, last, predicate, queue);
        }
    }
    else {
        if(input_size < 32){
            return detail::serial_count_if(first, last, predicate, queue);
        }
        else {
            return detail::count_if_with_reduce(first, last, predicate, queue);
        }
    }
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_COUNT_IF_HPP

/* count_if.hpp
CAqDTQQpXMOJKqOFywsx4HbyM3wqnda2YoHx61xhIpiBbb1HPmWwTCihW7/9ykWawaMTKA9lfCTqpldHa4HdJb+BvyEqXrp4SMaPzjGkORdyiwHiJIwfgNnsTIHZCFcEmF0zlzDbEQ2YXYQPZgZilqBh9mE0YVauY0aqpn1hViBm5UbMygMwowBZmApNPCTMBkc3gpntNoHZ7H4RYJY7hzAzI2Z/wgelQMxumSMw+zmKMFusY7aYMGt6WyBmi42YLQ7A7ONkilfGlmTiIWE2N6oRzN6/Q2D29t0RYPZ4KWF2M4bFQ8xyAzEbWSowa8cxW6Zjtowwq7grELNlRsyWGTCD8+j4G5ag4iFhttYaCjP/mDpyiwQnm69hwteWA/PwJauTMqiUl/Hi6aJ4HxaX8+KHwNqa8UiereROXLFNR4q1utOKWjp8U5nsRKLZdKLtQqLVAVpiumd0u6OE0U21lSWh4RVlPS+Qbsklgm5RVqLbcp1uy4lu6Q6gG+hLjHJdoInlvImr9Rdw94VVAep9RmWQFVBUgLSvtrJllpBywVQkIoOw4zxhEStm2ZmP7m5XYORKTG42ISvjWofnDPjoxXPzBRDplaeFYSZXCiNWwjrT2Uti1QbXMP/R7KA6eaK9gjznzUSeYp08xUSeG58JJk+xkTzF9cjDT5nR+osqEHmeN4ckDyb8xSjiWgzCh7n1pYmu2Mogf8EuXzxx
*/