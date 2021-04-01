//
// detail/buffer_resize_guard.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_BUFFER_RESIZE_GUARD_HPP
#define BOOST_ASIO_DETAIL_BUFFER_RESIZE_GUARD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/limits.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Helper class to manage buffer resizing in an exception safe way.
template <typename Buffer>
class buffer_resize_guard
{
public:
  // Constructor.
  buffer_resize_guard(Buffer& buffer)
    : buffer_(buffer),
      old_size_(buffer.size())
  {
  }

  // Destructor rolls back the buffer resize unless commit was called.
  ~buffer_resize_guard()
  {
    if (old_size_ != (std::numeric_limits<size_t>::max)())
    {
      buffer_.resize(old_size_);
    }
  }

  // Commit the resize transaction.
  void commit()
  {
    old_size_ = (std::numeric_limits<size_t>::max)();
  }

private:
  // The buffer being managed.
  Buffer& buffer_;

  // The size of the buffer at the time the guard was constructed.
  size_t old_size_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_BUFFER_RESIZE_GUARD_HPP

/* buffer_resize_guard.hpp
wOaYBFfD4Ai0zK2NB6FJ9+Eme3KWAGTK7MFphDzWACVIrpTyRoA7+drhzq+Ckb6wNTjBHC1bhKKHoHNeefnvxBNSVWMx2eHzM8L85iI+kRQaSSNafvemQlZZ98ps64D68qikZACw7x38Msrd7/LqqLpVGN0R4Zpko+JOtNCuM2d/Yb24FmhxZZJwWZnG4II7nTZnDMCxVu5JWjKck4i33zOy+SpMu/jl08lEX8ctQblb+eMms2fjXM0LEUjn/1mlEJje2kgGgr2p1rhMRLBeBDTlPXqzTm7py5eEalIkWs788Rj2tIx5ZP/2CgWRMuaEBUeSMULRFVvzl7RwAnblGm6KE9aUQ2ADBUbX1ilqXaAUlZWpbqy6oQJfmoK39s0X4+syU6PIpDIWbhFXubF8iKdp0PA2oVMHYH5+1DVT2a/YF6i4E4RWjNyN0RhBnWkPn9D5OkLv+PnZJSFFW8j4kHrwk3y6kPV66Irg7kPFuSpyuQCUB8bWrC5/k/z3UKBTxejlmYzpbwqgbv1YyhteXwq+an+j8lTjFyEQ6wie4HvEPKsJYap7ZV5CYA==
*/