// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_TERMINATE_HPP
#define BOOST_PROCESS_DETAIL_POSIX_TERMINATE_HPP

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/posix/child_handle.hpp>
#include <system_error>
#include <signal.h>
#include <sys/wait.h>


namespace boost { namespace process { namespace detail { namespace posix {

inline void terminate(const child_handle &p, std::error_code &ec) noexcept
{
    if (::kill(p.pid, SIGKILL) == -1)
        ec = boost::process::detail::get_last_error();
    else
        ec.clear();

    int status;
    ::waitpid(p.pid, &status, WNOHANG); //just to clean it up
}

inline void terminate(const child_handle &p)
{
    std::error_code ec;
    terminate(p, ec);
    boost::process::detail::throw_error(ec, "kill(2) failed");
}

}}}}

#endif

/* terminate.hpp
NdesEBSNyVDFUVg5gylayjLauf1skU4nAFVnh7p6/Lr/xZ3NzSeGKxgyLr/KU4FTLZiYfqGWlpju8C6GrkIv/WPaOa7UcXONL9xUx8rETyenDM/rPvS8L/hzOLBZ6fyI8gL/FT3VeTgqVV4fylaPp2rvqP8GVw/r396qaLWTKF2dHYeLR2flJkowFZ4Mfd5ezxzpS/yDS0CSVABLOIQshytIya/bi1Nw9AF6P3Pxc/yebiTmSDShlaAG1/X46PqamDM3C9vai/yRMeb5ZQHy9dsnuUz0hjB1Dh5Pl0HO4h6dXpZRHWe+3fRCJQr8MB81AOTY65AUB8dSlnDQ2mw6Ds3wxrkspVLNKy8NW6vlc8O7eZNfq4ouz9e7j4aUAs1bOn8pJsGp+ZKpb5w5OuByg1jD3vVH460kArNxxbWFdiVGn7pPmHgkq1rT++4eHoxJ1QbvJNbuLIdli/9UiEE8YqyFSzi14tjdXB9oPrSWy/l3XvyxlAWcnF4sEdo8WfvNJMfUB3fveHKqfxWWwqD5HG43Wlau2RM0vxt0T7kwmb+XfKKzAcd3ewo3YitpVSQ+gpHeuiG1sZ/PTfK2IIs023DUKr4vRoVYUEQU/CFpvpfBnw2KMIQHrD93xpm+F+tD5ZtHCBliNXwjzxv4OGhITvXP5vqvHgv0EH2e0oy4+e6yL/hSZWryHM6pwx4KwZryjjDaiGhbERGmBlYf
*/