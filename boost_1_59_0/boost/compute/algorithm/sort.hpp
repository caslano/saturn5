//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_SORT_HPP
#define BOOST_COMPUTE_ALGORITHM_SORT_HPP

#include <iterator>

#include <boost/utility/enable_if.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/detail/merge_sort_on_cpu.hpp>
#include <boost/compute/algorithm/detail/merge_sort_on_gpu.hpp>
#include <boost/compute/algorithm/detail/radix_sort.hpp>
#include <boost/compute/algorithm/detail/insertion_sort.hpp>
#include <boost/compute/algorithm/reverse.hpp>
#include <boost/compute/container/mapped_view.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class T>
inline void dispatch_gpu_sort(buffer_iterator<T> first,
                              buffer_iterator<T> last,
                              less<T>,
                              command_queue &queue,
                              typename boost::enable_if_c<
                                  is_radix_sortable<T>::value
                              >::type* = 0)
{
    size_t count = detail::iterator_range_size(first, last);

    if(count < 2){
        // nothing to do
        return;
    }
    else if(count <= 32){
        ::boost::compute::detail::serial_insertion_sort(first, last, queue);
    }
    else {
        ::boost::compute::detail::radix_sort(first, last, queue);
    }
}

template<class T>
inline void dispatch_gpu_sort(buffer_iterator<T> first,
                              buffer_iterator<T> last,
                              greater<T> compare,
                              command_queue &queue,
                              typename boost::enable_if_c<
                                  is_radix_sortable<T>::value
                              >::type* = 0)
{
    size_t count = detail::iterator_range_size(first, last);

    if(count < 2){
        // nothing to do
        return;
    }
    else if(count <= 32){
        ::boost::compute::detail::serial_insertion_sort(
            first, last, compare, queue
        );
    }
    else {
        // radix sorts in descending order
        ::boost::compute::detail::radix_sort(first, last, false, queue);
    }
}

template<class Iterator, class Compare>
inline void dispatch_gpu_sort(Iterator first,
                              Iterator last,
                              Compare compare,
                              command_queue &queue)
{
    size_t count = detail::iterator_range_size(first, last);

    if(count < 2){
        // nothing to do
        return;
    }
    else if(count <= 32){
        ::boost::compute::detail::serial_insertion_sort(
            first, last, compare, queue
        );
    }
    else {
        ::boost::compute::detail::merge_sort_on_gpu(
            first, last, compare, queue
        );
    }
}

// sort() for device iterators
template<class Iterator, class Compare>
inline void dispatch_sort(Iterator first,
                          Iterator last,
                          Compare compare,
                          command_queue &queue,
                          typename boost::enable_if<
                              is_device_iterator<Iterator>
                          >::type* = 0)
{
    if(queue.get_device().type() & device::gpu) {
        dispatch_gpu_sort(first, last, compare, queue);
        return;
    }
    ::boost::compute::detail::merge_sort_on_cpu(first, last, compare, queue);
}

// sort() for host iterators
template<class Iterator, class Compare>
inline void dispatch_sort(Iterator first,
                          Iterator last,
                          Compare compare,
                          command_queue &queue,
                          typename boost::disable_if<
                              is_device_iterator<Iterator>
                          >::type* = 0)
{
    typedef typename std::iterator_traits<Iterator>::value_type T;

    size_t size = static_cast<size_t>(std::distance(first, last));

    // create mapped buffer
    mapped_view<T> view(
        boost::addressof(*first), size, queue.get_context()
    );

    // sort mapped buffer
    dispatch_sort(view.begin(), view.end(), compare, queue);

    // return results to host
    view.map(queue);
}

} // end detail namespace

/// Sorts the values in the range [\p first, \p last) according to
/// \p compare.
///
/// \param first first element in the range to sort
/// \param last last element in the range to sort
/// \param compare comparison function (by default \c less)
/// \param queue command queue to perform the operation
///
/// For example, to sort a vector on the device:
/// \code
/// // create vector on the device with data
/// float data[] = { 2.f, 4.f, 1.f, 3.f };
/// boost::compute::vector<float> vec(data, data + 4, queue);
///
/// // sort the vector on the device
/// boost::compute::sort(vec.begin(), vec.end(), queue);
/// \endcode
///
/// The sort() algorithm can also be directly used with host iterators. This
/// example will automatically transfer the data to the device, sort it, and
/// then transfer the data back to the host:
/// \code
/// std::vector<int> data = { 9, 3, 2, 5, 1, 4, 6, 7 };
///
/// boost::compute::sort(data.begin(), data.end(), queue);
/// \endcode
///
/// Space complexity: \Omega(n)
///
/// \see is_sorted()
template<class Iterator, class Compare>
inline void sort(Iterator first,
                 Iterator last,
                 Compare compare,
                 command_queue &queue = system::default_queue())
{
    ::boost::compute::detail::dispatch_sort(first, last, compare, queue);
}

/// \overload
template<class Iterator>
inline void sort(Iterator first,
                 Iterator last,
                 command_queue &queue = system::default_queue())
{
    typedef typename std::iterator_traits<Iterator>::value_type value_type;

    ::boost::compute::sort(
        first, last, ::boost::compute::less<value_type>(), queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_SORT_HPP

/* sort.hpp
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
*/