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
1dHzSkx05fvoCZGXdCx+yq7Dag1o0mdxRdThXO49nert0uzT7ILg9f0KyCOf/zd1iRJfzN6RKHES/gUkDqUXebBQKlXKbcpqtVib6Sx1rbF7U2y+V7zH1GJvHl4lxcQVwHhSrCuZaYUUl+L2ev0+6F/qzcuN7uRnDFMh0gRhK4QgK/cRXu7dCX/upNynbVyDyrWqpqLOMg8l3gmYpMbsVjrn2w9A6X3+xfAR5M9YdWei9En4TaP4AZzxgAe96JloN4pfqJU7JjsX2KGh52LfBMF/N1aL3UW9q4CqxhSn4vJSAA+vHxpfTewDhvrVnwgzM6FuiP0nROZC2DIzcVaNl4wripNsbJ8yiatMWHfvsJn7+Wl9z5APD1pwJjOXCLPsguT1LZpJG38l/OBhtPj3QnlPuHU7Gvw+JBd7i0diah04zYbvxNJm5QG1UDmsbXHka3McZc55rhexu9L7hC/fO1LAeURZTk9iFip+smsH1UCrIKE7CvZbdvQTvf0hsgDCb39C25+cvG7X29aEkZfEJkjGfZfgJspC6Ak+HkyHT5mbcT4sLPUTwLNEDH3g3p8YsnDxP8IcNSpvBxYfklbAYqn41B0YhOGXJdcG9+02X7V/YsZp7BstUMgqjbkih8m2yptDoVpczkHb+eOfcPyqaxAprwdmBoJPx8/i+4zcVowxvsae9EXdDIYuJvyALStqQO/1TGGWZsfI7a2q
*/