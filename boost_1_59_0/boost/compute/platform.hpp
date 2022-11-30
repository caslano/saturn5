//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_PLATFORM_HPP
#define BOOST_COMPUTE_PLATFORM_HPP

#include <algorithm>
#include <string>
#include <vector>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <boost/compute/cl.hpp>
#include <boost/compute/device.hpp>
#include <boost/compute/detail/get_object_info.hpp>

namespace boost {
namespace compute {

/// \class platform
/// \brief A compute platform.
///
/// The platform class provides an interface to an OpenCL platform.
///
/// To obtain a list of all platforms on the system use the
/// system::platforms() method.
///
/// \see device, context
class platform
{
public:
    /// Creates a new platform object for \p id.
    explicit platform(cl_platform_id id)
        : m_platform(id)
    {
    }

    /// Creates a new platform as a copy of \p other.
    platform(const platform &other)
        : m_platform(other.m_platform)
    {
    }

    /// Copies the platform id from \p other.
    platform& operator=(const platform &other)
    {
        if(this != &other){
            m_platform = other.m_platform;
        }

        return *this;
    }

    /// Destroys the platform object.
    ~platform()
    {
    }

    /// Returns the ID of the platform.
    cl_platform_id id() const
    {
        return m_platform;
    }

    /// Returns the name of the platform.
    std::string name() const
    {
        return get_info<std::string>(CL_PLATFORM_NAME);
    }

    /// Returns the name of the vendor for the platform.
    std::string vendor() const
    {
        return get_info<std::string>(CL_PLATFORM_VENDOR);
    }

    /// Returns the profile string for the platform.
    std::string profile() const
    {
        return get_info<std::string>(CL_PLATFORM_PROFILE);
    }

    /// Returns the version string for the platform.
    std::string version() const
    {
        return get_info<std::string>(CL_PLATFORM_VERSION);
    }

    /// Returns a list of extensions supported by the platform.
    std::vector<std::string> extensions() const
    {
        std::string extensions_string =
            get_info<std::string>(CL_PLATFORM_EXTENSIONS);
        std::vector<std::string> extensions_vector;
        boost::split(extensions_vector,
                     extensions_string,
                     boost::is_any_of("\t "),
                     boost::token_compress_on);
        return extensions_vector;
    }

    /// Returns \c true if the platform supports the extension with
    /// \p name.
    bool supports_extension(const std::string &name) const
    {
        const std::vector<std::string> extensions = this->extensions();

        return std::find(
            extensions.begin(), extensions.end(), name) != extensions.end();
    }

    /// Returns a list of devices on the platform.
    std::vector<device> devices(cl_device_type type = CL_DEVICE_TYPE_ALL) const
    {
        size_t count = device_count(type);
        if(count == 0){
            // no devices for this platform
            return std::vector<device>();
        }

        std::vector<cl_device_id> device_ids(count);
        cl_int ret = clGetDeviceIDs(m_platform,
                                    type,
                                    static_cast<cl_uint>(count),
                                    &device_ids[0],
                                    0);
        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        std::vector<device> devices;
        for(cl_uint i = 0; i < count; i++){
            devices.push_back(device(device_ids[i]));
        }

        return devices;
    }

    /// Returns the number of devices on the platform.
    size_t device_count(cl_device_type type = CL_DEVICE_TYPE_ALL) const
    {
        cl_uint count = 0;
        cl_int ret = clGetDeviceIDs(m_platform, type, 0, 0, &count);
        if(ret != CL_SUCCESS){
            if(ret == CL_DEVICE_NOT_FOUND){
                // no devices for this platform
                return 0;
            }
            else {
                // something else went wrong
                BOOST_THROW_EXCEPTION(opencl_error(ret));
            }
        }

        return count;
    }

    /// Returns information about the platform.
    ///
    /// \see_opencl_ref{clGetPlatformInfo}
    template<class T>
    T get_info(cl_platform_info info) const
    {
        return detail::get_object_info<T>(clGetPlatformInfo, m_platform, info);
    }

    /// \overload
    template<int Enum>
    typename detail::get_object_info_type<platform, Enum>::type
    get_info() const;

    /// Returns the address of the \p function_name extension
    /// function. Returns \c 0 if \p function_name is invalid.
    void* get_extension_function_address(const char *function_name) const
    {
        #ifdef BOOST_COMPUTE_CL_VERSION_1_2
        return clGetExtensionFunctionAddressForPlatform(m_platform,
                                                        function_name);
        #else
        return clGetExtensionFunctionAddress(function_name);
        #endif
    }

    /// Requests that the platform unload any compiler resources.
    void unload_compiler()
    {
        #ifdef BOOST_COMPUTE_CL_VERSION_1_2
        clUnloadPlatformCompiler(m_platform);
        #else
        clUnloadCompiler();
        #endif
    }

    /// Returns \c true if the platform is the same at \p other.
    bool operator==(const platform &other) const
    {
        return m_platform == other.m_platform;
    }

    /// Returns \c true if the platform is different from \p other.
    bool operator!=(const platform &other) const
    {
        return m_platform != other.m_platform;
    }

    /// Returns \c true if the platform OpenCL version is major.minor
    /// or newer; otherwise returns \c false.
    bool check_version(int major, int minor) const
    {
        std::stringstream stream;
        stream << version();

        int actual_major, actual_minor;
        stream.ignore(7); // 'OpenCL '
        stream >> actual_major;
        stream.ignore(1); // '.'
        stream >> actual_minor;

        return actual_major > major ||
               (actual_major == major && actual_minor >= minor);
    }

private:
    cl_platform_id m_platform;
};

/// \internal_ define get_info() specializations for platform
BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS(platform,
    ((std::string, CL_PLATFORM_PROFILE))
    ((std::string, CL_PLATFORM_VERSION))
    ((std::string, CL_PLATFORM_NAME))
    ((std::string, CL_PLATFORM_VENDOR))
    ((std::string, CL_PLATFORM_EXTENSIONS))
)

#ifdef BOOST_COMPUTE_CL_VERSION_2_1
BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS(platform,
    ((cl_ulong, CL_PLATFORM_HOST_TIMER_RESOLUTION))
)
#endif // BOOST_COMPUTE_CL_VERSION_2_1

inline boost::compute::platform device::platform() const
{
    return boost::compute::platform(get_info<CL_DEVICE_PLATFORM>());
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_PLATFORM_HPP

/* platform.hpp
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
*/