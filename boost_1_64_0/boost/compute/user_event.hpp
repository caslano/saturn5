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
otfzf74ZW9bks94853m+67PdPNf1eW6e5TzHm39+67Nbn9sxz+pWPKddnsvmmTzT+RzmGRz33DXP3PH6rJ1DnNXC56cf/OAHP/jhT/bOBDCq4gzAbzckBhIgWWATwmGACAEDchtOE+QICBgQECslBJKQQEiWHBg5BBQ8WkRsqSKCoqKiVYstVG1r0ZaqvSy9raVVW9va1laUVmm9+u2//87u290HCaa26o4OX+a9f+bNm5k3+94//8zEXdzF3UfNfWjf/3Wt8/3/7bDv/2P6/X8PviN+j37/W2Hf/3VVq0obylEARHz/e4LjSyK7nXVBhjh956uMl/8C68h5JXwD4QSrzKx1Zl8LrjOcLnL95fyaTrKuV76kq/qCC+X8mWatuO9wb0/h7xBdQevoBDpYo9Lz9FttdmZIR3DkE6gjKJYxmaNXlW29J+P4wVe6LH7pmU2HBjjpDpzGalquU2ip7uBN0R3srv3559bc/ezOA7s+v8T34p5uzmNQaXJfvyzePemV+6uHb8s78uzf372+n5Mu43+ng4g95tO6uoltlj6v2i/s4I+OcFOYvbE/3An2g71gHuysugovHAMz4DSYCS+EXeEcmAVLYDdYBXvARk1nDTwT7lZdxh49vraZ6/CcamzE2DL/9n+7/s5EHpj5eKfxkTYvtM4YyeAXosdJ1nLdSF3INo45j5eceqzEridB9oWAruQA6TqNl/zgig82XtKcsZItL9jHS9qsT0DP0npjJQ+80LLxkgP3ttKYyfqEFo2bfJAxk2NxfU7cxV3cxV3cxZ24D3v//wr/mst8ybfG/v9+HcChMB3AUbVxPuDGrgvugkWZ2KVPEh1AKfa2hRfNHFJy0ZzZU2dOCcy33Snrgy/2he3HrfLTbGt6F6SLXD1Bs6Z3ncgtc+dYY9yqH9C4Qy2vyLismyQ80/09LKeGuTtJmtdqmr4kSbOxIjS3WOOfI+E5hGslvJH0zbrkVavLdY90I19oZek6+RslfKm7u2uSdciVa7Xnmh4557K2TvGfW0gJj5F87NB86N7WS0uraky6L0k6PcL2pyafgUtLesuQuV5kPuvKsea6suQYOwnLsfHuLOwdvmDNc6W408KuUdPIGK/kNRNuFtmL3T1cRdbXyWtb8ur1n+Po7yb7z3V0JVt7rUPkN2xddV+wDorIwzUi97CVype1V45hwSHHJpGnEZbPespqZ65fRbyAPmaRyLxoTcDKI0vv52HJzy9diRzJ4fiXqLO+Ih+qx27c12j8Qf++567x1pWuVdR+CtcOv/8Uc/+hay8z697n+q9NKMsf5q80Cd/kyuTYVO75067h5Nncr8SbSf6ukrR9pi1wToyuvbo2foOcz3KfwPplr6tYjwfLo8TVnrvdYK2R/dyHI3+FyK9yh/K4QsrH/zA9KHG+QgkuJB2OEbpTjo10pXC0lHIdgK6qLbLDPOg78F/HDxN9VciXCpu3JvwdU2xrwsuzt1PWdZfnU45da9Zv51nUY9sgzxLHaKN6bIeZ+y6N1rZHRY7acKe6kFVOp0HuL1JdYWnz+gmRpxa9Wj/fk/AbVkf+vRDvL9dC1TFq/6BxMiTOPMJPS/ifVhr6w2J86DlvuNxXHmjnlSZePWsH50ncStpa4lT/scXYVrSlZr3yTBerblOfN7N3xR0ia54vjfsIR7AZ49/exMlNQ7DNooj77zd69KKh/FNp7rtG4vYJf66MnrO7nNuhz1noOmdY++TerhDDUa0nqr4I/lvu7VtWNvfhoU0lcGx3mnptO9mnaDsHptrbToGt7SCj+tDCMP1osWkjUtbIpEoZvIJPsCqNDpU8B9rW/7ldVWwdqJOOz0k36qTjaz2dppM=
*/