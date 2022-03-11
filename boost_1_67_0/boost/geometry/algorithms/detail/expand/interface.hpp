// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015, 2016, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_INTERFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_INTERFACE_HPP

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/algorithms/dispatch/expand.hpp>

#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/expand.hpp>


namespace boost { namespace geometry
{

namespace resolve_strategy
{

template <typename Geometry>
struct expand
{
    template <typename Box, typename Strategy>
    static inline void apply(Box& box,
                             Geometry const& geometry,
                             Strategy const& strategy)
    {
        dispatch::expand<Box, Geometry>::apply(box, geometry, strategy);
    }

    template <typename Box>
    static inline void apply(Box& box,
                             Geometry const& geometry,
                             default_strategy)
    {
        typedef typename strategy::expand::services::default_strategy
            <
                typename tag<Geometry>::type,
                typename cs_tag<Geometry>::type
            >::type strategy_type;

        dispatch::expand<Box, Geometry>::apply(box, geometry, strategy_type());
    }
};

} //namespace resolve_strategy


namespace resolve_variant
{
    
template <typename Geometry>
struct expand
{
    template <typename Box, typename Strategy>
    static inline void apply(Box& box,
                             Geometry const& geometry,
                             Strategy const& strategy)
    {
        concepts::check<Box>();
        concepts::check<Geometry const>();
        concepts::check_concepts_and_equal_dimensions<Box, Geometry const>();
        
        resolve_strategy::expand<Geometry>::apply(box, geometry, strategy);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct expand<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename Box, typename Strategy>
    struct visitor: boost::static_visitor<void>
    {
        Box& m_box;
        Strategy const& m_strategy;
        
        visitor(Box& box, Strategy const& strategy)
            : m_box(box)
            , m_strategy(strategy)
        {}
        
        template <typename Geometry>
        void operator()(Geometry const& geometry) const
        {
            return expand<Geometry>::apply(m_box, geometry, m_strategy);
        }
    };
    
    template <class Box, typename Strategy>
    static inline void
    apply(Box& box,
          boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Box, Strategy>(box, strategy),
                                    geometry);
    }
};
    
} // namespace resolve_variant
    
    
/***
*!
\brief Expands a box using the extend (envelope) of another geometry (box, point)
\ingroup expand
\tparam Box type of the box
\tparam Geometry of second geometry, to be expanded with the box
\param box box to expand another geometry with, might be changed
\param geometry other geometry
\param strategy_less
\param strategy_greater
\note Strategy is currently ignored
 *
template
<
    typename Box, typename Geometry,
    typename StrategyLess, typename StrategyGreater
>
inline void expand(Box& box, Geometry const& geometry,
            StrategyLess const& strategy_less,
            StrategyGreater const& strategy_greater)
{
    concepts::check_concepts_and_equal_dimensions<Box, Geometry const>();

    dispatch::expand<Box, Geometry>::apply(box, geometry);
}
***/

/*!
\brief Expands (with strategy)
\ingroup expand
\tparam Box type of the box
\tparam Geometry \tparam_geometry
\tparam Strategy \tparam_strategy{expand}
\param box box to be expanded using another geometry, mutable
\param geometry \param_geometry geometry which envelope (bounding box)
\param strategy \param_strategy{expand}
will be added to the box

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/expand.qbk]}
 */
template <typename Box, typename Geometry, typename Strategy>
inline void expand(Box& box, Geometry const& geometry, Strategy const& strategy)
{

    resolve_variant::expand<Geometry>::apply(box, geometry, strategy);
}

/*!
\brief Expands a box using the bounding box (envelope) of another geometry
(box, point)
\ingroup expand
\tparam Box type of the box
\tparam Geometry \tparam_geometry
\param box box to be expanded using another geometry, mutable
\param geometry \param_geometry geometry which envelope (bounding box) will be
added to the box

\qbk{[include reference/algorithms/expand.qbk]}
 */
template <typename Box, typename Geometry>
inline void expand(Box& box, Geometry const& geometry)
{
    resolve_variant::expand<Geometry>::apply(box, geometry, default_strategy());
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_INTERFACE_HPP

/* interface.hpp
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
*/