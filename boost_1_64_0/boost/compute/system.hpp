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
h2WwAk6Cs2EVvBQeDK+H1bARToF3wanwXlhrHTesg0thPXwJHgGTqK8G2B4eCzeEx8HO8AS4OTwVDoSnw6FwDtwTngMnw/NgLTwfHgkvgMfDi+AJ8GL1u3gv8m4Pd9Xr1IX/X9Jr/J76v3ysYzk/gVlwORwKP4MT4OdwEvwaHg6/0bGr38LL4HfwKvgDvB7+DO+Ev8Gl8Hf4BrQe+u+C9rCUY9kQlsM0eAPsDF+AyfAHmA5/gRvDZI4/A24Mu8AusCtUPxTezaJ+KDNj/FBot0Zupcolu8j1NHKEkubLW26e19Y7Dhtj5hKbp2Nmr4TbaXoAvALurNuHwPnql3M9rII3wVnwFngBXASvg3fC+yBR7ov74VPwAfgcXAzfgY/r/fAE/AI+Bb+Hz0Hrnf4FuBl8EfaCr8AR8DW4D3wdHgjfgCH4JmxI0N9mYXEKPjbNz2Uf8aupI9Znr/uX+dX8nT41K3Zst9b8aqL+NC2f2/7vmtd+9S0tn9s+6jvTsjGvifrMvPQPzXHv5Ssz4Pr2azTH/VLun5XEjHGsQ0wcT2wY5/vG+MEPfvCDH/ywNsJasv9j3JzRX8z/a2j/747ud6A1Rm+SjO0fmtNfdLjG9r+Fjv1/T/fnDR+hEs4x/z+kRdcRmO0y5v8ayigYK/pb8yN2nfl8p84c2dbrzOfbdOb99Zh+DbrrzGfGHFNL9OWNk+L05aYOyl3G9y+wfCRifq/1uvLw76x2+Z3rLRuF/o7tgpl5Fa6NtU+sQV1fq3VtP6bqNh72ibhjatl8CiWV3vX9Upv4eriBYwsUxv5mi+ZRiKvvbur70kd/pyfxJss2Ueji++Lt80K9ax5KMDZWxjUiYeZPMPuNb4rTXqn73X1edBy0ypjz/T2t+XkRdPywq+0/On5YjtXozDk+p848zh/AaU+ao3b7A5MYfwR3h41WP+RWjyHs/k3XpebLN2uOPCDp3YI7B5PUThMMHLyPta3Uq761jDxJH0IZ90o6JSm+/odK/dwl+zdK0uuh+ffz9EHKgreJTFfJUxXNE+9/pPah62R/RpLdJkQeY+tZ5hx7Pm2i+smITd5u24/J91rAxZdHbT/9pJ7miS9PRHd1peRtDKTLtqBsG1sUXsPkjcCQeF8etZ/dIPm6e/ryVCPzlMj8Hozz3VF71U2yfxNX351cc/4Oe720g3S4So5xBm2vDeVZ26LtwNWfR22Fv8hvTg1K2rSd/cVO36OddG7iy9Nhw6nxtjCV6YXMjyJzXG/Tt8bI5BqZYz+Jldmf9Eak/0jAZ6gtcVqq03eoPYy1lbHf2MsqAya4+gIU2/yFOP84f6Ez9nH6CzV69Bl3ufQZi136jCUePkTLnD5EIvuakdU2b/qneF8hs75Rh+j6RlvCR+BdVp+zr6PPmVw+UXod136CqlP5Pqb9XiDpO4Ju/XReMCKfZe7phZKeF/TqtytNnp1MX3S1pPM1jd/Jfla6yPXel3YOL5Y8VwZNXyPpbTRPvC17Y7i/lHuZwwZNPtNvzBRZeYcgUFW2fuNWkTsx2JTt+TqRuToYXSd5qnXypr94RPafH06b89wrYNmh5/LMaEjhXc66X9pv426HVrl5yP0cvq+ui7v3VObRqEydl6/N7ewPqS36brVBQ3NfbdqxdfZo657i3OLszyUu90qly71SE3+vyPb62PtCt8802/Wax9wbC9ePf3+6l2u8rNjM3WHeWQP6zn53zHskst5zdpj9nnN2sL/1c3bc3Yo5OyLnPn+D+HN/wGrf48y5294fw+d+X8y5I+t97ma/57mzv/Xnft8anHv1hvHnvth6nx1n5iuJXnf3bzVkm5ynhP2tn6eE33KfpyTmPAakxp8=
*/