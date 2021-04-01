// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_TRAITS_CMD_OR_EXE_HPP_
#define BOOST_PROCESS_DETAIL_TRAITS_CMD_OR_EXE_HPP_

#include <string>
#include <vector>
#include <type_traits>
#include <initializer_list>
#include <boost/filesystem/path.hpp>
#include <boost/process/detail/traits/decl.hpp>
namespace boost { namespace process { namespace detail {

template<typename Char>
struct cmd_or_exe_tag {};

struct shell_;


template<> struct initializer_tag<const char*    > { typedef cmd_or_exe_tag<char>    type;};
template<> struct initializer_tag<const wchar_t* > { typedef cmd_or_exe_tag<wchar_t> type;};

template<> struct initializer_tag<char*    > { typedef cmd_or_exe_tag<char>     type;};
template<> struct initializer_tag<wchar_t* > { typedef cmd_or_exe_tag<wchar_t>  type;};

template<std::size_t Size> struct initializer_tag<const char    [Size]> { typedef cmd_or_exe_tag<char>     type;};
template<std::size_t Size> struct initializer_tag<const wchar_t [Size]> { typedef cmd_or_exe_tag<wchar_t>  type;};

template<std::size_t Size> struct initializer_tag<const char    (&)[Size]> { typedef cmd_or_exe_tag<char>     type;};
template<std::size_t Size> struct initializer_tag<const wchar_t (&)[Size]> { typedef cmd_or_exe_tag<wchar_t>  type;};

template<> struct initializer_tag<std::basic_string<char    >> { typedef cmd_or_exe_tag<char>     type;};
template<> struct initializer_tag<std::basic_string<wchar_t >> { typedef cmd_or_exe_tag<wchar_t>  type;};

template<> struct initializer_tag<std::vector<std::basic_string<char    >>> { typedef cmd_or_exe_tag<char>     type;};
template<> struct initializer_tag<std::vector<std::basic_string<wchar_t >>> { typedef cmd_or_exe_tag<wchar_t>  type;};

template<> struct initializer_tag<std::initializer_list<std::basic_string<char    >>> { typedef cmd_or_exe_tag<char>     type;};
template<> struct initializer_tag<std::initializer_list<std::basic_string<wchar_t >>> { typedef cmd_or_exe_tag<wchar_t>  type;};

template<> struct initializer_tag<std::vector<char    *>> { typedef cmd_or_exe_tag<char>     type;};
template<> struct initializer_tag<std::vector<wchar_t *>> { typedef cmd_or_exe_tag<wchar_t>  type;};

template<> struct initializer_tag<std::initializer_list<char    *>> { typedef cmd_or_exe_tag<char>     type;};
template<> struct initializer_tag<std::initializer_list<wchar_t *>> { typedef cmd_or_exe_tag<wchar_t>  type;};

template<> struct initializer_tag<std::initializer_list<const char    *>> { typedef cmd_or_exe_tag<char>     type;};
template<> struct initializer_tag<std::initializer_list<const wchar_t *>> { typedef cmd_or_exe_tag<wchar_t>  type;};

template<> struct initializer_tag<shell_>
{
    typedef cmd_or_exe_tag<typename boost::filesystem::path::value_type> type;
};

template<> struct initializer_tag<boost::filesystem::path>
{
    typedef cmd_or_exe_tag<typename boost::filesystem::path::value_type> type;
};

template <typename Char>
struct exe_setter_;
template <typename Char, bool Append = false>
struct arg_setter_;

template <typename Char, bool Append>
struct initializer_tag<arg_setter_<Char, Append>> { typedef cmd_or_exe_tag<Char> type;};

template<typename Char> struct initializer_tag<exe_setter_<Char>> { typedef cmd_or_exe_tag<Char> type;};

template<>
struct initializer_builder<cmd_or_exe_tag<char>>;

template<>
struct initializer_builder<cmd_or_exe_tag<wchar_t>>;


}}}



#endif /* BOOST_PROCESS_DETAIL_STRING_TRAITS_HPP_ */

/* cmd_or_exe.hpp
cjh9f21K4Ov2Z6AGMqMQ2qoN3vPpPJN9iyAwAWnBhkj6JhHaP5EucXtw8Xpg4ruS/b8dRhOQsYbKOEfJnFEYLGklMyqSh7qDD7KINOBVDDfFtFbhdHKOSr6lm5MaqhdIeDyhUzM6OoE5k/e8tDqCDdVwFXe6XM6hh9nso0NmtL4h2c9jn1l6HCd6whZiO2Tc9ennbegUqZpZ3SCCfF8qOloHbi6FmN9wpoGkAXRyKnebjJK6RYGsnAtAYQ3XaF2wOMgdHfb65X1xYfHZsFBn6H8I9Mlyu7n06bOMUAPMH+tEEUYV8WFgQzF2nbAQLNRkzLbSwr8wj4i7SCD1s0u2GZbMu8Kf8ecdMtMA4Y1cFbygJ9DzxJAMjKQWJeS6G8aG/Rz6phQQa719eFxQvuvH3d0mVIT2p6RemB5thvBD3Fh/mn4m0ujL4tD+orVchn5wHKVGBcsW1vgcAM2FdwZJ13VbnfitRP2y3+FmWRjZfJdl8946DCj4Aya+bqFNB+Lr+QWp54nk8b3/dGGeEUQAyFQrV0wGnjNP3GtTnSe/IDBeyyZfhDu3tcPv4A==
*/