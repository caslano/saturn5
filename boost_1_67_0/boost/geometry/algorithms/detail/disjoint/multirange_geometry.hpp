// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2017, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_MULTIRANGE_GEOMETRY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_MULTIRANGE_GEOMETRY_HPP

#include <boost/range.hpp>

#include <boost/geometry/algorithms/detail/check_iterator_range.hpp>
#include <boost/geometry/algorithms/dispatch/disjoint.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace disjoint
{


template <typename Geometry, typename Strategy, typename BinaryPredicate>
class unary_disjoint_geometry_to_query_geometry
{
public:
    unary_disjoint_geometry_to_query_geometry(Geometry const& geometry,
                                              Strategy const& strategy)
        : m_geometry(geometry)
        , m_strategy(strategy)
    {}

    template <typename QueryGeometry>
    inline bool apply(QueryGeometry const& query_geometry) const
    {
        return BinaryPredicate::apply(query_geometry, m_geometry, m_strategy);
    }

private:
    Geometry const& m_geometry;
    Strategy const& m_strategy;
};


template<typename MultiRange, typename ConstantSizeGeometry>
struct multirange_constant_size_geometry
{
    template <typename Strategy>
    static inline bool apply(MultiRange const& multirange,
                             ConstantSizeGeometry const& constant_size_geometry,
                             Strategy const& strategy)
    {
        typedef unary_disjoint_geometry_to_query_geometry
            <
                ConstantSizeGeometry,
                Strategy,
                dispatch::disjoint
                    <
                        typename boost::range_value<MultiRange>::type,
                        ConstantSizeGeometry
                    >
            > unary_predicate_type;

        return detail::check_iterator_range
            <
                unary_predicate_type
            >::apply(boost::begin(multirange), boost::end(multirange),
                     unary_predicate_type(constant_size_geometry, strategy));
    }

    template <typename Strategy>
    static inline bool apply(ConstantSizeGeometry const& constant_size_geometry,
                             MultiRange const& multirange,
                             Strategy const& strategy)
    {
        return apply(multirange, constant_size_geometry, strategy);
    }
};


}} // namespace detail::disjoint
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_MULTIRANGE_GEOMETRY_HPP

/* multirange_geometry.hpp
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
*/