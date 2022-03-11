// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014, 2015, 2016, 2017, 2019.
// Modifications copyright (c) 2014-2019 Oracle and/or its affiliates.

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

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/relate.hpp>


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

struct equals
{
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        return dispatch::equals
            <
                Geometry1, Geometry2
            >::apply(geometry1, geometry2, strategy);
    }

    template <typename Geometry1, typename Geometry2>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             default_strategy)
    {
        typedef typename strategy::relate::services::default_strategy
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
                ::apply(geometry1, geometry2, strategy);
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