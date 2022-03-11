// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_ARGS_HPP
#define BOOST_PROCESS_ARGS_HPP

/** \file boost/process/args.hpp
 *
 *    This header provides the \xmlonly <globalname alt="boost::process::args">args</globalname>\endxmlonly property. It also provides the
 *    alternative name \xmlonly <globalname alt="boost::process::argv">argv</globalname>\endxmlonly .
 *
 *
\xmlonly
<programlisting>
namespace boost {
  namespace process {
    <emphasis>unspecified</emphasis> <globalname alt="boost::process::args">args</globalname>;
    <emphasis>unspecified</emphasis> <globalname alt="boost::process::argv">argv</globalname>;
  }
}
</programlisting>
\endxmlonly
 */


#include <boost/process/detail/basic_cmd.hpp>
#include <iterator>

namespace boost { namespace process { namespace detail {

struct args_
{
    template<typename T>
    using remove_reference_t = typename std::remove_reference<T>::type;
    template<typename T>
    using value_type = typename remove_reference_t<T>::value_type;

    template<typename T>
    using vvalue_type = value_type<value_type<T>>;

    template <class Range>
    arg_setter_<vvalue_type<Range>, true>     operator()(Range &&range) const
    {
        return arg_setter_<vvalue_type<Range>, true>(std::forward<Range>(range));
    }
    template <class Range>
    arg_setter_<vvalue_type<Range>, true>     operator+=(Range &&range) const
    {
        return arg_setter_<vvalue_type<Range>, true>(std::forward<Range>(range));
    }
    template <class Range>
    arg_setter_<vvalue_type<Range>, false>    operator= (Range &&range) const
    {
        return arg_setter_<vvalue_type<Range>, false>(std::forward<Range>(range));
    }
    template<typename Char>
    arg_setter_<Char, true>     operator()(std::basic_string<Char> && str) const
    {
        return arg_setter_<Char, true> (str);
    }
    template<typename Char>
    arg_setter_<Char, true>     operator+=(std::basic_string<Char> && str) const
    {
        return arg_setter_<Char, true> (str);
    }
    template<typename Char>
    arg_setter_<Char, false>    operator= (std::basic_string<Char> && str) const
    {
        return arg_setter_<Char, false>(str);
    }
    template<typename Char>
    arg_setter_<Char, true>     operator()(const std::basic_string<Char> & str) const
    {
        return arg_setter_<Char, true> (str);
    }
    template<typename Char>
    arg_setter_<Char, true>     operator+=(const std::basic_string<Char> & str) const
    {
        return arg_setter_<Char, true> (str);
    }
    template<typename Char>
    arg_setter_<Char, false>    operator= (const std::basic_string<Char> & str) const
    {
        return arg_setter_<Char, false>(str);
    }
    template<typename Char>
    arg_setter_<Char, true>     operator()(std::basic_string<Char> & str) const
    {
        return arg_setter_<Char, true> (str);
    }
    template<typename Char>
    arg_setter_<Char, true>     operator+=(std::basic_string<Char> & str) const
    {
        return arg_setter_<Char, true> (str);
    }
    template<typename Char>
    arg_setter_<Char, false>    operator= (std::basic_string<Char> & str) const
    {
        return arg_setter_<Char, false>(str);
    }
    template<typename Char>
    arg_setter_<Char, true>     operator()(const Char* str) const
    {
        return arg_setter_<Char, true> (str);
    }
    template<typename Char>
    arg_setter_<Char, true>     operator+=(const Char* str) const
    {
        return arg_setter_<Char, true> (str);
    }
    template<typename Char>
    arg_setter_<Char, false>    operator= (const Char* str) const
    {
        return arg_setter_<Char, false>(str);
    }
//    template<typename Char, std::size_t Size>
//    arg_setter_<Char, true>     operator()(const Char (&str) [Size]) const
//    {
//        return arg_setter_<Char, true> (str);
//    }
//    template<typename Char, std::size_t Size>
//    arg_setter_<Char, true>     operator+=(const Char (&str) [Size]) const
//    {
//        return arg_setter_<Char, true> (str);
//    }
//    template<typename Char, std::size_t Size>
//    arg_setter_<Char, false>    operator= (const Char (&str) [Size]) const
//    {
//        return arg_setter_<Char, false>(str);
//    }

    arg_setter_<char, true> operator()(std::initializer_list<const char*> &&range) const
    {
        return arg_setter_<char>(range.begin(), range.end());
    }
    arg_setter_<char, true> operator+=(std::initializer_list<const char*> &&range) const
    {
        return arg_setter_<char, true>(range.begin(), range.end());
    }
    arg_setter_<char, false> operator= (std::initializer_list<const char*> &&range) const
    {
        return arg_setter_<char, true>(range.begin(), range.end());
    }
    arg_setter_<char, true> operator()(std::initializer_list<std::string> &&range) const
    {
        return arg_setter_<char>(range.begin(), range.end());
    }
    arg_setter_<char, true> operator+=(std::initializer_list<std::string> &&range) const
    {
        return arg_setter_<char, true>(range.begin(), range.end());
    }
    arg_setter_<char, false> operator= (std::initializer_list<std::string> &&range) const
    {
        return arg_setter_<char, true>(range.begin(), range.end());
    }

    arg_setter_<wchar_t, true> operator()(std::initializer_list<const wchar_t*> &&range) const
    {
        return arg_setter_<wchar_t>(range.begin(), range.end());
    }
    arg_setter_<wchar_t, true> operator+=(std::initializer_list<const wchar_t*> &&range) const
    {
        return arg_setter_<wchar_t, true>(range.begin(), range.end());
    }
    arg_setter_<wchar_t, false> operator= (std::initializer_list<const wchar_t*> &&range) const
    {
        return arg_setter_<wchar_t, true>(range.begin(), range.end());
    }
    arg_setter_<wchar_t, true> operator()(std::initializer_list<std::wstring> &&range) const
    {
        return arg_setter_<wchar_t>(range.begin(), range.end());
    }
    arg_setter_<wchar_t, true> operator+=(std::initializer_list<std::wstring> &&range) const
    {
        return arg_setter_<wchar_t, true>(range.begin(), range.end());
    }
    arg_setter_<wchar_t, false> operator= (std::initializer_list<std::wstring> &&range) const
    {
        return arg_setter_<wchar_t, true>(range.begin(), range.end());
    }
};


}
/**

The `args` property allows to explicitly set arguments for the execution. The
name of the executable will always be the first element in the arg-vector.

\section args_details Details

\subsection args_operations Operations

\subsubsection args_set_var Setting values

To set a the argument vector the following syntax can be used.

\code{.cpp}
args = value;
args(value);
\endcode

`std::initializer_list` is among the allowed types, so the following syntax is also possible.

\code{.cpp}
args = {value1, value2};
args({value1, value2});
\endcode

Below the possible types for `value` are listed, with `char_type` being either `char` or `wchar_t`.

\paragraph args_set_var_value value

 - `std::basic_string<char_type>`
 - `const char_type * `
 - `std::initializer_list<const char_type *>`
 - `std::vector<std::basic_string<char_type>>`

Additionally any range of `std::basic_string<char_type>` can be passed.

\subsubsection args_append_var Appending values

To append a the argument vector the following syntax can be used.

\code{.cpp}
args += value;
\endcode

`std::initializer_list` is among the allowed types, so the following syntax is also possible.

\code{.cpp}
args += {value1, value2};
\endcode

Below the possible types for `value` are listed, with `char_type` being either `char` or `wchar_t`.

\paragraph args_append_var_value value

 - `std::basic_string<char_type>`
 - `const char_type * `
 - `std::initializer_list<const char_type *>`
 - `std::vector<std::basic_string<char_type>>`

Additionally any range of `std::basic_string<char_type>` can be passed.


\subsection args_example Example

The overload form is used when more than one string is passed, from the second one forward.
I.e. the following expressions have the same results:

\code{.cpp}
spawn("gcc", "--version");
spawn("gcc", args ="--version");
spawn("gcc", args+="--version");
spawn("gcc", args ={"--version"});
spawn("gcc", args+={"--version"});
\endcode

\note A string will be parsed and set in quotes if it has none and contains spaces.


 */
constexpr boost::process::detail::args_ args{};

///Alias for \xmlonly <globalname alt="boost::process::args">args</globalname> \endxmlonly .
constexpr boost::process::detail::args_ argv{};


}}

#endif

/* args.hpp
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
*/