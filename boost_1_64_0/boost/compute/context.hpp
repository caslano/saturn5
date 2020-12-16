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
3jWlDlp3z9R5xzT9aORxh9BDK+6aOu6X8m6p416p8z6pUv+svzdaw/ui445OS/q+aH61416ovBNqrJ5llAD8gCCgE9ANeBCwEPAHYNyELGMyYE/AERNG9NEjv5HfyG/kN/Ib+Y38Rn4jv5HfyO//91sS9//D+L++PdwyHPf/Tf3973nRu/wB6maXNu1y0j3G1Du8KvZtzfLrG2fVNzTuo72DS9zV5b31z4T/I2NZlPYm760/lW+mC9vvVTFdqVFAnczHwv+pMRb/vw+I3odsbW8B8bN5570A7gcC9wvsP2UZCwDcx2eeK4kyPy4SrxuG9+Ed6WrEz3zNjK837VmK/HMF920Q/oww1JtSd18m8FJFeXnwby78p6O8XOwfTRb55SHkJBE+Gfs1mcKGprgTJ8KeMpYm/SjVxBdlNYm4JmMV5pFry6PEyBB0fyXoFiKX5w9GC5zHYf/Hx3oQdO/b0hithzECJ03qrH7B5txd4t1C7zt+yxgZORE6jFJI2vXOH+oSYWHe97Tf+bPXE3Cl3sMu301yUiLlGF1FEf929H9d5Hz3oZK63leoU3gBcDRwfK872iYUxQfo2iZx841c6jtLhf8k1H6lTac6KwSHdWqluQH7x5XKe/MBme8VEgeR8k3JXLahRwXOSkY22mcu7asGRdixxlTW49GCU8GCfD9iOmn0oz3sABD5jxJ4QEP+tAc5VeCFjHGk4bWxot20d5g45H9jgXMk9lIr5RmFiSJstNT5/pEXaSN/wv0rz/uNS5e2wXZAebJt6O2iCnk5z4rwPYAmgQuXbyCUvBGt86bWGTwpoh2TiL+c5HmO8Kfo7ngSv0K+gXC46aeN+O9Ef0SpAp91JOLXMlbGXdvqDNAIuv+G7LIzjLRc8UxFVvqo9OzREGts3cg3R7cQeaxDvyzTcT+3IQEdVzJ3TClnKARizr9Qzt0xcp7ZirR6ORM/U8r5NXc5E3/DeLlSJo+L+Bz6o/kVQ849kPG80RE5ZxlZ22eVmhLO0sr3dpF22di8hHwTPTuTiN1bS6bp1OWex3djjgOcb+qxY2Q6u6kNY2ET+3VUF02ZEh8Ucj5d5k3Tf5BRj7I0ulGmWV6eZ8sSaQ7FfcEU5XshASsNqN2J55cCkFGtSLeictzb0ZZmL55R2TGaRttX1hPxG0s70W3CnyHqNB1C7loqUqdp473rdEWRdh3alGbZoCXTSEVN+0TdJno+IzxK6uRVemH9OOfWBnhH/Tm2gbsBx5nn7950toG2hoPdxi/iryn71b4LOJ7xHYOY8w3EB+c85/Oi8F9ntNnfDUIacCvbyHMC5zbj8OibQcxneV39M/45jMs7xta3XKv8KnAONKZwXTZV0p9hjEedZy4tFJys81Hpacux1l3Gys8i9U4/8+NYKc5TcqysH+JbKpAtz27Enlmi7DT1vwXrvy87xoY33yjoWRCtf5worJ/RPGvmjKZ6uTDStoMFrva8GZ+e8FnAxMazyHsLr42hzX5mtBpgwPw2cPIi2nMorOUB+M454mPhT9PxRPzVtW3h5QWOcZ35pXqeL0xGBtYZtN5l5NlG8RsFOMIc02NksO/MppZGIQVtn2aa0brvIRmfy/SGSA+z2zbefxI4KUOqb67f49quwRzJsjGG623jrSivbUm0XZEOvuj4g+j2JhGfZ8h47fs4jI9dX8tvtKVFfLptfQySbG8zjRbxo4ckq0jfF3TzjKy9rSRmB1r97oXuLFDy720M13sYajvTunc4hu/di5/FmaUzlq869MCmHZ56edaRP27empqlOyOke/di8Z/dUr+/kvx7G8m+16I+A6Z7N8VhB1rMseXIt57vdiwwuEfCvZ5y7vs8T/w=
*/