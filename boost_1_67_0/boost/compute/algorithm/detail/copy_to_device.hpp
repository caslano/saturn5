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