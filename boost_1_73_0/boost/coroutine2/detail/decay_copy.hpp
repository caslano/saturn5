
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_DETAIL_DECAY_COPY_H
#define BOOST_COROUTINES2_DETAIL_DECAY_COPY_H

#include <type_traits>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {
namespace detail {

template< typename T >
typename std::decay< T >::type
decay_copy( T && t) {
    return std::forward< T >( t);
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_DETAIL_DECAY_COPY_H

/* decay_copy.hpp
/v9X+74an/+PH/EjfsSP+BE/4kf8iB/xI37Ej//sEcKc9ku9/+dVlE3eT+/+PTxz/4tUr10Xm/BgZ3h5I9a0r3P12oniMEmAV2/YlJLyCv95f/yaef9Z4rawpGBqMenz0c3m6740p7x8ZklZbqm/7jvcmz3/Qib8iZOn5BQXoBbNZy9t4ydb/bhxGG/iL8PjL6NK2krFnxREPoVp9KRsETct0cTzlYSR5Qkja+8wOBzvOYVI
*/