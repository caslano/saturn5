// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_WINDOWS_CMD_HPP_
#define BOOST_PROCESS_WINDOWS_CMD_HPP_

#include <string>

namespace boost
{
namespace process
{
namespace detail
{
namespace windows
{

template<typename CharType>
struct cmd_setter_ : ::boost::process::detail::handler_base
{
    typedef CharType value_type;
    typedef std::basic_string<value_type> string_type;

    cmd_setter_(string_type && cmd_line)      : _cmd_line(std::move(cmd_line)) {}
    cmd_setter_(const string_type & cmd_line) : _cmd_line(cmd_line) {}
    template <class Executor>
    void on_setup(Executor& exec)
    {
        exec.cmd_line = _cmd_line.c_str();
    }
    const string_type & str() const {return _cmd_line;}

private:
    string_type _cmd_line;
};

}


}
}
}



#endif /* INCLUDE_BOOST_PROCESS_WINDOWS_ARGS_HPP_ */

/* cmd.hpp
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
*/