// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2019.
// Modifications copyright (c) 2017, 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DIFFERENCE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DIFFERENCE_HPP


#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/detail/overlay/intersection_insert.hpp>
#include <boost/geometry/policies/robustness/get_rescale_policy.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/util/range.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace difference
{

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
    concepts::check<GeometryOut>();

    typedef typename geometry::rescale_overlay_policy_type
        <
            Geometry1,
            Geometry2,
            typename Strategy::cs_tag
        >::type rescale_policy_type;

    rescale_policy_type robust_policy
            = geometry::get_rescale_policy<rescale_policy_type>(
                geometry1, geometry2, strategy);

    return geometry::dispatch::intersection_insert
        <
            Geometry1, Geometry2,
            GeometryOut,
            overlay_difference,
            geometry::detail::overlay::do_reverse<geometry::point_order<Geometry1>::value>::value,
            geometry::detail::overlay::do_reverse<geometry::point_order<Geometry2>::value, true>::value
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
    typedef typename strategy::relate::services::default_strategy
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

struct difference
{
    template
    <
        typename Geometry1,
        typename Geometry2,
        typename Collection,
        typename Strategy
    >
    static inline void apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Collection & output_collection,
                             Strategy const& strategy)
    {
        typedef typename boost::range_value<Collection>::type geometry_out;

        detail::difference::difference_insert<geometry_out>(
            geometry1, geometry2,
            range::back_inserter(output_collection),
            strategy);
    }

    template
    <
        typename Geometry1,
        typename Geometry2,
        typename Collection
    >
    static inline void apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Collection & output_collection,
                             default_strategy)
    {
        typedef typename boost::range_value<Collection>::type geometry_out;
        
        detail::difference::difference_insert<geometry_out>(
            geometry1, geometry2,
            range::back_inserter(output_collection));
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
        resolve_strategy::difference::apply(geometry1, geometry2,
                                            output_collection,
                                            strategy);
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
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
*/