// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_SHELL_PATH_HPP
#define BOOST_PROCESS_SHELL_PATH_HPP

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/traits/wchar_t.hpp>

#if defined(BOOST_POSIX_API)
#include <boost/process/detail/posix/shell_path.hpp>
#elif defined(BOOST_WINDOWS_API)
#include <boost/process/detail/windows/shell_path.hpp>
#endif

/** \file boost/process/shell.hpp
 *
 *    Header which provides the shell property. This provides the
 *    property to launch a process through the system shell.
 *    It also allows the user to obtain the shell-path via shell().
\xmlonly
<programlisting>
namespace boost {
  namespace process {
    <emphasis>unspecified</emphasis> <globalname alt="boost::process::shell">shell</globalname>;
  }
}
</programlisting>
\endxmlonly

 */

namespace boost { namespace process { namespace detail {


struct shell_
{
    constexpr shell_() {}

    boost::filesystem::path operator()() const
    {
        return boost::process::detail::api::shell_path();
    }
    boost::filesystem::path operator()(std::error_code & ec) const noexcept
    {
        return boost::process::detail::api::shell_path(ec);
    }
};

template<>
struct is_wchar_t<shell_> : is_wchar_t<boost::filesystem::path>
{
};

}
/**
The shell property enables to launch a program through the shell of the system.

\code{.cpp}
system("gcc", shell);
\endcode

The shell argument goes without any expression. The operator() is overloaded, to
obtain the path of the system shell.

\code{.cpp}
auto shell_cmd = shell();
//avoid exceptions
std::error_code ec;
shell_cmd = shell(ec);
\endcode

\attention Launching through the shell will NOT provide proper error handling, i.e.
you will get an error via the return code.

\attention Executing shell commands that incorporate unsanitized input from an untrusted source makes a program vulnerable to shell injection, a serious security flaw which can result in arbitrary command execution. For this reason, the use of `shell` is strongly discouraged in cases where the command string is constructed from external input:

*/
constexpr ::boost::process::detail::shell_ shell;

}}



#endif

/* shell.hpp
HRz3BaJbdVW22wKibEnGV0xOMaN2Z56sQq5EQ8gadfmoRwoGJuLr6Bhs5NwYREhtbb9jPceYLQD/93txu6xeAaMFTi6jBRY0nCB5Iolr6RT7FNfO+LaX852DvMjvOMDVlbNMNN+MEVEUSlWKpr4Y8/JmnzAUrwTJ6SzVY4cDYEMZzgTlaLto6CEZezCbROLyiDf1X/gIeTA0wSo5LjmjJv0Guwn78PqmAUAtWfbyQv4pb7rqde8p2QbPvEsjUZcsG+eLj8T8Cw5Vn2+gPhKo7WW+5bOrgxY6rlOZdryaUwtIoI+yNDxeA8R5HlNdE+6Zj8wDdoL0OZdylXIGiugQCvoeDVaAb/KIM/aar9nYIwb3GPzbDDHtykl6OdONPnjZ6tJHUBjlMaWXxig1CWFt5N77m9iMLnb03kITLUPJZWQqVy7da9L+df9G8pCUdhIjAXSH8nHhVcSkzmNccoN+zKQCwgrDaCIsVscm3om9eFaUsK92zV9qVbu1yh5I2V/YJdOL0O3dkB0QGiySR8yVLwvfXkqf/kW2p57YM43y3GsSV6zbk5rxSUTunQ==
*/