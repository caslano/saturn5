//
// detail/noncopyable.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NONCOPYABLE_HPP
#define BOOST_ASIO_DETAIL_NONCOPYABLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class noncopyable
{
protected:
  noncopyable() {}
  ~noncopyable() {}
private:
  noncopyable(const noncopyable&);
  const noncopyable& operator=(const noncopyable&);
};

} // namespace detail

using boost::asio::detail::noncopyable;

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_NONCOPYABLE_HPP

/* noncopyable.hpp
SEXMpUaxnCZksKK+vz3nayUJ8cHnUDpBbO7qR56wlMmJsvy/ZuCuRJ30y4n0ay/pw8DxlSoDFxdFqV5DCpDHeFrGuUNxun4I0zUS0PcwF1UokW11AjNN3GtkeQrnO+WbbadpwQdZ52rPRtVk4Wde0B1Hm9wNn9dAeoIYJtOfag8z8ZvBmqC7MEu7sPA+9F0A9JWJe/FVEz96gC7+N+hwtDVZNI2p5U90tRRDN/F5YmidkCR2D9kEEjOU+8VTaCy604RLxNA9nOcRK3o63CkuDrd6tc579zPutYUxR6GVqBnpjZ53OPcdVp07nGcZ/VjNhHGWFSPXOqd3RxpS8P5h5oRTognbdbEZ1PIcZCcpq5PpbIMHY4arcWx5De/3pLGuHU+mc/WSrjBjeoVEl4DPFT6zGLCobu5T4ocor+Hcl2GLZCvnfhquzZ/PuadoF3CCHXzhZ4DjzwKLEB8Lrp71U6PeoAVYkhpaoB8NZgzUSXlVc5YL9rx6YkvYlebPPYo7qP8yn0bDquaUC0NeKs+rz/0qTdlY/RyGDMqavNnThBL3MX5J9bCq0+X8dXnMj8/6dJ2tOqDYqvdXf8rVtCsO6R1g/8HWwNdW+zUjj/bu52re3GnOemvTV9L74pdx0ltMwPQHLjuGe1o0VrfSezvN+g1wV+VCNYZLU8CKs8qCv8Ot6XdFXAoq9JB6D4YuZmbYZ6iGXcBjMuN3mpn/
*/