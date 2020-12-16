// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2017.
// Modifications copyright (c) 2013-2017, Oracle and/or its affiliates.

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

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/detail/relate/interface.hpp>
#include <boost/geometry/algorithms/dispatch/disjoint.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/strategies/disjoint.hpp>


namespace boost { namespace geometry
{

namespace resolve_strategy
{

struct disjoint
{
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        return dispatch::disjoint
                <
                    Geometry1, Geometry2
                >::apply(geometry1, geometry2, strategy);
    }

    template <typename Geometry1, typename Geometry2>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             default_strategy)
    {
        typedef typename strategy::disjoint::services::default_strategy
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


namespace resolve_variant {

template <typename Geometry1, typename Geometry2>
struct disjoint
{
    template <typename Strategy>
    static inline bool apply(Geometry1 const& geometry1, Geometry2 const& geometry2, Strategy const& strategy)
    {
        concepts::check_concepts_and_equal_dimensions
            <
                Geometry1 const,
                Geometry2 const
            >();

        return resolve_strategy::disjoint::apply(geometry1, geometry2, strategy);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Geometry2>
struct disjoint<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Geometry2>
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
            return disjoint<Geometry1, Geometry2>::apply(geometry1, m_geometry2, m_strategy);
        }
    };

    template <typename Strategy>
    static inline bool apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Strategy>(geometry2, strategy), geometry1);
    }
};

template <typename Geometry1, BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct disjoint<Geometry1, boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
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
            return disjoint<Geometry1, Geometry2>::apply(m_geometry1, geometry2, m_strategy);
        }
    };

    template <typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry2,
                             Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Strategy>(geometry1, strategy), geometry2);
    }
};

template
<
    BOOST_VARIANT_ENUM_PARAMS(typename T1),
    BOOST_VARIANT_ENUM_PARAMS(typename T2)
>
struct disjoint
    <
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T1)>,
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T2)>
    >
{
    template <typename Strategy>
    struct visitor: boost::static_visitor<bool>
    {
        Strategy const& m_strategy;

        visitor(Strategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Geometry1, typename Geometry2>
        bool operator()(Geometry1 const& geometry1,
                        Geometry2 const& geometry2) const
        {
            return disjoint<Geometry1, Geometry2>::apply(geometry1, geometry2, m_strategy);
        }
    };

    template <typename Strategy>
    static inline bool apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T1)> const& geometry1,
                             boost::variant<BOOST_VARIANT_ENUM_PARAMS(T2)> const& geometry2,
                             Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Strategy>(strategy), geometry1, geometry2);
    }
};

} // namespace resolve_variant


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
    return resolve_variant::disjoint
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
    return resolve_variant::disjoint
            <
                Geometry1, Geometry2
            >::apply(geometry1, geometry2, default_strategy());
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_INTERFACE_HPP

/* interface.hpp
TOFQkXmeNtuwZdyIEJmHzLaxSIOhidKEJJWkNImQUGmikUqkMoUoitJcOr9v2znOuc58nXP+Oq7LZdvf+tZ632e4n/u533etdXnG54kYLPR3Yq3lP4dV/1T+J2K192mx2icj/vv/w3XS0zH7L3D/1HX+9Fnf9POO+PMRuGaPjH0n/U7L0Xz/wbXnBL4Vy3US3+TeqXuUEjGfeLb1sN8ffda3zan7jAdk+O30T8zj1LufB5421lz/RsyX/fMxdE605Bn3Aqdfd3izxGNa/nS9wadf79/QGX7HnYV/sW9miPMWCH/am5o2sF/PxBNIEtd+IP1+2mxRYkzDGp28w31Umo8xG5vMB41207/XFiYWzOrZTTSqRDoNKnH+yX8z7pM6/YbaUyfPuOH2b3/eqGHpv3O1Ru2bNk7OuA8g4/kIw43vb5/u5HMOYvaojTjNjrF/dUbpJv6nRnZsw79gu/SN+yc5X7/fbzQe/b8xo4j5axdv5E84ZdtR/8C2szNsO/qftu1fvei/Zua/PfL0uFj8L9h/XMLVPdP+p+Hbs/Ofx++Yf2DjURk2HvtP2zhjVv9WCKeP7tj6f8GGf8Oj/00rtvsHMXDKtuP/gW1vzLDthH/atn9jtv+Mdf/+qI8t+Bds/mce/m/bOiMmfrfplf8k3l71T9v0z2bzz9ryVB5l3Idx6r6ZyRnX3VbYvTCn6huu0KRnkxYXd+h48e/3XGT87pLUjj1bte3QIf1NDxmfRRmftU1N7dSuY2L3apOLTz1HLf2zxPtJ26QkvtkkKf0doBnPUDj9e02Teya1ShyQ/lnmk5+ltGrVtHlSq5B+L0SWjHsKpjTKGGH6FvWMLcvpfvvL3ybmfJLXTKx86p1Y6Tbw/wwbZNw3k/FZxn0zp/5/6h6m6KS9Kp12706Pv3Mvl6kmJSceId0spXnP9FezJh4i3Tw147aNTv/wKEM/EZ3GK//iOfreHTxoaD90uZ/7a4eOCKfeR37yPfcZN8w6PuP3ORLvtz/1+9Pu98x4V1P6JvnEYwNG/emzXKd/1uHP9/nlC03cuJ+437FDv/RXVHiCZK8xQ9ISoxo+Ju20d1Uk9zv5DvkEUUt/S4xN0f1GDxw+pO+fvUPx1HEdh6f1GpI4+K8eVy60cop2YnvQ+JPbyv70WaXf3xudNOT3W0UTRjs1llq/34d58qWcf/X8jX5/t01S//6Jp5BMSH+J8Z/m3eL3zxMvx083zJ9s3Co06ZCcYeHTn/3f5s/fZ5DxfsWmfQelpd8+feraXQJbjhnloiffzZRxjt/fyf/7y6PSp336ZwP/9Fn6HSenfzYiNB+T2NzerMnAfn2u+P19Ihn33J5mu/G/H5dMDUhsev+LQ08/55Tfj/39mJMjOvX5jL/8/OSoTtnw1pOf/9l9GTPk9B2Jd9SefJxxwgjp+z7BUnTDadi48K/lV3KKu00Tr/HKeNX73z8k471pp7/34eRQMv6fuMOxlxgcPuA0v2f6/XcZm1szfn/6vrdT/dlNp2so/0E8+P+f///5/5////n/n///+f+fP//TbIHaXT4WSl8ahY+muRf2iSh8/ksU6oyNhSM3hjB3aTxceG8IeWbGwp7B8XD+1Z4N+ng8LDsQwv2fR2HKiCg0mIDDTY6F5leHMDspCt86rk2DeFieeOtTu3hY3z4WYr/FwntDotDymRD6t7cn78ZYOHQoFq7WBnx4WywMHBnCNY2i8EZqCDVujYcC1e0fKYDffhLCOeWjcGhoFB55MRbubRkLRWZbG/w0hGkrY+G8KiEMOhCFDy6OwsSfYuHoE+5/7hCF5Xui0KqR+5jnxkPyOd4ZWo7C/E4s7Ex1jS1RONwiFgp8Ews=
*/