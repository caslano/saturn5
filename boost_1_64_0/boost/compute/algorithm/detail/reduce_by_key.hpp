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
rRczQBPb89bDnmOED3NZA/FtyhwZNonT2sG0ec2B2JHVQ+AB6ROhdIKbgznsTIXzKzyZhm63ySw/jpSdzvr7VeCKm2fXrU2NKGwFw3tSuFg9OzA04V/1Cqe0lcNzhgmjRaqsYU9yrCITUJKUeVXqYAWeZmXAi/MgvfFoIZn/09WIQYr0H9Jw9VUFdFkp/4dyAoV59p0DTCPYxyIj8KiVnqqDqtyx6FASWIEV6CEXoLk9TLephxj1GQDHmzIGYEe8gllddUgf7ZmeUvEtSWuNwi5dAn9bZiy5DR8aJpWYg9nEM+Vx6hi0uokpWH+ckwERSilnfLclLFeMg4NjE+fVoEWT/MXNbMR7y/Ng8TEE/3q1rOB72gk/AIDCbSXXN+OUKe0pCDCK41wmCpNOVO2S5JD2/RI9ZVFa7fNyLV/aZ6lMWQ9hV1dKdqk6x8Zq7dVTy+y1DmcWsJmLKG0gkvRj6GqP9aiHeH1ERynIWqghGMH7LqlSlNTehC+GTS7/ZPWCSJZIms3nht416FAiG7eGBkbbjuKKaffdFVuRFPPsZ0AqWV3/TG69I+uB8w==
*/