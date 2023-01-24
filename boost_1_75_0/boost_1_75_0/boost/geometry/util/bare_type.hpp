// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2012 Bruno Lalande, Paris, France.
// Copyright (c) 2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_BARE_TYPE_HPP
#define BOOST_GEOMETRY_UTIL_BARE_TYPE_HPP


#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/remove_reference.hpp>


namespace boost { namespace geometry
{

namespace util
{

template <typename T>
struct bare_type
{
    typedef typename boost::remove_const
        <
            typename boost::remove_pointer
                <
                    typename boost::remove_reference
                        <
                            T
                        >::type
                >::type
        >::type type;
};


} // namespace util

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_BARE_TYPE_HPP

/* bare_type.hpp
YIqPxgKy0EK7hUhh8oVgP/0bFJIh1stb4RWQzY3rI+8j+uGB4M4lwYcZ6HW6YNDW4Cm3igenkHE2thIPqF9735aKEBjCAE9yLWe5yL4GM0KnH643zvNY5QVg/dfDDxcg/JwcmMXXNK6vgXdyZ6t3Xb8qKjOwlTK1S9Xh/URpV7nOxnoDSa9IxtmXEMU+RZoLkc0mWE1rsrzhB3uSKqhjlc24WlZrJL61c376EakkKgxL4X/9zq5VqrPSUbsrlUPUelr1UevR5SuLJhXfmQgi6UxC0nWQnwo1vqD+2sHD4Y5rRufRxdHD1sOyfXX66t6KcGeJOjmK5fcfZoWYnNWEpN+6V2jt0dUjY0xYfvz65vt0bxZtiGYkTHjKCekmfUGfj2BukxiYfIa3bAOjHYikhh28+7rfcr4Kp3rdtjTuMqGP7skbZdePa/uHQj+DfeCu25vaFeZiXxQgM4B+t+20980Mo1v4WT4pLZp4gBqJiYS0fBDty9QD3DeOyudoMu177OMpQE0ms16su7tLpif9lm3m+A3KMsLcRy3goSFyKUe8mVJYS2adx/8G67n7t2k5lOIZABqR8cXzzF7gjWeQ9pV7oK2AMhnS3CqUKJY7MCmI+Qq+wbqFg+KVtxXOCY4FJxwLemqFmPGRWGK+ce2MC7wZZcGPbNehytts1nnf9Z7GtAz/OH/0+jShP3svavLFzG1EbTTXhICVrrfz
*/