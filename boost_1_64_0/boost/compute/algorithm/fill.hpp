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
oL8s+DfYDP4F9oWfwPl6vVyvr4LH4UXQtilf6IPboR/+BibCF2ASPAxToEUfkApbwxTYGQZgD1gXFsBGcD7MgGvVfgXMgtfBZvB+2Bw+AlvA12Er+B7MgX4aVBuYDtvCnmo/A+bCobADnAd7wOWwC7xM7T+EefB22Avuhv3hX+FA+Dk8E/pT6A9gEhwCc2A+zIPD4AS1z4AjYRkcC5fCcfA7cCK8Gk6CP4WT4UNwCvw5XBesr/BC+DL8NnxF5f8Ap8N34Ex4BJ4NP4azYP1U2gvMhLNhc3ge/nvBQtgXztN+aVt4rKLjthJMhqwDDn2aItcVtoLDYFs4A7aHK2BHuBF20vW8nbW/6KLrebvCm2E3uAN2h/fAHnAP7An3wd6wGvbV9dn9dX32ADjPVzO9OHpw0YGH9d+zMA5994l13ei4a67f/ngIBiZ0j9dfb4Y7MKqz9tBXx+uqnbppTL7opFUPHa+D3o5RnbND37wQblf9cqCnQ6ccq082umR0yKo/Nrpj1RkbfTF6Yqd+OF43bPTCRifcEGN0wKeg/3XT91Zimotu16nXPYaJ0eMaHe4c1d1WBu1XonvF3I3Zgzl45Wm96OnP6c/pz9f3+bfp/8tKF3xd+v/ETMYzqjOtsM3vIEKBureO9buIzvSs6dPGTR5TWEQCzQE2dXRuk7MyzFxjlvhpZ+Z3CMNxds0ZYrfN2ZvJpOO1Gpx9UE/3lcjX8zKide8VPv39o+kfhGnFlwKX9DN3Juke5jzjQ2WzjB5hkdjzomQXmDyWyrWOYp9g/DaJm7PFm7VUrjUze8VsEXtajfM7LOp8kAHGvsCR/zJde7BA83825k0mx6pc8r+sfK2Zk2befWVFlD75aZEfYQUI2+ztpXmrZ8phpXNvLy23sO7mSbFPsJgDj+xBX4P7m+m4v5ouR54lXke+P9Z8J0a1w4KgDn1fXL7lIOJIfV2j+VPZGuj59bwWTd8aRzryNAF36P4tt+rEXL5LOlaVW65lSVpUPtMK62emif1a7gdafsxmTFNa5jHyfYjMfkUYgaRWgYFpgWTeyZM9ocpwP4j5TbpcS0vjtIGGbAiVk8iW98l5pt39Vc8+jegndI9irQvflrg5gwKN4Azddzl6r6KV+HmtFudket3DrklmDwfqLtS+J+fF2LKTXse1zxkosuO1HMN+m5g+52Kxs3cNIffhXh3DpNLv+HMpmKwESqgFXxr5NG/mHIbIHHTxkgXFC8188mgJr3WN9sFy6bdMv8tv27j6e1ZwzVB83hcXV+SFKrGl/ZezHuOndvV4mNbj6HNqxyaHBLVZcY2yyqSNx6dHFRyuaVF5/ymlJVw2gZT4tEwL6he80lIoihW3Nq5+/FH3Ey/ROoVaplf7gMheT7E6Es3DLs3DbN0XbwbmAq7sjcuD7HQp9TMdP1sxwfabVpeq2cg03g4nabuq82bOU8IfwO/2ZFNHB1iun/EZzjRzzooln8/0nNk/Ycq4kv9SXJopcE2DS1+GvOOc2flif5knoS1+kkQXJFVanyVhPy3NeTlzxf6irBo09y5mn/9zReY+TrlhPa2eR1yiYUWfGdviZey6x1WOtLsio3OqEtmJakf3LfYu0tfuDs7f1AnvsTeY82W7nvB82Y3it6k5P32r2C8lfeOYF03xPGf2IpFr4dgPrm4m97kWfWy+9rHRZ15RzrhJOavO0Lu+VutP40l678/EzMwOTkq53fs8r3uv8q3NWOrHYu8i8n7Zu0ySY/rvm7huzms1/lu6ttdseKNc76r3OizfTMcbtTtLK7bMBkDSiJukUcvWu8zWBEzfLR+/9pkH4susYm15sVt/qbIJNe5/3Pru6XVDgnN0DDI=
*/