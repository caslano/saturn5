//
// ip/address_v6_iterator.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
KXrQO1V+EC1SiVq0wLPri6LSlgxKZIr2D9tF7u1ekHTaS/wct1dLpdy3VmlufafwYr9KDFvwnwyZetwZLum4ttrP9R6ZWzrusBfCmAqSLpSiobon2i95G32qNE0yHsa1RZUBWSGH+gMS/kG+7IHZNJRZPzAnx6JHiusOMDCy2aHaPFPza5Kc3z5nnSyJB0tOl822KtgAQeaFvt9mChMkRAxwg83CyVXz/zFVuItClURkVcB0oLzDJU3peGdIAFEIfwyR5JvXN7g12dWgeh4GfxIxVPPr/mriC3cvvpY2zYh1Gfz0Hh+2Ba1/XxiABfUJbMarwuDKH4DaAZLWCple2b4v8mvuJb0FJMhxQQW7AaOUc9fCCFGNLj71l8fjklrOLSV8fwsbc/n+5jem8v3NDRlaz6/31Lgy6dprXgDNjIuPFsyMC48CZsYFkBIWKHtCDvJZ6rk380n85tazSaCz6+kkfrP9luctrRPqfVDn37ybYdl+CY3vvLek1lffD3mQsKwlL9YCSN9/BsQvqE9NX8WZZmTPkYiy8wH5XIm7D9vMtkvq/1QhxMHSFhyJA1hKxrgfvsq78AwJqvZ8LbQ+z4p7G13n6Ftbm2dUTqNIWmAjCaArGeN9kCvZVt7Ci/dnjVdgE52UGDteivtXFEzSTVVSz+cNkoflhdL1aWzMZHl9tC60XuWIE08wrOB+EPzbFR7pccQ1WTBSU0jc
*/