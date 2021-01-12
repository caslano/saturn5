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
qj3726ACQRCxp3nexRa/WlW2dbtdaVsHshOCEkuWNnsbW15BbZ3si3j2652YTDhS8hPWWYQnmgTPZ1fx+B+On+otdqsNe7Ba6L9F1hjVpkHCG+8nzxlKOhsW/oLD3R0A/upzADwULnDe4AsQoUzGpF8OCFHbZQM+1rMYK+Mv0/tCZnZz8OQB2mo9F/MLuwKFI4vn18O9iGZtvAXU3qVDdb9e3i8gvBHmXDwx0BDrzFTLPv3A
*/