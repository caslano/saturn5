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
Amsaoum/K69Qrihko3qXf3g/yqcA6D8FuYbAq+hbAcp7ri3fjylSAgviamtFZkrpI4CiZhdt81cqZdVTZmdX53ghD0LGx224a5BpkwiZMmWkB4MpW+ajttWuHsdHlkFfvBEDB9ITDPEVrpY2XpC9W0aWznLXA1lCgGnskC8eJaDWMJhqXFKvrq+5kYU3GPZ/db5SILW/SRldBPxBt9Rx4MYmyP6Z3nVdm0oRRPSoggQNdndqvy6hlGDOBZXo0GvaS4mN/+LJd50j1ws4dQd/DGQVzepWRwDszy81eqNGLIQVlEn1Gt/yyQbtmKEwI5gNTPd+g4d3ufSSaT/eWaP7Bcj1H2rEFgJbERBlEI8HR8jE/GlbicZSyq+usqlbrJYaDxWqrKb1XayCYWBV4NK2PtwXI8mMlk4CTUB5Ym/kW/L6kxr4tmnnHJWpWx1kbkksBxPmsG934lJYWeu4CoQpXfZCXCVtV2/l+XVnQskSlBfsAZ37sZQHzD5VCOq4vbD1ecnB+LQ4BAKiBkQFyrFGtMI0OJQnWWr0bR76nuZ26lX/bhUpYYMpKoF7/g==
*/