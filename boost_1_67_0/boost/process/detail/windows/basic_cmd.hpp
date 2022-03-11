// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_WINDOWS_BASIC_CMD_HPP_
#define BOOST_PROCESS_DETAIL_WINDOWS_BASIC_CMD_HPP_

#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/process/shell.hpp>
#include <boost/process/detail/windows/handler.hpp>

#include <vector>
#include <string>
#include <iterator>


namespace boost
{
namespace process
{
namespace detail
{
namespace windows
{

inline std::string build_args(const std::string & exe, std::vector<std::string> && data)
{
    std::string st = exe;

    //put in quotes if it has spaces
    {
        boost::replace_all(st, "\"", "\\\"");

        auto it = std::find(st.begin(), st.end(), ' ');

        if (it != st.end())//contains spaces.
        {
            st.insert(st.begin(), '"');
            st += '"';
        }
    }

    for (auto & arg : data)
    {
        boost::replace_all(arg, "\"", "\\\"");

        auto it = std::find(arg.begin(), arg.end(), ' ');//contains space?
        if (it != arg.end())//ok, contains spaces.
        {
            //the first one is put directly onto the output,
            //because then I don't have to copy the whole string
            arg.insert(arg.begin(), '"');
            arg += '"'; //thats the post one.
        }

        if (!st.empty())//first one does not need a preceeding space
            st += ' ';

        st += arg;
    }
    return st;
}

inline std::wstring build_args(const std::wstring & exe, std::vector<std::wstring> && data)
{
    std::wstring st = exe;

    //put in quotes if it has spaces
    {
        boost::replace_all(st, L"\"", L"\\\"");

        auto it = std::find(st.begin(), st.end(), L' ');

        if (it != st.end())//contains spaces.
        {
            st.insert(st.begin(), L'"');
            st += L'"';
        }
    }

    for (auto & arg : data)
    {
        boost::replace_all(arg, L"\"", L"\\\"");

        auto it = std::find(arg.begin(), arg.end(), L' ');//contains space?
        if (it != arg.end())//ok, contains spaces.
        {
            //the first one is put directly onto the output,
            //because then I don't have to copy the whole string
            arg.insert(arg.begin(), L'"');
            arg += L'"'; //thats the post one.
        }

        if (!st.empty())//first one does not need a preceeding space
            st += L' ';

        st += arg;
    }
    return st;
}

template<typename Char>
struct exe_cmd_init : handler_base_ext
{
    using value_type  = Char;
    using string_type = std::basic_string<value_type>;

    static const char*    c_arg(char)    { return "/c";}
    static const wchar_t* c_arg(wchar_t) { return L"/c";}

    exe_cmd_init(const string_type & exe, bool cmd_only = false)
                : exe(exe), args({}), cmd_only(cmd_only) {};
    exe_cmd_init(string_type && exe, bool cmd_only = false)
                : exe(std::move(exe)), args({}), cmd_only(cmd_only) {};

    exe_cmd_init(string_type && exe, std::vector<string_type> && args)
            : exe(std::move(exe)), args(build_args(this->exe, std::move(args))), cmd_only(false) {};
    template <class Executor>
    void on_setup(Executor& exec) const
    {

        if (cmd_only && args.empty())
            exec.cmd_line = exe.c_str();
        else
        {
            exec.exe = exe.c_str();
            exec.cmd_line = args.c_str();
        }
    }
    static exe_cmd_init<Char> exe_args(string_type && exe, std::vector<string_type> && args)
    {
        return exe_cmd_init<Char>(std::move(exe), std::move(args));
    }
    static exe_cmd_init<Char> cmd(string_type&& cmd)
    {
        return exe_cmd_init<Char>(std::move(cmd), true);
    }
    static exe_cmd_init<Char> exe_args_shell(string_type && exe, std::vector<string_type> && args)
    {
        std::vector<string_type> args_ = {c_arg(Char()), std::move(exe)};
        args_.insert(args_.end(), std::make_move_iterator(args.begin()), std::make_move_iterator(args.end()));
        string_type sh = get_shell(Char());

        return exe_cmd_init<Char>(std::move(sh), std::move(args_));
    }

    static std:: string get_shell(char)    {return shell(). string(codecvt()); }
    static std::wstring get_shell(wchar_t) {return shell().wstring(codecvt());}

    static exe_cmd_init<Char> cmd_shell(string_type&& cmd)
    {
        std::vector<string_type> args = {c_arg(Char()), std::move(cmd)};
        string_type sh = get_shell(Char());

        return exe_cmd_init<Char>(
                std::move(sh),
                std::move(args));
    }
private:
    string_type exe;
    string_type args;
    bool cmd_only;
};

}



}
}
}



#endif /* INCLUDE_BOOST_PROCESS_WINDOWS_ARGS_HPP_ */

/* basic_cmd.hpp
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
*/