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
+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
*/