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
/v2/1j8ZfT/1z7+5f3z/o/3D5GH+Rnv5S//HelR+IPL3Su9ROn/ckKcbrq8nyM+HtTdSeoaIXpSimJ4Puq+o3lzQg0R0Bnx6iOgZSB8uoqeCHi2iJ4KeKKJHgx4voocqofOXJIiee3/I2/sbaPpUUXpflJOspBxllyRFsbzzNiim5+9QTM9VQs8AvaimkJ6qhJ4IeqmIHg26Zi0hPVQJXTuR0g1FdPMCxfRstFdfRHdBehMR3Rf1monobqBri+jpKN9cRJcgfb6ovWagF4rohqBLROXogV4uSq8Jup4ofTnf7yI6f7mJ9E7Z9Wl80+uPjm/fv3h8u30a3+T6NL6FV+in8f23jO/ov3h8FykZl5/GN73+fx3fiWqO71D4tcrhz/JHvNQL50KBYd4UQ30omk3Gc3ucSzCAH60AcbNJ9H7aIZzjA2YDw3Cff76Xlo1y8TzKGvw4wL+XPJ/aG7wfq/yG6JzFQvhhwuFvEfl3jODXDk+mmAR+Q57Q/N5zaD5/HlGfK/xQ6cj3EH7CyNn0flAo7DTI7fpTWl7+TZyTAWq8p8ggXSLOBeTBP2oOuZWhvfngLxbpssC/IdKnQz56SFeCuD74LIWf0hTPg1Jwvwjle6Bd3qg3HeXnIV6AerRQvhn8sNeBuqjHHOlC8RwoHfdzgZpI9xbtfojydMFPIpAB3Qj5ysB3GfyBrYBZuG+I+5p8u3A/B/ybgi83
*/