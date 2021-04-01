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
eIUPEnisjwvsyvYhDpulG2pFfBUnCz8cTETyK/5jFKuAmirA94Gih8gfvGMZ3CA5+tL3AmevPDGQYL9gp8Ic8A0d4r2s3iEUckp9AVMGS1lfj4T1Ab3eYBa5AWTYRanLtyUdi1sL+K7OmpTRl8UDRiPSCSQ3YFRmm6C/bcCxEBPU3Zi8O2FDx50cPpICgjcYjD5QQEP895k3p3eeEGqPvSIGPIC5hauLdoIjDtFfD+itXqgWP7XTo8CZkOiq1bcyTBODbmeLL9I17OFzUjihVgdH5DD3ry0HcsPZCu8XShQNKjS1yWoehk5/sDcSG96azrG7JoYTYZATv63TeGMLmZP6bHKOH+wIDk4xcJugrn8NxIqV2DuBkC7RfmciUll85luSy9u7LaRW71DmKQeYLmlbRLylBi9rtPN6s0GHndoLXx1i6WGTF786g6kW39VYjqBsn91eROaBEi2gTHlB7liIsgiJzNVOCRx6nZ890Mf6ZiiFACJ/iToVh3sSB5fuOhS9JI5eRdbDCsYaSBzSLYYtQX0CWoxGTbcCYDabLGX+h0LhUDOp+kD6AQ==
*/