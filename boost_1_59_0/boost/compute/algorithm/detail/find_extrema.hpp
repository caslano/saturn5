//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_FIND_EXTREMA_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_FIND_EXTREMA_HPP

#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/algorithm/detail/find_extrema_on_cpu.hpp>
#include <boost/compute/algorithm/detail/find_extrema_with_reduce.hpp>
#include <boost/compute/algorithm/detail/find_extrema_with_atomics.hpp>
#include <boost/compute/algorithm/detail/serial_find_extrema.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class Compare>
inline InputIterator find_extrema(InputIterator first,
                                  InputIterator last,
                                  Compare compare,
                                  const bool find_minimum,
                                  command_queue &queue)
{
    size_t count = iterator_range_size(first, last);

    // handle trivial cases
    if(count == 0 || count == 1){
        return first;
    }

    const device &device = queue.get_device();

    // CPU
    if(device.type() & device::cpu) {
        return find_extrema_on_cpu(first, last, compare, find_minimum, queue);
    }

    // GPU
    // use serial method for small inputs
    if(count < 512)
    {
        return serial_find_extrema(first, last, compare, find_minimum, queue);
    }
    // find_extrema_with_reduce() is used only if requirements are met
    if(find_extrema_with_reduce_requirements_met(first, last, queue))
    {
        return find_extrema_with_reduce(first, last, compare, find_minimum, queue);
    }

    // use serial method for OpenCL version 1.0 due to
    // problems with atomic_cmpxchg()
    #ifndef BOOST_COMPUTE_CL_VERSION_1_1
        return serial_find_extrema(first, last, compare, find_minimum, queue);
    #endif

    return find_extrema_with_atomics(first, last, compare, find_minimum, queue);
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_FIND_EXTREMA_HPP

/* find_extrema.hpp
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
*/