//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_KERNEL_HPP
#define BOOST_COMPUTE_KERNEL_HPP

#include <string>

#include <boost/assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/optional.hpp>

#include <boost/compute/cl_ext.hpp> // cl_khr_subgroups

#include <boost/compute/config.hpp>
#include <boost/compute/exception.hpp>
#include <boost/compute/program.hpp>
#include <boost/compute/platform.hpp>
#include <boost/compute/type_traits/is_fundamental.hpp>
#include <boost/compute/detail/diagnostic.hpp>
#include <boost/compute/detail/get_object_info.hpp>
#include <boost/compute/detail/assert_cl_success.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class T> struct set_kernel_arg;

} // end detail namespace

/// \class kernel
/// \brief A compute kernel.
///
/// \see command_queue, program
class kernel
{
public:
    /// Creates a null kernel object.
    kernel()
        : m_kernel(0)
    {
    }

    /// Creates a new kernel object for \p kernel. If \p retain is
    /// \c true, the reference count for \p kernel will be incremented.
    explicit kernel(cl_kernel kernel, bool retain = true)
        : m_kernel(kernel)
    {
        if(m_kernel && retain){
            clRetainKernel(m_kernel);
        }
    }

    /// Creates a new kernel object with \p name from \p program.
    kernel(const program &program, const std::string &name)
    {
        cl_int error = 0;
        m_kernel = clCreateKernel(program.get(), name.c_str(), &error);

        if(!m_kernel){
            BOOST_THROW_EXCEPTION(opencl_error(error));
        }
    }

    /// Creates a new kernel object as a copy of \p other.
    kernel(const kernel &other)
        : m_kernel(other.m_kernel)
    {
        if(m_kernel){
            clRetainKernel(m_kernel);
        }
    }

    /// Copies the kernel object from \p other to \c *this.
    kernel& operator=(const kernel &other)
    {
        if(this != &other){
            if(m_kernel){
                clReleaseKernel(m_kernel);
            }

            m_kernel = other.m_kernel;

            if(m_kernel){
                clRetainKernel(m_kernel);
            }
        }

        return *this;
    }

    #ifndef BOOST_COMPUTE_NO_RVALUE_REFERENCES
    /// Move-constructs a new kernel object from \p other.
    kernel(kernel&& other) BOOST_NOEXCEPT
        : m_kernel(other.m_kernel)
    {
        other.m_kernel = 0;
    }

    /// Move-assigns the kernel from \p other to \c *this.
    kernel& operator=(kernel&& other) BOOST_NOEXCEPT
    {
        if(m_kernel){
            clReleaseKernel(m_kernel);
        }

        m_kernel = other.m_kernel;
        other.m_kernel = 0;

        return *this;
    }
    #endif // BOOST_COMPUTE_NO_RVALUE_REFERENCES

    /// Destroys the kernel object.
    ~kernel()
    {
        if(m_kernel){
            BOOST_COMPUTE_ASSERT_CL_SUCCESS(
                clReleaseKernel(m_kernel)
            );
        }
    }

    #if defined(BOOST_COMPUTE_CL_VERSION_2_1) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Creates a new kernel object based on a shallow copy of
    /// the undelying OpenCL kernel object.
    ///
    /// \opencl_version_warning{2,1}
    ///
    /// \see_opencl21_ref{clCloneKernel}
    kernel clone()
    {
        cl_int ret = 0;
        cl_kernel k = clCloneKernel(m_kernel, &ret);
        return kernel(k, false);
    }
    #endif // BOOST_COMPUTE_CL_VERSION_2_1

    /// Returns a reference to the underlying OpenCL kernel object.
    cl_kernel& get() const
    {
        return const_cast<cl_kernel &>(m_kernel);
    }

    /// Returns the function name for the kernel.
    std::string name() const
    {
        return get_info<std::string>(CL_KERNEL_FUNCTION_NAME);
    }

    /// Returns the number of arguments for the kernel.
    size_t arity() const
    {
        return get_info<cl_uint>(CL_KERNEL_NUM_ARGS);
    }

    /// Returns the program for the kernel.
    program get_program() const
    {
        return program(get_info<cl_program>(CL_KERNEL_PROGRAM));
    }

    /// Returns the context for the kernel.
    context get_context() const
    {
        return context(get_info<cl_context>(CL_KERNEL_CONTEXT));
    }

    /// Returns information about the kernel.
    ///
    /// \see_opencl_ref{clGetKernelInfo}
    template<class T>
    T get_info(cl_kernel_info info) const
    {
        return detail::get_object_info<T>(clGetKernelInfo, m_kernel, info);
    }

    /// \overload
    template<int Enum>
    typename detail::get_object_info_type<kernel, Enum>::type
    get_info() const;

    #if defined(BOOST_COMPUTE_CL_VERSION_1_2) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Returns information about the argument at \p index.
    ///
    /// For example, to get the name of the first argument:
    /// \code
    /// std::string arg = kernel.get_arg_info<std::string>(0, CL_KERNEL_ARG_NAME);
    /// \endcode
    ///
    /// Note, this function requires that the program be compiled with the
    /// \c "-cl-kernel-arg-info" flag. For example:
    /// \code
    /// program.build("-cl-kernel-arg-info");
    /// \endcode
    ///
    /// \opencl_version_warning{1,2}
    ///
    /// \see_opencl_ref{clGetKernelArgInfo}
    template<class T>
    T get_arg_info(size_t index, cl_kernel_arg_info info) const
    {
        return detail::get_object_info<T>(
            clGetKernelArgInfo, m_kernel, info, static_cast<cl_uint>(index)
        );
    }

    /// \overload
    template<int Enum>
    typename detail::get_object_info_type<kernel, Enum>::type
    get_arg_info(size_t index) const;
    #endif // BOOST_COMPUTE_CL_VERSION_1_2

    /// Returns work-group information for the kernel with \p device.
    ///
    /// \see_opencl_ref{clGetKernelWorkGroupInfo}
    template<class T>
    T get_work_group_info(const device &device, cl_kernel_work_group_info info) const
    {
        return detail::get_object_info<T>(clGetKernelWorkGroupInfo, m_kernel, info, device.id());
    }

    #if defined(BOOST_COMPUTE_CL_VERSION_2_1) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Returns sub-group information for the kernel with \p device. Returns a null
    /// optional if \p device is not 2.1 device, or is not 2.0 device with support
    /// for cl_khr_subgroups extension.
    ///
    /// \opencl_version_warning{2,1}
    /// \see_opencl21_ref{clGetKernelSubGroupInfo}
    /// \see_opencl2_ref{clGetKernelSubGroupInfoKHR}
    template<class T>
    boost::optional<T> get_sub_group_info(const device &device, cl_kernel_sub_group_info info,
                                          const size_t input_size, const void * input) const
    {
        if(device.check_version(2, 1))
        {
            return detail::get_object_info<T>(
                clGetKernelSubGroupInfo, m_kernel, info, device.id(), input_size, input
            );
        }
        else if(!device.check_version(2, 0) || !device.supports_extension("cl_khr_subgroups"))
        {
            return boost::optional<T>();
        }
        // Only CL_KERNEL_MAX_SUB_GROUP_SIZE_FOR_NDRANGE and CL_KERNEL_SUB_GROUP_COUNT_FOR_NDRANGE
        // are supported in cl_khr_subgroups extension for 2.0 devices.
        else if(info != CL_KERNEL_MAX_SUB_GROUP_SIZE_FOR_NDRANGE && info != CL_KERNEL_SUB_GROUP_COUNT_FOR_NDRANGE)
        {
            return boost::optional<T>();
        }

        BOOST_COMPUTE_DISABLE_DEPRECATED_DECLARATIONS();
        clGetKernelSubGroupInfoKHR_fn clGetKernelSubGroupInfoKHR_fptr =
            reinterpret_cast<clGetKernelSubGroupInfoKHR_fn>(
                reinterpret_cast<size_t>(
                    device.platform().get_extension_function_address("clGetKernelSubGroupInfoKHR")
                )
            );
        BOOST_COMPUTE_ENABLE_DEPRECATED_DECLARATIONS();

        return detail::get_object_info<T>(
            clGetKernelSubGroupInfoKHR_fptr, m_kernel, info, device.id(), input_size, input
        );
    }

    /// \overload
    template<class T>
    boost::optional<T> get_sub_group_info(const device &device, cl_kernel_sub_group_info info) const
    {
        return get_sub_group_info<T>(device, info, 0, 0);
    }

    /// \overload
    template<class T>
    boost::optional<T> get_sub_group_info(const device &device, cl_kernel_sub_group_info info,
                                          const size_t input) const
    {
        return get_sub_group_info<T>(device, info, sizeof(size_t), &input);
    }
    #endif // BOOST_COMPUTE_CL_VERSION_2_1

    #if defined(BOOST_COMPUTE_CL_VERSION_2_0) && !defined(BOOST_COMPUTE_CL_VERSION_2_1)
    /// Returns sub-group information for the kernel with \p device. Returns a null
    /// optional if cl_khr_subgroups extension is not supported by \p device.
    ///
    /// \opencl_version_warning{2,0}
    /// \see_opencl2_ref{clGetKernelSubGroupInfoKHR}
    template<class T>
    boost::optional<T> get_sub_group_info(const device &device, cl_kernel_sub_group_info info,
                                          const size_t input_size, const void * input) const
    {
        if(!device.check_version(2, 0) || !device.supports_extension("cl_khr_subgroups"))
        {
            return boost::optional<T>();
        }

        BOOST_COMPUTE_DISABLE_DEPRECATED_DECLARATIONS();
        clGetKernelSubGroupInfoKHR_fn clGetKernelSubGroupInfoKHR_fptr =
            reinterpret_cast<clGetKernelSubGroupInfoKHR_fn>(
                reinterpret_cast<size_t>(
                    device.platform().get_extension_function_address("clGetKernelSubGroupInfoKHR")
                )
            );
        BOOST_COMPUTE_ENABLE_DEPRECATED_DECLARATIONS();

        return detail::get_object_info<T>(
            clGetKernelSubGroupInfoKHR_fptr, m_kernel, info, device.id(), input_size, input
        );
    }
    #endif // defined(BOOST_COMPUTE_CL_VERSION_2_0) && !defined(BOOST_COMPUTE_CL_VERSION_2_1)

    #if defined(BOOST_COMPUTE_CL_VERSION_2_0) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// \overload
    template<class T>
    boost::optional<T> get_sub_group_info(const device &device, cl_kernel_sub_group_info info,
                                          const std::vector<size_t> input) const
    {
        BOOST_ASSERT(input.size() > 0);
        return get_sub_group_info<T>(device, info, input.size() * sizeof(size_t), &input[0]);
    }
    #endif // BOOST_COMPUTE_CL_VERSION_2_0

    /// Sets the argument at \p index to \p value with \p size.
    ///
    /// \see_opencl_ref{clSetKernelArg}
    void set_arg(size_t index, size_t size, const void *value)
    {
        BOOST_ASSERT(index < arity());

        cl_int ret = clSetKernelArg(m_kernel,
                                    static_cast<cl_uint>(index),
                                    size,
                                    value);
        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }
    }

    /// Sets the argument at \p index to \p value.
    ///
    /// For built-in types (e.g. \c float, \c int4_), this is equivalent to
    /// calling set_arg(index, sizeof(type), &value).
    ///
    /// Additionally, this method is specialized for device memory objects
    /// such as buffer and image2d. This allows for them to be passed directly
    /// without having to extract their underlying cl_mem object.
    ///
    /// This method is also specialized for device container types such as
    /// vector<T> and array<T, N>. This allows for them to be passed directly
    /// as kernel arguments without having to extract their underlying buffer.
    ///
    /// For setting local memory arguments (e.g. "__local float *buf"), the
    /// local_buffer<T> class may be used:
    /// \code
    /// // set argument to a local buffer with storage for 32 float's
    /// kernel.set_arg(0, local_buffer<float>(32));
    /// \endcode
    template<class T>
    void set_arg(size_t index, const T &value)
    {
        // if you get a compilation error pointing here it means you
        // attempted to set a kernel argument from an invalid type.
        detail::set_kernel_arg<T>()(*this, index, value);
    }

    /// \internal_
    void set_arg(size_t index, const cl_mem mem)
    {
        set_arg(index, sizeof(cl_mem), static_cast<const void *>(&mem));
    }

    /// \internal_
    void set_arg(size_t index, const cl_sampler sampler)
    {
        set_arg(index, sizeof(cl_sampler), static_cast<const void *>(&sampler));
    }

    /// \internal_
    void set_arg_svm_ptr(size_t index, void* ptr)
    {
        #ifdef BOOST_COMPUTE_CL_VERSION_2_0
        cl_int ret = clSetKernelArgSVMPointer(m_kernel, static_cast<cl_uint>(index), ptr);
        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }
        #else
        (void) index;
        (void) ptr;
        BOOST_THROW_EXCEPTION(opencl_error(CL_INVALID_ARG_VALUE));
        #endif
    }

    #ifndef BOOST_COMPUTE_NO_VARIADIC_TEMPLATES
    /// Sets the arguments for the kernel to \p args.
    template<class... T>
    void set_args(T&&... args)
    {
        BOOST_ASSERT(sizeof...(T) <= arity());

        _set_args<0>(args...);
    }
    #endif // BOOST_COMPUTE_NO_VARIADIC_TEMPLATES

    #if defined(BOOST_COMPUTE_CL_VERSION_2_0) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Sets additional execution information for the kernel.
    ///
    /// \opencl_version_warning{2,0}
    ///
    /// \see_opencl2_ref{clSetKernelExecInfo}
    void set_exec_info(cl_kernel_exec_info info, size_t size, const void *value)
    {
        cl_int ret = clSetKernelExecInfo(m_kernel, info, size, value);
        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }
    }
    #endif // BOOST_COMPUTE_CL_VERSION_2_0

    /// Returns \c true if the kernel is the same at \p other.
    bool operator==(const kernel &other) const
    {
        return m_kernel == other.m_kernel;
    }

    /// Returns \c true if the kernel is different from \p other.
    bool operator!=(const kernel &other) const
    {
        return m_kernel != other.m_kernel;
    }

    /// \internal_
    operator cl_kernel() const
    {
        return m_kernel;
    }

    /// \internal_
    static kernel create_with_source(const std::string &source,
                                     const std::string &name,
                                     const context &context)
    {
        return program::build_with_source(source, context).create_kernel(name);
    }

private:
    #ifndef BOOST_COMPUTE_NO_VARIADIC_TEMPLATES
    /// \internal_
    template<size_t N>
    void _set_args()
    {
    }

    /// \internal_
    template<size_t N, class T, class... Args>
    void _set_args(T&& arg, Args&&... rest)
    {
        set_arg(N, arg);
        _set_args<N+1>(rest...);
    }
    #endif // BOOST_COMPUTE_NO_VARIADIC_TEMPLATES

private:
    cl_kernel m_kernel;
};

inline kernel program::create_kernel(const std::string &name) const
{
    return kernel(*this, name);
}

/// \internal_ define get_info() specializations for kernel
BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS(kernel,
    ((std::string, CL_KERNEL_FUNCTION_NAME))
    ((cl_uint, CL_KERNEL_NUM_ARGS))
    ((cl_uint, CL_KERNEL_REFERENCE_COUNT))
    ((cl_context, CL_KERNEL_CONTEXT))
    ((cl_program, CL_KERNEL_PROGRAM))
)

#ifdef BOOST_COMPUTE_CL_VERSION_1_2
BOOST_COMPUTE_DETAIL_DEFINE_GET_INFO_SPECIALIZATIONS(kernel,
    ((std::string, CL_KERNEL_ATTRIBUTES))
)
#endif // BOOST_COMPUTE_CL_VERSION_1_2

/// \internal_ define get_arg_info() specializations for kernel
#ifdef BOOST_COMPUTE_CL_VERSION_1_2
#define BOOST_COMPUTE_DETAIL_DEFINE_KERNEL_GET_ARG_INFO_SPECIALIZATION(result_type, value) \
    namespace detail { \
        template<> struct get_object_info_type<kernel, value> { typedef result_type type; }; \
    } \
    template<> inline result_type kernel::get_arg_info<value>(size_t index) const { \
        return get_arg_info<result_type>(index, value); \
    }

BOOST_COMPUTE_DETAIL_DEFINE_KERNEL_GET_ARG_INFO_SPECIALIZATION(cl_kernel_arg_address_qualifier, CL_KERNEL_ARG_ADDRESS_QUALIFIER)
BOOST_COMPUTE_DETAIL_DEFINE_KERNEL_GET_ARG_INFO_SPECIALIZATION(cl_kernel_arg_access_qualifier, CL_KERNEL_ARG_ACCESS_QUALIFIER)
BOOST_COMPUTE_DETAIL_DEFINE_KERNEL_GET_ARG_INFO_SPECIALIZATION(std::string, CL_KERNEL_ARG_TYPE_NAME)
BOOST_COMPUTE_DETAIL_DEFINE_KERNEL_GET_ARG_INFO_SPECIALIZATION(cl_kernel_arg_type_qualifier, CL_KERNEL_ARG_TYPE_QUALIFIER)
BOOST_COMPUTE_DETAIL_DEFINE_KERNEL_GET_ARG_INFO_SPECIALIZATION(std::string, CL_KERNEL_ARG_NAME)
#endif // BOOST_COMPUTE_CL_VERSION_1_2

namespace detail {

// set_kernel_arg implementation for built-in types
template<class T>
struct set_kernel_arg
{
    typename boost::enable_if<is_fundamental<T> >::type
    operator()(kernel &kernel_, size_t index, const T &value)
    {
        kernel_.set_arg(index, sizeof(T), &value);
    }
};

// set_kernel_arg specialization for char (different from built-in cl_char)
template<>
struct set_kernel_arg<char>
{
    void operator()(kernel &kernel_, size_t index, const char c)
    {
        kernel_.set_arg(index, sizeof(char), &c);
    }
};

} // end detail namespace
} // end namespace compute
} // end namespace boost

#endif // BOOST_COMPUTE_KERNEL_HPP

/* kernel.hpp
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
*/