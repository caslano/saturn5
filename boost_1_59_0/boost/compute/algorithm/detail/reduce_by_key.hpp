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
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
*/