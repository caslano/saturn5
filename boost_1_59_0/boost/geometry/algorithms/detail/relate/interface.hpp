// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013-2020.
// Modifications copyright (c) 2013-2020 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_INTERFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_INTERFACE_HPP


#include <tuple>

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant_fwd.hpp>

#include <boost/geometry/algorithms/detail/relate/de9im.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/topological_dimension.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/strategies/default_strategy.hpp>
#include <boost/geometry/strategies/detail.hpp>
#include <boost/geometry/strategies/relate/services.hpp>
#include <boost/geometry/util/sequence.hpp>
#include <boost/geometry/util/type_traits.hpp>


namespace boost { namespace geometry {


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace relate {

// is_generic allows dispatch::relate to generate compile-time error
template <typename Geometry1, typename Geometry2>
struct is_generic
{
    static const bool value = (util::is_polysegmental<Geometry1>::value
                            && util::is_polysegmental<Geometry2>::value)
                              ||
                              (util::is_point<Geometry1>::value
                            && util::is_polysegmental<Geometry2>::value)
                              ||
                              (util::is_polysegmental<Geometry1>::value
                            && util::is_point<Geometry2>::value);
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

template <typename Geometry1, typename Geometry2, typename Result>
struct result_handler_type
    : not_implemented<Result>
{};

template <typename Geometry1, typename Geometry2>
struct result_handler_type<Geometry1, Geometry2, geometry::de9im::mask>
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

template <typename Geometry1, typename Geometry2, typename ...Masks>
struct result_handler_type<Geometry1, Geometry2, std::tuple<Masks...>>
{
    typedef mask_handler
        <
            std::tuple<Masks...>,
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
        geometry::de9im::static_mask<II, IB, IE, BI, BB, BE, EI, EB, EE>
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

template <typename Geometry1, typename Geometry2, typename ...StaticMasks>
struct result_handler_type<Geometry1, Geometry2, util::type_sequence<StaticMasks...>>
{
    typedef static_mask_handler
        <
            util::type_sequence<StaticMasks...>,
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


template
<
    typename Strategy,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategy>::value
>
struct relate
{
    template <typename Geometry1, typename Geometry2, typename ResultHandler>
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
};

template <typename Strategy>
struct relate<Strategy, false>
{
    template <typename Geometry1, typename Geometry2, typename ResultHandler>
    static inline void apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             ResultHandler & handler,
                             Strategy const& strategy)
    {
        using strategies::relate::services::strategy_converter;
        dispatch::relate
            <
                Geometry1,
                Geometry2
            >::apply(geometry1, geometry2, handler,
                     strategy_converter<Strategy>::get(strategy));
    }
};

template <>
struct relate<default_strategy, false>
{
    template <typename Geometry1, typename Geometry2, typename ResultHandler>
    static inline void apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             ResultHandler & handler,
                             default_strategy)
    {
        typedef typename strategies::relate::services::default_strategy
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

        resolve_strategy::relate<Strategy>::apply(geometry1, geometry2, handler, strategy);

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