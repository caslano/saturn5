/*
Copyright 2014-2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNMENT_OF_HPP
#define BOOST_ALIGN_DETAIL_ALIGNMENT_OF_HPP

#include <boost/align/detail/min_size.hpp>

namespace boost {
namespace alignment {
namespace detail {

template<class T>
struct offset_value {
    char value;
    T object;
};

template<class T>
struct alignment_of
    : min_size<sizeof(T), sizeof(offset_value<T>) - sizeof(T)> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* alignment_of.hpp
lnAL5IPgF9J84iW8Bf6VoXmTQXmw9KnDDt+CxvI8UPYE8RJkOXZEkTXUyolW2xRb4aRNSFEjPX8dXTztqvQFJEz6MOh2gGv2VBjxT9/S0FxLMVfzEkKtwimwH7IPSSBOD49u7jjcjW+SFuHnVTw3QwOmR9Mmq9PMUZURvjEVD1x2EPUsNCt5VgfJQARYL/totg8nQiTn6/eGCqymV1qfRI+fmGa96DTgj/ULeMiBckHgwhA99wtpBedqaZ2yt9/f8x3xJ6Rwg0pxfmNkvLhngomnoKNfa9QwQIJNl+WDUmYIKihzmibGaC5ylb7LtcdwyZFJ3NshzJpWBf5jJ1lxI5HyOsO+fG7+BVAuYXcQmzc/nF6wAJ9iPfgpvxFOJ6XdF+K59VUS0yFJ7ieYBJ79giuwTPOfGSOVTda0iYTeFBvrjqbzPrrjPazhHvC2/mjbGFXgK42ETY7VixTPSiRW4ZXwV9cmQayNBVCs/ekfHa47AB+rcp9oW/nJzs0NqPswvJYyUgCiBeJlRoN9fH/CxNo27ouWUyYpaHe8Jr3pstrNpiVm223uMLJ4ag==
*/