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
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
*/