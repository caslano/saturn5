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
3z9jqMn0XaGCgfya+vG7ouHi89CectWlq9qyjPw1rnYfa5CUv56mmvWGHCmh3hhN3LMM8rKaVNgYox/SJcrdrevYrh6s3+2D8E2JEEscKZ4uyc5jkPH6t8B86nJ7ZzAxUoItJeRSCAdyCcCZ+tJjGXAhxvuV0RkuoRBk6IUja08WL6uGoTExzVTnYb3s6WUR1Fj2s0WF00bOnI5he24HCauq5nclyIz1OyZv4hQH38/CAe0iQgxIASuKDJWFtlq7PMvcVJfKo8LSU30HCepfbQ31aonIZgJRWA1wMM0+x8uXcmp7Zy6HhtiQlD2FgHxr7aOrKjwaPwryzE+RLwzj9RwJ7iZSMPk7Zed+hCIfkojuYXFtqsDaauZyK2YoKoCV725M+2WIdyUGadrpSjJrRnokyjloPtJa1DS9M6frYJ74etxZ9Znq52kQLjtGxu4xWcJEL+FfhWl+4jhna4fvpRTktrFHu32EWTo1YTYTfOosw9xv6C59CU1f/prpVdpQk2adF9MnrXa0GZOeVQ/+o/Juc5J7P7jO2/2vHJztkg8FHBqvo1bpV0teeBkTtGn7oIi3LH8ZYjT/HfnTdylNJtv5S6XuzaGExJ2ZfFVmhlLanBQdsLqk0naFRd9579owIfz3bpGmCF+OeH+WJ7M+fmu8nok2INYCei3JQTV+EaXtWEMqAzR//zHelF+8icJuxChDPgXf6a/+lR/w
*/