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
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
*/