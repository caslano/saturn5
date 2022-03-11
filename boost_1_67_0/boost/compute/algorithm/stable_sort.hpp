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