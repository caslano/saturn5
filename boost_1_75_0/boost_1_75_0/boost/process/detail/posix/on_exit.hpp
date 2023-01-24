// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_POSIX_ON_EXIT_HPP_
#define BOOST_PROCESS_POSIX_ON_EXIT_HPP_

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/handler_base.hpp>
#include <boost/process/detail/posix/async_handler.hpp>
#include <system_error>
#include <functional>

namespace boost { namespace process { namespace detail { namespace posix {

struct on_exit_ : boost::process::detail::posix::async_handler
{
    std::function<void(int, const std::error_code&)> handler;
    on_exit_(const std::function<void(int, const std::error_code&)> & handler) : handler(handler)
    {

    }

    template<typename Executor>
    std::function<void(int, const std::error_code&)> on_exit_handler(Executor&) 
    {
        return handler;

    }
};


}}}}
#endif /* BOOST_PROCESS_POSIX_ON_EXIT_HPP_ */

/* on_exit.hpp
aq8Vo0phh6/1Ejw/BcwTbIQk9aGZkpDwdTR3vZF4ppbOadEVkk2w2+c1Qh68sZov7ymgdlaW52+FfdU5SDfBuKKHcV9Hd0U8vKBXjInJxDwOtJFV+x2NKmd1G21ZVMvWArJ8CBzOBLJKzx0OS1rvyTYGf/HEn+UntOLtU3+9K4s1aJyS60B6btIJvTY49QoY7YTS25Z7NhdpOEhMkzUkIzuZRhK70FNIFXaETk3gukXsmlfPmt4kVriFZ6y7/7TpdU6R02SBQCARWM2QLV1doUJjZTs7C84lTvYZ+/Vr2jZIS63k7da2KQvHiAJpR9pfO76RkytkMiBmzF2znXCidGoYDcnR0YJZ9HfU2D8N8FyKbKQL47RhFdlmjNzoKJK3eqvF9zFdnLAt5rqy8A2xRED6NNZP+Pb7xSX/MsDTVZqq8cE8lYeWzN0WfGjT3ji7fIDN3exqx+MT72EH5eNxe8rWaXl6uz6gOyCk44cZ99H6Htukp3iFvV49YeJDBBbszyBuY+di/MBc1oUfEk0Se64YItCCv2e4DByVeR2UFfobg+QalHDic9sy7Gp+DrYSsD91FuYoI+v6kAHeJOGI+zTpNfzd7kGWxr59eJpH1LDYIa62fhZtyvOjrj2QY1s/Rif+gtH/l8S2PkqQcRdDiPucXSMefW2r3nMgBdkNoYahQR3A3MSl1QDa27tIcgCutb2QSQzorfehKDZU
*/