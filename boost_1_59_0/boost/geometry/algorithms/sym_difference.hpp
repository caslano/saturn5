// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2015-2021.
// Modifications copyright (c) 2015-2021 Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_SYM_DIFFERENCE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_SYM_DIFFERENCE_HPP


#include <algorithm>
#include <iterator>
#include <vector>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/intersection.hpp>
#include <boost/geometry/algorithms/union.hpp>
#include <boost/geometry/geometries/multi_polygon.hpp>
#include <boost/geometry/policies/robustness/get_rescale_policy.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/relate/cartesian.hpp>
#include <boost/geometry/strategies/relate/geographic.hpp>
#include <boost/geometry/strategies/relate/spherical.hpp>
#include <boost/geometry/util/range.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace sym_difference
{


template <typename GeometryOut>
struct compute_difference
{
    template
    <
        typename Geometry1,
        typename Geometry2,
        typename RobustPolicy,
        typename OutputIterator,
        typename Strategy
    >
    static inline OutputIterator apply(Geometry1 const& geometry1,
                                       Geometry2 const& geometry2,
                                       RobustPolicy const& robust_policy,
                                       OutputIterator out,
                                       Strategy const& strategy)
    {
        return geometry::dispatch::intersection_insert
            <
                Geometry1,
                Geometry2,
                GeometryOut,
                overlay_difference,
                geometry::detail::overlay::do_reverse
                    <
                        geometry::point_order<Geometry1>::value
                    >::value,
                geometry::detail::overlay::do_reverse
                    <
                        geometry::point_order<Geometry2>::value, true
                    >::value
            >::apply(geometry1, geometry2, robust_policy, out, strategy);
    }
};



template <typename GeometryOut, typename Geometry1, typename Geometry2>
struct sym_difference_generic
{
    template
    <
        typename RobustPolicy,
        typename OutputIterator,
        typename Strategy
    >
    static inline OutputIterator apply(Geometry1 const& geometry1,
                                       Geometry2 const& geometry2,
                                       RobustPolicy const& robust_policy,
                                       OutputIterator out,
                                       Strategy const& strategy)
    {
        out = compute_difference
            <
                GeometryOut
            >::apply(geometry1, geometry2, robust_policy, out, strategy);

        return compute_difference
            <
                GeometryOut
            >::apply(geometry2, geometry1, robust_policy, out, strategy);
    }
};


template <typename GeometryOut, typename Areal1, typename Areal2>
struct sym_difference_areal_areal
{
    template
    <
        typename RobustPolicy,
        typename OutputIterator,
        typename Strategy
    >
    static inline OutputIterator apply(Areal1 const& areal1,
                                       Areal2 const& areal2,
                                       RobustPolicy const& robust_policy,
                                       OutputIterator out,
                                       Strategy const& strategy)
    {
        typedef geometry::model::multi_polygon
            <
                GeometryOut
            > helper_geometry_type;

        helper_geometry_type diff12, diff21;

        std::back_insert_iterator<helper_geometry_type> oit12(diff12);
        std::back_insert_iterator<helper_geometry_type> oit21(diff21);

        compute_difference
            <
                GeometryOut
            >::apply(areal1, areal2, robust_policy, oit12, strategy);

        compute_difference
            <
                GeometryOut
            >::apply(areal2, areal1, robust_policy, oit21, strategy);

        return geometry::dispatch::union_insert
            <
                helper_geometry_type,
                helper_geometry_type,
                GeometryOut
            >::apply(diff12, diff21, robust_policy, out, strategy);
    }
};


template
<
    typename GeometryOut,
    typename SingleTag,
    template <typename, typename, typename> class Algorithm
>
struct sym_difference_same_inputs_tupled_output
{
    template
    <
        typename Geometry1,
        typename Geometry2,
        typename RobustPolicy,
        typename OutputIterator,
        typename Strategy
    >
    static inline OutputIterator apply(Geometry1 const& geometry1,
                                       Geometry2 const& geometry2,
                                       RobustPolicy const& robust_policy,
                                       OutputIterator out,
                                       Strategy const& strategy)
    {
        typedef typename geometry::detail::output_geometry_access
            <
                GeometryOut, SingleTag, SingleTag
            > access;

        access::get(out) = Algorithm
            <
                typename access::type, Geometry1, Geometry2
            >::apply(geometry1, geometry2, robust_policy, access::get(out), strategy);

        return out;
    }
};


template
<
    typename GeometryOut,
    typename SingleTag1,
    typename SingleTag2,
    bool Reverse = (geometry::core_dispatch::top_dim<SingleTag1>::value
                    > geometry::core_dispatch::top_dim<SingleTag2>::value)
>
struct sym_difference_different_inputs_tupled_output
{
    template
    <
        typename Geometry1,
        typename Geometry2,
        typename RobustPolicy,
        typename OutputIterator,
        typename Strategy
    >
    static inline OutputIterator apply(Geometry1 const& geometry1,
                                       Geometry2 const& geometry2,
                                       RobustPolicy const& robust_policy,
                                       OutputIterator out,
                                       Strategy const& strategy)
    {
        return sym_difference_different_inputs_tupled_output
            <
                GeometryOut, SingleTag2, SingleTag1
            >::apply(geometry2, geometry1, robust_policy, out, strategy);
    }
};

template
<
    typename GeometryOut,
    typename SingleTag1,
    typename SingleTag2
>
struct sym_difference_different_inputs_tupled_output
    <
        GeometryOut, SingleTag1, SingleTag2, false
    >
{
    template
    <
        typename Geometry1,
        typename Geometry2,
        typename RobustPolicy,
        typename OutputIterator,
        typename Strategy
    >
    static inline OutputIterator apply(Geometry1 const& geometry1,
                                       Geometry2 const& geometry2,
                                       RobustPolicy const& robust_policy,
                                       OutputIterator out,
                                       Strategy const& strategy)
    {
        typedef typename geometry::detail::output_geometry_access
            <
                GeometryOut, SingleTag1, SingleTag1
            > access1;
        typedef typename geometry::detail::output_geometry_access
            <
                GeometryOut, SingleTag2, SingleTag2
            > access2;

        access1::get(out) = compute_difference
            <
                typename access1::type
            >::apply(geometry1, geometry2, robust_policy, access1::get(out), strategy);

        access2::get(out) = geometry::detail::convert_to_output
            <
                Geometry2,
                typename access2::type
            >::apply(geometry2, access2::get(out));

        return out;
    }
};


}} // namespace detail::sym_difference
#endif // DOXYGEN_NO_DETAIL



#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Geometry1,
    typename Geometry2,
    typename GeometryOut,
    typename TagIn1 = typename geometry::tag_cast
        <
            typename tag<Geometry1>::type, pointlike_tag, linear_tag, areal_tag
        >::type,
    typename TagIn2 = typename geometry::tag_cast
        <
            typename tag<Geometry2>::type, pointlike_tag, linear_tag, areal_tag
        >::type,
    typename TagOut = typename detail::setop_insert_output_tag<GeometryOut>::type
>
struct sym_difference_insert
    : detail::sym_difference::sym_difference_generic
        <
            GeometryOut, Geometry1, Geometry2
        >
{};


template
<
    typename Areal1,
    typename Areal2,
    typename GeometryOut,
    typename TagOut
>
struct sym_difference_insert
    <
        Areal1, Areal2, GeometryOut,
        areal_tag, areal_tag, TagOut
    > : detail::sym_difference::sym_difference_areal_areal
        <
            GeometryOut, Areal1, Areal2
        >
{};



template
<
    typename PointLike1,
    typename PointLike2,
    typename GeometryOut
>
struct sym_difference_insert
    <
        PointLike1, PointLike2, GeometryOut,
        pointlike_tag, pointlike_tag, detail::tupled_output_tag
    >
    : detail::expect_output<PointLike1, PointLike2, GeometryOut, point_tag>
    , detail::sym_difference::sym_difference_same_inputs_tupled_output
        <
            GeometryOut,
            point_tag,
            detail::sym_difference::sym_difference_generic
        >
{};

template
<
    typename Linear1,
    typename Linear2,
    typename GeometryOut
>
struct sym_difference_insert
    <
        Linear1, Linear2, GeometryOut,
        linear_tag, linear_tag, detail::tupled_output_tag
    >
    : detail::expect_output<Linear1, Linear2, GeometryOut, linestring_tag>
    , detail::sym_difference::sym_difference_same_inputs_tupled_output
        <
            GeometryOut,
            linestring_tag,
            detail::sym_difference::sym_difference_generic
        >
{};

template
<
    typename Areal1,
    typename Areal2,
    typename GeometryOut
>
struct sym_difference_insert
    <
        Areal1, Areal2, GeometryOut,
        areal_tag, areal_tag, detail::tupled_output_tag
    >
    : detail::expect_output<Areal1, Areal2, GeometryOut, polygon_tag>
    , detail::sym_difference::sym_difference_same_inputs_tupled_output
        <
            GeometryOut,
            polygon_tag,
            detail::sym_difference::sym_difference_areal_areal
        >
{};

template
<
    typename Geometry1,
    typename Geometry2,
    typename GeometryOut,
    typename TagIn1,
    typename TagIn2
>
struct sym_difference_insert
    <
        Geometry1, Geometry2, GeometryOut,
        TagIn1, TagIn2, detail::tupled_output_tag
    >
    : detail::expect_output
        <
            Geometry1, Geometry2, GeometryOut,
            typename detail::single_tag_from_base_tag<TagIn1>::type,
            typename detail::single_tag_from_base_tag<TagIn2>::type
        >
    , detail::sym_difference::sym_difference_different_inputs_tupled_output
        <
            GeometryOut,
            typename detail::single_tag_from_base_tag<TagIn1>::type,
            typename detail::single_tag_from_base_tag<TagIn2>::type
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH



#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace sym_difference
{



/*!
\brief \brief_calc2{symmetric difference}  \brief_strategy
\ingroup sym_difference
\details \details_calc2{symmetric difference, spatial set theoretic symmetric difference (XOR)}
    \brief_strategy. \details_insert{sym_difference}
\tparam GeometryOut output geometry type, must be specified
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam Strategy \tparam_strategy_overlay
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param out \param_out{difference}
\param strategy \param_strategy{difference}
\return \return_out

\qbk{distinguish,with strategy}
*/
template
<
    typename GeometryOut,
    typename Geometry1,
    typename Geometry2,
    typename OutputIterator,
    typename Strategy
>
inline OutputIterator sym_difference_insert(Geometry1 const& geometry1,
            Geometry2 const& geometry2,
            OutputIterator out,
            Strategy const& strategy)
{
    concepts::check<Geometry1 const>();
    concepts::check<Geometry2 const>();
    //concepts::check<GeometryOut>();
    geometry::detail::output_geometry_concept_check<GeometryOut>::apply();

    typedef typename geometry::rescale_overlay_policy_type
        <
            Geometry1,
            Geometry2,
            typename Strategy::cs_tag
        >::type rescale_policy_type;

    rescale_policy_type robust_policy
            = geometry::get_rescale_policy<rescale_policy_type>(
                geometry1, geometry2, strategy);

    return dispatch::sym_difference_insert
        <
            Geometry1, Geometry2, GeometryOut
        >::apply(geometry1, geometry2, robust_policy, out, strategy);
}


/*!
\brief \brief_calc2{symmetric difference}
\ingroup sym_difference
\details \details_calc2{symmetric difference, spatial set theoretic symmetric difference (XOR)}
    \details_insert{sym_difference}
\tparam GeometryOut output geometry type, must be specified
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param out \param_out{difference}
\return \return_out

*/
template
<
    typename GeometryOut,
    typename Geometry1,
    typename Geometry2,
    typename OutputIterator
>
inline OutputIterator sym_difference_insert(Geometry1 const& geometry1,
            Geometry2 const& geometry2, OutputIterator out)
{
    typedef typename strategies::relate::services::default_strategy
        <
            Geometry1, Geometry2
        >::type strategy_type;

    return sym_difference_insert<GeometryOut>(geometry1, geometry2, out, strategy_type());
}

}} // namespace detail::sym_difference
#endif // DOXYGEN_NO_DETAIL


namespace resolve_strategy {

template
<
    typename Strategy,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategy>::value
>
struct sym_difference
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

        detail::sym_difference::sym_difference_insert<single_out>(
            geometry1, geometry2,
            geometry::detail::output_geometry_back_inserter(output_collection),
            strategy);
    }
};

template <typename Strategy>
struct sym_difference<Strategy, false>
{
    template <typename Geometry1, typename Geometry2, typename Collection>
    static inline void apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Collection & output_collection,
                             Strategy const& strategy)
    {
        using strategies::relate::services::strategy_converter;

        sym_difference
            <
                decltype(strategy_converter<Strategy>::get(strategy))
            >::apply(geometry1, geometry2, output_collection,
                     strategy_converter<Strategy>::get(strategy));
    }
};

template <>
struct sym_difference<default_strategy, false>
{
    template <typename Geometry1, typename Geometry2, typename Collection>
    static inline void apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Collection & output_collection,
                             default_strategy)
    {
        typedef typename strategies::relate::services::default_strategy
            <
                Geometry1, Geometry2
            >::type strategy_type;

        sym_difference
            <
                strategy_type
            >::apply(geometry1, geometry2, output_collection, strategy_type());
    }
};

} // resolve_strategy


namespace resolve_variant
{
    
template <typename Geometry1, typename Geometry2>
struct sym_difference
{
    template <typename Collection, typename Strategy>
    static inline void apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Collection& output_collection,
                             Strategy const& strategy)
    {
        resolve_strategy::sym_difference
            <
                Strategy
            >::apply(geometry1, geometry2, output_collection, strategy);
    }
};


template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Geometry2>
struct sym_difference<variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Geometry2>
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
            sym_difference
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
struct sym_difference<Geometry1, variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
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
            sym_difference
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
struct sym_difference<variant<BOOST_VARIANT_ENUM_PARAMS(T1)>, variant<BOOST_VARIANT_ENUM_PARAMS(T2)> >
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
            sym_difference
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
\brief \brief_calc2{symmetric difference}
\ingroup sym_difference
\details \details_calc2{symmetric difference, spatial set theoretic symmetric difference (XOR)}.
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam Collection output collection, either a multi-geometry,
    or a std::vector<Geometry> / std::deque<Geometry> etc
\tparam Strategy \tparam_strategy{Sym_difference}
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param output_collection the output collection
\param strategy \param_strategy{sym_difference}

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/sym_difference.qbk]}
*/
template
<
    typename Geometry1,
    typename Geometry2,
    typename Collection,
    typename Strategy
>
inline void sym_difference(Geometry1 const& geometry1,
                           Geometry2 const& geometry2,
                           Collection& output_collection,
                           Strategy const& strategy)
{
    resolve_variant::sym_difference
        <
            Geometry1,
            Geometry2
        >::apply(geometry1, geometry2, output_collection, strategy);
}


/*!
\brief \brief_calc2{symmetric difference}
\ingroup sym_difference
\details \details_calc2{symmetric difference, spatial set theoretic symmetric difference (XOR)}.
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam Collection output collection, either a multi-geometry,
    or a std::vector<Geometry> / std::deque<Geometry> etc
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param output_collection the output collection

\qbk{[include reference/algorithms/sym_difference.qbk]}
*/
template
<
    typename Geometry1,
    typename Geometry2,
    typename Collection
>
inline void sym_difference(Geometry1 const& geometry1,
                           Geometry2 const& geometry2,
                           Collection& output_collection)
{
    resolve_variant::sym_difference
        <
            Geometry1,
            Geometry2
        >::apply(geometry1, geometry2, output_collection, default_strategy());    
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_SYM_DIFFERENCE_HPP

/* sym_difference.hpp
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
*/