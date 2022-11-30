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
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
*/