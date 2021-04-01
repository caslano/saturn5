// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_POSIX_CHILD_HPP
#define BOOST_PROCESS_POSIX_CHILD_HPP

#include <utility>
#include <system_error>

namespace boost { namespace process { namespace detail { namespace posix {

typedef ::pid_t pid_t;

struct child_handle
{
    int pid {-1};
    explicit child_handle(int pid) : pid(pid)
    {}

    child_handle()  = default;
    ~child_handle() = default;

    child_handle(const child_handle & c) = delete;
    child_handle(child_handle && c) : pid(c.pid)
    {
        c.pid = -1;
    }
    child_handle &operator=(const child_handle & c) = delete;
    child_handle &operator=(child_handle && c)
    {
        pid = c.pid;
        c.pid = -1;
        return *this;
    }

    int id() const
    {
        return pid;
    }
    bool in_group() const {return true;}
    bool in_group(std::error_code&) const noexcept {return true;}

    typedef int process_handle_t;
    process_handle_t process_handle() const { return pid; }

    bool valid() const
    {
        return pid != -1;
    }
};

}}}}

#endif

/* child_handle.hpp
LCKoLbrXWT3VnTWJwD7ITeGMlhcTVwT54cQjMfItcA482KJnmi2O+bq9wj9QD1d9pEuFtHV6Y81/JEXcQagxH6lWVKe0bIhuGODrGGzoduFwbqvpmKy2CgueUrR5m6chZPjZveuHOmPitzxxaWzDygCmsQFdn8QIekxkB7xXa3BT5Ctp4fDpzKGri4q+xRUVP1vDCQoOIPvWuiQ3CCfqZSUJqhn50TWVl3l31yXGODA76LhPhZP52wehXAwRv9QchG4IapqhC7L5QGikTVavhu9+XrsQ69JGtgYF31Iu1uTF89xe8235m/KgxdaWdeIxr6ACUD9aCIdD37KjzPH/BAktCcHn6j8Hsey2VRE0Av6l0vW8ytuPz2bnuQTC52ELcDPZ9ZCLApwdN8Q33cZ1/u41sdg6gb4LKK56Rd7GF0LXghKse+dSC0VAcdpSkanlVATggeNsQufguxNNHnIBLHZLxfJZdPPlI1eQnj8nmSh4Q9vE6xXVv2NtMel0ESN7yXHAI8W8tTAdmGf1rGqtGKVDStpHMTSk5rCDmcwmGSr45/UtCY0IYoATQw==
*/