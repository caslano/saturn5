//
// detail/gcc_arm_fenced_block.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_GCC_ARM_FENCED_BLOCK_HPP
#define BOOST_ASIO_DETAIL_GCC_ARM_FENCED_BLOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(__GNUC__) && defined(__arm__)

#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class gcc_arm_fenced_block
  : private noncopyable
{
public:
  enum half_t { half };
  enum full_t { full };

  // Constructor for a half fenced block.
  explicit gcc_arm_fenced_block(half_t)
  {
  }

  // Constructor for a full fenced block.
  explicit gcc_arm_fenced_block(full_t)
  {
    barrier();
  }

  // Destructor.
  ~gcc_arm_fenced_block()
  {
    barrier();
  }

private:
  static void barrier()
  {
#if defined(__ARM_ARCH_4__) \
    || defined(__ARM_ARCH_4T__) \
    || defined(__ARM_ARCH_5__) \
    || defined(__ARM_ARCH_5E__) \
    || defined(__ARM_ARCH_5T__) \
    || defined(__ARM_ARCH_5TE__) \
    || defined(__ARM_ARCH_5TEJ__) \
    || defined(__ARM_ARCH_6__) \
    || defined(__ARM_ARCH_6J__) \
    || defined(__ARM_ARCH_6K__) \
    || defined(__ARM_ARCH_6Z__) \
    || defined(__ARM_ARCH_6ZK__) \
    || defined(__ARM_ARCH_6T2__)
# if defined(__thumb__)
    // This is just a placeholder and almost certainly not sufficient.
    __asm__ __volatile__ ("" : : : "memory");
# else // defined(__thumb__)
    int a = 0, b = 0;
    __asm__ __volatile__ ("swp %0, %1, [%2]"
        : "=&r"(a) : "r"(1), "r"(&b) : "memory", "cc");
# endif // defined(__thumb__)
#else
    // ARMv7 and later.
    __asm__ __volatile__ ("dmb" : : : "memory");
#endif
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(__GNUC__) && defined(__arm__)

#endif // BOOST_ASIO_DETAIL_GCC_ARM_FENCED_BLOCK_HPP

/* gcc_arm_fenced_block.hpp
PWwO6Ja5RI+YK7qoOu31QyfRXNdJNDc0KeamjmvQfj9d+7uJ5tMDh2H9k3TWnKJz9KjF/pklr/ZHyQV5jBzI+8nr5bFyWR4nV+V2eUAeb4cj7y8PyQfIw/KB8git04txPYvm6cV6mhe/Wy8fIqflw+SMfLiclV8i5+RX2HzIGTt++ZV2/PKr5Jp8jNyUjyWxY/rVYod8nNxDj1qCB/G3ov4flt/jgrXrYALCH5Pm+X/+BP592Bcw+0cx/7WlftSEB/R6fF64v/g6bNcV2JjFxyfn7L2dTj5hRi2tuQ9sf/i+dCz/3vPB9v1y6JK5xPYKrM8XoQdoNLC9YU6yfVjGBzMYS17Osb3DnKa7zDVuL2tO0n7UPi50MXq8xmeus32ARgPdgPXzG3x9jsbDxydn2fOBx99pbvHxGbPP/j3mJrfnm1NsL5pzbC+b09xeNdof+9fNGbY3YX1+5Hij8YzleGfb/LB/p9lne8Zc4vHkYH1+4vk21+myOeDja+YKHz8YbZ/9h6Pt0+1zrD+dMtfoDKzPtxxP1N7O8ZgDjcfs63xG7Tqf5jQfPxz1P4Dj6bX9sX/KnOL2u8xpOmuu6HyaM2wPzFmNz1xv5/jMDc2XuUk3zS16hMbC7XXMtfOp8Zlrmi9zXeMzN9i/COv7YI7PnKNr5oyer5E5Xy1zk9tLzrPtc3+pyOM4PnrUcrZesrvVPk3Oyx8IHf88xMVyQe3L5bJ8nvWXr5aH5DXysHy63D5fn+/ktNwXOv75ielyj9ovlH358tDx/w9whVxS+zVyTT5VbsiB3JJX2fh8eoOckj8cOv59kavkLrWvtfHK823+5HLo+Ocrqjafat8SOv75iNWh479XsdGOJ+yP9fKgvFVuypeExrJAn3fteOSZoeOfhzhNzqj9g+Zz2H6mjU++SM6q//lyTt5k45cvsPHLl9r5kM+xz2fyuXJHHz3b5luuhI7/HsKHbDxq/4hd3/IyOZA32/HLc+S6vMKuZ7nfxif32vW6UN/n2PNLXmnXi7xELsqn2HzIV9p8yHPteln4yPcF/41LsGkS7zNf5/XZ/CFy+DZD95/VB9M5rs/erva1er4+hjm3ZvT5188jTwmv19Pt9YVu0qOWaeHn5/j+Mz00Fu1vhtyx9sFdb9b32Md6fN6lmP/4XmZbNl31BDj+YuYZ+/w8Nt5/8PuXwyfp9Y/OmrN0zlyhfRoNdNHs02VzQFfpUQuOP2wfUPt0efDwSQ9qPu534fieGd4fXhaND8Zqc0AH5hJdNmfpmrlCD9JooIfNddp7OY0LL3SHucH2tDnF9m5zU+MzZ9heMLfYXjLn2F6jRy3T9X3RUPz3qzh+9V9u7fIKeUReJne8gp4pp+V+OSvn5YI8Sy7JvXJNnmvjkVfLTXle6PjvCQVyS+3zYf77Fe3LXXKfjU9eKPvyYrksLwkd/z2ilTZetZ9i45VPlYflpTS+qKALoePreZWcetnDdH3/s5fWuPHhZX+8jbc9dM2cpOvmFN0wp+lhWJ9XYCwn2PONTpkz7H+0OUt3m3N0j7nJx/vmBh2YffYv0WigK9H+dTw0GnQ8sJ7/PJ5o/3Qz2j7dirZPt7/Btk+nzBm6y1yhs+YanTPX6cDcoEuRdTxRf40/2t44jtfcRHu4Q+vP9g4aC502J+mMOUVnYX1e5XjNac2/OUOXzVl6wDz69TJsH1L79NDx56UZckvtM0NjeSO9SE7KeblTXixn5CVyj3yq7MsL5aK8VK7JBbkhB3Ip/v/OOF61L5fb36T7rY1PXmXjk2fZ+OTZNh/yHLkg99p45blyWe6XB+SVNn55vtyUfRu/vNrm+0R6Qej4/Xuf3KH2U+SuE/9L7nc=
*/