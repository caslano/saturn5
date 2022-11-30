// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2014-2021.
// Modifications copyright (c) 2014-2021 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_CROSSES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_CROSSES_HPP

#include <cstddef>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/relate.hpp>
#include <boost/geometry/algorithms/detail/relate/relate_impl.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/relate/cartesian.hpp>
#include <boost/geometry/strategies/relate/geographic.hpp>
#include <boost/geometry/strategies/relate/spherical.hpp>


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
struct crosses
    : detail::relate::relate_impl
        <
            detail::de9im::static_mask_crosses_type,
            Geometry1,
            Geometry2
        >
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
struct crosses
{
    template <typename Geometry1, typename Geometry2>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        concepts::check<Geometry1 const>();
        concepts::check<Geometry2 const>();

        return dispatch::crosses
            <
                Geometry1, Geometry2
            >::apply(geometry1, geometry2, strategy);
    }
};

template <typename Strategy>
struct crosses<Strategy, false>
{
    template <typename Geometry1, typename Geometry2>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        //using strategies::crosses::services::strategy_converter;
        using strategies::relate::services::strategy_converter;
        return crosses
            <
                decltype(strategy_converter<Strategy>::get(strategy))
            >::apply(geometry1, geometry2,
                     strategy_converter<Strategy>::get(strategy));
    }
};

template <>
struct crosses<default_strategy, false>
{
    template <typename Geometry1, typename Geometry2>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             default_strategy)
    {
        //typedef typename strategies::crosses::services::default_strategy
        typedef typename strategies::relate::services::default_strategy
            <
                Geometry1,
                Geometry2
            >::type strategy_type;

        return crosses
            <
                strategy_type
            >::apply(geometry1, geometry2, strategy_type());
    }
};

} // namespace resolve_strategy


namespace resolve_variant
{
    template <typename Geometry1, typename Geometry2>
    struct crosses
    {
        template <typename Strategy>
        static inline bool apply(Geometry1 const& geometry1,
                                 Geometry2 const& geometry2,
                                 Strategy const& strategy)
        {
            return resolve_strategy::crosses
                <
                    Strategy
                >::apply(geometry1, geometry2, strategy);
        }
    };
    
    
    template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Geometry2>
    struct crosses<variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Geometry2>
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
            result_type operator()(Geometry1 const& geometry1) const
            {
                return crosses
                    <
                        Geometry1,
                        Geometry2
                    >::apply(geometry1, m_geometry2, m_strategy);
            }
        };
        
        template <typename Strategy>
        static inline bool apply(variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry1,
                                 Geometry2 const& geometry2,
                                 Strategy const& strategy)
        {
            return boost::apply_visitor(visitor<Strategy>(geometry2, strategy), geometry1);
        }
    };
    
    
    template <typename Geometry1, BOOST_VARIANT_ENUM_PARAMS(typename T)>
    struct crosses<Geometry1, variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
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
            result_type operator()(Geometry2 const& geometry2) const
            {
                return crosses
                    <
                        Geometry1,
                        Geometry2
                    >::apply(m_geometry1, geometry2, m_strategy);
            }
        };
        
        template <typename Strategy>
        static inline bool apply(Geometry1 const& geometry1,
                                 variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry2,
                                 Strategy const& strategy)
        {
            return boost::apply_visitor(visitor<Strategy>(geometry1, strategy), geometry2);
        }
    };
    
    
    template <BOOST_VARIANT_ENUM_PARAMS(typename T1), BOOST_VARIANT_ENUM_PARAMS(typename T2)>
    struct crosses<variant<BOOST_VARIANT_ENUM_PARAMS(T1)>, variant<BOOST_VARIANT_ENUM_PARAMS(T2)> >
    {
        template <typename Strategy>
        struct visitor: static_visitor<bool>
        {
            Strategy const& m_strategy;

            visitor(Strategy const& strategy)
                : m_strategy(strategy)
            {}

            template <typename Geometry1, typename Geometry2>
            result_type operator()(Geometry1 const& geometry1,
                                   Geometry2 const& geometry2) const
            {
                return crosses
                    <
                        Geometry1,
                        Geometry2
                    >::apply(geometry1, geometry2, m_strategy);
            }
        };
        
        template <typename Strategy>
        static inline bool apply(variant<BOOST_VARIANT_ENUM_PARAMS(T1)> const& geometry1,
                                 variant<BOOST_VARIANT_ENUM_PARAMS(T2)> const& geometry2,
                                  Strategy const& strategy)
        {
            return boost::apply_visitor(visitor<Strategy>(strategy), geometry1, geometry2);
        }
    };
    
} // namespace resolve_variant
    
    
/*!
\brief \brief_check2{crosses}
\ingroup crosses
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam Strategy \tparam_strategy{Crosses}
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param strategy \param_strategy{crosses}
\return \return_check2{crosses}

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/crosses.qbk]}
*/
template <typename Geometry1, typename Geometry2, typename Strategy>
inline bool crosses(Geometry1 const& geometry1,
                    Geometry2 const& geometry2,
                    Strategy const& strategy)
{
    return resolve_variant::crosses
            <
                Geometry1, Geometry2
            >::apply(geometry1, geometry2, strategy);
}

/*!
\brief \brief_check2{crosses}
\ingroup crosses
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\return \return_check2{crosses}

\qbk{[include reference/algorithms/crosses.qbk]}
\qbk{
[heading Examples]
[crosses]
[crosses_output]
}
*/
template <typename Geometry1, typename Geometry2>
inline bool crosses(Geometry1 const& geometry1, Geometry2 const& geometry2)
{
    return resolve_variant::crosses
            <
                Geometry1, Geometry2
            >::apply(geometry1, geometry2, default_strategy());
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_CROSSES_HPP

/* crosses.hpp
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
*/