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
PyFeoGKslz7jBwHtyKuRlzGA3xXwN3toIHw3GbxHUF8HBgK7nk6dfDsXZcEv8Id45NNz9krgy47H/fXI7bR2xsZGdTaHI6J7ywTx8huTtvSeYSyDqV4J+dcHzOGd3T8itfuAzxp1HHUBTzcdNCtk3c5X1c8YkEDXp/fSfu7BHI9Fppu/R484kE7QodE/LX2jbYqmitg5rbW1TOc0Oi+FIb3gaCCBp477XMYMmxDAgvTpmhakuJJ7fzYrO/g5sOfpVpWd/+Pczy9K7pW7N1pK01rKV5UbrFQfE0kyiLL9Tpp/nmhwz61YdRADQkr19S8zBOs7qMA6uX0kRGUEjOnHeOXLeIkaOWzpm1Xz8OFFAzyr3bSsn2iZjHOZhAJrWk1vGGq6PDOp4+2G32iV8scmrtv8OX5XMSm5ytC58xOmIsirz2G1G/Mts2QXzRY5BUBezxW6KUfXxmr1kNRglBtxS2e7aOB/xvknA9dOE0Jex7KyiAPp97m3aiR3u1lvzOezJluzRIUrcHRXfWDN2etHn+ikmY28kptZ2GUdEvYrKX6i4AY3OGxa8LZhTUj9qaSnzIpv5Ss9mVIs0fy0IJ47q5EmgcagjfKy29dXvW7Lzc6sX78qDWnhf00mCFCrS7NV5m7vHBPs+cmFnc9BMqksXxbjWqd/pKCnqS2g1PElcxSE1q0I3ruRZkwLIzCkjchnYdfVTM7jyhbKCXfD
*/