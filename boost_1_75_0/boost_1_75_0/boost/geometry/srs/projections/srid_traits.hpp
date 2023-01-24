// Boost.Geometry

// Copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_PROJECTIONS_SRID_TRAITS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_SRID_TRAITS_HPP


#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_SRID_TRAITS_BEG(AUTH, CODE) \
template<> \
struct AUTH##_traits<CODE> \
{ \
    typedef \

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_SRID_TRAITS_MID() \
    parameters_type; \
    static inline parameters_type parameters() \
    { \
        return parameters_type \

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_SRID_TRAITS_END() \
        ; \
    } \
}; \


#endif // BOOST_GEOMETRY_PROJECTIONS_SRID_TRAITS_HPP


/* srid_traits.hpp
U8hF9AzlQUYJ5XmPC+OBEsO6XHkRDfPuwmEch12HzkGZMY5jQDAuZS9tFLO4PWQuTyu3lwmk5JAN5QHwR+bFFL1gDpeVW6yAydxJdfzZiYGzAfBwOf57/d23rUQAAnXPwNHvnAt5m5HzC+YnNL+kLTE/CK7jXwbLgoZ6o/SXSJ+onrCfYN79rOgwHWjMp+dTUikh8CpYFfQOerhvJ91qeIswI+HZiziBm3vOiEJ89wJF5QpU1gbNafWmswR7O+IrqQHTudnzrgykyy7vZYdbQkGWtaxGLUCBp7msMTK++zVxazK/TWuyOmT+wBL/pseaAiiKDBqY/Iagyr9cEkiLwTo0bUuvKMtLy8fLXDz/bba0u2ya4JsDkbyCpRS7m5TWzEldxbeDHFVFTdkY4UgNdVXcPCACKezlYeM3I4QAQVE+N0OgANEJ0FjM1xPiaNr0JTas+oa5dzv7KOcoSKM9skPBNDqDeyZI7088MZnjIzjF6fdj62PxCN1uNb+6knJkZYpjK/8q29FnjVakF34mkCjRgdIflG+1mY6DqPU7bAemeBCS7UHBC8YbGoOxNdaI83u6pI5yl5ZAQqpxzfjuDs1xR1A/KNeuDpq+jr6givxUjgiJ8uje8G66pZGUiLimbxdnwsOTjNf4+qQSQwq4rOqBroHISZI+uHy5P8IGBlS8qgHNgjjxipKd4lW6hd9xjkK0Tp3swJAdAWzr
*/