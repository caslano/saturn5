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