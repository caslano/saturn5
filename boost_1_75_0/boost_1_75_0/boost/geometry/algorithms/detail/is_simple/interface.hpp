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
bRnoYzJGk8GzBNy6bRGel3FfPmLsHD5auWBxZa5h0TrLjIvu0IQKDIzaIEWD2eVywUlUAXrlNl0q+Im9TnSdvfyisFCqkP1Kt+VV2zqcZSuyzlI9lho5U8qzNWFrmX2no9De7Q56pmBXZWqOq9IRBBw5iEvQekwl/G1eu+qZ67IKBt7CD6D+2VD/zKH1vy8DZVD9d/DsA3caXICdV3DeAjdqaF5oYDTURxlA0CxwGEY2k7BYb9Bp4NY6TOwY1GRsT870T4vYgqbDWzPRkR8sZ8P95kTB789+HAqIc3KPE0BbLnWfEz1ii+jPF0HwjvG1sMROweJKqUespHZy69RsaxWxkXvQlePe7rk7dYn/UPZy/9rcqzBuy70Xp3tSPe58l9+x0rKBG75tFLKY4Vum6OdWPKo/L9dDL4Y22u4r226w3TcbAj/ZzuTzbtyu85mJgb5xxEDfmxEDfbGyI+u2E/0f+NsNTlR2LTCjurxXicDHh/AnVKE9YlwZ0RPbDXvNC79KQ69sp7qj7ZruzTA4NPqlAddNgkDGLxmum/LLaFz3fIKaRHDoyRjXCeGIYAjDmVxD7iWo/SWXr2gCz8/A7f1lRF55wGAztNeAjUTZfWe6er8wlOIX0Kl/S8x8jko33i2fUsotG1WbcqfsF5fCXkcv55Q8DPFAOq81OcJr/eSXBl7r3yAwqofV1dQTzWs9Irnei8NrXYPK2N3Q
*/