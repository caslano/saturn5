// Boost.Geometry

// Copyright (c) 2016-2017, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SEGMENT_INTERSECTION_HPP
#define BOOST_GEOMETRY_STRATEGIES_SEGMENT_INTERSECTION_HPP


#include <boost/geometry/strategies/tags.hpp>


#include <boost/mpl/assert.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace intersection
{

namespace services
{

/*!
\brief Traits class binding a segments intersection strategy to a coordinate system
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

}} // namespace strategy::intersection

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_SEGMENT_INTERSECTION_HPP

/* intersection.hpp
SlIhtPSghxEAAH5ZAAAcAAkAY3VybC1tYXN0ZXIvbGliL3NvY2tzX3NzcGkuY1VUBQABtkgkYO0caXfbxvG7fsWafVZAmyZFJulrrSYNTVI2nyVK5RFXTVw8EFiSqEAAxgI6Wue/d2Z3ASxAgKeUuAfjiASwc+zM7Mzs7JCNF4/3OiIvyMaXzv/X4QXvHOIq8P5BzbB4tK5/JuI/gPoZ3jcRaZAU5LNeJZtBPhONg+iSyp/ws65vIvQz8oZ/Ggj5s44f4Q6AIWTH8x8Ce74IidapktZJs0VewVurWSNdw7WpQ0Yhdac0mNfInyx+54eFcX9fZ/T7GqEhMZx6EZ6TP9YQG6C5MIKbiJELjzoODQDLkt/Ql+LGD6a39CNGg1tah4/fS77GC5sR5s3COyOgBD47tkldRi1iMGJRZgb2FC5sl4QLSma2Q0nn8uq6P3hbI3cL21wgkgcvImzhRY5FFsYtJQE1qX0rcPhGEBJvBuCA3LJZCAij0PbcOtCmJKTBkiEOJG84zCPGrWE7xhQIGSFZhKHPXjcaZhQ4IIqG5ZmsYcYyqC/CJRcLIrgGJpbGA/H8kIQeganWCI6skaVn2TN8B+nCTT+aOjZb1FJugJRrNbyAMBAV4gI4mzLBNiUjKZ4aDiM+cGyH+MY8
*/