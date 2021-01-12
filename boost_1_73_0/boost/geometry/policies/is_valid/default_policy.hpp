// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_POLICIES_IS_VALID_DEFAULT_POLICY_HPP
#define BOOST_GEOMETRY_POLICIES_IS_VALID_DEFAULT_POLICY_HPP

#include <boost/geometry/algorithms/validity_failure_type.hpp>


namespace boost { namespace geometry
{


template <bool AllowDuplicates = true, bool AllowSpikes = true>
class is_valid_default_policy
{
protected:
    static inline bool is_valid(validity_failure_type failure)
    {
        return failure == no_failure
            || (AllowDuplicates && failure == failure_duplicate_points);
    }

    static inline bool is_valid(validity_failure_type failure, bool is_linear)
    {
        return is_valid(failure)
            || (is_linear && AllowSpikes && failure == failure_spikes);
    }

public:
    template <validity_failure_type Failure>
    static inline bool apply()
    {
        return is_valid(Failure);
    }

    template <validity_failure_type Failure, typename Data>
    static inline bool apply(Data const&)
    {
        return is_valid(Failure);
    }

    template <validity_failure_type Failure, typename Data1, typename Data2>
    static inline bool apply(Data1 const& data1, Data2 const&)
    {
        return is_valid(Failure, data1);
    }
};


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_POLICIES_IS_VALID_DEFAULT_POLICY_HPP

/* default_policy.hpp
cDf/7hTjH9b6M7y9tf8AnmbtP4Bb69cX4db69Xx9fD0/TR9fx/9PE58W6Vff3zR8hHC9fqE7fptw/X60Pvhg6Xp+OH6TdD0//Bfq7xhx/rr+ww+F9P6vov7DDyqv+4x//8r/SnxP+Xjcte/xxco/xl3990fB/ELnrn4vH66/swMh9/6BluL5VQn3vzKDIa+Z1X7Aq1rlD36jdD0/AO9txEdSQvbx03Hr+INx6/g5eHj/T3d9
*/