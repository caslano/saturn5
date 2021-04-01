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
Ig19qt1ZD9OTvscRDD9XaWFXgMvGgnClQIYCeDmIMNm9djzd3uI8XjXpqMCFZKjpFIvDO+x/binvZSw0RtDh5lZ2eyLdZvSEBybJCjQ7rpsjPHqMI6a58JKMpZeOpUkpufJLMK2nOpnHFybGohqXvuhYTbQMhPNLSIubzRrQgOd38+eKZJxFDhUhY1EQSsCAi5Z8C2xGy5t7cemH5XTtdKJmbuJW4TBTJI1jqMJSJm8JPpsMhb6Q1YYbNMS/o1AM9DEenKTgdPtMXbkZrEv26yRX+xl/OytewgiSK0nQP0+EHsu4pGPM4NAOi/O1iTKgMSC6J6kBl23d9iwPM8laQ/BGrlBkeW7ZqNnGEoIajiDHbqH77jFSY7+qvjsrT84Z0fxY3psXYs3KPqQVTm4h7jKe/uXyCeAJybXP8asHedxi5DKNYtwqN0PYBDMhXqIC8u4pTgoF7nLjaPd6FRdyuykEnFScb9Auy9Pf1GIUep12Gbk+H0MzqZ8S62e8sdndfRnuL/oY7p0syF4/7fIdN4FKV3zySX5RSUqTYcUYipyz/r576AlMZZeC4w==
*/