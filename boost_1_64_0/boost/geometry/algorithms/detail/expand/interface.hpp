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
IWdaZ5JyLqk27bEk+DOiPjL3WJIcPw7T+X4dNX/qeH0/Hp1LquUcS5J+ZJ0rXeE+/aU616+9Do77NP1YkpxzRFxypsn4kpgjnWqBjiYirnSugZeXbugf4nNJepvNtWWPzmdbTh2vt2V0LqnW0LEkH/8xejhnq/hcUq2hY0leL+v1cJE7js8kqfwk69d0bXZDlj+tE9LuxcPc8RL4QuaYb14zSPYmK9vLyJrxj/yXuyuPj7uo4ikC4gEilKItpCVCKYXWJD1swStNAoS2aU0CAlbXZHeTLk12w27SpnhfqKgf7xPvA28BD/DACwQPVARvRREvPPDEW1G/83sz89785v12f4v/yYek7ft+Z+bNm/P35looZPhHzg/6THkuA4HUu48hTx9I8uHOIpx8I/L8B8mjd+Cfs5Lkxs1QE+8YPZfl0R1JPRSXfkcxY+odxcD0O4oJU+8ohly/o5gx9Y5iYPodxYSFh6pi29OJCs335A0sfUuMOQcR+4cYcw6iZG8mbPy1xXQ+fKnbXwnZwUfhm1LILofsVMiuFLKvWtlzhOxmKztNyH4ShM05D0qu6DR/FMan1Tua5o7V1rwXIy/0eDhtr3MbESm+Rr75J6ddrE5qae/T5hgybUwczLrapLlKb35a7NG/YyWddaI0Ek5lar4elPElAYe6OJe/FUskZqNXvlfWHK3wKCqfzi9XJnfAkMqpcxu/kpi//YfD/jrAceuMPJsUYvPyLrzfJlhlFq6BuaR/bLM8EgmeFY/nxc/KrA8UnuqDj6AA6+Sdk3P6aHHanPNiNe3fr/T1oThTwsANtwya+9x46p6ByzyPWrQ/cxXKEQm/8finGLP7SLmu/YXqEROwazB9p9XfNM48r0//Q+KUC3cPFN/bIzm7y9Oz5XrSt3ScSH3L2w9AH2r7gsOs7HVCdgxkNfQPwx2Qtd8/lParPqGXizIJdUWA8ZmK891zed3rRMbMYhYINFjRdUeifXpe5HNYLuLAnMbHg3S08NGdkMdx+KTCyjZ9vMAaGXGfAI6t75ZKumltgXWY4zuGD0/KkrKNCiXr6YmIG1ik10mQo73vwIki8+T76NjI0LA9k+htu1rjcL/C98KqPNRIeXZL5aAPSp2H6tV587K81qsccyNWTl8F18NyXX0n7rJjW97VRw3Ztt+2x6jJcfW7/t1BuqtlupRcvTxVaWDmZgbY5It8ujwX+gFXxlzmiXXlEx1P7n3jst+s4ja7Ys4za8c2EMzd+O32A2hKms/sCrUf4LzxXQxLIoyaZ5fozym95PIv86Ju1P4vUTgmkrz35on8YKOfVq5XqXN1mR+53+vh3vb0uTxTMuatNmQ5P0JyqBtPejzzurrkPTLgIR6UYG0/Uzvd97rkyX0/ejxkQo6G7zVgnrqPfkuI4yxKpq6mCDiFzDjCPVVzDwywxhxujSomf/DZ9RM4fHB+eIDljSy7nx5wsu1+ZsDLtvtZksd2V+NR7R7PWxqa3WV7ZrvHaWh21+Mgu8vzMaWam7qaRhTOgRfreCFZx5N3pfBYaJf3zbwc+a43eA0omzc9Dprj3LYy4hQneM5s9Yo4tD4d9R80vBr/ruxHb2EcNjHdMg2ODn8A3ZPgI6djlRx++4khXpkrz0i/0w7gPC/v3zbYN4yNfUNjg9uhZyO8O2dnJpcHbccdyeTyoOzKZCybawbmdse+aX2d5Put+kiUL8/nzua6iNlvJfAJnxD0D1x3lqo41RmHnRNgsNtCJgZv+F5gyriLCwzL+rhF50NE/s4V9RjeORHGy429ksxznZWYrzvA1bBOITrbivTefhTt0znezuULkO05tAPthmUTkH0bpE8msra/+Yig+gDuVMs=
*/