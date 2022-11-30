//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_COPY_TO_DEVICE_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_COPY_TO_DEVICE_HPP

#include <iterator>

#include <boost/utility/addressof.hpp>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/async/future.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>
#include <boost/compute/memory/svm_ptr.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class HostIterator, class DeviceIterator>
inline DeviceIterator copy_to_device(HostIterator first,
                                     HostIterator last,
                                     DeviceIterator result,
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

    size_t offset = result.get_index();

    queue.enqueue_write_buffer(result.get_buffer(),
                               offset * sizeof(value_type),
                               count * sizeof(value_type),
                               ::boost::addressof(*first),
                               events);

    return result + static_cast<difference_type>(count);
}

template<class HostIterator, class DeviceIterator>
inline DeviceIterator copy_to_device_map(HostIterator first,
                                         HostIterator last,
                                         DeviceIterator result,
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

    size_t offset = result.get_index();

    // map result buffer to host
    value_type *pointer = static_cast<value_type*>(
        queue.enqueue_map_buffer(
            result.get_buffer(),
            CL_MAP_WRITE,
            offset * sizeof(value_type),
            count * sizeof(value_type),
            events
        )
    );

    // copy [first; last) to result buffer
    std::copy(first, last, pointer);

    // unmap result buffer
    boost::compute::event unmap_event = queue.enqueue_unmap_buffer(
        result.get_buffer(),
        static_cast<void*>(pointer)
    );
    unmap_event.wait();

    return result + static_cast<difference_type>(count);
}

template<class HostIterator, class DeviceIterator>
inline future<DeviceIterator> copy_to_device_async(HostIterator first,
                                                   HostIterator last,
                                                   DeviceIterator result,
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
        return future<DeviceIterator>();
    }

    size_t offset = result.get_index();

    event event_ =
        queue.enqueue_write_buffer_async(result.get_buffer(),
                                         offset * sizeof(value_type),
                                         count * sizeof(value_type),
                                         ::boost::addressof(*first),
                                         events);

    return make_future(result + static_cast<difference_type>(count), event_);
}

#ifdef BOOST_COMPUTE_CL_VERSION_2_0
// copy_to_device() specialization for svm_ptr
template<class HostIterator, class T>
inline svm_ptr<T> copy_to_device(HostIterator first,
                                 HostIterator last,
                                 svm_ptr<T> result,
                                 command_queue &queue,
                                 const wait_list &events)
{
    size_t count = iterator_range_size(first, last);
    if(count == 0){
        return result;
    }

    queue.enqueue_svm_memcpy(
        result.get(), ::boost::addressof(*first), count * sizeof(T), events
    );

    return result + count;
}

template<class HostIterator, class T>
inline future<svm_ptr<T> > copy_to_device_async(HostIterator first,
                                                HostIterator last,
                                                svm_ptr<T> result,
                                                command_queue &queue,
                                                const wait_list &events)
{
    size_t count = iterator_range_size(first, last);
    if(count == 0){
        return future<svm_ptr<T> >();
    }

    event event_ = queue.enqueue_svm_memcpy_async(
        result.get(), ::boost::addressof(*first), count * sizeof(T), events
    );

    return make_future(result + count, event_);
}

template<class HostIterator, class T>
inline svm_ptr<T> copy_to_device_map(HostIterator first,
                                              HostIterator last,
                                              svm_ptr<T> result,
                                              command_queue &queue,
                                              const wait_list &events)
{
    size_t count = iterator_range_size(first, last);
    if(count == 0){
        return result;
    }

    // map
    queue.enqueue_svm_map(
        result.get(), count * sizeof(T), CL_MAP_WRITE, events
    );

    // copy [first; last) to result buffer
    std::copy(first, last, static_cast<T*>(result.get()));

    // unmap result
    queue.enqueue_svm_unmap(result.get()).wait();

    return result + count;
}
#endif // BOOST_COMPUTE_CL_VERSION_2_0

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_COPY_TO_DEVICE_HPP

/* copy_to_device.hpp
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
*/