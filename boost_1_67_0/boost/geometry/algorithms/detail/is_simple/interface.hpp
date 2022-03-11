// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2017, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_INTERFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_INTERFACE_HPP

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/algorithms/dispatch/is_simple.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/intersection.hpp>


namespace boost { namespace geometry
{

namespace resolve_strategy
{

struct is_simple
{
    template <typename Geometry, typename Strategy>
    static inline bool apply(Geometry const& geometry,
                             Strategy const& strategy)
    {
        return dispatch::is_simple<Geometry>::apply(geometry, strategy);
    }

    template <typename Geometry>
    static inline bool apply(Geometry const& geometry,
                             default_strategy)
    {
        // NOTE: Currently the strategy is only used for Linear geometries
        typedef typename strategy::intersection::services::default_strategy
            <
                typename cs_tag<Geometry>::type
            >::type strategy_type;

        return dispatch::is_simple<Geometry>::apply(geometry, strategy_type());
    }
};

} // namespace resolve_strategy

namespace resolve_variant
{

template <typename Geometry>
struct is_simple
{
    template <typename Strategy>
    static inline bool apply(Geometry const& geometry, Strategy const& strategy)
    {
        concepts::check<Geometry const>();

        return resolve_strategy::is_simple::apply(geometry, strategy);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct is_simple<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename Strategy>
    struct visitor : boost::static_visitor<bool>
    {
        Strategy const& m_strategy;

        visitor(Strategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Geometry>
        bool operator()(Geometry const& geometry) const
        {
            return is_simple<Geometry>::apply(geometry, m_strategy);
        }
    };

    template <typename Strategy>
    static inline bool
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Strategy>(strategy), geometry);
    }
};

} // namespace resolve_variant


/*!
\brief \brief_check{is simple}
\ingroup is_simple
\tparam Geometry \tparam_geometry
\tparam Strategy \tparam_strategy{Is_simple}
\param geometry \param_geometry
\param strategy \param_strategy{is_simple}
\return \return_check{is simple}

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/is_simple.qbk]}
*/
template <typename Geometry, typename Strategy>
inline bool is_simple(Geometry const& geometry, Strategy const& strategy)
{
    return resolve_variant::is_simple<Geometry>::apply(geometry, strategy);
}


/*!
\brief \brief_check{is simple}
\ingroup is_simple
\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\return \return_check{is simple}

\qbk{[include reference/algorithms/is_simple.qbk]}
*/
template <typename Geometry>
inline bool is_simple(Geometry const& geometry)
{
    return resolve_variant::is_simple<Geometry>::apply(geometry, default_strategy());
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_INTERFACE_HPP

/* interface.hpp
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
*/