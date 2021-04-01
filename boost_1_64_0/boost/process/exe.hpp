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
1aeJDLoxwrtqrj9OgknZ4jrVUvSrTKbyLR8u6aYdXhm8ZDTQbpm9MdTfiAbTRLZmM0BAKMOUWDZ83TJjtZtdaE5nzuGbUtzfw9JDSiJAIlKnXhfYsL+6biS4oQEKZ+lJoMUIm7qAHccaVAVLY56IfhzSPiiCEsTbKax/YqJ+Hv8Fp8gOzUkNxQFfO0kbZt3kZ9Vf5RZDZEDYiMSvba4OdyNO1iAmXr/Juxn/hAfjGXw2YARg0pEqG5mTwxfUuVKPS0wBquZp9GyYfaasrnlMvgcW3G3ypRyGb/Pr96LYLw2ABvpz03T7FH1FXxZv0FN13rXuKCtP6fhk9n4JZ0vc4/4v8iH2GiPVH+OqpB0rhUH5Sic3tIy7cvtSrBe4tOvAIG9QBX7DdzQry0hs48poMoRrbqb71V4qR4zB9ODrMqHXzm4VRsfqYnzcU0oLo+FubyvYizLWVEy4gzgQWeGxekD7xnJ9ia+eaMAi5nucG7lTzGWPFHp5gijKwjP826OCZcq/3lnVBRjvI5rvuGDTsM7hhYmwHZ6cLZTAUVW7aE8Myqw5JQoY04oJNA==
*/