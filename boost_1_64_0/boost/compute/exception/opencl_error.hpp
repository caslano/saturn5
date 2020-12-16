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
X1pMfVZyDz7hG4uwY+znn+gLzyO6dmEXtKeO7Br3wHaoYw3/NocOmZvJ82p0/Hfk870jiHfBiDH6Kbf3/vTNQ5YzhiODR7GuAX+Bd3eYmOFTuf88fNd1tBe9WaDuxX/gU1fSlgX0gzh54Y2szc+iq+uOoS+wiQL3su7e+2n8DvWZJ07ufTpl8kyo/m/a9CfyGiP+eDn13coa0FrmQMxTGCM4v4LY+jX0CzY9dzF9yr6feca8AvHhzFr067WH0w78L9fm/obPYV9DDV9aeCRjAvuja+ALP8GOfkx/vxy7+QbxwzPR9Z/SDq51YQeFG9CrIvZzO7ZHPFp/Kv6mn7asxv++mjHhPYyVv8a/4PcNMllYQP9+jN68gzHqFHTuFdjhYejZv/AtE/TZRur57kPx19gwc9WOo/A7r7sLvhn9Zw2hju9I3oTOoW8JsugaxgYeRH6HH8a8nzn5jqbcaTO+tutllMG99UHGCmKDLvx/7ST0azU6+Eragb+pEbeZW5gPU48aY0rXT8gDn7aw8zDqxbhBjFO4kjoxRy68nnt+DLadsfTvjEvohXksvnw9/fIc9AEZ1D9EvThDttFFf/egp5x5USD2qdOO2W7mCTcxZn0BuX2Vf4+h7+exw3czz/nSkZzRRt8a2j3LeDCPPrPO9uPXE5+uPoRy0/U2w9phB3GymcUeqEcX6/Fdh9L2fbSbOGzuCejbN+mHK8kDnrmGud33l6Db9Nll2MmLiZ/wR7XPH8WYwTpu3zGMmfTzX5DBWcjgQvobX5aQzvIveSsyoF+K1Kmf/u+nnTMv5T7W/2voQtdDsF9kUMOXJzsZO3fTVmLkeeKA+kZkV8K3XUUdv3IUPGz3Mdz3KXSC9/x/TazXxXyuSPzcIMYx70Wm9EP/89DjBnIeZb2PtaYZ9oqaEXTkLegL8W1tahFjM7qPnzfPRu7T2M0fkP2LsU1sqPiuuxIT4TvqlIU/nUcnao89lLES23wPa0GMX2Y1+f4MO/0qdv8S+v2qo/CxjLOMYfMnHoW+09/MswpXcx27q7+EOS/rPeaVxBnYRf2H9DFjYP1C5kF8N29dzB6SYxhHGOuX0cf/oI1nUu934XPvUuBvfAvt7Doefd+O/3skeZ+OPRBrd+GTaswTe4vImvl5gzY34MzzvfYWyj2dvy8nXsDeGq9FnrjzQ8y//23u/Nz5ufNz5+fOz52fOz93fu783Pn5P3zOec4hnFtMqMtrFswciDU1/Tefey4/+XcvY+/CG08njF5juE7KGUSk5gPMhUnN6cTDpOab31tOytLkcnDSe1j+4y6CR/rq1fBIr7jHUlIe398KTnrkx8BJt6znPkO6HZz0PY+CT/pX/mvl86plpOT7Br6T3vYHWw/OZCQ1d3zZkJLvN7ifdOcj70pKfW4lf9Jrbzek5Pc67iNd/jV4pBsKfDfUj+copOayeb4bUvbXkJoTT+W7gddrbDv5TnpNA77h+1pSQ/32wzfUewYe6S7k0cLvCk7a08t9pF94v23/UdSLdNU5ls9/Lfk8gPtIy8eAG74/fRkp5b1tCSnbBx7F/aRfvt7KrwpO+oybuE46+lu+G/LlHNFWed1cJ51ev5iUcllrb8nhTaSk4z8jX9KB18In/cnDDiFFXr/hukGu96UepJ88ewUpcrvBln8DPIN830s9SK+7cjEp3x+wjBT+B+CRvvM14KRrf2H7x9yFlHpdu4yU+i6jnwzt/A3fDfl0kq9B7mdZfbjV1udv5Ge4zjuRrfqeS30N/N8ZUr4/lHqSHlYxpJR7mu3XpStJ0Yd7Uj/S1x21hJTvDwY31KtCPob7WK9p6dXvuE764q/AJ734I7b9d6fepEvub9s=
*/