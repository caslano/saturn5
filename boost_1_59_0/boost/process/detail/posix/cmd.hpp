// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_POSIX_CMD_HPP_
#define BOOST_PROCESS_DETAIL_POSIX_CMD_HPP_

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/posix/handler.hpp>
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


template<typename Char>
inline std::vector<std::basic_string<Char>> build_cmd(const std::basic_string<Char> & value)
{
    std::vector<std::basic_string<Char>>  ret;

    bool in_quotes = false;
    auto beg = value.begin();
    for (auto itr = value.begin(); itr != value.end(); itr++)
    {
        if (*itr == quote_sign<Char>())
            in_quotes = !in_quotes;

        if (!in_quotes && (*itr == space_sign<Char>()))
        {
            if (itr != beg)
            {
                ret.emplace_back(beg, itr);
                beg = itr + 1;
            }
        }
    }
    if (beg != value.end())
        ret.emplace_back(beg, value.end());

    return ret;
}

template<typename Char>
struct cmd_setter_ : handler_base_ext
{
    typedef Char value_type;
    typedef std::basic_string<value_type> string_type;

    cmd_setter_(string_type && cmd_line)      : _cmd_line(api::build_cmd(std::move(cmd_line))) {}
    cmd_setter_(const string_type & cmd_line) : _cmd_line(api::build_cmd(cmd_line)) {}
    template <class Executor>
    void on_setup(Executor& exec) 
    {
        exec.exe = _cmd_impl.front();
        exec.cmd_line = &_cmd_impl.front();
        exec.cmd_style = true;
    }
    string_type str() const
    {
        string_type ret;
        std::size_t size = 0;
        for (auto & cmd : _cmd_line)
            size += cmd.size() + 1;
        ret.reserve(size -1);

        for (auto & cmd : _cmd_line)
        {
            if (!ret.empty())
                ret += equal_sign<Char>();
            ret += cmd;
        }
        return ret;
    }
private:
    static inline std::vector<Char*> make_cmd(std::vector<string_type> & args);
    std::vector<string_type> _cmd_line;
    std::vector<Char*> _cmd_impl  = make_cmd(_cmd_line);
};

template<typename Char>
std::vector<Char*> cmd_setter_<Char>::make_cmd(std::vector<std::basic_string<Char>> & args)
{
    std::vector<Char*> vec;

    for (auto & v : args)
        vec.push_back(&v.front());

    vec.push_back(nullptr);

    return vec;
}

}}}}

#endif

/* cmd.hpp
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
*/