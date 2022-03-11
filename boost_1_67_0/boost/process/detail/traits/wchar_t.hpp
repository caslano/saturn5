// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_TRAITS_WCHAR_T_HPP_
#define BOOST_PROCESS_DETAIL_TRAITS_WCHAR_T_HPP_

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