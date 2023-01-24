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
PxjeALfSwrlbNzLStGtjahE9SRcRr75uradmV30OOuUeX4+lfXJEughlrTJPjWpjjGb3Rs9qb5lvvL8uuDpcGHD783wJb5m72qjU3VqxWqbMkJazvHnFCk88TBWkBlWQ+nW3TxO511ncwiA0EHiKgcBTdI9biP9U6MBHQqUFyoM/ZbGt/IC11C3JbZYxtc4W6tzO8nd3CTBn9gnNdeL2rPmp5TM0CR5yhzuejkkzVTtJO0kJrlHK9Z3aCuMf7lbjac9llzFTewLvR4+yhHcUesJjqB4PxzhgfHt/B9/+j592Wxuf/JThD04C2q2ba7Obn0hwky0Oaig0btnE1+bwTU6+ZmiGOhzjOzGaiNnyrP0/xH9sEv4ga6DyFJTOTance8L4bBoOhN+ONZPJ6RzWiOcNOGkNpvnTtBz0uBZcg6XBWK5SitUOTKbpETLapdZqFfJ81ED1J4pH1Yn5zN2wC9ybhUwSgkoBlIrNttyM7O5MPk5sdupodqerXeQFLO2Hx/eQhOAJvgw0djDwBEEHT7Bos8BbXgmV16B8uDnFd9eZij7Bagsem9NeYWMQcyS4cKG5owdbc48Iseq5DAb9LWu0B47D4rpsjDlJZklj5D0s7foyfa2x0LPNvdy7wVfiL/OVuN1GQk9ozcpCfbxSJI+VEqSKMsIcopBaGDwBr+7z6zpNWMjXW7bDh3byA8KH9k6o3AdlxwOpnDDt
*/