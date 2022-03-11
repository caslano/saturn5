// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2019.
// Modifications copyright (c) 2013-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_AREAL_AREAL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_AREAL_AREAL_HPP

#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/algorithms/detail/for_each_range.hpp>
#include <boost/geometry/algorithms/detail/point_on_border.hpp>

#include <boost/geometry/algorithms/detail/disjoint/linear_linear.hpp>
#include <boost/geometry/algorithms/detail/disjoint/segment_box.hpp>

#include <boost/geometry/iterators/segment_iterator.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace disjoint
{

template <typename Geometry1, typename Geometry2, typename Strategy>
inline bool point_on_border_covered_by(Geometry1 const& geometry1,
                                       Geometry2 const& geometry2,
                                       Strategy const& strategy)
{
    typename geometry::point_type<Geometry1>::type pt;
    return geometry::point_on_border(pt, geometry1)
        && geometry::covered_by(pt, geometry2, strategy);
}

/*!
\tparam Strategy point_in_geometry strategy
*/
template<typename Geometry, typename Strategy>
struct check_each_ring_for_within
{
    bool not_disjoint;
    Geometry const& m_geometry;
    Strategy const& m_strategy;

    inline check_each_ring_for_within(Geometry const& g,
                                      Strategy const& strategy)
        : not_disjoint(false)
        , m_geometry(g)
        , m_strategy(strategy)
    {}

    template <typename Range>
    inline void apply(Range const& range)
    {
        not_disjoint = not_disjoint
                    || point_on_border_covered_by(range, m_geometry, m_strategy);
    }
};


/*!
\tparam Strategy point_in_geometry strategy
*/
template <typename FirstGeometry, typename SecondGeometry, typename Strategy>
inline bool rings_containing(FirstGeometry const& geometry1,
                             SecondGeometry const& geometry2,
                             Strategy const& strategy)
{
    check_each_ring_for_within
        <
            FirstGeometry, Strategy
        > checker(geometry1, strategy);
    geometry::detail::for_each_range(geometry2, checker);
    return checker.not_disjoint;
}



template <typename Geometry1, typename Geometry2>
struct areal_areal
{
    /*!
    \tparam Strategy relate (segments intersection) strategy
    */
    template <typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        if ( ! disjoint_linear<Geometry1, Geometry2>::apply(geometry1, geometry2, strategy) )
        {
            return false;
        }

        // If there is no intersection of segments, they might located
        // inside each other

        // We check that using a point on the border (external boundary),
        // and see if that is contained in the other geometry. And vice versa.

        if ( rings_containing(geometry1, geometry2,
                              strategy.template get_point_in_geometry_strategy<Geometry2, Geometry1>())
          || rings_containing(geometry2, geometry1,
                              strategy.template get_point_in_geometry_strategy<Geometry1, Geometry2>()) )
        {
            return false;
        }

        return true;
    }
};


template <typename Areal, typename Box>
struct areal_box
{
    /*!
    \tparam Strategy relate (segments intersection) strategy
    */
    template <typename Strategy>
    static inline bool apply(Areal const& areal,
                             Box const& box,
                             Strategy const& strategy)
    {
        if ( ! for_each_segment(geometry::segments_begin(areal),
                                geometry::segments_end(areal),
                                box,
                                strategy.get_disjoint_segment_box_strategy()) )
        {
            return false;
        }

        // If there is no intersection of any segment and box,
        // the box might be located inside areal geometry

        if ( point_on_border_covered_by(box, areal,
                strategy.template get_point_in_geometry_strategy<Box, Areal>()) )
        {
            return false;
        }

        return true;
    }

private:
    template <typename SegIter, typename Strategy>
    static inline bool for_each_segment(SegIter first,
                                        SegIter last,
                                        Box const& box,
                                        Strategy const& strategy)
    {
        for ( ; first != last ; ++first)
        {
            if (! disjoint_segment_box::apply(*first, box, strategy))
            {
                return false;
            }
        }
        return true;
    }
};


}} // namespace detail::disjoint
#endif // DOXYGEN_NO_DETAIL




#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Areal1, typename Areal2>
struct disjoint<Areal1, Areal2, 2, areal_tag, areal_tag, false>
    : detail::disjoint::areal_areal<Areal1, Areal2>
{};


template <typename Areal, typename Box>
struct disjoint<Areal, Box, 2, areal_tag, box_tag, false>
    : detail::disjoint::areal_box<Areal, Box>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_AREAL_AREAL_HPP

/* areal_areal.hpp
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
*/