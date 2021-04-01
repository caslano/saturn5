//
// impl/system_context.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_SYSTEM_CONTEXT_HPP
#define BOOST_ASIO_IMPL_SYSTEM_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/system_executor.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

inline system_context::executor_type
system_context::get_executor() BOOST_ASIO_NOEXCEPT
{
  return system_executor();
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_SYSTEM_CONTEXT_HPP

/* system_context.hpp
eyHgmJ2NCcwtYujP0GyAs9xy8yXKJ2RD1ZarYTc5dKuRF67TSgFmwBYG/OgeehQ4tL5TAP4c0s3rpQYtB3KkXUee5FyTQeeQMZzSEqmh/1ittfawdVOjuCTB0FwdA7Vd906yNt+Er0mXsKK8DlDvu89lgTjUkdi5ZD0idYhqp4FyMQYmFDdF67SYocSHtdN/v3tASgE7MNHgid1J29A/9Axs0K+P3EyqyFjVk07aDjlHErjeRxwv1HSYuCAnSX6NI1J3dFGQmdT8BwP3xkwIMkd8A8RHrSDreuJ5mNaiND2e8a4+hchQ5sV86bRRYMYutVssnUG99lS8AVd5FaeJU6N/9x/BDgfghYOsiPnmPiMOaHmcMeObTBxpeAztey+p+yUD6HAnnr9aylZswyGd0fBD+ZHaT9XR+hgpI1F1nTRpXbbq1CWWs/1+aPEOaD+ouLl0h2f2tJ4UrsL4tcpZRqsYWOHIpbxF0Mca5DoCYQF4YlAtRBn0bZrbpzjypDf/PA9Y1ZrXT5Sk3zZOD2NX3gKLO2FoGKvs+Yxoijh6WnjAwWsoK6oNhUlOxA==
*/