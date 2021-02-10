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
0U9VCkifnnWok6ol36F/hGffhyetgyuhK5F2gnD2hsaDq8vgUNVzKvI0NS4faUpSmA2AqeMUdQSYBbm79ZFTM7sdT6az4SwIdRJ8rXSUVrGkF6zYA2/1Mggubq5HV1GOBwcGu+4JHfsTr7YX/Hmzo2IVuMppYfkkRuptKRZJbP73/7+SrLRR99r1pK1lNIT+SoRvWpXJvLKL7JM3j3WVQeHReRCK2KXm9eXs4no4nQ8n4+AuGR6G/t3RXTKt883JdizhuaOweWm4/2JabhyuXfm4HEFTjijXVii9Y5l7EIfeKxCa0YZEQ0trBQPLNI/eIRFWpSQiqx6U3QTcCNJiANRdYCmFGRCPlk1PNRYBboSxywi7v3JEZQwDfpCiFbWAYpmCK5SX3nOIrwt0vY6Vvue0sUDaZBn3mbb4TgBWLK3vLFVu3A1+rB+50PNSzX130YcrXQYDpY2VwnFHJt4hKRX6v7EoImRWRBsmhBKB5xrsuaF3srBhEDDPRqgNOysK9HUkmIAdSXLUJOJY8QliaGPSwxR2jGd7JujAqAzcXLIfiIHr3j1jCDwzDgRtMb4D91mbL0tdYiMy7xB8m2hAAFwj2b7LNrR6DHJhEI/O9fPxzWiEh3abkiIvqlSw2jWoi7UGNrfwH6IYgFzz
*/