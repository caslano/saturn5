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
OcMWAYr3yTCnl5dwHvqqHNkoi29LNCS0GLwzCqtk7b+W86qQzRsqA3OpNh9yMp6lu33y+40Xs+/NCRA3UKXYi6acbNnfCdJdhiVSYtqu+zu73QhICUsSs+u51DRbX7+TWwN65GGGwyMSvA5/WnTjWRDCIJQgKqfjSR9S/0vanV9tg927GeM3BT5UPEeaD5D9/qtZfV6c4GzdyW7cPKYwd446pGVuCxq5MaoJLOdVpT3mP/c28EKp+Pgz9Ph8GaelyNios0+b542SrVljKDbNitzbqrpeaJ+9WIr5B5oqwVc+WWFG2B3sZhH4SHgDuYSnsfQkLoIeXuCLbKyKvEPj2KA9tqSoFlMb9njlyaCC9pJt/t782QChkNzvldBSCb7cjX0kM7+gathupnDIVgzJ/H2zWSh0xIgCVJYzoNTSRmmkwYXje9oxrQ/XaPWpPI1KWZ/t6/Ybm0Dc8jwFJeXvJKMPPF5i3mS+ZKAgwHCcdWzvMgrd/SAFvGv9hMHwkjRiJqJAx24mLWtesWuQF5VF6Y8Xl72wrCS9qbcsqGFsNQyJEmQw4r1C33f0gw==
*/