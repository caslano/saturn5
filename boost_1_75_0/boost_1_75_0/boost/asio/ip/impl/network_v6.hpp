//
// ip/impl/network_v6.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_IMPL_NETWORK_V6_HPP
#define BOOST_ASIO_IP_IMPL_NETWORK_V6_HPP

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
    std::basic_ostream<Elem, Traits>& os, const network_v6& addr)
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

#endif // BOOST_ASIO_IP_IMPL_NETWORK_V6_HPP

/* network_v6.hpp
ZiG7GuFKEIIhNJ/TKHhP6tNLvmXngE/RXmsyun3A7Y3uIOuUwGvWcK5BpvflfzNgT1t0/ULPa2iDyIOhzet7NAvQGg6QtB1IJn1PXz/T80Tf3/ClkQMHZaRdKPHcrz/DVzqe1h8OWinQblpef/Z7fMrBfCDxth2v0i0389P9TctreVkgNgcUv+n+fIRU/BL8+fZ8TYXV0/A9nnExza4rDf3GFG7jGvzUK+I6kc24DlfJZpPlCl5C0PAzh5vC60zhStPsetPsK+OeVLEPRZu5QFKpnxPO4LOm4XV999F4dn29OT1QqHMMqceQenLRz4bPq48B5EMgD8PFIBhocof8rfcbLqYQq9ba1XDxKWKdY1UZLr4KVsMhUEiMqT0foRl0kO2Lx+RYdaTeewdunFvvhTqyanbQC447yFvMcv5gh95Meyazt4cPE23uzl2z8xH+ybhh7xmApU6OZMcQXdQ5Uj/+7CV8ZzH8Cj7/dNw6yOE8hE4/h9OCzg4OZwU4zYWP3bYD7zYrWWWA3X4d7YFnQ7M1M4vv0/cvrmT7JpgtN1F5TPfHa7VgtHtcwU1RaNTvx9/i91l+UuP1xTrzKxqgyRR+DpvI2x7oV29epRHa3TrwuOYlB97pu73NMEqG7ZRgfg7QctMV8mTEZN12zUuh7wtk9E4wL8br4lBavLsLJkRS4LViEm/1+fDjNfENdn2DeRBFzwZBnPPV7ZLm
*/