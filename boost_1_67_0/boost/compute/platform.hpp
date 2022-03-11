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
+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
*/