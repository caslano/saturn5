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
+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
*/