// Boost.Geometry

// Copyright (c) 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_ORDER_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_ORDER_HPP


#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/strategies/point_order.hpp>
#include <boost/geometry/strategies/cartesian/area.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace point_order
{

template <typename CalculationType = void>
struct cartesian
    : strategy::area::cartesian<CalculationType>
{
    typedef area_tag version_tag;
};

namespace services
{

template <>
struct default_strategy<cartesian_tag>
{
    typedef cartesian<> type;
};

} // namespace services

}} // namespace strategy::point_order

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_ORDER_HPP

/* point_order.hpp
Osz6RRAPh+H03cDKZRQ3DaJ//HRSZimMZnXKVkrCWXBqYJUDu7ICapPtszbofiVxE3c0y0iaXIV9j04QBbjZ7fNU9u+vlzPUQppClGWG71wuDEb4MhyQBVgVPYWLTOX13CVHGIdHjnWZTuudFQQfbLylAbTGL3y/K2f61OdwafRjqCDW6loJ9wU5cwZwl19yox9g2/pOneDW7Ly5/wLRLykTU76r3+m1uZ/EPivhrPzfGXQmjtVVXNb+mbF3s3dPpBS+M0YHqwVuEfZ2W3f1rmXP0VitBb0UKOJzCQCqVOxECQ9dyvl19LrQ7TWPUFgY/e04BNnpcRX8ENfkrD+eSUoKhyGYeJvEERGuXrbzCQP4Ell9do9LoSasIhUU4suqtAnfp9zKl7pR02yAnWuriE0IU5cvQWVdxevvZ6DZgc02hGsxAWEXvn+OhHNLMcbbdaiuRIh7q9fqMGgCR751cxYZRwTVqF4WfBs9mc/z+gB9buvolAazRdzRzSVPWGcfuHPNdzzac/2nvo/MesqZ4lTwGbtgLmHLhbHHKCLhlk2gkK7EwydTJej27Q==
*/