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