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
KZ+0LwJcrEXf8MyGggovN5mBDJSd6Wu5qWXI5t1OOe4p5yt+KZlhpq3vwxROIqYG7sTjoWLOJrNsGS4PVUFQXraYlnyvCYe2R4R3SY33r4cSsijetRTdkM2V3xBTAawcriHaifnGC3NgvNip5I3i6FmqwugHaW3Rg92sqG/dUoNqfIuizzz3EjkE65Zjm0fgWsl5dNMqqDZjp/OV5fBamR36FNSQjA4EmcPNqI9qGEdsDEpsNfUI3febMXX0UjoCu9lEbWsjIg/s/HzB21J/VgCcbhZVN7mh7h/QGTe3ZbK+cgm9NwrQWeLa8QiMvijugCGubpmHdAkRSfX6lT9N6s6vsc1bzztb/6IYzL1cbpIJ73Nd/SPj/fTz8hOo2/IIUrzrUggLvpIhG2olUHeWD1zjLPA10Z7l22Mjc+l2P+NagYiWfGZk2aSiOUOalninqV/vMzd6ubwiukIofBCDrprl00kGiCNOQ8yUQH0eDXN8USpvsRsuB2sjtwN1eFHeLWLN5gC3S/73lU7J5Lc34zecf5gcAc+rX9ehCYBgTbHTB9dpJ97AboSTXv9oXDB40mQ1U+E92uX45h9uuzKbZDffCX6sFw608extlXS7nhj8ToTch5Zer/7jMZlNcBb9xP2u8715bvu7rivlekM3tVN0eFqFOeD5sTKHYX9Xg9B4zVnpFris9jDocWGSBNBr4mhh1X27SYm9tjtg
*/