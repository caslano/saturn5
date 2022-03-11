// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2015 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013, 2014, 2015, 2017.
// Modifications copyright (c) 2013-2017, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_TOUCHES_INTERFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_TOUCHES_INTERFACE_HPP


#include <deque>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/core/reverse_dispatch.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/relate.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch {

// TODO: Since CastedTags are used is Reverse needed?

template
<
    typename Geometry1,
    typename Geometry2,
    typename Tag1 = typename tag<Geometry1>::type,
    typename Tag2 = typename tag<Geometry2>::type,
    typename CastedTag1 = typename tag_cast<Tag1, pointlike_tag, linear_tag, areal_tag>::type,
    typename CastedTag2 = typename tag_cast<Tag2, pointlike_tag, linear_tag, areal_tag>::type,
    bool Reverse = reverse_dispatch<Geometry1, Geometry2>::type::value
>
struct touches
    : not_implemented<Tag1, Tag2>
{};

// If reversal is needed, perform it
template
<
    typename Geometry1, typename Geometry2,
    typename Tag1, typename Tag2,
    typename CastedTag1, typename CastedTag2
>
struct touches<Geometry1, Geometry2, Tag1, Tag2, CastedTag1, CastedTag2, true>
    : touches<Geometry2, Geometry1, Tag2, Tag1, CastedTag2, CastedTag1, false>
{
    template <typename Strategy>
    static inline bool apply(Geometry1 const& g1, Geometry2 const& g2, Strategy const& strategy)
    {
        return touches<Geometry2, Geometry1>::apply(g2, g1, strategy);
    }
};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_strategy
{

struct touches
{
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        return dispatch::touches
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

        return dispatch::touches
            <
                Geometry1, Geometry2
            >::apply(geometry1, geometry2, strategy_type());
    }
};

} // namespace resolve_strategy


namespace resolve_variant {

template <typename Geometry1, typename Geometry2>
struct touches
{
    template <typename Strategy>
    static bool apply(Geometry1 const& geometry1, Geometry2 const& geometry2, Strategy const& strategy)
    {
        concepts::check<Geometry1 const>();
        concepts::check<Geometry2 const>();

        return resolve_strategy::touches::apply(geometry1, geometry2, strategy);
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Geometry2>
struct touches<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Geometry2>
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
            return touches<Geometry1, Geometry2>::apply(geometry1, m_geometry2, m_strategy);
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
struct touches<Geometry1, boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
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
            return touches<Geometry1, Geometry2>::apply(m_geometry1, geometry2, m_strategy);
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

template <BOOST_VARIANT_ENUM_PARAMS(typename T1),
          BOOST_VARIANT_ENUM_PARAMS(typename T2)>
struct touches<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T1)>,
               boost::variant<BOOST_VARIANT_ENUM_PARAMS(T2)> >
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
            return touches<Geometry1, Geometry2>::apply(geometry1, geometry2, m_strategy);
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

template <typename Geometry>
struct self_touches;

template <BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct self_touches<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    struct visitor: boost::static_visitor<bool>
    {
        template <typename Geometry>
        bool operator()(Geometry const& geometry) const
        {
            return self_touches<Geometry>::apply(geometry);
        }
    };

    static inline bool
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry)
    {
        return boost::apply_visitor(visitor(), geometry);
    }
};

} // namespace resolve_variant


/*!
\brief \brief_check{has at least one touching point (self-tangency)}
\note This function can be called for one geometry (self-tangency) and
    also for two geometries (touch)
\ingroup touches
\tparam Geometry \tparam_geometry
\param geometry \param_geometry
\return \return_check{is self-touching}

\qbk{distinguish,one geometry}
\qbk{[def __one_parameter__]}
\qbk{[include reference/algorithms/touches.qbk]}
\qbk{
[heading Examples]
[touches_one_geometry]
[touches_one_geometry_output]
}
*/
template <typename Geometry>
inline bool touches(Geometry const& geometry)
{
    return resolve_variant::self_touches<Geometry>::apply(geometry);
}


/*!
\brief \brief_check2{have at least one touching point (tangent - non overlapping)}
\ingroup touches
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\return \return_check2{touch each other}

\qbk{distinguish,two geometries}
\qbk{[include reference/algorithms/touches.qbk]}
\qbk{
[heading Examples]
[touches_two_geometries]
[touches_two_geometries_output]
}
 */
template <typename Geometry1, typename Geometry2>
inline bool touches(Geometry1 const& geometry1, Geometry2 const& geometry2)
{
    return resolve_variant::touches
        <
            Geometry1, Geometry2
        >::apply(geometry1, geometry2, default_strategy());
}

/*!
\brief \brief_check2{have at least one touching point (tangent - non overlapping)}
\ingroup touches
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam Strategy \tparam_strategy{Touches}
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param strategy \param_strategy{touches}
\return \return_check2{touch each other}

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/touches.qbk]}
 */
template <typename Geometry1, typename Geometry2, typename Strategy>
inline bool touches(Geometry1 const& geometry1,
                    Geometry2 const& geometry2,
                    Strategy const& strategy)
{
    return resolve_variant::touches
        <
            Geometry1, Geometry2
        >::apply(geometry1, geometry2, strategy);
}


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_TOUCHES_INTERFACE_HPP

/* interface.hpp
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
*/