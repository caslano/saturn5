//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_CONTEXT_HPP
#define BOOST_COMPUTE_CONTEXT_HPP

#include <vector>

#include <boost/throw_exception.hpp>

#include <boost/compute/config.hpp>
#include <boost/compute/device.hpp>
#include <boost/compute/exception/opencl_error.hpp>
#include <boost/compute/detail/assert_cl_success.hpp>

namespace boost {
namespace compute {

/// \class context
/// \brief A compute context.
///
/// The context class represents a compute context.
///
/// A context object manages a set of OpenCL resources including memory
/// buffers and program objects. Before allocating memory on the device or
/// executing kernels you must set up a context object.
///
/// To create a context for the default device on the system:
/// \code
/// // get the default compute device
/// boost::compute::device gpu = boost::compute::system::default_device();
///
/// // create a context for the device
/// boost::compute::context context(gpu);
/// \endcode
///
/// Once a context is created, memory can be allocated using the buffer class
/// and kernels can be executed using the command_queue class.
///
/// \see device, command_queue
class context
{
public:
    /// Create a null context object.
    context()
        : m_context(0)
    {
    }

    /// Creates a new context for \p device with \p properties.
    ///
    /// \see_opencl_ref{clCreateContext}
    explicit context(const device &device,
                     const cl_context_properties *properties = 0)
    {
        BOOST_ASSERT(device.id() != 0);

        cl_device_id device_id = device.id();

        cl_int error = 0;
        m_context = clCreateContext(properties, 1, &device_id, 0, 0, &error);

        if(!m_context){
            BOOST_THROW_EXCEPTION(opencl_error(error));
        }
    }

    /// Creates a new context for \p devices with \p properties.
    ///
    /// \see_opencl_ref{clCreateContext}
    explicit context(const std::vector<device> &devices,
                     const cl_context_properties *properties = 0)
    {
        BOOST_ASSERT(!devices.empty());

        cl_int error = 0;

        m_context = clCreateContext(
            properties,
            static_cast<cl_uint>(devices.size()),
            reinterpret_cast<const cl_device_id *>(&devices[0]),
            0,
            0,
            &error
        );

        if(!m_context){
            BOOST_THROW_EXCEPTION(opencl_error(error));
        }
    }

    /// Creates a new context object for \p context. If \p retain is
    /// \c true, the reference count for \p context will be incremented.
    explicit context(cl_context context, bool retain = true)
        : m_context(context)
    {
        if(m_context && retain){
            clRetainContext(m_context);
        }
    }

    /// Creates a new context object as a copy of \p other.
    context(const context &other)
        : m_context(other.m_context)
    {
        if(m_context){
            clRetainContext(m_context);
        }
    }

    /// Copies the context object from \p other to \c *this.
    context& operator=(const context &other)
    {
        if(this != &other){
            if(m_context){
                clReleaseContext(m_context);
            }

            m_context = other.m_context;

            if(m_context){
                clRetainContext(m_context);
            }
        }

        return *this;
    }

    #ifndef BOOST_COMPUTE_NO_RVALUE_REFERENCES
    /// Move-constructs a new context object from \p other.
    context(context&& other) BOOST_NOEXCEPT
        : m_context(other.m_context)
    {
        other.m_context = 0;
    }

    /// Move-assigns the context from \p other to \c *this.
    context& operator=(context&& other) BOOST_NOEXCEPT
    {
        if(m_context){
            clReleaseContext(m_context);
        }

        m_context = other.m_context;
        other.m_context = 0;

        return *this;
    }
    #endif // BOOST_COMPUTE_NO_RVALUE_REFERENCES

    /// Destroys the context object.
    ~context()
    {
        if(m_context){
            BOOST_COMPUTE_ASSERT_CL_SUCCESS(
                clReleaseContext(m_context)
            );
        }
    }

    /// Returns the underlying OpenCL context.
    cl_context& get() const
    {
        return const_cast<cl_context &>(m_context);
    }

    /// Returns the device for the context. If the context contains multiple
    /// devices, the first is returned.
    device get_device() const
    {
        std::vector<device> devices = get_devices();

        if(devices.empty()) {
            return device();
        }

        return devices.front();
    }

    /// Returns a vector of devices for the context.
    std::vector<device> get_devices() const
    {
        return get_info<std::vector<device> >(CL_CONTEXT_DEVICES);
    }

    /// Returns information about the context.
    ///
    /// \see_opencl_ref{clGetContextInfo}
    template<class T>
    T get_info(cl_context_info info) const
    {
        return detail::get_object_info<T>(clGetContextInfo, m_context, info);
    }

    /// \overload
    template<int Enum>
    typename detail::get_object_info_type<context, Enum>::type
    get_info() const;

    /// Returns \c true if the context is the same as \p other.
    bool operator==(const context &other) const
    {
        return m_context == other.m_context;
    }

    /// Returns \c true if the context is different from \p other.
    bool operator!=(const context &other) const
    {
        return m_context != other.m_context;
    }

    /// \internal_
    operator cl_context() const
    {
        return m_context;
    }

private:
    cl_context m_context;
};

/// \internal_ define get_info() specializations for context
BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS(context,
    ((cl_uint, CL_CONTEXT_REFERENCE_COUNT))
    ((std::vector<cl_device_id>, CL_CONTEXT_DEVICES))
    ((std::vector<cl_context_properties>, CL_CONTEXT_PROPERTIES))
)

#ifdef BOOST_COMPUTE_CL_VERSION_1_1
BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS(context,
    ((cl_uint, CL_CONTEXT_NUM_DEVICES))
)
#endif // BOOST_COMPUTE_CL_VERSION_1_1

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_CONTEXT_HPP

/* context.hpp
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
*/