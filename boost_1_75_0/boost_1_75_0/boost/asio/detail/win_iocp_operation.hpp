//
// detail/win_iocp_operation.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_OPERATION_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_OPERATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)

#include <boost/asio/detail/handler_tracking.hpp>
#include <boost/asio/detail/op_queue.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/system/error_code.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class win_iocp_io_context;

// Base class for all operations. A function pointer is used instead of virtual
// functions to avoid the associated overhead.
class win_iocp_operation
  : public OVERLAPPED
    BOOST_ASIO_ALSO_INHERIT_TRACKED_HANDLER
{
public:
  typedef win_iocp_operation operation_type;

  void complete(void* owner, const boost::system::error_code& ec,
      std::size_t bytes_transferred)
  {
    func_(owner, this, ec, bytes_transferred);
  }

  void destroy()
  {
    func_(0, this, boost::system::error_code(), 0);
  }

protected:
  typedef void (*func_type)(
      void*, win_iocp_operation*,
      const boost::system::error_code&, std::size_t);

  win_iocp_operation(func_type func)
    : next_(0),
      func_(func)
  {
    reset();
  }

  // Prevents deletion through this type.
  ~win_iocp_operation()
  {
  }

  void reset()
  {
    Internal = 0;
    InternalHigh = 0;
    Offset = 0;
    OffsetHigh = 0;
    hEvent = 0;
    ready_ = 0;
  }

private:
  friend class op_queue_access;
  friend class win_iocp_io_context;
  win_iocp_operation* next_;
  func_type func_;
  long ready_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_IOCP)

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_OPERATION_HPP

/* win_iocp_operation.hpp
SRqgixTXDjF9RmbidqR88TauK4WykzDaMPv8a7kpLNdX933AUN4pXBrJxisFL0/qSzBn5BtvZapnVu4kcURWLAupX7gyayvnmNnaPF/Yh+r8xhBCFBRS+VcmxMkVgeQEjWp8nfFhXN5QhHblbRTjrdee3j4LZOMt8nJ7NRbo8hvNp05NBPlX5s5a/E9ievLLc3uByNUDRDk9+CAtPpkP+Aw+Ir3ofi7+kEFOTnqNiYpMNnBHzPmCRoSYQqkYWHNNwwsVdVP6WRKYI5xqx/Vm3N57n+57MfJ/xpvRAMMbKUwU+eCjt/Kr6uX8diD0fsrdHJNsXb7gYzCEXPpgB/foqiZekEdynTpoGqpbhuRwMaIJs4tyu1v09cdp7noPQl3LphpALYCSugxiS6MOq8fNhVF5z5tPvOPSCUMvni6qkiHoffmH3EYS3BrwT4G6olsIkmTwS3RsJDX5IVlaEtuHu4Nvv1iJaxB0FWe+wux2OGX3h6exTW1Y73B0bCRIiF1dmr759yQGoONJo2kILafSI0B9e+HqYhruRukiHz+D5o1qNze3gGoklEj7KA5GXzUDHYww9fXZwGgv6ZfSPVp8tGThGZEDyqpkSL5gFgirpnU6wsrvRSner2HX573r7CypbEzhnY0NNbKvpMhODXEfGUqTY0a4kw7Qn3FGaoZIHrBe5d/ScQPqPiKXGiW6I06m95FHzk7emshg0bGt
*/