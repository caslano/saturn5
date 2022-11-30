//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_EXCEPTION_UNSUPPORTED_EXTENSION_ERROR_HPP
#define BOOST_COMPUTE_EXCEPTION_UNSUPPORTED_EXTENSION_ERROR_HPP

#include <exception>
#include <sstream>
#include <string>

namespace boost {
namespace compute {

/// \class unsupported_extension_error
/// \brief Exception thrown when attempting to use an unsupported
///        OpenCL extension.
///
/// This exception is thrown when the user attempts to use an OpenCL
/// extension which is not supported on the platform and/or device.
///
/// An example of this is attempting to use CL-GL sharing on a non-GPU
/// device.
///
/// \see opencl_error
class unsupported_extension_error : public std::exception
{
public:
    /// Creates a new unsupported extension error exception object indicating
    /// that \p extension is not supported by the OpenCL platform or device.
    explicit unsupported_extension_error(const char *extension) throw()
        : m_extension(extension)
    {
        std::stringstream msg;
        msg << "OpenCL extension " << extension << " not supported";
        m_error_string = msg.str();
    }

    /// Destroys the unsupported extension error object.
    ~unsupported_extension_error() throw()
    {
    }

    /// Returns the name of the unsupported extension.
    std::string extension_name() const throw()
    {
        return m_extension;
    }

    /// Returns a string containing a human-readable error message containing
    /// the name of the unsupported exception.
    const char* what() const throw()
    {
        return m_error_string.c_str();
    }

private:
    std::string m_extension;
    std::string m_error_string;
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_EXCEPTION_UNSUPPORTED_EXTENSION_ERROR_HPP

/* unsupported_extension_error.hpp
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
*/