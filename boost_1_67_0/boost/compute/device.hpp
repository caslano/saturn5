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