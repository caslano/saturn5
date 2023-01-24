//
// detail/solaris_fenced_block.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SOLARIS_FENCED_BLOCK_HPP
#define BOOST_ASIO_DETAIL_SOLARIS_FENCED_BLOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(__sun)

#include <atomic.h>
#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class solaris_fenced_block
  : private noncopyable
{
public:
  enum half_t { half };
  enum full_t { full };

  // Constructor for a half fenced block.
  explicit solaris_fenced_block(half_t)
  {
  }

  // Constructor for a full fenced block.
  explicit solaris_fenced_block(full_t)
  {
    membar_consumer();
  }

  // Destructor.
  ~solaris_fenced_block()
  {
    membar_producer();
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(__sun)

#endif // BOOST_ASIO_DETAIL_SOLARIS_FENCED_BLOCK_HPP

/* solaris_fenced_block.hpp
M7t8Zgo+lOQXAO5TSea00P2ncRT3ybZ9kR5Kbb4tZg8BPs9Rh3Y8GlPHFMs5lmJprpEZ5ntjS+xHAf/7hgP+0W4V8IhmzRr+Ly6hWrEzDg3/nSAit+LpP+woq6OB4R8NaU2oWjnOOqABWvTOcLZVMk8qtwLGpInidEQMx09GCaQvMsldiC/IKdYZpQKY8RkCMYNisO2LwA+6bQhIt2Kmpu5T2N7+4VMYvXk254w+hUWFzyJ0PevJ1YJK2CBcKec0e/suRJ/78cXpM+/pFG7wZXZBOwxGbBEEBDIcHwk0rgvjlLC4rkASuqmPLRYdMUI/DQOyUTIG+mCyGAwy36MIZ8IBCQzSVB9tEvA68shU4IypYZwIe5KSSslUlVSWD9N50q+GXTtf9dQvdn2ozgPWpxbQ80d+RuuIybB7AtENY7vX4Ia3zyQhSKpqAZBDkpOM9APNSznnkdXme42QgKzCuAMjayECQ2fI6KzbnnJhKFr826oboNatFhQKUc1GjXi9FiUu4QVquBT/AhqVX6Q7eU+ka5boRErH+6rp0bwSVMx5yHD0P0A903TCHLD5hq2Wyi4sqzRqPz0Ba5TroT0XPWTcC/pcEPdUCqangGwcufUAjIz3A0PJ9EXAvaZECH3ICFojOhUWDyvRBXg+wENeR8cD+VAW+qFVwYzFzgGJZeuazeaq9rISzSDfQx7wdyha223bZuCxZ7LmfqZN
*/