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
YhRa2RfvR39BkzYeMIi8utBgVFhfEOAybOjQzrqltNNHFIOjPNMO24F8V4Xb2LxBhwVzxoBGEncyPlNeA7jYeHFTMCK6oz0v/gCpAy17CsjE/1WgjQ0hEqEHdCnzdtLaozKhAfA8Bohun9dQUE4YXrQrhq2+LzFjuTzbDYraHpLEHfQb0woDQNU7X+V1kcoWk/wm6lmyU6GINgTNwoaTA3keCM8mob+f97zn3CV8allV/DD4P4FKOBdzxrkKqA6ycWDYbzwEBLoPDzXNuu0IR1SXyNWiFrZ1lN3WvqSFNBEX4AyyFbS3hiCyIyoWn9PFS/AVuZIkG0l/NJ3+wM1iAGc8VnP+0FykbYIScjv7VaaczGtgH/az73kyXouSsRsN1LpDW1MUUaJOJ8zK6+pHc1+qKrm9RV2D5hTSL65Quim4Fz/OTREWI3Jmh2ouWiJhiPBAqGO6e7nSSfBVkxqo5eqGFdMHWvNQ0UCyOfIEZzQFcklnuIgW7cXpToiahjUhiFQk3UDVKXnicQcE1hskiL1xunI8fsyGvMusqOlstdQ2PAP6MegsxOGwjA==
*/