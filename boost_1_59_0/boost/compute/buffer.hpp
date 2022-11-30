//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_BUFFER_HPP
#define BOOST_COMPUTE_BUFFER_HPP

#include <boost/compute/config.hpp>
#include <boost/compute/context.hpp>
#include <boost/compute/exception.hpp>
#include <boost/compute/memory_object.hpp>
#include <boost/compute/detail/get_object_info.hpp>

namespace boost {
namespace compute {

// forward declarations
class command_queue;

/// \class buffer
/// \brief A memory buffer on a compute device.
///
/// The buffer class represents a memory buffer on a compute device.
///
/// Buffers are allocated within a compute context. For example, to allocate
/// a memory buffer for 32 float's:
///
/// \snippet test/test_buffer.cpp constructor
///
/// Once created, data can be copied to and from the buffer using the
/// \c enqueue_*_buffer() methods in the command_queue class. For example, to
/// copy a set of \c int values from the host to the device:
/// \code
/// int data[] = { 1, 2, 3, 4 };
///
/// queue.enqueue_write_buffer(buf, 0, 4 * sizeof(int), data);
/// \endcode
///
/// Also see the copy() algorithm for a higher-level interface to copying data
/// between the host and the device. For a higher-level, dynamically-resizable,
/// type-safe container for data on a compute device, use the vector<T> class.
///
/// Buffer objects have reference semantics. Creating a copy of a buffer
/// object simply creates another reference to the underlying OpenCL memory
/// object. To create an actual copy use the buffer::clone() method.
///
/// \see context, command_queue
class buffer : public memory_object
{
public:
    /// Creates a null buffer object.
    buffer()
        : memory_object()
    {
    }

    /// Creates a buffer object for \p mem. If \p retain is \c true, the
    /// reference count for \p mem will be incremented.
    explicit buffer(cl_mem mem, bool retain = true)
        : memory_object(mem, retain)
    {
    }

    /// Create a new memory buffer in of \p size with \p flags in
    /// \p context.
    ///
    /// \see_opencl_ref{clCreateBuffer}
    buffer(const context &context,
           size_t size,
           cl_mem_flags flags = read_write,
           void *host_ptr = 0)
    {
        cl_int error = 0;
        m_mem = clCreateBuffer(context,
                               flags,
                               (std::max)(size, size_t(1)),
                               host_ptr,
                               &error);
        if(!m_mem){
            BOOST_THROW_EXCEPTION(opencl_error(error));
        }
    }

    /// Creates a new buffer object as a copy of \p other.
    buffer(const buffer &other)
        : memory_object(other)
    {
    }

    /// Copies the buffer object from \p other to \c *this.
    buffer& operator=(const buffer &other)
    {
        if(this != &other){
            memory_object::operator=(other);
        }

        return *this;
    }

    #ifndef BOOST_COMPUTE_NO_RVALUE_REFERENCES
    /// Move-constructs a new buffer object from \p other.
    buffer(buffer&& other) BOOST_NOEXCEPT
        : memory_object(std::move(other))
    {
    }

    /// Move-assigns the buffer from \p other to \c *this.
    buffer& operator=(buffer&& other) BOOST_NOEXCEPT
    {
        memory_object::operator=(std::move(other));

        return *this;
    }
    #endif // BOOST_COMPUTE_NO_RVALUE_REFERENCES

    /// Destroys the buffer object.
    ~buffer()
    {
    }

    /// Returns the size of the buffer in bytes.
    size_t size() const
    {
        return get_memory_size();
    }

    /// \internal_
    size_t max_size() const
    {
        return get_context().get_device().max_memory_alloc_size();
    }

    /// Returns information about the buffer.
    ///
    /// \see_opencl_ref{clGetMemObjectInfo}
    template<class T>
    T get_info(cl_mem_info info) const
    {
        return get_memory_info<T>(info);
    }

    /// \overload
    template<int Enum>
    typename detail::get_object_info_type<buffer, Enum>::type
    get_info() const;

    /// Creates a new buffer with a copy of the data in \c *this. Uses
    /// \p queue to perform the copy.
    buffer clone(command_queue &queue) const;

    #if defined(BOOST_COMPUTE_CL_VERSION_1_1) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Creates a new buffer out of this buffer.
    /// The new buffer is a sub region of this buffer.
    /// \p flags The mem_flags which should be used to create the new buffer
    /// \p origin The start index in this buffer
    /// \p size The size of the new sub buffer
    ///
    /// \see_opencl_ref{clCreateSubBuffer}
    ///
    /// \opencl_version_warning{1,1}
    buffer create_subbuffer(cl_mem_flags flags, size_t origin,
                            size_t size)
    {
        BOOST_ASSERT(origin + size <= this->size());
        BOOST_ASSERT(origin % (get_context().
                               get_device().
                               get_info<CL_DEVICE_MEM_BASE_ADDR_ALIGN>() / 8) == 0);
        cl_int error = 0;

        cl_buffer_region region = { origin, size };

        cl_mem mem = clCreateSubBuffer(m_mem,
                                       flags,
                                       CL_BUFFER_CREATE_TYPE_REGION,
                                       &region,
                                       &error);

        if(!mem){
            BOOST_THROW_EXCEPTION(opencl_error(error));
        }

        return buffer(mem, false);
    }
  #endif // BOOST_COMPUTE_CL_VERSION_1_1
};

/// \internal_ define get_info() specializations for buffer
BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS(buffer,
    ((cl_mem_object_type, CL_MEM_TYPE))
    ((cl_mem_flags, CL_MEM_FLAGS))
    ((size_t, CL_MEM_SIZE))
    ((void *, CL_MEM_HOST_PTR))
    ((cl_uint, CL_MEM_MAP_COUNT))
    ((cl_uint, CL_MEM_REFERENCE_COUNT))
    ((cl_context, CL_MEM_CONTEXT))
)

#ifdef BOOST_COMPUTE_CL_VERSION_1_1
BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS(buffer,
    ((cl_mem, CL_MEM_ASSOCIATED_MEMOBJECT))
    ((size_t, CL_MEM_OFFSET))
)
#endif // BOOST_COMPUTE_CL_VERSION_1_1

namespace detail {

// set_kernel_arg specialization for buffer
template<>
struct set_kernel_arg<buffer>
{
    void operator()(kernel &kernel_, size_t index, const buffer &buffer_)
    {
        kernel_.set_arg(index, buffer_.get());
    }
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_BUFFER_HPP

/* buffer.hpp
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
*/