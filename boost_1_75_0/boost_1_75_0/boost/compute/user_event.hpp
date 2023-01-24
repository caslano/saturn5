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
+vnje8AgfhpWPvDN37+FbYHvJN+oYiZcDGITHq7axua3BAalYX1VdjPN6nqFkz+zCha9QkeLdmQBBlo26jItT7Wv+JbmrjqagI+s6fMHTMC5YlanpaLCKpcpHTeocBJoPOhJZbTOS2AEK61FQvN2NoMq0JwmkmWMf6ABLGdz/jI251fAnL8C5ny2WmHv4ifAqOLw50ZzLsyjoSqBT4fQmOjzZaKsTJQhCj8fABTY1NgUibbuAGFkErUNo0aiKEvUy4Rn/PgkvaxclJWLMmPPwipxooPEacvWOloEwk9GiqKRoqiZ3o3gzRQ+q9sPwKw+PoVbUXaqdusBYHyOBIPWDQN4XmSgx+zNwZs6THK+WQQjGJr/7niORrCNi+i6hl+HPU8j2rv8d5/n6foi/FYW5rHZm/2at4hqlfBa0/nVzcsfWtSAL/ojYxv3Re+53xLSF33Mj9b/yhe9bf/IfNFHPNdATAZYdn96n77s1mMyCJDLWNcVoRgIWH7el4H82Q/W4FAMSRCKAWOc2IyhGJI4HKFCMXTS1tBSjiHqVB5fQ29TXl4Iaw1/tOOTWNMmioeyc13s34uHEhsc3yUBFWg+lb2XnPsX7hGswAkkeuk/xB4BxMLMkb93yvtd8m8u+fNTVvSog1zqJi30ozgVood+xBKGexEa7uBkLlbG/YF1ZnpWaBKvisO5NNI8z56vjsJ9Mdx2KMWUQjgD+DBi
*/