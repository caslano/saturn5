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
Qu8avq7dK32rjGvZ2znPdb6XBafrdA8Qq4e8NxMql1TPfr1WhVOOxVpnhr5XNE37fVn30T4kvDM72EcDaUP8GcmFZieNT4y9jz6u8zDGGB4lX9JPOWZwD6EM3U8HBPw9DWc/lXjHiHeFsi1p61OhOAVpMl+VOOm9g/3Jv/WW5NmJ3fyB5A8mBgIZnZ3X3/a0J/YOpd3wRjhte5yVxEkPjhPZjnFC4jT0NscJv2OckDh7iJMZHCdqIseJ0LcsLncZF5gXwKD0O8fjQolzXDDP10f7y7u3GNoTvgpXjyeNJV7jgjx8kG8dHkHfZ4hXeHwQ/RxzfGjR7md9Czi6fUwJz51f03Ge9hXSSmTMkHT6Or6RUmSGZUufxXbtfs63mHmM175chZfqfbe0uxj3Mu2e6YuYr5r7gi0pNr9NghsF7b7TWIJfuI9U2/p9qo6zUvpMSGefkYqf27VGiQ7vSnzc5jG2GSX42b8PGp5Hr9R2DyBGp8hxxEz31zpOL7d09ZgwjnNCYz85b+eo8zbv9uUkJCYG4iYH4jrFPCac0uWe5BvP/2551v1Djneon1ybZmxNi7wuzZQ4rf3kuqTz1rGBzhvd32WUuOn9pU92c5y7zfNyv17hPnclsjfLdm7W35Lp34sw8xzddv8LvdtH+6dfSfs3+6C9X3aTPijfmdH3La9XdYPfuvGGdk8sNt22exiHBgUPOpjAATAAa9Q9jKUe/dN+e8nS166ptfRP9KM+j5LwPLMfrNTu33rdw5D4I8z98VZo97tez6sk/lDcwb67TLv/quNnqIzK2BDqU8WEA1/4HnjlZmu/fk6HDxO3z/iLdicHvzHYS88jeDEz+M55Di63ucN7WifNfNe8Wbu3GhfhE45/ldkH39bhAxhtsoxM7SfHVV9TItYkajLcZzi8ZR5zi473HX0drM5vL9KO6gcy3qi+OIUTc0ryUHpj13j7/RBTv1Ly24sUHP1f7NuyVO5LiW27tDugvzXXTBkXDQxdYy9zXGOH4tQNlP6aMsVxH0lJtti+j3gf0H32+kD8Am47ud9LMOMfJv7FKq8N9zDwpDELSUnUx5XwE4SvUuklN+w0bYtIow994zKdxh8TA/4uiQm8+my/zrbfLyjX59e2+7b93Eq/Mfu18x5Yicsz0nLrM1LRzYG0Q/x0O9R9vnWp/bnp3NDzpMFBY/YgfZGPIzeq+8mXefV5Tj8x9vtgGoPNb5Q/o911XuOAxB9onlOe1u4tznFA+mmzDr9ZxoWQfo5u44cHqfed5Xwz2Hq+SRzaxrkGt8wRdHrLLPUqY3sM3/+Se5bhej2DdQXWZw/bhwYTXe6jTuEl8Dl1LbUssn74ery+vWHIuOa4jhKdgeY86Q7tvsDH+dox55lnxu9vnns/rt3n+9Jt8wApM6mz93WcWnFzNb1cuadb4mNn2Vpz3KhYLntmyNi/Q+vn+9IYO17DX9Vl+WDqdkiw/wXiGm5P7kIXTKILJnUx3PrgQNE5NUSuQRInJyfTBNLNKcfoNucboTbwXW3P74NzBkk3Zyi5UOkGGt4KsENF5By+H+5EGQMulf1O1VgwT/0+g2/XZ0Sc1wvD53VbG9k/PKi8WtrIYvj98dh5uWsbYfWDZxsRnUHmdfNM7R7rCxgBuZ61tRGJn2O2kQLtvjBqG3lCx6kz28jwFco907ON5OjwBN1GqjjGRVp/lq8v//8Sf9VGdlAnh4aZbWRHclcZpr3aiOj0GR5qIxdGtJFxMbeR67U9fwm2EUl31nCzjZwM+P+1bSTB5V7zMPlAyVsyzr+MTGacb1nh1kYqN23asLna3PsoOLZLGwnp5JrjevwVyv1N4pprDaR9hOKOMPcm7qI=
*/