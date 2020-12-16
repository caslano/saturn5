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
DrbW/9HmbCVcpyU0dE59i/ynPmWuksx6y+Ypsyzl17Utoevr1wOrbwkly7x175RI5jl3dXsul5PiZlnmKBco5djsz9D1XRn3M3zT7b4s475wXDbXbXGpdVvSs3Vb6nNkt3JLPyxufb+9ly0drB793H3RJY0t02DZBssF+/efdw75eBBbvrI1rk82YCtUFvNhp9ZsxXXaTEsJmIslynIxLueOWouaUUrmcctcLfMtPx9b2ICtiswG1rasT39uz3XL7TrdcHzUnjtYA2pP4knmUacttniDWS1xFmvag5+y+SiTmJH5KatfPnQsW5ChzhBlb31WtYFtmLLsYUfm8twdA9aQ/o2MnSxCWVj9P6azRRnKzTKUi1X2wNq0y7z+4sEa0c/hmeNy2BKdDdqrZ1kH1pjaSN4c25MtRdmEbe8e4DrTwNzp5/AJi/qyZSibk354NVuWsqsjprdjyyGzgf1e/fhNtkLnco4csRUrw7iUKJMx0P9Kweg+1xFrtnKDVTqbY06wVdVp/pYasKaWFY5Ys1nSnE1iRmZV1rJei85sNmUSTzIvg9kN5muwQGV39ki7gy1Y2ZPnq4ezhRrqDDNYuMEiDRZt6GeMoZ9xhjoTDJZksGRlOCdSyWxgRQWzz7FlKTu7/cuubPmqzpNHVo1lK1QmewFZscFKlMmcJytVdiYleQJbuTLZX8gqlVV+7vEHW5VhfK7P113OnayucnYop8fgW6cFWALBmlnuduxnbMHKZHxkoWQ2MLk2kkWocl89dFdntihlcq0im6XsvYVf38sWa7B4Q52JBltnsBRDe2nKfl+wdzZbRp22eHkWmM0yL1ZiTZajrPjV6yvY8pTJHklWoEyuD2RFymTfJTtFZgNbs2F0AVu5Kjfoue5b2SpVuaUPXzjPdlOV23Zq/QE2163O1vOP4nl8fXcHa07XXxkfmYcy2V/IvJXJ2YbMB6wFmeSWzI/MBiZjJwtV5WSPJAsDa0n/5niLe3exhaOps02ksqFxjVP5rBEN5oHnCbIYZdIXsjhlMnayBGXLouZfZ0sylEtGU+elVGVybiVLN9SZabBsMhtY6Ner9rAVKLt+5/4YthJDP0uVyRwkK1c2Z8ELFWyVymTfJatSfbn/iu99bK7bbpfzpH+W6y397o4m87rWPNBkXteat8F8DOanDOdLkDIcewiZDWyzZ8BGtnBVbsDb+xPZIpXFLPe6wBZtGHuMMjnX0e9xyjAPCc4Ge6uLJQmsFf0z7iHJymSN0e+pZDawTpPL/mTLUuWSe0/8gS3H0F6eMtyXCpThflZksFOqn56NOr7GVm7oS6UyuT7Q71UGqzH0xZLubJg/K1hr+ucLZ2e9zmZTJvf29LuXMqzTjqbmhC+aWg+BYF4WSwrurcHKcH6GKsM6w8hsYHKvRhalykk8yWapctv2VLzBlqDKne3yaQFbkjLHXs7zGqwN/XPHB/8+z5YK1pb+jax3svT/Y7Jfg7Wjf4Mxy1aG6z1XmaxNsnxlcpYiK1QmZ1OyYmWYoxJlb5au68BWquyluSO/YCs31FlpsCpluM/XGMpZXnA2nEtWg9nAdJ1eypzWijKntaLsRMH0wfIsFsybfuJeFwzWHs8oZKFoqlyYMtxDwg0WqQznfLQy3LNilElcyOKU4R6ZoExyS5ZEZgNr1SD4CFuaKif7GVmGsmNPez/ClqXskQ3FMoYcNDy/kOUpe7vBAxKXAmUvPrfJha1Imaw/slPKZL+m/50F6yB5r7UyNMl7rVWgSaxr7YrBqtFkTtTaTTQ5C9ea64vONvHI6FNs7mgyJ2rNA0096/JGk3NrrfmgyTmy1vzQZC7VWpDBQtBkTtTaMDCdhzHKPu0=
*/