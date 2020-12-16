//
// detail/null_fenced_block.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NULL_FENCED_BLOCK_HPP
#define BOOST_ASIO_DETAIL_NULL_FENCED_BLOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class null_fenced_block
  : private noncopyable
{
public:
  enum half_or_full_t { half, full };

  // Constructor.
  explicit null_fenced_block(half_or_full_t)
  {
  }

  // Destructor.
  ~null_fenced_block()
  {
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_NULL_FENCED_BLOCK_HPP

/* null_fenced_block.hpp
dI67RhvDCJ/lMibEZ/kGjNJ13oJe3eJ0QlcaZ/+Mj0evLvD5GKbLXMXemB++Czt0i/djq87GeP6wKD7L52OWrvANmKHr3MRW3eL9WK+zdzsvVusCl9Cvy3wNduo6b8EO3eL9WGT82VifxQxd4POxWpf5GozTNb4Lo322yS9iis7eYw1ggi7ypdjjWip8Kwbb3uCn0G97OrErvRHzbM/zeVimy3w9Fus6b8Fm3eL92Kuz9zoXeuKe8uUYoKu8CvN1gx/GdN3mIeOsT53j8Riti3wpRsXc8o2Yruv8ACbrFu/Hzrgv47vSu9ATc8sXYIAu8zWYrWv8B6zUTf4vlup0kuvFBp3n07FHl/gqDIvx8x0YrBt84fvsr6t8C+aPHM7+84L7pcM9WKYLfCeG6RZPer/r0uGrMEGHH8B0nX3AHKOsG3zmBx3rWO95ft8En9Xhj2OSDv8I03XuZOsQ6Rif5bkTYXudT/iQ++WYJR47qSsV7FPmT5xirdpe41NP9fzbHl6Bpg7fh92a/b211oku8w+w1PFr/Ecs0k0+fbL3p33Cv8UsHX4EC3V42Ok+q8vc9WHnjbniV7Bb58/QGGWfQtH9PNM8RPOnsNi5yrwAA+xf5eXo0XXeiMG6ybuwJ9YbDzzL+HXGI7BX53kituoiz8ROXeYF2KGrPOls9915K7wdq3WbJ01xr3WJb8R23eDaOb4fdYuvnGptH2ds/IaP+C1he4Gvxijba/ybad6PunCue3Ge4+o6P4gVOtz1Ub8TdPh4bNJFvhgtXebFqI5yTF6HhbrBezFN56Z7TlHRBT4PfbrEl6OsK3w95uoar0NJN/ghLNG587vSe9DnvCVegLIO/wFzdbiFqk4fM+fI+Wz4AozU4QoKusYbsdv+4dd+3O8KHc5hUIyZz0UpzstzME1XuB9rY2ylrnT7J8xP9Ce70rYL3FMd7phhLnS4gMHHWye8CzXb2zzwQnOuMx6Bus7zIxhr/2xmV7oOOd3gTZ+yPW97X1e6Fmvf5ph82kWeTV3m7ovdU13gB5B07hJrBvtiDPzfWZ6X2OdSaw1jdXaZ+cFI3eBxnzYPusy3Yahu8ONl91rnP+PZxDLd4As+a3w6/Ffs0OzPrjUPujzbX+983u9v4w/PxywdfhLzdWVOV1qDUW83Tj77C8agK9w71xh0kVd+0fMY83C5ObzCvYvt3IdJrrHMCzBXV3k5+nSdN2KhbvIuVHSbB86zrnTGIzBN53kiSrrIM9HQZV6ATbrKy7Fb13kjWrrJu9DUbR54pXHqjEdgu87zRKzVRZ6Jqi7zAizRVV6Omq7zRtR1k3dhhW7zoC+ZW53xpRhtTuo8o+Je6hZ//CrH0Wl+V/oSpuvwGVf7/tLhPizSTT55gd8VusynfN27S6dv+E5Hb8z/N7vSNzHjnc7Fxy3ye0AX+fMYpsO3o1eHt2Cczl3j+FjhOOH5qOvwj7FJN/j13zKfusgXoabL/H0Me5dnmdehRzd4L3bG8b/t/YPBthf4POy1vcSXo19X+HoMiOPwOuyxvcEPodf2UtXvavTH+uTl2PmO4a/6CezR4QO+4zg+m+epGGd7+PuYoMO3Y7pu8cDvmnP7h0/GPB3+JBbrOm/DAPuHD/2ea9Hhd6JXl3gBZuvw3Zinw49hsc4Wd6UxWKnDn8dqHf4uNusG78JK5w0f/X376PAHsFmX+evYax6qvBxLdJ0Pvdbzbq7y/Fcs0uEPLHFPdXghNuncdRp7dZ3/h3GjjfP6rvSzpdbxCa7rBu9bjLJPha/FaF3jNZinG7wN83WLn8csnX7UlQ7DbJ3jMZiuCzwVM3SJ52CyrvC1GKdrvAZTdIO3YYJu8Z0/9p4=
*/