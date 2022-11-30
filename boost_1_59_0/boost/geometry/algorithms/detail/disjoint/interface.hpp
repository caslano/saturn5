// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2021.
// Modifications copyright (c) 2013-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_INTERFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_INTERFACE_HPP

#include <cstddef>

#include <boost/geometry/algorithms/detail/relate/interface.hpp>
#include <boost/geometry/algorithms/detail/visit.hpp>
#include <boost/geometry/algorithms/dispatch/disjoint.hpp>

#include <boost/geometry/geometries/adapted/boost_variant.hpp> // For backward compatibility
#include <boost/geometry/geometries/concepts/check.hpp>

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
struct disjoint
{
    template <typename Geometry1, typename Geometry2>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        return dispatch::disjoint
                <
                    Geometry1, Geometry2
                >::apply(geometry1, geometry2, strategy);
    }
};

template <typename Strategy>
struct disjoint<Strategy, false>
{
    template <typename Geometry1, typename Geometry2>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        using strategies::relate::services::strategy_converter;

        return dispatch::disjoint
                <
                    Geometry1, Geometry2
                >::apply(geometry1, geometry2,
                         strategy_converter<Strategy>::get(strategy));
    }
};

template <>
struct disjoint<default_strategy, false>
{
    template <typename Geometry1, typename Geometry2>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             default_strategy)
    {
        typedef typename strategies::relate::services::default_strategy
            <
                Geometry1, Geometry2
            >::type strategy_type;

        return dispatch::disjoint
                <
                    Geometry1, Geometry2
                >::apply(geometry1, geometry2, strategy_type());
    }
};

} // namespace resolve_strategy


namespace resolve_dynamic {

template
<
    typename Geometry1, typename Geometry2,
    bool IsDynamic = util::is_dynamic_geometry<Geometry1>::value
                  || util::is_dynamic_geometry<Geometry2>::value,
    bool IsCollection = util::is_geometry_collection<Geometry1>::value
                     || util::is_geometry_collection<Geometry2>::value
>
struct disjoint
{
    template <typename Strategy>
    static inline bool apply(Geometry1 const& geometry1, Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        concepts::check_concepts_and_equal_dimensions
            <
                Geometry1 const,
                Geometry2 const
            >();

        return resolve_strategy::disjoint
            <
                Strategy
            >::apply(geometry1, geometry2, strategy);
    }
};

template <typename Geometry1, typename Geometry2>
struct disjoint<Geometry1, Geometry2, true, false>
{
    template <typename Strategy>
    static inline bool apply(Geometry1 const& geometry1, Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        bool result = true;
        detail::visit([&](auto const& g1, auto const& g2)
        {
            result = disjoint
                <
                    util::remove_cref_t<decltype(g1)>, util::remove_cref_t<decltype(g2)>
                >::apply(g1, g2, strategy);
        }, geometry1, geometry2);
        return result;
    }
};

// TODO: The complexity is quadratic for two GCs
//   Decrease e.g. with spatial index
template <typename Geometry1, typename Geometry2, bool IsDynamic>
struct disjoint<Geometry1, Geometry2, IsDynamic, true>
{
    template <typename Strategy>
    static inline bool apply(Geometry1 const& geometry1, Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        bool result = true;
        detail::visit_breadth_first([&](auto const& g1)
        {
            detail::visit_breadth_first([&](auto const& g2)
            {
                result = disjoint
                    <
                        util::remove_cref_t<decltype(g1)>, util::remove_cref_t<decltype(g2)>
                    >::apply(g1, g2, strategy);
                // If any of the combination intersects then the final result is not disjoint
                return result;
            }, geometry2);
            return result;
        }, geometry1);
        return result;
    }
};

} // namespace resolve_dynamic


/*!
\brief \brief_check2{are disjoint}
\ingroup disjoint
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam Strategy \tparam_strategy{Disjoint}
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param strategy \param_strategy{disjoint}
\return \return_check2{are disjoint}

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/disjoint.qbk]}
*/
template <typename Geometry1, typename Geometry2, typename Strategy>
inline bool disjoint(Geometry1 const& geometry1,
                     Geometry2 const& geometry2,
                     Strategy const& strategy)
{
    return resolve_dynamic::disjoint
            <
                Geometry1, Geometry2
            >::apply(geometry1, geometry2, strategy);
}


/*!
\brief \brief_check2{are disjoint}
\ingroup disjoint
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\return \return_check2{are disjoint}

\qbk{[include reference/algorithms/disjoint.qbk]}
\qbk{
[heading Examples]
[disjoint]
[disjoint_output]
}
*/
template <typename Geometry1, typename Geometry2>
inline bool disjoint(Geometry1 const& geometry1,
                     Geometry2 const& geometry2)
{
    return resolve_dynamic::disjoint
            <
                Geometry1, Geometry2
            >::apply(geometry1, geometry2, default_strategy());
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_INTERFACE_HPP

/* interface.hpp
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
*/