// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014, 2017, 2018, 2019.
// Modifications copyright (c) 2014-2019 Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_UNION_HPP
#define BOOST_GEOMETRY_ALGORITHMS_UNION_HPP


#include <boost/range/metafunctions.hpp>

#include <boost/geometry/core/is_areal.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/reverse_dispatch.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/algorithms/detail/overlay/overlay.hpp>
#include <boost/geometry/policies/robustness/get_rescale_policy.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/util/range.hpp>

#include <boost/geometry/algorithms/detail/overlay/linear_linear.hpp>
#include <boost/geometry/algorithms/detail/overlay/pointlike_pointlike.hpp>


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
    typename TagOut = typename tag<GeometryOut>::type,
    bool Areal1 = geometry::is_areal<Geometry1>::value,
    bool Areal2 = geometry::is_areal<Geometry2>::value,
    bool ArealOut = geometry::is_areal<GeometryOut>::value,
    bool Reverse1 = detail::overlay::do_reverse<geometry::point_order<Geometry1>::value>::value,
    bool Reverse2 = detail::overlay::do_reverse<geometry::point_order<Geometry2>::value>::value,
    bool ReverseOut = detail::overlay::do_reverse<geometry::point_order<GeometryOut>::value>::value,
    bool Reverse = geometry::reverse_dispatch<Geometry1, Geometry2>::type::value
>
struct union_insert: not_implemented<TagIn1, TagIn2, TagOut>
{};


// If reversal is needed, perform it first

template
<
    typename Geometry1, typename Geometry2, typename GeometryOut,
    typename TagIn1, typename TagIn2, typename TagOut,
    bool Areal1, bool Areal2, bool ArealOut,
    bool Reverse1, bool Reverse2, bool ReverseOut
>
struct union_insert
    <
        Geometry1, Geometry2, GeometryOut,
        TagIn1, TagIn2, TagOut,
        Areal1, Areal2, ArealOut,
        Reverse1, Reverse2, ReverseOut,
        true
    >: union_insert<Geometry2, Geometry1, GeometryOut>
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
    typename TagIn1, typename TagIn2, typename TagOut,
    bool Reverse1, bool Reverse2, bool ReverseOut
>
struct union_insert
    <
        Geometry1, Geometry2, GeometryOut,
        TagIn1, TagIn2, TagOut,
        true, true, true,
        Reverse1, Reverse2, ReverseOut,
        false
    > : detail::overlay::overlay
        <Geometry1, Geometry2, Reverse1, Reverse2, ReverseOut, GeometryOut, overlay_union>
{};


// dispatch for union of non-areal geometries
template
<
    typename Geometry1, typename Geometry2, typename GeometryOut,
    typename TagIn1, typename TagIn2, typename TagOut,
    bool Reverse1, bool Reverse2, bool ReverseOut
>
struct union_insert
    <
        Geometry1, Geometry2, GeometryOut,
        TagIn1, TagIn2, TagOut,
        false, false, false,
        Reverse1, Reverse2, ReverseOut,
        false
    > : union_insert
        <
            Geometry1, Geometry2, GeometryOut,
            typename tag_cast<TagIn1, pointlike_tag, linear_tag>::type,
            typename tag_cast<TagIn2, pointlike_tag, linear_tag>::type,
            TagOut,
            false, false, false,
            Reverse1, Reverse2, ReverseOut,
            false
        >
{};


// dispatch for union of linear geometries
template
<
    typename Linear1, typename Linear2, typename LineStringOut,
    bool Reverse1, bool Reverse2, bool ReverseOut
>
struct union_insert
    <
        Linear1, Linear2, LineStringOut,
        linear_tag, linear_tag, linestring_tag,
        false, false, false,
        Reverse1, Reverse2, ReverseOut,
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
    bool Reverse1, bool Reverse2, bool ReverseOut
>
struct union_insert
    <
        PointLike1, PointLike2, PointOut,
        pointlike_tag, pointlike_tag, point_tag,
        false, false, false,
        Reverse1, Reverse2, ReverseOut,
        false
    > : detail::overlay::union_pointlike_pointlike_point
        <
            PointLike1, PointLike2, PointOut
        >
{};


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
    concepts::check<GeometryOut>();

    typename strategy::intersection::services::default_strategy
        <
            typename cs_tag<GeometryOut>::type
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

struct union_
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
               Geometry1, Geometry2, geometry_out
           >::apply(geometry1, geometry2, robust_policy,
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
        typedef typename strategy::relate::services::default_strategy
            <
                Geometry1,
                Geometry2
            >::type strategy_type;

        apply(geometry1, geometry2, output_collection, strategy_type());
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
        concepts::check<typename boost::range_value<Collection>::type>();

        resolve_strategy::union_::apply(geometry1, geometry2,
                                        output_collection,
                                        strategy);
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
DL7OsgPkDhnMG8If8v4uyKOv7418caoOZx3Suys8lJOr6uedUD96fFzULVBHWXB+8AD5bmmkbecZ8A00vL8Xyk7IsnwI+LAk8srJkDl+e3GftQfSZtUv1kQYe5JuPLiUnVLEsRvKpDVAA+n2qtuoH/0MWZw5CfLoovp9cipjXoXehODhz63QEcgpBTs17Qz4YJWzL24D/wfH7z+inhlQHmhBeuc6AHqC/DMHeLXhMsPnicK0sJll5AXS+2vGQfq6QS/iq4K+cw+F/YCNmL8XvEUen8yDrdwRZQhoGSvreadp3DPwE107bAIdgQw2XRb8XBpl70lUdntUjwPvF4FbZSOkvwd8XQn+IS/7Ctogd6RhzA6x2zoroy6NevK20Omp9oQOQ25/TmiVy7Ahpy1khwL6F6R0Hgu6+imfk5+3US6cCvm8tAfSBfv7JtJ8YAF5a16yc+DN1IPQiw6yWZDxBjnY3B2AxT3F3PC7M/QR9vW3E5Fnl4AsoVMvH4G6wynQIdxngGc9OyF+6PmWVEacCJrXh32zr0NC2H+rLnGCrBtYZfGlxJ/JtoGOIbzo2g55vA3xTrE18vNKoGdS5CHI7Qcfur4f7Drisq9tIEd/NujPptCPPuhKGu8bQMagb9UNkTbo6q3ImwvA5kwM3TtmLuTnFaCTi4MX0JOTkU9X2Qh+8d4/BfgBGi+He3k6pP9AYPIIDzw7Hfqw28Sop6EMW2MW8GEz5MmTSY6UlkWh++OgrJx5VegDeHMeaNqrCL0B3S+3IR9WhurrfFvV1+MVj0u6ID7kmz7Y1aPAIx91i2I36EnDHhcgA6Rx8/kghxK+++DrrqgHI97vu2DzsvC7D+wUyr85FoW+QA+vmRF+ehDPQuD1oTr8/feL42pP0PplmLB5gf7dtApeUTm9ybygcRakeQA2KABfrLrFURPAPoK/d8wJ/k+F/LEMygOkYYYS9BW8fm9l0JIHX/PAwU4fESA9IeQB/ZsAOn0zaD7zYMhxOdjzjcDLI3S4z28IHYUd3Wd2/T4t2cgO5NM+2NT7FgE9O8A9izyO90uJpompnFpjHuicD5tIdcl8B27IdmBm5NXJrHo69Ghc2NPDTkI+gB5cBXpX3RX54qTYz0wr4ab6dgXhfoR0lKjd14X037I/2UXk06fWxo3ycEbQ/cBplLfht3gk7BXy9luUnyadGfcUSDOl9xXo8S87wT6jfOhGe+6U3ZGmkxH2aqAJuvRIR0zPkyiPHgK/kldLBeUMsCtDf149HG03xL/46cgHyBerkS68DJm2Ia8fj7j2WQa6j/TehzI+eb0CezEl7ELvOvi+PWiFbN9dGnq4MWSzOfIv9Gv8tanejLjmWFY/n3K6/oV9+f/6//ovrnHERh3tm3anOrfs2HCztTrFamKi6aCN40pLl0LW3GizDbvXUz422nitzlT3Vl2dYvHV27dYps6HNdYQ30wpxptue+DmAR4lwjc7ivGmnmK68YSuPfbm9OTxXDrjiW+ku/Q7sXTv9cvVinbbAW4HS7ccumrhL8IfLt0w3wpdfkK6peHvaOkWyK2ZxDfLiQmmmwC097RY2XwcFbCcW4t4Jemb2Q4g+dtvJhXjtMjSd3z1PG5LFvjJwRmZlorQaZkSaVmY0jKXrsykU7l0MV/YRdGSA2ZcuKnjfBHO4qBF8rHXpkXIGaLpbFbTQS+ahtXgHxxLGIJUd1eqY8PO9jGbdaXWGbvxZl0KOMQVIUi680T3mkTnnJrOVM9S4CG9jyPf2+L3ceX70vH7ePJ9Gc3L8fG539Av+bNKtSQPhc0uFqZ7V1O01LiAjrlreZQapLjnorgG2xA28abIDHs1CrugcJumqqVUj/g=
*/