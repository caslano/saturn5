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
yMg8ysqRJahrrhV+N1yvYP8nByiBNEEx0EqSa23Ye/Vy+cv4fMaHa6wDEUImqkrpdWSlOzuES67KyQfh/OrgqjyD5GpHoigiPLPVA0NRZqCBwkinv/T0q7QGNZQYLqqtckyItblhcgEr8WJn0r4ysAh7q1N3ByoSa7KKoCOpOhPQApPsKKNmLuD82bHJKxmeo88RB04UtAZsZUkyiRwD5YN8Y5XCrttaIvYQpQ3aBem2qqgxyAdpg4nhORCd0IlZhZbLAHaN7CPmNyBtwOuD6RqZq5Ip9K6JDBwX0Sb5RubXsA0OwFeOzJ0t/LCHepj1fxfsP406gNyDfV97fwA0RdDJnwdNA9CJtBbQc6MLxbmGbi3xqNcRuDYfyuCuw5pXO+qqNmXjIlmwYVsFMyDRC4wNz56jIUqd7JdZlxkZze4KBObuXWT8G/R36fyQT3RbY7y54wsAyegdFNBDBoFiSBkCCy4FipXMBVNHd4N7h0UcUNtcvqisWgJtoAbBF7igG+Oc4nGEA41hx+6REdxaG62AL9mijyKUzsDDPkwILTOgb7XwEip4UGLu8oyZw36tzRb0CfLELrsqWN5hSkT0F1DnBv1Yco9vHYPr+S4L004UJ+NksRWK0wnzGQB3dAe9SWNNzkcYFTPJJ9kH
*/