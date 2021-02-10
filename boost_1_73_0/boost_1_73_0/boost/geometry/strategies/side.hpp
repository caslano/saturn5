// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SIDE_HPP
#define BOOST_GEOMETRY_STRATEGIES_SIDE_HPP


#include <boost/mpl/assert.hpp>

#include <boost/geometry/strategies/tags.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace side
{

namespace services
{

/*!
\brief Traits class binding a side determination strategy to a coordinate system
\ingroup util
\tparam CSTag tag of coordinate system of point-type
\tparam CalculationType \tparam_calculation
*/
template <typename CSTag, typename CalculationType = void>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_TYPE
            , (types<CSTag>)
        );
};


} // namespace services


}} // namespace strategy::side


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_SIDE_HPP

/* side.hpp
F0VNG6VJQmbFlxlINnHVribYPFwt1/dLjZ+wlGArJ5kJcGXGuCMzKrGXm5bAhnVQznmrlPNWhvOjAw14Ta6XdgSsyT9PNlcuN6yCNSlYCQfNgzhYXUprko8SDlp5DtZv1DZ4qb32b0eP1bS3sWFvY0eUUhfLN+pt0e90QAPOPh5wqy9nbLcxz+mtKIXeT0XNld42VUnN4q7KXdSEVSMlFXi6c6uVSsPTdwxu3S94eLfgASLfqhHwsN60J1Tq0y5svgQftQFqu/anbY6sM74u1/j0ZO5omw6lvfuTHq076YBOmad05LkmotbOMsm0EBXof0370Jcokj26fDb2+KxJEDMdPpsriyri7WqIBwuq4DcF9vE/2+yHysJV0aZmtQlntxacHb1ZJj4dsqF4GruVxrBFVlb4PffWTrVw/O2i9kXxzqMEpNset7feqmza8ZTV9br08LreHrW5rVF/8nyl+r++kJedi1rIi1OLIhvbPjVaV7PJU2geROHxCr6/5plSgQzUpLdZkuVuDIYyUGjPnXW9tPiN9moZ/VI9/e9Ywq49u2n2u3f961F8/o4Cym0OC/T9m9rkasXytz/hW7MnW28LJ6W2sDrNvSeJjKz5ZYvxcCJ/2KKol8wwTfy5TmzBeM7Uto15YAAHVq6D
*/