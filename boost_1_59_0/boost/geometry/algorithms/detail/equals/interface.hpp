// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014-2021.
// Modifications copyright (c) 2014-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_EQUALS_INTERFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_EQUALS_INTERFACE_HPP


#include <cstddef>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/reverse_dispatch.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tag_cast.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/relate/services.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Geometry1,
    typename Geometry2,
    typename Tag1 = typename tag<Geometry1>::type,
    typename Tag2 = typename tag<Geometry2>::type,
    typename CastedTag1 = typename tag_cast<Tag1, pointlike_tag, linear_tag, areal_tag>::type,
    typename CastedTag2 = typename tag_cast<Tag2, pointlike_tag, linear_tag, areal_tag>::type,
    std::size_t DimensionCount = dimension<Geometry1>::type::value,
    bool Reverse = reverse_dispatch<Geometry1, Geometry2>::type::value
>
struct equals: not_implemented<Tag1, Tag2>
{};


// If reversal is needed, perform it
template
<
    typename Geometry1, typename Geometry2,
    typename Tag1, typename Tag2,
    typename CastedTag1, typename CastedTag2,
    std::size_t DimensionCount
>
struct equals<Geometry1, Geometry2, Tag1, Tag2, CastedTag1, CastedTag2, DimensionCount, true>
    : equals<Geometry2, Geometry1, Tag2, Tag1, CastedTag2, CastedTag1, DimensionCount, false>
{
    template <typename Strategy>
    static inline bool apply(Geometry1 const& g1, Geometry2 const& g2, Strategy const& strategy)
    {
        return equals
            <
                Geometry2, Geometry1,
                Tag2, Tag1,
                CastedTag2, CastedTag1,
                DimensionCount,
                false
            >::apply(g2, g1, strategy);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_strategy
{

template
<
    typename Strategy,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategy>::value
>
struct equals
{
    template <typename Geometry1, typename Geometry2>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        return dispatch::equals
            <
                Geometry1, Geometry2
            >::apply(geometry1, geometry2, strategy);
    }
};

template <typename Strategy>
struct equals<Strategy, false>
{
    template <typename Geometry1, typename Geometry2>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        using strategies::relate::services::strategy_converter;

        return dispatch::equals
            <
                Geometry1, Geometry2
            >::apply(geometry1, geometry2,
                     strategy_converter<Strategy>::get(strategy));
    }
};

template <>
struct equals<default_strategy, false>
{
    template <typename Geometry1, typename Geometry2>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             default_strategy)
    {
        typedef typename strategies::relate::services::default_strategy
            <
                Geometry1,
                Geometry2
            >::type strategy_type;

        return dispatch::equals
            <
                Geometry1, Geometry2
            >::apply(geometry1, geometry2, strategy_type());
    }
};

} // namespace resolve_strategy


namespace resolve_variant {

template <typename Geometry1, typename Geometry2>
struct equals
{
    template <typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        concepts::check_concepts_and_equal_dimensions
            <
                Geometry1 const,
                Geometry2 const
            >();

        return resolve_strategy::equals
            <
                Strategy
            >::apply(geometry1, geometry2, strategy);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Geometry2>
struct equals<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Geometry2>
{
    template <typename Strategy>
    struct visitor: static_visitor<bool>
    {
        Geometry2 const& m_geometry2;
        Strategy const& m_strategy;

        visitor(Geometry2 const& geometry2, Strategy const& strategy)
            : m_geometry2(geometry2)
            , m_strategy(strategy)
        {}

        template <typename Geometry1>
        inline bool operator()(Geometry1 const& geometry1) const
        {
            return equals<Geometry1, Geometry2>
                   ::apply(geometry1, m_geometry2, m_strategy);
        }

    };

    template <typename Strategy>
    static inline bool apply(
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry1,
        Geometry2 const& geometry2,
        Strategy const& strategy
    )
    {
        return boost::apply_visitor(visitor<Strategy>(geometry2, strategy), geometry1);
    }
};

template <typename Geometry1, BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct equals<Geometry1, boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename Strategy>
    struct visitor: static_visitor<bool>
    {
        Geometry1 const& m_geometry1;
        Strategy const& m_strategy;

        visitor(Geometry1 const& geometry1, Strategy const& strategy)
            : m_geometry1(geometry1)
            , m_strategy(strategy)
        {}

        template <typename Geometry2>
        inline bool operator()(Geometry2 const& geometry2) const
        {
            return equals<Geometry1, Geometry2>
                   ::apply(m_geometry1, geometry2, m_strategy);
        }

    };

    template <typename Strategy>
    static inline bool apply(
        Geometry1 const& geometry1,
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry2,
        Strategy const& strategy
    )
    {
        return boost::apply_visitor(visitor<Strategy>(geometry1, strategy), geometry2);
    }
};

template <
    BOOST_VARIANT_ENUM_PARAMS(typename T1),
    BOOST_VARIANT_ENUM_PARAMS(typename T2)
>
struct equals<
    boost::variant<BOOST_VARIANT_ENUM_PARAMS(T1)>,
    boost::variant<BOOST_VARIANT_ENUM_PARAMS(T2)>
>
{
    template <typename Strategy>
    struct visitor: static_visitor<bool>
    {
        Strategy const& m_strategy;

        visitor(Strategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Geometry1, typename Geometry2>
        inline bool operator()(Geometry1 const& geometry1,
                               Geometry2 const& geometry2) const
        {
            return equals<Geometry1, Geometry2>
                   ::apply(geometry1, geometry2, m_strategy);
        }

    };

    template <typename Strategy>
    static inline bool apply(
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T1)> const& geometry1,
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T2)> const& geometry2,
        Strategy const& strategy
    )
    {
        return boost::apply_visitor(visitor<Strategy>(strategy), geometry1, geometry2);
    }
};

} // namespace resolve_variant


/*!
\brief \brief_check{are spatially equal}
\details \details_check12{equals, is spatially equal}. Spatially equal means
    that the same point set is included. A box can therefore be spatially equal
    to a ring or a polygon, or a linestring can be spatially equal to a
    multi-linestring or a segment. This only works theoretically, not all
    combinations are implemented yet.
\ingroup equals
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam Strategy \tparam_strategy{Equals}
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param strategy \param_strategy{equals}
\return \return_check2{are spatially equal}

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/equals.qbk]}
 */
template <typename Geometry1, typename Geometry2, typename Strategy>
inline bool equals(Geometry1 const& geometry1,
                   Geometry2 const& geometry2,
                   Strategy const& strategy)
{
    return resolve_variant::equals
            <
                Geometry1, Geometry2
            >::apply(geometry1, geometry2, strategy);
}


/*!
\brief \brief_check{are spatially equal}
\details \details_check12{equals, is spatially equal}. Spatially equal means
    that the same point set is included. A box can therefore be spatially equal
    to a ring or a polygon, or a linestring can be spatially equal to a
    multi-linestring or a segment. This only works theoretically, not all
    combinations are implemented yet.
\ingroup equals
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\return \return_check2{are spatially equal}

\qbk{[include reference/algorithms/equals.qbk]}
 */
template <typename Geometry1, typename Geometry2>
inline bool equals(Geometry1 const& geometry1, Geometry2 const& geometry2)
{
    return resolve_variant::equals<Geometry1, Geometry2>
                          ::apply(geometry1, geometry2, default_strategy());
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_EQUALS_INTERFACE_HPP


/* interface.hpp
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
*/