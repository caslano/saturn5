//---------------------------------------------------------------------------//
// Copyright (c) 2013-2015 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_EXCEPTION_NO_DEVICE_FOUND_HPP
#define BOOST_COMPUTE_EXCEPTION_NO_DEVICE_FOUND_HPP

#include <exception>

namespace boost {
namespace compute {

/// \class no_device_found
/// \brief Exception thrown when no OpenCL device is found
///
/// This exception is thrown when no valid OpenCL device can be found.
///
/// \see opencl_error
class no_device_found : public std::exception
{
public:
    /// Creates a new no_device_found exception object.
    no_device_found() throw()
    {
    }

    /// Destroys the no_device_found exception object.
    ~no_device_found() throw()
    {
    }

    /// Returns a string containing a human-readable error message.
    const char* what() const throw()
    {
        return "No OpenCL device found";
    }
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_EXCEPTION_NO_DEVICE_FOUND_HPP

/* no_device_found.hpp
tPC6HEE0tNSPCTX2kQ8DwST4IOoWDzfYvpMioejpWAC6yAo6s1S7oU+U0O36jmJ4Lva183/hA8QDfyvJ4jos3iRa0a1rWr65CPlcO7QuniiH03WNCplujrNbzPoXX6lByI1N+H6tO0BRUOd1IRr/EQb5tBDPO8EQW978vGQaeUPh6CGCk7N4PXWQ78CLj5i37nlrJtPBeHTZn/7VLKgNijPJ8he5/A9QSwMECgAAAAgALWdKUuYenhB3GAAA8T8AACkACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvbGliY3VybC1lcnJvcnMuM1VUBQABtkgkYK1ba3PbOLL9zl+B9ZfYW478fk3t3b20RMe60WtEKRnfSpWKEiGLG4rUEmQcT82Pv6cbAB+SnMzW3Uxl7EhEo9HoPn26Aba+HIi//sf+OC0SJ376Z8Z/Z/iDn3bQKEv/KRf5/gGz2R9C/4eBX/DzT0x1IqpRf8yOxJ8a9Yc45FEzM9ff6PfZ7E9M94WUpP+d0OAvM/oVn+iRZnw73bxm0fMqF4ftI3F2d3cr3ovz0/PTY9EJkkjGws9lMpfZ87H4W8if/Pcq+P69peTfj4XMRRC3GgInq0gJlS7zlyCTAr/H0UImSoYiUCKUapFFc/wjSkS+kmIZ
*/