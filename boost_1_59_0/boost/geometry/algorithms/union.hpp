// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014-2021.
// Modifications copyright (c) 2014-2021 Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_UNION_HPP
#define BOOST_GEOMETRY_ALGORITHMS_UNION_HPP


#include <boost/range/value_type.hpp>

#include <boost/geometry/algorithms/detail/intersection/multi.hpp>
#include <boost/geometry/algorithms/detail/overlay/intersection_insert.hpp>
#include <boost/geometry/algorithms/detail/overlay/linear_linear.hpp>
#include <boost/geometry/algorithms/detail/overlay/overlay.hpp>
#include <boost/geometry/algorithms/detail/overlay/pointlike_pointlike.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/reverse_dispatch.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/policies/robustness/get_rescale_policy.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/relate/cartesian.hpp>
#include <boost/geometry/strategies/relate/geographic.hpp>
#include <boost/geometry/strategies/relate/spherical.hpp>
#include <boost/geometry/util/range.hpp>



namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Geometry1, typename Geometry2, typename GeometryOut,
    typename TagIn1 = typename tag<Geometry1>::type,
    typename TagIn2 = typename tag<Geometry2>::type,
    typename TagOut = typename detail::setop_insert_output_tag<GeometryOut>::type,
    typename CastedTagIn1 = typename geometry::tag_cast<TagIn1, areal_tag, linear_tag, pointlike_tag>::type,
    typename CastedTagIn2 = typename geometry::tag_cast<TagIn2, areal_tag, linear_tag, pointlike_tag>::type,
    typename CastedTagOut = typename geometry::tag_cast<TagOut, areal_tag, linear_tag, pointlike_tag>::type,
    bool Reverse = geometry::reverse_dispatch<Geometry1, Geometry2>::type::value
>
struct union_insert: not_implemented<TagIn1, TagIn2, TagOut>
{};


// If reversal is needed, perform it first

template
<
    typename Geometry1, typename Geometry2, typename GeometryOut,
    typename TagIn1, typename TagIn2, typename TagOut,
    typename CastedTagIn1, typename CastedTagIn2, typename CastedTagOut
>
struct union_insert
    <
        Geometry1, Geometry2, GeometryOut,
        TagIn1, TagIn2, TagOut,
        CastedTagIn1, CastedTagIn2, CastedTagOut,
        true
    >
{
    template <typename RobustPolicy, typename OutputIterator, typename Strategy>
    static inline OutputIterator apply(Geometry1 const& g1,
                                       Geometry2 const& g2,
                                       RobustPolicy const& robust_policy,
                                       OutputIterator out,
                                       Strategy const& strategy)
    {
        return union_insert
            <
                Geometry2, Geometry1, GeometryOut
            >::apply(g2, g1, robust_policy, out, strategy);
    }
};


template
<
    typename Geometry1, typename Geometry2, typename GeometryOut,
    typename TagIn1, typename TagIn2, typename TagOut
>
struct union_insert
    <
        Geometry1, Geometry2, GeometryOut,
        TagIn1, TagIn2, TagOut,
        areal_tag, areal_tag, areal_tag,
        false
    > : detail::overlay::overlay
        <
            Geometry1, Geometry2,
            detail::overlay::do_reverse<geometry::point_order<Geometry1>::value>::value,
            detail::overlay::do_reverse<geometry::point_order<Geometry2>::value>::value,
            detail::overlay::do_reverse<geometry::point_order<GeometryOut>::value>::value,
            GeometryOut,
            overlay_union
        >
{};


// dispatch for union of linear geometries
template
<
    typename Linear1, typename Linear2, typename LineStringOut,
    typename TagIn1, typename TagIn2
>
struct union_insert
    <
        Linear1, Linear2, LineStringOut,
        TagIn1, TagIn2, linestring_tag,
        linear_tag, linear_tag, linear_tag,
        false
    > : detail::overlay::linear_linear_linestring
        <
            Linear1, Linear2, LineStringOut, overlay_union
        >
{};


// dispatch for point-like geometries
template
<
    typename PointLike1, typename PointLike2, typename PointOut,
    typename TagIn1, typename TagIn2
>
struct union_insert
    <
        PointLike1, PointLike2, PointOut,
        TagIn1, TagIn2, point_tag,
        pointlike_tag, pointlike_tag, pointlike_tag,
        false
    > : detail::overlay::union_pointlike_pointlike_point
        <
            PointLike1, PointLike2, PointOut
        >
{};


template
<
    typename Geometry1, typename Geometry2, typename SingleTupledOut,
    typename TagIn1, typename TagIn2,
    typename CastedTagIn
>
struct union_insert
    <
        Geometry1, Geometry2, SingleTupledOut,
        TagIn1, TagIn2, detail::tupled_output_tag,
        CastedTagIn, CastedTagIn, detail::tupled_output_tag,
        false
    >
{
    typedef typename geometry::detail::single_tag_from_base_tag
        <
            CastedTagIn
        >::type single_tag;

    typedef detail::expect_output
        <
            Geometry1, Geometry2, SingleTupledOut, single_tag
        > expect_check;

    typedef typename geometry::detail::output_geometry_access
        <
            SingleTupledOut, single_tag, single_tag
        > access;

    template <typename RobustPolicy, typename OutputIterator, typename Strategy>
    static inline OutputIterator apply(Geometry1 const& g1,
                                       Geometry2 const& g2,
                                       RobustPolicy const& robust_policy,
                                       OutputIterator out,
                                       Strategy const& strategy)
    {
        access::get(out) = union_insert
            <
                Geometry2, Geometry1, typename access::type
            >::apply(g2, g1, robust_policy, access::get(out), strategy);

        return out;
    }
};


template
<
    typename Geometry1, typename Geometry2, typename SingleTupledOut,
    typename SingleTag1, typename SingleTag2,
    bool Geometry1LesserTopoDim = (topological_dimension<Geometry1>::value
                                    < topological_dimension<Geometry2>::value)
>
struct union_insert_tupled_different
{
    typedef typename geometry::detail::output_geometry_access
        <
            SingleTupledOut, SingleTag1, SingleTag1
        > access1;

    typedef typename geometry::detail::output_geometry_access
        <
            SingleTupledOut, SingleTag2, SingleTag2
        > access2;

    template <typename RobustPolicy, typename OutputIterator, typename Strategy>
    static inline OutputIterator apply(Geometry1 const& g1,
                                       Geometry2 const& g2,
                                       RobustPolicy const& robust_policy,
                                       OutputIterator out,
                                       Strategy const& strategy)
    {
        access1::get(out) = geometry::dispatch::intersection_insert
            <
                Geometry1, Geometry2,
                typename access1::type,
                overlay_difference,
                geometry::detail::overlay::do_reverse<geometry::point_order<Geometry1>::value>::value,
                geometry::detail::overlay::do_reverse<geometry::point_order<Geometry2>::value, true>::value
            >::apply(g1, g2, robust_policy, access1::get(out), strategy);

        access2::get(out) = geometry::detail::convert_to_output
            <
                Geometry2,
                typename access2::type
            >::apply(g2, access2::get(out));

        return out;
    }
};


template
<
    typename Geometry1, typename Geometry2, typename SingleTupledOut,
    typename SingleTag1, typename SingleTag2
>
struct union_insert_tupled_different
    <
        Geometry1, Geometry2, SingleTupledOut, SingleTag1, SingleTag2, false
    >
{
    template <typename RobustPolicy, typename OutputIterator, typename Strategy>
    static inline OutputIterator apply(Geometry1 const& g1,
                                       Geometry2 const& g2,
                                       RobustPolicy const& robust_policy,
                                       OutputIterator out,
                                       Strategy const& strategy)
    {
        return union_insert_tupled_different
            <
                Geometry2, Geometry1, SingleTupledOut, SingleTag2, SingleTag1, true
            >::apply(g2, g1, robust_policy, out, strategy);
    }
};


template
<
    typename Geometry1, typename Geometry2, typename SingleTupledOut,
    typename TagIn1, typename TagIn2,
    typename CastedTagIn1, typename CastedTagIn2
>
struct union_insert
    <
        Geometry1, Geometry2, SingleTupledOut,
        TagIn1, TagIn2, detail::tupled_output_tag,
        CastedTagIn1, CastedTagIn2, detail::tupled_output_tag,
        false
    >
{
    typedef typename geometry::detail::single_tag_from_base_tag
        <
            CastedTagIn1
        >::type single_tag1;

    typedef detail::expect_output
        <
            Geometry1, Geometry2, SingleTupledOut, single_tag1
        > expect_check1;

    typedef typename geometry::detail::single_tag_from_base_tag
        <
            CastedTagIn2
        >::type single_tag2;

    typedef detail::expect_output
        <
            Geometry1, Geometry2, SingleTupledOut, single_tag2
        > expect_check2;

    template <typename RobustPolicy, typename OutputIterator, typename Strategy>
    static inline OutputIterator apply(Geometry1 const& g1,
                                       Geometry2 const& g2,
                                       RobustPolicy const& robust_policy,
                                       OutputIterator out,
                                       Strategy const& strategy)
    {
        return union_insert_tupled_different
            <
                Geometry1, Geometry2, SingleTupledOut, single_tag1, single_tag2
            >::apply(g1, g2, robust_policy, out, strategy);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace union_
{

/*!
\brief_calc2{union}
\ingroup union
\details \details_calc2{union_insert, spatial set theoretic union}.
    \details_insert{union}
\tparam GeometryOut output geometry type, must be specified
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam OutputIterator output iterator
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param out \param_out{union}
\return \return_out
*/
template
<
    typename GeometryOut,
    typename Geometry1,
    typename Geometry2,
    typename OutputIterator
>
inline OutputIterator union_insert(Geometry1 const& geometry1,
            Geometry2 const& geometry2,
            OutputIterator out)
{
    concepts::check<Geometry1 const>();
    concepts::check<Geometry2 const>();
    geometry::detail::output_geometry_concept_check<GeometryOut>::apply();

    typename strategies::relate::services::default_strategy
        <
            Geometry1, Geometry2
        >::type strategy;

    typedef typename geometry::rescale_overlay_policy_type
        <
            Geometry1,
            Geometry2
        >::type rescale_policy_type;

    rescale_policy_type robust_policy
            = geometry::get_rescale_policy<rescale_policy_type>(
                geometry1, geometry2, strategy);

    return dispatch::union_insert
           <
               Geometry1, Geometry2, GeometryOut
           >::apply(geometry1, geometry2, robust_policy, out, strategy);
}


}} // namespace detail::union_
#endif // DOXYGEN_NO_DETAIL


namespace resolve_strategy {

template
<
    typename Strategy,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategy>::value
>
struct union_
{
    template <typename Geometry1, typename Geometry2, typename Collection>
    static inline void apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Collection & output_collection,
                             Strategy const& strategy)
    {
        typedef typename geometry::detail::output_geometry_value
            <
                Collection
            >::type single_out;

        typedef typename geometry::rescale_overlay_policy_type
            <
                Geometry1,
                Geometry2,
                typename Strategy::cs_tag
            >::type rescale_policy_type;

        rescale_policy_type robust_policy
                = geometry::get_rescale_policy<rescale_policy_type>(
                    geometry1, geometry2, strategy);

        dispatch::union_insert
           <
               Geometry1, Geometry2, single_out
           >::apply(geometry1, geometry2, robust_policy,
                    geometry::detail::output_geometry_back_inserter(output_collection),
                    strategy);
    }
};

template <typename Strategy>
struct union_<Strategy, false>
{
    template <typename Geometry1, typename Geometry2, typename Collection>
    static inline void apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Collection & output_collection,
                             Strategy const& strategy)
    {
        using strategies::relate::services::strategy_converter;

        union_
            <
                decltype(strategy_converter<Strategy>::get(strategy))
            >::apply(geometry1, geometry2, output_collection,
                     strategy_converter<Strategy>::get(strategy));
    }
};

template <>
struct union_<default_strategy, false>
{
    template <typename Geometry1, typename Geometry2, typename Collection>
    static inline void apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Collection & output_collection,
                             default_strategy)
    {
        typedef typename strategies::relate::services::default_strategy
            <
                Geometry1,
                Geometry2
            >::type strategy_type;

        union_
            <
                strategy_type
            >::apply(geometry1, geometry2, output_collection, strategy_type());
    }
};

} // resolve_strategy


namespace resolve_variant
{
    
template <typename Geometry1, typename Geometry2>
struct union_
{
    template <typename Collection, typename Strategy>
    static inline void apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Collection& output_collection,
                             Strategy const& strategy)
    {
        concepts::check<Geometry1 const>();
        concepts::check<Geometry2 const>();
        //concepts::check<typename boost::range_value<Collection>::type>();
        geometry::detail::output_geometry_concept_check
            <
                typename geometry::detail::output_geometry_value
                    <
                        Collection
                    >::type
            >::apply();

        resolve_strategy::union_
            <
                Strategy
            >::apply(geometry1, geometry2, output_collection, strategy);
    }
};


template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Geometry2>
struct union_<variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Geometry2>
{
    template <typename Collection, typename Strategy>
    struct visitor: static_visitor<>
    {
        Geometry2 const& m_geometry2;
        Collection& m_output_collection;
        Strategy const& m_strategy;
        
        visitor(Geometry2 const& geometry2,
                Collection& output_collection,
                Strategy const& strategy)
            : m_geometry2(geometry2)
            , m_output_collection(output_collection)
            , m_strategy(strategy)
        {}
        
        template <typename Geometry1>
        void operator()(Geometry1 const& geometry1) const
        {
            union_
                <
                    Geometry1,
                    Geometry2
                >::apply(geometry1, m_geometry2, m_output_collection, m_strategy);
        }
    };
    
    template <typename Collection, typename Strategy>
    static inline void
    apply(variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry1,
          Geometry2 const& geometry2,
          Collection& output_collection,
          Strategy const& strategy)
    {
        boost::apply_visitor(visitor<Collection, Strategy>(geometry2,
                                                           output_collection,
                                                           strategy),
                             geometry1);
    }
};


template <typename Geometry1, BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct union_<Geometry1, variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename Collection, typename Strategy>
    struct visitor: static_visitor<>
    {
        Geometry1 const& m_geometry1;
        Collection& m_output_collection;
        Strategy const& m_strategy;
        
        visitor(Geometry1 const& geometry1,
                Collection& output_collection,
                Strategy const& strategy)
            : m_geometry1(geometry1)
            , m_output_collection(output_collection)
            , m_strategy(strategy)
        {}
        
        template <typename Geometry2>
        void operator()(Geometry2 const& geometry2) const
        {
            union_
                <
                    Geometry1,
                    Geometry2
                >::apply(m_geometry1, geometry2, m_output_collection, m_strategy);
        }
    };
    
    template <typename Collection, typename Strategy>
    static inline void
    apply(Geometry1 const& geometry1,
          variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry2,
          Collection& output_collection,
          Strategy const& strategy)
    {
        boost::apply_visitor(visitor<Collection, Strategy>(geometry1,
                                                           output_collection,
                                                           strategy),
                             geometry2);
    }
};


template <BOOST_VARIANT_ENUM_PARAMS(typename T1), BOOST_VARIANT_ENUM_PARAMS(typename T2)>
struct union_<variant<BOOST_VARIANT_ENUM_PARAMS(T1)>, variant<BOOST_VARIANT_ENUM_PARAMS(T2)> >
{
    template <typename Collection, typename Strategy>
    struct visitor: static_visitor<>
    {
        Collection& m_output_collection;
        Strategy const& m_strategy;
        
        visitor(Collection& output_collection, Strategy const& strategy)
            : m_output_collection(output_collection)
            , m_strategy(strategy)
        {}
        
        template <typename Geometry1, typename Geometry2>
        void operator()(Geometry1 const& geometry1,
                        Geometry2 const& geometry2) const
        {
            union_
                <
                    Geometry1,
                    Geometry2
                >::apply(geometry1, geometry2, m_output_collection, m_strategy);
        }
    };
    
    template <typename Collection, typename Strategy>
    static inline void
    apply(variant<BOOST_VARIANT_ENUM_PARAMS(T1)> const& geometry1,
          variant<BOOST_VARIANT_ENUM_PARAMS(T2)> const& geometry2,
          Collection& output_collection,
          Strategy const& strategy)
    {
        boost::apply_visitor(visitor<Collection, Strategy>(output_collection,
                                                           strategy),
                             geometry1, geometry2);
    }
};
    
} // namespace resolve_variant


/*!
\brief Combines two geometries which each other
\ingroup union
\details \details_calc2{union, spatial set theoretic union}.
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam Collection output collection, either a multi-geometry,
    or a std::vector<Geometry> / std::deque<Geometry> etc
\tparam Strategy \tparam_strategy{Union_}
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param output_collection the output collection
\param strategy \param_strategy{union_}
\note Called union_ because union is a reserved word.

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/union.qbk]}
*/
template
<
    typename Geometry1,
    typename Geometry2,
    typename Collection,
    typename Strategy
>
inline void union_(Geometry1 const& geometry1,
                   Geometry2 const& geometry2,
                   Collection& output_collection,
                   Strategy const& strategy)
{
    resolve_variant::union_
        <
            Geometry1,
            Geometry2
        >::apply(geometry1, geometry2, output_collection, strategy);
}


/*!
\brief Combines two geometries which each other
\ingroup union
\details \details_calc2{union, spatial set theoretic union}.
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam Collection output collection, either a multi-geometry,
    or a std::vector<Geometry> / std::deque<Geometry> etc
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param output_collection the output collection
\note Called union_ because union is a reserved word.

\qbk{[include reference/algorithms/union.qbk]}
*/
template
<
    typename Geometry1,
    typename Geometry2,
    typename Collection
>
inline void union_(Geometry1 const& geometry1,
                   Geometry2 const& geometry2,
                   Collection& output_collection)
{
    resolve_variant::union_
        <
            Geometry1,
            Geometry2
        >::apply(geometry1, geometry2, output_collection, default_strategy());
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_UNION_HPP

/* union.hpp
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
*/