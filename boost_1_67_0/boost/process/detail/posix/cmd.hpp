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