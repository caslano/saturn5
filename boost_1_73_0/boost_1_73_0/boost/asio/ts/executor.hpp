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
eS1kZWxheS5kVVQFAAG2SCRgdZBPS8QwEMXv+RRzVLAF9SAUEcSLgp4UPM82L23YNFkyU5f66U1TV0Hwlj9v3vu9eU5x6ChD89JYBF7MfS4Pt4I+RSt35hHh0NE7eyX1E2gHPQKxjniIubcWtqOb9vKqvTYPrBhSXjrq5xxM0zTmhfeoN5IAHEhHL8RTmqNScidTlzII3I8bCx3HksGkmaM4ZBpZjGMfYOnodTx9eRQX5JwynRXCfuQ4QEoGyMLxHJR23O+T+w7iUOjK/GT+9Dhv6W0FSwf1KdJ6imEhHxUZoj4O5B01zUa3NgiSzCywLb1Cq6A2q0skTfSJnAprCDT9bKDo/2VrjXlym8cvxBpAgg9kDlUlF9UgsJTtRWwBO1Rha74AUEsDBAoAAAAIAC1nSlJ3EzA8TwEAAEcCAAAuAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvcmV0cnktbWF4LXRpbWUuZFVUBQABtkgkYH1RS0vEMBC+51fMTYVtQD0IRYTFi4J40D16ic20HcyjJtN9+OudpLuiFy9NCd87TzEMLSTkdGi82TdMHtU6yd1txi4Gm+/UA7qphZeCgRjcAXbEIwWQT4YJE0Wr1taibeFGX17pa3VvGIeYDi10c3Kq
*/