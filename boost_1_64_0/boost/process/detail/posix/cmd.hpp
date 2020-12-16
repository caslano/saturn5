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
XjFlmYlzTh1r4b7I/9h8VJ7T3cS2iiOi9h/ZKc6HnOrcrufF83byPNLeZzfGtIw31VXHIbDFSysXRNkRqWXH9h2o9WPYLco6rBSgPBHTlWfdVjmGha6ss4rdvPniHL0lyqmn5LY/97TPmtiGM55yGxRFPd+biWMeoJ7LweJ5LSUTsfzMtTnPxDW5tQ6Ng+FuGvuqu5vF3dTG3c0syujghczfqZvDUy7zkGUqWJfJPLam/RyetnJL8RWxMbsod44ot8o/LzeEZTZZl3Edu8q+3Mk8L2jfvv4c43rO90o77+d+nIVdvdW2bRGbwAGbSBpCfBJ6eMn5OPn/FDl/5wpivb1T26xLPce4BeIzbJtPc8yzc072GvNse3E3Laa224ZpMbXdNnTMs+3KDbWY2pZbXYuVtcWCxjzb1pxPi6nbt1GLVbS1AyeJmNbOmzjmr7Xz/tnYAhf+bEyAv9BeatwumvF7wF92e2m/CGt8eOuD4eeeDg4O7Zv521cfVOmUXjtextvr/m7tn8btmem1T2Z8DISMthtntD3TuB07/XZO4/bt9No/02/H/lWM7Ske4rs7AcNJfN+K/18hVdDFN+nid0nLzPK3pfztexZbkBJldVsZOY5pWfTDQIzAIIzByjgS6+IcrIfzsAEuwka4BJvgu9gU12Jz3IohuB1b4ofYCpOwNSZjG9yP7fBjbI9HsCMewzD8DDvjFbldP2I3TMHueB+rYRZ2sjpmxZqYG/dgXkzGQrgPS+J+DMADWA0PYh08hPWxB3bCnhiOvbEH9sHh2A+nYzTOwv64HGNwMw7A9zEOj+IgPIlD8CwOxe9xON7BUfgYR8s23LGYA8ehH8ZjYZyJr2Ii1sS3sQnOwRY4F8NwPkbgQuyDi3AQLsbRcvlZuAzn4ApchStxE67GnbgG9+JaPIrr8LTMfwXfwx9xK97DbfgQt8vxCT7ALLgTs+Mu9MPd6I+HkHb/P23b8uH5ZlaazP+P4SVSWce4sC+lrcsxrsD/fvuWo23r39u29fi0o23L8XA8HA/Hw/FwPBwPx8PxcDz+Fx7/YO9M4KOozgA+u5uTLJCEECBcAbkExHCDKHeAaEBKAgKiIZAAgVzmgHBYsSCgVYtoFQUUERUPKlZUUFRsUWmLVq0HVvHCW6qAF1qV/vfbb9/MbgaF3v01y+/xz/ve9+43b97MvONf/v2/e4/ABIB/+Pv/EZfv/8givv8jc/n+j0y//w/LGjsqE98qd3y/H5Y5LjfHEUa8/V3fyBKCYYwakjXG+E9UvaxcwnX4b6zy4Zk5RtZMZOOGjBlu66XpPIOzMieZMJuLLJCiEVnZmbZui2CYQ0Y7ZK3VvzPudOd+BCprE7kfgcrbGnm4frtgGoaMHZI7yqnfXuWSMoe8g+ZXfRh5R5WrDyPv5DIfArnrfIirZD5EQ2mji6Mt+b3l4TkY7oNWy8AztcyHyC+eqV+edT7EG40s5Iixu+1tIP74l4zul/JxLF/OXrRU/9ujEevQZRm6/T28TPxP8DxrlZq1thvmyDmItJdhkgZvS/XrWLv8hOh0Md/QD4r9FNHvkyTpKCOmQBrkW7d+Lzfpq5pfXhhK4xFnGvncNV3TGPp2/JWkMUbCjgqlpYe93v1ecf9W7aG0dA3b832GI99JcILonMR11VTCjZFw5xTMcORxkOhMdy2XBXwjDXhZpd8yW+k3zqv5+xqMyg2/T7R1fqk6Trdr4Tx4HVyNuV50bPkN8C2IkW+ifsv+xUV+E+Vboa9YvjkUlJUWmu+EgbbUWNsS3/6kbdBmkNltBl2prz5JyLUO05AdMd8Jw+pPvhWepnN9rHr6nYSIE5RNKKQMScviguqS8uA8iTw=
*/