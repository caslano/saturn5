// Copyright (c) 2106 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_IS_RUNNING_HPP
#define BOOST_PROCESS_WINDOWS_IS_RUNNING_HPP

#include <boost/process/detail/config.hpp>
#include <system_error>
#include <cstdlib>
#include <boost/winapi/process.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

constexpr static ::boost::winapi::DWORD_ still_active = 259;


struct child_handle;

inline bool is_running(const child_handle &p, int & exit_code, std::error_code &ec) noexcept
{
    ::boost::winapi::DWORD_ code;
    //single value, not needed in the winapi.
    if (!::boost::winapi::GetExitCodeProcess(p.process_handle(), &code))
        ec = ::boost::process::detail::get_last_error();
    else
        ec.clear();

    if (code == still_active)
        return true;
    else
    {
        exit_code = code;
        return false;
    }
}

inline bool is_running(const child_handle &p, int & exit_code)
{
    std::error_code ec;
    bool b = is_running(p, exit_code, ec);
    boost::process::detail::throw_error(ec, "GetExitCodeProcess() failed in is_running");
    return b;
}

inline bool is_running(int code)
{
    return code == still_active;
}

inline int eval_exit_status(int in ) {return in;}

}}}}

#endif

/* is_running.hpp
jLRfA63WbyL+vJXLwvIZy3CZhQ5twAe22l6q5m3MIzToZsDG6kLzwarXefPDxHlW58sKlx347vms88tnQ5YSCtKkdOnAMmQYDQuKoe4b0iQZqtam26LLGkSwiLv9+nyYx62R3EEbxnSQhUQdmRaGUB99H1Por1XYIYI+rekG4h1t8WfQ1g4GKhbx8BfMsHjGAbi0ylXE0h93fSflHseAlGXv8lfJNv79/bPTD8sHuzFwkGd6c0KKh3TA7hBMfI8zmiHLhFEMspoRBsrsEv1zI+ZkG9Ccz4dE7JugIBAd3CIMbGKoE+g4JZ9EEtqGauE+1NKofKfra++b39h40GuicQS2GL1xxYDhr35wvL+/l1hQO9peNFK0qhkENnw+3Ajm/aWY23khcbuedARocVOCaFX6EjDXLz/rR1mHnSG2Y7aQHCGusT3abVVw3RkBj4u8Cqrg3hDJJ5otTzawhXCbMdrRK+QFyM8Yqj80U3w9fVXUc8z56rdkHj5cylm8P/RjmlBqoGowHAS2sULlQwXg9Z/dyCn71kLHQ73g9bEeyPnRteF1V4KsxVZj3P9QQ1wDXZNwyVGIZSz8VQIGXfQbrhFPHuF04KG4N+Z0iDt6TciUG+HXZwzoUNFv8BgS39Cd8WfkT8i/6Rx64O34hL6FQocGhoqFGvZRhPaGBm0Cw69CpUgHH2G2lfqk++iUbHvLh9SNiE64+vj6giJS
*/