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
kB/fS0mu68FA81AZFiny3nPOPbyM1yHe/LQniD0cfvjk7T+nh8Z90tzo/3jhTifk+Qu6HyWuaXwF1RCHrJd8gFdlveCszcp7ris/z/NX0K29SP8a+uR17qe00mX2+SNdPxtxXzmcjQZ4++HD7zjH5cXlRYQbpgSXyBxXG27uI1yV7cpfFXt6ii3/GIE7MBkfAS4rYWH11j0yw0FzKQquLC/BLEpuCyM29CEUXMWxFZJjNJuv0uk/ER4rUVQ9zrNuYCvdyBIVe+AwvODioYOpmXHQW0Ig/FJYR5iNE1rFRM/huNnZHsaLYNJqsAcmJNsQHXOonKvtH8Nh0RhJlQxLXdhhsbcirtzuf1WtSM2OPUPXDk6jsTyCj4+w06XY+pEsosW62Uhhq+ggiwhVOdQGlkvZw1Gq4LYrgSPr3Yp8JGpSL5wfrFbWsz1WencUSLb2QNvGKKIjWyiu1GR8hEaV3LTxrRF7lt7l1vIfHNlBewmtSBXCJEOahdgwK2yEL+nydna3xJdksUimyxVmfyOZrnq8f9PpDfWGIFYD/lQbbkmFgdjVUvDyiPwn3vTlLfx55raiMnKqgBtDrO8QXv6GpDbU1he/hgil2Pg4vI/fXn73+YmphskwiLNbTJNP4+AU2Dn1oSPP4Q1S9/uG
*/