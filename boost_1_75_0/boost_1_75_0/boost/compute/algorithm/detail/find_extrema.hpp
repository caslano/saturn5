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
xDOdfaa0yvuVS77B1WlA3tkH7CyTTGMePw7xfDx+LlvXhRMNLayPoO3a/2fnueB9w3UWeJdEO8FrSYR3oet84L1/7dngffqnDp5T+KZEX7RLE2BlZhUf090kKN1+HstFYB1izY8WjVJCzObASq88j6SnwahVx/rju3pQKurBXhiYBPvkR0XTsII17+/lsTiUC4GykOUGiIsDMPmwJM+2qut+wa36yXfiLsVxvcnm0x1aF/6Avh2/7CvmGHvGcgCOL5Aik1sBn5VjX8OiwNNbSfoCkG6T0G0MJTEmlfJu9t5wPstz6O3ODmQMfq29g3tD/jd2pbZ3aGeu1/Lt8SF5SLFKGNZpUJNu6ArHPFhLsx4GVXEKMY23veC8IB/6dvK8J9gMZ+gO64wb8LHo6LC/iaXs8Blvtbtl0eHJ1UjKQQ5J3PgTlrJx1gYz3eFbHe6KWzOJIQWplR0CgavdecuyAnayhWS585ZnBo9hAFpYdERNtC1gBbKBeNe0pZADb3aNZGr0OoFMYkY2DxLjvrpo28ed7+ok25JRVUFra9ACsOUXOBbDMbcDJFxR+FM1RQADEHeixHsJQiKUR1AvOc2RIIRbAytjQrha4JYL4CECBt9s7MpahF/Db94/IJiG9iL8YqPkbMQvemC7jPKYdnmcO4SyvihZFThE05bcfWLLKZgZ0fmRW5hQ6w4XOMgQjJMmr0BBR0nFEg6wcyQ5
*/