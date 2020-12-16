// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/**
 * \file boost/process/config.hpp
 *
 * Defines various macros.
 */

#ifndef BOOST_PROCESS_DETAIL_CONFIG_HPP
#define BOOST_PROCESS_DETAIL_CONFIG_HPP

#include <boost/config.hpp>
#include <system_error>
#include <boost/system/api_config.hpp>

#include <boost/process/exception.hpp>

#if defined(BOOST_POSIX_API)
#include <errno.h>
#if defined(__GLIBC__)
#include <features.h>
#else
extern char **environ;
#endif
#elif defined(BOOST_WINDOWS_API)
#include <boost/winapi/get_last_error.hpp>
#else
#error "System API not supported by boost.process"
#endif

namespace boost { namespace process { namespace detail
{

#if !defined(BOOST_PROCESS_PIPE_SIZE)
#define BOOST_PROCESS_PIPE_SIZE 1024
#endif

#if defined(BOOST_POSIX_API)
namespace posix {namespace extensions {}}
namespace api = posix;

inline std::error_code get_last_error() noexcept
{
    return std::error_code(errno, std::system_category());
}

//copied from linux spec.
#if (_XOPEN_SOURCE >= 500 || _XOPEN_SOURCE && _XOPEN_SOURCE_EXTENDED) && !(_POSIX_C_SOURCE >= 200809L || _XOPEN_SOURCE >= 700)
#define BOOST_POSIX_HAS_VFORK 1
#endif

#if (_POSIX_C_SOURCE >= 199309L)
#define BOOST_POSIX_HAS_SIGTIMEDWAIT 1
#endif

#elif defined(BOOST_WINDOWS_API)
namespace windows {namespace extensions {}}
namespace api = windows;

inline std::error_code get_last_error() noexcept
{
    return std::error_code(::boost::winapi::GetLastError(), std::system_category());
}
#endif

inline void throw_last_error(const std::string & msg)
{
    throw process_error(get_last_error(), msg);
}

inline void throw_last_error(const char * msg)
{
    throw process_error(get_last_error(), msg);
}

inline void throw_last_error()
{
    throw process_error(get_last_error());
}

inline void throw_error(const std::error_code& ec)
{
    if (ec)
        throw process_error(ec);
}

inline void throw_error(const std::error_code& ec, const char* msg)
{
    if (ec)
        throw process_error(ec, msg);
}

template<typename Char> constexpr Char null_char();
template<> constexpr char     null_char<char>     (){return   '\0';}
template<> constexpr wchar_t  null_char<wchar_t>  (){return  L'\0';}

template<typename Char> constexpr Char equal_sign();
template<> constexpr char     equal_sign<char>    () {return  '='; }
template<> constexpr wchar_t  equal_sign<wchar_t> () {return L'='; }

template<typename Char> constexpr Char quote_sign();
template<> constexpr char     quote_sign<char>    () {return  '"'; }
template<> constexpr wchar_t  quote_sign<wchar_t> () {return L'"'; }

template<typename Char> constexpr Char space_sign();
template<> constexpr char     space_sign<char>    () {return  ' '; }
template<> constexpr wchar_t  space_sign<wchar_t> () {return L' '; }


}}}
#endif

/* config.hpp
ny67Vf7PcnFWEbwLxsG7YSV4D2wC58Nr4TrYDC6AHeF9sAe8H/aBD8ARcBHMUvqj4UPwdvgoXAAfg+vg43AjXAq3wWXwIHwSfg5XQH86rIY+uAaWgmthRbgOytk9xtpuOAeTEnR2z+c8jzr8Cnrht9AHf4CV4WnYEJ6BTeCPcAg8B9PhzzADnoR58Hso6WqsS4bbMcHper2qR2+AYTBN+T8cJsJ0WBZmqHBkwlowD6bCUbARHAM7w2zYHebAXnA8zIAT4QiYCyfByfBmOBXOgDfDR+BI+AS8Da5U/qyCWXAzvBFuU/J8OMBYHwwrqviF2d7ZyPL8rASjYWVYXF2XglVhWVgNloNVYAW5tp7jocr9DQ7PsYv89TMERkAPjFbXieq6GSwK82AUfEDJH4XRcDmMgU/COLgK+uA6WBw+D+PhdlgS7oKJcC8sDU/AFPglLAdPwvIwH1aAZ2FFGKkTb1gUVoEJsBmsC1vBhrAtbAvbw56wAxwIO8KRsBO8DXaDd8Ee8DHYU/k3yljbB9diUoLOxPpCpdfXMAV+A7vA7+Bg+D3MhafgX2A+XARPw8Xq+hm5tto7+5R/S/RL2zuvu4k3fAumwLdhfbgb9oR7YBp8B06Be+EsuA8ugPvh/fAAXAEPwjXwEHwTvguT8PN9WBN+AOvBD2Ffdd0Pvgez4F54G/wY3g+PqnK8z1jDBdupeCTwe4eKR40Q4gHrwMqwLqwJ68F6sD7sDBvAAbAhTIeN4Gh4DbwVXguXwGZwJWwOt8IW8AhsCb+CreA3sDW8ANvAEJ2wwWjYHpaCHWAq7A7rwk6wDeRa4vW0uc4Jt1S8Yvn9kIrXebc6AwsmQR17paELVoAhsDH0wKYwFHaBRWA3GAb7wAg4AhZV8YyDa2ApuBGWhm/BFHgYloX+Z7sybA6rGuHVjTUQ8k6Q8Nb1/1bP+xsqH3bB1vBt2AvW8HDMEtzDdQbcC2fAffB+db0E/hVugh/Azer+O/AI/BAeg0fhJ/B7+BmMw++TMAV+ByvA72FNeAo2hvmwGTwBu8AvYE94Do6AP8PR8DN4G7wI50GNcD8MdbgUuuAK6IbPwhC4C4bC4zAcnoDF4DkYA3+DsfAi9MEQ0q04DIUJMBImwqIwCcbC0rASLAOrwRRYF5aDHWEV2BlWhdfDajAPVoezIOkt+XXMmHMOz6v6pgQ8pMrXL9QTcg+GwiJu0hOGwwQYAZNhKiwFo2EFGANrwThYBybAVjAR9ocl4E2wJPwzTIb3wFJwISwDN8DK8BVYBe6DKfCg8u8QrAY/hNXhV7AmPANrw19hqvkeV/Oe4QcO7/F71XvuLzABLoSl4QaYAu+DdeH9sBFcBJvAB2Fn+BDsAR+BveByeAN8Ao6Hz8JJyr3JcAW8C66EC+BquBA+A9fAtfBVuA6+rezvU/YPwvXwfXWdD+ebc32hil8xOFPFbzR6OhwDI2C2it84WBuOh83gBNgK3gU7wklwMJwMh8GbYTqcBXPgbIgR/TlwHrxHXct3ujFvFqY6fKdPDiFccCqMgDfDEnAaTIHTYVV4C6wNb4XGWZQ9lbvNMSlBZ1HWpnz7WReGwvqwNGwAa8GGsBlsBPNhqjEXE8Yr99ywgnKvHuXIz/qwOGwAjfitU/a6OMSvm2qX9oTRsA9MhH1hCrwO1oQDYGc4yPyuVPMIQT+H78rGyt0msCi8FpaAzWBF2BxWhi1hLdgK1oWtYWPYEbaCnWFr2A52VPLrRG6dHTlUheMFTErQ2ZEzVT/LbJgI74Bl4BxYHs6FDeBdsAW8G/aE98B+cD5MgwvgWPgXmAsXwinwfngnXAQfhEvgY/Ah+CR8GK6Fj8Dn4aMwH6ITmGs=
*/