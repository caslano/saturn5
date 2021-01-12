// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_DETAIL_POD_SINGLETON_DWA200655_HPP
# define BOOST_DETAIL_POD_SINGLETON_DWA200655_HPP

namespace boost { namespace detail {

template<typename T>
struct pod_singleton
{
    static T instance;
};

template<typename T>
T pod_singleton<T>::instance;

}} // namespace boost::detail

#endif // BOOST_DETAIL_POD_SINGLETON_DWA200655_HPP

/* pod_singleton.hpp
7YWwDGVSR38qmBKju2pxhn0MsZCadDY8YYyHhqf0N+qA96lXzTyF+A/tFu5ofhX0EaNRavUsKpYgN5BQcXMRZEwm/1Bi9gJFY/wDvN4fYI7fa6WVbzIMdiI+EbMGMVG/TxuDOLpVuGsh7GKN7LCMiJyjXnPDmdzxsz76W4Q/hLewYpL4fYovco7A/Agw89H+nVoZ1tc+kMXr7RQff/HX+8kSUo0aOZdlcpFcvTG1+e5oVCAI
*/