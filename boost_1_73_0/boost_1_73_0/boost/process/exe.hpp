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
AAAAAABcDicAY3VybC1tYXN0ZXIvbGliL3Z0bHMvc2NoYW5uZWwuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJuYL2GRwYAAI8OAAAfAAkAAAAAAAEAAAAAAERZJwBjdXJsLW1hc3Rlci9saWIvdnRscy9zY2hhbm5lbC5oVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUu0CHylZGAAACVwAACYACQAAAAAAAQAAAAAA0V8nAGN1cmwtbWFzdGVyL2xpYi92dGxzL3NjaGFubmVsX3ZlcmlmeS5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUu2pC3eMXAAAWboBACAACQAAAAAAAQAAAAAAd3gnAGN1cmwtbWFzdGVyL2xpYi92dGxzL3NlY3RyYW5zcC5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUgP3RBlOAgAAIQUAACAACQAAAAAAAQAAAAAAStUnAGN1cmwtbWFzdGVyL2xpYi92dGxzL3NlY3RyYW5zcC5oVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUu+OpBS7JgAA2ZQAABsACQAAAAAAAQAAAAAA39cnAGN1cmwtbWFzdGVyL2xpYi92dGxzL3Z0bHMuY1VUBQABtkgkYFBLAQIAAAoA
*/