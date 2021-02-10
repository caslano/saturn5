// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2015 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2018.
// Modifications copyright (c) 2013-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_BOX_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_BOX_BOX_HPP

#include <cstddef>

#include <boost/geometry/algorithms/dispatch/disjoint.hpp>

// For backward compatibility
#include <boost/geometry/strategies/cartesian/disjoint_box_box.hpp>
#include <boost/geometry/strategies/spherical/disjoint_box_box.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace disjoint
{


/*!
    \brief Internal utility function to detect if boxes are disjoint
    \note Is used from other algorithms, declared separately
        to avoid circular references
 */
template <typename Box1, typename Box2, typename Strategy>
inline bool disjoint_box_box(Box1 const& box1, Box2 const& box2, Strategy const&)
{
    return Strategy::apply(box1, box2);
}


}} // namespace detail::disjoint
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Box1, typename Box2, std::size_t DimensionCount>
struct disjoint<Box1, Box2, DimensionCount, box_tag, box_tag, false>
{
    template <typename Strategy>
    static inline bool apply(Box1 const& box1, Box2 const& box2, Strategy const&)
    {
        return Strategy::apply(box1, box2);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_BOX_BOX_HPP

/* box_box.hpp
8HqLks0C9TibEgMlYFPiRXSPz+AdPDFxWiUDl1tg1O7eWn1Loy/jWuelXcrnedSt4lCnj5cP180wzVx7OXc4z+8HTWztAh8I36tZaiMq4VbsyMeeV11g8w4/yS7Ov3umr+ABL3S//BbOl6VZl3DBrKCK1qKZLFmnaVIk0Qi5YK1TI7UGET5HMnOTQhlPGgk9xMTXdc9GHQMiLmboB1Dx+Me77hypGEXLp6qZxRwG1L/KJakOqauji8nTlnm351bbielZSaiSskXXV92L19137XcXl79oxXqo0LBZYTeN7xtPzZ/OtXYz9XlJTo9R9MQnI6melRnIyXo6Z4V447A8hxolHzFBYYRMcJSb7LaVDAululfSrH53dNW8wlfmu5ZfEat5UJ7Kyz2y4pzhvpq+OmvwGgbXUIrcXH0hdQOEV1NqHVyS6+K/+nqCvcOLcZsGV+K53K6+lHD38Fq8tsHFCLu28ipK/UrzmjolSwxWEludgfxvnLy2WAlP314t3orh4SEumEVtYWGYxNzKMEUhrx0hJwES2lLOaiQn6IId9eOR3cJXUqZvRY88V3pbK868X0eojOu7jnmYb5qfMLLObO+aQtNqNr3NoB1nODSvmCMBSf2JrjTUrxrw//gSbMLXy3EL81+9gCeqVqff
*/