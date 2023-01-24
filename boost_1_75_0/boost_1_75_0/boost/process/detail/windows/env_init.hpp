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
/TptFirC30jYzrPbSuBBbLBcKR4gNY9zZTrv4IbxkLXsVRDOaxhDXIXhZLKIMBJtKrf72FZl0Eu/K9pw6sSCw08FzW6sWV0WqAxNJB8Hu+N+vQq6X0j0sKoZ8/0dNG+wdwQb+uBGz7XcTrXr9mI0C2iyRlhvw7M/dLR3r32jh56Vwhc8acrgiftJdQmD5SnFXYWJYKKH/X3s6wkr8RreysHIw21+zq/zucX5xXW0Ra+lZ76GEI1aBv1ruhTrSCoO7bFn1APtHbD20IN+zdWxNbfrW2pUlr7BzhistfWzJLfC2yL1O9g34PFjY7D/Q8E6cwyWTwH9A8wp/fpBbwHrFW3z+kFAiKS987G0s/2hH+ArumA4YPH6IUgMPWmw84HvvL7r5P0q7KXz+lEq//px3PT4QdWgy7Ck8fG9IXv+vW7gw2mpg/Lusq5kB8vao+GqU8CCZmU+TGi4ptOsc9Jo50Ny6RnYs88XYTOLNpAFrtp5uDoQHkyr38Gd5d3glyBuYIeYrLJdCfcyPnoER3unpa4880W8o8yVZzSEDayTro6ZXIEJCWsT3vIRZ33AU1zn3pgA73HD7UcKIuoGVftUjcaI3j66mOoLaD2TDQCj4QaD1NIDosDiAyLBfXuAPxNFjE+V4kiHcLEDXkTWRq7VU8wbyZZCDfApKxcJa6qze89XkFu/OuxIfLvzQiDMC+sDRPP8gfLWOuFG9kxT
*/