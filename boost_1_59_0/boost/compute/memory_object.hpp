//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_MEMORY_OBJECT_HPP
#define BOOST_COMPUTE_MEMORY_OBJECT_HPP

#include <boost/compute/config.hpp>
#include <boost/compute/context.hpp>
#include <boost/compute/kernel.hpp>
#include <boost/compute/detail/get_object_info.hpp>
#include <boost/compute/detail/assert_cl_success.hpp>

namespace boost {
namespace compute {

/// \class memory_object
/// \brief Base-class for memory objects.
///
/// The memory_object class is the base-class for memory objects on
/// compute devices.
///
/// \see buffer, vector
class memory_object
{
public:
    /// Flags for the creation of memory objects.
    enum mem_flags {
        read_write = CL_MEM_READ_WRITE,
        read_only = CL_MEM_READ_ONLY,
        write_only = CL_MEM_WRITE_ONLY,
        use_host_ptr = CL_MEM_USE_HOST_PTR,
        alloc_host_ptr = CL_MEM_ALLOC_HOST_PTR,
        copy_host_ptr = CL_MEM_COPY_HOST_PTR
        #ifdef BOOST_COMPUTE_CL_VERSION_1_2
        ,
        host_write_only = CL_MEM_HOST_WRITE_ONLY,
        host_read_only = CL_MEM_HOST_READ_ONLY,
        host_no_access = CL_MEM_HOST_NO_ACCESS
        #endif
    };

    /// Symbolic names for the OpenCL address spaces.
    enum address_space {
        global_memory,
        local_memory,
        private_memory,
        constant_memory
    };

    /// Returns the underlying OpenCL memory object.
    cl_mem& get() const
    {
        return const_cast<cl_mem &>(m_mem);
    }

    /// Returns the size of the memory object in bytes.
    size_t get_memory_size() const
    {
        return get_memory_info<size_t>(CL_MEM_SIZE);
    }

    /// Returns the type for the memory object.
    cl_mem_object_type get_memory_type() const
    {
        return get_memory_info<cl_mem_object_type>(CL_MEM_TYPE);
    }

    /// Returns the flags for the memory object.
    cl_mem_flags get_memory_flags() const
    {
        return get_memory_info<cl_mem_flags>(CL_MEM_FLAGS);
    }

    /// Returns the context for the memory object.
    context get_context() const
    {
        return context(get_memory_info<cl_context>(CL_MEM_CONTEXT));
    }

    /// Returns the host pointer associated with the memory object.
    void* get_host_ptr() const
    {
        return get_memory_info<void *>(CL_MEM_HOST_PTR);
    }

    /// Returns the reference count for the memory object.
    uint_ reference_count() const
    {
        return get_memory_info<uint_>(CL_MEM_REFERENCE_COUNT);
    }

    /// Returns information about the memory object.
    ///
    /// \see_opencl_ref{clGetMemObjectInfo}
    template<class T>
    T get_memory_info(cl_mem_info info) const
    {
        return detail::get_object_info<T>(clGetMemObjectInfo, m_mem, info);
    }

    #if defined(BOOST_COMPUTE_CL_VERSION_1_1) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Registers a function to be called when the memory object is deleted
    /// and its resources freed.
    ///
    /// \see_opencl_ref{clSetMemObjectDestructorCallback}
    ///
    /// \opencl_version_warning{1,1}
    void set_destructor_callback(void (BOOST_COMPUTE_CL_CALLBACK *callback)(
                                     cl_mem memobj, void *user_data
                                 ),
                                 void *user_data = 0)
    {
        cl_int ret = clSetMemObjectDestructorCallback(m_mem, callback, user_data);
        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }
    }
    /// Registers a function to be called when the memory object is deleted
    /// and its resources freed.
    ///
    /// The function specified by \p callback must be invokable with zero
    /// arguments (e.g. \c callback()).
    ///
    /// \opencl_version_warning{1,1}
    template<class Function>
    void set_destructor_callback(Function callback)
    {
        set_destructor_callback(
            destructor_callback_invoker,
            new boost::function<void()>(callback)
        );
    }
    #endif // BOOST_COMPUTE_CL_VERSION_1_1

    /// Returns \c true if the memory object is the same as \p other.
    bool operator==(const memory_object &other) const
    {
        return m_mem == other.m_mem;
    }

    /// Returns \c true if the memory object is different from \p other.
    bool operator!=(const memory_object &other) const
    {
        return m_mem != other.m_mem;
    }

private:
    #ifdef BOOST_COMPUTE_CL_VERSION_1_1
    /// \internal_
    static void BOOST_COMPUTE_CL_CALLBACK
    destructor_callback_invoker(cl_mem, void *user_data)
    {
        boost::function<void()> *callback =
            static_cast<boost::function<void()> *>(user_data);

        (*callback)();

        delete callback;
    }
    #endif // BOOST_COMPUTE_CL_VERSION_1_1

protected:
    /// \internal_
    memory_object()
        : m_mem(0)
    {
    }

    /// \internal_
    explicit memory_object(cl_mem mem, bool retain = true)
        : m_mem(mem)
    {
        if(m_mem && retain){
            clRetainMemObject(m_mem);
        }
    }

    /// \internal_
    memory_object(const memory_object &other)
        : m_mem(other.m_mem)
    {
        if(m_mem){
            clRetainMemObject(m_mem);
        }
    }

    /// \internal_
    memory_object& operator=(const memory_object &other)
    {
        if(this != &other){
            if(m_mem){
                clReleaseMemObject(m_mem);
            }

            m_mem = other.m_mem;

            if(m_mem){
                clRetainMemObject(m_mem);
            }
        }

        return *this;
    }

    #ifndef BOOST_COMPUTE_NO_RVALUE_REFERENCES
    /// \internal_
    memory_object(memory_object&& other) BOOST_NOEXCEPT
        : m_mem(other.m_mem)
    {
        other.m_mem = 0;
    }

    /// \internal_
    memory_object& operator=(memory_object&& other) BOOST_NOEXCEPT
    {
        if(m_mem){
            clReleaseMemObject(m_mem);
        }

        m_mem = other.m_mem;
        other.m_mem = 0;

        return *this;
    }
    #endif // BOOST_COMPUTE_NO_RVALUE_REFERENCES

    /// \internal_
    ~memory_object()
    {
        if(m_mem){
            BOOST_COMPUTE_ASSERT_CL_SUCCESS(
                clReleaseMemObject(m_mem)
            );
        }
    }

protected:
    cl_mem m_mem;
};

namespace detail {

// set_kernel_arg specialization for memory_object
template<>
struct set_kernel_arg<memory_object>
{
    void operator()(kernel &kernel_, size_t index, const memory_object &mem)
    {
        kernel_.set_arg(index, mem.get());
    }
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_MEMORY_OBJECT_HPP

/* memory_object.hpp
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
*/