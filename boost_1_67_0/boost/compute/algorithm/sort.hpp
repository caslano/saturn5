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