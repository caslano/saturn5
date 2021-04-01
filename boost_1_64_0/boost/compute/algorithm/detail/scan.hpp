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
rRRZbaKEY26wV8U35fvILa4W+hWKM8GXDRu3pPmYo/OIOvOxPCXkhboRXfvnkxj/0ZLyEJ2Rd7E2DBHuguIYV8jeGKve/1mrQ7Z+8ovBgu/r5kJ1JRz00lwR9wrsPg9jTGnjDZWVjoVSicjp/Vo8J9pF6+cDava1DJelbKMEPw7+ehHddNjg08ejskRdyz4c3ZQRWuP3l5CDARWkgFsl2/8wLv7atpY13st4e3w2FlhFcuMckvrqUlkCBt2f3YzpGME5RpS4CLDJr+BA5sDwCeh5sJVVtndrHNEqL4Rxo0wR/oBg00MFYKs6piAjXVYlUw+qrXt55/jIpELVozHCGpcRnNQlpGKYLZ4GjZUxE1SyKOk9sqnshZbBawnK69UWKmvw1YX+l9iqbTj5eSwqYEewn3p+/paRyczGRrH7Y53DaWe7uA6tFYTIKEp2olFw4ChEjiG6fXT9PPjFCTqMH8gZ6FiikYfBpPuMLqrSmEu3hy3c4tCbmAuvCxgYT43FUike7IpbR/X4xrt76BDW9Iqkq+kJr2XJ44Tcj1asvzTSIiYFR1BiUlmnyA==
*/