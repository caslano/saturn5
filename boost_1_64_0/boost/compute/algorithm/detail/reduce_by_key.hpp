//---------------------------------------------------------------------------//
// Copyright (c) 2015 Jakub Szuppe <j.szuppe@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_REDUCE_BY_KEY_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_REDUCE_BY_KEY_HPP

#include <algorithm>
#include <iterator>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/algorithm/detail/serial_reduce_by_key.hpp>
#include <boost/compute/algorithm/detail/reduce_by_key_with_scan.hpp>
#include <boost/compute/type_traits.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputKeyIterator, class InputValueIterator,
         class OutputKeyIterator, class OutputValueIterator,
         class BinaryFunction, class BinaryPredicate>
size_t reduce_by_key_on_gpu(InputKeyIterator keys_first,
                            InputKeyIterator keys_last,
                            InputValueIterator values_first,
                            OutputKeyIterator keys_result,
                            OutputValueIterator values_result,
                            BinaryFunction function,
                            BinaryPredicate predicate,
                            command_queue &queue)
{
    return detail::reduce_by_key_with_scan(keys_first, keys_last, values_first,
                                           keys_result, values_result, function,
                                           predicate, queue);
}

template<class InputKeyIterator, class InputValueIterator,
         class OutputKeyIterator, class OutputValueIterator>
bool reduce_by_key_on_gpu_requirements_met(InputKeyIterator keys_first,
                                           InputValueIterator values_first,
                                           OutputKeyIterator keys_result,
                                           OutputValueIterator values_result,
                                           const size_t count,
                                           command_queue &queue)
{
    const device &device = queue.get_device();
    return (count > 256)
               && !(device.type() & device::cpu)
               && reduce_by_key_with_scan_requirements_met(keys_first, values_first,
                                                           keys_result,values_result,
                                                           count, queue);
    return true;
}

template<class InputKeyIterator, class InputValueIterator,
         class OutputKeyIterator, class OutputValueIterator,
         class BinaryFunction, class BinaryPredicate>
inline std::pair<OutputKeyIterator, OutputValueIterator>
dispatch_reduce_by_key(InputKeyIterator keys_first,
                       InputKeyIterator keys_last,
                       InputValueIterator values_first,
                       OutputKeyIterator keys_result,
                       OutputValueIterator values_result,
                       BinaryFunction function,
                       BinaryPredicate predicate,
                       command_queue &queue)
{
    typedef typename
        std::iterator_traits<OutputKeyIterator>::difference_type key_difference_type;
    typedef typename
        std::iterator_traits<OutputValueIterator>::difference_type value_difference_type;

    const size_t count = detail::iterator_range_size(keys_first, keys_last);
    if (count < 2) {
        boost::compute::copy_n(keys_first, count, keys_result, queue);
        boost::compute::copy_n(values_first, count, values_result, queue);
        return
            std::make_pair<OutputKeyIterator, OutputValueIterator>(
                keys_result + static_cast<key_difference_type>(count),
                values_result + static_cast<value_difference_type>(count)
            );
    }

    size_t result_size = 0;
    if(reduce_by_key_on_gpu_requirements_met(keys_first, values_first, keys_result,
                                             values_result, count, queue)){
        result_size =
            detail::reduce_by_key_on_gpu(keys_first, keys_last, values_first,
                                         keys_result, values_result, function,
                                         predicate, queue);
    }
    else {
        result_size =
              detail::serial_reduce_by_key(keys_first, keys_last, values_first,
                                           keys_result, values_result, function,
                                           predicate, queue);
    }

    return
        std::make_pair<OutputKeyIterator, OutputValueIterator>(
            keys_result + static_cast<key_difference_type>(result_size),
            values_result + static_cast<value_difference_type>(result_size)
        );
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_REDUCE_BY_KEY_HPP

/* reduce_by_key.hpp
O+GUbTX8k98xKvrQfvz//U1+HG4e3kh+eKPlX8DfbMfXxvVx3R3yc+MOOH1sXfrc1fBDXYKzvhjrXk9fH4AngreL87M9v37Ukcn+5cTzXMIe1H1qxvo/7z90nudq3Ue/LV6o1ljwM/yXvLPnTnYVeCvOi+/js3U10ov8H/IfJ6uz/BoO3SLOXhS8WNQP8Mdhh7F+v/NeOg8et/7Wa+k9+26Lvu0Y/6nPmD1284sd+uG64O4h/GLWPLxaHn0cljx3rOPEwL3J599k/u9Fcjzk/zSeHJ+884v4PfaZH9/HPFFvj8+brWMFuw++Ib5/kZ5uEF+3ylumi88r1CFnqevj1er0v5Q/lSOPgWO/GX2NyTrj/63GfZ/Bp5Wl889ahEe4Fa7dDjfutb4B+JYn8BR4iQVT1HHvgHu7kuMhh9/xh1votzpxZbd69Wt4v/d9jydc1Cqu7bRPx4T9RH01zo/6Jz95AvmvYS8PwQXBU8T1kzN9EnGfyB8SfBWfX4fjP8xOxzP0y19Mbscn+h7nPzyw3+DwA4eLo3+BA+GT4d/C90/hV66gd4vhqsTP1YU+zxbXjmcn/exT7Et8rstOx6XqQTXw7qQ4P3gzfmcJftO+tQUOCDmcY58eFPcDZ8d5D9HbD8nbcy75e464Zp8my58ucv4dMQbelpdl6l874N4l9PRX6XjwfHyXPLzgKfJcjMfc4HkOFddr8SjRzx4jnDaLX62E40pOhQ/EqdzoW4vvb0j8QHz/J3q/Nr3P9CJ4hH+Y9CzetDiOBx9gf4Ifj3Un+fkpcTyXPvv9hZrT4N4+/Il5Gy6EB0vFydv5/xp2EHxEzBvPE8+vr7OPfo+4Rv8Vf9h6F38w176cmOkHYEf8xTp5ztAqPPJ8+nAJ/m6Quia9HnmwOP8GXlM8qz4vP11XCzscGf4geY45Gb3CR02hv/ji5r+ot6+O86L+neKylqHp8YK32BN83p3h5aJvK54n+Lj4PFXe4z5du+HI/fEdhYNT/cAnL19FbvRs1g2ew/WlH9CXZvyM+sqOmsTuYh44fNlXPAd+v8j7x3tmwSORB8d84s7Q4mSM/Xgljsf7wuqrB1gv/9p+nn2/0/tH/HVvimeT54RXcvCP98OJl/KLPxNPjs9P5d4c9w1/Ie8Nu4wxkcc+sZ8DyZFdN+Y472686hFw1hfY2fo4Hnyl/Fb/b+kdeLh/sIOv4peS+JAX1x+i3mfdC+XLdeXsG++XS/+2vYzvifgV83aya+uvgt8bL9ZXl8eOTtwnHTfI72bAPy+Im5fjC/a3jsPI95zkc9y3Fv+OT+zQN1RYiJc8Mx3X9cEdd+Ix+OFt9+uPa4TH4b+WYn7x27nsEz6/QL4gj5lwuL7YDnqQ9MPuH3oadZu4rj+9OjEfDrBuvMTQK9LjDd3ue4N13C7PTPKw/mE/PfxE2Hmc/0f83rXeM1qeHI/1vMJujmb3j7DLuC6O13rvMuwx9ul8+v0IvVzjPurKncfC4/p7ZunfqTyOHR6WjHF+5v+4iPtZQ8SnCfiigvCL0ffEz2fqqFX8G/stgc+q3k/HHZvEm2My/gePeID7T/d85Nmjb2SU/vUFTyafY31XyrsPSI7H9+Pt/4/VddR/Vn+QnZ5Hj+ve1N81LY8dx/lRNxWX30rr2l2P6OuBI3vu49/3x7dmqSccnfJJYy4y70z/566RPDbaJ/PuvBce+TN/+Tn+S75YeCP8e9jgVP6vp8eHD4aXM88Z/Focz8jf7yaNaMvGP8rP+YG+hfCw/W2M80M+LfT3dnYrvo69lF4sFfe/BH9EXTfOX42fSdaX7gc9v1ZemSOf7MVffFt/1GfywNfS+7f/Qn6LZ2trlIeJO78=
*/