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
d0OEUbl0fdEJZodtCjH0lPztG4qw9EKHiQaWRzv1fCU7ShM0Ltf1bRTWrK4aZYrN66ohTk2nedqnF2sVlIvrEnNTxRr81NQKWpz3q+8wJ4ySJuuxp3GbaPEMuEuvSv9Q2lmyKHtWa2sfndU67tH4Hlt/6VQbdtXxHPYiG/ZTE9Zim3f5wektJS8zi7R5zRdDTno30+bc6Prhgf61bhGArqL3/eJYzKtMwbMs4gMu11rmzwt5dCAQ+5Nq8J4zc2eFPo0byi1GHLg7liTTWjAnywPF9gGOU99P41A7dpzy07Ico9OU6NOZ6os4jXKO3qt3nNMiTuLL1lxWowwGvz+vcugAGvG4X05YXr5emSoVzEyktblpYMfi+/Hk1EmjsNNt2LQIe4UNe5oIe6UN2ynCXm/DzhJhb7FhwyLsbTYsJ8LOs2FHibB32rDFaViLtp7gv6b3Up6zSD37Bzl4nZ8e6x1cm354nP5OXxRg6nspEpfjgHeH6QZ3GJ5PmLudjG4my9wb816NE90RqHHCOwLfp6YT3k35QeKk117AsaU8IzsynQ8pnPjexZgj9+NfqKSR3Rd1UZ+/x6iSGx3Bf6PRG5QXgwOof82aLcP9a7YFdfaREFPrTOKyzi4J4wb7/D9G2MaR43KDG4fg/5OGfNkvjfD4HECIh+cAPh7FD9+F+RTheB/ZyOXwT3N49O4MhYfvzlzO/CD9z7nwkaFUgNPJ5znc65JlMAYhPvwLHCfQ4ZUUPjLaP7plJK3VUIdfinBNhxIPdfjlOD7Ec/1eDVyYVGA314SYbjeMB3bzlTBusFf32j46XyH6At8ermcsbJ+ibd7AnKDdyLx923KE7fpyfYcxYVvch3xPxcN3om/RORPyHs8fMQe2xbr5cRAe3rP8kwAL0/uZwGBHXp8/D8OD9/7uzGATwrZ+zZiwD87LXQ7nevQ6vDvGgvfn7o1xyOa0/wAcZ1xUG7iPsaY28ABzmtrAP4ij2sDDjKk28B+J6zaAiSDJ0W3g0cSJbOCxFK7awOMDLExvH8IiG9iXwlUbmEOYagPzGFNt4ADCVRtYwJhqAwcpOL/TS+eY6ubR76SKZUTW69OX+XC62SqhO8RaXasinwc7iiY0n+d2dUz/LMhEPnG56rrUu67TWUFzUNuX5xDm0DmUAo2NHX6ohot9wwszePaswCLG6YbEAsYD+UIwr7A45FgRvFdxURZPXfequYwtQVnMvUo4/MDzQUdm+KRCzEdMlwo0X6HLxXy4ubKihNzxXXXzJIfnzOlYCfQQ55FvNkOmFjfBi0lCN72VoNId+VK5o6nOaGWE9hs241C+S+F9mktCjrsGUy+/vxWOLGDh7Bwqnshzt84z1qDnmeyRdrqLcvUu47sNTePiWQ8xV01tyaRDj6xN5oO9mMsFXipjeqGEeSQFm6xUdjaQer402dHKngdqg9rdPQ8sUta/w/NdKLg93tWGLO3Onr+rY/nr5hrd0p4jdNgDxw0M271g6L2Yh29A5H8yTdhOef+Ut3n18YzLelpFdUl3UG44brOU5ucLiVOcqTPY6t06VP5a8TSKqsxp/EfROX2D6Bvz/8hs1EuT2n64vQ7X+tljlkU6RXebHqjv8HOjOmcqEW+7HRtzkmw6qzUOpcPnvlkHaB5G/+KcB2M0P5vC3HbEOANA6Jev57jbbTdttMXznCGO+OJOvggza1CbBtcKPW5QOTBBYb96OgXMi5QKsm/bGPMKlUY5WNfYHHPg3rEehyKc7yY9UWCk/1xpylicnOcMOWXMEgV93YjAXRcerssBDzlYKzSfPJaxhfFE1InP50kBrudzm+Bo+TwlwPV8vlByOJ++3nKiXx84eRSTu4M=
*/