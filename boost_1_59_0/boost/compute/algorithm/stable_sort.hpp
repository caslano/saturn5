//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_STABLE_SORT_HPP
#define BOOST_COMPUTE_ALGORITHM_STABLE_SORT_HPP

#include <iterator>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/detail/merge_sort_on_cpu.hpp>
#include <boost/compute/algorithm/detail/merge_sort_on_gpu.hpp>
#include <boost/compute/algorithm/detail/radix_sort.hpp>
#include <boost/compute/algorithm/detail/insertion_sort.hpp>
#include <boost/compute/algorithm/reverse.hpp>
#include <boost/compute/functional/operator.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class Iterator, class Compare>
inline void dispatch_gpu_stable_sort(Iterator first,
                                     Iterator last,
                                     Compare compare,
                                     command_queue &queue)
{
    size_t count = detail::iterator_range_size(first, last);

    if(count < 32){
        detail::serial_insertion_sort(
            first, last, compare, queue
        );
    } else {
        detail::merge_sort_on_gpu(
            first, last, compare, true /* stable */, queue
        );
    }
}

template<class T>
inline typename boost::enable_if_c<is_radix_sortable<T>::value>::type
dispatch_gpu_stable_sort(buffer_iterator<T> first,
                         buffer_iterator<T> last,
                         less<T>,
                         command_queue &queue)
{
    ::boost::compute::detail::radix_sort(first, last, queue);
}

template<class T>
inline typename boost::enable_if_c<is_radix_sortable<T>::value>::type
dispatch_gpu_stable_sort(buffer_iterator<T> first,
                         buffer_iterator<T> last,
                         greater<T>,
                         command_queue &queue)
{
    // radix sorts in descending order
    ::boost::compute::detail::radix_sort(first, last, false, queue);
}

} // end detail namespace

/// Sorts the values in the range [\p first, \p last) according to
/// \p compare. The relative order of identical values is preserved.
///
/// Space complexity: \Omega(n)
///
/// \see sort(), is_sorted()
template<class Iterator, class Compare>
inline void stable_sort(Iterator first,
                        Iterator last,
                        Compare compare,
                        command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator>::value);

    if(queue.get_device().type() & device::gpu) {
        ::boost::compute::detail::dispatch_gpu_stable_sort(
            first, last, compare, queue
        );
        return;
    }
    ::boost::compute::detail::merge_sort_on_cpu(first, last, compare, queue);
}

/// \overload
template<class Iterator>
inline void stable_sort(Iterator first,
                        Iterator last,
                        command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator>::value);
    typedef typename std::iterator_traits<Iterator>::value_type value_type;

    ::boost::compute::less<value_type> less;

    ::boost::compute::stable_sort(first, last, less, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_STABLE_SORT_HPP

/* stable_sort.hpp
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
*/