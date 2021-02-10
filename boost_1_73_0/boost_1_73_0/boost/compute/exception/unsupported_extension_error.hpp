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
sEyhu5gXUZy/jxKd2CvXcMJCkp0CfiLUGx/KRaRMuiaolAElOnKDwE65O5EjE4rwkL5BUgGtiHIsC7lKfwyTlsDJY1glhkzolGacFHVMwrkILA28se8xx7AhCwvowSUO1yzWHk57ncFkNvb8Ye+TR5H025M4vILp2nbnaL/jb7zd3191MHDA6w/EiiCXt5ktOJd2QPjDmR6HPjb5et9EJLE+TybXaa4/Ljfqh3O0h4OB14b4G4h/YHcncyzSJAEFPjyif7A07dtYVV3KZ6877sx8b/zJG0PdUQ8GuTXOqGT2TRL7SXIRBnlQ7lHp56BzShpfqLCW9f6apC8JoVmgHJMrEL2T0Z4ZCYHnckkYf9O6OmudNjQce/3hxJu57bbn+7OON+h6HXF4Bx0/YybJiQHkFji3WBBdwXIJd8vA1WY1rBUSW0I8QFGocqz9nRO0QgYkRptnr5x/YEBkkmdZieNtCSOw2TzNmkakZZF+yIUan4DNhO6fWeRLAFgipEg1tzNmrfYI3GzxVUcBECmAa8MvIBNPKgo2Io2E5MdVSirNzJuTfjO0EQLzLI2tYBpL+Stag6xkOyrrnRi5MKvZ+TNKKe4SkEhhRUqzfBJN+lCCeUE8WqPolRyXfoHgxqxKYzqwy8nkJn7d9Y8o
*/