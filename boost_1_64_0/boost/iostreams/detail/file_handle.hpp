/*
 * Distributed under the Boost Software License, Version 1.0.(See accompanying 
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)
 * 
 * See http://www.boost.org/libs/iostreams for documentation.
 *
 * File:        boost/iostreams/detail/file_handle.hpp
 * Date:        Sun Jun 22 14:23:12 MDT 2008
 * Copyright:   2008 CodeRage, LLC
 * Author:      Jonathan Turkanis
 * Contact:     turkanis at coderage dot com
 *
 * Defines the type boost::iostreams::detail::file_handle, representing an
 * operating system file handle.
 */

#ifndef BOOST_IOSTREAMS_DETAIL_FILE_HANDLE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_FILE_HANDLE_HPP_INCLUDED

#include <boost/iostreams/detail/config/windows_posix.hpp>

namespace boost { namespace iostreams { namespace detail {

#ifdef BOOST_IOSTREAMS_WINDOWS
    typedef void*  file_handle;  // A.k.a. HANDLE
#else
    typedef int    file_handle;
#endif

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_FILE_HANDLE_HPP_INCLUDED

/* file_handle.hpp
dt47ydEOoY3K0dj5zYXZoXeIsFD1qyAT9O9kpgPZsD6sCRvAurAhbKjnfWFjOA42gzmwJSyAraDMUTbv2eQ9IEfYXqgyd9bh07AKfAHW1/OO8Bk4AT4LF8Pn4FrVuwO+Ce+Df4VH4NPmXZC8/5IjBdmpf3+Enh8egynwb7CpnreEX8Me8O9wJPwGjoXH4RnwWzgJfg/nQ4t8LgG14IXQhpfCOLgCVoJXwHh4DawC18KqcD2sDn8Ja8B7YCLcofGZuZTjzBxBjvC5lNDsWxIHW5k9YfW9iXmPEz5XtaGWeyMYgI2hPHfDurApbAKbwVA6Dmt8zT3S0VbT0Q42gx01HfG2Psvr+wy5JnJcw2USf1XYD9aC/fX6A2AaHKj1Mxg2h8NhBzgS9oej4Dg4Bi7WeFbDLPgMHAurcfFxcDIcDzfBSfADOBV+BxfCvj7u2+BF8Dx4F1wEn4EXwHdgMTwGL4ed/cHrZsGr4Hh4NZwIr4FT4bUwF16n5bjf3BtKXuSQd61aHmu0PNZpedwMk+FG2BneCjPhr2E/+Bs4FN4GR8A74OnwfrgCboO3wwfgk/BB+DTcDp/V85f0/B24A76v5x/q+ad6flTPnTp9GDaHv4eD4U4o7S40zsMXPdpdS2136ZrOTlpvneFvYBf4AszQfh6ai5ofsbfOHuYXRu6vsx+33lTiIeie5xk/NM7aNzZgrYjYX8fsrROxr04T9Psj05CLkA3INmQPcgiJH1Yxt7HiqDgqjoojluOfbP8/f25OYffg/7oB4I/89u/YuSsmbHFP5x4na9Sg8d3dGwCK/1puRlb3Mv7uDQBl7kD3GPb/S8wK3//PxERqCn/k/n+ZP2D/v8YvOe7+R9c9PKf6cxvrVz77rTvPq/Xuf//+f0nVHfcVd9z86ntPpacve2p8cd61tx+Kvu7Z3MdkRd8vcIne714Mk+AlsCG8FLaHy2EneBksIpJ5E+OsVcjk005ca5M4RtfbmLU24ets9iO6tkbX04SvpWHff70XglnB/fxXeezjfwOS7Fon02Yc8SCRa2LaI66993WPQt1HP2IP/f1mrUvkOpew/fHN3vhmH3yP9S26tsWsZVkLD8HQfvbzPPaxD+1hb+ke9aG96bdMrLhHqzgqjoqj4qg4Ko6Ko+KoOCqOf8fxL3r+59F5PqbAnBcAP+7533l+7+Ga+79SP1DyqGT54Fj+q9Sa7xp95Pk9+Ng+M1eSE/qu+kgtmePYXeaW6nfVVqK/x25BLGORVcgfkP3WPZ7fWonffGs9MxiffPhspHMSLhH/IXYXZ9cA5E7kAWuJ57dXd1w5EldObkFR6Vzvy8S/D/NyAp7zq93h54u9PuaOzyidR/BtX8f/DGZOt/eez9kn0obfrHkzZheKbrJLN9lDN2Qnr0PIlrz4t/I15/8s5BrkEcS2memIjLB7W6/ap5rv2edJ2tobW+st+jnnp3HtNsZW+C2iU8Ntq92EPyJ+2UZ3HOHlK3awLDjYYkEsslI3Wp67JI2/s5tRnrOQW5EPESdP+dKe1Ia+1uXjco0t4XE6Khwpmo7vJM5CvrX5qG+fqQvicrZgMHNVukhcF1gdaQ+LeIfE92D5uEePEM5PCbJnapC94FS1hfs+Or1Tzd8ifTjvi0yrEzxfjx/+YtPySQQa/w0Sruy58I59W8rxBHvkTr+po/0m9M3/THGTtm/mQOSIm7ZhnXtGWeCm7RK3ZGOvUdpa2BqJBjr/+wPEVtZoTTr7u/p07oKwPr3d9JtCU9arRH+uNdEKePVh4ovsN3kLLM851kZX2kDP4LXy8ufkFnjaFhd9zz5l5tI8Jf5Jnv3RHZay5Cjumt7DMmHvEP/K7v5g5pg=
*/