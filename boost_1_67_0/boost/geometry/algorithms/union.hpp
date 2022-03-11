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
18o+VPNddPnPJFoQfqLxa0tKri2fYobeW/QhymXQTql+ANgNPaitBXhvqJUuZe+x8CtLOxIA7JM2A6Sb6I5Q+PAgla4H/pZ4nLAfwBjxhqgT8QjrdhkBooPyCjUN6ibZK1Xg/1b70gXEI/RRxO0tAPucuwfZJvYh5CfMVU68Bpr+ywl7S/FdYPzavF8lBP1qswUHlojnABl6K8C2yUw+gyuvR0LB176uwRvFgV9IOyJrnzk7WKO33qCHqt97c8wZnA/sxvT2wPpMi+m5ev/daRH9mgNCNf7JH/Tm/8/1BBbENIds/dn9X07og2r2IFP8fszgLeL80w1rr+7o7TvznnD0iqpfo6smwBekEu1G1fCdW+S1QBfMLPYj40erOtDn6nxVTJ7/g24+gcoXqD6fgu9jK+o1egsou9pBe+kDgJN4A/jGo4nPOjD1al7gDUF8yY9nGLh59052VQIZb5wrQzlRL7ceCf71oO0UP+l5FJhdd3h7eDvg3dK/9N3ghwqB2nL18+j2eiKN9Cj38oQPNqrtfL2KgXTTjnPkFbMSr/s+IPUWOQAJITi1j76o+Mb3fQSCD8n5b58puHxvnhUdPn3x3ul8EH39LyCmve7NrXrEfW8g/9WXXrfBLp4Gvhxb/mqT05Q16fV64bXKVXuM1wmTFaQi92R5mE3rB+2WYoU/v/F9v/vbwg/lhLLp5647MANq9kh0krRjP82Be+WPPhvCde2iQV20FVJm/QvWt+dpnX8VRrXNOXABIH3qnHgFXE0irM65Bhtv2R2h0a1wtXCMf4fV8a14vrO8YU2yHGZv7jXdbccZz1OZ8rYJHMDg4Dsg5BUuwZz3wihJsU2cXS1vODzSZ5Rpc45D1SNXM/QsurcdAvIwfa0IHob8rGz5qfaGlu6T5CXzY1jz53BD2C8GpF9GAo093p18mEiVtmT97ZOWMT7uzCkg+8z+t3JgwdjH8LXNMHy5kb3swnxNLSVHi6zbOPzN6NMBCXm7EBCAh5Ykj4ucj7nXFINPl0ldsVfy6CX1LHnu11nLmc7ICJWzu+v+O3y1bv484K8/s7bhh0Pugj1A1M1ttKTnhe4Ac2xpnrD5TegeFXuGEiTqhdjygTQP5k5qFdGeK1UizHtknhGZtonazTQ1BJ3Ze1v6LA6cApQ5ey6InpT+iqdNiUP7OVb5mE4KWrcorzHZphP34vy3RZLiBI9KT1Lppe+P953kQTnG8UgU9ByHW1trj6fjMQNy/Vk3J+2Xks/jpIiWD3EyAK5H/F8XlL7u3lSKCn/H6KXl/C9IpGHyF29q0GFKZNEMMwC350wAF8fhkfZWpIiWCTGdqFsP2g0O9jYIXQBiL/YPW8Ic82XTbVigTSbBAHF6ztRNhUeSHCB0eTyVao3jyGm757Czp3plf2uAcv3BekGkPWA00eFyNfRSzWqDabxkGzbTVmAR2RvN3glxZ/zRoevMF+rPeL9NK4GNmMcm7Ut7Xoni6UqFSnJFVDaa96Ks3KN4g7d407WVeH5JEAGdd3en0UwI2svTsLxP0C/MgK5APQCZ3kyghyRuCKQWn2l/MSRHj+ndm6dAiTNloXfkggfKfLTdenRgo73WqdJ6VNjjaeM5yvmCOQfZcslCtUQlo4z5Bur3tuZ/YYXyv6JMJaOQ+cZ/gzT/Cxn/vaPKIU5wcXIv82X74M7uNVwwg1aSFbHIBvtZ3Te5xPdwlu4zI1htwf21wfmlCB+ccr5xdWeQxWb5Rv/zwyt14PJih22866pl+I4kqkJAZL0DOo/Q3M7yXerxEX78IpMe/qmoY7yt709NC2apCFA2VXuDexuhs6oVxT5/5ZY/Pi84NuCET48e0UL+rWXznR4IVsGzZawjOpsquZEyEXyB+68pypjUR2BvbGyhZmzHnvDCNPUe6YjOzfbdsubSlZktjSXa4GwchvlRXgtWRSU2T6GxAgFDVcPnDdwrtR/BA4J0ZlNHgtrQ6XM6y9iGhEiZ9Wf88Hk7us2it2RLC7hZmNS9LL39yYqwA/KHMeS8AqmDt7KN7Z82ZkCMoiSdK0JSR8CE8xq3ksT9k5SC+dKyVF0lgRh9Vofm9dOwiklDS9W4s17bxO670jFoq/+M1dP8q7F46TEB7TkW9FAjdfQ1m465CKH2jU4mZ0Ou9OPl8/ySxmZQqyfYRsXudcROaXcHlOMjaTSBAZ72xPP7ODITR8TzXBb3EeQPNsACU+aznrcraSciM++Q351XiXJff0Jtwd9HPomAp+6SzktPbn++JhsbkU9nWKsAHlJDPD6oyFazL5LxpJK9ZyFe9jhM546ewNpFrbaJ5i3zttsOkNAbVy9oFfk01w3mDFKOf0NSxbXVUHabD51Bq5Ns98/Y04oj7ihse6PAJc1yQLBv3q/1ZCcjJTkndtx160LH7WCXjpdOLwGpIEuD/aR+ZscyzHds3fOXTVuBLWL8HMJnQ3wHH073CqQAgLjjp87ggoHUtUSFEveRMtgl7K7QL8KVZk9Uc6GmfZMafD7B6qqVWgyriQ+sjKEXMRS96bxmAj9Tsx9sk6OyPq6MQG9lHPfEe6V85B4Z+tViWS0pIHvTwEKWrE9a3BtnkOXrVRjJuctSJZUNfOdYtZ/lK2SIyqSyQZroPk2SR+b9zBAQ/KbLxZSFuXZRuwTxp1oxX9UiCTzliJ0o8jT4z2MA6g4rSUun9KoGjf19Qps0VPIrM91vHYKjA0hbGYLtfA7pnFYl/QtbmBJfkoPwdcvZrrO6VhtBzucBWILoM1ez9z+w1fwNOyWX6QnWBR1Gk3yzh6l8+9CcMXdfkXdiji139FuGdHzCE9XF9QK2NYPmipvVFVTXaCuKRDpzkraqaPvNOAyOLEmvEAO6ci9M5JE+lm9VjVMmbnF3NhSrODFc3VAzm/t/Ma69yaUQgwlM3B/0bMqrZIKtBL1bAdHOjXxCe8uaxnV6WyAY9msiauywPTau7YJ8C7NLrSpZwecA/EuHowxuDsO2+7/D843ZdYAWz1eCo+atteo2PS9rQpTrPvNwK2PvPzVXV83BpTbAXy0fhy5yNWt5Cw/c77jFfssg1uzhrw5Qy0WqflP5Mu4WSwQ+IeuTOX2Bnv7kpuJiOxXO5mAEfgGX8i/tM7sEJaQvSm660efRw8dYn/O2gui8UrXd+HMjjz8BtwKpoY9/YZPrlixDbSxm3DlyED3ZJaw7dPx1ffHV/nAUWLy6B9oa0brRh49jQPgdbjY6EXsDTnK7dMt6n8WSRMzXvkqnmoNOj5LKeacqUd/1weefc1os+TcEHU5jc4P9S6dyPDXtutSC9l81ba+KsK6ERmPSd103o6sCfb2vzQSihNa6u5iM2oIYAdTb86Neh8S0gChk48zQC/aTU/wNCRTc/Q61pz2OlMrT2GrH8YX3jiUN5tCGnZ6/ySeCBNySrj+oK21KlD/ZW1Of0GQuwn+4WzOeNUMxmdb7gG1d57lvwo0ESdtc9c49h0ZvqOfbzuGa0BZ0H6tMHXBOuv+4f8YwgRKku6VNaBKU8ezATo/h2/7wWeSKqEXWIV91fRcX6uwhtBGhorf7d1hD0C0z3LhQSUi/zakr1FA52eJxWKwf0drfoGwhMTmq3/bzo/y2E8MlHu+pe7WTU7VXI2KWTOyXF5AlkyPAblmwnFQCYYN2R2mhXCbNE2nbYFAdZbiQrxtZbOyxZSLj+G0oVp6nOKmtsKedG+9SH2/JmewSShyvjUlqwdudPHnFyzov+7CeL7CB/G/OvwY+u66TFM8WKfNTkeQMh6fh+q3JCHz+rE4DjcbhVUQXsxdvtWc6s5NYjB/WOYCB/Ue9jubXKA1r+pHUyOvTy7xbC3+o0sgEskK6O75UmfYXKF514ZrHGb3tFn1P2bPYhoVFnKkNQXfAov5Lx94yDuXcR7VpbQ6NraGYko41OuveRIX858bFlJRzR64mZiTGX1pEm35gPJRpiX5E5Fk8amnTJvos+RKOE81dp8SBOwsP68zG5L1BYBWfdxjL3GziAkiB3YxgmkwfHxcIRxoFLDTrac0D5Xq24i6JxQw1fnALT8TfdMCyDE3FiCFs1EjBZEaWEmYPoOXj6+vLvw0EJOBb4Legb8HfQr6Ffgv7Fv4t4lvkt6hv0d9ivsV+i/sW/y3hW+K3pG/J31K+pX5L+5b+LeNb5resb9nfcr7lfsv7lv+t4Fvht6Jvxd9KvpV+K/tW/q3iW+W3qm/V32q+1X6r+1b/reFb47emb83fWr61fmv71v6t41vnt65v3d96vvV+6/vW/23g2+C3oW/D30a+jX4b+zb+beLb5Lepb9PfZr7Nfpv7Nv9t4dvit6Vvy99Wvq1+W/u2/m3j2+a3rW/b3wDfdr7tftv7tv/t4Nvht6Nvx99Ovp1+O/t2/u3i2+W3q2/X326+3X67+3b/7eHb47enb8/fXr69fnv79v4N+O3j2+c3kPbv/Pu7r58kue5JPjc3u2ieW/Um65PNfXcC94J9Z814bwwyXiWeL4/wKjD2epTdcBWJfCzonU+LEXHXbLM0TXfbvb4UT9sy9zVdn+sD2fWWJcFP5SEfsdoa8PJT76uuSU+Bu7v0ay+6Us58caPu3Axzy4BwvFQTc2VshDvfjo974BhXiSeP207p9Aa3lusgeaSe5ZlS+JyUM8T/9FuljD6XrmIaW75ZtJ15idTO6IFA7Fdfa9WdivnlzHO3wFIfrJv8aiMCsD0Ss6M4lPKLE6wJL9T9fWpqEnWoEiW2GbMrNiqi3P269vLpqyQ6MzJe3vLDpG9N3XBspQa3MT7Q+KV0sifijnHU4jy5W1k+xiH6ilw5cWuctAQwgtPoyETo50zbJwml1xTu6utJ28/12w7DZCt9QWybECJ/18mKYyDRM3UcAphM4ORD9wUvp/6eUeeikt/E+n6Fb7biqQ1/w/Vi6Sa2PJuhwxVFp2QwZvrP6s0Ht8cf7zQe5l1CV/D1KR7Hq7Hb35wGQMo7XcVU7sosWF4dPYFWNwmXTcmEyDLdgHlPF7RgDp/ScY3k9wg9uUJ3ESz7Fr9ZgUqx0dd+5f2TYGWZ+YjHe/D+3aLfG/8djW2HLv5RtGpp+Fl8jcbWjz4wR9YDsU+uB3fheIBCEiCO9Fb1HGj5bK7T0RFwLluWzL+Yxv+w78bFtfzbsgg//Xjr08hD4F3k0q9hF+1knPv1ViH5vrq3MU0camuNOL+NWR3CZb4qP/waEFzblLwqdC4zZxbWTI+aT59OmRQFtDjviTq7lq78Yi//OkOt/uKv+ZRpnBc7FxB/tP2u6pT7bkAv9+CPGPiV+uL2UKiGN+onjuhp/8G92mU64dpll3azXp1mXDkwtJ7dr+Wvg/fAq/6ubh43EUs9Y4idr+zXEtd9Bih9NS1U6U6eQ09k0Eydq6fW8IzmSHe7GnZjTLakHbUU01QZ8nbMXFJeiH/8649ySrDOKRlaNoEVr0MELXUVU9QN1F4zV7eoFNi2srqeUj+l5KJ7TmlnY5x/dTGRAYSYeye5aYVzarHCZwxS3GG38sxR3CL1t0PoPxqz0eke8dpbAxY/BB489r2zq20fVqzKGQR9nZ9wqyiba7NXHcHe+dcppU9DncsmJCh49AAgSx4Sad5EXpaFAzHl+kKDqlPiH+Sm4CfL4G7oXigjNj4q6yAKkSEVdipTJGuKY/SfPhFlliWqqlBPLTneuuHdU37nHWFnmjsrK9X/JR3UtPT+xdmaXR7Lt/AzXYFRyIWXrO8oF4ccOHdMvjiHUUCJZMCec0rplddyiyj/1OeuBv87R2F462cOBUx3UuOvD4WgAl7TEAeVj9OLEn6T98rLxiombca1M51GT1zyvTWI5cAmPuPJhNDusebSBHsKAOyKe3twXlAM8RSt55vPEcR8d7Em+hRA9BXR7VWzTVjAPNXnk5bKt4lPvOC9VBVeRSOLgqHGJ3JB6M6iwxUqaO6+PCYy7fjt57VQGUSZ5J1qlYdBwur+5a43i6Fp6NmFN/TThrsav1GPNp0e5Yat5yXBrUjq8wLye9Xw8f7PL+ZDXTNnmS5fJtFroVKXLu2L6AxmQ6Xi+Kjpi92v2LcbNC92vyefnzMG3sHs8ReuPp9hi7KBJmZs6eyi5lDC6RsV7siPjyYvWiqazBpdzuTmUBW9tnRY11/xLd2JL1Ug+yKYIb+EWct0T/+mOmEw+sLpirzJ1jOqApwTvXswjrUInz7u1b0RiCUbqqSb4mdwPUd5nyhKa8SvF5IU+j8T5F+JrnjyvUhXKN+i8foWxSqu1Hmn3Y/1tx/9+CIyzRYeLt7Ghc5IOZ/jL97EkOZDAL87PpEnn3f/aX/97Ew5y47+fk1uZdJbcW19Y2k9h98OMB9ceq/uJZAm9VJe1D3/nO/pf1NytPMde1ln758YHLFYS1ntdbdcS3EjPOqySH9HKb4wp9aO0QHsUdpHdr75DKrHd0qaQiOnbLW6uJCangz3jPmSV2xU0o+kt/d357YrNzRU/TmrObL8+Ysy4yKlgN+xoUq5Kwb/sclIM8iV8bas8qGwKIF0TQPo+9xnrnTPGaUY/Qw3vMpdNq1VTWLdCHXbiK/ZA/919mfTug+g/fIFCdT0/qzb5fCd1XGdEtc09V4MHD5aAak7r93hcS4PXEaHacy22bkXPhJx+kdJPeOgNtSCWP2nuzbzoXCByYd+Yxk92GZk2cxc8VoC3YwgMVTzOk81vVHZKvVzJuzZD/IXvfE5Qs9zV5rsSdkK8eN7tOHTZQcBTovOuXu5bgjeoevoI02ZUSlXfvZlZzLnS3kI9pkx5Hsb3mEr+o0KUPO0PCXWWmSNuuPC8rcHvEPX8uWC29kfi5Pe+vPapjO8K9BEe4UX1WwdII5Re1fWpRX4Q/dESe1W075Ml0L5dtEcbUYAi4WuvbI1XklbQdkTpFqo9WwJX+NHq5bx5GewDrQLD595PgYfQCqxHSz53h0tKKNq2abU3tBOuxJa7NzMC/gkIla2jlVF+tmWZZTFyQZeHQl/APjVb7uP4JFYeqXmWS84k4JwJNIw2C2cbuqUzgumHJMItY917Vt46RPo81ECPz2SnIUoJT9wSkyHpV7UW7ImOUpcMAvPEbH8oNJnnQWV5POlPvHH2MOX+srvQoXfVML8KFOWR4JmrV+HsVquIJ+w2HgsB/uAp6CrSdKPb/bFVGIQYBLqe6h25Xruln1A5I5is3h1cnH0ZKLHfzqpQZEYL810J9vAxahFwfWgpREh+ormHP24rrORjExQkO/dQ932tGAu5zq6nj4P9NhJ9a6q0GPbg5MMPO/ix55MWt2X0dRjfigusL2kCmt+0ICum3xN4LfFoAzaPAnWLwwyYqN5KwUkENRd65hf93avrt3B0cH8wWpiycWJfDVoHnVtBqrOQrVqn0W1otsVUaK/sT2joIFbRo4wa9SsXxKQepcL37dFrB/Xsg9lh5EXk7Vd52B27LknA0Tpth+ucvxw+mvi4Mlcgsv4y76Gjt0gMRY5LTw+eSpqcOhzMGANlmiXDgbS/RZIMH6L6ZIKTxUAMVzDOD0uWYZGSptp27Lp8uxDp1/gPjeMAJdX6AT5p6OWF0W9beus51nkEYfMPbcquS7ndTIRTA5o8cTqVRFe+mK0NxXG0jKQPmE7EmHKhpawU9v5sQtbWpy3n03yGqWXUpaD/8Z92dTfNsvqkblRy/lyQ9SuHa6Dn8j3Lnh92nx696XlL04IojYAIlcNgBa4TUWhjOLU+9PnjvcgEwuVUd6YNB3aAw9mo+dH+Kizp4ynlw8FoFO8RtxgAmQqLUag6gPWzB3TMuUwX9vo6VGxysgIGyOV5zlK7AP6Htx0htDdEIpneMpldPeCphTwT767viPUcl22K2L4dkXlKxHm34LFyc4lQoixsJAwxAqXy2Fb/mFl/BycOoxauEqEJ3Y50o4MY8sxfU++7abJYZ42j0Dz4t7r0KcIbA/9IBzLQ/Vh09EalgAPcScIZqyphBIvrWLquo/lyCIAlAyXgxes32NLhsrikR7AS1bRm49jP6vxSAXXXHnmvs75wd98j6/RQ8S+e1QjW6ryNerGSocYuJVZebl8zG9zmxRbpQ42j7Y701LV6lNlCnMdZRYYf/8YztcBdq1waP0K15ngZMgl6WmZnmGuI+AdUVfjLo6ARNiHLAcZ2o9d95ksezcJHVMKN045x4R113nk/NWy1LoeZBxn0sq+l1O60Qx/2/J/GHunZmF4Lkh027Zt27b3s23btm3btm3btm3b837nzA+YXKSSdGWtvkhVuqtWJYh/NcQzrEHUhuq1yvU5bmruykXaT4cE04J8XQlx2fkRuzv6qjA/5laxL+GIlzoZerkz+a04paI5Xt8glljHuRmarmsyDwq3yCUlfKEazY2zSHF8sH5dsXdIinhoRdMGzxp6Y3GHTEomP4RqRb8I+HvRPpwcc93qdRu2KXWjQVCDYFxUJPuHzeW8wGYDYFcpVDUHtrAOduVxThorv1dV9t7kfjEkEg5Qf1sfzhmcyHRPqDVwm+hJScW1SeTUuR1L0/sl42dGJGMU+jmTVpaQXi+WXCuLrnXnbvhTgQ+8sZSvIrNNa/snrHPjfNLMYr3SmkXfKRzi3IjENFspoG1d3ljMzsk8OSYzoVCJZqaZLcvHqCyVHyMXRBZ8ZCuGxouoJIg5HNsc4E8GY/zQ767+3e0WU/ve2fV4K9ZfHiX8LUITRFMUxMEVqOTqYUlT4utSOa1dPZq584kjUl2jynYzzvq5Ri1jQkDWe9B6aTG7mqWmG5iQ/zltl4edJHYgvakOM+qL0SYYGjL4HF9dVMs6wbkmoDpOS+c5uNbVajaTVUj6xswNJF0zJtSLOpwOZLk26+iT6lQoUvZC48UQ3un+bX26tVAP1pf+PF4nBSkVdQyi2nlrpzu0BvKE1A2Zv6m+FPK5TZAfjZIZRPYD0i1Wdk/2BeshPWwEW43hF82JhRrjk3W4Fl3xSZW7HWmvjzBOHS0QZdg09xtKsEvVCl/qkpDtHPoJFWs36Bt1DCz7lpgm7x10bPInDeOzxlTq0mqb/pr2k3EN9D3XWuu4lvWcJJP6cvRILUAz5jsKTemU5mVjhpX7VKQvpmMPGNi/8NpPg6vnD9ZNzhkoj5iW1U+meC1I6GYkZxDPspM63600leZTqS7lWe4DrVYcohjHvFZKGKgqWe0kN+I7IxcX0J2tm/c=
*/