//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_COPY_HPP
#define BOOST_COMPUTE_ALGORITHM_COPY_HPP

#include <algorithm>
#include <iterator>

#include <boost/utility/enable_if.hpp>

#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>

#include <boost/compute/buffer.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/detail/copy_on_device.hpp>
#include <boost/compute/algorithm/detail/copy_to_device.hpp>
#include <boost/compute/algorithm/detail/copy_to_host.hpp>
#include <boost/compute/async/future.hpp>
#include <boost/compute/container/mapped_view.hpp>
#include <boost/compute/detail/device_ptr.hpp>
#include <boost/compute/detail/is_contiguous_iterator.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/parameter_cache.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>
#include <boost/compute/type_traits/type_name.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

namespace mpl = boost::mpl;

// meta-function returning true if copy() between InputIterator and
// OutputIterator can be implemented with clEnqueueCopyBuffer().
template<class InputIterator, class OutputIterator>
struct can_copy_with_copy_buffer :
    mpl::and_<
        mpl::or_<
            boost::is_same<
                InputIterator,
                buffer_iterator<typename InputIterator::value_type>
            >,
            boost::is_same<
                InputIterator,
                detail::device_ptr<typename InputIterator::value_type>
            >
        >,
        mpl::or_<
            boost::is_same<
                OutputIterator,
                buffer_iterator<typename OutputIterator::value_type>
            >,
            boost::is_same<
                OutputIterator,
                detail::device_ptr<typename OutputIterator::value_type>
            >
        >,
        boost::is_same<
            typename InputIterator::value_type,
            typename OutputIterator::value_type
        >
    >::type {};

// meta-function returning true if value_types of HostIterator and
// DeviceIterator are same
template<class HostIterator, class DeviceIterator>
struct is_same_value_type :
    boost::is_same<
        typename boost::remove_cv<
            typename std::iterator_traits<HostIterator>::value_type
        >::type,
        typename boost::remove_cv<
            typename DeviceIterator::value_type
        >::type
    >::type {};

// meta-function returning true if value_type of HostIterator is bool
template<class HostIterator>
struct is_bool_value_type :
    boost::is_same<
        typename boost::remove_cv<
            typename std::iterator_traits<HostIterator>::value_type
        >::type,
        bool
    >::type {};

// host -> device (async)
template<class InputIterator, class OutputIterator>
inline future<OutputIterator>
dispatch_copy_async(InputIterator first,
                    InputIterator last,
                    OutputIterator result,
                    command_queue &queue,
                    const wait_list &events,
                    typename boost::enable_if<
                        mpl::and_<
                            mpl::not_<
                                is_device_iterator<InputIterator>
                            >,
                            is_device_iterator<OutputIterator>,
                            is_same_value_type<InputIterator, OutputIterator>
                        >
                    >::type* = 0)
{
    BOOST_STATIC_ASSERT_MSG(
        is_contiguous_iterator<InputIterator>::value,
        "copy_async() is only supported for contiguous host iterators"
    );

    return copy_to_device_async(first, last, result, queue, events);
}

// host -> device (async)
// Type mismatch between InputIterator and OutputIterator value_types
template<class InputIterator, class OutputIterator>
inline future<OutputIterator>
dispatch_copy_async(InputIterator first,
                    InputIterator last,
                    OutputIterator result,
                    command_queue &queue,
                    const wait_list &events,
                    typename boost::enable_if<
                        mpl::and_<
                            mpl::not_<
                                is_device_iterator<InputIterator>
                            >,
                            is_device_iterator<OutputIterator>,
                            mpl::not_<
                                is_same_value_type<InputIterator, OutputIterator>
                            >
                        >
                    >::type* = 0)
{
    BOOST_STATIC_ASSERT_MSG(
        is_contiguous_iterator<InputIterator>::value,
        "copy_async() is only supported for contiguous host iterators"
    );

    typedef typename std::iterator_traits<InputIterator>::value_type input_type;

    const context &context = queue.get_context();
    size_t count = iterator_range_size(first, last);

    if(count < size_t(1)) {
        return future<OutputIterator>();
    }

    // map [first; last) to device and run copy kernel
    // on device for copying & casting
    ::boost::compute::mapped_view<input_type> mapped_host(
        // make sure it's a pointer to constant data
        // to force read only mapping
        const_cast<const input_type*>(
            ::boost::addressof(*first)
        ),
        count,
        context
    );
    return copy_on_device_async(
        mapped_host.begin(), mapped_host.end(), result, queue, events
    );
}

// host -> device
// InputIterator is a contiguous iterator
template<class InputIterator, class OutputIterator>
inline OutputIterator
dispatch_copy(InputIterator first,
              InputIterator last,
              OutputIterator result,
              command_queue &queue,
              const wait_list &events,
              typename boost::enable_if<
                  mpl::and_<
                      mpl::not_<
                          is_device_iterator<InputIterator>
                      >,
                      is_device_iterator<OutputIterator>,
                      is_same_value_type<InputIterator, OutputIterator>,
                      is_contiguous_iterator<InputIterator>
                  >
              >::type* = 0)
{
    return copy_to_device(first, last, result, queue, events);
}

// host -> device
// Type mismatch between InputIterator and OutputIterator value_types
// InputIterator is a contiguous iterator
template<class InputIterator, class OutputIterator>
inline OutputIterator
dispatch_copy(InputIterator first,
              InputIterator last,
              OutputIterator result,
              command_queue &queue,
              const wait_list &events,
              typename boost::enable_if<
                  mpl::and_<
                      mpl::not_<
                          is_device_iterator<InputIterator>
                      >,
                      is_device_iterator<OutputIterator>,
                      mpl::not_<
                          is_same_value_type<InputIterator, OutputIterator>
                      >,
                      is_contiguous_iterator<InputIterator>
                  >
              >::type* = 0)
{
    typedef typename OutputIterator::value_type output_type;
    typedef typename std::iterator_traits<InputIterator>::value_type input_type;

    const device &device = queue.get_device();

    // loading parameters
    std::string cache_key =
        std::string("__boost_compute_copy_to_device_")
            + type_name<input_type>() + "_" + type_name<output_type>();
    boost::shared_ptr<parameter_cache> parameters =
        detail::parameter_cache::get_global_cache(device);

    uint_ map_copy_threshold;
    uint_ direct_copy_threshold;

    // calculate default values of thresholds
    if (device.type() & device::gpu) {
        // GPUs
        map_copy_threshold = 524288;  // 0.5 MB
        direct_copy_threshold = 52428800; // 50 MB
    }
    else {
        // CPUs and other devices
        map_copy_threshold = 134217728; // 128 MB
        direct_copy_threshold = 0; // it's never efficient for CPUs
    }

    // load thresholds
    map_copy_threshold =
        parameters->get(
            cache_key, "map_copy_threshold", map_copy_threshold
        );
    direct_copy_threshold =
        parameters->get(
            cache_key, "direct_copy_threshold", direct_copy_threshold
        );

    // select copy method based on thresholds & input_size_bytes
    size_t count = iterator_range_size(first, last);
    size_t input_size_bytes = count * sizeof(input_type);

    // [0; map_copy_threshold) -> copy_to_device_map()
    if(input_size_bytes < map_copy_threshold) {
        return copy_to_device_map(first, last, result, queue, events);
    }
    // [map_copy_threshold; direct_copy_threshold) -> convert [first; last)
    //     on host and then perform copy_to_device()
    else if(input_size_bytes < direct_copy_threshold) {
        std::vector<output_type> vector(first, last);
        return copy_to_device(
            vector.begin(), vector.end(), result, queue, events
        );
    }

    // [direct_copy_threshold; inf) -> map [first; last) to device and
    //     run copy kernel on device for copying & casting
    // At this point we are sure that count > 1 (first != last).

    // Perform async copy to device, wait for it to be finished and
    // return the result.
    // At this point we are sure that count > 1 (first != last), so event
    // returned by dispatch_copy_async() must be valid.
    return dispatch_copy_async(first, last, result, queue, events).get();
}

// host -> device
// InputIterator is NOT a contiguous iterator
template<class InputIterator, class OutputIterator>
inline OutputIterator
dispatch_copy(InputIterator first,
              InputIterator last,
              OutputIterator result,
              command_queue &queue,
              const wait_list &events,
              typename boost::enable_if<
                  mpl::and_<
                      mpl::not_<
                          is_device_iterator<InputIterator>
                      >,
                      is_device_iterator<OutputIterator>,
                      mpl::not_<
                          is_contiguous_iterator<InputIterator>
                      >
                  >
              >::type* = 0)
{
    typedef typename OutputIterator::value_type output_type;
    typedef typename std::iterator_traits<InputIterator>::value_type input_type;

    const device &device = queue.get_device();

    // loading parameters
    std::string cache_key =
        std::string("__boost_compute_copy_to_device_")
            + type_name<input_type>() + "_" + type_name<output_type>();
    boost::shared_ptr<parameter_cache> parameters =
        detail::parameter_cache::get_global_cache(device);

    uint_ map_copy_threshold;
    uint_ direct_copy_threshold;

    // calculate default values of thresholds
    if (device.type() & device::gpu) {
        // GPUs
        map_copy_threshold = 524288;  // 0.5 MB
        direct_copy_threshold = 52428800; // 50 MB
    }
    else {
        // CPUs and other devices
        map_copy_threshold = 134217728; // 128 MB
        direct_copy_threshold = 0; // it's never efficient for CPUs
    }

    // load thresholds
    map_copy_threshold =
        parameters->get(
            cache_key, "map_copy_threshold", map_copy_threshold
        );
    direct_copy_threshold =
        parameters->get(
            cache_key, "direct_copy_threshold", direct_copy_threshold
        );

    // select copy method based on thresholds & input_size_bytes
    size_t input_size = iterator_range_size(first, last);
    size_t input_size_bytes = input_size * sizeof(input_type);

    // [0; map_copy_threshold) -> copy_to_device_map()
    //
    // if direct_copy_threshold is less than map_copy_threshold
    // copy_to_device_map() is used for every input
    if(input_size_bytes < map_copy_threshold
        || direct_copy_threshold <= map_copy_threshold) {
        return copy_to_device_map(first, last, result, queue, events);
    }
    // [map_copy_threshold; inf) -> convert [first; last)
    //     on host and then perform copy_to_device()
    std::vector<output_type> vector(first, last);
    return copy_to_device(vector.begin(), vector.end(), result, queue, events);
}

// device -> host (async)
template<class InputIterator, class OutputIterator>
inline future<OutputIterator>
dispatch_copy_async(InputIterator first,
                    InputIterator last,
                    OutputIterator result,
                    command_queue &queue,
                    const wait_list &events,
                    typename boost::enable_if<
                        mpl::and_<
                            is_device_iterator<InputIterator>,
                            mpl::not_<
                                is_device_iterator<OutputIterator>
                            >,
                            is_same_value_type<OutputIterator, InputIterator>
                        >
                    >::type* = 0)
{
    BOOST_STATIC_ASSERT_MSG(
        is_contiguous_iterator<OutputIterator>::value,
        "copy_async() is only supported for contiguous host iterators"
    );

    return copy_to_host_async(first, last, result, queue, events);
}

// device -> host (async)
// Type mismatch between InputIterator and OutputIterator value_types
template<class InputIterator, class OutputIterator>
inline future<OutputIterator>
dispatch_copy_async(InputIterator first,
                    InputIterator last,
                    OutputIterator result,
                    command_queue &queue,
                    const wait_list &events,
                    typename boost::enable_if<
                        mpl::and_<
                            is_device_iterator<InputIterator>,
                            mpl::not_<
                                is_device_iterator<OutputIterator>
                            >,
                            mpl::not_<
                                is_same_value_type<OutputIterator, InputIterator>
                            >
                        >
                    >::type* = 0)
{
    BOOST_STATIC_ASSERT_MSG(
        is_contiguous_iterator<OutputIterator>::value,
        "copy_async() is only supported for contiguous host iterators"
    );

    typedef typename std::iterator_traits<OutputIterator>::value_type output_type;
    const context &context = queue.get_context();
    size_t count = iterator_range_size(first, last);

    if(count < size_t(1)) {
        return future<OutputIterator>();
    }

    // map host memory to device
    buffer mapped_host(
        context,
        count * sizeof(output_type),
        buffer::write_only | buffer::use_host_ptr,
        static_cast<void*>(
            ::boost::addressof(*result)
        )
    );
    // copy async on device
    ::boost::compute::future<buffer_iterator<output_type> > future =
        copy_on_device_async(
            first,
            last,
            make_buffer_iterator<output_type>(mapped_host),
            queue,
            events
        );
    // update host memory asynchronously by maping and unmaping memory
    event map_event;
    void* ptr = queue.enqueue_map_buffer_async(
        mapped_host,
        CL_MAP_READ,
        0,
        count * sizeof(output_type),
        map_event,
        future.get_event()
    );
    event unmap_event =
        queue.enqueue_unmap_buffer(mapped_host, ptr, map_event);
    return make_future(result + count, unmap_event);
}

// device -> host
// OutputIterator is a contiguous iterator
template<class InputIterator, class OutputIterator>
inline OutputIterator
dispatch_copy(InputIterator first,
              InputIterator last,
              OutputIterator result,
              command_queue &queue,
              const wait_list &events,
              typename boost::enable_if<
                  mpl::and_<
                      is_device_iterator<InputIterator>,
                      mpl::not_<
                          is_device_iterator<OutputIterator>
                      >,
                      is_same_value_type<OutputIterator, InputIterator>,
                      is_contiguous_iterator<OutputIterator>,
                      mpl::not_<
                          is_bool_value_type<OutputIterator>
                      >
                  >
              >::type* = 0)
{
    return copy_to_host(first, last, result, queue, events);
}

// device -> host
// Type mismatch between InputIterator and OutputIterator value_types
// OutputIterator is NOT a contiguous iterator or value_type of OutputIterator
// is a boolean type.
template<class InputIterator, class OutputIterator>
inline OutputIterator
dispatch_copy(InputIterator first,
              InputIterator last,
              OutputIterator result,
              command_queue &queue,
              const wait_list &events,
              typename boost::enable_if<
                  mpl::and_<
                      is_device_iterator<InputIterator>,
                      mpl::not_<
                          is_device_iterator<OutputIterator>
                      >,
                      mpl::or_<
                          mpl::not_<
                              is_contiguous_iterator<OutputIterator>
                          >,
                          is_bool_value_type<OutputIterator>
                      >
                  >
              >::type* = 0)
{
    typedef typename std::iterator_traits<OutputIterator>::value_type output_type;
    typedef typename InputIterator::value_type input_type;

    const device &device = queue.get_device();

    // loading parameters
    std::string cache_key =
        std::string("__boost_compute_copy_to_host_")
            + type_name<input_type>() + "_" + type_name<output_type>();
    boost::shared_ptr<parameter_cache> parameters =
        detail::parameter_cache::get_global_cache(device);

    uint_ map_copy_threshold;
    uint_ direct_copy_threshold;

    // calculate default values of thresholds
    if (device.type() & device::gpu) {
        // GPUs
        map_copy_threshold = 33554432;  // 30 MB
        direct_copy_threshold = 0; // it's never efficient for GPUs
    }
    else {
        // CPUs and other devices
        map_copy_threshold = 134217728; // 128 MB
        direct_copy_threshold = 0; // it's never efficient for CPUs
    }

    // load thresholds
    map_copy_threshold =
        parameters->get(
            cache_key, "map_copy_threshold", map_copy_threshold
        );
    direct_copy_threshold =
        parameters->get(
            cache_key, "direct_copy_threshold", direct_copy_threshold
        );

    // select copy method based on thresholds & input_size_bytes
    size_t count = iterator_range_size(first, last);
    size_t input_size_bytes = count * sizeof(input_type);

    // [0; map_copy_threshold) -> copy_to_host_map()
    //
    // if direct_copy_threshold is less than map_copy_threshold
    // copy_to_host_map() is used for every input
    if(input_size_bytes < map_copy_threshold
        || direct_copy_threshold <= map_copy_threshold) {
        return copy_to_host_map(first, last, result, queue, events);
    }
    // [map_copy_threshold; inf) -> copy [first;last) to temporary vector
    //     then copy (and convert) to result using std::copy()
    std::vector<input_type> vector(count);
    copy_to_host(first, last, vector.begin(), queue, events);
    return std::copy(vector.begin(), vector.end(), result);
}

// device -> host
// Type mismatch between InputIterator and OutputIterator value_types
// OutputIterator is a contiguous iterator
// value_type of OutputIterator is NOT a boolean type
template<class InputIterator, class OutputIterator>
inline OutputIterator
dispatch_copy(InputIterator first,
              InputIterator last,
              OutputIterator result,
              command_queue &queue,
              const wait_list &events,
              typename boost::enable_if<
                  mpl::and_<
                      is_device_iterator<InputIterator>,
                      mpl::not_<
                          is_device_iterator<OutputIterator>
                      >,
                      mpl::not_<
                          is_same_value_type<OutputIterator, InputIterator>
                      >,
                      is_contiguous_iterator<OutputIterator>,
                      mpl::not_<
                          is_bool_value_type<OutputIterator>
                      >
                  >
              >::type* = 0)
{
    typedef typename std::iterator_traits<OutputIterator>::value_type output_type;
    typedef typename InputIterator::value_type input_type;

    const device &device = queue.get_device();

    // loading parameters
    std::string cache_key =
        std::string("__boost_compute_copy_to_host_")
            + type_name<input_type>() + "_" + type_name<output_type>();
    boost::shared_ptr<parameter_cache> parameters =
        detail::parameter_cache::get_global_cache(device);

    uint_ map_copy_threshold;
    uint_ direct_copy_threshold;

    // calculate default values of thresholds
    if (device.type() & device::gpu) {
        // GPUs
        map_copy_threshold = 524288;  // 0.5 MB
        direct_copy_threshold = 52428800; // 50 MB
    }
    else {
        // CPUs and other devices
        map_copy_threshold = 134217728; // 128 MB
        direct_copy_threshold = 0; // it's never efficient for CPUs
    }

    // load thresholds
    map_copy_threshold =
        parameters->get(
            cache_key, "map_copy_threshold", map_copy_threshold
        );
    direct_copy_threshold =
        parameters->get(
            cache_key, "direct_copy_threshold", direct_copy_threshold
        );

    // select copy method based on thresholds & input_size_bytes
    size_t count = iterator_range_size(first, last);
    size_t input_size_bytes = count * sizeof(input_type);

    // [0; map_copy_threshold) -> copy_to_host_map()
    if(input_size_bytes < map_copy_threshold) {
        return copy_to_host_map(first, last, result, queue, events);
    }
    // [map_copy_threshold; direct_copy_threshold) -> copy [first;last) to
    //     temporary vector then copy (and convert) to result using std::copy()
    else if(input_size_bytes < direct_copy_threshold) {
        std::vector<input_type> vector(count);
        copy_to_host(first, last, vector.begin(), queue, events);
        return std::copy(vector.begin(), vector.end(), result);
    }

    // [direct_copy_threshold; inf) -> map [result; result + input_size) to
    //     device and run copy kernel on device for copying & casting
    // map host memory to device.

    // Perform async copy to host, wait for it to be finished and
    // return the result.
    // At this point we are sure that count > 1 (first != last), so event
    // returned by dispatch_copy_async() must be valid.
    return dispatch_copy_async(first, last, result, queue, events).get();
}

// device -> device
template<class InputIterator, class OutputIterator>
inline OutputIterator
dispatch_copy(InputIterator first,
              InputIterator last,
              OutputIterator result,
              command_queue &queue,
              const wait_list &events,
              typename boost::enable_if<
                  mpl::and_<
                      is_device_iterator<InputIterator>,
                      is_device_iterator<OutputIterator>,
                      mpl::not_<
                          can_copy_with_copy_buffer<
                              InputIterator, OutputIterator
                          >
                      >
                  >
              >::type* = 0)
{
    return copy_on_device(first, last, result, queue, events);
}

// device -> device (specialization for buffer iterators)
template<class InputIterator, class OutputIterator>
inline OutputIterator
dispatch_copy(InputIterator first,
              InputIterator last,
              OutputIterator result,
              command_queue &queue,
              const wait_list &events,
              typename boost::enable_if<
                  mpl::and_<
                      is_device_iterator<InputIterator>,
                      is_device_iterator<OutputIterator>,
                      can_copy_with_copy_buffer<
                          InputIterator, OutputIterator
                      >
                  >
              >::type* = 0)
{
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;
    typedef typename std::iterator_traits<InputIterator>::difference_type difference_type;

    difference_type n = std::distance(first, last);
    if(n < 1){
        // nothing to copy
        return result;
    }

    queue.enqueue_copy_buffer(first.get_buffer(),
                              result.get_buffer(),
                              first.get_index() * sizeof(value_type),
                              result.get_index() * sizeof(value_type),
                              static_cast<size_t>(n) * sizeof(value_type),
                              events);
    return result + n;
}

// device -> device (async)
template<class InputIterator, class OutputIterator>
inline future<OutputIterator>
dispatch_copy_async(InputIterator first,
                    InputIterator last,
                    OutputIterator result,
                    command_queue &queue,
                    const wait_list &events,
                    typename boost::enable_if<
                        mpl::and_<
                            is_device_iterator<InputIterator>,
                            is_device_iterator<OutputIterator>,
                            mpl::not_<
                                can_copy_with_copy_buffer<
                                    InputIterator, OutputIterator
                                >
                            >
                        >
                    >::type* = 0)
{
    return copy_on_device_async(first, last, result, queue, events);
}

// device -> device (async, specialization for buffer iterators)
template<class InputIterator, class OutputIterator>
inline future<OutputIterator>
dispatch_copy_async(InputIterator first,
                    InputIterator last,
                    OutputIterator result,
                    command_queue &queue,
                    const wait_list &events,
                    typename boost::enable_if<
                        mpl::and_<
                            is_device_iterator<InputIterator>,
                            is_device_iterator<OutputIterator>,
                            can_copy_with_copy_buffer<
                                InputIterator, OutputIterator
                            >
                        >
                    >::type* = 0)
{
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;
    typedef typename std::iterator_traits<InputIterator>::difference_type difference_type;

    difference_type n = std::distance(first, last);
    if(n < 1){
        // nothing to copy
        return make_future(result, event());
    }

    event event_ =
        queue.enqueue_copy_buffer(
            first.get_buffer(),
            result.get_buffer(),
            first.get_index() * sizeof(value_type),
            result.get_index() * sizeof(value_type),
            static_cast<size_t>(n) * sizeof(value_type),
            events
        );

    return make_future(result + n, event_);
}

// host -> host
template<class InputIterator, class OutputIterator>
inline OutputIterator
dispatch_copy(InputIterator first,
              InputIterator last,
              OutputIterator result,
              command_queue &queue,
              const wait_list &events,
              typename boost::enable_if_c<
                  !is_device_iterator<InputIterator>::value &&
                  !is_device_iterator<OutputIterator>::value
              >::type* = 0)
{
    (void) queue;
    (void) events;

    return std::copy(first, last, result);
}

} // end detail namespace

/// Copies the values in the range [\p first, \p last) to the range
/// beginning at \p result.
///
/// The generic copy() function can be used for a variety of data
/// transfer tasks and provides a standard interface to the following
/// OpenCL functions:
///
/// \li \c clEnqueueReadBuffer()
/// \li \c clEnqueueWriteBuffer()
/// \li \c clEnqueueCopyBuffer()
///
/// Unlike the aforementioned OpenCL functions, copy() will also work
/// with non-contiguous data-structures (e.g. \c std::list<T>) as
/// well as with "fancy" iterators (e.g. transform_iterator).
///
/// \param first first element in the range to copy
/// \param last last element in the range to copy
/// \param result first element in the result range
/// \param queue command queue to perform the operation
///
/// \return \c OutputIterator to the end of the result range
///
/// For example, to copy an array of \c int values on the host to a vector on
/// the device:
/// \code
/// // array on the host
/// int data[] = { 1, 2, 3, 4 };
///
/// // vector on the device
/// boost::compute::vector<int> vec(4, context);
///
/// // copy values to the device vector
/// boost::compute::copy(data, data + 4, vec.begin(), queue);
/// \endcode
///
/// The copy algorithm can also be used with standard containers such as
/// \c std::vector<T>:
/// \code
/// std::vector<int> host_vector = ...
/// boost::compute::vector<int> device_vector = ...
///
/// // copy from the host to the device
/// boost::compute::copy(
///     host_vector.begin(), host_vector.end(), device_vector.begin(), queue
/// );
///
/// // copy from the device to the host
/// boost::compute::copy(
///     device_vector.begin(), device_vector.end(), host_vector.begin(), queue
/// );
/// \endcode
///
/// Space complexity: \Omega(1)
///
/// \see copy_n(), copy_if(), copy_async()
template<class InputIterator, class OutputIterator>
inline OutputIterator copy(InputIterator first,
                           InputIterator last,
                           OutputIterator result,
                           command_queue &queue = system::default_queue(),
                           const wait_list &events = wait_list())
{
    return detail::dispatch_copy(first, last, result, queue, events);
}

/// Copies the values in the range [\p first, \p last) to the range
/// beginning at \p result. The copy is performed asynchronously.
///
/// \see copy()
template<class InputIterator, class OutputIterator>
inline future<OutputIterator>
copy_async(InputIterator first,
           InputIterator last,
           OutputIterator result,
           command_queue &queue = system::default_queue(),
           const wait_list &events = wait_list())
{
    return detail::dispatch_copy_async(first, last, result, queue, events);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_COPY_HPP

/* copy.hpp
NeJ8Y4Vx4vghlWYWX1Pza2khiBnewUr5p4wwDd2FNHQ6Xf0sovcUVCiJu1hipUqLlMTSdLkkF3qBcCzFEUjBzj3maa+t++W0S8xWRG5IRzLvYCcjHB25iOKZtf5fjKjCyHaQLihAMoTkOObRuED3WBXj0b/g0WHl69vg67o3sAQQcq+Gm2oDSPAyj8cn//Q5i16cBO1jZysKHl1Oq1iFMYlk5NP1nLvQS2vRc0cGQTjIqIT1MjyF7T3EXENqqMIay1XIvbnOIT/NktLMJqWk8KlxzT5ltO0dDllOxzT3vAM5wyxUK3c5Dulw1RDSKKVjZHuXg9Ghu7YzLgZJTF6tTfNtQLJ0xElv2R6mW60KVbpqO/JqLTDK9gNKYJ1MPFfkyCzRQV9kdkULGlqJcMC6Q3gLKfjEAXFaFeqQnIA6HJmc+nVNRv1wXWJ/qUeS4kuss+pq3uJ85qDQMbDikq6vBsZj++qAEl3r2idYX6FaEe5nRHZWq5NyT4Q76wh21kz6v4+zbUDp61n0Ui9+nyGSY3BrodZbkUaq9Z+VoKPUXpiZoBfUvpyRIMkBJYk5YUepnZT1H4q+9JQsP8QCpennrqu30TVO72yGjmvA92KA/Sj+/y8yk2AGKD9oJL4OZX1rx4x3PRNzvKqSpT+/b40B7FToTcurk+zf5LOcIJ29lxHTs/S3AVTzj9PrHSz+eACjK57QZIN758WN8qKeoKapdAIBfBnjItAqUzcG+0x6HMNb4SUi4LNN3iqziV++HGTaaiMwCI6qseMYUTN4+VklHl3i+R9/O40+pfXXFhp8V5L1xQ2j3jlkHjlxvv/qTuurbZCEd0fs7RNvstAnWu+/8AYXc8gbiy9HX51Ev0iff5H19RAtQjtDnzmEx0bvwtWkQPkrRWZjkSVlQFN5UpjOIinxIAQtxPiiCWoSWZ+rWhLhwzGXHZ0fRxVK9Ko7Dr3p16oV6XDYDmBWNUc66OrFCq4dqxP8564SL3KaMk8qKaNntxtgeMsg3+0PGdDvOpoRiamy4k9VOVCsehgp/p7T0DAPjzjk2hFyQuup7RR76hytqgNBE6ZPdTLe/XAzizy1oRojtipP5TpgMenDVzLnT7xE6y/18pGrpsBJn0v0ugWXRciEWkHWPUc/hGrI5YUirZ6vcaETz+QSm7bDm8lpkf4oLby1V6HnqpHW/zQYrHsD5SfOt0guz3TI7mynXLIA9YUdf8Q157tWSUznP6l0i+P1YDCnNWzbvX5hw6hvAc3cw2beadr5JgzFCfruRUx+mgzTwGtMVYNxyrBJg/cj2sR9/i3FnLyh2MeTUsaouqvOIYgxii/aNm+BO/+3Od/X1Br8eodSgxOvBYP63tFmiqdq+zgIiq2Po4EG+2bdjr92HECSXx2DUtligOIjdDDKvR6fZMhM576g+hI3H+ZYgIbXf89xLG1Ufpq/n8lNHjaF/f1Sp+rv143+fh+/FoXHEUgu6A77VkV6T2nuUu+9MCG+D3N9Nk2C/2CaHP/BFA//QaEfhZPiPaN9eiXf8N6k1ulmBeBFCkUapu3Pq1b8QJ/TQohL2CExlvr+jiAeIY16vxksAW7NYoC/yYSvYBK04siczAYDA2agafoQfeE3MJCDnAFN06PpZRyD/AnG15JofP/m/n3dqn/foZYJ/PsCybsnmS8v/XLC+QLj+YOWv6G/AR/yNxjfHYIMUDwOvvDeiM1cZVIqLJVYAiXm+vDIKn48ej+EnKm5HBwDLrTlzSTDJC4Hce2tbv6z3t7qks7eSmef9n0H7Vyrt0/D9y4L2sgLvOQwS4stev8Ggsd73mkwsBI2RLk24zXPrpdaJHPoC/8mE1dr9W8yc5tn+DdZuM3GJsOb3wgHYQtHWCs4gTHVHAEDYxJv2JXCgmWo9AWNCQSzUwwYen4Db9F/l7RhIQoSq8E7m+GWOuhPn1PmRQIUdLdNexWNne5fU3hJxUBfpfNH+0vw4JdDO+iK5yLx4I/8IhIP/t5nGB78nKfDePD5T8Xiwd/91N8DDx4okG49wX00/4JLkK1RDZvtul9M7ICr9F9ry1T8o/qlSko/+sAKPLkkDEnLzNIyXlpmk+zjhxDYO9du8RnJRjP9+Q7orYAsGuSlXBjp/SGDm277uVKTDiChM7Zd0ZhSvrh08AupyEwfgG8OoWGQ5yBiedP7QimDkHJeY8rdi0swJU/vxJTTWEpE9abf1FIye4mo5DbKY2V8QyR5m7lxmYUa4BYjZxG3aVtSY9Fl3jn0k5+mcO1FllvpR+zisgXxUbMpbX1e9TKj71gj1pt1vxbArenHKdEB3Fy6+G1Xsvht+zF+Wz2kbUwuUYK3DYVcdXT5fbVr6vl175oov22CWXf+zOgHWrhYSHdWh0N00juOMouZmOB3Snr2vTnqe1vk9+c7w9/H+t8xaxRbILn5BAMGmcUCon0EXTg4a5OFQQvWPsvFRkd74NkJ4lFExbfC9RwT32rbTyaJb/Xjn8SNbzXyMy4U36r82ZTY+Fbh+FHogmua1aqFjipJRzxag8Rb9xtW6eQxqG9OawWsHqZ9zxN462O4pNRgSngm4/aQY/R6YJvJV2S4Ibi5lJmfLwbCmh/QBVIaI0XpaMltdjucdGuHlTOA5FakxIsaS6kZx/hJNfz8bEhmyB7MJEYipuExNzCs+Ye9twJnsdgvjBkaFwclu9nvGucMLkuKi2emHk9sjIia9GAQrVeIMEZc4zouJX57fh1uzy6tPWt3TKU9MJeWZQBTD7PodwG1PQvjtCcD2rMAUlv3c2QuRoKCZvWANJPf5s1iQp0BJo8wxtpkt6TY1TZ5I9pUFa9N2n7LAsRcjgFiJDOQNzEcGSYmns6k6dOj8C+j4sngRqrFYDm9QxeDxbdzgngw0/4cRi4QYxLp11tE/JW7tl5Y+pOMGRuukk3HkZ5ltRlbja0ifevpiSKxvNxtjY3EMnYqpNgJxaeaBjtPRHQqYx8GpwJSFApOdZsW4ecmLTjVNVHBqTA01f8BAAD//7x9D2BT1bn4TZO2FxrIBVIoUrRqVWZxokVHDc5WTClq6k1iExTauve0dpnbQ8jFMmkpptFejnG44eY2dezJFDf2xjaEqqj9g00rHRRkWgQVHb4dlm4GqW2A2vv7vnNv/rRNC/re+7mRJuee853vfOf7e853zs0hOtNOrnJZRVvlMl+HUtHWNfy/MtJrJ/ZckuJv9vIFRQtX6eWihc4N5Vkud3+bztTwDsdxpCiHcLJ10N9samjD32Vm35kUKZPYBVK0MC+FSEZSLvxcH572fmi+74xOmtHfliJNh8fDn2X5D3onk+uq75sukNkPwGcoDZ5BDf8R0+MGHcet4/39pkfOsC4FsgCBB39ued/0o79D0VreEjY99gF8y6sdJEXz9EPfgBo5ugX91qwUU0M3a5VLFvgVDcui+YQj9hwyVR8ka3LlGWTJ/LxWWXfiBXgICJoa/FgrRbZmwdjXjjeoq3FQU7/KeNYuWGfw96+8dtg41l261mAJPzQ7rzYLkGP4L8nVFYSyVKBkX8ZerzERHrHylfmd8rwKealBLuHlEqNcIiwjn5a3mrnE+bOanT93kbBeMrphpCSdvD+tXEicUJKJQC2fS0YLA2xqeAOJYM3Veb8Xn11vJU7EM1x0In6M9AFy3BAbQC0bwEOjJiA3xbtCI773fgQoMOoPJ3zIxireRG6Sa3Oh4vVApmsZmeYO72UG62VKXm3uMDJNVkehkebzsYmTww3jb18v7yIn+4sLebc3h9TlkhkwbzNI6ULLgVUCKUY8W2VTXgspnS/rAKovokgTK/ObKxCWgSOuXHKDE/A1QwUyk7ynf9/yzqp0ZcKJq4BlAWyKdKNfkQz5R0JGhFYqkKy8mfqPSNsB6ovkrEpvygE6htKAvplEeVVRlHV53QDBcIBKJ/3NknFZJQqm2pm+TQyU3gKzQS+dqigkQooFIshlEf8R71Snw03/2WIC8Yv49gCPSfNIqVmuWygXkOJceQFiZx2UdYCRQbJCQyzKwYfzgpwOUbgP6pH9eW/rSheCZJSayUd5rXnv62aS0lx9EIa+P69DbxuEMcg8AgF0SwVsnxPk8D9SOk8uCOUgEB4KAUSFkNcKLS2kLievQ06HnopYU513goNO+AnH+fYYAJyvtFCn8EBZsjqXTF4WsOvk6ZWNOm3Io/QRY0ig1kLgCkvK6utIGe87o3gzbhAVb1p/EdD7EuA+BdWSwp5MwhZ84xTSivDym/ETSMqAAzyY/GDa0f3TBLr/c6DpPpo1oCj9Vh6wdNF//7GKZXuFigvU9yjVoaapwr2/xkGLvt45TtevN/qyhPy3xIC1797nGS2sfP4RuTwMaK4oyJIe8Aj0oyehOAywZCkslw/6+70WYjUClUqy/J1eA2kJ6X3N2WLA1kUHfq4or+GUBIsNCC2Y9jii91bjFE4u5mWXMZSS309sfNA6COyiyNeAKvby2PL7v1CUJmxDbH33ypOw8V0VyPRRvb6hyDhMxW8omtQ2gr5AD1LMi8G07G7o9N8Q7VLBTu/CLy6zg4pPIkmMSKFg2tbgNAHpZHlyOJ0S4AG9Zr2SQK8F49LL1PA4/C7IMvkb4K8ni764cSTdnMnptpu++bSiBGzH7MNptwNp95+PTuFAUlw8KTHIpUYiAhkFUmhEuMXmMei5m86GmWhKGYee6vi2Jo4vy+lyjxqghwvYKF312BTOd+PtKTMFjsxe+kyWAD3iUxi5lIdVeqkYryIJvy6Bv4XP4+fzWIQV3FCB1PLkOiwg6ZYVxlWXkBKeGP/o75Sy62vMnHc6/StUwidTYaBk/p9CafmdoePkpL9fug9UhYGcCpUHrGG3SJcPKYpvD9Nps6rNb0+DLo7Sp9pNXPWCC2bgDzv94dugU6QwosfL1yHW9HdIzWIDtFplKJSLDfCEvgllLvopfAJNYbAaMemLWLc9gX6ViQREebaZnaQ8G/C6zeUmtTirYDdyfQu4DTO8s0DFw7e6aaAgwIDwgQd18rzGKaadraEMooMJNO086FC6AQYOwdBuFXSLb5N2V1Ygj5QJsiCXGJaVtyXyI9R1ESkbGKkYHRno7nq1u9GdgSYSGmeadrbFOntnRGel0pvLErqqKB/hQKn8UZLIH3wy/oDZEOlN9YoiaixB//NLUEa1yPikR6MlGJkClUuu9ANRFxtAvUxgk1AiLzaQhwwDH87qh8cD79JroMKlA96JZDpJ8ejIPsB6GmpYR5ZI9ioHR01HVGiZPRRwPthcbHR6ODf92QETSjz0lpYXJOFQCjkFPgWxCS63CEDtgbKIQ6TXACsRXrYJRDT49mTph/I+lMvM3nnEltPQ6b2MCB6dHaTPDoLmwOHa6X9gCzBfIIjYQraaF98WCoBzYDNCSWWFXGSQp5CWry9v+gYUpmpgWZC35Unl7ZgvVmW4vGERVvi7T5M3LBhL3u5rOE952306ibxd1pYobxODifKGWFOLb7S83eFDeZN8I+XtW75zyBvQ74E/J9Bv7vj2qwbslxf08EUkpod7VT28KLke7qDf+olmvwCCpoadItkHGKYwjcwMS8o/FUXTu/I1GvKa3u2gv/nJOezYcPl6OM4P9iTMQHSBB0VU/FI4eMs12xdA94HSHRovBIt3MON/8B9gPEp30As+A6Z0bSc3G4K3zNu+EB65NOyCadvB2tGtqoobRuEYZmg/Aw9uBy/i35S4FzF7Q3LrqPnnOiIKoJJ4l4YSyGe75v1En5vHfv4V5OFUPTL7vao83JNUHrrjVYbLw72aPLxXr8nDvePIQ9n685SHBxTYU3AgOhQG4Nrc2rZtb82tbdu2bdu2bdu2bfP2PnyTTJ4yyZz8SbqlCOHTpsLubYtp/uEiWKSr8KnjWpeLurXWeBdya/77jc9T8cOcuUuHPxiiChN4AUjLs9RFCWPMnRjsJLCZWh1+m/H1+OWFAmQBUBf4bA+mlPuXE5xKHxNuTq0/7O7dhx/9q1Z0vXQMsRs1arE1o02KyXBqzx4LY8i7MgC8ab7+lTjUqlwz5GmjNA+o6v63tQFgOUahSehQy9oGzFbmZo15oAJ+lqfMLJYjBEnoQEYjOO9ejjeYtRxX+GmPKya5Sm92ibYX/8jn1HjvaW0D+IRdVgAh0TCo+5b+WTSM8uOywngyQ29V+b2YYim2PlKrZjgu3hvy0ZPviySjs266SRNQnNiBTA/XGxR+olNwQd3Fd2s1tmh08M855k1YkNkgubA6lqvALa84220/5iblf1q4AreSgMmLPH3gs2bIhEdiVHWzQLOL31zQu7LHJS/5uaqDK9gFW7tLZeR5NT6q0Bee8VPbf3SufjqWgwyuYUyhos+uuc+tYj3SFA6eXjC//lbJ7dEBBoLwuyQIhYJQxVnyGmdelFgXWTKgIbwYRhcOYe2/dzOzfc8V0wQajQH6hzBOtM1QTf0JwqMHMavoSx1o+jCnaMst4hQrEiMH4OWofEuLxInmsSOu08V0EJO9iAY5FqlKrDRv69CG/alAyGmm+sY077pkcWn/BTlL/AqWkj0MW0ywvP6i+WM97YBFhFqWNb9kn/XK+XiTcGzRGscTF1Z1tgGptFgDqxEsqxDWQiI6msmH4olmE1Rtkj5u3gCnM6Us/KHPYAqZGa/r4XoaJYELm+uD0yhVTNYuva195K3Hc5lHpl74VTi7Gu1ma6JmWvnlv+peJUFK775NZd59nAoDjr4pqoNp2bNCcUiqTwhX7zgwHTrpIpYb3A+XqvffrIYXV3k2veAgQwpia8oz3OC8ZsFk9m/K+kHl+tu+0BPH3QAP7PDn0qTNVZVfdLnKpnAUG4kvcUS1YmT6apiL/iezAUg+cJ9gbTZIGYP3xWwgwy0adyZ+i6CqyWyIF3lAYYT9IUBGGr1q5xe+fqKspwIvNJonWRuzmmzg+xYbTMVs6TQ0FfU8mtqDBQZE76AANT6qI0tnqFazdJpkOIRNmJXrQoWXrrPtUWcR9TiHXuiQFBbELcenG4/L0u4XyjvwDm1NCssYvidM1DgVCwRQLVbwfZmWJq3blmAF9mpMCDNoFMwsvn4n1oNFADcog81ZiUYBCeDb6bsIfQMe63v5Ns9DPNy2V4IyOldMm+cc5XQQpyIXWn3ne1L15RE2AeO99YPtWav14mkYmSJ91wASvFYu/2R1NiFB4OUGYDEztmut7Na3HI3lHnilYXtEKydYA4Cz0Rx9Z3BUy6Gp5f+24GCPlwijfT2j2YHYfefqfA73BVp0wWb3b4dWESwTKBR38zz4rUxM4moVOBHVWUUSqsJLc8oKI4JIazaPEWxMvkr7roVY44VY6wxidn5X2sx02vTST7gMigVuyqQ0j4DVhsEC1IJPhjkx/SG0zdB3MdCJEdJp8grzspKcTzlSdAxtFjk2nbmhYzRQwSTq7HeRRipcVIG5FcXpmMYN+ibS3EFAmKGGnUFHtMwApMFuYgqeGFM42JOHb/0E3Lsbta8pqBYshILdZdvOItrJkhxvHkA2An5o1ZoF9gKhZJq7vWrDeXUpQjQULHx/mmQKP4+9P4g66t3SukVuhPtq1H7K8Cd6bKTJ/EHjdEMLnRWLkVtqwUJ6shpjf0dNpCndvMdeayfStQK7ahelvSjuUCYt
*/