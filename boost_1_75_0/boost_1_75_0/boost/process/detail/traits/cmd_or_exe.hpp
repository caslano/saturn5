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
LV+GgwG9/TeSR6QIiPL9n+EvR3KiBn53Mq0hMMQigmra8Qjs4qmEBq/muZqImUZKXwrEA+NESi7bmJlF61CQwOSWLqABP/LiwtQOaOXs9WEaQOBoNFTGMvvsL1ypgyQ+zO6aRhrf327jhwrQKcXT/Agg1jVnhjp9TX7Y8jEtqUEewEyeYHRZeZPPil49cbjLSPbL2vF/rlsXmV6QQv4vTWf43zH6Pyi6nz3lkA/SUiHdKSqfRW/RTUbh97dIkLA6IWMUoQ/+iXUk0UQBy0iSJJePkmvlHtWfJuaoL8mUFG3nNEyP4kQfgzGLgjZIVCL6j9msNfo4DD9aY0PT0GWw5xXSOjM/NnypV628h2cMUYHm45ls+OSDx7fX0p4sDxGWnUtnkxc5yJXBJuDxrcNWPuPxx4NpjBFJXwbUIaIITdUjWghAnimR1f26+BipBScQD93kZxU9zNsXmsIgeoGFIhNkLo6ZS/QZffmdShB/mYuIVn6n4N5z8TEz4PYz0Qpt1iORhM3c/uznGvNVSR+bHPDdpb1PZHcXa8YaL6LzIbSoFTLU2eOq7rTB5OJD9PtTLC1FiBeGJXcM2crLvZ/ffb+hPWPIGxC5afOClYI00iua0MV8mOa1IYIkuk/pvBqYNjEITFj0wjUN+lHSLrDoIbtpBNYK3Hhcan/m744+vs0R5N3BR2QLPhGbPAl9+9yJ9xz+osBH6V5gCgGr
*/