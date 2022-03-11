// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2014, 2017.
// Modifications copyright (c) 2014-2017 Oracle and/or its affiliates.

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

struct crosses
{
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        concepts::check<Geometry1 const>();
        concepts::check<Geometry2 const>();

        return dispatch::crosses<Geometry1, Geometry2>::apply(geometry1, geometry2, strategy);
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

        return apply(geometry1, geometry2, strategy_type());
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
            return resolve_strategy::crosses::apply(geometry1, geometry2, strategy);
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