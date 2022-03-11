//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_SYSTEM_HPP
#define BOOST_COMPUTE_SYSTEM_HPP

#include <string>
#include <vector>
#include <cstdlib>

#include <boost/throw_exception.hpp>

#include <boost/compute/cl.hpp>
#include <boost/compute/device.hpp>
#include <boost/compute/context.hpp>
#include <boost/compute/platform.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/detail/getenv.hpp>
#include <boost/compute/exception/no_device_found.hpp>

namespace boost {
namespace compute {

/// \class system
/// \brief Provides access to platforms and devices on the system.
///
/// The system class contains a set of static functions which provide access to
/// the OpenCL platforms and compute devices on the host system.
///
/// The default_device() convenience method automatically selects and returns
/// the "best" compute device for the system following a set of heuristics and
/// environment variables. This simplifies setup of the OpenCL enviornment.
///
/// \see platform, device, context
class system
{
public:
    /// Returns the default compute device for the system.
    ///
    /// The default device is selected based on a set of heuristics and can be
    /// influenced using one of the following environment variables:
    ///
    /// \li \c BOOST_COMPUTE_DEFAULT_DEVICE -
    ///        name of the compute device (e.g. "GTX TITAN")
    /// \li \c BOOST_COMPUTE_DEFAULT_DEVICE_TYPE
    ///        type of the compute device (e.g. "GPU" or "CPU")
    /// \li \c BOOST_COMPUTE_DEFAULT_PLATFORM -
    ///        name of the platform (e.g. "NVIDIA CUDA")
    /// \li \c BOOST_COMPUTE_DEFAULT_VENDOR -
    ///        name of the device vendor (e.g. "NVIDIA")
    /// \li \c BOOST_COMPUTE_DEFAULT_ENFORCE -
    ///        If this is set to "1", then throw a no_device_found() exception
    ///        if any of the above environment variables is set, but a matching
    ///        device was not found.
    ///
    /// The default device is determined once on the first time this function
    /// is called. Calling this function multiple times will always result in
    /// the same device being returned.
    ///
    /// If no OpenCL device is found on the system, a no_device_found exception
    /// is thrown.
    ///
    /// For example, to print the name of the default compute device on the
    /// system:
    /// \code
    /// // get the default compute device
    /// boost::compute::device device = boost::compute::system::default_device();
    ///
    /// // print the name of the device
    /// std::cout << "default device: " << device.name() << std::endl;
    /// \endcode
    static device default_device()
    {
        static device default_device = find_default_device();

        return default_device;
    }

    /// Returns the device with \p name.
    ///
    /// \throws no_device_found if no device with \p name is found.
    static device find_device(const std::string &name)
    {
        const std::vector<device> devices = system::devices();
        for(size_t i = 0; i < devices.size(); i++){
            const device& device = devices[i];

            if(device.name() == name){
                return device;
            }
        }

        BOOST_THROW_EXCEPTION(no_device_found());
    }

    /// Returns a vector containing all of the compute devices on
    /// the system.
    ///
    /// For example, to print out the name of each OpenCL-capable device
    /// available on the system:
    /// \code
    /// for(const auto &device : boost::compute::system::devices()){
    ///     std::cout << device.name() << std::endl;
    /// }
    /// \endcode
    static std::vector<device> devices()
    {
        std::vector<device> devices;

        const std::vector<platform> platforms = system::platforms();
        for(size_t i = 0; i < platforms.size(); i++){
            const std::vector<device> platform_devices = platforms[i].devices();

            devices.insert(
                devices.end(), platform_devices.begin(), platform_devices.end()
            );
        }

        return devices;
    }

    /// Returns the number of compute devices on the system.
    static size_t device_count()
    {
        size_t count = 0;

        const std::vector<platform> platforms = system::platforms();
        for(size_t i = 0; i < platforms.size(); i++){
            count += platforms[i].device_count();
        }

        return count;
    }

    /// Returns the default context for the system.
    ///
    /// The default context is created for the default device on the system
    /// (as returned by default_device()).
    ///
    /// The default context is created once on the first time this function is
    /// called. Calling this function multiple times will always result in the
    /// same context object being returned.
    static context default_context()
    {
        static context default_context(default_device());

        return default_context;
    }

    /// Returns the default command queue for the system.
    static command_queue& default_queue()
    {
        static command_queue queue(default_context(), default_device());

        return queue;
    }

    /// Blocks until all outstanding computations on the default
    /// command queue are complete.
    ///
    /// This is equivalent to:
    /// \code
    /// system::default_queue().finish();
    /// \endcode
    static void finish()
    {
        default_queue().finish();
    }

    /// Returns a vector containing each of the OpenCL platforms on the system.
    ///
    /// For example, to print out the name of each OpenCL platform present on
    /// the system:
    /// \code
    /// for(const auto &platform : boost::compute::system::platforms()){
    ///     std::cout << platform.name() << std::endl;
    /// }
    /// \endcode
    static std::vector<platform> platforms()
    {
        cl_uint count = 0;
        clGetPlatformIDs(0, 0, &count);

        std::vector<platform> platforms;
        if(count > 0)
        {
            std::vector<cl_platform_id> platform_ids(count);
            clGetPlatformIDs(count, &platform_ids[0], 0);

            for(size_t i = 0; i < platform_ids.size(); i++){
                platforms.push_back(platform(platform_ids[i]));
            }
        }
        return platforms;
    }

    /// Returns the number of compute platforms on the system.
    static size_t platform_count()
    {
        cl_uint count = 0;
        clGetPlatformIDs(0, 0, &count);
        return static_cast<size_t>(count);
    }

private:
    /// \internal_
    static device find_default_device()
    {
        // get a list of all devices on the system
        const std::vector<device> devices_ = devices();
        if(devices_.empty()){
            BOOST_THROW_EXCEPTION(no_device_found());
        }

        // check for device from environment variable
        const char *name     = detail::getenv("BOOST_COMPUTE_DEFAULT_DEVICE");
        const char *type     = detail::getenv("BOOST_COMPUTE_DEFAULT_DEVICE_TYPE");
        const char *platform = detail::getenv("BOOST_COMPUTE_DEFAULT_PLATFORM");
        const char *vendor   = detail::getenv("BOOST_COMPUTE_DEFAULT_VENDOR");
        const char *enforce  = detail::getenv("BOOST_COMPUTE_DEFAULT_ENFORCE");

        if(name || type || platform || vendor){
            for(size_t i = 0; i < devices_.size(); i++){
                const device& device = devices_[i];
                if (name && !matches(device.name(), name))
                    continue;

                if (type && matches(std::string("GPU"), type))
                    if (!(device.type() & device::gpu))
                        continue;

                if (type && matches(std::string("CPU"), type))
                    if (!(device.type() & device::cpu))
                        continue;

                if (platform && !matches(device.platform().name(), platform))
                    continue;

                if (vendor && !matches(device.vendor(), vendor))
                    continue;

                return device;
            }

            if(enforce && enforce[0] == '1')
                BOOST_THROW_EXCEPTION(no_device_found());
        }

        // find the first gpu device
        for(size_t i = 0; i < devices_.size(); i++){
            const device& device = devices_[i];

            if(device.type() & device::gpu){
                return device;
            }
        }

        // find the first cpu device
        for(size_t i = 0; i < devices_.size(); i++){
            const device& device = devices_[i];

            if(device.type() & device::cpu){
                return device;
            }
        }

        // return the first device found
        return devices_[0];
    }

    /// \internal_
    static bool matches(const std::string &str, const std::string &pattern)
    {
        return str.find(pattern) != std::string::npos;
    }
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_SYSTEM_HPP

/* system.hpp
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
*/