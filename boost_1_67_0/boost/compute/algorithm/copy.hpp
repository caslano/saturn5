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
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
*/