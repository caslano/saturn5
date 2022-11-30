// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2020, Oracle and/or its affiliates.

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
#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/relate/services.hpp>


namespace boost { namespace geometry
{

namespace resolve_strategy
{

template
<
    typename Strategy,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategy>::value
>
struct is_simple
{
    template <typename Geometry>
    static inline bool apply(Geometry const& geometry,
                             Strategy const& strategy)
    {
        return dispatch::is_simple<Geometry>::apply(geometry, strategy);
    }
};

template <typename Strategy>
struct is_simple<Strategy, false>
{
    template <typename Geometry>
    static inline bool apply(Geometry const& geometry,
                             Strategy const& strategy)
    {
        using strategies::relate::services::strategy_converter;
        return dispatch::is_simple
            <
                Geometry
            >::apply(geometry, strategy_converter<Strategy>::get(strategy));
    }
};

template <>
struct is_simple<default_strategy, false>
{
    template <typename Geometry>
    static inline bool apply(Geometry const& geometry,
                             default_strategy)
    {
        // NOTE: Currently the strategy is only used for Linear geometries
        typedef typename strategies::relate::services::default_strategy
            <
                Geometry, Geometry
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

        return resolve_strategy::is_simple<Strategy>::apply(geometry, strategy);
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