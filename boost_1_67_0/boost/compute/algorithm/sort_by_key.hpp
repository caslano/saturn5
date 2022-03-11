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