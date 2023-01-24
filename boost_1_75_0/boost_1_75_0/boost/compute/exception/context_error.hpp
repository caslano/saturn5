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
p3lJ87f4fr1p4sBfrdJvuEa1SKy35iuX/AZ1T2da7tE37bPvmV3fN5kbS6wfHbFe+kW9pRN+futu0dfw5L7CbLsTKW06LRiuv3LL54cbuUS9do5q+H6TYz9//Zt+xWuSW0y0OagZeC23q7tbj2RjoxPVr+jERjHZzt/uWdZTFJ+85WJ4/qO7jlFf3/r5UoM1D3Q77NIo7vlA8uXSnX1q2DgP/lnHa8nSXCuLxF7eE8etefn04u66cT6Rzy33Bf54z/Di2fHtPUcMPDD63pC9pmnfGegya14FTnMatGKU7YZindWZ+1zXGedE7795qMQ5yevc04OLez2e3jj9R2P9I+ZLjfcvXpYyboyjg+uIfk2v6eysz7hozB57gItHNmfjtWjc8sHr/iZH8nQWbWCSz7U88dMd59pJ8wc1slmnEXwofcfLOl9mrbrlm7TQevuutes++2H81dRJGiMutFnovH5zcoeFjxudnjp8T5tEzWs6Gb5se+eUV+fK73xM3+rY7cZXLwzePYDEm8viHSPMhwR9lW4ff2teszmn9i016d9o6cw68y0SRmvX8h/nd7qJ/cjz2tbnbI6c0r9Xs1vSNU+TdsFZ506Y7266beXEzDptzndOz2sbm6ez3JTlt81nl74rzul6aPIVnQMJNJ4lun9cFD8hip8R5b8nun9JFF+8uMGqKeV5Onv7sPGGnRtfFt3v1n9A1zlO13QS
*/