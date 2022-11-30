//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_COPY_TO_HOST_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_COPY_TO_HOST_HPP

#include <iterator>

#include <boost/utility/addressof.hpp>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/async/future.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>
#include <boost/compute/memory/svm_ptr.hpp>
#include <boost/compute/detail/iterator_plus_distance.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class DeviceIterator, class HostIterator>
inline HostIterator copy_to_host(DeviceIterator first,
                                 DeviceIterator last,
                                 HostIterator result,
                                 command_queue &queue,
                                 const wait_list &events)
{
    typedef typename
        std::iterator_traits<DeviceIterator>::value_type
        value_type;

    size_t count = iterator_range_size(first, last);
    if(count == 0){
        return result;
    }

    const buffer &buffer = first.get_buffer();
    size_t offset = first.get_index();

    queue.enqueue_read_buffer(buffer,
                              offset * sizeof(value_type),
                              count * sizeof(value_type),
                              ::boost::addressof(*result),
                              events);

    return iterator_plus_distance(result, count);
}

template<class DeviceIterator, class HostIterator>
inline HostIterator copy_to_host_map(DeviceIterator first,
                                     DeviceIterator last,
                                     HostIterator result,
                                     command_queue &queue,
                                     const wait_list &events)
{
    typedef typename
        std::iterator_traits<DeviceIterator>::value_type
        value_type;
    typedef typename
        std::iterator_traits<DeviceIterator>::difference_type
        difference_type;

    size_t count = iterator_range_size(first, last);
    if(count == 0){
        return result;
    }

    size_t offset = first.get_index();

    // map [first; last) buffer to host
    value_type *pointer = static_cast<value_type*>(
        queue.enqueue_map_buffer(
            first.get_buffer(),
            CL_MAP_READ,
            offset * sizeof(value_type),
            count * sizeof(value_type),
            events
        )
    );

    // copy [first; last) to result buffer
    std::copy(
        pointer,
        pointer + static_cast<difference_type>(count),
        result
    );

    // unmap [first; last)
    boost::compute::event unmap_event = queue.enqueue_unmap_buffer(
        first.get_buffer(),
        static_cast<void*>(pointer)
    );
    unmap_event.wait();

    return iterator_plus_distance(result, count);
}

template<class DeviceIterator, class HostIterator>
inline future<HostIterator> copy_to_host_async(DeviceIterator first,
                                               DeviceIterator last,
                                               HostIterator result,
                                               command_queue &queue,
                                               const wait_list &events)
{
    typedef typename
        std::iterator_traits<DeviceIterator>::value_type
        value_type;

    size_t count = iterator_range_size(first, last);
    if(count == 0){
        return future<HostIterator>();
    }

    const buffer &buffer = first.get_buffer();
    size_t offset = first.get_index();

    event event_ =
        queue.enqueue_read_buffer_async(buffer,
                                        offset * sizeof(value_type),
                                        count * sizeof(value_type),
                                        ::boost::addressof(*result),
                                        events);

    return make_future(iterator_plus_distance(result, count), event_);
}

#ifdef BOOST_COMPUTE_CL_VERSION_2_0
// copy_to_host() specialization for svm_ptr
template<class T, class HostIterator>
inline HostIterator copy_to_host(svm_ptr<T> first,
                                 svm_ptr<T> last,
                                 HostIterator result,
                                 command_queue &queue,
                                 const wait_list &events)
{
    size_t count = iterator_range_size(first, last);
    if(count == 0){
        return result;
    }

    queue.enqueue_svm_memcpy(
        ::boost::addressof(*result), first.get(), count * sizeof(T), events
    );

    return result + count;
}

template<class T, class HostIterator>
inline future<HostIterator> copy_to_host_async(svm_ptr<T> first,
                                               svm_ptr<T> last,
                                               HostIterator result,
                                               command_queue &queue,
                                               const wait_list &events)
{
    size_t count = iterator_range_size(first, last);
    if(count == 0){
        return future<HostIterator>();
    }

    event event_ = queue.enqueue_svm_memcpy_async(
        ::boost::addressof(*result), first.get(), count * sizeof(T), events
    );

    return make_future(iterator_plus_distance(result, count), event_);
}

template<class T, class HostIterator>
inline HostIterator copy_to_host_map(svm_ptr<T> first,
                                     svm_ptr<T> last,
                                     HostIterator result,
                                     command_queue &queue,
                                     const wait_list &events)
{
    size_t count = iterator_range_size(first, last);
    if(count == 0){
        return result;
    }

    // map
    queue.enqueue_svm_map(first.get(), count * sizeof(T), CL_MAP_READ, events);

    // copy [first; last) to result
    std::copy(
        static_cast<T*>(first.get()),
        static_cast<T*>(last.get()),
        result
    );

    // unmap [first; last)
    queue.enqueue_svm_unmap(first.get()).wait();

    return iterator_plus_distance(result, count);
}
#endif // BOOST_COMPUTE_CL_VERSION_2_0

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_COPY_TO_HOST_HPP

/* copy_to_host.hpp
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
*/