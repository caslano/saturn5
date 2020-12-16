// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_LINEAR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_LINEAR_HPP

#include <cstddef>

#include <boost/range.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/range.hpp>

#include <boost/geometry/algorithms/equals.hpp>
#include <boost/geometry/algorithms/validity_failure_type.hpp>
#include <boost/geometry/algorithms/detail/check_iterator_range.hpp>
#include <boost/geometry/algorithms/detail/is_valid/has_invalid_coordinate.hpp>
#include <boost/geometry/algorithms/detail/is_valid/has_spikes.hpp>
#include <boost/geometry/algorithms/detail/num_distinct_consecutive_points.hpp>

#include <boost/geometry/algorithms/dispatch/is_valid.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_valid
{


template <typename Linestring>
struct is_valid_linestring
{
    template <typename VisitPolicy, typename Strategy>
    static inline bool apply(Linestring const& linestring,
                             VisitPolicy& visitor,
                             Strategy const& strategy)
    {
        if (has_invalid_coordinate<Linestring>::apply(linestring, visitor))
        {
            return false;
        }

        if (boost::size(linestring) < 2)
        {
            return visitor.template apply<failure_few_points>();
        }

        std::size_t num_distinct = detail::num_distinct_consecutive_points
            <
                Linestring,
                3u,
                true,
                not_equal_to
                    <
                        typename point_type<Linestring>::type,
                        typename Strategy::equals_point_point_strategy_type
                    >
            >::apply(linestring);

        if (num_distinct < 2u)
        {
            return
                visitor.template apply<failure_wrong_topological_dimension>();
        }

        if (num_distinct == 2u)
        {
            return visitor.template apply<no_failure>();
        }

        return ! has_spikes
                    <
                        Linestring, closed
                    >::apply(linestring, visitor,
                             strategy.get_side_strategy());
    }
};


}} // namespace detail::is_valid
#endif // DOXYGEN_NO_DETAIL




#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// A linestring is a curve.
// A curve is 1-dimensional so it has to have at least two distinct
// points.
// A curve is simple if it does not pass through the same point twice,
// with the possible exception of its two endpoints
//
// There is an option here as to whether spikes are allowed for linestrings; 
// here we pass this as an additional template parameter: allow_spikes
// If allow_spikes is set to true, spikes are allowed, false otherwise.
// By default, spikes are disallowed
//
// Reference: OGC 06-103r4 (6.1.6.1)
template <typename Linestring, bool AllowEmptyMultiGeometries>
struct is_valid
    <
        Linestring, linestring_tag, AllowEmptyMultiGeometries
    > : detail::is_valid::is_valid_linestring<Linestring>
{};


// A MultiLinestring is a MultiCurve
// A MultiCurve is simple if all of its elements are simple and the
// only intersections between any two elements occur at Points that
// are on the boundaries of both elements.
//
// Reference: OGC 06-103r4 (6.1.8.1; Fig. 9)
template <typename MultiLinestring, bool AllowEmptyMultiGeometries>
class is_valid
    <
        MultiLinestring, multi_linestring_tag, AllowEmptyMultiGeometries
    >
{
private:
    template <typename VisitPolicy, typename Strategy>
    struct per_linestring
    {
        per_linestring(VisitPolicy& policy, Strategy const& strategy)
            : m_policy(policy)
            , m_strategy(strategy)
        {}

        template <typename Linestring>
        inline bool apply(Linestring const& linestring) const
        {
            return detail::is_valid::is_valid_linestring
                <
                    Linestring
                >::apply(linestring, m_policy, m_strategy);
        }

        VisitPolicy& m_policy;
        Strategy const& m_strategy;
    };

public:
    template <typename VisitPolicy, typename Strategy>
    static inline bool apply(MultiLinestring const& multilinestring,
                             VisitPolicy& visitor,
                             Strategy const& strategy)
    {
        if (BOOST_GEOMETRY_CONDITION(
                AllowEmptyMultiGeometries && boost::empty(multilinestring)))
        {
            return visitor.template apply<no_failure>();
        }

        typedef per_linestring<VisitPolicy, Strategy> per_ls;

        return detail::check_iterator_range
            <
                per_ls,
                false // do not check for empty multilinestring (done above)
            >::apply(boost::begin(multilinestring),
                     boost::end(multilinestring),
                     per_ls(visitor, strategy));
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_LINEAR_HPP

/* linear.hpp
RFhYOgpNR0Th8jR2u8czf73iMGYWnOqUCDcOTISRz8GcHxLhi9fi0O+Ad9hui8Ji499PDpHPyfF//zxFsub2PA5pTPqRZqQX6UPmkFlkPllInifLyW6ynxwiJ8lpcorcmIe/k8IkM2lBehvD2E/gMH9YeSEKGYfHYd8DUbiOrXf4JBFawOkzH0Sh8muJ8OUguPNEwvuAfVcgEd6EJ5tPJELHuxJh549wmW3M/S4RSr8Kp71o/GLVKLxRDRZVgLEHE+H98nF4KfnuSsd9UhJWLI/C7dvYCLv5qV0cjtPhdUviMP2cef+aCDf18D7M7+wd6x2FMo8nwoiNiXBsHd1/w20WJMJz7LHPHLpuBgf+FoX3B8fh2TzwiywhR8iXpGzFKLx8HSwZap1vicLANHzwR1gzxX0zs/PKfKFsFB4rFIfv704EH4cbTurRFoHzneKwfQM9Lo3CU3PiUNM9HliVfC90FPbR6SuZo9AYPn/k/iefikKJ4YnwFAwfk9W44dXBllGYdSPsXpoIiT+j0H9EIgzYaJ9UkxA+ap8INd6OwoCxbI0PL4Llra8zPr75fVl2PxoemWdoS69X4jCjMRxb6No747A7TyK8NDwK92+Owk4+erRNHNLT+UkxdLJ4c6uXtd8q3hUkxcggmDLjmL+NWjcRyj5hX+VkPlZfXNycCLn+wS/eFQ8axKEd7No4NBF+KM1v+hnbsERYk87YnLv3JeuRKRE6tId/rnk9HN7wLR9Y7lrnEqHa73G4cBPsfDoRvoYZf3bz/tbTUSj8cRyKd4Cd19hFT/Zl7C2cf8TYH3e9Z9+ntxsS4ZvXVQPvUKMW3+sM9XdLCtPt23G48bYopP8NHsyLw7L53kedRc2zIRvInQgFB+IHy+OwwFrkvScRfmYPvzzFt1y/D1lQIhFusC6/wstC7GmV+410/Rrm/EKtRKj6WBwy/pkIVeD+yDaJsMw5kw9F4RrMXP24OPUHW5nKr6qIwxftefVy+xmOaVc6Dl9o7NzSLQpzPoChw60RO2m7Iv6XfZ5dF4VFjnsxOYassPIua/dtImxsLP7Bm9Mn2Dtd7RC3v4FJs5vEoe5dceiVy32G2IOX37q9DAucv7kr+2dHafnAEMX+V9MnwrwNifDQG2JHb88oOuYzcoqcJRngZnpyM8lEspFCpCApRor8+/vX+c+wQdZ3q+uxq4Z8+asbo9BlZRSeWBeHS4+IMeadmgPH2B3/6xr9i/GDB6Owu624WiURju8Sf9jo/vLWrE8iNHiYDhyXQmYme9fs8W93JEKvQn993pm8tDYRakZR2P4CHBEf8vU3lkWJcFnsGSIevtEiDnv+Lo5USoQsT9LVIjh1ORFiWNp+Bzz2/c/1+bprjViZCFvnic0NYVitOEz7io18Jt6MFC9fFiNK2JvORoqqpb9nPbe2j8P+z6NQa3cipG1uvfn/KpzpeNFE2FDG/Tsnwrt/g3VwPaWPeHo//oSr1EqNwzdf88+X+D0MaPMaXX/hXsZwfiNcFfsb9EuEzDvE+jJxeCYtTtPEfS7wQ9cYXcU134bZcG6LWPLCAOs9FN6Y73BrPU8cfr2EuHiW3n6OQvfnxS9+86Xrb3oa3hhvMZLmDmv4SxTmdrPe/PKxX+AqjOznjw29fIBNspWSrRL4ZCIsrUsnB2A2225k/Uq/lwinBxj/h4nwcsnkxix+Dss+gH9fPZkIB7qJNS/EYeLHeBZcOzSTb4hxw2vG4cqGKGycEIUDrd2jEb53jp4yms9hfyP8S8flEYON/8WP+U9Sd+bVIz0fwHlWnIxCtlrWeV8UrqfHbFNhZXLv6CPW+D55wJA4PGT91s6FAezp/uVseBvM7R+Fjn8=
*/