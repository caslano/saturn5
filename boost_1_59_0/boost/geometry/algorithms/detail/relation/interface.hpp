// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013-2020.
// Modifications copyright (c) 2013-2020 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATION_INTERFACE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATION_INTERFACE_HPP


#include <boost/geometry/algorithms/detail/relate/interface.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace relate
{

template <typename Geometry1, typename Geometry2>
struct result_handler_type<Geometry1, Geometry2, geometry::de9im::matrix>
{
    typedef matrix_handler<geometry::de9im::matrix> type;
};


}} // namespace detail::relate
#endif // DOXYGEN_NO_DETAIL

namespace resolve_variant
{

template <typename Geometry1, typename Geometry2>
struct relation
{
    template <typename Matrix, typename Strategy>
    static inline Matrix apply(Geometry1 const& geometry1,
                               Geometry2 const& geometry2,
                               Strategy const& strategy)
    {
        concepts::check<Geometry1 const>();
        concepts::check<Geometry2 const>();
        assert_dimension_equal<Geometry1, Geometry2>();

        typename detail::relate::result_handler_type
            <
                Geometry1,
                Geometry2,
                Matrix
            >::type handler;

        resolve_strategy::relate
            <
                Strategy
            >::apply(geometry1, geometry2, handler, strategy);

        return handler.result();
    }
};

template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Geometry2>
struct relation<boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Geometry2>
{
    template <typename Matrix, typename Strategy>
    struct visitor : boost::static_visitor<Matrix>
    {
        Geometry2 const& m_geometry2;
        Strategy const& m_strategy;

        visitor(Geometry2 const& geometry2, Strategy const& strategy)
            : m_geometry2(geometry2), m_strategy(strategy) {}

        template <typename Geometry1>
        Matrix operator()(Geometry1 const& geometry1) const
        {
            return relation<Geometry1, Geometry2>
                   ::template apply<Matrix>(geometry1, m_geometry2, m_strategy);
        }
    };

    template <typename Matrix, typename Strategy>
    static inline Matrix
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry1,
          Geometry2 const& geometry2,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Matrix, Strategy>(geometry2, strategy), geometry1);
    }
};

template <typename Geometry1, BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct relation<Geometry1, boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> >
{
    template <typename Matrix, typename Strategy>
    struct visitor : boost::static_visitor<Matrix>
    {
        Geometry1 const& m_geometry1;
        Strategy const& m_strategy;

        visitor(Geometry1 const& geometry1, Strategy const& strategy)
            : m_geometry1(geometry1), m_strategy(strategy) {}

        template <typename Geometry2>
        Matrix operator()(Geometry2 const& geometry2) const
        {
            return relation<Geometry1, Geometry2>
                   ::template apply<Matrix>(m_geometry1, geometry2, m_strategy);
        }
    };

    template <typename Matrix, typename Strategy>
    static inline Matrix
    apply(Geometry1 const& geometry1,
          boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> const& geometry2,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Matrix, Strategy>(geometry1, strategy), geometry2);
    }
};

template
<
    BOOST_VARIANT_ENUM_PARAMS(typename T1),
    BOOST_VARIANT_ENUM_PARAMS(typename T2)
>
struct relation
    <
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T1)>,
        boost::variant<BOOST_VARIANT_ENUM_PARAMS(T2)>
    >
{
    template <typename Matrix, typename Strategy>
    struct visitor : boost::static_visitor<Matrix>
    {
        Strategy const& m_strategy;

        visitor(Strategy const& strategy)
            : m_strategy(strategy) {}

        template <typename Geometry1, typename Geometry2>
        Matrix operator()(Geometry1 const& geometry1,
                          Geometry2 const& geometry2) const
        {
            return relation<Geometry1, Geometry2>
                   ::template apply<Matrix>(geometry1, geometry2, m_strategy);
        }
    };

    template <typename Matrix, typename Strategy>
    static inline Matrix
    apply(boost::variant<BOOST_VARIANT_ENUM_PARAMS(T1)> const& geometry1,
          boost::variant<BOOST_VARIANT_ENUM_PARAMS(T2)> const& geometry2,
          Strategy const& strategy)
    {
        return boost::apply_visitor(visitor<Matrix, Strategy>(strategy), geometry1, geometry2);
    }
};

} // namespace resolve_variant


/*!
\brief Calculates the relation between a pair of geometries as defined in DE-9IM.
\ingroup relation
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam Strategy \tparam_strategy{Relation}
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param strategy \param_strategy{relation}
\return The DE-9IM matrix expressing the relation between geometries.

\qbk{distinguish,with strategy}
\qbk{[include reference/algorithms/relation.qbk]}
 */
template <typename Geometry1, typename Geometry2, typename Strategy>
inline de9im::matrix relation(Geometry1 const& geometry1,
                              Geometry2 const& geometry2,
                              Strategy const& strategy)
{
    return resolve_variant::relation
        <
            Geometry1,
            Geometry2
        >::template apply<de9im::matrix>(geometry1, geometry2, strategy);
}


/*!
\brief Calculates the relation between a pair of geometries as defined in DE-9IM.
\ingroup relation
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\return The DE-9IM matrix expressing the relation between geometries.

\qbk{[include reference/algorithms/relation.qbk]}
 */
template <typename Geometry1, typename Geometry2>
inline de9im::matrix relation(Geometry1 const& geometry1,
                              Geometry2 const& geometry2)
{
    return resolve_variant::relation
        <
            Geometry1,
            Geometry2
        >::template apply<de9im::matrix>(geometry1, geometry2, default_strategy());
}


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_INTERFACE_HPP

/* interface.hpp
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
*/