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