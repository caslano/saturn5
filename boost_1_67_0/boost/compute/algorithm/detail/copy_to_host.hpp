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