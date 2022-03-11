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