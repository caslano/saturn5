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