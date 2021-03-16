// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2013 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2013 Bruno Lalande, Paris, France.
// Copyright (c) 2013 Mateusz Loskot, London, UK.
// Copyright (c) 2013 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_POLICIES_ROBUSTNESS_ROBUST_POINT_TYPE_HPP
#define BOOST_GEOMETRY_POLICIES_ROBUSTNESS_ROBUST_POINT_TYPE_HPP

namespace boost { namespace geometry
{

// Meta-function to typedef a robust point type for a policy
template <typename Point, typename Policy>
struct robust_point_type
{
    // By default, the point itself is the robust type
    typedef Point type;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_POLICIES_ROBUSTNESS_ROBUST_POINT_TYPE_HPP

/* robust_point_type.hpp
jdU6EHdYN3Sly5ICC8WPP4iviwvjBfrOVoG+6TITfHgZIwbyAyYm1ZnWkl3AiKKGuzkRA3kAyBilg0DGJh2M6ZUgYttqI0GoZ2gUrWIoyNjIRSBjI+OeTLsZZKzkapCxkv8ZZAzk5ZhiWY3aqARkbFEKqCZji9KZlAyRWAVjNYzdztg+xl5jLNZQjG3FqjaPiMt6q9q86uGm23AZWSset1VzbwtXOx2WuMJNtlK4sTiC3FBg4lGdyA24y2KFm9Q=
*/