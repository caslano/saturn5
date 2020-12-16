//
// ip/address_v6_range.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//                         Oliver Kowalke (oliver dot kowalke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_ADDRESS_V6_RANGE_HPP
#define BOOST_ASIO_IP_ADDRESS_V6_RANGE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/ip/address_v6_iterator.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

template <typename> class basic_address_range;

/// Represents a range of IPv6 addresses.
/**
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
template <> class basic_address_range<address_v6>
{
public:
  /// The type of an iterator that points into the range.
  typedef basic_address_iterator<address_v6> iterator;

  /// Construct an empty range.
  basic_address_range() BOOST_ASIO_NOEXCEPT
    : begin_(address_v6()),
      end_(address_v6())
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
    return begin_ == end_;
  }

  /// Find an address in the range.
  iterator find(const address_v6& addr) const BOOST_ASIO_NOEXCEPT
  {
    return addr >= *begin_ && addr < *end_ ? iterator(addr) : end_;
  }

private:
  iterator begin_;
  iterator end_;
};

/// Represents a range of IPv6 addresses.
typedef basic_address_range<address_v6> address_v6_range;

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_ADDRESS_V6_RANGE_HPP

/* address_v6_range.hpp
435Dl+XN4817LuaY7tPhzxlec6/+Ojxd3Nyr0O4M1zlWQIfNEncoboJ+rtFE/bSOkHmEPzeQkBTw9+WxhOv8X+Knj5R5QpcLHHOYfhKnjvA5iH8Z86peyWXJuWo/kzQzPm1J8uZsR0XavnJxm/babNhN2quD7erOyDYVytchwi/Rc5WHMCINAzISwmtm2nwuZ32OIe3rGu2eGF67oecUZVeY6yG0+3O43dbU7BgdTDifwJ7CXRdwr3RlZNvTyyNIy2xz664Lj00SP9tsKyO0O8MXDGennCuV2+dsW9L2Ltfxf+FsW1L+N+vwleLm6NptvyefJvsHbdRhm4l7hbk31Gzt9zfdvvLyqM9RofY1J5CQHEha57VXjsSvI/4aPf9t+Il5Pycizm7irA3eX/ph5P2l0HEPjQrV/+1e9W/GfYO4c1Xc2uQ5RGTrbvvxkkZLm++6znDMjXEn4H6vB3nlAUwZ8d7v0eaaFBm/rO1L6ln8ZB8S3aZ2r7S3sS/hljZmG9/6jHF+3/gWtUbjysg2pp9RbdKT11rX8Q2d2L5rLOs0Qnmw2XPAxZ5bsafR3Z7q0prSjUaU83JjjDal2WzSadjsmp/vtOs27Gpys0vPJ9WEwduupnNk1xsudm3HrmZ3u8rL1mxQhnna1XyWdpnPP89z2vVh9YzW267gTcu13mV29BzZ1ud8p223q3N6FNuqN1VWrLnO27aWs7TtYrHtSQ/bWqPYVlN2zaY1pXV8PNvbvtaztM9c9zbW3T7jA6728a5KFRMiT7vQOzd25Y1zfgt9B3aluNpVVr9qbWldqbddopfqtYeUhGebY3txRuzfeTbz4L2HlJmvQ+Oc5f1R8pXvmi+kjeuU/LMsb+lD7KPgtOtj2FXgaZfcf41iW8E5su20i20fx7YiN9tkzi4rHDxtKzpHtu0e77RtJ7aVRLWNp7xRyq3kLG0znz9PcO/b1a62XcN7G0w/othVfY7sOuxi1yfwa4hi16o1qz3tajhLu0Lz85UTnd+VvxC7dkbaRT2u2WCdM9WKLRIXTRlHuK5texyxX2PU2my6d1Iw4itId+RHyB3Y1OywieWdZt0516v/Ssd/3Pgg/6s5bQl5PYboOXTnhscdz2gljsHxrw3GecgrTi5x6lWchDnOZ80Sp5A41+nrtdFmnKXWewByTXg9ca7IoM/3UPPo2ObQap/J0lXmPpO2tlY32Xke+bSat6yKLL9anrO2Pf9EzzyPPJ+qwoMqcp1PuP08smVk2/Uf7TzCMfDTx7Dlq/BCZx/6rJpXOPMV0/w1qJegny9vGq/DTR3JG3Ha388y8UuBpI2fmbb92mWKM0+NaqwoceQpprkvemaeKnWewjqSJ+KcfZ5IGz8zbfu5yyVPn1fzGGeeYp43p4jNmYSvk3zZ9CRvKWeRt2zJG+njZ0vflr9jFznzt4f85TjzF/PcO8eSvyslf3Y9ued6DvJH+vhZ07fP3w9Pdc9fvjN/ZzR/zxfbs808uunKesqzyGc/Rz6tx7D3vz3T3PNa4MxrTNcCBY56JNyqJ/krOIv82evRmr79+VF9gez+KueB3sj9ag7pmre1ZdV15V75QifyWkLiy7UE4bb9aLed5TkgeC2hj2Grr23Tnee2B9U8ypmnmK6R0It6jUS4+c6EP1GF6wTluaMZbuZ79Tm8hgrd5+e4+Knj2ut3+QxnWTys7jO5lsW6ytL1td73mCzlMFCXg8QPPZ+NyOdtZ1m/HAM/fQz7NfBMZ3/8kpr7OfMU07Vis+V8WKH7o1VH1n6dRV8MnQ9JGz9JO+J6KTDLmadH1XzMmaeYrzOPWsaZNZIvu57Mzc4ib6FxhvTxs6Zvz98Jl/w9Tv4=
*/