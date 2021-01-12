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
F3fu0odLDX99pCA+JVylj7hHQ975on+l19/WwEOF+1eu/ErEA4X7V259R138lBe9f9UQP+4Z/avskHeXzP/6+eHjjfjLBnyU9X4KPMN6PwU+zGqfLCvI39GP3wyfi6v5Ce75NsdnK78Od++/xmcqX4u7/t9y2tdG+2s/3sHaH5eXm2bGCFfpuxY+nj/qyd8f6o8f1cbHKT881C8f6uBjlLce5pcPdfFRwvX7JbNXh7zVxvzX
*/