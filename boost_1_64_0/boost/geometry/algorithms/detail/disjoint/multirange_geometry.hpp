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
uvJkxUo914yV/TZCNQ+PjdRwXeunlurFvpFwZocS4kPPaAG4GCLh/wvCyL9+nH9Udyk0ohV0N6n1SLTHtGqp2gvfK0dhWj+93nIZQuXcKHAtpOk764/XydIc8pFk1KMVuB7Rd/8hDsJEWx76mFm2jockPuXh1MSZee1c+JTyj8d26KBiBc0Tgw0LiNfT9c3rxc3VMoWhNlhL4nE5N0Yq8YBU9xuhLXf0Kh9PZt6xJgbMUlJd49OYpTs/iiO0Y/uXXiNtoUdlMAUoJbLSde4m807d4+aZi2URZtfOiLj2i1snBbjvWlIVlO9K+LckcRpHsvmF1wylgDcVuHUvF0jPGq5dwz89ptwxtslA+e27iiB8u0OHhgVcNfj8xJpp+I7RIMjOWf1WaPxcf3+Zw2/TkDx9vrdzP4QYlDabSUDtSOlIw/FiRmaZ+CliGWI7g6iG1OLKZ2Ecm4GgUKqtGVuAqVL29ZMl3m6swLr/+VMl4+eR2ClX9jFVTcuRiU+GjwkMt7RG+XmliQ9FUE2c5FZXowwuFh+3Lk3JOf+LwHVHyMkz1DJRDkhBsZNBPA==
*/