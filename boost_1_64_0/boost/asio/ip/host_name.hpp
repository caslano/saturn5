//
// ip/host_name.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_HOST_NAME_HPP
#define BOOST_ASIO_IP_HOST_NAME_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <string>
#include <boost/system/error_code.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// Get the current host name.
BOOST_ASIO_DECL std::string host_name();

/// Get the current host name.
BOOST_ASIO_DECL std::string host_name(boost::system::error_code& ec);

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/ip/impl/host_name.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_IP_HOST_NAME_HPP

/* host_name.hpp
B26qubhOzi7WPDUS9hmzzzDD+er9FFTpdbbiV9l5qiI8hHUfQxEi/sffVPq3GyXG1NA9eF5U99YQLnH1tR5R8XuNFjRkxg/NV8/VPrTZF7Vjc4cD0helbvQnzzNfYR7vMElfid5ypprpmzPSMybTUIakhNM/QDxjc0c/qoqkypglYSxLhQepZ+fKs1uywv1cnT95qMu7ERvq9MX256t9yp9Xfd0eX7ivU/Ws7t3kC/v4qh7Vu6mLe0F1z1JX4v+jN8f3porkjPpvQ+ME95byO+QZDvvD79/8jrot7V42JzyTtR/+sArfQesNeNmc8EzQ9vGQCu9jJckAVxs6nzQ/UGneb2wzCuWez3hc3duDN7jNYUPD+esrKv4T+Np+ZS9HkX9kdthepvqTm73tZYqkvyk7ZBPJFRklGVPwd1M0Lk1L82fC5xj7e/X5h5U88+jpBmqfLuNM895KaicHLY4JvTcl727yPlCMrCkLbPefzhY7GzzTaWPH9Q6N2NUc0GJX9rOpxV4myPxSIXRwNPV4pm1vSdmmlo7NvFHd3qeSttDyThLfLo45Enn/2N/1ck5/qmU+d3UpZYiSSXrNVR0Xb2YW1XB7/whPap/7YEx50iN9vK1N9brIc3cR9+3yhPtzU8musvSegCzh+qod7qyvx00/KEoWqS7371BE1deCYfH44vKtBZf6OjrcqZ/7kCnzLLtM9uoS2ew6guf4dBSSp8Ymz6489/oqipJH+r9QhXnYT1Hf8izzqjP9DZ58EVz8p9PFfyqLyOP0BUyPyl0m4cvXY4SlKjzJ5kcNET9qsYqbIP1zmDfX9T14vooL6PfgNhXOMOzv0PjnPz38JZtuOkfIOdLINhEcDM5GQXti6UYmQ13sBz6Z+5N31pdV+HXPub8DKv4vxsO0pifNuVA99ydrKEXHj6t0r6o8W9LM+K16fvHXKq7bc07QHDfvQ29HChi/EO9PalITFwMz+C91qGU9JYcxWd6/yfPVGEDFdyjZG+uaJF4pT8VPCb3TqKOBMu/4vSn2OceazBOZe0wNfHS+jMFbW2UuUrc7r7lI3XcuGhn124vYfubZ9vqVftNrHCHpcxw2vlzF9f83GA8btfUnB0c6vt+gbDToXgaxTve+Nxgl6xenxC+r9L329lPoLlu1l2wyde4lX3WUfIG45mm83w2Vo9zrv9Min/TD2gC8+uLOGDbQeYpt4NAodz13u5ZDFO2h4+6TbAO7RrvL1uspmxiBh3y9J8kGZhhDlXxl8rIYKQwjoFey6A9D8plH0NGxnVbOba++UNKO9OwL/6zi82O8p4uWhX3kdL3O28xD/GGRddpYWaNJnnng36Hy0+EOKlktP5hs2kyU9Td1/C0tr6QvMsbKOyKowr833k5el0MfgXqgH0P6ezpRv53zGpLnFKrnZBM+S4V/bbyN9/JOaA/0CPQjSM3/pylZ9DzmWHl/naH4jhrb+H8XdBv0beiXkd9UJK8RrvPXBaLny1WaD6PpTEb8pxlXgGF/4X4Vl+o5d92g4gMSJqcFapztMY/et58h4x1ZCxDSf67tGzTW329kjUCaeV/rx2anj0vd50KDha41FwMrOTvbtodOTKxlNb4q4++LHGNmSZtrm1/1bjtFtnLwPBm32eXaOM4p12HSdtnlauq42FuuLrtcjIX7L5duK8VOuV4mbY9drtAH9wxP2Uhvnc+zf5toGCjxkfFwP2WPfJ/o1H536GTtcXDfs+C1ht9rL4PXGv7j37PgvtfAay+D99r+S4Lm/Yaz//poVtML77659IXT7r3mrNu99jh4fcfJ63tNXnsfvPY4eO1lOP49Jse79+F49zi47z3x3qvyV3PuHuJS4w4=
*/