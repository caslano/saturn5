//---------------------------------------------------------------------------//
// Copyright (c) 2015 Jakub Szuppe <j.szuppe@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_REDUCE_BY_KEY_HPP
#define BOOST_COMPUTE_ALGORITHM_REDUCE_BY_KEY_HPP

#include <iterator>
#include <utility>

#include <boost/static_assert.hpp>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/device.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/detail/reduce_by_key.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// The \c reduce_by_key() algorithm performs reduction for each contiguous
/// subsequence of values determinate by equivalent keys.
///
/// Returns a pair of iterators at the end of the ranges [\p keys_result, keys_result_last)
/// and [\p values_result, \p values_result_last).
///
/// If no function is specified, \c plus will be used.
/// If no predicate is specified, \c equal_to will be used.
///
/// \param keys_first the first key
/// \param keys_last the last key
/// \param values_first the first input value
/// \param keys_result iterator pointing to the key output
/// \param values_result iterator pointing to the reduced value output
/// \param function binary reduction function
/// \param predicate binary predicate which returns true only if two keys are equal
/// \param queue command queue to perform the operation
///
/// The \c reduce_by_key() algorithm assumes that the binary reduction function
/// is associative. When used with non-associative functions the result may
/// be non-deterministic and vary in precision. Notably this affects the
/// \c plus<float>() function as floating-point addition is not associative
/// and may produce slightly different results than a serial algorithm.
///
/// For example, to calculate the sum of the values for each key:
///
/// \snippet test/test_reduce_by_key.cpp reduce_by_key_int
///
/// Space complexity on GPUs: \Omega(2n)<br>
/// Space complexity on CPUs: \Omega(1)
///
/// \see reduce()
template<class InputKeyIterator, class InputValueIterator,
         class OutputKeyIterator, class OutputValueIterator,
         class BinaryFunction, class BinaryPredicate>
inline std::pair<OutputKeyIterator, OutputValueIterator>
reduce_by_key(InputKeyIterator keys_first,
              InputKeyIterator keys_last,
              InputValueIterator values_first,
              OutputKeyIterator keys_result,
              OutputValueIterator values_result,
              BinaryFunction function,
              BinaryPredicate predicate,
              command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputKeyIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputValueIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputKeyIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputValueIterator>::value);

    return detail::dispatch_reduce_by_key(keys_first, keys_last, values_first,
                                          keys_result, values_result,
                                          function, predicate,
                                          queue);
}

/// \overload
template<class InputKeyIterator, class InputValueIterator,
         class OutputKeyIterator, class OutputValueIterator,
         class BinaryFunction>
inline std::pair<OutputKeyIterator, OutputValueIterator>
reduce_by_key(InputKeyIterator keys_first,
              InputKeyIterator keys_last,
              InputValueIterator values_first,
              OutputKeyIterator keys_result,
              OutputValueIterator values_result,
              BinaryFunction function,
              command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputKeyIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputValueIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputKeyIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputValueIterator>::value);
    typedef typename std::iterator_traits<InputKeyIterator>::value_type key_type;

    return reduce_by_key(keys_first, keys_last, values_first,
                         keys_result, values_result,
                         function, equal_to<key_type>(),
                         queue);
}

/// \overload
template<class InputKeyIterator, class InputValueIterator,
         class OutputKeyIterator, class OutputValueIterator>
inline std::pair<OutputKeyIterator, OutputValueIterator>
reduce_by_key(InputKeyIterator keys_first,
              InputKeyIterator keys_last,
              InputValueIterator values_first,
              OutputKeyIterator keys_result,
              OutputValueIterator values_result,
              command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputKeyIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputValueIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputKeyIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputValueIterator>::value);
    typedef typename std::iterator_traits<InputKeyIterator>::value_type key_type;
    typedef typename std::iterator_traits<InputValueIterator>::value_type value_type;

    return reduce_by_key(keys_first, keys_last, values_first,
                         keys_result, values_result,
                         plus<value_type>(), equal_to<key_type>(),
                         queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_REDUCE_BY_KEY_HPP

/* reduce_by_key.hpp
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
*/