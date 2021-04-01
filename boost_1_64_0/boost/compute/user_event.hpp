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
E+yGx+5hiexZGWqN95ODUToIgvK+12XXQ/PAWatEOpbarOHhARxq6RxQ5qvl9eRbBeIrAYojNExYppyM2EjFU6vlZWv2gri7KE4Hcn/7ddWvLqNkluY8iviOJyU1ikG5Cm2ubTSXzpfRf3pMz73sPP4yv29mW8ofjgx3BW1+gnJSTdFxOD4N7vL/L4oZmEIQN0FIkQhBduubMaKaqqM0mMTNApGrWWrxFJ86EcN//RE0D2GrjYCTnltbrutZIg8bcB5N28J2yfZq0wM01AxqmwUDXqWTp2WbSnE/vSdV0U/CACoFPRYKOects05wrDxavckowLeqEf9Q0c/K1FBcvogptAuQ7wnLgicNkgI+eh/4yJe0JH7bLF1s3vHTbsx4h1M6uTUO3M1sFcpew8+z3q9WPlh62q5uecEI56NLcQIb5lv79sBDOGYk4bsU2tku0QvyUGknhSrF5rDkVy/bWVpe1rU4q6UFlRZT6jp+5TuHiLPlU+ZCqKtbzcva0BVRDGu1vO7nzQ1V7EBIZrN6XAStiMQ+R42NpI277PFGx3Jr1K5NpAG2MFi35w==
*/