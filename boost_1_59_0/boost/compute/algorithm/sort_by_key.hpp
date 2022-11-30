//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_SORT_BY_KEY_HPP
#define BOOST_COMPUTE_ALGORITHM_SORT_BY_KEY_HPP

#include <iterator>

#include <boost/static_assert.hpp>
#include <boost/utility/enable_if.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/detail/merge_sort_on_cpu.hpp>
#include <boost/compute/algorithm/detail/merge_sort_on_gpu.hpp>
#include <boost/compute/algorithm/detail/insertion_sort.hpp>
#include <boost/compute/algorithm/detail/radix_sort.hpp>
#include <boost/compute/algorithm/reverse.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class KeyIterator, class ValueIterator>
inline void
dispatch_gpu_sort_by_key(KeyIterator keys_first,
                         KeyIterator keys_last,
                         ValueIterator values_first,
                         less<typename std::iterator_traits<KeyIterator>::value_type> compare,
                         command_queue &queue,
                         typename boost::enable_if_c<
                             is_radix_sortable<
                                 typename std::iterator_traits<KeyIterator>::value_type
                             >::value
                         >::type* = 0)
{
    size_t count = detail::iterator_range_size(keys_first, keys_last);

    if(count < 32){
        detail::serial_insertion_sort_by_key(
            keys_first, keys_last, values_first, compare, queue
        );
    }
    else {
        detail::radix_sort_by_key(
            keys_first, keys_last, values_first, queue
        );
    }
}

template<class KeyIterator, class ValueIterator>
inline void
dispatch_gpu_sort_by_key(KeyIterator keys_first,
                         KeyIterator keys_last,
                         ValueIterator values_first,
                         greater<typename std::iterator_traits<KeyIterator>::value_type> compare,
                         command_queue &queue,
                         typename boost::enable_if_c<
                             is_radix_sortable<
                                 typename std::iterator_traits<KeyIterator>::value_type
                             >::value
                         >::type* = 0)
{
    size_t count = detail::iterator_range_size(keys_first, keys_last);

    if(count < 32){
        detail::serial_insertion_sort_by_key(
            keys_first, keys_last, values_first, compare, queue
        );
    }
    else {
        // radix sorts in descending order
        detail::radix_sort_by_key(
            keys_first, keys_last, values_first, false, queue
        );
    }
}

template<class KeyIterator, class ValueIterator, class Compare>
inline void dispatch_gpu_sort_by_key(KeyIterator keys_first,
                                     KeyIterator keys_last,
                                     ValueIterator values_first,
                                     Compare compare,
                                     command_queue &queue)
{
    size_t count = detail::iterator_range_size(keys_first, keys_last);

    if(count < 32){
        detail::serial_insertion_sort_by_key(
            keys_first, keys_last, values_first, compare, queue
        );
    } else {
        detail::merge_sort_by_key_on_gpu(
            keys_first, keys_last, values_first, compare, queue
        );
    }
}

template<class KeyIterator, class ValueIterator, class Compare>
inline void dispatch_sort_by_key(KeyIterator keys_first,
                                 KeyIterator keys_last,
                                 ValueIterator values_first,
                                 Compare compare,
                                 command_queue &queue)
{
    if(queue.get_device().type() & device::gpu) {
        dispatch_gpu_sort_by_key(keys_first, keys_last, values_first, compare, queue);
        return;
    }
    ::boost::compute::detail::merge_sort_by_key_on_cpu(
        keys_first, keys_last, values_first, compare, queue
    );
}

} // end detail namespace

/// Performs a key-value sort using the keys in the range [\p keys_first,
/// \p keys_last) on the values in the range [\p values_first,
/// \p values_first \c + (\p keys_last \c - \p keys_first)) using \p compare.
///
/// If no compare function is specified, \c less is used.
///
/// Space complexity: \Omega(2n)
///
/// \see sort()
template<class KeyIterator, class ValueIterator, class Compare>
inline void sort_by_key(KeyIterator keys_first,
                        KeyIterator keys_last,
                        ValueIterator values_first,
                        Compare compare,
                        command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<KeyIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<ValueIterator>::value);
    ::boost::compute::detail::dispatch_sort_by_key(
        keys_first, keys_last, values_first, compare, queue
    );
}

/// \overload
template<class KeyIterator, class ValueIterator>
inline void sort_by_key(KeyIterator keys_first,
                        KeyIterator keys_last,
                        ValueIterator values_first,
                        command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<KeyIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<ValueIterator>::value);
    typedef typename std::iterator_traits<KeyIterator>::value_type key_type;

    ::boost::compute::sort_by_key(
        keys_first, keys_last, values_first, less<key_type>(), queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_SORT_BY_KEY_HPP

/* sort_by_key.hpp
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
*/