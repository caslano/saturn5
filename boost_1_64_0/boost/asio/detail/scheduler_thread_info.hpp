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
BzxX8V1Y949PAyuBzwBX+nS6Nvl0um5U8kVYz09/F9by/O+Bzyo5DPgc7c+LXfP3AeCHwFfDWu54Laz1VweBcYo/gVOUnAFc5Jdwoqd6A1gNfCus5Y23w5ov3gtrfdX7YS1vfAC8T/VrYeF7KU/qjXhmDm3dQ29UxPlYCedjpUA5G8V50DLqOS/i/KccqPTdFSHdX1eGdH9dHdL6xBUhez6dWB17Pv1sQMv1vyG/PgdcongKWKvkXvLbCfM8kciW0fPp7wW0/HkT9RY/COh++ZaA5rMfAYvVeAOUdUTgxYr/gPcq/gM+qMYf4FOK74CvAu8K6Pnx3cAewHuA/YG7gLnA+4EbVf8HvFrxG3C74jfgA6rfAx5U41dA6yUfA3YEPh7QeskngIOBvwROAD4JPAf4FHCp6veY/5E8Y0H9f5R+fGBA64MGBfQ8Y3BA9zNZDN/o4z566RN0eKVvqGN7zWZ5jQ3oefY44IXA8ewfJrB/mEj9ziTgQ8CpwBeA31L6GeAFLLeFwD8DFwV0+zw3oNvnecAPVR6YrhnAzxlPGGlZAjwDWBzQ89YSoKxtB3Q7nBfQ89b5wHrg7ICe31wU0Hq65QE9fy4HvgSsAP5RyUEBPZ+pUfWIvNcCM4F1wIHABuCZwIsDejy5BKj689XAG4FrVP8HbATuAa4HPgPcEND64Y0BrQf+dkDL9ZsDWg91NfCfwGuY32prPzH6Io92CJlb5ru9gOm0d6d9mOp/g3oemhnUerm+Qd1fDqL8OkDJcYofgHfTneMG95+i7/UYN9aGdftfR/3teupvrwxrPcwG6l03As9TcozSJ9BeSHsd6dYDNyl9MsPfqOSdsL1Oc4jpCHis0xznfP9TILyMz8KOdTaGG++hJ5jq13qHaX69zjbdr8tvpl/La7O4fjXbr/uHXL/Ws80Fjqad3+H+RPCYx3cW8DsL/Vqfez7jhV3G93y/1j+cC5wg/rq+zgPOErutj9jD75R66CMKQNdRzqZq/UEBv1PGeC/y6/WvCs63qxlvhsG9b9xvA3f53YHxIoxFV9hCusYm6IocdNtbSLenhXSHWkhnrGmebpeiJd1WD73fZM4bpwc1/8wI6vawmHremZynzQKWKT7iPG0O8FbFR0Gtb50HfEbxTlDrORYEtZ41D+hX+lRgP6VPpbyXH9T92bmUk88Pyjgi3z0ZQh2pCobZBrMb5kWYnRg4jgATKv3GAJhpMMtgnlbuMOn9/UYuTCPMbphDMIVw3wSanTB7YY7AJFQhPMwsmGUwG2G2wzwNcwDmxCj4jfEb5TCbYHbC7IE5Cr+DwGws+gbHwqDQM2FyYXrCng/3ZfhdB9wI3AazC2Yv7Adg9lcjXtCVw2yFuQfmBNz2ARMHIm3AhLP9RoYyK/zGGJgSmDUw2fDPgftW/N4Bsxi/HwFOg3s5TCPMVpiNcD8I95OKDr/3wC2xBuUH3Af7cZhs2GfBlMNsgdkFkzoONMAjMAm1fmMk7PkwxxFuDTAdbkFMODfj96Ra5BMmD/ZGYAPwHrhvq0UZAu8BboLbfuAJmLfgthP2YA7SUoeyh3lkEBD2nDrQ4HchcBLsmYORZ2Aj7JuBebDvBJYAt8FtF8we2A8oo+xw3wtzog52YGI94oDJgTkJmkLgRpj08TBYlL+5HmFgxsCeB/NiPeoVZgD8GmBPXYm8j/YbWStBA7fFMDkrQQtTjt91wI0wjfi9Fbh5POKD2QH7fuAe4AkVzwSEg9m1Em4wL8IchjFWwQ+mBH4bYbJWISwwD7gXeATmJOJYBnvCENAonIh0A/eocHBbA7MZ5h6Yw6tADzMANPthfwsmsQHfnghamOOwB4f6jQ4wa2DvORQ=
*/