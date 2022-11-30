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
        return arg_setter_<char, true>(range.begin(), range.end());
    }
    arg_setter_<char, true> operator+=(std::initializer_list<const char*> &&range) const
    {
        return arg_setter_<char, true>(range.begin(), range.end());
    }
    arg_setter_<char, false> operator= (std::initializer_list<const char*> &&range) const
    {
        return arg_setter_<char, false>(range.begin(), range.end());
    }
    arg_setter_<char, true> operator()(std::initializer_list<std::string> &&range) const
    {
        return arg_setter_<char, true>(range.begin(), range.end());
    }
    arg_setter_<char, true> operator+=(std::initializer_list<std::string> &&range) const
    {
        return arg_setter_<char, true>(range.begin(), range.end());
    }
    arg_setter_<char, false> operator= (std::initializer_list<std::string> &&range) const
    {
        return arg_setter_<char, false>(range.begin(), range.end());
    }

    arg_setter_<wchar_t, true> operator()(std::initializer_list<const wchar_t*> &&range) const
    {
        return arg_setter_<wchar_t, true>(range.begin(), range.end());
    }
    arg_setter_<wchar_t, true> operator+=(std::initializer_list<const wchar_t*> &&range) const
    {
        return arg_setter_<wchar_t, true>(range.begin(), range.end());
    }
    arg_setter_<wchar_t, false> operator= (std::initializer_list<const wchar_t*> &&range) const
    {
        return arg_setter_<wchar_t, false>(range.begin(), range.end());
    }
    arg_setter_<wchar_t, true> operator()(std::initializer_list<std::wstring> &&range) const
    {
        return arg_setter_<wchar_t, true>(range.begin(), range.end());
    }
    arg_setter_<wchar_t, true> operator+=(std::initializer_list<std::wstring> &&range) const
    {
        return arg_setter_<wchar_t, true>(range.begin(), range.end());
    }
    arg_setter_<wchar_t, false> operator= (std::initializer_list<std::wstring> &&range) const
    {
        return arg_setter_<wchar_t, false>(range.begin(), range.end());
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