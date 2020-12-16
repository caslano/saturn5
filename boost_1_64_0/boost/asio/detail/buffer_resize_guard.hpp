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
ng374J+xrZK7lnHG7MN104a46ZlNDI/H7ujZ2sS52WdGXDrqWAog3zVmPy30smnXA37vEC8nI1f/CtpZ6FMlko3jCo/UgUy/xmajGhjT52AL6Fw+jzrQbCTGXmqTEsm7tRxew4lh5HiP8njoZVN/finr2AzpCsrfhM4A/PYq9A/UQz+eWCDv1QL8aUUO7PGDauhS5zXSNci6FfwyC3rmeSQ8bdjramjWUzedGHma8x9RnmCeJUNrfzL+tBJfbsmXCg/kuaoIu8FjMP5ua4Z2MbJg2xtcrH9akQk/b4fWd6H5QSp0sOGfpqHLKMbXYdQx9yjhP7wRH5UTr2XwyEEujvuBCPK/M5rxC2SZvZTEa+QU/FrHWAqNogppEjp7SK9DhzPdyFVLn8Cvl5UyNoKdufQF7FZGu5NJF1JWk4Ue5lkjcq6bhFzItscGTfQYkcj4lkY6njbm+mE+dc3+gzJ0zcYvpJnQep40FRmXMz5mxEkrSU8Zjfyt+AZ8Dznc0OsxCj8nIBc+a0WfzeS9OAH9qDshHntlMi7lE8s1yGf2O5g91VXYBzlfg/7P4R+fJA1swSfm2U8R9UqQl/RtH/6n7T0J+Jo6dQ4pAbld2GlfHPPAOOwwA77YeRf2CTf3isw9hTHEK2WXm75CHESUSpUjkH04/Ry6Keh5L+knnD9M3Zdr6Rf4bQf+zUTuAsaOFo/kq6Ge2cuGXj3Mc/B+0AURhfgC++aZPQyc30ZZNHmnk24iv3ebNHsOOsSTD4/P0acD2W3w+oGDduh+LfnLXKw34DV8LL4vZRxtQE9ky0Gf44YwZ1LvnGT6KHVqKdtNrD1ikZ7zSuaVwkke8t34zC6V0t5eju3c1McHU2nz3gn4ifQ3pk+bPuVCFmSYTtsvqHNLGTIgR2oWvGh7ko14o1+sgd7H+OL4Iua3eOxirn1y8EOe5IH+FVn4bQC2oF59P/iTn4yNGvFFaSHyQfvdVuka0mftjKEWUnidQVl2EfTq6Yvo5eL8OmQcB71V8NhI/o3I+bMq6JvrH7OPFnlmmzkxF93M9Q/ttjiJF/AxOMfMdaSPNtEf4L+eOjeDaOS7Abv+IgVfUT7H7EOok1rJGwseGU97fLUEXg5iZfUo6hNXM+cxnph9QRxPmgd980zdSp+k3tPIGoG9XOBlZHpzEDEWRwxVsEY6gZT688waL4Gxy6wV8xnLyevJGLB8BLxMX6KueTXqi+Rvd6GHGzvnst4wezGw44lmr2sTviqE1jT8V8R4MYx44dwKRk9nDUH6iI8xezq0KDvfrAWGI/9I+gTt+0OzYzztzNocnqUu7JfBGoGyPyLXF+ADZB86m/bQ6U1+OHzakWMabWuzsdtMeGLD66m3iPa9kT/Ciu/N/kwwxjzzmErfx3bPt1EfWd8tRP48fGH2SELnSmy2GL28YEsBskDrd2a/Wh1xZZ47WPEp5x8n0S+xW5t5zmLuSWH702ulL5uIY4+Uau5ZGZ8mMy8m4V+zh36yZG+GRwIxNQl9SD+DZn2Z5IHmC/h4SR7yp2Ibjk+zEp9DsJG5j0Wsjkdmdy4xb55JUWcBujQj37h66Vxi/zbKysqlhT6px1Bil3Yvk7rM83M7sUH9fdipKk2qAzW0azH/BSkHacR1C7JBd8s89HQRt+nQo05kIvl2ZE1hDqO8GAwfgF2OR2d4nu0h7pOxb3/y4mhLTL+Pjx/LIG7N/lt0fJj8IdQJ5/gUc/89C9kof9GJ/0oYs7DdBtqd1SbZ4TkvHjsj65JMqQQdMsx/GPKIFTAnCRsRR6uwcTyyJtLGQcz8CRpn0iYsFf9g730t0LJAw1yrmzVVK37Cjp/PxhbgAXyWb/YdQn9aBfI=
*/