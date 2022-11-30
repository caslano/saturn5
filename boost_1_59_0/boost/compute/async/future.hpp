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
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
*/