// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/**
 * \file boost/process/group.hpp
 *
 * Defines a group process class.
 * For additional information see the platform specific implementations:
 *
 *   - [windows - job object](https://msdn.microsoft.com/en-us/library/windows/desktop/ms684161.aspx)
 *   - [posix - process group](http://pubs.opengroup.org/onlinepubs/009695399/functions/setpgid.html)
 *
 */

#ifndef BOOST_PROCESS_GROUP_HPP
#define BOOST_PROCESS_GROUP_HPP

#include <boost/process/detail/config.hpp>
#include <boost/process/child.hpp>
#include <chrono>
#include <memory>

#include <boost/none.hpp>
#include <atomic>


#if defined(BOOST_POSIX_API)
#include <boost/process/detail/posix/group_handle.hpp>
#include <boost/process/detail/posix/group_ref.hpp>
#include <boost/process/detail/posix/wait_group.hpp>
#elif defined(BOOST_WINDOWS_API)
#include <boost/process/detail/windows/group_handle.hpp>
#include <boost/process/detail/windows/group_ref.hpp>
#include <boost/process/detail/windows/wait_group.hpp>
#endif

namespace boost {

namespace process {

namespace detail {
    struct group_builder;
}

/**
 * Represents a process group.
 *
 * Groups are movable but non-copyable. The destructor
 * automatically closes handles to the group process.
 *
 * The group will have the same interface as std::thread.
 *
 * \note If the destructor is called without a previous detach or wait, the group will be terminated.
 *
 * \attention If a default-constructed group is used before being used in a process launch, the behaviour is undefined.
 *
 * \attention Waiting for groups is currently broken on windows and will most likely result in a dead-lock.
 */
class group
{
    ::boost::process::detail::api::group_handle _group_handle;
    bool _attached = true;
public:
    typedef ::boost::process::detail::api::group_handle group_handle;
    ///Native representation of the handle.
    typedef group_handle::handle_t native_handle_t;
    explicit group(group_handle &&ch) : _group_handle(std::move(ch)) {}
    ///Construct the group from a native_handle
    explicit group(native_handle_t & handle) : _group_handle(handle) {};
    group(const group&) = delete;
    ///Move constructor
    group(group && lhs)
        : _group_handle(std::move(lhs._group_handle)),
          _attached (lhs._attached)
    {
        lhs._attached = false;
    }
    ///Default constructor
    group() = default;
    group& operator=(const group&) = delete;
    ///Move assign
    group& operator=(group && lhs)
    {
        _group_handle= std::move(lhs._group_handle);
        _attached    = lhs._attached;

        return *this;
    };

    ///Detach the group
    void detach() {_attached = false; }

    /** Join the child. This just calls wait, but that way the naming is similar to std::thread */
    void join() {wait();}
    /** Check if the child is joinable. */
    bool joinable() {return _attached;}

    /** Destructor
     *
     * \note If the destructor is called without a previous detach or wait, the group will be terminated.
     *
     */
    ~group()
    {
        std::error_code ec;
        if ( _attached && valid())
            terminate(ec);
    }

    ///Obtain the native handle of the group.
    native_handle_t native_handle() const { return _group_handle.handle(); }

    ///Wait for the process group to exit.
    void wait()
    {
        boost::process::detail::api::wait(_group_handle);
    }
    ///\overload void wait()
    void wait(std::error_code & ec) noexcept
    {
        boost::process::detail::api::wait(_group_handle, ec);
    }
    /** Wait for the process group to exit for period of time.
      *  \return True if all child processes exited while waiting.*/
    template< class Rep, class Period >
    bool wait_for  (const std::chrono::duration<Rep, Period>& rel_time)
    {
        return boost::process::detail::api::wait_for(_group_handle, rel_time);
    }

    /** \overload bool wait_for(const std::chrono::duration<Rep, Period>& timeout_time ) */
    template< class Rep, class Period >
    bool wait_for  (const std::chrono::duration<Rep, Period>& rel_time, std::error_code & ec) noexcept
    {
        return boost::process::detail::api::wait_for(_group_handle, rel_time, ec);
    }

    /** Wait for the process group to exit until a point in time.
      *  \return True if all child processes exited while waiting.*/
    template< class Clock, class Duration >
    bool wait_until(const std::chrono::time_point<Clock, Duration>& timeout_time )
    {
        return boost::process::detail::api::wait_until(_group_handle, timeout_time);
    }
    /** \overload bool wait_until(const std::chrono::time_point<Clock, Duration>& timeout_time ) */
    template< class Clock, class Duration >
    bool wait_until(const std::chrono::time_point<Clock, Duration>& timeout_time, std::error_code & ec) noexcept
    {
        return boost::process::detail::api::wait_until(_group_handle, timeout_time, ec);
    }

    ///Check if the group has a valid handle.
    bool valid() const
    {
        return _group_handle.valid();
    }
    ///Convenience to call valid.
    explicit operator bool() const {return valid();}

    ///Terminate the process group, i.e. all processes in the group
    void terminate()
    {
        ::boost::process::detail::api::terminate(_group_handle);
    }
    ///\overload void terminate()
    void terminate(std::error_code & ec) noexcept
    {
        ::boost::process::detail::api::terminate(_group_handle, ec);
    }

    ///Assign a child process to the group
    void add(const child &c)
    {
        _group_handle.add(c.native_handle());
    }
    ///\overload void assign(const child & c)
    void add(const child &c, std::error_code & ec) noexcept
    {
        _group_handle.add(c.native_handle(), ec);
    }

    ///Check if the child process is in the group
    bool has(const child &c)
    {
        return _group_handle.has(c.native_handle());
    }
    ///\overload bool has(const child &)
    bool has(const child &c, std::error_code & ec) noexcept
    {
        return _group_handle.has(c.native_handle(), ec);

    }

    friend struct detail::group_builder;
};

namespace detail
{

struct group_tag;
struct group_builder
{
    group * group_p;

    void operator()(group & grp) {this->group_p = &grp;};

    typedef api::group_ref result_type;
    api::group_ref get_initializer() {return api::group_ref (group_p->_group_handle);};
};

template<>
struct initializer_tag<group>
{
    typedef group_tag type;
};

template<>
struct initializer_builder<group_tag>
{
    typedef group_builder type;
};

}
}}
#endif


/* group.hpp
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
*/