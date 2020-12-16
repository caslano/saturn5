//
// detail/thread_context.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_THREAD_CONTEXT_HPP
#define BOOST_ASIO_DETAIL_THREAD_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <climits>
#include <cstddef>
#include <boost/asio/detail/call_stack.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class thread_info_base;

// Base class for things that manage threads (scheduler, win_iocp_io_context).
class thread_context
{
public:
  // Per-thread call stack to track the state of each thread in the context.
  typedef call_stack<thread_context, thread_info_base> thread_call_stack;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_THREAD_CONTEXT_HPP

/* thread_context.hpp
cIlc92fIxcIvYRL8C/wfe2cCF1URx/GHICGgIhqZFZlZHqViaZpZgUppIpJiadeComGRkGJZWVJZ2U1lZTeVqd10X1ZUVlZWdNtt9112X3Z8Z/a/s2/3vccui9m17/P582Pe/OfN/GfmHTvzPzLAz8BM8EswG/xK+jEBs7te4FrSO4LfiXzfg7mSvwf4I+kx4K9gCbgOrJZ0jfB9A1qBfTzZM6wX2wn9nSh23N3BTcBtwWywl6S3k3QuuCW4F9hV+reb1LsNOBXsIfOrFzgL7C3zbDtwLrg9eLxc72wwB1wI9gcvAbcGrwIHgvXgTuB94CB5Tu4MvgAOBV8HdwXfBncH35dy34IjwO/BPcB26n0LyntM9onUM8f5HhsFX1twL3AH8ABwEOgDh4KTwBGSHinpMeAEcIKcnyTpg8ACcJqcP0TSleBY8DQ5f7ak6yV9h6QflfST4DjweUm/LGnk4b0peyhghozrJrZvnrvg6wjeDXYB7wV7gPeLHI+C+4OPyziuBCvAJ8HDwaekfU+D54DPyvutUe6Pd8HrwBfkPnlR3m8vgQ+Dr4ArwDfBNcL/GfgW+L2kVeMfAFuD74pcyyxZbwcTRC51n1wqctEW/fxZKO/p88GtwAvAPuCF4A7gIlDruIEngZeAtZb4swAvA28FLwfvAq8AG8A68FHwSvBFKfc6eDX4JrgY/BxcYrfvvzlo3z/RM0Y3FCVfro2vKozvGhtfSZR8Nd58fKfavgei5GuIkm9NFHydzRoQa1Yy3qpsOqiO4TKue4EDJD0IHAnuLOfzwNHgXuAYsAQsBA8Bx4JHSvpoSZ8LFoHng3uDl4DjwJXgeHAVWAy+BO4HvgFOAj+Q9Bfg/tK/B4KZtNUHdgZLwK5gKTgAHAPuAU4DR4P7gJXgdPBs8FDwcrACvBGcAd4MVoKLW/v9QpThaGUBVP9WZP8Qg5dE9hFRtCToJ6IozG99OXnV4Oq3NrzfiLlL/h7fEUlvbzj/ETlvR+dDonZJ8/1I3ECZhiXRxz1fvSR6nxIfLwn6lUhaynXebtq/RKelQR8TOUtb7mdi5NKWxUSvejvU50QJ16vegfrebn589OqlQR8UZyyN3Q/FDW87fVHULY3eH8XtS/9dPinWLI3sl+K7pU7fFOnLmuefooF+fR9KWUO/QMXQXKgOWgF9DFnvMDZQAVQCzYFqocXQcugN6Duo07uMPzQRmgvVQaug76DN36O+9/7bPi82mP1/xfTJ68P/v7LRGs0He8Y7ahl86pxqLjyrmrV1zhdwvugKzqNDUzqjrHRmmQ+GWdrGf6d+VlCPTb49esm+YHdoLGWrztV7aGOH7eWbjI7yTFTZKO/fWxpDPhqCU48ye2fCT2mth7KxUwfK5Js9Q/Z3pXx5MN/sWYyWPcPBtvHx0tsbo/cMaY9Nb482GL0csTeQfUTqNbp8oXH0ToDaQ3OhIqVr4++DiYzbPjuq8F0+0bUx/qB1l5j9qyc0f7k1gr/SL3KNTeFB34k0t7S1s9qj6ZhtZJ0g+zMBnkZ4huj9oIPse8O63tH2/VjR3XpN17G9pKn7PJVO09eU8mqvh/kyXpd/ZwAnks18Mdd5TF+nk9/OI4p+9/vPVX0Qahe4KEnWA8RW42VoG3hLznPpT19pxfRS9iOD82J6ma+6UuSjT6Qc+lpZoss6W6efsnbm7zwotOy0mZWHmb1oyorNn+z7WjJmAb20eTp/udWb9ldBfl/f4rNesdp0Ix/1tx9PCm2NftKVspfmgxQOboadjMxHkVf8B5vzRpZQW0+JO3exzNWFMldrFrr0rYxvpn2+6lM2/9q63HxrbzNn5Vr0dzfm46WMZUNrv1yJXZNT0ts=
*/