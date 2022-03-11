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