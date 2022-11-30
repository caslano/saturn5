//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DEVICE_HPP
#define BOOST_COMPUTE_DEVICE_HPP

#include <algorithm>
#include <string>
#include <vector>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <boost/compute/config.hpp>
#include <boost/compute/exception.hpp>
#include <boost/compute/types/fundamental.hpp>
#include <boost/compute/detail/duration.hpp>
#include <boost/compute/detail/get_object_info.hpp>
#include <boost/compute/detail/assert_cl_success.hpp>

namespace boost {
namespace compute {

class platform;

/// \class device
/// \brief A compute device.
///
/// Typical compute devices include GPUs and multi-core CPUs. A list
/// of all compute devices available on a platform can be obtained
/// via the platform::devices() method.
///
/// The default compute device for the system can be obtained with
/// the system::default_device() method. For example:
///
/// \snippet test/test_device.cpp default_gpu
///
/// \see platform, context, command_queue
class device
{
public:
    enum type {
        cpu = CL_DEVICE_TYPE_CPU,
        gpu = CL_DEVICE_TYPE_GPU,
        accelerator = CL_DEVICE_TYPE_ACCELERATOR
    };

    /// Creates a null device object.
    device()
        : m_id(0)
    {
    }

    /// Creates a new device object for \p id. If \p retain is \c true,
    /// the reference count for the device will be incremented.
    explicit device(cl_device_id id, bool retain = true)
        : m_id(id)
    {
        #ifdef BOOST_COMPUTE_CL_VERSION_1_2
        if(m_id && retain && is_subdevice()){
            clRetainDevice(m_id);
        }
        #else
        (void) retain;
        #endif
    }

    /// Creates a new device object as a copy of \p other.
    device(const device &other)
        : m_id(other.m_id)
    {
        #ifdef BOOST_COMPUTE_CL_VERSION_1_2
        if(m_id && is_subdevice()){
            clRetainDevice(m_id);
        }
        #endif
    }

    /// Copies the device from \p other to \c *this.
    device& operator=(const device &other)
    {
        if(this != &other){
            #ifdef BOOST_COMPUTE_CL_VERSION_1_2
            if(m_id && is_subdevice()){
                clReleaseDevice(m_id);
            }
            #endif

            m_id = other.m_id;

            #ifdef BOOST_COMPUTE_CL_VERSION_1_2
            if(m_id && is_subdevice()){
                clRetainDevice(m_id);
            }
            #endif
        }

        return *this;
    }

    #ifndef BOOST_COMPUTE_NO_RVALUE_REFERENCES
    /// Move-constructs a new device object from \p other.
    device(device&& other) BOOST_NOEXCEPT
        : m_id(other.m_id)
    {
        other.m_id = 0;
    }

    /// Move-assigns the device from \p other to \c *this.
    device& operator=(device&& other) BOOST_NOEXCEPT
    {
        #ifdef BOOST_COMPUTE_CL_VERSION_1_2
        if(m_id && is_subdevice()){
            clReleaseDevice(m_id);
        }
        #endif

        m_id = other.m_id;
        other.m_id = 0;

        return *this;
    }
    #endif // BOOST_COMPUTE_NO_RVALUE_REFERENCES

    /// Destroys the device object.
    ~device()
    {
        #ifdef BOOST_COMPUTE_CL_VERSION_1_2
        if(m_id && is_subdevice()){
            BOOST_COMPUTE_ASSERT_CL_SUCCESS(
                clReleaseDevice(m_id)
            );
        }
        #endif
    }

    /// Returns the ID of the device.
    cl_device_id id() const
    {
        return m_id;
    }

    /// Returns a reference to the underlying OpenCL device id.
    cl_device_id& get() const
    {
        return const_cast<cl_device_id&>(m_id);
    }

    /// Returns the type of the device.
    cl_device_type type() const
    {
        return get_info<cl_device_type>(CL_DEVICE_TYPE);
    }

    #ifdef BOOST_COMPUTE_DOXYGEN_INVOKED
    /// Returns the platform for the device.
    platform platform() const;
    #else
    boost::compute::platform platform() const;
    #endif

    /// Returns the name of the device.
    std::string name() const
    {
        return get_info<std::string>(CL_DEVICE_NAME);
    }

    /// Returns the name of the vendor for the device.
    std::string vendor() const
    {
        return get_info<std::string>(CL_DEVICE_VENDOR);
    }

    /// Returns the device profile string.
    std::string profile() const
    {
        return get_info<std::string>(CL_DEVICE_PROFILE);
    }

    /// Returns the device version string.
    std::string version() const
    {
        return get_info<std::string>(CL_DEVICE_VERSION);
    }

    /// Returns the driver version string.
    std::string driver_version() const
    {
        return get_info<std::string>(CL_DRIVER_VERSION);
    }

    /// Returns a list of extensions supported by the device.
    std::vector<std::string> extensions() const
    {
        std::string extensions_string =
            get_info<std::string>(CL_DEVICE_EXTENSIONS);
        std::vector<std::string> extensions_vector;
        boost::split(extensions_vector,
                     extensions_string,
                     boost::is_any_of("\t "),
                     boost::token_compress_on);
        return extensions_vector;
    }

    /// Returns \c true if the device supports the extension with
    /// \p name.
    bool supports_extension(const std::string &name) const
    {
        const std::vector<std::string> extensions = this->extensions();

        return std::find(
            extensions.begin(), extensions.end(), name) != extensions.end();
    }

    /// Returns the number of address bits.
    uint_ address_bits() const
    {
        return get_info<uint_>(CL_DEVICE_ADDRESS_BITS);
    }

    /// Returns the global memory size in bytes.
    ulong_ global_memory_size() const
    {
        return get_info<ulong_>(CL_DEVICE_GLOBAL_MEM_SIZE);
    }

    /// Returns the local memory size in bytes.
    ulong_ local_memory_size() const
    {
        return get_info<ulong_>(CL_DEVICE_LOCAL_MEM_SIZE);
    }

    /// Returns the clock frequency for the device's compute units.
    uint_ clock_frequency() const
    {
        return get_info<uint_>(CL_DEVICE_MAX_CLOCK_FREQUENCY);
    }

    /// Returns the number of compute units in the device.
    uint_ compute_units() const
    {
        return get_info<uint_>(CL_DEVICE_MAX_COMPUTE_UNITS);
    }

    /// \internal_
    ulong_ max_memory_alloc_size() const
    {
        return get_info<ulong_>(CL_DEVICE_MAX_MEM_ALLOC_SIZE);
    }

    /// \internal_
    size_t max_work_group_size() const
    {
        return get_info<size_t>(CL_DEVICE_MAX_WORK_GROUP_SIZE);
    }

    /// \internal_
    uint_ max_work_item_dimensions() const
    {
        return get_info<uint_>(CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS);
    }

    /// Returns the preferred vector width for type \c T.
    template<class T>
    uint_ preferred_vector_width() const
    {
        return 0;
    }

    /// Returns the profiling timer resolution in nanoseconds.
    size_t profiling_timer_resolution() const
    {
        return get_info<size_t>(CL_DEVICE_PROFILING_TIMER_RESOLUTION);
    }

    /// Returns \c true if the device is a sub-device.
    bool is_subdevice() const
    {
    #if defined(BOOST_COMPUTE_CL_VERSION_1_2)
        try {
            return get_info<cl_device_id>(CL_DEVICE_PARENT_DEVICE) != 0;
        }
        catch(opencl_error&){
            // the get_info() call above will throw if the device's opencl version
            // is less than 1.2 (in which case it can't be a sub-device).
            return false;
        }
    #else
        return false;
    #endif
    }

    /// Returns information about the device.
    ///
    /// For example, to get the number of compute units:
    /// \code
    /// device.get_info<cl_uint>(CL_DEVICE_MAX_COMPUTE_UNITS);
    /// \endcode
    ///
    /// Alternatively, the template-specialized version can be used which
    /// automatically determines the result type:
    /// \code
    /// device.get_info<CL_DEVICE_MAX_COMPUTE_UNITS>();
    /// \endcode
    ///
    /// \see_opencl_ref{clGetDeviceInfo}
    template<class T>
    T get_info(cl_device_info info) const
    {
        return detail::get_object_info<T>(clGetDeviceInfo, m_id, info);
    }

    /// \overload
    template<int Enum>
    typename detail::get_object_info_type<device, Enum>::type
    get_info() const;

    #if defined(BOOST_COMPUTE_CL_VERSION_1_2) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Partitions the device into multiple sub-devices according to
    /// \p properties.
    ///
    /// \opencl_version_warning{1,2}
    std::vector<device>
    partition(const cl_device_partition_property *properties) const
    {
        // get sub-device count
        uint_ count = 0;
        int_ ret = clCreateSubDevices(m_id, properties, 0, 0, &count);
        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        // get sub-device ids
        std::vector<cl_device_id> ids(count);
        ret = clCreateSubDevices(m_id, properties, count, &ids[0], 0);
        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }

        // convert ids to device objects
        std::vector<device> devices(count);
        for(size_t i = 0; i < count; i++){
            devices[i] = device(ids[i], false);
        }

        return devices;
    }

    /// \opencl_version_warning{1,2}
    std::vector<device> partition_equally(size_t count) const
    {
        cl_device_partition_property properties[] = {
            CL_DEVICE_PARTITION_EQUALLY,
            static_cast<cl_device_partition_property>(count),
            0
        };

        return partition(properties);
    }

    /// \opencl_version_warning{1,2}
    std::vector<device>
    partition_by_counts(const std::vector<size_t> &counts) const
    {
        std::vector<cl_device_partition_property> properties;

        properties.push_back(CL_DEVICE_PARTITION_BY_COUNTS);
        for(size_t i = 0; i < counts.size(); i++){
            properties.push_back(
                static_cast<cl_device_partition_property>(counts[i]));
        }
        properties.push_back(CL_DEVICE_PARTITION_BY_COUNTS_LIST_END);
        properties.push_back(0);

        return partition(&properties[0]);
    }

    /// \opencl_version_warning{1,2}
    std::vector<device>
    partition_by_affinity_domain(cl_device_affinity_domain domain) const
    {
        cl_device_partition_property properties[] = {
            CL_DEVICE_PARTITION_BY_AFFINITY_DOMAIN,
            static_cast<cl_device_partition_property>(domain),
            0
        };

        return partition(properties);
    }
    #endif // BOOST_COMPUTE_CL_VERSION_1_2

    #if defined(BOOST_COMPUTE_CL_VERSION_2_1) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Returns the current value of the host clock as seen by device
    /// in nanoseconds.
    ///
    /// \see_opencl21_ref{clGetHostTimer}
    ///
    /// \opencl_version_warning{2,1}
    ulong_ get_host_timer() const
    {
        ulong_ host_timestamp = 0;
        cl_int ret = clGetHostTimer(m_id, &host_timestamp);
        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }
        return host_timestamp;
    }

    /// Returns a reasonably synchronized pair of timestamps from the device timer
    /// and the host timer as seen by device in nanoseconds. The first of returned
    /// std::pair is a device timer timestamp, the second is a host timer timestamp.
    ///
    /// \see_opencl21_ref{clGetDeviceAndHostTimer}
    ///
    /// \opencl_version_warning{2,1}
    std::pair<ulong_, ulong_> get_device_and_host_timer() const
    {
        ulong_ host_timestamp;
        ulong_ device_timestamp;
        cl_int ret = clGetDeviceAndHostTimer(
            m_id, &device_timestamp, &host_timestamp
        );
        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }
        return std::make_pair(
            device_timestamp, host_timestamp
        );
    }

    #if !defined(BOOST_COMPUTE_NO_HDR_CHRONO) || !defined(BOOST_COMPUTE_NO_BOOST_CHRONO)
    /// Returns the current value of the host clock as seen by device
    /// as duration.
    ///
    /// For example, to print the current value of the host clock as seen by device
    /// in milliseconds:
    /// \code
    /// std::cout << device.get_host_timer<std::chrono::milliseconds>().count() << " ms";
    /// \endcode
    ///
    /// \see_opencl21_ref{clGetHostTimer}
    ///
    /// \opencl_version_warning{2,1}
    template<class Duration>
    Duration get_host_timer() const
    {
        const ulong_ nanoseconds = this->get_host_timer();
        return detail::make_duration_from_nanoseconds(Duration(), nanoseconds);
    }

    /// Returns a reasonably synchronized pair of timestamps from the device timer
    /// and the host timer as seen by device as a std::pair<Duration, Duration> value.
    /// The first of returned std::pair is a device timer timestamp, the second is
    /// a host timer timestamp.
    ///
    /// \see_opencl21_ref{clGetDeviceAndHostTimer}
    ///
    /// \opencl_version_warning{2,1}
    template<class Duration>
    std::pair<Duration, Duration> get_device_and_host_timer() const
    {
        const std::pair<ulong_, ulong_> timestamps = this->get_device_and_host_timer();
        return std::make_pair(
            detail::make_duration_from_nanoseconds(Duration(), timestamps.first),
            detail::make_duration_from_nanoseconds(Duration(), timestamps.second)
        );
    }
    #endif // !defined(BOOST_COMPUTE_NO_HDR_CHRONO) || !defined(BOOST_COMPUTE_NO_BOOST_CHRONO)
    #endif // BOOST_COMPUTE_CL_VERSION_2_1

    /// Returns \c true if the device is the same at \p other.
    bool operator==(const device &other) const
    {
        return m_id == other.m_id;
    }

    /// Returns \c true if the device is different from \p other.
    bool operator!=(const device &other) const
    {
        return m_id != other.m_id;
    }

    /// Returns \c true if the device OpenCL version is major.minor
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
    cl_device_id m_id;
};

/// \internal_
template<>
inline uint_ device::preferred_vector_width<short_>() const
{
    return get_info<uint_>(CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT);
}

/// \internal_
template<>
inline uint_ device::preferred_vector_width<int_>() const
{
    return get_info<uint_>(CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT);
}

/// \internal_
template<>
inline uint_ device::preferred_vector_width<long_>() const
{
    return get_info<uint_>(CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG);
}

/// \internal_
template<>
inline uint_ device::preferred_vector_width<float_>() const
{
    return get_info<uint_>(CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT);
}

/// \internal_
template<>
inline uint_ device::preferred_vector_width<double_>() const
{
    return get_info<uint_>(CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE);
}

/// \internal_ define get_info() specializations for device
BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS(device,
    ((cl_uint, CL_DEVICE_ADDRESS_BITS))
    ((bool, CL_DEVICE_AVAILABLE))
    ((bool, CL_DEVICE_COMPILER_AVAILABLE))
    ((bool, CL_DEVICE_ENDIAN_LITTLE))
    ((bool, CL_DEVICE_ERROR_CORRECTION_SUPPORT))
    ((cl_device_exec_capabilities, CL_DEVICE_EXECUTION_CAPABILITIES))
    ((std::string, CL_DEVICE_EXTENSIONS))
    ((cl_ulong, CL_DEVICE_GLOBAL_MEM_CACHE_SIZE))
    ((cl_device_mem_cache_type, CL_DEVICE_GLOBAL_MEM_CACHE_TYPE))
    ((cl_uint, CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE))
    ((cl_ulong, CL_DEVICE_GLOBAL_MEM_SIZE))
    ((bool, CL_DEVICE_IMAGE_SUPPORT))
    ((size_t, CL_DEVICE_IMAGE2D_MAX_HEIGHT))
    ((size_t, CL_DEVICE_IMAGE2D_MAX_WIDTH))
    ((size_t, CL_DEVICE_IMAGE3D_MAX_DEPTH))
    ((size_t, CL_DEVICE_IMAGE3D_MAX_HEIGHT))
    ((size_t, CL_DEVICE_IMAGE3D_MAX_WIDTH))
    ((cl_ulong, CL_DEVICE_LOCAL_MEM_SIZE))
    ((cl_device_local_mem_type, CL_DEVICE_LOCAL_MEM_TYPE))
    ((cl_uint, CL_DEVICE_MAX_CLOCK_FREQUENCY))
    ((cl_uint, CL_DEVICE_MAX_COMPUTE_UNITS))
    ((cl_uint, CL_DEVICE_MAX_CONSTANT_ARGS))
    ((cl_ulong, CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE))
    ((cl_ulong, CL_DEVICE_MAX_MEM_ALLOC_SIZE))
    ((size_t, CL_DEVICE_MAX_PARAMETER_SIZE))
    ((cl_uint, CL_DEVICE_MAX_READ_IMAGE_ARGS))
    ((cl_uint, CL_DEVICE_MAX_SAMPLERS))
    ((size_t, CL_DEVICE_MAX_WORK_GROUP_SIZE))
    ((cl_uint, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS))
    ((std::vector<size_t>, CL_DEVICE_MAX_WORK_ITEM_SIZES))
    ((cl_uint, CL_DEVICE_MAX_WRITE_IMAGE_ARGS))
    ((cl_uint, CL_DEVICE_MEM_BASE_ADDR_ALIGN))
    ((cl_uint, CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE))
    ((std::string, CL_DEVICE_NAME))
    ((cl_platform_id, CL_DEVICE_PLATFORM))
    ((cl_uint, CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR))
    ((cl_uint, CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT))
    ((cl_uint, CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT))
    ((cl_uint, CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG))
    ((cl_uint, CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT))
    ((cl_uint, CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE))
    ((std::string, CL_DEVICE_PROFILE))
    ((size_t, CL_DEVICE_PROFILING_TIMER_RESOLUTION))
    ((cl_command_queue_properties, CL_DEVICE_QUEUE_PROPERTIES))
    ((cl_device_fp_config, CL_DEVICE_SINGLE_FP_CONFIG))
    ((cl_device_type, CL_DEVICE_TYPE))
    ((std::string, CL_DEVICE_VENDOR))
    ((cl_uint, CL_DEVICE_VENDOR_ID))
    ((std::string, CL_DEVICE_VERSION))
    ((std::string, CL_DRIVER_VERSION))
)

#ifdef CL_DEVICE_DOUBLE_FP_CONFIG
BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS(device,
    ((cl_device_fp_config, CL_DEVICE_DOUBLE_FP_CONFIG))
)
#endif

#ifdef CL_DEVICE_HALF_FP_CONFIG
BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS(device,
    ((cl_device_fp_config, CL_DEVICE_HALF_FP_CONFIG))
)
#endif

#ifdef BOOST_COMPUTE_CL_VERSION_1_1
BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS(device,
    ((bool, CL_DEVICE_HOST_UNIFIED_MEMORY))
    ((cl_uint, CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR))
    ((cl_uint, CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT))
    ((cl_uint, CL_DEVICE_NATIVE_VECTOR_WIDTH_INT))
    ((cl_uint, CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG))
    ((cl_uint, CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT))
    ((cl_uint, CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE))
    ((std::string, CL_DEVICE_OPENCL_C_VERSION))
)
#endif // BOOST_COMPUTE_CL_VERSION_1_1

#ifdef BOOST_COMPUTE_CL_VERSION_1_2
BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS(device,
    ((std::string, CL_DEVICE_BUILT_IN_KERNELS))
    ((bool, CL_DEVICE_LINKER_AVAILABLE))
    ((cl_device_id, CL_DEVICE_PARENT_DEVICE))
    ((cl_uint, CL_DEVICE_PARTITION_MAX_SUB_DEVICES))
    ((cl_device_partition_property, CL_DEVICE_PARTITION_PROPERTIES))
    ((cl_device_affinity_domain, CL_DEVICE_PARTITION_AFFINITY_DOMAIN))
    ((cl_device_partition_property, CL_DEVICE_PARTITION_TYPE))
    ((size_t, CL_DEVICE_PRINTF_BUFFER_SIZE))
    ((bool, CL_DEVICE_PREFERRED_INTEROP_USER_SYNC))
    ((cl_uint, CL_DEVICE_REFERENCE_COUNT))
)
#endif // BOOST_COMPUTE_CL_VERSION_1_2

#ifdef BOOST_COMPUTE_CL_VERSION_2_0
BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS(device,
    ((size_t, CL_DEVICE_GLOBAL_VARIABLE_PREFERRED_TOTAL_SIZE))
    ((size_t, CL_DEVICE_MAX_GLOBAL_VARIABLE_SIZE))
    ((cl_uint, CL_DEVICE_MAX_ON_DEVICE_EVENTS))
    ((cl_uint, CL_DEVICE_MAX_ON_DEVICE_QUEUES))
    ((cl_uint, CL_DEVICE_MAX_PIPE_ARGS))
    ((cl_uint, CL_DEVICE_MAX_READ_WRITE_IMAGE_ARGS))
    ((cl_uint, CL_DEVICE_PIPE_MAX_ACTIVE_RESERVATIONS))
    ((cl_uint, CL_DEVICE_PIPE_MAX_PACKET_SIZE))
    ((cl_uint, CL_DEVICE_PREFERRED_GLOBAL_ATOMIC_ALIGNMENT))
    ((cl_uint, CL_DEVICE_PREFERRED_LOCAL_ATOMIC_ALIGNMENT))
    ((cl_uint, CL_DEVICE_PREFERRED_PLATFORM_ATOMIC_ALIGNMENT))
    ((cl_uint, CL_DEVICE_QUEUE_ON_DEVICE_MAX_SIZE))
    ((cl_uint, CL_DEVICE_QUEUE_ON_DEVICE_PREFERRED_SIZE))
    ((cl_command_queue_properties, CL_DEVICE_QUEUE_ON_DEVICE_PROPERTIES))
    ((cl_device_svm_capabilities, CL_DEVICE_SVM_CAPABILITIES))
    ((cl_uint, CL_DEVICE_IMAGE_BASE_ADDRESS_ALIGNMENT))
    ((cl_uint, CL_DEVICE_IMAGE_PITCH_ALIGNMENT))
)
#endif // BOOST_COMPUTE_CL_VERSION_2_0

#ifdef BOOST_COMPUTE_CL_VERSION_2_1
BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS(device,
    ((std::string, CL_DEVICE_IL_VERSION))
    ((cl_uint, CL_DEVICE_MAX_NUM_SUB_GROUPS))
    ((bool, CL_DEVICE_SUB_GROUP_INDEPENDENT_FORWARD_PROGRESS))
)
#endif // BOOST_COMPUTE_CL_VERSION_2_1

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DEVICE_HPP

/* device.hpp
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
*/