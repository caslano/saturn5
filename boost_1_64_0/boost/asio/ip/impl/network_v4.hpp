//
// ip/impl/network_v4.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
// Copyright (c) 2014 Oliver Kowalke (oliver dot kowalke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_IMPL_NETWORK_V4_HPP
#define BOOST_ASIO_IP_IMPL_NETWORK_V4_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#if !defined(BOOST_ASIO_NO_IOSTREAM)

#include <boost/asio/detail/throw_error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

template <typename Elem, typename Traits>
std::basic_ostream<Elem, Traits>& operator<<(
    std::basic_ostream<Elem, Traits>& os, const network_v4& addr)
{
  boost::system::error_code ec;
  std::string s = addr.to_string(ec);
  if (ec)
  {
    if (os.exceptions() & std::basic_ostream<Elem, Traits>::failbit)
      boost::asio::detail::throw_error(ec);
    else
      os.setstate(std::basic_ostream<Elem, Traits>::failbit);
  }
  else
    for (std::string::iterator i = s.begin(); i != s.end(); ++i)
      os << os.widen(*i);
  return os;
}

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

#endif // BOOST_ASIO_IP_IMPL_NETWORK_V4_HPP

/* network_v4.hpp
s1G+/Kzrj/nauzr5c4yS4vqENGNGr2sJJzvX7LmPzDtkLcV9lvBbXMWADnUKRmC94ip4l4ztUGA7WGJ5isN4zC2F7niCqCelWv56+MPxECZqJcHPMyU+eb/CLhQCm1WxRZtGYBmHrmfUaRgfdoopa6sPLApM/EC1aZotQF9ktyljgkDHP7wt645aiG4f0PK953qzgIMCFiTdeS2b3ajqwAgIKNIMEilucxKmiVYnJbzdc3wBEd7rcLItq3Vngpm+BA9ZQyxY87IHhFe+eUIeitgDNarN+TWbwr4W1FNFyJl/2s4ehecNbanoG3qt+LkxnLE9aRY6qQABhdvmcOqV2Jq0fw739ysEm/Tpg9JspWnUdA4diixXQVQ5534yOAff872YX7hOJQwjeVWtVwlgo/7K2o0u5dI4zNsWAA3L6YQW3HeL6+8Yc9zmF7JgBebOFUr4zmlkfuW6rhB35wFx54I693qYlcUcgef+GEFg5BvKFDb/CGQRPnv0eQxv1NljkXTwg4lREZQXq1t5fPy0/nQIjV9zynuO8QlEivycFX/Vkl13NBoSw8zk6g==
*/