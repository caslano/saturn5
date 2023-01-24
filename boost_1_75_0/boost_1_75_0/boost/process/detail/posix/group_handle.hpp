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
gFwQbbOkdWcAvKkQg60ELK2IgKxnhqqjpxGp3Hw67TzFIG5dKM43JxIaTghpDMmoRdUxeMo3xmTaelgYifwuyjdgd6rnOug1qWbw9OhcEemQpofqkVL7D1y4LkUA9uwNiH8YvBhZ/g08fMJGomq7vTzrJFUeMRB42VuB86wUuGHCoMjEpF/voKKRl3rZ/rtOkc8L1ve3d+4xxYjXlZq+1yQoNdQ0N2kEFc7S0Vn23Xbopb0Ck+d4+ZNLfnU8nGJW0wR7d3m32crCdoL0PGC1OB8AbGe6shBo3dHZQ5j7MFPDHVAokVqQ1oNkgtjeCL3pgVCh5b0h2JYtwPSMjhK55p7BOjfxdeBqQfNE9STyxFrBODfdJZkP8sFRCcLBQRUMYi0gO0bCemP4zjsopPcvwwF/BzbaHTKy2LvItxyBDpKUTXloeKogjDYqpPi3I4F7vehGnzxx+dFp6S6tNmR+wpkvjgIzAm97UbQvt5ujnenoZ+3f1L6xGhMKE0qI0DbSWcpqO3pTLbFlPedkJwcojSu9N1299tVJINERFHKyNtdJMJ9/qlRQAJUqmK5xNmQFEQC/NWY5hVgkw2y8RFLmIqbOm+x1uCxAuRzDf8ZC7RUUdJDTzUhNveRBuXO12iEd5geKfnehAjXZ38ypTX5yu9ALVpYbxP2sjbM8EW5SVLTg8h4mpWBnuFEbXZm0v59py44jKctraDicPMb1
*/