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