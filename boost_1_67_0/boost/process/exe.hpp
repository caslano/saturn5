// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_EXE_HPP
#define BOOST_PROCESS_EXE_HPP

#include <boost/process/detail/basic_cmd.hpp>

/** \file boost/process/exe.hpp
 *
 *    Header which provides the exe property.
\xmlonly
<programlisting>
namespace boost {
  namespace process {
    <emphasis>unspecified</emphasis> <globalname alt="boost::process::exe">exe</globalname>;
  }
}
</programlisting>
\endxmlonly
 */
namespace boost {
namespace filesystem { class path; }

namespace process {

namespace detail {

struct exe_
{
    template<typename = void>
    inline exe_setter_<typename boost::filesystem::path::value_type> operator()(const boost::filesystem::path & pth) const
    {
        return exe_setter_<typename boost::filesystem::path::value_type>(pth.native());
    }

    template<typename = void>
    inline exe_setter_<typename boost::filesystem::path::value_type> operator=(const boost::filesystem::path & pth) const
    {
        return exe_setter_<typename boost::filesystem::path::value_type>(pth.native());
    }


    template<typename Char>
    inline exe_setter_<Char> operator()(const Char *s) const
    {
        return exe_setter_<Char>(s);
    }
    template<typename Char>
    inline exe_setter_<Char> operator= (const Char *s) const
    {
        return exe_setter_<Char>(s);
    }

    template<typename Char>
    inline exe_setter_<Char> operator()(const std::basic_string<Char> &s) const
    {
        return exe_setter_<Char>(s);
    }
    template<typename Char>
    inline exe_setter_<Char> operator= (const std::basic_string<Char> &s) const
    {
        return exe_setter_<Char>(s);
    }
};

}

/** The exe property allows to explicitly set the executable.

The overload form applies when to the first, when several strings are passed to a launching
function.

The following expressions are valid, with `value` being either a C-String or
a `std::basic_string` with `char` or `wchar_t` or a `boost::filesystem::path`.

\code{.cpp}
exe="value";
exe(value);
\endcode

The property can only be used for assignments.


 */
constexpr boost::process::detail::exe_ exe{};

}}

#endif

/* exe.hpp
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
*/