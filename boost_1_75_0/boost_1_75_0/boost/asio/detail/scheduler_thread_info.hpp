//
// detail/scheduler_thread_info.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SCHEDULER_THREAD_INFO_HPP
#define BOOST_ASIO_DETAIL_SCHEDULER_THREAD_INFO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/op_queue.hpp>
#include <boost/asio/detail/thread_info_base.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class scheduler;
class scheduler_operation;

struct scheduler_thread_info : public thread_info_base
{
  op_queue<scheduler_operation> private_op_queue;
  long private_outstanding_work;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_SCHEDULER_THREAD_INFO_HPP

/* scheduler_thread_info.hpp
pl1fMf0yh6lBj+9xvOOtKXhrduCWin2opSpf22Zd8cSUbbkUxnCxuj+9IkKpXLsOhGL5bmg1yr/m8N3KG6H6cD5+P98O2BvkddiCWfY5oUhQCUVRLoWZaQTUkkvUcaicgYwf7JCLQ3eD6biXOUZidAj5mD7MsQJQj9ZVdFy7NqqiI7k8vqJjSeg8CEzebOHQ+5L3Wo54qXOy42oEJ46i2zdotw1rL5M6Y7zjA5VcEqjEUxmJm2xZlNQZWR4pvalInQoq03rV5ClE19flLbC8W3Fak9JMjsaOzzHInejA//cI7jrKlyazlVQSJWpmp++jpXlFTjhZD2xRs3AXYXtvJUKGlBvweIQdv4Xear8lhHKHbBKT7wqB5r1E2yNw5h1hme1Eh1/V3vXTu10hrMN+4jFS+UdGOJp+U4K4al46Y6nbesQm3scmDQY+TkY1nou2hfY6g1CJGeGp5HHma9ytx6LcO4yNBwoS7EAjM/MOXDNAB0pKwtHhzWb7gRlAWt7C7lkCxHtz31H4q57jl9xkjsAauqONetqY7Vc8+5CheKxDUfeDyQAjpKXiZRxHR2jTZr8vxs/+wf6fjZOT+ohz1zsCS7BNxdqu8hkQD8vJ5IvElACKJyGKr8qm3uVlh/QOd3baVe/IDu9btt1IK4z9qERdXEOrFhvUheW6CDjos7Cb5tpYCfEd0IBfL/JTSr7MRrVOVrOQKvx8YX8V
*/