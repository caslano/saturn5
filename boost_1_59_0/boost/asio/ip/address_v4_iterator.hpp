//
// ip/address_v4_iterator.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
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
*/