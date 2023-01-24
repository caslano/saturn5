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
FZBgv9fvweVhxGx632NKOmFwmwaARF+k9eNH+X5dI3BIVglrv2fYRGR3tl4Xrb1TT01CGpI/UkfbghUuFDpNfkjmejsCpSEK9d7bLhxLNtev1LpX6Blmd+BrwWohaBJT4TDrN4jgiTTH7xci45OP+Zt3/KYVz3eOegdBG45hFzc/84vDseh3EtR0WMwAXyRPhFvW1jcK7rfvUxJTCWTh8mAYTsAtS07Rok/Q0+lTrYFJ3C1pQKYGgoiwQYxP0HsmwqST2YuSGqj6y94kXHs/CWjEm+gW0IAKqr2jfgIOzO8gNGRzLPK/Bo07wZWZL04WnB6gLbUkeEvpM34C9u0fwEg21TzF3+gsvprP3GUh7GTzfaA5E5PkrbxRrgxoWhMMH+hOEVoD4xcF102Eg63fQT/PPIKZDiRPa3Zr/d68g4H3SvcCT69sK+/mi66C3XqBRYu3YNh261mzd8+RKEzGonzCb9ugDdzmGxiGhSsqHVA4TVIY3Tlch0iXi/4gVmVBU7ZRHK46IxY74VeZZ8bB5xuG50EUX6EAiHBPTO88vjbpMr/TSa92GtPPhmPN4j3AFNZFj9yFx6EhTyr5O46Zzi4iU9jeOaTGab8bXzKlb4K3d62TMnmnlXLekUDIzeva5NNRiCxuRJByy8TkjGn89dBDsBVlouJI+cae9IKSUYc9k7qcD/VOBB0as/4hHabXVb53nP1EJl+Z+yf8
*/