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
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
*/