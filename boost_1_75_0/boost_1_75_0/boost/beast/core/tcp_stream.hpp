//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_TCP_STREAM_HPP
#define BOOST_BEAST_CORE_TCP_STREAM_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/basic_stream.hpp>
#include <boost/beast/core/rate_policy.hpp>
#include <boost/asio/executor.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace boost {
namespace beast {

/** A TCP/IP stream socket with timeouts and a polymorphic executor.

    @see basic_stream
*/
using tcp_stream = basic_stream<
    net::ip::tcp,
    net::executor,
    unlimited_rate_policy>;

} // beast
} // boost

#endif

/* tcp_stream.hpp
O1eYihOQMmev6Qnjp21W1bTCNbbB/tUpIOJNVS9+CurG6MVV80rs8xkDR+4i/LFK9oGqlcY3gx+gOthEQUVwKSEnBMVRc7rRFhse/XVeRZ5A4gvI2TuWRqESFhal5X0hxDulyGn3ZBbV+QLUanrq65Y1rvjd0M5d05GMwGOWaokEM0nrvNuCgSz+D6CGtjUuZCvsNQ23qPxlL+Qm8I2QCJmq7ep4nBxZ8dG2ezfH+u67+atdprPjPAKqp77g4Chd6Er05qddLlsOoAKxVfqPVaTUk0Bo0X2RsF/UV0TkF794UM6q1Pxg50q+ovykxuqSNKY706mRPoKaWVg3cl0xutRo/uHXWULC5eHUFgUDtsRYW5kFQqfa+mUdneXvaVDOfve9hss9mNHWe4naI92dX+9d9nWIPGPua3JVYX90AvSvng+jfRW0Xh//rFL4/0vGGP6TjLGz/gt6wSbm6uJib/cP7AUREKQnfT/WsBjdfvLVbiOamMYxU6mdWHiHD8vbcL3ecWegcpYDdaLB18Re5zKtzf20OccBA4PFNbGRAkVFC60Y/qv19A1jbsXv3z8gfBVB+YQQpvW0rShSUJAzysvufClUu+GhGCRiLHU4sZbKfpjB6zyR0VL32nHJ/N4/mKV/K08rE5KNsDE0J6ahRBzfrU76JdgDTBk/vDSeCiuCldwpf0BatG3RkyZIqj+YR+FEaUBB+4RPwSim
*/