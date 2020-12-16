//
// detail/future.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_FUTURE_HPP
#define BOOST_ASIO_DETAIL_FUTURE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#if defined(BOOST_ASIO_HAS_STD_FUTURE)
# include <future>
// Even though the future header is available, libstdc++ may not implement the
// std::future class itself. However, we need to have already included the
// future header to reliably test for _GLIBCXX_HAS_GTHREADS.
# if defined(__GNUC__) && !defined(BOOST_ASIO_HAS_CLANG_LIBCXX)
#  if defined(_GLIBCXX_HAS_GTHREADS)
#   define BOOST_ASIO_HAS_STD_FUTURE_CLASS 1
#  endif // defined(_GLIBCXX_HAS_GTHREADS)
# else // defined(__GNUC__) && !defined(BOOST_ASIO_HAS_CLANG_LIBCXX)
#  define BOOST_ASIO_HAS_STD_FUTURE_CLASS 1
# endif // defined(__GNUC__) && !defined(BOOST_ASIO_HAS_CLANG_LIBCXX)
#endif // defined(BOOST_ASIO_HAS_STD_FUTURE)

#endif // BOOST_ASIO_DETAIL_FUTURE_HPP

/* future.hpp
K3epvSL3yJfIgbxYrsobQsev30vkQbUvlYfls218Cfo8e7xckDPyMjknT7fxyH7o+OdN58kVtc+V6/JZclO+QG7JZ4SO33/MkNvb2D7T5lPOy2l5uY1fXmTzKX9Izsuny0V5jY1fXmHjl9fZ8cobQ8efH9bb/Mv9oeP3SyvlET3+Yjsfj6Lfb8cjnyJ3y/NDxz+PdWbo+P3WRaHjzyNlO396/Fo7f/L5oePPJ6faeNX+ATt+ebadP3mOHY/8QbljDL0pdPx5p9f2p/YFclYO7PzIq2y8cp9ckk+z8crn2PNLXm3nSx69HMT5/vmT7N8LOT5zku4xp2jf3DiQ14+5eRDHY27RA+bcozmeaPtJnj9zje3JX8h1utPcpDPmgM6aS9xe3txge8Hc0njNGbpiztID5hzdMPv0cLR/ONyujZfugPXvoZxfc4buNmfpvDlHF2ksHH812h49aE7SrWj7mr9f2vmi0+ZKkvNlrtE5c50umEscTyl6PF2lsRzI8ZhbbG+Z0xN4v/qV9d+fx29O0nlzii6a03TdnKFHYL0/5fH92uaPztJooH1zkuMtmTNsHzA3DuD1GfU/iOf3HutPd5pTdLc5Rwdmn67SaKAHzSVt/zc2v9q+uabtm4MJ3L65RFeix9N1c5bzNWzO0R33msfy+WT26Zw5oANYP8/A/UX9ub3BqD/t/db6013mCu2bazrfUTv3VzPXdf5hfd7j/dfc0P5G7HiTPD5zju6S8UGWx2dO0UVzXfs3N7V/c4tumn1u3/udHT/dSWM5gNcjrM8zPH5ziy6Zk+xfM6foQXNa16c5R7fM2UdzPL+37dMd5gz7p81ZOiNjALzfR+0HcbzmFNur5jQ9GG2fHob1eY2vx3+w7Y/j/JiTdJc5RXeb03SP2ed48+YM28vmLD0YbU/35z02X2zvMPvavznQ/swlumCu0EVzja5E/Tm+AXOd7cPR49ne8Ue7HtieNTfpwNyiB8yZCTz/5prOv7lOe3+y7dEpc4vuorFwe1mzr9cjc1r3M3Ndr+/mBl03B3x8M9o/538k2r5en+6z+dLrk7lCd5sbej03Z3X/M+foUrQ97q9q9nU/NNfYPhTtj27d96T/ic/Ljyz/H0tuP3s/P/r32/k2DO3h2yvmdJjjZeQVe3/P0Z7Z2x37uHMfP/fEfX6/fqI+vz+e+T4sHl9vDguflk/S/rN0xZyj62afbsD6PjN0y1yBw68bzPuHTsL6/jF02pzi9jLmGvv3ROb2CuYS+xej7Wu8sN7Phh4wZ+hG1D4u9LA5yXbvyTb/dArW6xfHZ/bpHnNA580lOoD1eSF0OXo8PWBOcX9DsF6/OJ5Jdj7YnjTX2J42NzR/5iTnN2dO0b450PyZW3TV3KQHYb2/4/gis70VjYdOTpZHf7/L8ar9dLlbXivn5ffLgVyUy/JMeUBeKg/J+dBYnhJ9X8LxyRvllDxDzsiz5Jx8vo1HDuSKvEquy7Plptwrt+S5oeO/TzDPxvdUff8VOv6+ap31V/sZNl75ArlH3iT78mK5KPs2frkg1+SSPCivtPHIq+145EU0JpQ+V+6Qz5O75Ok2Xvkcm9/UwY+8vmMpHKLrnvn+Fj6ND43a28LnR2z+vmXsMeH5jM2fF4g9Nny9iT0uPH/PiNwenr/Y48PzF3v/8Pkb+4DwOGLz7x3FPih8/sZ+dPh8ic33x4dFPjy8vGI/OxxP7Inh/SQ2f/8+9tPC8cU+JJy/2E8Pxxf70HD+YvPfk2I/L7z+Yx8WTtIzIz8zHETszvD+F/s54fM3Nn/ePXY6vP/E5s87xebfV4k9JRx/7L0W+/a/au0pumZO03Vzhva/Yr8fTTesPUc3zT4=
*/