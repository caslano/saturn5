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