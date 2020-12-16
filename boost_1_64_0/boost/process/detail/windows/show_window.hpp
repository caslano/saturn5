// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_SHOW_WINDOW_HPP
#define BOOST_PROCESS_WINDOWS_SHOW_WINDOW_HPP

#include <boost/winapi/process.hpp>
#include <boost/winapi/show_window.hpp>
#include <boost/process/detail/handler_base.hpp>


namespace boost { namespace process { namespace detail { namespace windows {

template<::boost::winapi::WORD_ Flags>
struct show_window : ::boost::process::detail::handler_base
{
    template <class WindowsExecutor>
    void on_setup(WindowsExecutor &e) const
    {
        e.startup_info.dwFlags |= ::boost::winapi::STARTF_USESHOWWINDOW_;
        e.startup_info.wShowWindow |= Flags;
    }
};

struct create_no_window_ : public ::boost::process::detail::handler_base
{
    template <class Executor>
    void on_setup(Executor &exec) const
    {
        exec.creation_flags |= ::boost::winapi::CREATE_NO_WINDOW_;
    }
};


}}}}

#endif


/* show_window.hpp
YxD9XeGeYreGGX8f+ieNdPgHiPk7cq8VoWr/kiGcE8Q+QOwfClP2Oe42srvYP0k46up9DX3F7D05t/UsefzoY8yhy/d6Gzq+s+U3JNgeFFymhPV3tpSba7ipH4GbMrmvmM+x6aR09jxOuSYQvv2DOgXVCKrG/7VKBPjag+qX8PUNKRHuOGkk1PcePkvqGxTUHPtRQW3YFhroZ/6Ov6ENnixhf45UrYOOPD/+snh67jgvEZ18YtzS+A1C9c1BUkjsA3m2PpL+fpjNErO1mPhQ/tt7xPUM8QhwpE9gN69nRlSIuv37DMVvZ6ivIHHDTOdNKX/L27vLn7GumrxCnxct9k1VmxvbQZc/OWnZos3V6VZTdBvZoqzbHPwqfjsc2+H27bDff5w+waErSZs8ec8lbbpKH8/3IZ5wetzAjjmsD7sQuJE6PaZkqRlJY/snBsazfEaLfjV7P0K7Cp/8rb+pLP6a97ONmjLGIm20rp4Hpdum6/90satu78//KxE/vo/cgTQso/qPFVGaydxnDHTtF3ocPyo50tdtJvOjcyO4LsaeFY/xmU4D8zyxxMfzu498pE2oPOutvlmw7G53Ghu/GuQ636oK4YxFqiLVkOrF6KMZn+3q1U6Lw4gPcgipQV4oNN5XbWvy9t2paPgv0R/LfECMdR/rbq/fndJzR0PjZZxu+Zxx7/2bU+Z2xZu+3NG6P2XUT5CUyZw4cdyULFf+DYUlJXxP2aKpDXuyk3+u4cyNNmJXQvLsyXDnXqmJ2e7+4znxfz99ELvex7qDG/fC4x5IT0TWjdXv7m5zkQ+KkfccYxfCYTqDyfq7VwFevnsV7OW7VyEe5rd+9yxhza3rFm+SuHskPLmSGEmSm+RopVS+v+54j0qnF31ub9/owQ/P+q9GMfK4q/5z+B2h/Db2sWo86VTuh9iRvsjgiuQDZ3gnZ/NxNsKnF1os6jXrfB5vro/ceeCC2HWxtXJ/v0Lqn8ciRKhnbl+ve6tfjO8SHVdxi1YOo5Ac6vj4jhI3apGUzIk5aXpvqJ29oV7igxvPb/jUxLNad5D++E848V+1uX3FPzmPxyPM+WutwzzSFWb5bL+tWGEeaRHm2v9FmLO9hPnSOqfjbFV3TkIK0Ml1hVmWes1hdvetlolesu1e6z4C/rjbwddDne6N+34Xiv1Y8q7lmXjavft8MdcWasNZjB09z2L8Sq5L6v2IdQhoXaSeYn2kJtIg6vb1kUV66naQ+IhZjkrjf6o0fsaUxolPOz0co9J4tDONuYNKY+dysdc0DhG9AbYO1mmMP3+dxiXEPgm1klZpjPvbp3EH0XG3Fb3luqTeM2RO45pIw/9x+iZ1cqevsd9xRqUvdvpvRnnSeKUvZrmOLyQl8bZeUnLOjAkpao5lfHnv3wHEXTHfLyDsEL8c9bOE6TLXe3wZ5zTnudl93w5NHTWp4TNPbnl54I1qB7m5b6DD/IX1GzvP8/O90Sml5YsTTrdMZh3E32H+xWPffdApLWP9nF8eGPVytRcw+7KEw7zSsZSgzBHd550stTCrRt3EZ+kjlXSYb1w1uu8rfhe+efO5WjefXJH3HOWplMPc/3LUb+N7pw//KrD2I1mPzaGzuCrAYf5ecLndSc2avdvBv37rSZW70FZ8KOZxcRv7/3Dkj+i+x2fG9H065gDjOQnPpCp1Y1+JWrHj9xmv5X26qIgGJsXPYd77ted7fXtz670XX1y5OnBLzae4r8TrfH7s2ob7JlyfU7Th9bkbqmxlDtPXYZ51aPzCXy/V/uCzx++JafBdq7cZi8h9fZ7LqFbjoSutK1yrEBrx91FfSRuMeecv/Sd23hI/9Nrinxd1mljtPH068X9W/sA=
*/