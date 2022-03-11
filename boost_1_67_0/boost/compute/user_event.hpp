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