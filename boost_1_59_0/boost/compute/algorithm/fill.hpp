//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_FILL_HPP
#define BOOST_COMPUTE_ALGORITHM_FILL_HPP

#include <iterator>

#include <boost/static_assert.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/utility/enable_if.hpp>

#include <boost/compute/cl.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/async/future.hpp>
#include <boost/compute/iterator/constant_iterator.hpp>
#include <boost/compute/iterator/discard_iterator.hpp>
#include <boost/compute/detail/is_buffer_iterator.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>


namespace boost {
namespace compute {
namespace detail {

namespace mpl = boost::mpl;

// fills the range [first, first + count) with value using copy()
template<class BufferIterator, class T>
inline void fill_with_copy(BufferIterator first,
                           size_t count,
                           const T &value,
                           command_queue &queue)
{
    ::boost::compute::copy(
        ::boost::compute::make_constant_iterator(value, 0),
        ::boost::compute::make_constant_iterator(value, count),
        first,
        queue
    );
}

// fills the range [first, first + count) with value using copy_async()
template<class BufferIterator, class T>
inline future<void> fill_async_with_copy(BufferIterator first,
                                         size_t count,
                                         const T &value,
                                         command_queue &queue)
{
    return ::boost::compute::copy_async(
               ::boost::compute::make_constant_iterator(value, 0),
               ::boost::compute::make_constant_iterator(value, count),
               first,
               queue
           );
}

#if defined(BOOST_COMPUTE_CL_VERSION_1_2)

// meta-function returing true if Iterator points to a range of values
// that can be filled using clEnqueueFillBuffer(). to meet this criteria
// it must have a buffer accessible through iter.get_buffer() and the
// size of its value_type must by in {1, 2, 4, 8, 16, 32, 64, 128}.
template<class Iterator>
struct is_valid_fill_buffer_iterator :
    public mpl::and_<
        is_buffer_iterator<Iterator>,
        mpl::contains<
            mpl::vector<
                mpl::int_<1>,
                mpl::int_<2>,
                mpl::int_<4>,
                mpl::int_<8>,
                mpl::int_<16>,
                mpl::int_<32>,
                mpl::int_<64>,
                mpl::int_<128>
            >,
            mpl::int_<
                sizeof(typename std::iterator_traits<Iterator>::value_type)
            >
        >
    >::type { };

template<>
struct is_valid_fill_buffer_iterator<discard_iterator> : public boost::false_type {};

// specialization which uses clEnqueueFillBuffer for buffer iterators
template<class BufferIterator, class T>
inline void
dispatch_fill(BufferIterator first,
              size_t count,
              const T &value,
              command_queue &queue,
              typename boost::enable_if<
                 is_valid_fill_buffer_iterator<BufferIterator>
              >::type* = 0)
{
    typedef typename std::iterator_traits<BufferIterator>::value_type value_type;

    if(count == 0){
        // nothing to do
        return;
    }

    // check if the device supports OpenCL 1.2 (required for enqueue_fill_buffer)
    if(!queue.check_device_version(1, 2)){
        return fill_with_copy(first, count, value, queue);
    }

    value_type pattern = static_cast<value_type>(value);
    size_t offset = static_cast<size_t>(first.get_index());

    if(count == 1){
        // use clEnqueueWriteBuffer() directly when writing a single value
        // to the device buffer. this is potentially more efficient and also
        // works around a bug in the intel opencl driver.
        queue.enqueue_write_buffer(
            first.get_buffer(),
            offset * sizeof(value_type),
            sizeof(value_type),
            &pattern
        );
    }
    else {
        queue.enqueue_fill_buffer(
            first.get_buffer(),
            &pattern,
            sizeof(value_type),
            offset * sizeof(value_type),
            count * sizeof(value_type)
        );
    }
}

template<class BufferIterator, class T>
inline future<void>
dispatch_fill_async(BufferIterator first,
                    size_t count,
                    const T &value,
                    command_queue &queue,
                    typename boost::enable_if<
                       is_valid_fill_buffer_iterator<BufferIterator>
                    >::type* = 0)
{
    typedef typename std::iterator_traits<BufferIterator>::value_type value_type;

    // check if the device supports OpenCL 1.2 (required for enqueue_fill_buffer)
    if(!queue.check_device_version(1, 2)){
        return fill_async_with_copy(first, count, value, queue);
    }

    value_type pattern = static_cast<value_type>(value);
    size_t offset = static_cast<size_t>(first.get_index());

    event event_ =
        queue.enqueue_fill_buffer(first.get_buffer(),
                                  &pattern,
                                  sizeof(value_type),
                                  offset * sizeof(value_type),
                                  count * sizeof(value_type));

    return future<void>(event_);
}

#ifdef BOOST_COMPUTE_CL_VERSION_2_0
// specializations for svm_ptr<T>
template<class T>
inline void dispatch_fill(svm_ptr<T> first,
                          size_t count,
                          const T &value,
                          command_queue &queue)
{
    if(count == 0){
        return;
    }

    queue.enqueue_svm_fill(
        first.get(), &value, sizeof(T), count * sizeof(T)
    );
}

template<class T>
inline future<void> dispatch_fill_async(svm_ptr<T> first,
                                        size_t count,
                                        const T &value,
                                        command_queue &queue)
{
    if(count == 0){
        return future<void>();
    }

    event event_ = queue.enqueue_svm_fill(
        first.get(), &value, sizeof(T), count * sizeof(T)
    );

    return future<void>(event_);
}
#endif // BOOST_COMPUTE_CL_VERSION_2_0

// default implementations
template<class BufferIterator, class T>
inline void
dispatch_fill(BufferIterator first,
              size_t count,
              const T &value,
              command_queue &queue,
              typename boost::disable_if<
                  is_valid_fill_buffer_iterator<BufferIterator>
              >::type* = 0)
{
    fill_with_copy(first, count, value, queue);
}

template<class BufferIterator, class T>
inline future<void>
dispatch_fill_async(BufferIterator first,
                    size_t count,
                    const T &value,
                    command_queue &queue,
                    typename boost::disable_if<
                        is_valid_fill_buffer_iterator<BufferIterator>
                    >::type* = 0)
{
    return fill_async_with_copy(first, count, value, queue);
}
#else
template<class BufferIterator, class T>
inline void dispatch_fill(BufferIterator first,
                          size_t count,
                          const T &value,
                          command_queue &queue)
{
    fill_with_copy(first, count, value, queue);
}

template<class BufferIterator, class T>
inline future<void> dispatch_fill_async(BufferIterator first,
                                        size_t count,
                                        const T &value,
                                        command_queue &queue)
{
    return fill_async_with_copy(first, count, value, queue);
}
#endif // !defined(BOOST_COMPUTE_CL_VERSION_1_2)

} // end detail namespace

/// Fills the range [\p first, \p last) with \p value.
///
/// \param first first element in the range to fill
/// \param last last element in the range to fill
/// \param value value to copy to each element
/// \param queue command queue to perform the operation
///
/// For example, to fill a vector on the device with sevens:
/// \code
/// // vector on the device
/// boost::compute::vector<int> vec(10, context);
///
/// // fill vector with sevens
/// boost::compute::fill(vec.begin(), vec.end(), 7, queue);
/// \endcode
///
/// Space complexity: \Omega(1)
///
/// \see boost::compute::fill_n()
template<class BufferIterator, class T>
inline void fill(BufferIterator first,
                 BufferIterator last,
                 const T &value,
                 command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<BufferIterator>::value);
    size_t count = detail::iterator_range_size(first, last);
    if(count == 0){
        return;
    }

    detail::dispatch_fill(first, count, value, queue);
}

template<class BufferIterator, class T>
inline future<void> fill_async(BufferIterator first,
                               BufferIterator last,
                               const T &value,
                               command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(detail::is_buffer_iterator<BufferIterator>::value);
    size_t count = detail::iterator_range_size(first, last);
    if(count == 0){
        return future<void>();
    }

    return detail::dispatch_fill_async(first, count, value, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_FILL_HPP

/* fill.hpp
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
*/