//
// detail/gcc_hppa_fenced_block.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_GCC_HPPA_FENCED_BLOCK_HPP
#define BOOST_ASIO_DETAIL_GCC_HPPA_FENCED_BLOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(__GNUC__) && (defined(__hppa) || defined(__hppa__))

#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class gcc_hppa_fenced_block
  : private noncopyable
{
public:
  enum half_t { half };
  enum full_t { full };

  // Constructor for a half fenced block.
  explicit gcc_hppa_fenced_block(half_t)
  {
  }

  // Constructor for a full fenced block.
  explicit gcc_hppa_fenced_block(full_t)
  {
    barrier();
  }

  // Destructor.
  ~gcc_hppa_fenced_block()
  {
    barrier();
  }

private:
  static void barrier()
  {
    // This is just a placeholder and almost certainly not sufficient.
    __asm__ __volatile__ ("" : : : "memory");
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(__GNUC__) && (defined(__hppa) || defined(__hppa__))

#endif // BOOST_ASIO_DETAIL_GCC_HPPA_FENCED_BLOCK_HPP

/* gcc_hppa_fenced_block.hpp
D/MyTf/+0zFNr6dyWp5Ox7+fKxfkmXI27I/1ck7Oy0V5llyVZ8sNeY7clHvlljyXxsD0+iun5Plyl7xA7pH7ZF9eKAfyIhufvFgelJfIw/JSuX1G6HiJ379yvt4T3T85H+YGXTFX6Jq5Tjdg3Z84H+Ym25Pvjd5/8XyZM+yfkTFSzoc5xXbfnKaL5hxdNfv0gDmgG9H26WFzkk6+L3q95PkxV9ieN9fowJxi/7I5TQ+Ym+w/ZG5ofswZ9A8v9P/O5/fi8J+w4vfHpdDx/7+5iMYFputTTsnl0PHfW10qF+Xpckb9z5d75E1yQS7INXmZjUc+W27JH5CTy/T6Ejr+e6MX2P7li6xd/RfaeOQVciBvCB3/fc+8XFF7v41PvtDGJ59j41uu19fQ8fv5WaHj999B6Pj993lypx6/0cYjrwod/33Q2Tafap9j25d75QF5rtyU58kj8nwb/wraDx3/Pc8FNp9q77Px0aMWvP/keBZF7085Hlj3A44H1vtFHt9ie37TKXOOTsN6/nJ8Zp/teVjPX55fc4X9KzQa2L9OY2H/RmT2HzaXNL4ldn+hO2Dd/zg+c5aPz5gzdI85zf6+Ocf2wNxie8lcp6uw7mccf9TO8TTNDXoE1v2N53epme2dsO7vHK85SWcjc3++uUaXzCW6ZvY1n+Ys3Vr633n/fLiX1NSk/s4cc/B65qzW17S+obz3gvWzD4nX8/lzaHg++//q542wvav/78+/Pl+NCU/jBrvexocumpN02Zyma+YWHz9IY2H7kLnJ9pY5G7bjxm/XL9s7zHW2d5mTbM/Cer0Pnaex7B+6YG7x8SVzhq5G22P/ujlFN8xpuhmNj48fgfV+K3SyZOPleDphPf85fnOW7jHn6ILZp8tRf25/IOpPD0X96RFzQHecE92vuH9Y30dw/7D+/Zb7NzfYXjEHbK+b69zecNRfx3+unV/tz9zS/iKzvWCusL1sLml/NBa2D5uTdPK86P7L/dFYNL/mNNsL5gxdNFc03+aarufIup7NAd2EdX/j/JtzdPtGOz+6HsyBxmtu0jnz6Ocvz2dRn6fktDxDzsgz5ZycDx3/vvpsuaD2OXJZ7pUH5LnykDxPbslrbHzr6Plyl7xczsoftP3Lvu1f7rf9yytt//IKeUQ+3fZ/Bl2y+ZEvDh3/+8TZNj9qXycHcsXGI58mV+XN8qD8IbkpnxEay5n0WTY++XybH/lcuUfeJPvymXJR3iBX5FNsvuSCzZe81o5fnmXt8e+z83pdr8+7cko+1a4veZnNn7wxdPzvsX1mtV9i8ykHck1eFTr+e0Gr5brai/Kw/H4b71n0Qjvf8qLQ8f+vvdiuP7VfYe7Tvx/bfKt9ic23fKmdf3mL3JAvtPmVL7Ln2wZ9frHxyeeFjv89bKmNZ8Pff31+ZPn3L7nzeZ5aP+P7M//nzGnlGvOopWXrf5F8WM9zk+PB71dyu839HsOfK00gh29XmEsHMb/zaR5/rnAinZr4mIfn71hpyX6M4xmcqP8vRblH65tyWTm3z/pAOR+vp5V9rR+Rs8qFfdZ32fbi9TreB/d3g9LPf8ELpxx51Iu6XvzKVx1z7KuPe033a1/3+qnHn/CG7BvfdOJJb37LW3ve9vb3vPd906bPmJmfNXtO79x58/0FfQsXLV6ytLBs+XOfN/qEjQ3XDW+390P0CKz3O6Hbr7X3O3SnOUV3w3r/HDpvztBFc5r9q1E7PRg9nh6O2jme9uusnU6Zc3SX2aez5oD2zUmOpxT1p6s0Gui6uUIPmWt0K9o+3X599PmE4zOXuP+MOcfj6zH7dMEc0OXo8XTNXKEbNBrolrlOJ+vR+2fOj7lJZ80t2pdxJDw=
*/