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
V9V56fNa0q/5wG0cq1hNV2p9N+HzeMYYScP3ou2SZrojmPfYsLwLgE8I3VRL3jP0c+cpifvRiIW2htQVsbY2KH8bTEzV9SgaPWZs7/FFZhjPso+WPulnuPm+Mkj3STLvkvXXv3T8HL0eSQG2Fpp4qas5bnulPiMdLAs9OnV06fRiqx4t84W8xFI7nZP2Nkl3jGEgMuW41GkXeJLl8/0jg2WnSPxulQm+zFeFrFOQV0PWI/odbqqkS1cZ5O1F4r/UqApNewy54a87+6+Qc478tkTyrhnKayIzkyHDr0PFDvqfj7GUY3j++OXYQPjN9h7LlXcRory76L/fAu4D7oErJB7Pxd9EPPvE1U6RZyCcXxbmAc/0LpOcHnyXgRyyPbNKEId5yfW6krBZOkxklISVIWyz5GP2Cd95dJhF1iB8mU7fW/zl2j/WzEvmFHgUfpln+ow1+NvMX/wdtX+Gv57KkkaF3EGfwftU0bDGwLbAtaA9hdGMLMsLO4MpwuU5+bi5w0wXy+8ggXyGRJPdjO+v19itJL1DePeNGia9nY8aS3yc5F+g01+KdpLeIrspk0nTQ8v7BpJHjBFcf/XWz46aEpdhWOQx01Mex4au2zpL/9eTdFWMwFxJF//5Ftlsz6cc+USUmfAF5dUsyhTwreSXhBwYJ/2CdJa1SDuh+adZK/38WSth8AuN9kt/PSsHEyA58enHKl8vFpofLPLLLosygaeFxkk/nkTi76qaYq6iaeqGDJmfMje3oRO/ABZmcO7RLczgu3LsWeZgbHAOohz7HIyNMAdjI8xBhIE/7HOQYWFzEOEY3+AcpF/PQWWbgzKfWvAMwmnOpz5wacRmkKVrnDKf+MIoH1elf1MRZygEjRoxatzooKx/TOjzuAZiesv31c/Eb+jzryNM+Xb2b6M9rWs8lI026LJtZynysvwJvoc7H+4tuHVoc7LL2g4sqvmxITi/R42zfGsgfa7+rpgn/tcjPmtzgLZnFvPJAs6UdFPhlz7DD2WP7a37q6/EP6xqoj88iC3kc2I7v2FZvxurs/Db6Zggv+1z2fktWfOWtJPfpMLkq+7HYdlKfpm0wxMPvA20BW5rP5YUjxg12r/WQvuGtLTzBPuSaaryHR1fMMT/o0rBv+vgdsJxzWQbh146bYbK5jiMEf8PKgl1XQv3GFyIrRF55i4UujuhM97I0vdSMdBwLSw0s9RF+C9kfLRsel9oZuJbey35dtweg3pdVehMyjtQi3hnfrzbraK8r5N+A+jfkffgjir0fT2Q50nQnACNs+wQ34CrxITPEXu+qJB6V97fy8pD398D/pO5FX93wvjZ5lWq/rZHvgnhEVd16rNTj3cp3B3IY6snyCP4YokM8dFyfJFlrsETnGukr6nX+AfEvwB7WG7hq4XkK36vIm8E0lXTa+NXxD8f+v6xEXnimMRPwFMzU59brufle0Dotyw+gz+TNCOhC1pNxn94tv8M4ymz353nYfDjnR3xb8TxJ/0G0P9RvgM1Dxv/4Jrx7PKP3185j6UP9ffXhRw79pHtvfckx2kyXBoxCW0t8+pxCnxcC2yfBb67IT4QZdlDk3SDOH7MxyLjPxW/EeH7TYX2wWyyPkFkva6Djf+KavgT5Jt01N292pT1vrB2yWcU7kcFz7dSDjQT+lw9NoWsX27U+rF/WY+Cmv6IGBL44OaiHiUR6lEqEwJl6/6dMX7ymCnsu0CamPBvbJHiuP4rsMTJc+IsPOTT/cqyeZaSawXxZ2l/b1tbN9RS8ruGvFQKNxttLYvcVkz70mhtZZrqet6vEP8IdTn+DZMVHKt7hKYG+ySQR1XKdEM9K/7W4L0MSx5SLGjIv0IzUvVFu9g=
*/