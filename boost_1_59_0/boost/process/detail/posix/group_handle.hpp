// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_GROUP_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_GROUP_HPP_

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/posix/child_handle.hpp>
#include <system_error>
#include <unistd.h>

namespace boost { namespace process { namespace detail { namespace posix {

struct group_handle
{
    pid_t grp = -1;

    typedef pid_t handle_t;
    handle_t handle() const { return grp; }

    explicit group_handle(handle_t h) :
        grp(h)
    {
    }

     group_handle() = default;

    ~group_handle() = default;
    group_handle(const group_handle & c) = delete;
    group_handle(group_handle && c) : grp(c.grp)
    {
        c.grp = -1;
    }
    group_handle &operator=(const group_handle & c) = delete;
    group_handle &operator=(group_handle && c)
    {
        grp = c.grp;
        c.grp = -1;
        return *this;
    }

    void add(handle_t proc)
    {
        if (::setpgid(proc, grp))
            throw_last_error();
    }
    void add(handle_t proc, std::error_code & ec) noexcept
    {
        if (::setpgid(proc, grp))
            ec = get_last_error();
    }

    bool has(handle_t proc)
    {
        return ::getpgid(proc) == grp;
    }
    bool has(handle_t proc, std::error_code &) noexcept
    {
        return ::getpgid(proc) == grp;
    }

    bool valid() const
    {
        return grp != -1;
    }
};

inline  void terminate(group_handle &p, std::error_code &ec) noexcept
{
    if (::killpg(p.grp, SIGKILL) == -1)
        ec = boost::process::detail::get_last_error();
    else
        ec.clear();

    p.grp = -1;
}

inline void terminate(group_handle &p)
{
    std::error_code ec;
    terminate(p, ec);
    boost::process::detail::throw_error(ec, "killpg(2) failed in terminate");
}

inline bool in_group()
{
    return true;
}

}}}}

#endif /* BOOST_PROCESS_DETAIL_WINDOWS_GROUP_HPP_ */

/* group_handle.hpp
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
*/