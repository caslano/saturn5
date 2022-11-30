//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_USER_EVENT_HPP
#define BOOST_COMPUTE_USER_EVENT_HPP

#include <boost/compute/event.hpp>
#include <boost/compute/context.hpp>

namespace boost {
namespace compute {

#if defined(BOOST_COMPUTE_CL_VERSION_1_1) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
/// \class user_event
/// \brief An user-created event.
///
/// \opencl_version_warning{1,1}
///
/// \see event
class user_event : public event
{
public:
    /// Creates a new user-event object.
    ///
    /// \see_opencl_ref{clCreateUserEvent}
    explicit user_event(const context &context)
    {
        cl_int error;
        m_event = clCreateUserEvent(context.get(), &error);
        if(!m_event){
            BOOST_THROW_EXCEPTION(opencl_error(error));
        }
    }

    /// Creates a new user-event from \p other.
    user_event(const user_event &other)
        : event(other)
    {
    }

    /// Copies the user-event from \p other to \c *this.
    user_event& operator=(const user_event &other)
    {
        event::operator=(other);

        return *this;
    }

    #ifndef BOOST_COMPUTE_NO_RVALUE_REFERENCES
    /// Move-constructs a new user event object from \p other.
    user_event(user_event&& other) BOOST_NOEXCEPT
        : event(std::move(other))
    {
    }

    /// Move-assigns the user event from \p other to \c *this.
    user_event& operator=(user_event&& other) BOOST_NOEXCEPT
    {
        event::operator=(std::move(other));

        return *this;
    }
    #endif // BOOST_COMPUTE_NO_RVALUE_REFERENCES

    /// Sets the execution status for the user-event.
    ///
    /// \see_opencl_ref{clSetUserEventStatus}
    void set_status(cl_int execution_status)
    {
        cl_int ret = clSetUserEventStatus(m_event, execution_status);
        if(ret != CL_SUCCESS){
            BOOST_THROW_EXCEPTION(opencl_error(ret));
        }
    }
};
#endif // BOOST_COMPUTE_CL_VERSION_1_1

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_EVENT_HPP

/* user_event.hpp
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
*/