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
87eOc66zIxH/1pymsT75OPV0+L04/sEWjC109zhASdaBhLEmrvNs6tT8a9bp1PfPWOfPHb+wzvH5EqivngvYOnd7uav5+mHI2dc5IU5gSzuBZWNddTyNXSVClXEGVF3bnrw6ruAE/pY6ta1/hDr9+K/xCZQSZ/DokLPPYNL8AZyDGJxzWJd3PZswfQTnQ0POC84cMRHObW0EZwVD6qlvd0bqDySiuc8N/kWae+Ya3U199xz5B+p7wxtdrdF1g893LzrERDokMLgbGKqv+nP8pEiaX8vgX5jfc83Na630DfdD9A3/42fMDXyAwX9uWncuejqBfcPBvlHzeGd6yil900XnPf9AC9n0f0t66Z5/ZXi95F1OChNnv21Ql7Pfxd59ljozS6yzW/99xt4tHtQZ++J06TZ4uQxd2SO21a8bDOoozPv2Bqq3X32ITDLwoJl+V9E82H71Onn6SoK7lrFCQL5WDYqTr1+e1++b2TlVRfBe/+4Z5xTD66MDf2FeE+fgqWY2DGB/M97nwxhBYB+T9WFMoN/bZaqh9Z/3aBhewV1NNTw/hHl6nb64p9NGPQs9iY9nCBuPlc3/Zxvi40nC9wUDz47v6108TipibruG1VRu628wJMcJHbkmIWb4YH89gqqCi+dPpHaOoGLxDFSLcgfwmWKkMEOz/arKGMujnlWnHOzZop3NXv8NugogyfiA3p7aS7MNrOIxJtXB
*/