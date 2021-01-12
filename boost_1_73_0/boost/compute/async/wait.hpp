//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ASYNC_WAIT_HPP
#define BOOST_COMPUTE_ASYNC_WAIT_HPP

#include <boost/compute/config.hpp>
#include <boost/compute/utility/wait_list.hpp>

namespace boost {
namespace compute {
namespace detail {

#ifndef BOOST_COMPUTE_NO_VARIADIC_TEMPLATES
template<class Event>
inline void insert_events_variadic(wait_list &l, Event&& event)
{
    l.insert(std::forward<Event>(event));
}

template<class Event, class... Rest>
inline void insert_events_variadic(wait_list &l, Event&& event, Rest&&... rest)
{
    l.insert(std::forward<Event>(event));

    insert_events_variadic(l, std::forward<Rest>(rest)...);
}
#endif // BOOST_COMPUTE_NO_VARIADIC_TEMPLATES

} // end detail namespace

#ifndef BOOST_COMPUTE_NO_VARIADIC_TEMPLATES
/// Blocks until all events have completed. Events can either be \ref event
/// objects or \ref future "future<T>" objects.
///
/// \see event, wait_list
template<class... Events>
inline void wait_for_all(Events&&... events)
{
    wait_list l;
    detail::insert_events_variadic(l, std::forward<Events>(events)...);
    l.wait();
}
#endif // BOOST_COMPUTE_NO_VARIADIC_TEMPLATES

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ASYNC_WAIT_HPP

/* wait.hpp
r7hh0mfS/qm2f+xHiOxX5IvbIkrBmXYup6O4628amjj7bFwm9voSpt/2h+aKmT+y31aUH5qLUndPip22WgeGwkt00uxYjpkyqtpuEXNEpWJnLM+0z/adPhazRaYBaZxi/MekUcKz116t+3TepcTYfMoe4t6/xo49u8ozf4XJol5upHn3kNgZ7ZlrNplR1GUXOr83mTpHsljydaP3Rp6Zxz37Iud3pHNpIr6ve6LYjTd1wvqx
*/