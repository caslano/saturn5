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

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_COVERED_BY_INTERFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_COVERED_BY_INTERFACE_HPP


#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/detail/within/interface.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/strategies/cartesian/point_in_box.hpp>
#include <boost/geometry/strategies/cartesian/box_in_box.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>


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
struct covered_by
    : not_implemented<Tag1, Tag2>
{};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_strategy {

struct covered_by
{
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        concepts::within::check<Geometry1, Geometry2, Strategy>();
        concepts::check<Geometry1 const>();
        concepts::check<Geometry2 const>();
        assert_dimension_equal<Geometry1, Geometry2>();

        return dispatch::covered_by<Geometry1, Geometry2>::apply(geometry1,
                                                                 geometry2,
                                                                 strategy);
    }

    template <typename Geometry1, typename Geometry2>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             default_strategy)
    {
        typedef typename strategy::covered_by::services::default_strategy
            <
                Geometry1,
                Geometry2
            >::type strategy_type;

        return covered_by::apply(geometry1, geometry2, strategy_type());
    }
};

} // namespace resolve_strategy


namespace resolve_variant {

template <typename Geometry1, typename Geometry2>
struct covered_by
{
    template <typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        return resolve_strategy::covered_by
                               ::apply(geometry1, geometry2, strategy);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Geometry2>
struct covered_by<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Geometry2>
{
    template <typename Strategy>
    struct visitor: boost::static_visitor<bool>
    {
        Geometry2 const& m_geometry2;
        Strategy const& m_strategy;

        visitor(Geometry2 const& geometry2, Strategy const& strategy)
        : m_geometry2(geometry2), m_strategy(strategy) {}

        template <typename Geometry1>
        bool operator()(Geometry1 const& geometry1) const
        {
            return covered_by<Geometry1, Geometry2>
                   ::apply(geometry1, m_geometry2, m_strategy);
        }
    };

    template <typename Strategy>
    static inline bool
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry1,
          Geometry2 const& geometry2,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Strategy>(geometry2, strategy), geometry1);
    }
};

template <typename Geometry1, BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct covered_by<Geometry1, boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename Strategy>
    struct visitor: boost::static_visitor<bool>
    {
        Geometry1 const& m_geometry1;
        Strategy const& m_strategy;

        visitor(Geometry1 const& geometry1, Strategy const& strategy)
        : m_geometry1(geometry1), m_strategy(strategy) {}

        template <typename Geometry2>
        bool operator()(Geometry2 const& geometry2) const
        {
            return covered_by<Geometry1, Geometry2>
                   ::apply(m_geometry1, geometry2, m_strategy);
        }
    };

    template <typename Strategy>
    static inline bool
    apply(Geometry1 const& geometry1,
          boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry2,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Strategy>(geometry1, strategy), geometry2);
    }
};

template <
    BOOST_VARIANT_ENUM_PARAMS(typename T1),
    BOOST_VARIANT_ENUM_PARAMS(typename T2)
>
struct covered_by<
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
            return covered_by<Geometry1, Geometry2>
                   ::apply(geometry1, geometry2, m_strategy);
        }
    };

    template <typename Strategy>
    static inline bool
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T1)> const& geometry1,
          boost::variant<BOOST_VARIANT_ENUM_PARAMS(T2)> const& geometry2,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Strategy>(strategy), geometry1, geometry2);
    }
};

} // namespace resolve_variant


/*!
\brief \brief_check12{is inside or on border}
\ingroup covered_by
\details \details_check12{covered_by, is inside or on border}.
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\param geometry1 \param_geometry which might be inside or on the border of the second geometry
\param geometry2 \param_geometry which might cover the first geometry
\return true if geometry1 is inside of or on the border of geometry2,
    else false
\note The default strategy is used for covered_by detection

\qbk{[include reference/algorithms/covered_by.qbk]}
\qbk{
[heading Examples]
[covered_by]
[covered_by_output]
}
 */
template<typename Geometry1, typename Geometry2>
inline bool covered_by(Geometry1 const& geometry1, Geometry2 const& geometry2)
{
    return resolve_variant::covered_by<Geometry1, Geometry2>
                          ::apply(geometry1, geometry2, default_strategy());
}

/*!
\brief \brief_check12{is inside or on border} \brief_strategy
\ingroup covered_by
\details \details_check12{covered_by, is inside or on border}, \brief_strategy. \details_strategy_reasons
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\param geometry1 \param_geometry which might be inside or on the border of the second geometry
\param geometry2 \param_geometry which might cover the first geometry
\param strategy strategy to be used
\return true if geometry1 is inside of or on the border of geometry2,
    else false

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/covered_by.qbk]}

*/
template<typename Geometry1, typename Geometry2, typename Strategy>
inline bool covered_by(Geometry1 const& geometry1, Geometry2 const& geometry2,
        Strategy const& strategy)
{
    return resolve_variant::covered_by<Geometry1, Geometry2>
                          ::apply(geometry1, geometry2, strategy);
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_COVERED_BY_INTERFACE_HPP

/* interface.hpp
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
*/