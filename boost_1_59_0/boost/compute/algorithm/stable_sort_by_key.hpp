//---------------------------------------------------------------------------//
// Copyright (c) 2016 Jakub Szuppe <j.szuppe@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_STABLE_SORT_BY_KEY_HPP
#define BOOST_COMPUTE_ALGORITHM_STABLE_SORT_BY_KEY_HPP

#include <iterator>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/sort_by_key.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

namespace detail {

template<class KeyIterator, class ValueIterator>
inline void
dispatch_gpu_ssort_by_key(KeyIterator keys_first,
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
dispatch_gpu_ssort_by_key(KeyIterator keys_first,
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
inline void dispatch_gpu_ssort_by_key(KeyIterator keys_first,
                                      KeyIterator keys_last,
                                      ValueIterator values_first,
                                      Compare compare,
                                      command_queue &queue)
{
    size_t count = detail::iterator_range_size(keys_first, keys_last);

    if(count < 32){
        detail::serial_insertion_sort_by_key(
            keys_first, keys_last, values_first,
            compare, queue
        );
    } else {
        detail::merge_sort_by_key_on_gpu(
            keys_first, keys_last, values_first,
            compare, true /* stable */, queue
        );
    }
}

template<class KeyIterator, class ValueIterator, class Compare>
inline void dispatch_ssort_by_key(KeyIterator keys_first,
                                  KeyIterator keys_last,
                                  ValueIterator values_first,
                                  Compare compare,
                                  command_queue &queue)
{
    if(queue.get_device().type() & device::gpu) {
        dispatch_gpu_ssort_by_key(
            keys_first, keys_last, values_first, compare, queue
        );
        return;
    }
    ::boost::compute::detail::merge_sort_by_key_on_cpu(
        keys_first, keys_last, values_first, compare, queue
    );
}

} // end detail namespace

/// Performs a key-value stable sort using the keys in the range [\p keys_first,
/// \p keys_last) on the values in the range [\p values_first,
/// \p values_first \c + (\p keys_last \c - \p keys_first)) using \p compare.
///
/// If no compare function is specified, \c less is used.
///
/// Space complexity: \Omega(2n)
///
/// \see sort()
template<class KeyIterator, class ValueIterator, class Compare>
inline void stable_sort_by_key(KeyIterator keys_first,
                               KeyIterator keys_last,
                               ValueIterator values_first,
                               Compare compare,
                               command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<KeyIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<ValueIterator>::value);
    ::boost::compute::detail::dispatch_ssort_by_key(
        keys_first, keys_last, values_first, compare, queue
    );
}

/// \overload
template<class KeyIterator, class ValueIterator>
inline void stable_sort_by_key(KeyIterator keys_first,
                               KeyIterator keys_last,
                               ValueIterator values_first,
                               command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<KeyIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<ValueIterator>::value);
    typedef typename std::iterator_traits<KeyIterator>::value_type key_type;

    ::boost::compute::stable_sort_by_key(
        keys_first, keys_last, values_first, less<key_type>(), queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_STABLE_SORT_BY_KEY_HPP

/* stable_sort_by_key.hpp
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
*/