// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2013, 2014, 2017, 2018.
// Modifications copyright (c) 2013-2018 Oracle and/or its affiliates.

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
#include <boost/geometry/strategies/within.hpp>


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

struct within
{
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        concepts::within::check<Geometry1, Geometry2, Strategy>();

        return dispatch::within<Geometry1, Geometry2>::apply(geometry1, geometry2, strategy);
    }

    template <typename Geometry1, typename Geometry2>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             default_strategy)
    {
        typedef typename strategy::within::services::default_strategy
            <
                Geometry1,
                Geometry2
            >::type strategy_type;

        return apply(geometry1, geometry2, strategy_type());
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

        return resolve_strategy::within::apply(geometry1,
                                               geometry2,
                                               strategy);
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