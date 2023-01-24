// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/**
 * \file boost/process/spawn.hpp
 *
 * Defines the spawn function.
 */

#ifndef BOOST_PROCESS_SPAWN_HPP
#define BOOST_PROCESS_SPAWN_HPP

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/child_decl.hpp>
#include <boost/process/detail/execute_impl.hpp>
#include <boost/process/detail/async_handler.hpp>

#if defined(BOOST_POSIX_API)
#include <boost/process/posix.hpp>
#endif

namespace boost {

namespace process {

namespace detail {

}

/** Launch a process and detach it. Returns no handle.

This function starts a process and immediately detaches it. It thereby prevents the system from creating a zombie process,
but will also cause the system to be unable to wait for the child to exit.

\note This will set `SIGCHLD` to `SIGIGN` on posix.

\warning This function does not allow asynchronous operations, since it cannot wait for the end of the process.
It will fail to compile if a reference to `boost::asio::io_context` is passed.

 */
template<typename ...Args>
inline void spawn(Args && ...args)
{
    typedef typename ::boost::process::detail::has_async_handler<Args...>::type
            has_async;


    static_assert(
            !has_async::value,
            "Spawn cannot wait for exit, so async properties cannot be used");

    auto c = ::boost::process::detail::execute_impl(
#if defined(BOOST_POSIX_API)
            ::boost::process::posix::sig.ign(),
#endif
             std::forward<Args>(args)...);
    c.detach();
}

}}
#endif


/* spawn.hpp
5kOJjk87L4nCBei2Csvx+V1HhISCiOtplWf+dCawNPfhKisr80rwXXh8nxYRS7/CGX7EH4B2KsnbmXpm4ybBpg/cH0M+t3ibCd5+2/3qGG4xDXgnCeM8HJyNt98Z9ml4Xc+Q/VVxx4iNlBUg88rQ6h6/SuMPCwZVrG5FezMPSZIdvviOXRfNEIdXt4nfcqPNbf5c5WVU5630Z40qgAIZtdHPSKI9ci1uAP800ZQIrq5Ffh0IBuIo94J9HUNuj4EkEMKdHTTd2SBTMZH7ZlOWyyfB1x8tkDcPC6iFqFY6eyRlX3q0wracJYpSKw2frhclLsujPQudWZui2fkWWIPO7FsNQmhRSx47M3IkOfZdPqHpYjbGIqjD3lDQDeU2XbDXd2xG5XX246BKmyeivR8CMy3IttF1oqLjsbCTWeWwlZsRWmv4nkf8Cf13gvp1GJwYeOgiNvQJk6rN6a0vvwUXj3kqm06YmXQpz17MpH5SZgcd/kRYyFRwbzXJT7KoX+18vlkeyicGtP6vKdFCJai09gpMlOstlwe2MKpY2GU/oC2hYbrALvlo8NOKbhl1+zW+hriysLBnfAjBj7dysdebafRZWlUGtU1HkBNG6RoliMJEPyuGbNM5K5Gj0USBVFeC5E9S75+/dr/pz58ZKm9Fk3i9a7mKOq902UxcjpEDBfQp9TeovZqa7ESVEAihi4ka7Ocw/9PH1lo4l2H4
*/