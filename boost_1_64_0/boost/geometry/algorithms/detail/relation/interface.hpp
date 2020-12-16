// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013, 2014, 2015, 2017.
// Modifications copyright (c) 2013-2017 Oracle and/or its affiliates.

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
struct result_handler_type<Geometry1, Geometry2, geometry::de9im::matrix, false>
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

        resolve_strategy::relate::apply(geometry1, geometry2, handler, strategy);

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
fpfXmV4sj+Cn79mrMMLY+ByBEZo7gRQCretIS0UKKwVmt05idtg9vPuFatZIj1Ug2iF46PKR9vFO51LaGF+TxnrP9OQbs+7no5khDvULpOgYZMVq54snf47RO3qPaKSMfH94pGerL7pisYg66EAzY8bscwiss6kxC6bGjFmnMqJwXcB81a+3dTE3ZvTOoPybMbdD59ejPbKSK8SOfVJ5rMyuFutUC3NwyH5+LRey4hUUgghWC+yM7/VCJG8S9Y2rqRBdmlYk8SSFziJhvVt5+CFTrZpP+YHY8DTs3J7EjwlO2qhnWsZjGGWVSy76wHcV3pu01UQxf+Fn2xSIrdccOcRfYoWmlMcuGCZ49U9b9ZAeAJBLzbnS6f7IS0LFjtd9Sj9PsG5nEsqvzbVtwMRn29uy7ggE9MGjY43tRRGeo/G46nbQU19x9ZBrbVE2IU2YKK22tnyAUUDuPxKamaoGUc3GbycJW+V9VDjR4XDTMByjrbcfcVBx01NsBPOcYbRX5L6epaJhbNU+aVhTlB5gn9j4k8W8FTtPBxOOs4mjDNFdmijKhmjtIN0OR0i0toivNPz2nhi6eU6NDxGg0lnjbLdMM6CdGW7gVr5zgaBkJJMfnkz+UsqRw5T9Bsg9zNKcaO06F1tNDOngCSqROSKnWESk5H6CALeKFblZjiOpj3GnpH2Nlhwat4iCLEMeZDrloE1w0No5HKeas+TOxs7g/QL8eJaWHs8hcjqWFXwAK0BKa44RqcYxFRXOlAK44AgL6cMXkZwoccon48UnGj95waFVS3VkIko0MWZVvo9cpFJu1mK3NJyOzxp+ZItPvk7gw1Bv0KfluuGS5hwmCejTiGhcK4+OP1cVOiXN1v/6o5R2fOQPbkLsvNVZMU2iJO3nOU3xOzG2BmkIPE6IbOl4OphPP9VtmDfrXRGa8zqBtxbEOp+SSuMSkfmhWPxtkk5RuXm1Tdb5P8n5a/hR9SwPOjDqrFfNrjsLuKckPA9uLIf4pbkGCmscd8bxPp5o49hyNsGPwg4aCG40d0gW0x+4bFDdF5xCN05e1+FM58aa7hanro6KklYwusmSLGwVu0+5vpGZj+dLpVEAyBONm/AXpi81CfFSpAYMwPqu5gDCZsyPkEd5yZPgIurkuT4JIBhP+vP+biBOIES/gJglIPYEf50ApQFjwptEeNwO/f6SJmPWG1xRCMQPeyA62JNIwfcJAEopkMcGci0h2AAwhynW5fDjQNWz/reKs6JQPfPZGFqJW27IpLh6zY3WG7do4r1UvIsSF1lrEYi28yOMcZU0vrEcYQGpNLajgrTuVkwuQTl/gktP0vNDm0U2LBbUEyW2pqsZ2fhbuZTcnY6l5BcSZzvP2hXVYH0cbyTKsoM3Ck9kAkKoF9Pfh/RxWlOg25l6OX9BArL8TKNc7vmKH5VDoi4Nb4Cj7Ct8U8Lh4dHL7PVKl8hcrSzpXM9I/tGtH6IcZeb+uF8yLAH/tYUaUSNBkwPq0JDpShNnoff/JlbHfq06D5ygRCloj7KcO8Te39pwOO7Ua3uO25Bi4jekSzX3OHYNHuUkD/DBHbp6S6Xh6sEjupwDb8FySz24RqaLakqthH3PHNHvQFur5ZmLSj6d2973kGz7Bzq1/XXQiq2AlM44Rt2GKPVRpfzIwEd24u1WBRK3n8iU0XTBnkxN+sZvmNRZbY+McKzs59FwIRqAnIUI7n7ca3inhKCpiQZ6Iir0xU9NCHrYPYCDQqd2Uk165y1i1Vx+kKzsv7lG09f7E/Z6xiVPEO+9vddRp9rDE4Q06SHlfpq4NJDuRHSMg+tUP6Xfom4K/NCUME5MFN/Y8o6YACc0/JJdlKmG2KsPyCE=
*/