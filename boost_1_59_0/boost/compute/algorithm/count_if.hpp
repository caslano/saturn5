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
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
*/