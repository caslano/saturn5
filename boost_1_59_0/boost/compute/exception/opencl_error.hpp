//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_EXCEPTION_OPENCL_ERROR_HPP
#define BOOST_COMPUTE_EXCEPTION_OPENCL_ERROR_HPP

#include <exception>
#include <string>
#include <sstream>

#include <boost/compute/cl.hpp>

namespace boost {
namespace compute {

/// \class opencl_error
/// \brief A run-time OpenCL error.
///
/// The opencl_error class represents an error returned from an OpenCL
/// function.
///
/// \see context_error
class opencl_error : public std::exception
{
public:
    /// Creates a new opencl_error exception object for \p error.
    explicit opencl_error(cl_int error) throw()
        : m_error(error),
          m_error_string(to_string(error))
    {
    }

    /// Destroys the opencl_error object.
    ~opencl_error() throw()
    {
    }

    /// Returns the numeric error code.
    cl_int error_code() const throw()
    {
        return m_error;
    }

    /// Returns a string description of the error.
    std::string error_string() const throw()
    {
        return m_error_string;
    }

    /// Returns a C-string description of the error.
    const char* what() const throw()
    {
        return m_error_string.c_str();
    }

    /// Static function which converts the numeric OpenCL error code \p error
    /// to a human-readable string.
    ///
    /// For example:
    /// \code
    /// std::cout << opencl_error::to_string(CL_INVALID_KERNEL_ARGS) << std::endl;
    /// \endcode
    ///
    /// Will print "Invalid Kernel Arguments".
    ///
    /// If the error code is unknown (e.g. not a valid OpenCL error), a string
    /// containing "Unknown OpenCL Error" along with the error number will be
    /// returned.
    static std::string to_string(cl_int error)
    {
        switch(error){
        case CL_SUCCESS: return "Success";
        case CL_DEVICE_NOT_FOUND: return "Device Not Found";
        case CL_DEVICE_NOT_AVAILABLE: return "Device Not Available";
        case CL_COMPILER_NOT_AVAILABLE: return "Compiler Not Available";
        case CL_MEM_OBJECT_ALLOCATION_FAILURE: return "Memory Object Allocation Failure";
        case CL_OUT_OF_RESOURCES: return "Out of Resources";
        case CL_OUT_OF_HOST_MEMORY: return "Out of Host Memory";
        case CL_PROFILING_INFO_NOT_AVAILABLE: return "Profiling Information Not Available";
        case CL_MEM_COPY_OVERLAP: return "Memory Copy Overlap";
        case CL_IMAGE_FORMAT_MISMATCH: return "Image Format Mismatch";
        case CL_IMAGE_FORMAT_NOT_SUPPORTED: return "Image Format Not Supported";
        case CL_BUILD_PROGRAM_FAILURE: return "Build Program Failure";
        case CL_MAP_FAILURE: return "Map Failure";
        case CL_INVALID_VALUE: return "Invalid Value";
        case CL_INVALID_DEVICE_TYPE: return "Invalid Device Type";
        case CL_INVALID_PLATFORM: return "Invalid Platform";
        case CL_INVALID_DEVICE: return "Invalid Device";
        case CL_INVALID_CONTEXT: return "Invalid Context";
        case CL_INVALID_QUEUE_PROPERTIES: return "Invalid Queue Properties";
        case CL_INVALID_COMMAND_QUEUE: return "Invalid Command Queue";
        case CL_INVALID_HOST_PTR: return "Invalid Host Pointer";
        case CL_INVALID_MEM_OBJECT: return "Invalid Memory Object";
        case CL_INVALID_IMAGE_FORMAT_DESCRIPTOR: return "Invalid Image Format Descriptor";
        case CL_INVALID_IMAGE_SIZE: return "Invalid Image Size";
        case CL_INVALID_SAMPLER: return "Invalid Sampler";
        case CL_INVALID_BINARY: return "Invalid Binary";
        case CL_INVALID_BUILD_OPTIONS: return "Invalid Build Options";
        case CL_INVALID_PROGRAM: return "Invalid Program";
        case CL_INVALID_PROGRAM_EXECUTABLE: return "Invalid Program Executable";
        case CL_INVALID_KERNEL_NAME: return "Invalid Kernel Name";
        case CL_INVALID_KERNEL_DEFINITION: return "Invalid Kernel Definition";
        case CL_INVALID_KERNEL: return "Invalid Kernel";
        case CL_INVALID_ARG_INDEX: return "Invalid Argument Index";
        case CL_INVALID_ARG_VALUE: return "Invalid Argument Value";
        case CL_INVALID_ARG_SIZE: return "Invalid Argument Size";
        case CL_INVALID_KERNEL_ARGS: return "Invalid Kernel Arguments";
        case CL_INVALID_WORK_DIMENSION: return "Invalid Work Dimension";
        case CL_INVALID_WORK_GROUP_SIZE: return "Invalid Work Group Size";
        case CL_INVALID_WORK_ITEM_SIZE: return "Invalid Work Item Size";
        case CL_INVALID_GLOBAL_OFFSET: return "Invalid Global Offset";
        case CL_INVALID_EVENT_WAIT_LIST: return "Invalid Event Wait List";
        case CL_INVALID_EVENT: return "Invalid Event";
        case CL_INVALID_OPERATION: return "Invalid Operation";
        case CL_INVALID_GL_OBJECT: return "Invalid GL Object";
        case CL_INVALID_BUFFER_SIZE: return "Invalid Buffer Size";
        case CL_INVALID_MIP_LEVEL: return "Invalid MIP Level";
        case CL_INVALID_GLOBAL_WORK_SIZE: return "Invalid Global Work Size";
        #ifdef BOOST_COMPUTE_CL_VERSION_1_2
        case CL_COMPILE_PROGRAM_FAILURE: return "Compile Program Failure";
        case CL_LINKER_NOT_AVAILABLE: return "Linker Not Available";
        case CL_LINK_PROGRAM_FAILURE: return "Link Program Failure";
        case CL_DEVICE_PARTITION_FAILED: return "Device Partition Failed";
        case CL_KERNEL_ARG_INFO_NOT_AVAILABLE: return "Kernel Argument Info Not Available";
        case CL_INVALID_PROPERTY: return "Invalid Property";
        case CL_INVALID_IMAGE_DESCRIPTOR: return "Invalid Image Descriptor";
        case CL_INVALID_COMPILER_OPTIONS: return "Invalid Compiler Options";
        case CL_INVALID_LINKER_OPTIONS: return "Invalid Linker Options";
        case CL_INVALID_DEVICE_PARTITION_COUNT: return "Invalid Device Partition Count";
        #endif // BOOST_COMPUTE_CL_VERSION_1_2
        #ifdef BOOST_COMPUTE_CL_VERSION_2_0
        case CL_INVALID_PIPE_SIZE: return "Invalid Pipe Size";
        case CL_INVALID_DEVICE_QUEUE: return "Invalid Device Queue";
        #endif
        default: {
            std::stringstream s;
            s << "Unknown OpenCL Error (" << error << ")";
            return s.str();
        }
        }
    }

private:
    cl_int m_error;
    std::string m_error_string;
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_EXCEPTION_OPENCL_ERROR_HPP

/* opencl_error.hpp
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
*/