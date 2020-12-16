//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_PRINT_RANGE_HPP
#define BOOST_COMPUTE_DETAIL_PRINT_RANGE_HPP

#include <vector>
#include <iostream>
#include <iterator>

#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/is_buffer_iterator.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator>
inline void print_range(InputIterator first,
                        InputIterator last,
                        command_queue &queue,
                        typename boost::enable_if<
                            is_buffer_iterator<InputIterator>
                        >::type* = 0)
{
    typedef typename
        std::iterator_traits<InputIterator>::value_type
        value_type;

    const size_t size = iterator_range_size(first, last);

    // copy values to temporary vector on the host
    std::vector<value_type> tmp(size);
    ::boost::compute::copy(first, last, tmp.begin(), queue);

    // print values
    std::cout << "[ ";
    for(size_t i = 0; i < size; i++){
        std::cout << tmp[i];
        if(i != size - 1){
            std::cout << ", ";
        }
    }
    std::cout << " ]" << std::endl;
}

template<class InputIterator>
inline void print_range(InputIterator first,
                        InputIterator last,
                        command_queue &queue,
                        typename boost::enable_if_c<
                            !is_buffer_iterator<InputIterator>::value
                        >::type* = 0)
{
    typedef typename
        std::iterator_traits<InputIterator>::value_type
        value_type;

    const context &context = queue.get_context();
    const size_t size = iterator_range_size(first, last);

    // copy values to temporary vector on the device
    ::boost::compute::vector<value_type> tmp(size, context);
    ::boost::compute::copy(first, last, tmp.begin(), queue);

    print_range(tmp.begin(), tmp.end(), queue);
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_PRINT_RANGE_HPP

/* print_range.hpp
n74+G+1Z6IlB8pi4a8nxDvW/WhXk2VfptjF8iZ0MVQd5fct+o9+b6/+drps3Kch5b7bE7tPsr2hvtvLPJqvDu+XHVwfhlmPtZSm23M6+1NswoyqI7KcS/EEf9xTX7XOTZ0Op0VVBptNzoPvJPX/Nzlvd7z2N4qGTg3B2VZD2vmtyEZ2Tf4ZeU2/73IY9ThxNX/Y8mKg9V5Lt9tVsZ5J9DOj3ZrZ6M3t+N7SuTT570Kkykxuz6bMqvUMwxZoUW/yIvP7u03PgAfvPfjMxGLzXNYFnRvcgmyP5wwJ2PanKfsR0y7az2p1xX+Z4++s6V3yM7Y5kV6fwqagqKIR8cAH51Cnj2ElBoI3eFQzKvXTXzG7fdC4ep2v7Fn1THURb6t+WfGRv7T/M/X7bj15nC2Jg3t/ZjJgwaQy/Zoubs/ed2NLt7LyR/vZnS/Pp4aqYPQJH2OvD8dPVuYf9i5+z3j1X7PuNOrUj/cGEIGTbgb1Pih+F8jC2fmZ1kNiGnj7X/p+ygdfVd4V++D+BpSwfuMK9+ygvO8F+73TxnHtvVs6zdHalcyurxEj9qdX+zcQatpPrk/vdpn90Ed1M3+/znwvkVOSQuVGsrBa7x2jrgcoXZ0sHu7+X3hc4t17/Fk0KQv1PLiDHO0bY33VKUCL33JP8t8hvRvrOjsqLR7JLa9WXTlam/n8t1k8dYc9BbZ8Zt8cweVsjz347wfObfHIFG14+0V4yE4PSJ+rz2XAyGzmV/etP22+Um7LWcpb6rVtEXeR/Gl+wD2LOZ8n+c4kDx3t/U19nimu/Fbv/wC6eY4t56yr36f/aiUEuz85O5TtNZP53vrpabP2E7L4bH+TsB5N9j3226vPujvPP5JUT/G8PdjQkzu1AHzk+8a7+N7If7Yl20efV4+0zxKem8OGLnWsk35njg7XaHIoxkWdYUk/J5T5kE3P413/07Vk623OCd6SM2Vn/M4sesvuwZ2u8WecLO4i7R6h/xRT7NtHZdsbhu/iFdYv85WLq3eL7Vuyonl2uE1vsjxWcURU0fBwzVrC7brKi02il5xbbxJgt4mROXkeQ99HGg5PFhMPErnvZz0y+fAufZ69ZcSvxWCVbEZNa5Ctv0t812qz85CvaIHal9xPnT+NXh4vLO4uFu2vH0b57hyOMixvbipuIetj41e6xR3h4q75Exp0q/f6pemeMEMP593L2ehb5JPRtnDUzOkm9r/64sfUWMWm2dm2szDcn+L/+2mwvzcwvlXH2xuLYSH4udmlf4XpczT79X82oUX8PnhwUxe3gbWP6rDFiZkVQ4C+Z68TiLacE2T+xi9+w2XVkW+I3C9nanezhdP0+m20/NMJ+ap5L3ZUd3Bfzfgkb3TH0swGZ+P/CZT6aC+Ped58YBL1keoZ6fkCvF4pDTfx8nva/UsHnxejtlLO2wvhXwbflD2JnVuwsZUZ7JodfTWfLU1w/tppuJnnngy10smd/J/dlk6+xSfUXtLnMP/P1dD7Ezt50XI5RONwYOZ3vROza96I+lj4LxZzJyiTXw+h+L/bpmsSermVXqcfo/R162RnpeBDSUdazZdF85c0zLi6NeQZDvNubrufwW7lL7m66+QGd9GnHZaOtkcmH7UNQfraSr4pNfCU4g+zP06+cNnrOIef60L4IJXEnupvv30s2I7w3QBf5v2F7Y2XFGHmq54zz9O/5reRL9Oy+XDtb/JCPKS93iRjYKUe7QDuuMN4av1K/NsY63nAFmT4gFzyKvB6Xu4oFhYe0u5Vee423e0wMylXsZiTdL9J3tpT8u/Hy49D4LR8NK+TY9CvXKvfQJbmk9zHe/o3sl5LPb5X7MF89h8zUnTpX7EyR1Y+MRXI=
*/