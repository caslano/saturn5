// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2013-2021.
// Modifications copyright (c) 2013-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_WITHIN_INTERFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_WITHIN_INTERFACE_HPP


#include <boost/concept_check.hpp>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tag_cast.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/strategies/concepts/within_concept.hpp>
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
    typename Tag2 = typename tag<Geometry2>::type
>
struct within
    : not_implemented<Tag1, Tag2>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_strategy
{

template
<
    typename Strategy,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategy>::value
>
struct within
{
    template <typename Geometry1, typename Geometry2>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        concepts::within::check<Geometry1, Geometry2, Strategy>();

        return dispatch::within
            <
                Geometry1, Geometry2
            >::apply(geometry1, geometry2, strategy);
    }
};

template <typename Strategy>
struct within<Strategy, false>
{
    template <typename Geometry1, typename Geometry2>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        using strategies::relate::services::strategy_converter;

        return within
            <
                decltype(strategy_converter<Strategy>::get(strategy))
            >::apply(geometry1, geometry2,
                     strategy_converter<Strategy>::get(strategy));
    }
};

template <>
struct within<default_strategy, false>
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

        return within
            <
                strategy_type
            >::apply(geometry1, geometry2, strategy_type());
    }
};

} // namespace resolve_strategy


namespace resolve_variant
{

template <typename Geometry1, typename Geometry2>
struct within
{
    template <typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        concepts::check<Geometry1 const>();
        concepts::check<Geometry2 const>();
        assert_dimension_equal<Geometry1, Geometry2>();

        return resolve_strategy::within
            <
                Strategy
            >::apply(geometry1, geometry2, strategy);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Geometry2>
struct within<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Geometry2>
{
    template <typename Strategy>
    struct visitor: boost::static_visitor<bool>
    {
        Geometry2 const& m_geometry2;
        Strategy const& m_strategy;

        visitor(Geometry2 const& geometry2, Strategy const& strategy)
            : m_geometry2(geometry2)
            , m_strategy(strategy)
        {}

        template <typename Geometry1>
        bool operator()(Geometry1 const& geometry1) const
        {
            return within<Geometry1, Geometry2>::apply(geometry1,
                                                       m_geometry2,
                                                       m_strategy);
        }
    };

    template <typename Strategy>
    static inline bool
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry1,
          Geometry2 const& geometry2,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Strategy>(geometry2, strategy),
                                    geometry1);
    }
};

template <typename Geometry1, BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct within<Geometry1, boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename Strategy>
    struct visitor: boost::static_visitor<bool>
    {
        Geometry1 const& m_geometry1;
        Strategy const& m_strategy;

        visitor(Geometry1 const& geometry1, Strategy const& strategy)
            : m_geometry1(geometry1)
            , m_strategy(strategy)
        {}

        template <typename Geometry2>
        bool operator()(Geometry2 const& geometry2) const
        {
            return within<Geometry1, Geometry2>::apply(m_geometry1,
                                                       geometry2,
                                                       m_strategy);
        }
    };

    template <typename Strategy>
    static inline bool
    apply(Geometry1 const& geometry1,
          boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry2,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Strategy>(geometry1, strategy),
                                    geometry2
        );
    }
};

template <
    BOOST_VARIANT_ENUM_PARAMS(typename T1),
    BOOST_VARIANT_ENUM_PARAMS(typename T2)
>
struct within<
    boost::variant<BOOST_VARIANT_ENUM_PARAMS(T1)>,
    boost::variant<BOOST_VARIANT_ENUM_PARAMS(T2)>
>
{
    template <typename Strategy>
    struct visitor: boost::static_visitor<bool>
    {
        Strategy const& m_strategy;

        visitor(Strategy const& strategy): m_strategy(strategy) {}

        template <typename Geometry1, typename Geometry2>
        bool operator()(Geometry1 const& geometry1,
                        Geometry2 const& geometry2) const
        {
            return within<Geometry1, Geometry2>::apply(geometry1,
                                                       geometry2,
                                                       m_strategy);
        }
    };

    template <typename Strategy>
    static inline bool
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T1)> const& geometry1,
          boost::variant<BOOST_VARIANT_ENUM_PARAMS(T2)> const& geometry2,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Strategy>(strategy),
                                    geometry1,
                                    geometry2);
    }
};

}


/*!
\brief \brief_check12{is completely inside}
\ingroup within
\details \details_check12{within, is completely inside}.
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\param geometry1 \param_geometry which might be within the second geometry
\param geometry2 \param_geometry which might contain the first geometry
\return true if geometry1 is completely contained within geometry2,
    else false
\note The default strategy is used for within detection


\qbk{[include reference/algorithms/within.qbk]}

\qbk{
[heading Example]
[within]
[within_output]
}
 */
template<typename Geometry1, typename Geometry2>
inline bool within(Geometry1 const& geometry1, Geometry2 const& geometry2)
{
    return resolve_variant::within
        <
            Geometry1,
            Geometry2
        >::apply(geometry1, geometry2, default_strategy());
}

/*!
\brief \brief_check12{is completely inside} \brief_strategy
\ingroup within
\details \details_check12{within, is completely inside}, \brief_strategy. \details_strategy_reasons
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\param geometry1 \param_geometry which might be within the second geometry
\param geometry2 \param_geometry which might contain the first geometry
\param strategy strategy to be used
\return true if geometry1 is completely contained within geometry2,
    else false

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/within.qbk]}
\qbk{
[heading Available Strategies]
\* [link geometry.reference.strategies.strategy_within_winding Winding (coordinate system agnostic)]
\* [link geometry.reference.strategies.strategy_within_franklin Franklin (cartesian)]
\* [link geometry.reference.strategies.strategy_within_crossings_multiply Crossings Multiply (cartesian)]

[heading Example]
[within_strategy]
[within_strategy_output]

}
*/
template<typename Geometry1, typename Geometry2, typename Strategy>
inline bool within(Geometry1 const& geometry1,
                   Geometry2 const& geometry2,
                   Strategy const& strategy)
{
    return resolve_variant::within
        <
            Geometry1,
            Geometry2
        >::apply(geometry1, geometry2, strategy);
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_WITHIN_INTERFACE_HPP

/* interface.hpp
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
*/