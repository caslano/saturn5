//
// ts/executor.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_TS_EXECUTOR_HPP
#define BOOST_ASIO_TS_EXECUTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/async_result.hpp>
#include <boost/asio/associated_allocator.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/is_executor.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/bind_executor.hpp>
#include <boost/asio/executor_work_guard.hpp>
#include <boost/asio/system_executor.hpp>
#include <boost/asio/executor.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/post.hpp>
#include <boost/asio/defer.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/packaged_task.hpp>
#include <boost/asio/use_future.hpp>

#endif // BOOST_ASIO_TS_EXECUTOR_HPP

/* executor.hpp
hxBjJ7Tx+lT9G32Dfl8vhrguMILMieZ8k8p2sjFqIr2fPktfpT2Y80wFPlqYIdQTva2kz3Hkfi5Zz97lnTB2naUvpLWSs7JUmaHmqSLGJ1M/rNcwhhkTjNIma35p5ljxlOdkwR81juSRUDqHDmJZNp5NYcexi9jd7BlE1mu2FBfCteC6cF9ws7hvuG+5w9wd7gH3mHvG/YlMGsJv4F/wNPpEBwakAgVmC/OEDCGzEKFPCDeEfOGuUCA8EZ4LrwRKdBU9RR/RV/QT/cUAMVAMEoPFOiIRQ8TGYqgYJoaLkWK0GCsOEyeJqcCQLeIOcY+YLR4ST4jnxLviK9FJKi/9KBFZl1PkB3IT5XNli9JYHQtM+wZ9fEN10Sporrqn7q8H6IF6sB6iL9cf6ovMhyZV4ETlor0mKSCl6Fb0UvoR3YupwLblenCrgQ0/cyrfhm/HD7fR7Z9j1YqQR7ynUEv4rLC1i4QVwnXhpvAU7XMTi4klxbJiJXGWuEvkpOZSgpQoJUvDpElSqrRISpdWSJnSISldfgQsrKSI4OUW4OVeyg9ARWe1otpS7aueVRtq7d5HygVtt/67HmSkG4FmkMmZkqmZjc0YsPAwc5KZagt/ZyrNxvDyJJR0IPFkCkknu4gv/Tl4KIs+Q1cG845lgtkwtj07lc1gd7K/sb6cP1eRC+JqcRHcJG4mN5c7w9/mPxHqAtG9xXXifnGcfdVp
*/