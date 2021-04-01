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
4+y2R/KNh2Hx9QTXdm82ChICc7vHWmAn0UNgdP5LwUzq3IQEUtTgNG0KrIUQ+Pap1G2nGS8YcIQW/7S/s7ijVN56726+20v9E+vHxxOBgnHPna/P/TiMX61YhAnAiGoRkPJmjS00CGUaqQXnwBMdy68cj7GVFtrhi0DwSbPX3DN38PaXTHphln5/s+mgo8TCpK0ny0lpgLQ4j29Qf6/rRJkm+e9ElJZIzlv5xaxBIFK77byq230DLcKz32ZAdJgdtNre1rVt2w29ka41dKBveHa45LG+k4aCvlsH/Klsdce1f+b98U9qqM+pzOwpO6kqnJ+VzZNa8prKQMHYcreBihuAB8FEJHsC+bKruUO99YoKQSatSJqa9FFR+CLYt++MkfVguozjGjo+M4KyFzfoSMS0x4kWFAUGWDeMGtSrKIjKgC95X3isER2zNrxn4B2R3nKXZNP0dGZQO8ZhG79jsm7267vagGgHfrRUjmgxOQOS+t1hBdWpI1jw80xjpk5ufAwd4gVZcQ0IldwLG7zmcpSpSCorcUYdWgxB0IdGU3iwFi26IkMpsBPjuQ==
*/