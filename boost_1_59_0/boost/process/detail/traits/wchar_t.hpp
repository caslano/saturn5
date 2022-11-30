// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_TRAITS_WCHAR_T_HPP_
#define BOOST_PROCESS_DETAIL_TRAITS_WCHAR_T_HPP_

#include <algorithm>

#include <boost/process/detail/traits/decl.hpp>
#include <boost/process/detail/traits/cmd_or_exe.hpp>
#include <boost/process/detail/traits/env.hpp>
#include <boost/process/locale.hpp>

namespace boost { namespace process { namespace detail {

//template

template<typename T> struct is_wchar_t : std::false_type {};

template<> struct is_wchar_t<boost::filesystem::path> : std::is_same<typename boost::filesystem::path::value_type, wchar_t>
{
};

template<> struct is_wchar_t<const wchar_t* > : std::true_type {};

template<> struct is_wchar_t<wchar_t* > : std::true_type {};

template<std::size_t Size> struct is_wchar_t<const wchar_t [Size]>    : std::true_type {};
template<std::size_t Size> struct is_wchar_t<const wchar_t (&)[Size]> : std::true_type {};

template<> struct is_wchar_t<std::wstring>               : std::true_type {};
template<> struct is_wchar_t<std::vector<std::wstring>>  : std::true_type {};
template<> struct is_wchar_t<std::initializer_list<std::wstring>> : std::true_type {};
template<> struct is_wchar_t<std::vector<wchar_t *>>           : std::true_type {};
template<> struct is_wchar_t<std::initializer_list<wchar_t *>> : std::true_type {};



template<typename Char, typename T>
struct char_converter
{
    static T&  conv(T & in)
    {
        return in;
    }
    static T&& conv(T&& in)
    {
        return std::move(in);
    }
    static const T&  conv(const T & in)
    {
        return in;
    }
};

template<typename Char, typename T>
using char_converter_t = char_converter<Char,
        typename std::remove_cv<typename std::remove_reference<T>::type>::type>;


template<>
struct char_converter<char, const wchar_t*>
{
    static std::string conv(const wchar_t* in)
    {
        std::size_t size = 0;
        while (in[size] != L'\0') size++;
        return ::boost::process::detail::convert(in, in + size);
    }
};

template<>
struct char_converter<char, wchar_t*>
{
    static std::string conv(wchar_t* in)
    {
        std::size_t size = 0;
        while (in[size] != L'\0') size++;
        return ::boost::process::detail::convert(in, in + size);
    }
};

template<std::size_t Size>
struct char_converter<char, wchar_t[Size]>
{
    static std::string conv(const wchar_t(&in)[Size])
    {
        return ::boost::process::detail::convert(in, in + Size -1);
    }
};

template<>
struct char_converter<wchar_t, const char*>
{
    static std::wstring conv(const char* in)
    {
        std::size_t size = 0;
        while (in[size] != '\0') size++;
        return ::boost::process::detail::convert(in, in + size);
    }
};

template<>
struct char_converter<wchar_t, char*>
{
    static std::wstring conv(char* in)
    {
        std::size_t size = 0;
        while (in[size] != '\0') size++;
        return ::boost::process::detail::convert(in, in + size);
    }
};


template<std::size_t Size>
struct char_converter<wchar_t, char[Size]>
{
    static std::wstring conv(const char(&in)[Size])
    {
        return ::boost::process::detail::convert(in, in + Size -1);
    }
};

//all the containers.
template<>
struct char_converter<wchar_t, std::string>
{
    static std::wstring conv(const std::string & in)
    {
        return ::boost::process::detail::convert(in);
    }
};

template<>
struct char_converter<char, std::wstring>
{
    static std::string conv(const std::wstring & in)
    {
        return ::boost::process::detail::convert(in);
    }
};

template<>
struct char_converter<wchar_t, std::vector<std::string>>
{
    static std::vector<std::wstring> conv(const std::vector<std::string> & in)
    {
        std::vector<std::wstring> ret(in.size());
        std::transform(in.begin(), in.end(), ret.begin(),
                [](const std::string & st)
                {
                    return convert(st);
                });
        return ret;
    }
};

template<>
struct char_converter<wchar_t, std::initializer_list<std::string>>
{
    static std::vector<std::wstring> conv(const std::initializer_list<std::string> & in)
    {
        std::vector<std::wstring> ret(in.size());
        std::transform(in.begin(), in.end(), ret.begin(),
                [](const std::string & st)
                {
                    return convert(st);
                });
        return ret;
    }
};

template<>
struct char_converter<wchar_t, std::vector<char* >>
{
    static std::vector<std::wstring> conv(const std::vector<char* > & in)
    {
        std::vector<std::wstring> ret(in.size());
        std::transform(in.begin(), in.end(), ret.begin(),
                [](const char* st)
                {
                    std::size_t sz = 0;
                    while (st[sz] != '\0') sz++;
                    return convert(st, st + sz);
                });
        return ret;
    }
};

template<>
struct char_converter<wchar_t, std::initializer_list<char *>>
{
    static std::vector<std::wstring>  conv(const std::initializer_list<char * > & in)
    {
        std::vector<std::wstring> ret(in.size());
        std::transform(in.begin(), in.end(), ret.begin(),
                [](const char* st)
                {
                    std::size_t sz = 0;
                    while (st[sz] != '\0') sz++;
                    return convert(st, st + sz);
                });
        return ret;
    }
};

template<>
struct char_converter<char, std::vector<std::wstring>>
{
    static std::vector<std::string> conv(const std::vector<std::wstring> & in)
    {
        std::vector<std::string> ret(in.size());
        std::transform(in.begin(), in.end(), ret.begin(),
                [](const std::wstring & st)
                {
                    return convert(st);
                });
        return ret;
    }
};

template<>
struct char_converter<char, std::initializer_list<std::wstring>>
{
    static std::vector<std::string> conv(const std::initializer_list<std::wstring> & in)
    {
        std::vector<std::string> ret(in.size());
        std::transform(in.begin(), in.end(), ret.begin(),
                [](const std::wstring & st)
                {
                    return convert(st);
                });
        return ret;
    }
};

template<>
struct char_converter<char, std::vector<wchar_t* >>
{
    static std::vector<std::string> conv(const std::vector<wchar_t* > & in)
    {
        std::vector<std::string> ret(in.size());
        std::transform(in.begin(), in.end(), ret.begin(),
                [](const wchar_t* st)
                {
                    std::size_t sz = 0;
                    while (st[sz] != L'\0') sz++;
                    return convert(st, st + sz);
                });
        return ret;
    }
};

template<>
struct char_converter<char, std::initializer_list<wchar_t * >>
{
    static std::vector<std::string> conv(const std::initializer_list<wchar_t *> & in)
    {
        std::vector<std::string> ret(in.size());
        std::transform(in.begin(), in.end(), ret.begin(),
                [](const wchar_t* st)
                {
                    std::size_t sz = 0;
                    while (st[sz] != L'\0') sz++;
                    return convert(st, st + sz);
                });
        return ret;
    }
};


}}}
#endif /* BOOST_PROCESS_DETAIL_TRAITS_WCHAR_T_HPP_ */

/* wchar_t.hpp
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
*/