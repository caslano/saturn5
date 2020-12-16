//
// detail/timer_scheduler_fwd.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_TIMER_SCHEDULER_FWD_HPP
#define BOOST_ASIO_DETAIL_TIMER_SCHEDULER_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_WINDOWS_RUNTIME)
typedef class winrt_timer_scheduler timer_scheduler;
#elif defined(BOOST_ASIO_HAS_IOCP)
typedef class win_iocp_io_context timer_scheduler;
#elif defined(BOOST_ASIO_HAS_EPOLL)
typedef class epoll_reactor timer_scheduler;
#elif defined(BOOST_ASIO_HAS_KQUEUE)
typedef class kqueue_reactor timer_scheduler;
#elif defined(BOOST_ASIO_HAS_DEV_POLL)
typedef class dev_poll_reactor timer_scheduler;
#else
typedef class select_reactor timer_scheduler;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_TIMER_SCHEDULER_FWD_HPP

/* timer_scheduler_fwd.hpp
N0n30BOrKSG2aBv6DIVp9Rmn35cnv+c/TOm/p7RXnjR860rkd+B3SWaqbRDW/vrg+EeKuC7v7QHbKJxe/jX+6mabqNxsa6td06ngNR0PvwHFmW6bgnv1oyPtJTgs+K5xCPobsU4SOcDAuZrCMgcGqO/Ko2lPX02xj3dljvPJAPVdeYbxXZllYgZirUXkHe3aKOcwnUzWQN7z18b1rGHPH8vkyXRqXPp0Ellm6UDeu3hBzdyYyFb6/YsyrTrIvZZOaU23uqcDkDnrXlv6mxwf9fpDhtexVlnlFTOIdWtb87bUTbtGxfs4PoLMt7w+9Xx39D88403Gte8yA1uj6j1Xs34AfxT7F+CCOkY7Lb6DFZusXVUY90PKMS8tm7/Xo2H0YFwI2cZr1THP/3dKt2wf+s5UYc2lzHID5JiVMF/4P7MtQW+1GOc4Tj85hrQWcTAy32CLtNwbewvJdJZ7Y2eVCv8GtKHlpmPZeJJ/yNbPlijHspMUB37Jy0y3JcfomylOie0LJRVSuIa+68Q15IO+/IWSZsu33P97LcnFyD1M15P/OttXnNYkTVpRWAm32+Zp7oPW6OUYsoTkFti+5LjjNXGTlS+VNrZqxKW9FfihKjVryskk90dbFeKIfleP9n0G8+UJ6nc9YiJjFeO+YZZLG6qOMYXuMSbOx75hjuMYqo4xLhc2DhvHGZarhlwmrRcvu0Dfz3rD34p5mz8WfSrey2EvceBczqKvoZ69+lqX+ca+VmHR1xaZ9DVXC9/zfx1nzC3EGfPCgTZnP5/wzfaSN+7osCF5YI4VN8z/H9+zOe+1NZfM1+J7vobveZdN8j3Lv0sT5N80fyu8LxQdXP6dIP92f4dKAo6H+5nmb+wrwg86wRVp/sb4QZy9s+Dw7UnK4xuTTBPPUVL+W83fZzV/45mA0smB+wP/nQvXqPkb46XMS3IgL7Dmep6MiZXlcAbUmot6kkauPsD0TvuQy9HIOUqs8/2RlIMrCzA9H3K52vvzoe84jZwrgPS2wu1iuZMslwBcz3InICf8nwC7Az8F9gV+BhwG/Bw4Gvg9cDLwT0An8M/Aa4Gngbfx9fuA3wA3As8CnwT+DfgSxz8MPAd8l/3HgaeAv2e/5LIut9ZrlkbO6aN+Lpdy+FX4T28PXBbLdTHhsn4Txd0LeAQ4BPhr5mU6CnQCoROVx3vAKvZfz/4bgceAPwG+D6wBHmfO6g+Au4EfMld1I/A3wN8Df8fpnwZ+DPwKeAoYJvYVACOAnwFZT5yXCaz9N1znv91QuVUG1q6zKv2Xr1N4uL4uYrlWwDyW6w25WGAGMA7YF5gMHAhMBQ4BpgGHcvvsBxzM14eL65yPC87J97Of84nl9QyFebaSmCcrlTnl+zJ/VrZID/gj4FDgVcwdnw/MAZYDh3P9jQDeDhwJvJ855TexnOzvVYHVh6sqsPrYVRVYfTRW+a+PWoX3swI/Y7nWwOUs1wC5FOBRYFf292Z/DvAd4BTgu8DZwPeAhcBjwHLgb4CLgO8D7wD+FngP8DjwUeAHwOc4vQbg7/m+1sJVcDtJ4X4Yx3vdxG8P39fzwHTgXuAg4D5uB/uB04EvAGcBXwRWAuv5fl7i+3gZuA74CnAH8ACPV68CDwEPAk8DXweKfamH+f6KFd5DCNxsYntgK+SSgNuAHYGP8ji6HZgL3AGcAHycx9OdwFLgLuAy4BN8f7s1/aZR5mfsNxu4fzwM7Mn+dPbnAOuAVwB/zvXyC+DNHL4SuInzWaHw/i7gEc7nQuBSzudZBfrQOMnlD5wE3Au8jK9fA9wHvA64H7gQ+AJwMbAeKPJ4Cbia420AvgZ8DPgqcB/wde4/aXJPE+Ygbgdim1Y=
*/