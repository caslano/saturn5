//
// detail/reactor.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTOR_HPP
#define BOOST_ASIO_DETAIL_REACTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/reactor_fwd.hpp>

#if defined(BOOST_ASIO_HAS_EPOLL)
# include <boost/asio/detail/epoll_reactor.hpp>
#elif defined(BOOST_ASIO_HAS_KQUEUE)
# include <boost/asio/detail/kqueue_reactor.hpp>
#elif defined(BOOST_ASIO_HAS_DEV_POLL)
# include <boost/asio/detail/dev_poll_reactor.hpp>
#elif defined(BOOST_ASIO_HAS_IOCP) || defined(BOOST_ASIO_WINDOWS_RUNTIME)
# include <boost/asio/detail/null_reactor.hpp>
#else
# include <boost/asio/detail/select_reactor.hpp>
#endif

#endif // BOOST_ASIO_DETAIL_REACTOR_HPP

/* reactor.hpp
Qqre+YWLRUaznyU+VlSQm7G4mJb5s3wp5PLZIqxlATk3rYwd42Hq+ffIv2MDmN7GlVlxedbrconLphPpLpcYLLrCz4qAnB/IWEUA44dxeYQVrChH5FNEyry8ZXkl5NmZYCO+K315wfwCab9jbJXEFERgUYnJLEQeHWfB1H2Mj5e4moUczyofQ3Lhp1rKZRYBqwlgsjxqPSyLesvC4sVq/1rnYUVFYksofMOsVuQ5RUUl2YVlRTTqmOGt9a2XuJuTeVRH2b+X/hhw3ooii9ZcuFEqKcqYky3iFAeu9/kCa7BgRcDWAKOUkDocicVEJ8nYCSY2u5yO4RK2gLUmJjpfuQ+4iTOKMVOBcT5QOpX3CWvRgdOpaEWZGQXZIiPRUSC9601OUcH8jEyBnWzBclA+pwAT+4kWZs9GfDdAnp9ZVCAaQvcYB6xDVzCOC9rUTaZcnHYg1qFrWGFuThbGTFV5fh7FYCGHdboqJ6Hbunt5eYaBlVBv4WFn6lhRwSxqx4oEdpaJZWUUZyAfNpsY0nS2KafeINsbO1UxrP1R4/lzFafavYhyODc/k7EtCsYVnI+vE/7O0bG8ObnZ7pM5nud6WPHc7EKu1Bg7hbxgVvZYHreH/HwpF2LIL/Dl87NmwwePn0LOhyGPxfipJqPaMEf0c1t1+YKMzDI3Rxm7SMeKMmZnkz+sHdcwqQ9fosllG3ypIp+AvL1MldEbM0epA5drGL0jhYsLir0xUgPj/p2aEMLFmnEDX0QlVgBd7ioNQ6uVkZeFlkusG9c41MfmFJSpdeIaFeeCz87yx0aDWCF7Bn5dAJcR5LFRFedsxdioKudsFeHdqMgn6t0I49vsuBsC4zepuKvcLuJWmGPM46OJcfcZzNmemEPPwT7gKkdJ1y9VuZKuWz253yeUFVAJ5WfB3w6BYysF91E431iTLyzJyBXYEMJu97DC/NLF6MkIlFshoXzvUHkIyftu3AkMna5YD67J5LtwlyaXe2/cDbn5nXlPQC71m18FMBner4GZ36D3Ql5o0d/uk5hVf7tf4lb97QGJK4/FeKaJGXrNQzYc+/8+LLGy/IzsAjGBqYix3yhYQVERIOzlLTFNZ9wVkMs8/W0Ak3n6KDDvHHiv/B+DnM83hexxVZaTJc5ShqxYnukp1m9LuXLOIMYmrRjHl/HdVly2sU9JnHpUnLGsyWTdfEaTyzD2qHL0V7/XZb695FlDXon1qM9JuXJWEvbtBqacmSLGIoNy/9vphQAm25UXgcn91HHOspBra8lfljLshSvkrwTkor79UcqVfVaFn70aVlLq1e1XFbm/fyqe/ycNo2RA/pomL8z1wnrdkHPKgf3ZwNSzKP9iYni33lDkstHDOKAVKxJrnhVMKOEYA5Rydc8sse5ZwfBysfwdIQ+M9bxryNW0vmdgalr/amJI6/uqHHqd5+cDFaMu2JP/TZXTXHFP/qEiF8/G+J4qrxRjdR+RLFJfz0PMGC2Kqft7/53w6NjyoO0P5fAxcJvd9BNgNnvYp8AUuxfLP4Ncsady3D9n+QrP/inOVYbM1v98Ccxmz/yKsXBCe+bXwE175gEpt9ozvwFus2d+C8xmz/wHMJs98ztgNnvm98Aas2f+YOGo4f8I3GbPdDoAs5RfCJhpz2wGuWnPTJJyqz2zOXCbPbNFAAvaM5Mlx2rPPAy4zZ7ZEpjNntkKmGnPbA25tGeKuLaBvDGbZVtwbDbLdsBsNsv2wII2S+G3g4qviPKhQJHyan5/OgJT7ZkpkDVmz0wFx7Bncnw6AUtks+wMPJHNsgtwm82yq8SsNsvDJe63B92kTE0+Y92B2eyZPYCZ9syekJv2zF6Q2+yZvYGZ9sw+kJs=
*/