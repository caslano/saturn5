// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_WINDOWS_ENV_INIT_HPP_
#define BOOST_PROCESS_DETAIL_WINDOWS_ENV_INIT_HPP_

#include <boost/winapi/error_codes.hpp>
#include <boost/winapi/process.hpp>


#include <boost/process/detail/config.hpp>
#include <boost/process/detail/handler_base.hpp>
#include <boost/process/environment.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

template<typename Char>
struct env_init : public ::boost::process::detail::handler_base
{
    boost::process::basic_environment<Char> env;

    env_init(boost::process::basic_environment<Char> && env) : env(std::move(env)) {};
    env_init(const boost::process::basic_environment<Char> & env) : env(env) {};

    constexpr static ::boost::winapi::DWORD_ creation_flag(char)    {return 0u;}
    constexpr static ::boost::winapi::DWORD_ creation_flag(wchar_t)
    {
       return ::boost::winapi::CREATE_UNICODE_ENVIRONMENT_;
    }

    template <class WindowsExecutor>
    void on_setup(WindowsExecutor &exec) const
    {
        auto e = env.native_handle();
        if (*e == null_char<char>())
        {
            exec.set_error(std::error_code(::boost::winapi::ERROR_BAD_ENVIRONMENT_, std::system_category()),
                    "Empty Environment");
        }

        exec.env = e;
        exec.creation_flags |= creation_flag(Char());
    }

};

}}}}



#endif /* BOOST_PROCESS_DETAIL_WINDOWS_ENV_INIT_HPP_ */

/* env_init.hpp
Q+2u5OkjUSPv8UOEvUZ3ujAmHWGJAQSgwxMJIRV7RpHjeggCrK4+VICQv43PrRZbBL+a/TG4Y/JI8r5PMXEkCU3stugM4MUnSd5oz1LLGPOR93UvK3hov2jCzMRto3sQUTT8t+IewcUVARLjRg9L9nyL2oFN2GjtnPonyqfEqHQsdTdvHBM1SlQpeEb96lcI5htRZCkTqf5J2F6umfe+1wnzKQRSUZMv7EBoRk1+dgI9CrAA
*/