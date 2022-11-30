//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_EXCEPTION_CONTEXT_ERROR_HPP
#define BOOST_COMPUTE_EXCEPTION_CONTEXT_ERROR_HPP

#include <exception>

namespace boost {
namespace compute {

class context;

/// \class context_error
/// \brief A run-time OpenCL context error.
///
/// The context_error exception is thrown when the OpenCL context encounters
/// an error condition. Boost.Compute is notified of these error conditions by
/// registering an error handler when creating context objects (via the
/// \c pfn_notify argument to the \c clCreateContext() function).
///
/// This exception is different than the opencl_error exception which is thrown
/// as a result of error caused when calling a single OpenCL API function.
///
/// \see opencl_error
class context_error : public std::exception
{
public:
    /// Creates a new context error exception object.
    context_error(const context *context,
                  const char *errinfo,
                  const void *private_info,
                  size_t private_info_size) throw()
        : m_context(context),
          m_errinfo(errinfo),
          m_private_info(private_info),
          m_private_info_size(private_info_size)
    {
    }

    /// Destroys the context error object.
    ~context_error() throw()
    {
    }

    /// Returns a string with a description of the error.
    const char* what() const throw()
    {
        return m_errinfo;
    }

    /// Returns a pointer to the context object which generated the error
    /// notification.
    const context* get_context_ptr() const throw()
    {
        return m_context;
    }

    /// Returns a pointer to the private info memory block.
    const void* get_private_info_ptr() const throw()
    {
        return m_private_info;
    }

    /// Returns the size of the private info memory block.
    size_t get_private_info_size() const throw()
    {
        return m_private_info_size;
    }

private:
    const context *m_context;
    const char *m_errinfo;
    const void *m_private_info;
    size_t m_private_info_size;
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_EXCEPTION_CONTEXT_ERROR_HPP

/* context_error.hpp
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
*/