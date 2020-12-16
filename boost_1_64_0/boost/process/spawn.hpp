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
6Mx3wfcwDldiCq7GUfg+jsE1OB/X4QLcgEtwL27CT/EEfoYX8XO8hV+gRxTvpxiEX2JdPIwxeBxb4rfYFb/HnngCB+JJHIrncQb+iK/iT7gKL+JavITb8TIew6v4Df6CZ/B3vIk30KMk+ycWxNsYincwCv/AcvgvrIQOX84H0BOboBe2x3z4DHpjAgbgBCyK/8KSGFKK/QgbYnkcgJUwDaNxFBbDcVgcJ2BlnINV8G2sgFuwBu7Bmvg51sKjWBuvYTOsVpr9EGOwFbbENpiAbTEd2+FgbI9DsQPOwM74DnbBDdgVN2M33IPd8Z/4NB7EHvgL9sQ7+Bz6lmG/xCB8AWtiHDbGftgVEzAJk3AYZmMuTsV1OA034XTUyrLdow/OxG64BF/AdzABl+JCXI5r8D1chyvxMK7Hk7gdNWcbG1gYP8YGuBM74CfYH3fjQNyDKbgXs/EQzsIjOAeP4Tz8Bt/D47geG/jxPo8NcRfG4D48Sf/v8BSew9N4Cc/gdTyLt/EHzF+e7R0L4U9YBC9jCbyCpfEqVsDfsB7ewqZ4G1uixnTboSd2QX8cgAUwHUMxCwvjKAzDhVgU38EI3IW98SDG4UlMwGuYiNdxAGoVWJ9YBAdiKRyElTAFq2Mq1sA0rInp2ECVb4MjMQ1zcCiOxYk4DmfhHJyHr+ESzMYtOBN3qv77Vf9jWAZ/wnKoVWQ/Ql98EvNjJQzGKhiGVbE4VsPSWB1rYg2MwdrYD+vgQKyL6Vgfx2EDnIoN8RWMwTewMa7AFrgKW+HH+AbuwYG+HDcxBc9hKl7ANKz6JNup8/wId2JXXMFwz+FKjMdVmI2rcRzuo9xs3I+v4C+4Bq/hFvwNP8Rv8Cv8Fk/id3gRv8df8Ajex6NYqBLL7ct6xbr4JNbDargB2+Em7IQ/YxxewGS8iGl4HSfjfZyBBZ31hIE4B0fhOmyLm7Ed7sP2eAI74DXsiNexM97GrngPe2D+ynwuxVB8C8vjAozGpVgPl2MHzPbk+1lcS/dIXI/jcQPOwo24GDfhKvwAP8TNeBS34hXcjh5VOK5gYfwQK+BHWAs/xqa4EzvgJ9gTd2EC7sZxuAfn415cj5/iR7gPP8PP8DQewOsa9aT/vgJXqe/zvTFGc/0NdnC9BIdjDI7Ep3E09scXcSbm4HVMIg6p8R1W48uPvdX4LlLUCy+hP17GYLyCRfAqbsI7uB3/wE/wT/wc7+IhvIfXMcO4l515UtPzxwQ1vdoOpoN1MQIbYhQ2wjbYGJ/FJjgQm2IqtsLB2ByHYEscLnnzPgy5Lxv729yHcZD5kzrAgngEi+NRbITfYBM8jk1V/imV76jynfAYxql8ouTN+zAWq+n7OR6+D6MQ8+mBIVgFC2MLDMPuWATjMRzTsSiOwQichsVwIRbH97EEbsRo3IQlcTuWwk+wNH6FlfAaVkVP5ikUfTFa1Vtf/f5frKzm24/XT6v5vk+5AvgAi6PmwfoCT4xGL4zBfOjlII/F0RcroB/yWVRLKcMLYi6xlthPnCE02o0IJ6KJDkQCMZqYS2wkviKuEF58iRlJ1CJ6E8OJ2UQusYc4TlwhfGmnrAIR2pq6P8a9v3zJGs3rtuR6E9nEdCKX2EIcIi4QXhUYPxFN9KT8ZGIHcYVoSy6KjbMDsZjYSSSRG03MIdYSh4hrhG9FyhIxRE9iODGX2EgEPsfnsud5MktHjqOEVyfez4gYoi8xmphNnGHj2oIniHtEVGeOe085NK/jzAuvM4jpRC6xgzhDXCMCurBeiaeJbGIusYU4Q9wjQrtyfkn0JnKIxcRa4hBxnrhDRDON8G6UI3oT2cRkIpfYSOwnrhGh3XmvIHoTGcR04i1iB3E=
*/