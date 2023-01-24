//
// detail/null_reactor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NULL_REACTOR_HPP
#define BOOST_ASIO_DETAIL_NULL_REACTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP) || defined(BOOST_ASIO_WINDOWS_RUNTIME)

#include <boost/asio/detail/scheduler_operation.hpp>
#include <boost/asio/execution_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class null_reactor
  : public execution_context_service_base<null_reactor>
{
public:
  // Constructor.
  null_reactor(boost::asio::execution_context& ctx)
    : execution_context_service_base<null_reactor>(ctx)
  {
  }

  // Destructor.
  ~null_reactor()
  {
  }

  // Destroy all user-defined handler objects owned by the service.
  void shutdown()
  {
  }

  // No-op because should never be called.
  void run(long /*usec*/, op_queue<scheduler_operation>& /*ops*/)
  {
  }

  // No-op.
  void interrupt()
  {
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IOCP) || defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_NULL_REACTOR_HPP

/* null_reactor.hpp
6xl9Bv9ejX+3j6LvE+nvHPy760rqBMcZysCociCOUcHtHneqjiZ+zCTFuOJnoXA1FQE2Fd/ADXxuDcfniQ3NrFJrdxAxvGoqlaCKyxEFd+8jlOIizk3+ojuPc++kKwv4UQRZQApl6q1nxAS3E8sZAdkWMXSFkF4h3mWbKZzvz7axirPTj/g803XKfTuwA3w7sH+UFexdMZQupOB7lwnD9ffYS8ps1810oNMU18/xE5ws1O9aTdeSo0+G4jzkauhtid6u3oGsrN6L7GMNdR/k3AE0R0yY9uLRje4jnKeR3mwlqX0Tz/8J2Ji4Swt6fH4TtvVF5BYVyArvrfPSL+UJBE+KXbctzWrhRyB8chHOOUDeB1eHtaddt4m1lmUVmSmc+2uoX+Mgo81IbW+Dl64Frwtrt3vf6n2bPc5uKYnqa9RUI01BBHjE55Be02VH3GEhmdttEkNFkCuGcnhbb4NirXpboyiN2+1YmtDs234e9kHXHZy7Bnu6C2GULoJRUMqd8m/TEEbB72VM2AlGiSij3AuultvdSGe7+fyo7tRTFyD8QoVLHtsZddYCuBSEZcSu1dy2Owj6WDuEKuXcRTb8cjPnvmEIQh93I/TRdcvm2a6fL81q5icjhZ6VBH5ggxH88MwBsxw8iIk5Vav80nXzUink24uVBl+KxYQdr7umlaV3VmQdEBIlslt5EHgpdtfUMrx20WImBtJebFK+
*/