//
// detail/std_fenced_block.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_STD_FENCED_BLOCK_HPP
#define BOOST_ASIO_DETAIL_STD_FENCED_BLOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_STD_ATOMIC)

#include <atomic>
#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class std_fenced_block
  : private noncopyable
{
public:
  enum half_t { half };
  enum full_t { full };

  // Constructor for a half fenced block.
  explicit std_fenced_block(half_t)
  {
  }

  // Constructor for a full fenced block.
  explicit std_fenced_block(full_t)
  {
    std::atomic_thread_fence(std::memory_order_acquire);
  }

  // Destructor.
  ~std_fenced_block()
  {
    std::atomic_thread_fence(std::memory_order_release);
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_STD_ATOMIC)

#endif // BOOST_ASIO_DETAIL_STD_FENCED_BLOCK_HPP

/* std_fenced_block.hpp
/w7Z6+JT/u9TOXlQ+fUQbAYf/Rd7ZwIeRZEF4J5chCRAiJxBMAooIpcIghxy30cCguCxhpsgIYkkCIpouBQFNSoKIgoKqMshiCgooFkWBRU1sh54brxxl3VxxV13PXb/qnlT0zPTnUwC4uc6w1f8qe5XVV1HV3fXe1UF64u/EdwNG8tx2RtQbPCIU7mgvQFzJd48aX/Tpb4LpP+ZAVvCWVLus6UfulH6oTlS/tfDDDgXXiLnr4AL4Xjxy/MMOznJp8fh/cXjvb+HwiYwHZ4l/lbiz4AZ8EfxN1RjM1L+OyyxdYKvSH5rwY0SfxuPvE/Ic6WdxN8engfPhx1hB9gXdoRD4AUwHXaCF8POcDzsCgvhhXAx7AaL5Pgq8T8Iu8N1sDdcD/vArbAf3AMHmHYmNkSifysNaGfy/BW5MWHKFYYpt/oL9z0uD9j3zAxTrrQMuXU2OetweHJpZcg9ay+/MOXGhClXGKbc6jDlisOQ2x8lOkXRU9KO9Xvyrih570OuBpwo7XiytNcpcDi8El4Cs+EMOA1eA3OkvebCm+FV8B44A66B0+EmmA+fgFfDJ+FM+BycBffBa+Cr8Dr4JbwBpirdO2wC58EWcD7sABfAC+BC2AveCAfBm+BIeAvMhYthPlwC58Fb4U3wNngfvB3eD4vgGngHXA/vhFvh3fA9eA/8GC6DHspsOWwHV8DO8D7YFT4Ae8NVsC98CA6Ba2A6fBheDB+Bo+EGmAk3wrHwCZgFt8Er4WZ4FdwC8yXduXAnvBVuh8vgMrgZPgefhXvgm/CP8B24Fx6GL8Cv4D74LdwPf4QvwRrRjDPCZvAVOAyWwOvhQbgIvgFXwDfhbvgWfBG+Df8ED8H34HsqHfg+jI/BdhmeB0thV/gxHAU/gWPhp3Aa/ByuF/m98Av4Kvwr/BgeMc9F0ZfB6g7Pxd4yftRHxrP6+r93RYdFGIfvn3cl3HsyjvSBjOd9KONff5ZxylI4BH4Mx8FP4RHbnhKXUwkFuLL2lchQe0rk4g9zf4nI3hInfm+JX2JfiSXPVnJviWfD318i5pH/3z0mDjx7YveZ+K3tMXEy9pf4lDqKeY5rxfXHZeGKcDtwpbj4YtLFjcBdh1uJ24U7hPsOd+ofiAeXh1uO24V7HxezhzrEZeBm4YpwO3Cf4pL/SBnhxuAW4bbhSnCHccl7CYfrjRuDuw63FLcDV4qLeZ5rxfXHZeOKcNtwh3A/qHMvcA6XjVuK2/jCr3PfjMgv8ov8Ir/IL/KL/CK/yC/yi/wiv1/b7+Tt/zc9R2//d5z7/6n9/Ba3tszasafKYjAZfEY2ha3gY+3Qm+1jbNK7hubF52X2GT2CC5gia3KtSNZ7+c8o8M+FEvlm2j8K/3LtT4uyr7VpWxNe5LuZfRU2a/9hxkszrK1WFTnusb7Rxw94MrDin4EWS8V3htnrztJydfBv1HL/8HTFAvGfsvdYlkmnC37k+OuBF5W/lm3PDmZtTiRjcm1TTJgLtD8H/++1v2aUCvN9bQRlr3n7ugTvapkX9fWlckG0CuaP+fPbWKdbz8wbGq38+Jhfo+d2PazDp0bZ5+AUyD7mKkw2cRzUMkc8Cf593O17u0u4XDNHrS68VKfTW/ySf1nrsntNSYet5O1zprbpdOJM3p7x1qUOEx0nYTJlT3wJs3A/MviirGpm7tMyfayKp6y6zNPxydx35EYS7gEt1yhKzV3awdkF0ehN1NyluS3iquu5S7H1fXOOVsoaTmeK7F6fbH5co+gmcbHRqXFVo89gmZH6cTWSomLN/JBGtMlUnC98ioQ/zMlsjifVnPuX4LlUvn3yn0nFfgaZRFw30spN9sazDsXyWDi1ZjjzjWI=
*/