// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_CMD_LINE_HPP
#define BOOST_PROCESS_DETAIL_CMD_LINE_HPP

#include <boost/winapi/config.hpp>
#include <boost/process/detail/config.hpp>
#include <boost/process/detail/handler_base.hpp>
#include <boost/process/detail/traits/cmd_or_exe.hpp>
#include <boost/process/detail/traits/wchar_t.hpp>

#if defined(BOOST_POSIX_API)
#include <boost/process/detail/posix/cmd.hpp>
#elif defined(BOOST_WINDOWS_API)
#include <boost/process/detail/windows/cmd.hpp>
#endif

/** \file boost/process/cmd.hpp
 *
 *    This header provides the \xmlonly <globalname alt="boost::process::cmd">cmd</globalname>\endxmlonly property.
 *
\xmlonly
<programlisting>
namespace boost {
  namespace process {
    <emphasis>unspecified</emphasis> <globalname alt="boost::process::cmd">cmd</globalname>;
  }
}
</programlisting>
\endxmlonly
*/

namespace boost { namespace process { namespace detail {


struct cmd_
{
    constexpr cmd_() = default;

    template<typename Char>
    inline api::cmd_setter_<Char> operator()(const Char *s) const
    {
        return api::cmd_setter_<Char>(s);
    }
    template<typename Char>
    inline api::cmd_setter_<Char> operator= (const Char *s) const
    {
        return api::cmd_setter_<Char>(s);
    }

    template<typename Char>
    inline api::cmd_setter_<Char> operator()(const std::basic_string<Char> &s) const
    {
        return api::cmd_setter_<Char>(s);
    }
    template<typename Char>
    inline api::cmd_setter_<Char> operator= (const std::basic_string<Char> &s) const
    {
        return api::cmd_setter_<Char>(s);
    }
};

template<> struct is_wchar_t<api::cmd_setter_<wchar_t>> : std::true_type {};



template<>
struct char_converter<char, api::cmd_setter_<wchar_t>>
{
    static api::cmd_setter_<char> conv(const api::cmd_setter_<wchar_t> & in)
    {
        return { ::boost::process::detail::convert(in.str()) };
    }
};

template<>
struct char_converter<wchar_t, api::cmd_setter_<char>>
{
    static api::cmd_setter_<wchar_t> conv(const api::cmd_setter_<char> & in)
    {
        return { ::boost::process::detail::convert(in.str()) };
    }
};






}


/** The cmd property allows to explicitly set commands for the execution.

The overload form applies when only one string is passed to a launching function.
The string will be internally parsed and split at spaces.

The following expressions are valid, with `value` being either a C-String or
a `std::basic_string` with `char` or `wchar_t`.

\code{.cpp}
cmd="value";
cmd(value);
\endcode

The property can only be used for assignments.


 */
constexpr static ::boost::process::detail::cmd_ cmd;

}}

#endif

/* cmd.hpp
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
*/