//
// ip/address_v6_iterator.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//                         Oliver Kowalke (oliver dot kowalke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_ADDRESS_V6_ITERATOR_HPP
#define BOOST_ASIO_IP_ADDRESS_V6_ITERATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/ip/address_v6.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

template <typename> class basic_address_iterator;

/// An input iterator that can be used for traversing IPv6 addresses.
/**
 * In addition to satisfying the input iterator requirements, this iterator
 * also supports decrement.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
template <> class basic_address_iterator<address_v6>
{
public:
  /// The type of the elements pointed to by the iterator.
  typedef address_v6 value_type;

  /// Distance between two iterators.
  typedef std::ptrdiff_t difference_type;

  /// The type of a pointer to an element pointed to by the iterator.
  typedef const address_v6* pointer;

  /// The type of a reference to an element pointed to by the iterator.
  typedef const address_v6& reference;

  /// Denotes that the iterator satisfies the input iterator requirements.
  typedef std::input_iterator_tag iterator_category;

  /// Construct an iterator that points to the specified address.
  basic_address_iterator(const address_v6& addr) BOOST_ASIO_NOEXCEPT
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
    : address_(BOOST_ASIO_MOVE_CAST(address_v6)(other.address_))
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
    address_ = BOOST_ASIO_MOVE_CAST(address_v6)(other.address_);
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  /// Dereference the iterator.
  const address_v6& operator*() const BOOST_ASIO_NOEXCEPT
  {
    return address_;
  }

  /// Dereference the iterator.
  const address_v6* operator->() const BOOST_ASIO_NOEXCEPT
  {
    return &address_;
  }

  /// Pre-increment operator.
  basic_address_iterator& operator++() BOOST_ASIO_NOEXCEPT
  {
    for (int i = 15; i >= 0; --i)
    {
      if (address_.addr_.s6_addr[i] < 0xFF)
      {
        ++address_.addr_.s6_addr[i];
        break;
      }

      address_.addr_.s6_addr[i] = 0;
    }

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
    for (int i = 15; i >= 0; --i)
    {
      if (address_.addr_.s6_addr[i] > 0)
      {
        --address_.addr_.s6_addr[i];
        break;
      }

      address_.addr_.s6_addr[i] = 0xFF;
    }

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
  address_v6 address_;
};

/// An input iterator that can be used for traversing IPv6 addresses.
typedef basic_address_iterator<address_v6> address_v6_iterator;

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_ADDRESS_V6_ITERATOR_HPP

/* address_v6_iterator.hpp
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
*/