//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_SCAN_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_SCAN_HPP

#include <boost/compute/device.hpp>
#include <boost/compute/algorithm/detail/scan_on_cpu.hpp>
#include <boost/compute/algorithm/detail/scan_on_gpu.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class OutputIterator, class T, class BinaryOperator>
inline OutputIterator scan(InputIterator first,
                           InputIterator last,
                           OutputIterator result,
                           bool exclusive,
                           T init,
                           BinaryOperator op,
                           command_queue &queue)
{
    const device &device = queue.get_device();

    if(device.type() & device::cpu){
        return scan_on_cpu(first, last, result, exclusive, init, op, queue);
    }
    else {
        return scan_on_gpu(first, last, result, exclusive, init, op, queue);
    }
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_SCAN_HPP

/* scan.hpp
jotRmcXqwV0a71rca8HrUdAD2EXy+1XIOkOf+z2yTtEKu+fV9aowkF/EdzCE8vALlUCfRhJopMY66znrXL+MkUioWUfHNjpcIxGmK9G/LwPdiJmf31r08XFgZF9gkaE/Id2CZdSf9AbPvo9ipzbRtqB+R6V/PMbOHgk1N+KRBHjttSi4VX+5uyvOORSb7At8OCrYnxzjYHWNISWxk0JPQ6+Nyp2WPneBORN+GZbXVQOtS7FXDQXSFzUHhRqWd6kbIBgIEpctDgyAu4unFi/VYMFDeVg7lilWtomGabjCwZSQuS3zYNIpVOjOuuJqdlQERbIcq/LTYyjhlADCbvTG9g3dI8XtlnMbF8R9eBi9i450r5k6pPfqKdo0lcd2YM0lX6K2YsK9CYPfEyd6x/7xFXbMIo8SCMmXL6VBSX3v2UycISzlg1LHdwyWPEK8i0wZ5XAZoVdw9i1RiH35AL1imcq+6FTFdQsYjerARE+Xa5dAY/V279i+CJfBj+eosihpJ8xhmLYTQ1N6+7twSoIOLKEOLGHfPoYChVK4o1EcFnJ30dEXaZ9innqcT3i30SP0yxILcpucQ3MudZpEJQDXruNEWLiCWShAKTEp8ocDIxmxBnZXhcVhX6zxFOpFNMoBSvnbSk6o1XxGKnqYTdskzcKDnelgPcb6W6eJWMWUxcvYtVQlVp4BhTs3HsDQzYiJkPxYNYx7uWMxDt9r
*/