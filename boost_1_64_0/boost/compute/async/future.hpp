//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ASYNC_FUTURE_HPP
#define BOOST_COMPUTE_ASYNC_FUTURE_HPP

#include <boost/compute/event.hpp>

namespace boost {
namespace compute {

/// \class future
/// \brief Holds the result of an asynchronous computation.
///
/// \see event, wait_list
template<class T>
class future
{
public:
    future()
        : m_event(0)
    {
    }

    future(const T &result, const event &event)
        : m_result(result),
          m_event(event)
    {
    }

    future(const future<T> &other)
        : m_result(other.m_result),
          m_event(other.m_event)
    {
    }

    future& operator=(const future<T> &other)
    {
        if(this != &other){
            m_result = other.m_result;
            m_event = other.m_event;
        }

        return *this;
    }

    ~future()
    {
    }

    /// Returns the result of the computation. This will block until
    /// the result is ready.
    T get()
    {
        wait();

        return m_result;
    }

    /// Returns \c true if the future is valid.
    bool valid() const
    {
        return m_event != 0;
    }

    /// Blocks until the computation is complete.
    void wait() const
    {
        m_event.wait();
    }

    /// Returns the underlying event object.
    event get_event() const
    {
        return m_event;
    }

    #if defined(BOOST_COMPUTE_CL_VERSION_1_1) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Invokes a generic callback function once the future is ready.
    ///
    /// The function specified by callback must be invokable with zero arguments.
    ///
    /// \see_opencl_ref{clSetEventCallback}
    /// \opencl_version_warning{1,1}
    template<class Function>
    future& then(Function callback)
    {
        m_event.set_callback(callback);
        return *this;
    }
    #endif // BOOST_COMPUTE_CL_VERSION_1_1

private:
    T m_result;
    event m_event;
};

/// \internal_
template<>
class future<void>
{
public:
    future()
        : m_event(0)
    {
    }

    template<class T>
    future(const future<T> &other)
        : m_event(other.get_event())
    {
    }

    explicit future(const event &event)
        : m_event(event)
    {
    }

    template<class T>
    future<void> &operator=(const future<T> &other)
    {
        m_event = other.get_event();

        return *this;
    }

    future<void> &operator=(const future<void> &other)
    {
        if(this != &other){
            m_event = other.m_event;
        }

        return *this;
    }

    ~future()
    {
    }

    void get()
    {
        wait();
    }

    bool valid() const
    {
        return m_event != 0;
    }

    void wait() const
    {
        m_event.wait();
    }

    event get_event() const
    {
        return m_event;
    }

    #if defined(BOOST_COMPUTE_CL_VERSION_1_1) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)
    /// Invokes a generic callback function once the future is ready.
    ///
    /// The function specified by callback must be invokable with zero arguments.
    ///
    /// \see_opencl_ref{clSetEventCallback}
    /// \opencl_version_warning{1,1}
    template<class Function>
    future<void> &then(Function callback)
    {
        m_event.set_callback(callback);
        return *this;
    }
    #endif // BOOST_COMPUTE_CL_VERSION_1_1

private:
    event m_event;
};

/// \internal_
template<class Result>
inline future<Result> make_future(const Result &result, const event &event)
{
    return future<Result>(result, event);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ASYNC_FUTURE_HPP

/* future.hpp
qBZ49l11pzQ4+6WwfhsXvIfxmtJO3hgoD86jQ9zEj+e4/pv6CsN6kDy36lvjuFN9+WY4XN1t0Dx+/KrxL5UfDsWnx7vPc+otBfqPxsHR1fQL+v3s/epPE+1npC+uZJl1JPFwBv0ucTu/mSC/+qzoI5/9Gfw+Ux1yEH6ewQ4T96q73aOPdZP5aYJj8drsE+T5N/jZyAh1e/ySnpXcT1/hTHVP41B+BF46Sb15rvHDI3tV42Wd5IsF4oq6WME09/tQ3Z49jOZX/cO+/DT7+rwkj4f7PNGNZ1pvmHQj3KQOvFU+yv8DjqbLtazwvanqKx9bh2Xe5g+ATw/Rz1GCj+lvG/laJL01gl15r7Xid5T53SW+PKQu4zn6x4S6FB23vb4O+n31IeIKnJXo+yPn0434ce6heONx4sl/1IMGJtAzgnkrjaeD90gIxuU37xPm73T62Hr92GXGc4/8NgtP/zc9dLr58/xt/G6teSszrykj4fEF4TrL4HmnfoNnbaCvXaLOS4dt4e95W+gnv+E1eHDSMH5onCPpFQWPhusG9P9cr+/oPHHtWrr0r55nlzpaId5/abgfhPfDj8e9Ay/tx1NO1edWQA8SB2KWssfb1Mu/xBfYV1M8f3rYJ91r9Ffm7VP1yRvFQXFg+9Nx9GE4sYt9W56BY8TZJvEuNQlfs09pzPFw8a36WbbFwI/y4SfyyLPi67Oe4yJ8s1ReO07frHWiMTlhfUi9sFHdVr9v4c34ebZ4azzzo8Wze+H9b2ODefhN/j2Y3V/OvthjNvzX8jE7uEk8aII/v6cv8Z+ivfqsnmIv2+GNt+j5bfpJ1fUbTrPP2nX4Hh6X3p4/pbObZdaDfKKudCK7P5ZelQB/2AevZTK+7H1S6XF56faPfd64/SV+/5feya/KmvEodYv8buF4yKv2/xr9H/edyw/sK1FPf8uKFefHqGvugZtb4T/5oGUCna+Cf/5Kz6c7JU0RJ9M9Xxd4bZJ8dzJe+jp+XoKH/vMv2L+fve9QL7Cf57iHxe3NEXQQOuMu/18X5fmjg/tYj559iuftY32ieFwWI/6NME8N/GOevHolPD6KzvG4uvS9+k8OmK8sdadY9e0YeKERbj2gbxqvqNH/UiJOztcXm0MXK/yP574l1j4U+qeetV/823D9XO/Vyn7V1cu+N66/mse+8Mq/8JQ6+OlHfLB9nHhjHK/Q13isvoY1+kryvN9d+sR68iv7/E01XivNV/U96uUPWYeUYz/o6+nI8H7/ODhuoz4webjkfPyS/ZVMbqcfj244UR3vXLjgMfa+i85H/0qLioKrxYVM+xvs1p/0lHwjfmaw20UdxL+PXWcX/WOp/oF/84+O/v4b92+0z2gGnJkrXt2gLpGuzlKC150Hf9eyS/XsQafwa3hz0F/y+ip6+Rp9d7eY/zPVf/QFTbkeDi/0vDPwvA/Vo+XhEuv3RvfVD3uceDNUPf9UcQteanua/tFZPZNOu/0VfQ+30r3v01eeZ96cOzLL71Mi8Pm/jGMOfXmyOn69ukxYJ81Txz7cOODDBc/rh6PLNn2gX2F7LLyOr50ufn4JL47Ul2rfnqJOcOVBcEWhuDyTXlKIpzbLE9+Jm+5b1cKeX1EPnIZn/01P7hfr/An50vkzJXnh/mziyOPw9xR27vvTn8P7vxafvlSnwm/Xf+V7X8Nl+lrTDsAfx4rf16jb91IHGypeiccZN4rbD9Axn2SnZ1hPW+rclHQ4Dv8eZx/SDHpFehTd9AH6HDwcubCd/Sbxy2TxCG6OXAJfLsYfj5GX3qX7pNFlXvf8d6lrPMZ/K6xXbJLnxtgnBz5uogvUPws/rJXHU+kZk9n32fxnJ558nn1yGzo=
*/