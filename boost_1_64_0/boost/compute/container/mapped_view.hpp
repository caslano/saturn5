//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_CONTAINER_MAPPED_VIEW_HPP
#define BOOST_COMPUTE_CONTAINER_MAPPED_VIEW_HPP

#include <cstddef>
#include <exception>

#include <boost/config.hpp>
#include <boost/throw_exception.hpp>

#include <boost/compute/buffer.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/context.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>

namespace boost {
namespace compute {

/// \class mapped_view
/// \brief A mapped view of host memory.
///
/// The mapped_view class simplifies mapping host-memory to a compute
/// device. This allows for host-allocated memory to be used with the
/// Boost.Compute algorithms.
///
/// The following example shows how to map a simple C-array containing
/// data on the host to the device and run the reduce() algorithm to
/// calculate the sum:
///
/// \snippet test/test_mapped_view.cpp reduce
///
/// \see buffer
template<class T>
class mapped_view
{
public:
    typedef T value_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef buffer_iterator<T> iterator;
    typedef buffer_iterator<T> const_iterator;

    /// Creates a null mapped_view object.
    mapped_view()
    {
        m_mapped_ptr = 0;
    }

    /// Creates a mapped_view for \p host_ptr with \p n elements. After
    /// constructing a mapped_view the data is available for use by a
    /// compute device. Use the \p unmap() method to make the updated data
    /// available to the host.
    mapped_view(T *host_ptr,
                size_type n,
                const context &context = system::default_context())
        : m_buffer(_make_mapped_buffer(host_ptr, n, context))
    {
        m_mapped_ptr = 0;
    }

    /// Creates a read-only mapped_view for \p host_ptr with \p n elements.
    /// After constructing a mapped_view the data is available for use by a
    /// compute device. Use the \p unmap() method to make the updated data
    /// available to the host.
    mapped_view(const T *host_ptr,
                size_type n,
                const context &context = system::default_context())
        : m_buffer(_make_mapped_buffer(host_ptr, n, context))
    {
        m_mapped_ptr = 0;
    }

    /// Creates a copy of \p other.
    mapped_view(const mapped_view<T> &other)
        : m_buffer(other.m_buffer)
    {
        m_mapped_ptr = 0;
    }

    /// Copies the mapped buffer from \p other.
    mapped_view<T>& operator=(const mapped_view<T> &other)
    {
        if(this != &other){
            m_buffer = other.m_buffer;
            m_mapped_ptr = 0;
        }

        return *this;
    }

    /// Destroys the mapped_view object.
    ~mapped_view()
    {
    }

    /// Returns an iterator to the first element in the mapped_view.
    iterator begin()
    {
        return ::boost::compute::make_buffer_iterator<T>(m_buffer, 0);
    }

    /// Returns a const_iterator to the first element in the mapped_view.
    const_iterator begin() const
    {
        return ::boost::compute::make_buffer_iterator<T>(m_buffer, 0);
    }

    /// Returns a const_iterator to the first element in the mapped_view.
    const_iterator cbegin() const
    {
        return begin();
    }

    /// Returns an iterator to one past the last element in the mapped_view.
    iterator end()
    {
        return ::boost::compute::make_buffer_iterator<T>(m_buffer, size());
    }

    /// Returns a const_iterator to one past the last element in the mapped_view.
    const_iterator end() const
    {
        return ::boost::compute::make_buffer_iterator<T>(m_buffer, size());
    }

    /// Returns a const_iterator to one past the last element in the mapped_view.
    const_iterator cend() const
    {
        return end();
    }

    /// Returns the number of elements in the mapped_view.
    size_type size() const
    {
        return m_buffer.size() / sizeof(T);
    }

    /// Returns the host data pointer.
    T* get_host_ptr()
    {
        return static_cast<T *>(m_buffer.get_info<void *>(CL_MEM_HOST_PTR));
    }

    /// Returns the host data pointer.
    const T* get_host_ptr() const
    {
        return static_cast<T *>(m_buffer.get_info<void *>(CL_MEM_HOST_PTR));
    }

    /// Resizes the mapped_view to \p size elements.
    void resize(size_type size)
    {
        T *old_ptr = get_host_ptr();

        m_buffer = _make_mapped_buffer(old_ptr, size, m_buffer.get_context());
    }

    /// Returns \c true if the mapped_view is empty.
    bool empty() const
    {
        return size() == 0;
    }

    /// Returns the mapped buffer.
    const buffer& get_buffer() const
    {
        return m_buffer;
    }

    /// Maps the buffer into the host address space.
    ///
    /// \see_opencl_ref{clEnqueueMapBuffer}
    void map(cl_map_flags flags, command_queue &queue)
    {
        BOOST_ASSERT(m_mapped_ptr == 0);

        m_mapped_ptr = queue.enqueue_map_buffer(
            m_buffer, flags, 0, m_buffer.size()
        );
    }

    /// Maps the buffer into the host address space for reading and writing.
    ///
    /// Equivalent to:
    /// \code
    /// map(CL_MAP_READ | CL_MAP_WRITE, queue);
    /// \endcode
    void map(command_queue &queue)
    {
        map(CL_MAP_READ | CL_MAP_WRITE, queue);
    }

    /// Unmaps the buffer from the host address space.
    ///
    /// \see_opencl_ref{clEnqueueUnmapMemObject}
    void unmap(command_queue &queue)
    {
        BOOST_ASSERT(m_mapped_ptr != 0);

        queue.enqueue_unmap_buffer(m_buffer, m_mapped_ptr);

        m_mapped_ptr = 0;
    }

private:
    /// \internal_
    static buffer _make_mapped_buffer(T *host_ptr,
                                      size_t n,
                                      const context &context)
    {
        return buffer(
            context,
            n * sizeof(T),
            buffer::read_write | buffer::use_host_ptr,
            host_ptr
        );
    }

    /// \internal_
    static buffer _make_mapped_buffer(const T *host_ptr,
                                      size_t n,
                                      const context &context)
    {
        return buffer(
            context,
            n * sizeof(T),
            buffer::read_only | buffer::use_host_ptr,
            const_cast<void *>(static_cast<const void *>(host_ptr))
        );
    }

private:
    buffer m_buffer;
    void *m_mapped_ptr;
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_CONTAINER_MAPPED_VIEW_HPP

/* mapped_view.hpp
Eq6XOox5DD1iIfrACPUm6v11+ejWmeQVvvQl0necGoW9voq69/vUvZ6ib4V8OCKVevw4dZVcK/Rf6hvEEUkn8MeWNuif9M8HMv/xs1E34Nf/Zh+uD/7XmjiziziV/LS5DR0vnLzBhfjvIc5/D/oafmRtJXX2rwxdgvW9C13Hln2bjG9UAP7K6Gsz9nfdTv0HPbCSPjszeajNTD43GD9DnNSWg55N/TOgm/jKlfiF+5l1P+fLfjmD4SL0W3TN7mHW39vo/ZPpN2q3Qac285xz6knt7Ncsw4+1cD3UnVzrLOjvRO/t5L7H0u/DdacS56Ya74PdiW7Mc3gdd3P/iO/6jD7Oj5n/xN2J/djbQO6rO/HznfRZUK+wZz1XbjMxLjwHei3P5d5Kvdia82deje2hrlmPnpIymfPBHluiI/EeZrMHemop/rGP8XYhTkX/X0/eGUCfjs8pdJWnsT8+vP/8KnQyvj98Er3sd3RJF+7/48QR5cRZxPWBtcQTB9CxRqkDoEvHvs58vhZ7PGA9cX6R+Avis54Z2EHq9UnU3cw836AFfcfsiV9axXudyCNisav1z6PbvEE+wTrNW4juzjz3RE/29EfHdKb+MRvdxI16nzE/LjOef4c9Jt7wKWOdfkzcid/YzfyzryAPs2A9bSbOm0u+0kO8x7wo7mE9TsL+NpMnWeJPLkWP+hd27TX0J/of3V3RD9LJN7FbGz+yID6jnl6KP3fH7vI8aJtgzr+bOPMN4jXq833DzGPynv01jGcG71HfhZ39Aj91L3r43cRb6F0Fmfwe877uRfwreVZbN/0gfeQNPxGPbUU347nkO6P5fZ43OEAd56DRN+SMv9pNXTUTHTKIvPUA/YBPcn3TuM/vYD8eoX8zhP7oaeRf16LbfGPsl8VvxTH/7me+rSRfPEEevpA472nWLfPq0PNcVwzxH/u2IxyJAyfRn4mu7XwMO4OedOhu7Cd6rNdV3J+LqQP9bksehF2pQv+5Fnvvhs7Leqljn+NB4o1DxBWzbKj/TWE/JHbcv5Z+uALGk/exB5LfVS6iru+BnXuEcTaezxrCum/ATmQTb68lzw7CLlVg79GZspzIq/5inVRj7y2IY6fz/hE+3/yjCXtBPGHN9XmxTm+irnsPfeFG/jTA/ZmB3ZhK3v84uvlJ7NnX1JGJkyo9qIe9ib0/jH5KXN9HX5T7W+joU/j8a9A5R/E3ucTZl3M8/G4W+1j8I8hH53L94ayzt9H/6HuNf4j9rMV8vYh19wP6xTzixgbsDeNhwu401hHX7CWe4T4Nc16xk6mLzrNDN0Bfwa7bPE3eu5m8iuty70PfeYw8Zw526E0zdQPypxP4tYdZ18Tfnr8R99FnvdeN+GgAPzyT9byL+urr9PHcQPx4M30t/yU+RL/Ju4V4YRb11pe4fhP3/3b0qkewp7Op620l7kMv3b2BeU38UzCbeUn+7kEeZk/fSvccrqsDf2nYj2XktyPEA2Z+/yDr8Bw6/7Ep2APmkwv6wA/4T2fW72L2i5G3p5L/FtiQB6OzNn7P57zIn+RDpr85b/rT3BmXAfJmf/xiN/0hdfjFvY5cXxr65kp0x5/RlV9kvrtZE79aorvhzw6h15+YjP014X+4jgfQs+gvGuY93M4B3Lf9xFnEAQOTyN/t7fBX6IynmN/e6LXk9VFB5HP70fHxo45Lse/M1wHWr/ffxEX4RfMged67XOdM3qcSTdy0k/5UW8aF8TqIf84oI/8KQceyJB/lPRJbLubnixl3+lGHyb/H/Kh7v0PdhOfP+JDfenJenpfTt7eH+4X+m4pe5nPUhnoeev7nzI/PiYvQXTzPYsfHGSf0lSjWcyJxZMHL3K8=
*/