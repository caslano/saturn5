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

    //put in quotes if it has spaces or double quotes
    if(!exe.empty())
    {
        auto it = st.find_first_of(" \"");

        if(it != st.npos)//contains spaces.
        {
            // double existing quotes
            boost::replace_all(st, "\"", "\"\"");

            // surround with quotes
            st.insert(st.begin(), '"');
            st += '"';
        }
    }

    for (auto & arg : data)
    {
        if(!arg.empty())
        {
            auto it = arg.find_first_of(" \"");//contains space or double quotes?
            if(it != arg.npos)//yes
            {
                // double existing quotes
                boost::replace_all(arg, "\"", "\"\"");

                // surround with quotes
                arg.insert(arg.begin(), '"');
                arg += '"';
            }
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

    //put in quotes if it has spaces or double quotes
    if(!exe.empty())
    {
        auto it = st.find_first_of(L" \"");

        if(it != st.npos)//contains spaces or double quotes.
        {
            // double existing quotes
            boost::replace_all(st, L"\"", L"\"\"");

            // surround with quotes
            st.insert(st.begin(), L'"');
            st += L'"';
        }
    }

    for(auto & arg : data)
    {
        if(!arg.empty())
        {
            auto it = arg.find_first_of(L" \"");//contains space or double quotes?
            if(it != arg.npos)//yes
            {
                // double existing quotes
                boost::replace_all(arg, L"\"", L"\"\"");

                // surround with quotes
                arg.insert(arg.begin(), L'"');
                arg += '"';
            }
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