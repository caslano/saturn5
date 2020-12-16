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
H+IcHxnzQ46DiJFTXOvazqm4TKkblmIiL/6EC9iuE6nnVFR0lBi13TYGN7E+ET3k+PO2OpLvZ1nzWseXzmt0rlGW0bjnA6OGRRrfKyTza+tU56g0PpdO2J/LtvH3Dc8l4/xy2GN1XOxvRZ7hhueXtryc20eO60/tg+E5diL9z5o659L3Is+XJuvyeXXL59Utn1kdO12bf+xLceyzivX665bz1y3ny3KrcorlxIDMXaKY6VAemyK6ZYpoy+jGPufd19WnXRevnzbpxuJWj9kwsS251TrPk+L5bcM5QVm3qKu0m5NQPac2iWX9OVfzqvMo3xTr/sJ0kOgVkt1nVv3eajdb9I0S53lmkjcpN6WUR1v/m+UiT3ZdnSXndXRUmjlDU8Q25HhmmQ5KB3G83tDNE/QFyTa298dy/p6WHJTKpFZyHG8Lr4Via1IbUltSO1J7UmHSEs9/Poa3tU6M7VDrxHz1Y2irn02jcb3F581uvnv5udJ9pxjNX+Fji2ufE3W+e/28Fpz/Ip7X4HvMg7i/Oj54JO+Hlzj3OC95rj8vtTHA7efM4P1U2xgm5lTEo6srnzHpA15JFsdmtPwFZTT3vXaOHZwjxnDnDAtQ3+PSb1tjXrJ9QZZH6fdctDYAGTduXxBtB8bLaXHjee698No80TeOvINEWWc5DmfEMo1cvxFlib+tqf3DuqSdXzdwvvZdsIbl0uZNO5/kHyIvnwr5/RMs9jvauY8ywqmOc1Gx7u2UUTbRGk9xGedi/52gtRUkibJ+5D1vJ5bbwHKKWM7fdZvLs+0Z+eVy40WeS5bdymDGYsmvBFhKKIMtHmq/wlpim751NjOyUG1zdlN7S24z5Yu5RiaLZee4FHdJ/V6cZdfGMUO8XpH8vmajNpdk6/kl8mx2qeOi/WYRcwzL76cLatuCdrz5+6muo73Y762cl++qfTC7i9gAJQ+/2nsoZrGu05QTJNZ13WW4S5r5JCMjY8UHTawvJc36bB9Zbd6JHuLceKKU5ddwLGfIcaWM+j2qfcey/fIzbdvOz8T5c8hpGw1Stvav63OtsRli1tb8IkZrmzjew529Gdm0r6UW40YGKI+cwsQ+HGMdfmIf3FwXyn2IEdsZPjC6HHNeDIwU+ZaQr4jI99hlhu29l8d+sDz2i8lTTOR56DJFPR5y260HWOY7Qb6aqeeIy0AXw7nB1XYcH5HP3XWpPp/ue4l8ok0gr8jn5DqXfOnMoy3a4/5sDve14thllu+57bilmLMwctJRs4dY12bKGCHWtdIlkHUZzsst27gyi3y+rmv126R+d2pzV94Q7+Mw5w6mOKWGc2kl1tlJnbejjtiGb5xjGF01xtkkyl5G2WGi7IMubV3U31PyvBN/btXPv1nk22YpZ4pnHNn8rFN/TtzmnPA3h5jDGdvpmDnN30z5ftn+RruLcto6B7KNrzqXkXPya9vXXxljyU8F+TkGO2I7n+nfW0ie6yI/OaIZfSnMUllZbFnO790hjMFTQOzbSvbNlieOkap8bdtk97eEvGIOol5iu3a6NHbhSIvrAt33otgHbR7tvAvEvDHiXNjJsvZzBCcRuyPei9dc9+uPq91vY288If7GxPO8vPzuTfs35hJlDRHbtsaliu08sbUpRwzqx/9FvqXk8xf5FNfZ5LP/7VNCnptvpn6vm3IqnqwxF/Xa2akTzqsc4Z34he8Ms8lNmx+Fc5GzQP2euCS2tR/fWpUM/x4eZBvixDZscKmhP1e13wXqexMh8iW5/GZpY7bv1277DnpffI5aU1fvJ89D+Z3P++nE+Vab803X/1z9e/OhWC6EffaTMdtytc3WvxXa/vG51f19/ER+brW5bPm+ETMCads=
*/