//
// ip/address_v4_iterator.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_ADDRESS_V4_ITERATOR_HPP
#define BOOST_ASIO_IP_ADDRESS_V4_ITERATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/ip/address_v4.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

template <typename> class basic_address_iterator;

/// An input iterator that can be used for traversing IPv4 addresses.
/**
 * In addition to satisfying the input iterator requirements, this iterator
 * also supports decrement.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
template <> class basic_address_iterator<address_v4>
{
public:
  /// The type of the elements pointed to by the iterator.
  typedef address_v4 value_type;

  /// Distance between two iterators.
  typedef std::ptrdiff_t difference_type;

  /// The type of a pointer to an element pointed to by the iterator.
  typedef const address_v4* pointer;

  /// The type of a reference to an element pointed to by the iterator.
  typedef const address_v4& reference;

  /// Denotes that the iterator satisfies the input iterator requirements.
  typedef std::input_iterator_tag iterator_category;

  /// Construct an iterator that points to the specified address.
  basic_address_iterator(const address_v4& addr) BOOST_ASIO_NOEXCEPT
    : address_(addr)
  {
  }

  /// Copy constructor.
  basic_address_iterator(
      const basic_address_iterator& other) BOOST_ASIO_NOEXCEPT
    : address_(other.address_)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  /// Move constructor.
  basic_address_iterator(basic_address_iterator&& other) BOOST_ASIO_NOEXCEPT
    : address_(BOOST_ASIO_MOVE_CAST(address_v4)(other.address_))
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  /// Assignment operator.
  basic_address_iterator& operator=(
      const basic_address_iterator& other) BOOST_ASIO_NOEXCEPT
  {
    address_ = other.address_;
    return *this;
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  /// Move assignment operator.
  basic_address_iterator& operator=(
      basic_address_iterator&& other) BOOST_ASIO_NOEXCEPT
  {
    address_ = BOOST_ASIO_MOVE_CAST(address_v4)(other.address_);
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  /// Dereference the iterator.
  const address_v4& operator*() const BOOST_ASIO_NOEXCEPT
  {
    return address_;
  }

  /// Dereference the iterator.
  const address_v4* operator->() const BOOST_ASIO_NOEXCEPT
  {
    return &address_;
  }

  /// Pre-increment operator.
  basic_address_iterator& operator++() BOOST_ASIO_NOEXCEPT
  {
    address_ = address_v4((address_.to_uint() + 1) & 0xFFFFFFFF);
    return *this;
  }

  /// Post-increment operator.
  basic_address_iterator operator++(int) BOOST_ASIO_NOEXCEPT
  {
    basic_address_iterator tmp(*this);
    ++*this;
    return tmp;
  }

  /// Pre-decrement operator.
  basic_address_iterator& operator--() BOOST_ASIO_NOEXCEPT
  {
    address_ = address_v4((address_.to_uint() - 1) & 0xFFFFFFFF);
    return *this;
  }

  /// Post-decrement operator.
  basic_address_iterator operator--(int)
  {
    basic_address_iterator tmp(*this);
    --*this;
    return tmp;
  }

  /// Compare two addresses for equality.
  friend bool operator==(const basic_address_iterator& a,
      const basic_address_iterator& b)
  {
    return a.address_ == b.address_;
  }

  /// Compare two addresses for inequality.
  friend bool operator!=(const basic_address_iterator& a,
      const basic_address_iterator& b)
  {
    return a.address_ != b.address_;
  }

private:
  address_v4 address_;
};

/// An input iterator that can be used for traversing IPv4 addresses.
typedef basic_address_iterator<address_v4> address_v4_iterator;

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_ADDRESS_V4_ITERATOR_HPP

/* address_v4_iterator.hpp
dGmnM2C6Cpd2OhP2FfcAcZv71NV4l+9AGWcHSbvMhRnilvLlesy7XaZLO8+A8TDTMk4fjXLc7nLcFDluqhwXd7g/1HjXq/k+hNTrp8xxVeb++hzlHFd7ynryvnA07AfHwv5wMbwQXg6nwCvgRTK+D4Z1cAjcDYfC++FwuA+OhE/B0fBZOAYegefBn8Dz4c/hBfANOB7+FU4K15PMjbHNpbyGSnkNg+lwhIwfw2ESEU+xVjP9T/6Y1l0HPhjD2usHwuuvDz7asQb7TNZgv/zof+Y67FOPtm8tduAx7MEv77H/zzXZLXvPzbrsPPpnEVKPNCKHkVakz9t+oxCpRHYhB5EWJOkk67GRIqQeaUSOICeRrD+zlxVSiexEnkSO/bljvXbHX8dfx1/HX8fff9ffv279//n152L9v1rLf7fle/0tcbLvt49rCpgLvzFBbcZvf5Yjz0ws6/VqzHvnxJVnsvLMWLu7Wr6Dv7b0ulpz3QXx7d/q/4J2J/vcnq0UmekPML+neJ92Z+n4zcE1flXWb7BnVarwzto9H/cA7a4Tt8+4E7d8m1Wen8iTUksaZZW2Zyiik4RbPy+S5zLhZ+Bf1Db9TX8P9CD+asqWy8VWIH55IKGz4fgu81Tc3XDfI89WQvuhHOPe6b34HeTic2qvoPwMv8/gdyCH9+9h3/TYnrdgs+N5izyLiFjHr+pHnre47hMk30PyO79H9QAXoCkbbd+jml5cvGTOjKXFs63fORvcy+WbVBvb/50z0tPfnOrYK+Sfu1fIuXp+Epim/FNu/G35Z97MWd57XvnFO47XzfnPe07yr9wrRI0PSeRzmTwDaQqNjTIe7464B5Qh94B6w7GwD1wM+8LlcBC8CubCD8IhcCfMg7vhKPgQHAO/Cs+H34Xj4GtwIvwVnATfhVNgCjZMhRlwOuwLZ8BcONO61/7G8F77Sda99uUZwI5z9W79Ax3v17fn3s5/4n2d9tzT+X99v/5c3cspeoc9xt/puN/S8dfx1/HX8Xe2f/+y63+u/c/V9f+dlnf5m+Ud09/4mRcKX1N7dq8LX/8vnL5g9qpNVWWVFVXm/qcZ5rd5Z+jryJU6/iN+ubYT/dnmesgy7R7of9s46cvUfj7jtgrld5MxgSekc40sfZ1Ynajf7d28TtY8zjPT2mYsYgbbT/an3KP9yvy9jCSeYfZiHcZdcX39s5zv/xK/3CWNcksaaUZ35sw5kWnwxwWspNETblmv4m+Me8tXbmQrP1wp2u/duErjLd+X4uKMb8Wxb21Y31xnOVjHSzbfR/PpvPeTcL4SvD68F3Qav1rLlbuclbsXWOyp3FS5ljm2vKe4Qcep5jPjzEVYmRH0D5frUNrFXJUm+k/pF3lYJboqWLbyDrR1TaiZ7l90uZyIq/MdN3bGFaMfme4F5nr+v+m43fzhdCrNPFdp++J1uhvV2n4d92Tcdb5447NxU8XfZ3xSp3uNMUzfa6D85D1xHojrOAvRHavL58txCTwJHx9XTskp/3D5D+Ip/zQjO64pzid1EHrf9mrzPtKr2p5M853xnVq3ifypcClz4s+nngaqOPgVaL8nfOot3stoJ7exomqrL8W4xxe8F7RSv8MQ7Bdpcn+qr073SNx87MzWfmE7uxrz4x6MSzJtrA6+q2Cu7/2CPt4e9fap9ivGb7Uut8H+Lxqr40LvLlyiyyxAORDHkv4nfXHGF3y7iJlhPBIXr+upQF2D6TQe81va0vn6Xo60x/P0cR/yXUn53qTakrTDx7X/bF93VoD9jv5s0T8vlOcseL0+/qa4F3y3yP6/jv6t87uDhkGOtN4y8rZE2/UVfxktSLXTw8MMevT62lVrN1XUaftm0pY=
*/