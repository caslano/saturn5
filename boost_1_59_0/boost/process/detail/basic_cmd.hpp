// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_BASIC_CMD_HPP_
#define BOOST_PROCESS_DETAIL_BASIC_CMD_HPP_

#include <boost/process/detail/config.hpp>

#include <boost/process/detail/handler_base.hpp>
#include <boost/process/detail/traits/cmd_or_exe.hpp>
#include <boost/process/detail/traits/wchar_t.hpp>

#if defined( BOOST_WINDOWS_API )
#include <boost/process/detail/windows/basic_cmd.hpp>
#include <boost/process/detail/windows/cmd.hpp>
#elif defined( BOOST_POSIX_API )
#include <boost/process/detail/posix/basic_cmd.hpp>
#include <boost/process/detail/posix/cmd.hpp>
#endif

#include <boost/process/shell.hpp>

#include <iterator>


namespace boost { namespace process { namespace detail {

template<typename Char>
struct exe_setter_
{
    typedef Char value_type;
    typedef std::basic_string<Char> string_type;

    string_type exe_;
    exe_setter_(string_type && str)      : exe_(std::move(str)) {}
    exe_setter_(const string_type & str) : exe_(str) {}
};

template<> struct is_wchar_t<exe_setter_<wchar_t>> : std::true_type {};


template<>
struct char_converter<char, exe_setter_<wchar_t>>
{
    static exe_setter_<char> conv(const exe_setter_<wchar_t> & in)
    {
        return {::boost::process::detail::convert(in.exe_)};
    }
};

template<>
struct char_converter<wchar_t, exe_setter_<char>>
{
    static exe_setter_<wchar_t> conv(const exe_setter_<char> & in)
    {
        return {::boost::process::detail::convert(in.exe_)};
    }
};



template <typename Char, bool Append >
struct arg_setter_
{
    using value_type = Char;
    using string_type = std::basic_string<value_type>;
    std::vector<string_type> _args;

    typedef typename std::vector<string_type>::iterator       iterator;
    typedef typename std::vector<string_type>::const_iterator const_iterator;

    template<typename Iterator>
    arg_setter_(Iterator && begin, Iterator && end) : _args(begin, end) {}

    template<typename Range>
    arg_setter_(Range && str) :
            _args(std::begin(str),
                  std::end(str)) {}

    iterator begin() {return _args.begin();}
    iterator end()   {return _args.end();}
    const_iterator begin() const {return _args.begin();}
    const_iterator end()   const {return _args.end();}
    arg_setter_(string_type & str)     : _args{{str}} {}
    arg_setter_(string_type && s)      : _args({std::move(s)}) {}
    arg_setter_(const string_type & s) : _args({s}) {}
    arg_setter_(const value_type* s)   : _args({std::move(s)}) {}

    template<std::size_t Size>
    arg_setter_(const value_type (&s) [Size]) : _args({s}) {}
};

template<> struct is_wchar_t<arg_setter_<wchar_t, true >> : std::true_type {};
template<> struct is_wchar_t<arg_setter_<wchar_t, false>> : std::true_type {};

template<>
struct char_converter<char, arg_setter_<wchar_t, true>>
{
    static arg_setter_<char, true> conv(const arg_setter_<wchar_t, true> & in)
    {
        std::vector<std::string> vec(in._args.size());
        std::transform(in._args.begin(), in._args.end(), vec.begin(),
                [](const std::wstring & ws)
                {
                    return ::boost::process::detail::convert(ws);
                });
        return {vec};
    }
};

template<>
struct char_converter<wchar_t, arg_setter_<char, true>>
{
    static arg_setter_<wchar_t, true> conv(const arg_setter_<char, true> & in)
    {
        std::vector<std::wstring> vec(in._args.size());
        std::transform(in._args.begin(), in._args.end(), vec.begin(),
                [](const std::string & ws)
                {
                    return ::boost::process::detail::convert(ws);
                });

        return {vec};
    }
};

template<>
struct char_converter<char, arg_setter_<wchar_t, false>>
{
    static arg_setter_<char, false> conv(const arg_setter_<wchar_t, false> & in)
    {
        std::vector<std::string> vec(in._args.size());
        std::transform(in._args.begin(), in._args.end(), vec.begin(),
                [](const std::wstring & ws)
                {
                    return ::boost::process::detail::convert(ws);
                });
        return {vec};    }
};

template<>
struct char_converter<wchar_t, arg_setter_<char, false>>
{
    static arg_setter_<wchar_t, false> conv(const arg_setter_<char, false> & in)
    {
        std::vector<std::wstring> vec(in._args.size());
        std::transform(in._args.begin(), in._args.end(), vec.begin(),
                [](const std::string & ws)
                {
                    return ::boost::process::detail::convert(ws);
                });
        return {vec};
    }
};

using api::exe_cmd_init;

template<typename Char>
struct exe_builder
{
    //set by path, because that will not be interpreted as a cmd
    bool not_cmd = false;
    bool shell   = false;
    using string_type = std::basic_string<Char>;
    string_type exe;
    std::vector<string_type> args;

    void operator()(const boost::filesystem::path & data)
    {
        not_cmd = true;
        if (exe.empty())
            exe = data.native();
        else
            args.push_back(data.native());
    }

    void operator()(const string_type & data)
    {
        if (exe.empty())
            exe = data;
        else
            args.push_back(data);
    }
    void operator()(const Char* data)
    {
        if (exe.empty())
            exe = data;
        else
            args.push_back(data);
    }
    void operator()(shell_) {shell = true;}
    void operator()(std::vector<string_type> && data)
    {
        if (data.empty())
            return;

        auto itr = std::make_move_iterator(data.begin());
        auto end = std::make_move_iterator(data.end());

        if (exe.empty())
        {
            exe = *itr;
            itr++;
        }
        args.insert(args.end(), itr, end);
    }

    void operator()(const std::vector<string_type> & data)
    {
        if (data.empty())
            return;

        auto itr = data.begin();
        auto end = data.end();

        if (exe.empty())
        {
            exe = *itr;
            itr++;
        }
        args.insert(args.end(), itr, end);
    }
    void operator()(exe_setter_<Char> && data)
    {
        not_cmd = true;
        exe = std::move(data.exe_);
    }
    void operator()(const exe_setter_<Char> & data)
    {
        not_cmd = true;
        exe = data.exe_;
    }
    void operator()(arg_setter_<Char, false> && data)
    {
        args.assign(
                std::make_move_iterator(data._args.begin()),
                std::make_move_iterator(data._args.end()));
    }
    void operator()(arg_setter_<Char, true> && data)
    {
        args.insert(args.end(),
                std::make_move_iterator(data._args.begin()),
                std::make_move_iterator(data._args.end()));
    }
    void operator()(const arg_setter_<Char, false> & data)
    {
        args.assign(data._args.begin(), data._args.end());
    }
    void operator()(const arg_setter_<Char, true> & data)
    {
        args.insert(args.end(), data._args.begin(), data._args.end());
    }

    api::exe_cmd_init<Char> get_initializer()
    {
        if (not_cmd || !args.empty())
        {
            if (shell)
                return api::exe_cmd_init<Char>::exe_args_shell(std::move(exe), std::move(args));
            else
                return api::exe_cmd_init<Char>::exe_args(std::move(exe), std::move(args));
        }
        else
            if (shell)
                return api::exe_cmd_init<Char>::cmd_shell(std::move(exe));
            else
                return api::exe_cmd_init<Char>::cmd(std::move(exe));

    }
    typedef api::exe_cmd_init<Char> result_type;
};

template<>
struct initializer_builder<cmd_or_exe_tag<char>>
{
    typedef exe_builder<char> type;
};

template<>
struct initializer_builder<cmd_or_exe_tag<wchar_t>>
{
    typedef exe_builder<wchar_t> type;
};

}}}



#endif /* BOOST_PROCESS_DETAIL_EXE_BUILDER_HPP_ */

/* basic_cmd.hpp
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
*/