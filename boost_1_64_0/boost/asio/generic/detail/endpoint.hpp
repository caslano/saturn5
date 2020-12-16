//
// generic/detail/endpoint.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_GENERIC_DETAIL_ENDPOINT_HPP
#define BOOST_ASIO_GENERIC_DETAIL_ENDPOINT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <cstddef>
#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace generic {
namespace detail {

// Helper class for implementing a generic socket endpoint.
class endpoint
{
public:
  // Default constructor.
  BOOST_ASIO_DECL endpoint();

  // Construct an endpoint from the specified raw bytes.
  BOOST_ASIO_DECL endpoint(const void* sock_addr,
      std::size_t sock_addr_size, int sock_protocol);

  // Copy constructor.
  endpoint(const endpoint& other)
    : data_(other.data_),
      size_(other.size_),
      protocol_(other.protocol_)
  {
  }

  // Assign from another endpoint.
  endpoint& operator=(const endpoint& other)
  {
    data_ = other.data_;
    size_ = other.size_;
    protocol_ = other.protocol_;
    return *this;
  }

  // Get the address family associated with the endpoint.
  int family() const
  {
    return data_.base.sa_family;
  }

  // Get the socket protocol associated with the endpoint.
  int protocol() const
  {
    return protocol_;
  }

  // Get the underlying endpoint in the native type.
  boost::asio::detail::socket_addr_type* data()
  {
    return &data_.base;
  }

  // Get the underlying endpoint in the native type.
  const boost::asio::detail::socket_addr_type* data() const
  {
    return &data_.base;
  }

  // Get the underlying size of the endpoint in the native type.
  std::size_t size() const
  {
    return size_;
  }

  // Set the underlying size of the endpoint in the native type.
  BOOST_ASIO_DECL void resize(std::size_t size);

  // Get the capacity of the endpoint in the native type.
  std::size_t capacity() const
  {
    return sizeof(boost::asio::detail::sockaddr_storage_type);
  }

  // Compare two endpoints for equality.
  BOOST_ASIO_DECL friend bool operator==(
      const endpoint& e1, const endpoint& e2);

  // Compare endpoints for ordering.
  BOOST_ASIO_DECL friend bool operator<(
      const endpoint& e1, const endpoint& e2);

private:
  // The underlying socket address.
  union data_union
  {
    boost::asio::detail::socket_addr_type base;
    boost::asio::detail::sockaddr_storage_type generic;
  } data_;

  // The length of the socket address stored in the endpoint.
  std::size_t size_;

  // The socket protocol associated with the endpoint.
  int protocol_;

  // Initialise with a specified memory.
  BOOST_ASIO_DECL void init(const void* sock_addr,
      std::size_t sock_addr_size, int sock_protocol);
};

} // namespace detail
} // namespace generic
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/generic/detail/impl/endpoint.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_GENERIC_DETAIL_ENDPOINT_HPP

/* endpoint.hpp
1FTq2iPlU9XZ+JdIeLaOf0NVJbTR5pejJX6m6ouQ57pdzv/HT91T9c9JwnM58tOD5drhnNOmzYrebLPaNdHN0GZL+F3BTK7Fp4L2TkI/cSonuB/Vj08u037GY8xftG7O/Hvo/vEQ+pxerz00TpvAeT72n2TsbHXQSz7AdTnWG+WS1Nq/V1i7/7YTpnpbpPiH2/o+iwX6RB5+DdT4WV2MBqStndQeQqTwJap6TAihHILV4wljPapnzRH6dxzBsSeVa+CcsCDlVVi6qbi8wmkOQdlU3fhEfq7p8yS+P8tM4/dyTaz4sTDV1sTgYbmr8VlbE3dyLWVcE8t9TGtidW9DOZ300faY5dSP5eQPUk4d7BVQNtVpr4Dx/YLuFYDn37JXoJXLeTrymM5yyQadxj+NQcul3O+0t4lyoex0nNHo0fk5pAzbUJPwZLCsNBkvwiwr8ENbSTNPl+YYV6+L1obCpaygl/Dpy0rubXiu1CTRbznbUCnoDBJp7aCcCour1wfbB47tkSB+m8bhXzVmhbX7uc5g2SEZlpUWP1qVlYtlpfmQTJU0J0n8Pd62+MraGpk/YPwRv0yuRNQ9KDAncsMTCjzj4Z+4fub5kxa+g2WdY1/Ws5E11MuU2CwpvzDuq1vLvUC10bY84ZrodA+vQU+jTx/6XPyI5h+O5d7QI1i5B13XQ9b4TLhHwjOt/Zh1dLfEj2f5a/I+9ZwrhsyhEL53DbXf6tvdGTo++QAUT/w5BLzuYPmX/ffyUud1IuR5fg/LYKSET7li8e8c0DrQK1wnfJAo8ipNlgPT8EkauQgPl/BPMZ9A/YGKQC+D7M4MeEV4Bymf540SLsU3JKP0fqfKS3Rjxr3CE6WLLwFDuw+lxyQ+D3MHjCNyTUu3n+yNbUNbOjsAZ76nB/bfsTeGMresV8jnTdHej3zM8n4kmTw54HlxJHjcdZ6IaI97giciwvYMA/KXpGjvZervtbyXIc8u8Lw0UnweNZjn31raZ6H3bzs9LzS+p0Gd4pqqU+MceqB17X9gEp774U5tzrpfZW1zlEeqPrWXqRNq/wYVfKF9S2+3h5GMa161j6lP3+QXO9U+j0WOeVT7Qk75o2y4bq9WBFS+ii4gX3GGfEm6hvxUDFLngsmvP/f8/Y756XgvqU020XG/n/EXlB/zfr9675pmrZ+zgXE/SH5kutZBnhp0dVRrk6eGi1BHtQ55SqAfwV5MKCD/W+Sp0TFP3FMLnifK93LME+P/KXk6P9h6ftbjaHdNwfLkr62CR7XSIO+aKB+r88OmhFS+wGNYU9zZxbmzz/CtOu9jGi+ODbHWXTmEmh3zyf1G5zxStpc8H+MljzXtZ05cQJ31YZ3FS36M86nGofb11RI0H1W1QdZBlI3VjXsi0H5WkqmeXg3hfCvHuZKqJ7mHoS1mpVvfYxwMxEQ45E02puTt52Zsx8k+2X6Ujwfp7JO9yt66+UFo79H0vutOpTv4rovohO+6iA5810UkXJDvOs3ep2JEG/c3ub65C9SCwva36Vq+uaZQzJSkJrjpEtDp/gRpD7JRSp0pM0r5E79Twrvb1sGRil/tDyxSMiPU/toXJLyT5WLc285T/Oky91uO8B4JF7gWosbAg2thrrMRxvV3r0Aactf2ffXbhGcNZqLZXD8xbay/fMIDz50S3oA2FQGucPF/iWzL79cS14PXIIyf3JfzWLfs9Yn5idrn+5nEX45visNlLdaSjrIeLj6jMN+cFNMrJgNrsfBouzYxH/IHRH6Qsgn5noQT7dqI6PktxNMGA2HmB7lDfgzzyqrkzu03ou7RlqQu1RiK+tWuQQmuq1W7kzoU3vlqrc06MZ170jiq7YZXI78Dgas=
*/