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
12puMAsNom6l4MUR+U886ek10DyzUum61JzDe/A/QNRqIVHRp2998KXYkAuchWfh0/+fWdMx6Xthcg2z6PPEOwZ6A+7GAEvZCtUZuYdNJ1CadSetIDmOyblglsF1mi5gMU9SyCsmGoeZrGbzRRInXngBv4gml13B4ZxIeglWn7zQtPg2Bn+rRHFcyAlOo8M95Iwk3VYZC699IIfRH17ICsdyNUkul/Eijeczz8207JqcjoWbKcfkc4YjDeFKQaMsqfgVJFjYuowddi1qnolG2JP3o3W5wENqLGfFK++4HycjAuxMr7pcchRI14Kr/rsO2TFrW46CLGCHevAOTATFiqLnCXsF1h1WteGQMynJv+L9jnC4FR77DUcL0R42hd23grz3ePoYnhVWouIfquHM7DM8RsQ1FPSA0nOEnkf7olWioUAsxs0ZcyFew+rHd7SOWmaGmvE1lXJ5s5zOF2lGI6eJDyy4JLDpQ5IHNHQvhTZWWF6T0wG41Kr2Bof/twZHsFXfUAEjzHVdXtBLZ+5BDyBYluYWdwGmR4BPpOpKxZyfb73bOLTYsO+zm+kUWRZYpWhuaUMzZ3tgQQtVMaSwE4hbs2+8X8MPWusT8URd80Kg3nA6NHpUHDDnETqxRl+ieBpdxNM4XXlXD+Ik
*/