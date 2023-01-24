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
gNFRbUGwk0j07CPhVs84N7sO3lgBGxyY28ZL0zZvAJFj91YCGQIAOAg8/BYhAhTshlN2b39CUto2QbKaN3RDCfEBrAAbQgvQAaywyw0BEmOABvwM3WDzxHGBZvHeq8cOUiVY0Som0phIJVkmOaoZXvkfYm8lvifBiEMRBoJM9Lo2WPWOFVIAJFmB4Vh2C17F4J80x+ps2+o0WxWTZdK0sRsIJWm7ig3vL0JlaHdUztU7hAgwi3kDMQr1LyCzByeIPiAfSYqwWUETJzssadvUDlpUyzqIdc4qq3e+HpBYjc0NwJaTUKZijyDuUheM0860yio2ri3SQANw/TZP5SqGRCWwwS6HAUfWuTunJ0YwfljnqAgNBYRmrraB8CKEYDhhT4EEprmW8FDnVscKC82uXH4AVq9vou55SdovzawG1JhIBsSqqJgko0jO/pHmi7RQWrPFu0TPBbIEfRkEpLA7ESvoSamZEPr1XRSNEXVRVbcuSita0VsXbUOWCYt8QGm3j3UUDEcYTKsIqR18QgNpuNMzE6RLjHeWHnoWpdrXINy+hSkAegTFf1obnwGg02AGABzWgnizkiRANHEcS5XVDBUVregemsLxgWkDphEuEIpWc4nQTH3GEJngQbGjTiiSo4omFAsOO46NwUcdVAuDTR1AjhWISoDPIdIvNKdY0s6wsYeMmd2F4p11EjEeAs5EAsh7kHWqxD6HGJgc
*/