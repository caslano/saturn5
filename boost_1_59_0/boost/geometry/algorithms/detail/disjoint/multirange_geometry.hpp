// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_MULTIRANGE_GEOMETRY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_MULTIRANGE_GEOMETRY_HPP


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

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
    inline bool operator()(QueryGeometry const& query_geometry) const
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
        using disjoint = unary_disjoint_geometry_to_query_geometry
            <
                ConstantSizeGeometry,
                Strategy,
                dispatch::disjoint
                    <
                        typename boost::range_value<MultiRange>::type,
                        ConstantSizeGeometry
                    >
            >;

        return std::all_of(boost::begin(multirange),
                           boost::end(multirange),
                           disjoint(constant_size_geometry, strategy));
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
+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
*/