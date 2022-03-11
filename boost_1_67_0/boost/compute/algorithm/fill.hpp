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