//
// ip/address_v4_range.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_ADDRESS_V4_RANGE_HPP
#define BOOST_ASIO_IP_ADDRESS_V4_RANGE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/ip/address_v4_iterator.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

template <typename> class basic_address_range;

/// Represents a range of IPv4 addresses.
/**
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
template <> class basic_address_range<address_v4>
{
public:
  /// The type of an iterator that points into the range.
  typedef basic_address_iterator<address_v4> iterator;

  /// Construct an empty range.
  basic_address_range() BOOST_ASIO_NOEXCEPT
    : begin_(address_v4()),
      end_(address_v4())
  {
  }

  /// Construct an range that represents the given range of addresses.
  explicit basic_address_range(const iterator& first,
      const iterator& last) BOOST_ASIO_NOEXCEPT
    : begin_(first),
      end_(last)
  {
  }

  /// Copy constructor.
  basic_address_range(const basic_address_range& other) BOOST_ASIO_NOEXCEPT
    : begin_(other.begin_),
      end_(other.end_)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  /// Move constructor.
  basic_address_range(basic_address_range&& other) BOOST_ASIO_NOEXCEPT
    : begin_(BOOST_ASIO_MOVE_CAST(iterator)(other.begin_)),
      end_(BOOST_ASIO_MOVE_CAST(iterator)(other.end_))
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  /// Assignment operator.
  basic_address_range& operator=(
      const basic_address_range& other) BOOST_ASIO_NOEXCEPT
  {
    begin_ = other.begin_;
    end_ = other.end_;
    return *this;
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  /// Move assignment operator.
  basic_address_range& operator=(
      basic_address_range&& other) BOOST_ASIO_NOEXCEPT
  {
    begin_ = BOOST_ASIO_MOVE_CAST(iterator)(other.begin_);
    end_ = BOOST_ASIO_MOVE_CAST(iterator)(other.end_);
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  /// Obtain an iterator that points to the start of the range.
  iterator begin() const BOOST_ASIO_NOEXCEPT
  {
    return begin_;
  }

  /// Obtain an iterator that points to the end of the range.
  iterator end() const BOOST_ASIO_NOEXCEPT
  {
    return end_;
  }

  /// Determine whether the range is empty.
  bool empty() const BOOST_ASIO_NOEXCEPT
  {
    return size() == 0;
  }

  /// Return the size of the range.
  std::size_t size() const BOOST_ASIO_NOEXCEPT
  {
    return end_->to_uint() - begin_->to_uint();
  }

  /// Find an address in the range.
  iterator find(const address_v4& addr) const BOOST_ASIO_NOEXCEPT
  {
    return addr >= *begin_ && addr < *end_ ? iterator(addr) : end_;
  }

private:
  iterator begin_;
  iterator end_;
};

/// Represents a range of IPv4 addresses.
typedef basic_address_range<address_v4> address_v4_range;

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_ADDRESS_V4_RANGE_HPP

/* address_v4_range.hpp
gn+P62NMI/wC7d9Dxt/9yp80k8U/TdZePKj9y4xOXNmOwD/YGklT5+llajGJes5nj8V01sf8wHgYn2eo1zSdho/QUNzeur8U4R4o9/dyqbe71Hsg/obDgYQegYSb5gf83QIJDKfmnrjcz0Lk3RDRK0TvU0qva0Oruf+AxBkicQ4Q55MpKu2tY5ITecM40Z+cBLqo/+J5x8XcR6G2rsZyz3Kpzu8AHb5ZlxhjoIRnweU6fKA+1miO3UX1DtL5BINbKTyFTMWW0xa/lUi5vDPQbLj9UVh6HJmc2gQX+Xz63uN7FXLvsWqtdn+rwn4vUjky5Bvsek0/bvoCbhn78Uvx2fZGwC+Q+iE1QL2aQB7Ky+rlfbESyPhGPBnfxL8I0p7wN9sTx56U+oJuc6ztzDVs39GulBca+kjGeiN/wMaU4L3wVZQ2hoxV7d61DjjvSdw+rnWQCtM2ON5f9bzPmWTuLaGOYb8Xm9LZeS/2q+q9wA3mvVjz1D17YfGSy9XNWLG7aLzjXix67b8XS3pyL9Zu43EXG7+OjSWeNl5TWrm5zNPGErHRPMfLu2HmfjoReVjQzjzY39XkGB33mP+p3xN3v1ftfS+5QN9LTl3WWLFryG1He47pNviuS/v9smM/aus9Zmnz+jyynHivGMHzVZHaC95A1/L7T0hznMyR5RqgQZ1P1LlIng9my/ejB8DZcDicC0fAK2AerIWj4fVwDNwC8+E2OBZ+GI6DH4MXwDvgeHg/nAgPwknw23AyPAynwefgRfAFOBX+WPxbYQF8D06HCXJvOgvOhCPgLDgGXgyXwDnwMnGvEPdKOBeWw5XwVnglvAd+AH5O3PfDVfAhWAIPSvhRuFrZB9fAn8EyeAKWw9/DCtiNstwAc2AlHAWr4CR4NZwi4YXwOjgPXg+Xwg/C1fBDcD1s4N+H4E3wFngz3AlvhZ+Et8G74Ha4F34Y7oe3w8fgR+HX4E74TYl/FH4CvgZ3wV/AO+Fv4D2wFd4F/wx3w9PwbpjpD6YzFE6DeXAvvEDcc+CDcCF8CC6BD8P18IuwCn4J1sImeA38MrwPPgYfhVvgV+EN8OtwnrITHoC/gk+Y69vlHCzncdq+bX37y8RTfAXGwVdhV/hT2BMeg73ha+azDTk3ynmsKOLZxhxLvJJo8c7wGUhgX8cewx3PQDqegZzpHsPRnn2M+wv7ByOVyK6/dDwD6fjr+Ov46/jr+Ov46/jr+Ov46/jr+Duzv3jkqn/F8//Kzerx/1k/+59hefafH+fc63uc2tvykvCz//mLFs1bWqR2FSytrCit1ffeX9Nr9NfU1YfvzYvOKB3+XpZ9/+4ehhnu+tykKKxvf34v4RUR4evTCJf19+H9vSWOub937Ht6kx/u85Mfy57I5MG2d3eR/VmM7Ikc8XxKnkVhH37YJ8+behTKd8XG2/fROujyzYHziJNf6Fb+66jLshp2T64iXa96QDd6PUi46z7qRaIfpR4Ib7se8gv/ufVg2UP9jOrhUqmH8yPqoTDBWQ+jiVPtVg/yZWr5GLJnPVS3UQ8S7vq94KKwvud3lBerODHURfU/uS6s3yLOlLqwf3PZuz4+KfUxZrx9T8sd8g2CsVIfo5GRxGlyrQ/Znc+7T4jeWM+6kHDPupDwyHKWejDDY947MbJsJ7qUbYG9bKUOnGX4ipRh3nj7PnhJ8ix7ItJVynKYGtudZbimrsazHUv8ieZ4QPjG8B669nD5tkPN+jVSdhH6aYaEV8p4EhG+P91jXD+HbTg4Tqg8RI7rQbtlPIHiVxluv9hnK/vec4JlPzyi7F+Usp+N9BD+nJCCOY6yX1dTVuYse1kLtGKOdR/8kH62uFnNpt0+83k=
*/