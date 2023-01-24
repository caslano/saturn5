//
// detail/local_free_on_block_exit.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_LOCAL_FREE_ON_BLOCK_EXIT_HPP
#define BOOST_ASIO_DETAIL_LOCAL_FREE_ON_BLOCK_EXIT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
#if !defined(BOOST_ASIO_WINDOWS_APP)

#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class local_free_on_block_exit
  : private noncopyable
{
public:
  // Constructor blocks all signals for the calling thread.
  explicit local_free_on_block_exit(void* p)
    : p_(p)
  {
  }

  // Destructor restores the previous signal mask.
  ~local_free_on_block_exit()
  {
    ::LocalFree(p_);
  }

private:
  void* p_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_WINDOWS_APP)
#endif // defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)

#endif // BOOST_ASIO_DETAIL_LOCAL_FREE_ON_BLOCK_EXIT_HPP

/* local_free_on_block_exit.hpp
CGgT7cGQWZwIjLszrCR4OhUr/rJI32a7jwgHlg0erg/gBzRJT0SYT7b4cG03kLjSp5Po/hkF4SokfH6JPBF7BYLQeSAyedUgLOfZeI6EcHh1Xtgb610UzmNAqfKRPB4KWsRKwpR3SDVHEye9wxZl9a49cZYgfDB+MnIdQGyxVyV2j1cn9oMbgdgy3Q2TFj57fxfbLTcbJwfhMDKQOh3s8rnyZnjzb1omEVCGg8CjnMfo6kL74Sqyl4ZPhNDgWwBrUh//6feOZRmk/uH7B5D6kfcPPkr0f/frTW274X80SsT/T0eJIo3bdZ+hcakoYnja05X3dYWt9WVczXRUqbJJAyr3l/fpzYy54X+i3Pz/WrlTtIbK8pse2h5Rn3ZPT7vWUy+2sBSBjihPykiBFLHczrbpoHHkEXK3R2/q2BXQ1Duccgg3cz1VOrVdPg7fgFllEFlkTOSLcAhJaJPenvpGVmhDrrSverS3uNd9EMePkqsd4FQuzUg2wy8hdm7GeLPQlpGCSVJub341cCob1DQWShmaD3qAxdmUl6VPomz592igLN4QCuOS7No0bffYCQa/OZg/pS0ocd+JZHlYpLHTlmO+21Sn58In3Pq94XSP5vaoc8JAz8dlpsBTb0aeUsrpqQJtn0pZznFTRxDKALU6IWc+vpmy2eAommQkxOBMkukZqfxG6BJgTzbuikPTrJT96vSPkdWlZmDluOq4
*/