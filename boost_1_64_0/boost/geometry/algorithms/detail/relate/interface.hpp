// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013, 2014, 2015, 2017.
// Modifications copyright (c) 2013-2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_INTERFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_INTERFACE_HPP


#include <boost/type_traits/is_same.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/topological_dimension.hpp>

#include <boost/geometry/algorithms/detail/relate/de9im.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/relate.hpp>


namespace boost { namespace geometry {


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace relate {

// Those are used only to allow dispatch::relate to produce compile-time error

template <typename Geometry,
          typename Tag = typename geometry::tag<Geometry>::type>
struct is_supported_by_generic
{
    static const bool value
        = boost::is_same<Tag, linestring_tag>::value
       || boost::is_same<Tag, multi_linestring_tag>::value
       || boost::is_same<Tag, ring_tag>::value
       || boost::is_same<Tag, polygon_tag>::value
       || boost::is_same<Tag, multi_polygon_tag>::value;
};

template <typename Geometry1,
          typename Geometry2,
          typename Tag1 = typename geometry::tag<Geometry1>::type,
          typename Tag2 = typename geometry::tag<Geometry2>::type>
struct is_generic
{
    static const bool value = is_supported_by_generic<Geometry1>::value
                           && is_supported_by_generic<Geometry2>::value;
};


template <typename Point, typename Geometry, typename Tag>
struct is_generic<Point, Geometry, point_tag, Tag>
{
    static const bool value = is_supported_by_generic<Geometry>::value;
};

template <typename Geometry, typename Point, typename Tag>
struct is_generic<Geometry, Point, Tag, point_tag>
{
    static const bool value = is_supported_by_generic<Geometry>::value;
};

template <typename Point1, typename Point2>
struct is_generic<Point1, Point2, point_tag, point_tag>
{
    static const bool value = false;
};


}} // namespace detail::relate
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch {


template <typename Geometry1,
          typename Geometry2,
          typename Tag1 = typename geometry::tag<Geometry1>::type,
          typename Tag2 = typename geometry::tag<Geometry2>::type,
          int TopDim1 = geometry::topological_dimension<Geometry1>::value,
          int TopDim2 = geometry::topological_dimension<Geometry2>::value,
          bool IsGeneric = detail::relate::is_generic<Geometry1, Geometry2>::value
>
struct relate : not_implemented<Tag1, Tag2>
{};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace relate {

template <typename Geometry1, typename Geometry2>
struct interruption_enabled
{
    static const bool value =
        dispatch::relate<Geometry1, Geometry2>::interruption_enabled;
};

template <typename Geometry1,
          typename Geometry2,
          typename Result,
          bool IsSequence = boost::mpl::is_sequence<Result>::value>
struct result_handler_type
    : not_implemented<Result>
{};

template <typename Geometry1, typename Geometry2>
struct result_handler_type<Geometry1, Geometry2, geometry::de9im::mask, false>
{
    typedef mask_handler
        <
            geometry::de9im::mask,
            interruption_enabled
                <
                    Geometry1,
                    Geometry2
                >::value
        > type;
};

template <typename Geometry1, typename Geometry2, typename Head, typename Tail>
struct result_handler_type<Geometry1, Geometry2, boost::tuples::cons<Head, Tail>, false>
{
    typedef mask_handler
        <
            boost::tuples::cons<Head, Tail>,
            interruption_enabled
                <
                    Geometry1,
                    Geometry2
                >::value
        > type;
};

template <typename Geometry1, typename Geometry2,
          char II, char IB, char IE,
          char BI, char BB, char BE,
          char EI, char EB, char EE>
struct result_handler_type
    <
        Geometry1,
        Geometry2,
        geometry::de9im::static_mask<II, IB, IE, BI, BB, BE, EI, EB, EE>,
        false
    >
{
    typedef static_mask_handler
        <
            geometry::de9im::static_mask<II, IB, IE, BI, BB, BE, EI, EB, EE>,
            interruption_enabled
                <
                    Geometry1,
                    Geometry2
                >::value
        > type;
};

template <typename Geometry1, typename Geometry2, typename StaticSequence>
struct result_handler_type<Geometry1, Geometry2, StaticSequence, true>
{
    typedef static_mask_handler
        <
            StaticSequence,
            interruption_enabled
                <
                    Geometry1,
                    Geometry2
                >::value
        > type;
};


}} // namespace detail::relate
#endif // DOXYGEN_NO_DETAIL

namespace resolve_strategy {

struct relate
{
    template <typename Geometry1, typename Geometry2, typename ResultHandler, typename Strategy>
    static inline void apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             ResultHandler & handler,
                             Strategy const& strategy)
    {
        dispatch::relate
            <
                Geometry1,
                Geometry2
            >::apply(geometry1, geometry2, handler, strategy);
    }

    template <typename Geometry1, typename Geometry2, typename ResultHandler>
    static inline void apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             ResultHandler & handler,
                             default_strategy)
    {
        typedef typename strategy::relate::services::default_strategy
            <
                Geometry1,
                Geometry2
            >::type strategy_type;
        
        dispatch::relate
            <
                Geometry1,
                Geometry2
            >::apply(geometry1, geometry2, handler, strategy_type());
    }
};

} // resolve_strategy

namespace resolve_variant {

template <typename Geometry1, typename Geometry2>
struct relate
{
    template <typename Mask, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Mask const& mask,
                             Strategy const& strategy)
    {
        concepts::check<Geometry1 const>();
        concepts::check<Geometry2 const>();
        assert_dimension_equal<Geometry1, Geometry2>();

        typename detail::relate::result_handler_type
            <
                Geometry1,
                Geometry2,
                Mask
            >::type handler(mask);

        resolve_strategy::relate::apply(geometry1, geometry2, handler, strategy);

        return handler.result();
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Geometry2>
struct relate<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Geometry2>
{
    template <typename Mask, typename Strategy>
    struct visitor : boost::static_visitor<bool>
    {
        Geometry2 const& m_geometry2;
        Mask const& m_mask;
        Strategy const& m_strategy;

        visitor(Geometry2 const& geometry2, Mask const& mask, Strategy const& strategy)
            : m_geometry2(geometry2), m_mask(mask), m_strategy(strategy) {}

        template <typename Geometry1>
        bool operator()(Geometry1 const& geometry1) const
        {
            return relate<Geometry1, Geometry2>
                   ::apply(geometry1, m_geometry2, m_mask, m_strategy);
        }
    };

    template <typename Mask, typename Strategy>
    static inline bool
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry1,
          Geometry2 const& geometry2,
          Mask const& mask,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Mask, Strategy>(geometry2, mask, strategy), geometry1);
    }
};

template <typename Geometry1, BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct relate<Geometry1, boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename Mask, typename Strategy>
    struct visitor : boost::static_visitor<bool>
    {
        Geometry1 const& m_geometry1;
        Mask const& m_mask;
        Strategy const& m_strategy;

        visitor(Geometry1 const& geometry1, Mask const& mask, Strategy const& strategy)
            : m_geometry1(geometry1), m_mask(mask), m_strategy(strategy) {}

        template <typename Geometry2>
        bool operator()(Geometry2 const& geometry2) const
        {
            return relate<Geometry1, Geometry2>
                   ::apply(m_geometry1, geometry2, m_mask, m_strategy);
        }
    };

    template <typename Mask, typename Strategy>
    static inline bool
    apply(Geometry1 const& geometry1,
          boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry2,
          Mask const& mask,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Mask, Strategy>(geometry1, mask, strategy), geometry2);
    }
};

template <
    BOOST_VARIANT_ENUM_PARAMS(typename T1),
    BOOST_VARIANT_ENUM_PARAMS(typename T2)
>
struct relate<
    boost::variant<BOOST_VARIANT_ENUM_PARAMS(T1)>,
    boost::variant<BOOST_VARIANT_ENUM_PARAMS(T2)>
>
{
    template <typename Mask, typename Strategy>
    struct visitor : boost::static_visitor<bool>
    {
        Mask const& m_mask;
        Strategy const& m_strategy;

        visitor(Mask const& mask, Strategy const& strategy)
            : m_mask(mask), m_strategy(strategy) {}

        template <typename Geometry1, typename Geometry2>
        bool operator()(Geometry1 const& geometry1,
                        Geometry2 const& geometry2) const
        {
            return relate<Geometry1, Geometry2>
                   ::apply(geometry1, geometry2, m_mask, m_strategy);
        }
    };

    template <typename Mask, typename Strategy>
    static inline bool
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T1)> const& geometry1,
          boost::variant<BOOST_VARIANT_ENUM_PARAMS(T2)> const& geometry2,
          Mask const& mask,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Mask, Strategy>(mask, strategy), geometry1, geometry2);
    }
};

} // namespace resolve_variant

/*!
\brief Checks relation between a pair of geometries defined by a mask.
\ingroup relate
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam Mask An intersection model Mask type.
\tparam Strategy \tparam_strategy{Relate}
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param mask An intersection model mask object.
\param strategy \param_strategy{relate}
\return true if the relation is compatible with the mask, false otherwise.

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/relate.qbk]}
 */
template <typename Geometry1, typename Geometry2, typename Mask, typename Strategy>
inline bool relate(Geometry1 const& geometry1,
                   Geometry2 const& geometry2,
                   Mask const& mask,
                   Strategy const& strategy)
{
    return resolve_variant::relate
            <
                Geometry1,
                Geometry2
            >::apply(geometry1, geometry2, mask, strategy);
}

/*!
\brief Checks relation between a pair of geometries defined by a mask.
\ingroup relate
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam Mask An intersection model Mask type.
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param mask An intersection model mask object.
\return true if the relation is compatible with the mask, false otherwise.

\qbk{[include reference/algorithms/relate.qbk]}
 */
template <typename Geometry1, typename Geometry2, typename Mask>
inline bool relate(Geometry1 const& geometry1,
                   Geometry2 const& geometry2,
                   Mask const& mask)
{
    return resolve_variant::relate
            <
                Geometry1,
                Geometry2
            >::apply(geometry1, geometry2, mask, default_strategy());
}

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_INTERFACE_HPP

/* interface.hpp
KPoEHTNr5CyltJV9twxXB1nGbNHppmYa0ZHSkbsN9foz4QnwcCLH99QBwHyuAsGr5nnCuVxUTLaan8u+2Sbbn6gQi/7ddj/fWMl8QD3CHcqrHx1VQkmta1O5fcq/Ki94tfmhPGEZYXQlsctCyYuG0W3g6BQaqMKEkn9jMdpX3nYh2ni7EzVjsmdpUlaD+NRCIAKxu1jyfsPs9Qk8ZMjKdcvUsS1CzL3e8K2k3CfM55x/7H5/G39Zgj9y8ow2fn8bfxv460X9dyj/W0/Qr/GsUYE2VrdIL+XLjUqIwuQHWYxDQ40Th7S9RcJ4HK9mmeMJKtJdhXRAE803zz/DjNbBAOL2JKsthsgdq7V/kJxufG81v9fmr23j/3v9T6lOSPyJ7foSlEzx5Pz+5+b1mymVnZN++FlQpOuCd+sOEAlSHrvDs3yCWCDCkjv+RUmIvQcfj+nbXSNaYMIQ4RtTI3Dn0afrt9D9gXSvkpTI2+EzfiyDtjM6dpRwt8joo/P4VrjXiQinjMjUREQ3EdHCiKZBIsItI744kREHEAFmSNH5ifUZCdNXwmwVMK0SJt2E+a2EWSxzfkDAODhqqmRElYy4UURojLhURuRJrAtERBIjTmeEqrZz8HHetclSe+z0ExWNArvLEYO/Li/TP+KH+amxzXzVYvfzgNxJ986MOP1Rb3l9R+lvaZM+S+OJysGUqfBKUTvOekufOcHb8j9Vmfp+dpj6JzYO7ZBjSpUnT5RnTP1XyqfXK3I05teu/1c8bi9HB/HWsGov755f6Lm5tj7O/7VM8VvViK1MAAJgPPDI3Uwn4wKeMbGPKY0WiX1M/xLsYyjpIpIeiCyR25Alu839semOrGCMAgD0V2+e8cM+jYlLOYzvEQMRyRWR/q3iNO/NKyZRWB0u6xpDJ/kL6kK9ApHupSzKDUwKiymwhZeJGbKYEW3imTIzgOtLXRW3isHtkFTApvAiWhZoRTt830DEQRv5O3JuP1ApWgBT9uC1ZXLkacdBnPCbA6zb7CzMz7tyXVK0Iu8dnrDdO5QNNJWU/7Ae7yKLV6s1smHxI5aLPYK9Kdbrp08kQcQSe5DxiyORgVRoKLaoyKRKZVLeNpPmASRs+LGcMc4BFMd74YB4zm1nz/uPEgtUhjlrDD+SCNidmiGms56J/sHThDwPPbDUrr/nbrXGjXCJNe6e0ab+nk+MfgNs+nu8eUJiA+6D3VTfc8e4r1bfY8o/S8gvT+W3SOaXb+X3mnFPf3t+M5FfuZXfsV8rP6n/Ndxuvpk2iPPN350PItejtanB6u/Gs3fIq9QO+F/Dpn4TNqN9JaV+k5kDv5t+E1OU0d4l1v5GKQ87k51Tv2OOYqvuLxdtChRA3rIckhH6tQGWljFjlEhU//X0ayqO8PqOynPBElMUAkFMFa0jqbcjlGXcc4XQXzOQY6BsoXD3VOzxirfdOBbBpgwzHYxF09zBPgR3S/A0WxHJrTksoC+Xn7e8zeftR7fRl3NMR/RaQijG+9UsYWQd3Gy6f4ROUbM/cB/qVFiheInvcfVf/n5j0n9WiEqryNdcospKZu1GrXmufRmRlKwhVcQPOdYlGeC91WtdShCcsacfedfAh09+rcdF8MMK/ouRmAs3HSamKgZxqhqDsfUWwoVMQEDXDJXbXrwyeo1CwHLTenGCJDa4xAO3rO9jz4/kBHh9pRMlj6VRL9Y0r9sMoXj1WwvUqGx+6HxfBHcHyJ8lm+OWob8WmJEVcX+HjfBXt8dKW3usYnt8nftZ2ZNvX2Tdy5Iotyn3DfP+UO8jCAkOE5IK+vmgLF+IEzAeF100OCBWHz6QOvc1S4DYxXaVnYy7/M+yHt7Z9LV+iv97UZw=
*/