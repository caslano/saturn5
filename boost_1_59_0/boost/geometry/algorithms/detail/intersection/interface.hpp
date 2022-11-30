// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014-2020.
// Modifications copyright (c) 2014-2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTION_INTERFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTION_INTERFACE_HPP


#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/detail/overlay/intersection_insert.hpp>
#include <boost/geometry/algorithms/detail/tupled_output.hpp>
#include <boost/geometry/policies/robustness/get_rescale_policy.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/relate/services.hpp>
#include <boost/geometry/util/range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

// By default, all is forwarded to the intersection_insert-dispatcher
template
<
    typename Geometry1, typename Geometry2,
    typename Tag1 = typename geometry::tag<Geometry1>::type,
    typename Tag2 = typename geometry::tag<Geometry2>::type,
    bool Reverse = reverse_dispatch<Geometry1, Geometry2>::type::value
>
struct intersection
{
    template <typename RobustPolicy, typename GeometryOut, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
            Geometry2 const& geometry2,
            RobustPolicy const& robust_policy,
            GeometryOut& geometry_out,
            Strategy const& strategy)
    {
        typedef typename geometry::detail::output_geometry_value
            <
                GeometryOut
            >::type SingleOut;

        intersection_insert
            <
                Geometry1, Geometry2, SingleOut,
                overlay_intersection
            >::apply(geometry1, geometry2, robust_policy,
                     geometry::detail::output_geometry_back_inserter(geometry_out),
                     strategy);

        return true;
    }

};


// If reversal is needed, perform it
template
<
    typename Geometry1, typename Geometry2,
    typename Tag1, typename Tag2
>
struct intersection
<
    Geometry1, Geometry2,
    Tag1, Tag2,
    true
>
    : intersection<Geometry2, Geometry1, Tag2, Tag1, false>
{
    template <typename RobustPolicy, typename GeometryOut, typename Strategy>
    static inline bool apply(
        Geometry1 const& g1,
        Geometry2 const& g2,
        RobustPolicy const& robust_policy,
        GeometryOut& out,
        Strategy const& strategy)
    {
        return intersection
            <
                Geometry2, Geometry1,
                Tag2, Tag1,
                false
            >::apply(g2, g1, robust_policy, out, strategy);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


namespace resolve_strategy {

template
<
    typename Strategy,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategy>::value
>
struct intersection
{
    template
    <
        typename Geometry1,
        typename Geometry2,
        typename GeometryOut
    >
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             GeometryOut & geometry_out,
                             Strategy const& strategy)
    {
        typedef typename geometry::rescale_overlay_policy_type
            <
                Geometry1,
                Geometry2,
                typename Strategy::cs_tag
            >::type rescale_policy_type;
        
        rescale_policy_type robust_policy
            = geometry::get_rescale_policy<rescale_policy_type>(
                    geometry1, geometry2, strategy);

        return dispatch::intersection
            <
                Geometry1,
                Geometry2
            >::apply(geometry1, geometry2, robust_policy, geometry_out,
                     strategy);
    }
};

template <typename Strategy>
struct intersection<Strategy, false>
{
    template
    <
        typename Geometry1,
        typename Geometry2,
        typename GeometryOut
    >
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             GeometryOut & geometry_out,
                             Strategy const& strategy)
    {
        using strategies::relate::services::strategy_converter;
        return intersection
            <
                decltype(strategy_converter<Strategy>::get(strategy))
            >::apply(geometry1, geometry2, geometry_out,
                     strategy_converter<Strategy>::get(strategy));
    }
};

template <>
struct intersection<default_strategy, false>
{
    template
    <
        typename Geometry1,
        typename Geometry2,
        typename GeometryOut
    >
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             GeometryOut & geometry_out,
                             default_strategy)
    {
        typedef typename strategies::relate::services::default_strategy
            <
                Geometry1, Geometry2
            >::type strategy_type;

        return intersection
            <
                strategy_type
            >::apply(geometry1, geometry2, geometry_out, strategy_type());
    }
};

} // resolve_strategy


namespace resolve_variant
{
    
template <typename Geometry1, typename Geometry2>
struct intersection
{
    template <typename GeometryOut, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             GeometryOut& geometry_out,
                             Strategy const& strategy)
    {
        concepts::check<Geometry1 const>();
        concepts::check<Geometry2 const>();
        
        return resolve_strategy::intersection
            <
                Strategy
            >::apply(geometry1, geometry2, geometry_out, strategy);
    }
};


template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Geometry2>
struct intersection<variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Geometry2>
{
    template <typename GeometryOut, typename Strategy>
    struct visitor: static_visitor<bool>
    {
        Geometry2 const& m_geometry2;
        GeometryOut& m_geometry_out;
        Strategy const& m_strategy;
        
        visitor(Geometry2 const& geometry2,
                GeometryOut& geometry_out,
                Strategy const& strategy)
            : m_geometry2(geometry2)
            , m_geometry_out(geometry_out)
            , m_strategy(strategy)
        {}
        
        template <typename Geometry1>
        bool operator()(Geometry1 const& geometry1) const
        {
            return intersection
                <
                    Geometry1,
                    Geometry2
                >::apply(geometry1, m_geometry2, m_geometry_out, m_strategy);
        }
    };
    
    template <typename GeometryOut, typename Strategy>
    static inline bool
    apply(variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry1,
          Geometry2 const& geometry2,
          GeometryOut& geometry_out,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<GeometryOut, Strategy>(geometry2,
                                                                   geometry_out,
                                                                   strategy),
                                    geometry1);
    }
};


template <typename Geometry1, BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct intersection<Geometry1, variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename GeometryOut, typename Strategy>
    struct visitor: static_visitor<bool>
    {
        Geometry1 const& m_geometry1;
        GeometryOut& m_geometry_out;
        Strategy const& m_strategy;
        
        visitor(Geometry1 const& geometry1,
                GeometryOut& geometry_out,
                Strategy const& strategy)
            : m_geometry1(geometry1)
            , m_geometry_out(geometry_out)
            , m_strategy(strategy)
        {}
        
        template <typename Geometry2>
        bool operator()(Geometry2 const& geometry2) const
        {
            return intersection
                <
                    Geometry1,
                    Geometry2
                >::apply(m_geometry1, geometry2, m_geometry_out, m_strategy);
        }
    };
    
    template <typename GeometryOut, typename Strategy>
    static inline bool
    apply(Geometry1 const& geometry1,
          variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry2,
          GeometryOut& geometry_out,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<GeometryOut, Strategy>(geometry1,
                                                                   geometry_out,
                                                                   strategy),
                                    geometry2);
    }
};


template <BOOST_VARIANT_ENUM_PARAMS(typename T1), BOOST_VARIANT_ENUM_PARAMS(typename T2)>
struct intersection<variant<BOOST_VARIANT_ENUM_PARAMS(T1)>, variant<BOOST_VARIANT_ENUM_PARAMS(T2)> >
{
    template <typename GeometryOut, typename Strategy>
    struct visitor: static_visitor<bool>
    {
        GeometryOut& m_geometry_out;
        Strategy const& m_strategy;
        
        visitor(GeometryOut& geometry_out, Strategy const& strategy)
            : m_geometry_out(geometry_out)
            , m_strategy(strategy)
        {}
        
        template <typename Geometry1, typename Geometry2>
        bool operator()(Geometry1 const& geometry1,
                        Geometry2 const& geometry2) const
        {
            return intersection
                <
                    Geometry1,
                    Geometry2
                >::apply(geometry1, geometry2, m_geometry_out, m_strategy);
        }
    };
    
    template <typename GeometryOut, typename Strategy>
    static inline bool
    apply(variant<BOOST_VARIANT_ENUM_PARAMS(T1)> const& geometry1,
          variant<BOOST_VARIANT_ENUM_PARAMS(T2)> const& geometry2,
          GeometryOut& geometry_out,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<GeometryOut, Strategy>(geometry_out,
                                                                   strategy),
                                    geometry1, geometry2);
    }
};
    
} // namespace resolve_variant
    

/*!
\brief \brief_calc2{intersection}
\ingroup intersection
\details \details_calc2{intersection, spatial set theoretic intersection}.
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam GeometryOut Collection of geometries (e.g. std::vector, std::deque, boost::geometry::multi*) of which
    the value_type fulfills a \p_l_or_c concept, or it is the output geometry (e.g. for a box)
\tparam Strategy \tparam_strategy{Intersection}
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param geometry_out The output geometry, either a multi_point, multi_polygon,
    multi_linestring, or a box (for intersection of two boxes)
\param strategy \param_strategy{intersection}

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/intersection.qbk]}
*/
template
<
    typename Geometry1,
    typename Geometry2,
    typename GeometryOut,
    typename Strategy
>
inline bool intersection(Geometry1 const& geometry1,
                         Geometry2 const& geometry2,
                         GeometryOut& geometry_out,
                         Strategy const& strategy)
{
    return resolve_variant::intersection
        <
            Geometry1,
            Geometry2
        >::apply(geometry1, geometry2, geometry_out, strategy);
}


/*!
\brief \brief_calc2{intersection}
\ingroup intersection
\details \details_calc2{intersection, spatial set theoretic intersection}.
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam GeometryOut Collection of geometries (e.g. std::vector, std::deque, boost::geometry::multi*) of which
    the value_type fulfills a \p_l_or_c concept, or it is the output geometry (e.g. for a box)
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param geometry_out The output geometry, either a multi_point, multi_polygon,
    multi_linestring, or a box (for intersection of two boxes)

\qbk{[include reference/algorithms/intersection.qbk]}
*/
template
<
    typename Geometry1,
    typename Geometry2,
    typename GeometryOut
>
inline bool intersection(Geometry1 const& geometry1,
                         Geometry2 const& geometry2,
                         GeometryOut& geometry_out)
{
    return resolve_variant::intersection
        <
            Geometry1,
            Geometry2
        >::apply(geometry1, geometry2, geometry_out, default_strategy());
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTION_INTERFACE_HPP

/* interface.hpp
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
*/