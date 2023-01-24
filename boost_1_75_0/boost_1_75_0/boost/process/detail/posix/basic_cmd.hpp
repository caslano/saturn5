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
nwogvCiHHT14HmUfZzHvCdAGPrmIoO4EoO0aiHQZ9bs+kiPu0PcFYv/MCrumaAPTOG1G5lGc5sDjyBj9UfH7lnfM/LDIuZvmPWGZNtGNVDtfea/ptRT+lr+UcWHxgr2tz+A6gv22oPUT7IA05z+6opZKEkQCVXcjrKGC+nthD1nmzv4LomfEdjb0oVUVXl6wIFr9FUrrk6Sodc7aB8+wG9e04zfxQccZrzUKzsEJ/+lh56PwG++byCVIfdYrxQXvBfuylcAgErdJ3U1AoNQgTnnFsihlfUifJjtauVVpR6U12t6t8hWC3Sx2l79DDaIUvJMFS5qkyhi2Ims7RBDsflyNw73P4C/Rf4O7C4L6IN8Np3hFSYvmqZ1SULHLs+p7DdKGm2U7iX2klbpth+rSCBJNgWggQWTx74EwouszgviqQDBsh0yXuwG95/SJbkJwirxCIzbPlob0lbagmG9w2Oss2264OQjkn4iUGsQrzzw+NNinnGbMzRUrbiJkL0qQOMDbYbvvs/xMsYK/fJjInp3zEPuI8ojpbthEoLTD6RwKqMevkxHxFJO8TLgsm2VLdN3GDiRG6KlxU/YIsWQpLxPBByzTZqkPeXINoGG0YQ1xCiidSq59vGVO+GIXEBS0bTNc4zzB2mFU73O/eZpsUlxjTO3ai4AsbYv0NUymsTNdqY83yQjYLrr3E0+/5UBU7naDEVfhVqmuYey+
*/