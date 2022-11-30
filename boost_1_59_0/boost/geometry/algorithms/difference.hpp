// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017-2021.
// Modifications copyright (c) 2017-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DIFFERENCE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DIFFERENCE_HPP


#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/detail/intersection/multi.hpp>
#include <boost/geometry/algorithms/detail/overlay/intersection_insert.hpp>
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
namespace detail { namespace difference
{

template
<
    typename Geometry1,
    typename Geometry2,
    typename SingleOut,
    typename OutTag = typename detail::setop_insert_output_tag<SingleOut>::type,
    bool ReturnGeometry1 = (topological_dimension<Geometry1>::value
                            > topological_dimension<Geometry2>::value)
>
struct call_intersection_insert
{
    template
    <
        typename OutputIterator,
        typename RobustPolicy,
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
                Geometry1, Geometry2,
                SingleOut,
                overlay_difference,
                geometry::detail::overlay::do_reverse<geometry::point_order<Geometry1>::value>::value,
                geometry::detail::overlay::do_reverse<geometry::point_order<Geometry2>::value, true>::value
            >::apply(geometry1, geometry2, robust_policy, out, strategy);
    }
};

template
<
    typename Geometry1,
    typename Geometry2,
    typename SingleOut
>
struct call_intersection_insert_tupled_base
{
    typedef typename geometry::detail::single_tag_from_base_tag
        <
            typename geometry::tag_cast
                <
                    typename geometry::tag<Geometry1>::type,
                    pointlike_tag, linear_tag, areal_tag
                >::type
        >::type single_tag;

    typedef detail::expect_output
        <
            Geometry1, Geometry2, SingleOut, single_tag
        > expect_check;

    typedef typename geometry::detail::output_geometry_access
        <
            SingleOut, single_tag, single_tag
        > access;
};

template
<
    typename Geometry1,
    typename Geometry2,
    typename SingleOut
>
struct call_intersection_insert
    <
        Geometry1, Geometry2, SingleOut,
        detail::tupled_output_tag,
        false
    >
    : call_intersection_insert_tupled_base<Geometry1, Geometry2, SingleOut>
{
    typedef call_intersection_insert_tupled_base<Geometry1, Geometry2, SingleOut> base_t;

    template
    <
        typename OutputIterator,
        typename RobustPolicy,
        typename Strategy
    >
    static inline OutputIterator apply(Geometry1 const& geometry1,
                                       Geometry2 const& geometry2,
                                       RobustPolicy const& robust_policy,
                                       OutputIterator out,
                                       Strategy const& strategy)
    {
        base_t::access::get(out) = call_intersection_insert
            <
                Geometry1, Geometry2,
                typename base_t::access::type
            >::apply(geometry1, geometry2, robust_policy,
                     base_t::access::get(out), strategy);

        return out;
    }
};

template
<
    typename Geometry1,
    typename Geometry2,
    typename SingleOut
>
struct call_intersection_insert
    <
        Geometry1, Geometry2, SingleOut,
        detail::tupled_output_tag,
        true
    >
    : call_intersection_insert_tupled_base<Geometry1, Geometry2, SingleOut>
{
    typedef call_intersection_insert_tupled_base<Geometry1, Geometry2, SingleOut> base_t;

    template
    <
        typename OutputIterator,
        typename RobustPolicy,
        typename Strategy
    >
    static inline OutputIterator apply(Geometry1 const& geometry1,
                                       Geometry2 const& ,
                                       RobustPolicy const& ,
                                       OutputIterator out,
                                       Strategy const& )
    {
        base_t::access::get(out) = geometry::detail::convert_to_output
            <
                Geometry1,
                typename base_t::access::type
            >::apply(geometry1, base_t::access::get(out));

        return out;
    }
};


/*!
\brief_calc2{difference} \brief_strategy
\ingroup difference
\details \details_calc2{difference_insert, spatial set theoretic difference}
    \brief_strategy. \details_inserter{difference}
\tparam GeometryOut output geometry type, must be specified
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam OutputIterator output iterator
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
inline OutputIterator difference_insert(Geometry1 const& geometry1,
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

    return geometry::detail::difference::call_intersection_insert
        <
            Geometry1, Geometry2, GeometryOut
        >::apply(geometry1, geometry2, robust_policy, out, strategy);
}

/*!
\brief_calc2{difference}
\ingroup difference
\details \details_calc2{difference_insert, spatial set theoretic difference}.
    \details_insert{difference}
\tparam GeometryOut output geometry type, must be specified
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam OutputIterator output iterator
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param out \param_out{difference}
\return \return_out

\qbk{[include reference/algorithms/difference_insert.qbk]}
*/
template
<
    typename GeometryOut,
    typename Geometry1,
    typename Geometry2,
    typename OutputIterator
>
inline OutputIterator difference_insert(Geometry1 const& geometry1,
                                        Geometry2 const& geometry2,
                                        OutputIterator out)
{
    typedef typename strategies::relate::services::default_strategy
        <
            Geometry1,
            Geometry2
        >::type strategy_type;

    return difference_insert<GeometryOut>(geometry1, geometry2, out,
                                          strategy_type());
}


}} // namespace detail::difference
#endif // DOXYGEN_NO_DETAIL


namespace resolve_strategy {

template
<
    typename Strategy,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategy>::value
>
struct difference
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

        detail::difference::difference_insert<single_out>(
            geometry1, geometry2,
            geometry::detail::output_geometry_back_inserter(output_collection),
            strategy);
    }
};

template <typename Strategy>
struct difference<Strategy, false>
{
    template <typename Geometry1, typename Geometry2, typename Collection>
    static inline void apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Collection & output_collection,
                             Strategy const& strategy)
    {
        using strategies::relate::services::strategy_converter;
        
        difference
            <
                decltype(strategy_converter<Strategy>::get(strategy))
            >::apply(geometry1, geometry2, output_collection,
                     strategy_converter<Strategy>::get(strategy));
    }
};

template <>
struct difference<default_strategy, false>
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
        
        difference
            <
                strategy_type
            >::apply(geometry1, geometry2, output_collection, strategy_type());
    }
};

} // resolve_strategy


namespace resolve_variant
{
    
template <typename Geometry1, typename Geometry2>
struct difference
{
    template <typename Collection, typename Strategy>
    static inline void apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Collection& output_collection,
                             Strategy const& strategy)
    {
        resolve_strategy::difference
            <
                Strategy
            >::apply(geometry1, geometry2, output_collection, strategy);
    }
};


template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Geometry2>
struct difference<variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Geometry2>
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
            difference
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
struct difference<Geometry1, variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
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
            difference
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
struct difference<variant<BOOST_VARIANT_ENUM_PARAMS(T1)>, variant<BOOST_VARIANT_ENUM_PARAMS(T2)> >
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
            difference
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
\brief_calc2{difference}
\ingroup difference
\details \details_calc2{difference, spatial set theoretic difference}.
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam Collection \tparam_output_collection
\tparam Strategy \tparam_strategy{Difference}
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param output_collection the output collection
\param strategy \param_strategy{difference}

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/difference.qbk]}
*/
template
<
    typename Geometry1,
    typename Geometry2,
    typename Collection,
    typename Strategy
>
inline void difference(Geometry1 const& geometry1,
                       Geometry2 const& geometry2,
                       Collection& output_collection,
                       Strategy const& strategy)
{
    resolve_variant::difference
        <
            Geometry1,
            Geometry2
        >::apply(geometry1, geometry2, output_collection, strategy);
}


/*!
\brief_calc2{difference}
\ingroup difference
\details \details_calc2{difference, spatial set theoretic difference}.
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam Collection \tparam_output_collection
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param output_collection the output collection

\qbk{[include reference/algorithms/difference.qbk]}
*/
template
<
    typename Geometry1,
    typename Geometry2,
    typename Collection
>
inline void difference(Geometry1 const& geometry1,
                       Geometry2 const& geometry2,
                       Collection& output_collection)
{
    resolve_variant::difference
        <
            Geometry1,
            Geometry2
        >::apply(geometry1, geometry2, output_collection, default_strategy());
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DIFFERENCE_HPP

/* difference.hpp
+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
*/