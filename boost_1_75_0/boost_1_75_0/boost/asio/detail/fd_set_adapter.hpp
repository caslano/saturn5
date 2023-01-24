//
// detail/fd_set_adapter.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_FD_SET_ADAPTER_HPP
#define BOOST_ASIO_DETAIL_FD_SET_ADAPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_WINDOWS_RUNTIME)

#include <boost/asio/detail/posix_fd_set_adapter.hpp>
#include <boost/asio/detail/win_fd_set_adapter.hpp>

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
typedef win_fd_set_adapter fd_set_adapter;
#else
typedef posix_fd_set_adapter fd_set_adapter;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // !defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_FD_SET_ADAPTER_HPP

/* fd_set_adapter.hpp
LivGjZ9xTx2CAF5ZGpUUSI3AqaxGSAtO90sLaufibisSlRidFmC5kh/reAbL9A3FCgypQV6i/MR5xtTgeEfXoKmBXV53HqYGEO9gdvCB7jEeeIN5jBL58MmoeLR7xelw33i0RH4p+qGnb+z/kNg2P9Jf4spXTeLKPaZS2s5ivwfnZu5v16Xo8yYz20I4WIq72eYnPwYdfEJqEWv/Kb0lvhOGWMcnHAKvfP9kuL824Sq7DXL9+1PoYT2wWfiYKxE6UXrjMWtL0gn2DsTr4KtHiHVhf3ai+H4Yoxy6IR0QA/+U6sVmtDL3g3kzrU3cepqVW2umcn25b4J5wRjIZXrMZSuRQkW+ylpfcaM85URXOGGfMMzpurmkSB7Lfk10maQDWwOozVL9Ksrbm01grLu/pdsOsfJN8+Z4scEsFjeacNZS7iGpW/zGLH5sYm9igm54L3M5iVnufrg7N1H6EHyqtbGk1FfwZtKH8ni4eWHum7h1REnpuA/lRHxYeNPanvRherh01e20vO4QzqEI5+Bsl6QPrUJtaVJ549bjn9xkMrlSxuEYyuc5eMTefqglxy6deKwUAtnZSe+DDL2RQ3Xn2KKuvsSuWuGiNZD0vi+32Vd8KLMykb9dvigHwx+wtxtyVOX6DcEQe5zyQu2KlyL9PY+Zc5sxNhpefIgCmpUrTjNjuFDK0cKgSgqDXu376Cx4FEOhZhYKrShX3xwB
*/