//
// detail/signal_init.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SIGNAL_INIT_HPP
#define BOOST_ASIO_DETAIL_SIGNAL_INIT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_WINDOWS) && !defined(__CYGWIN__)

#include <csignal>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <int Signal = SIGPIPE>
class signal_init
{
public:
  // Constructor.
  signal_init()
  {
    std::signal(Signal, SIG_IGN);
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_WINDOWS) && !defined(__CYGWIN__)

#endif // BOOST_ASIO_DETAIL_SIGNAL_INIT_HPP

/* signal_init.hpp
9+EptDogNsn5hHxYPDfcfy5SytkpmynJ2d6daTGDiDzSb9uGGrpcEvM4GnOCMAHJrTSN7NzZDqkMQhIZp1cMcii0QUPz3UbqXqwIPdJMMrBOHoWXsKQdv8tRa9v2GOtp/ka0dRkAHfa6NondtQcmscDfkAyi3uAS0bfBG8itiqV5kdJwaZm9WPJY8FTTPLM0L0bakChtSJA2xFOykTbEtj4M1cPKYIfL7XYjyKxZcs5OCscSdWob6dwhZce25ij05qxss5Qdg+X6nM+7rs20UOXJ+Qr17h7Z7nzewEf1xfM+gYi+ew0IXHakWP4aJ/QRy/dzQgTAFPCgzsznfA2olTzPCsD77H3OE1SbpsQ9o4bWouMcKNjZ7ILHZ/g4g49P8XESHydcZOAydHiSIGUniOWv0Hr2QD1ydkLgXlbPK2H1rOu1nkU/pZ6/LlXriRfLX6T1vNS9nhfD6rH0Ws93V39CPVlaPYk4r2bHIl77og4XUSndLm2wt+5BTzXCM3LBtlyy7Jc4VMnRrZTc9y7VqI7843Yq3pCSPwWVOmZ/1aKOX77HeP7ly+o8nOAmxVOou6MRJev+FG0vWXi7EaSHRKQ/ELPocQkQ3ixQbmCJDGLyFJpadibwt6IWArURVCeZCNI69UtyEQ+2gTja4GyJR2METYxUTgaG9nEmgiDa41SfErcciAqtN3bsmFFatIIvylq1uuhWDq31/gzc
*/