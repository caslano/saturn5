// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_POSIX_BASIC_CMD_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_BASIC_CMD_HPP_

#include <boost/process/detail/posix/handler.hpp>
#include <boost/process/detail/posix/cmd.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/process/shell.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/join.hpp>
#include <string>
#include <vector>

namespace boost
{
namespace process
{
namespace detail
{
namespace posix
{


inline std::string build_cmd_shell(const std::string & exe, std::vector<std::string> && data)
{
    std::string st = exe;
    for (auto & arg : data)
    {
        boost::replace_all(arg, "\"", "\\\"");

        auto it = std::find(arg.begin(), arg.end(), ' ');//contains space?
        if (it != arg.end())//ok, contains spaces.
        {
            //the first one is put directly onto the output,
            //because then I don't have to copy the whole string
            arg.insert(arg.begin(), '"' );
            arg += '"'; //thats the post one.
        }

        if (!st.empty())//first one does not need a preceeding space
            st += ' ';

        st += arg;
    }
    return  st ;
}

inline std::vector<std::string>  build_args(const std::string & data)
{
    std::vector<std::string>  st;
    
    typedef std::string::const_iterator itr_t;

    //normal quotes outside can be stripped, inside ones marked as \" will be replaced.
    auto make_entry = [](const itr_t & begin, const itr_t & end)
    {
        std::string data;
        if ((*begin == '"') && (*(end-1) == '"'))
            data.assign(begin+1, end-1);
        else
            data.assign(begin, end);

        boost::replace_all(data, "\\\"", "\"");
        return data;

    };

    bool in_quote = false;

    auto part_beg = data.cbegin();
    auto itr = data.cbegin();

    for (; itr != data.cend(); itr++)
    {
        if (*itr == '"')
            in_quote ^= true;

        if (!in_quote && (*itr == ' '))
        {
            //alright, got a space

            if ((itr != data.cbegin()) && (*(itr -1) != ' ' ))
                st.push_back(make_entry(part_beg, itr));

            part_beg = itr+1;
        }
    }
    if (part_beg != itr)
        st.emplace_back(make_entry(part_beg, itr));


    return st;
}

template<typename Char>
struct exe_cmd_init;

template<>
struct exe_cmd_init<char> : boost::process::detail::api::handler_base_ext
{
    exe_cmd_init(const exe_cmd_init & ) = delete;
    exe_cmd_init(exe_cmd_init && ) = default;
    exe_cmd_init(std::string && exe, std::vector<std::string> && args)
            : exe(std::move(exe)), args(std::move(args)) {};
    template <class Executor>
    void on_setup(Executor& exec) 
    {
        if (exe.empty()) //cmd style
        {
            exec.exe = args.front().c_str();
            exec.cmd_style = true;
        }
        else
            exec.exe = &exe.front();

        cmd_impl = make_cmd();
        exec.cmd_line = cmd_impl.data();
    }
    static exe_cmd_init exe_args(std::string && exe, std::vector<std::string> && args) {return exe_cmd_init(std::move(exe), std::move(args));}
    static exe_cmd_init cmd     (std::string && cmd)
    {
        auto args = build_args(cmd);
        return exe_cmd_init({}, std::move(args));
    }

    static exe_cmd_init exe_args_shell(std::string&& exe, std::vector<std::string> && args)
    {
        auto cmd = build_cmd_shell(std::move(exe), std::move(args));

        std::vector<std::string> args_ = {"-c", std::move(cmd)};
        std::string sh = shell().string();

        return exe_cmd_init(std::move(sh), std::move(args_));
    }
    static exe_cmd_init cmd_shell(std::string&& cmd)
    {
        std::vector<std::string> args = {"-c", "\"" + cmd + "\""};
        std::string sh = shell().string();

        return exe_cmd_init(
                std::move(sh),
                {std::move(args)});
    }
private:
    inline std::vector<char*> make_cmd();
    std::string exe;
    std::vector<std::string> args;
    std::vector<char*> cmd_impl;
};

std::vector<char*> exe_cmd_init<char>::make_cmd()
{
    std::vector<char*> vec;
    if (!exe.empty())
        vec.push_back(&exe.front());

    if (!args.empty()) {
        for (auto & v : args)
            vec.push_back(&v.front());
    }

    vec.push_back(nullptr);

    return vec;
}


}}}}

#endif

/* basic_cmd.hpp
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
*/