// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017.
// Modifications copyright (c) 2017 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_SORT_ON_SEGMENT_RATIO_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_SORT_ON_SEGMENT_RATIO_HPP

#include <cstddef>
#include <algorithm>
#include <map>
#include <set>
#include <vector>

#include <boost/range.hpp>

#include <boost/geometry/algorithms/detail/overlay/copy_segment_point.hpp>
#include <boost/geometry/algorithms/detail/overlay/sort_by_side.hpp>
#include <boost/geometry/strategies/side.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

// Wraps "turn_operation" from turn_info.hpp,
// giving it extra information, necessary for sorting
template <typename TurnOperation>
struct indexed_turn_operation
{
    typedef TurnOperation type;

    std::size_t turn_index;
    std::size_t operation_index;
    bool skip;
    // use pointers to avoid copies, const& is not possible because of usage in vector
    segment_identifier const* other_seg_id; // segment id of other segment of intersection of two segments
    TurnOperation const* subject;

    inline indexed_turn_operation(std::size_t ti, std::size_t oi,
                TurnOperation const& sub,
                segment_identifier const& oid)
        : turn_index(ti)
        , operation_index(oi)
        , skip(false)
        , other_seg_id(&oid)
        , subject(boost::addressof(sub))
    {}

};

template
<
    typename Turns,
    typename Indexed,
    typename Geometry1, typename Geometry2,
    typename RobustPolicy,
    typename SideStrategy,
    bool Reverse1, bool Reverse2
>
struct less_by_segment_ratio
{
    inline less_by_segment_ratio(Turns const& turns
            , Geometry1 const& geometry1
            , Geometry2 const& geometry2
            , RobustPolicy const& robust_policy
            , SideStrategy const& strategy)
        : m_turns(turns)
        , m_geometry1(geometry1)
        , m_geometry2(geometry2)
        , m_robust_policy(robust_policy)
        , m_strategy(strategy)
    {
    }

private :

    Turns const& m_turns;
    Geometry1 const& m_geometry1;
    Geometry2 const& m_geometry2;
    RobustPolicy const& m_robust_policy;
    SideStrategy const& m_strategy;

    typedef typename geometry::point_type<Geometry1>::type point_type;

    inline bool default_order(Indexed const& left, Indexed const& right) const
    {
        // We've nothing to sort on. Take the indexes
        return left.turn_index < right.turn_index;
    }

    inline bool consider_relative_order(Indexed const& left,
                    Indexed const& right) const
    {
        point_type pi, pj, ri, rj, si, sj;

        geometry::copy_segment_points<Reverse1, Reverse2>(m_geometry1, m_geometry2,
            left.subject->seg_id,
            pi, pj);
        geometry::copy_segment_points<Reverse1, Reverse2>(m_geometry1, m_geometry2,
            *left.other_seg_id,
            ri, rj);
        geometry::copy_segment_points<Reverse1, Reverse2>(m_geometry1, m_geometry2,
            *right.other_seg_id,
            si, sj);

        int const side_rj_p = m_strategy.apply(pi, pj, rj);
        int const side_sj_p = m_strategy.apply(pi, pj, sj);

        // Put the one turning left (1; right == -1) as last
        if (side_rj_p != side_sj_p)
        {
            return side_rj_p < side_sj_p;
        }

        int const side_sj_r = m_strategy.apply(ri, rj, sj);
        int const side_rj_s = m_strategy.apply(si, sj, rj);

        // If they both turn left: the most left as last
        // If they both turn right: this is not relevant, but take also here most left
        if (side_rj_s != side_sj_r)
        {
            return side_rj_s < side_sj_r;
        }

        return default_order(left, right);
    }


public :

    // Note that left/right do NOT correspond to m_geometry1/m_geometry2
    // but to the "indexed_turn_operation"
    inline bool operator()(Indexed const& left, Indexed const& right) const
    {
        if (! (left.subject->seg_id == right.subject->seg_id))
        {
            return left.subject->seg_id < right.subject->seg_id;
        }

        // Both left and right are located on the SAME segment.

        if (! (left.subject->fraction == right.subject->fraction))
        {
            return left.subject->fraction < right.subject->fraction;
        }


        typedef typename boost::range_value<Turns>::type turn_type;
        turn_type const& left_turn = m_turns[left.turn_index];
        turn_type const& right_turn = m_turns[right.turn_index];

        // First check "real" intersection (crosses)
        // -> distance zero due to precision, solve it by sorting
        if (left_turn.method == method_crosses
            && right_turn.method == method_crosses)
        {
            return consider_relative_order(left, right);
        }

        bool const left_both_xx = left_turn.both(operation_blocked);
        bool const right_both_xx = right_turn.both(operation_blocked);
        if (left_both_xx && ! right_both_xx)
        {
            return true;
        }
        if (! left_both_xx && right_both_xx)
        {
            return false;
        }

        bool const left_both_uu = left_turn.both(operation_union);
        bool const right_both_uu = right_turn.both(operation_union);
        if (left_both_uu && ! right_both_uu)
        {
            return true;
        }
        if (! left_both_uu && right_both_uu)
        {
            return false;
        }

        return default_order(left, right);
    }
};


}} // namespace detail::overlay
#endif //DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_SORT_ON_SEGMENT_RATIO_HPP

/* less_by_segment_ratio.hpp
mD4IgxIx+3LCTzfhB9iKO+FQJWbNzza9XrNklGxrqmT7HlLez8jsOHRkooy5w/R6gF7R+QUqQd11aP4IGcZ40gwQQgCcvZRAbwmolueMi6HrEIdw/0XjdhkoeIU/1FLgER2ILtvXufQmkFFr+qaIkjcQrgW9KwnKMRy/blkkD93H0f0l6dYVUbf2bIzq95NnxgzfrzXZz8cjFTZIb7wFUpPcfhLHnzvBvENOIejMf6Oz2sfyq5yUHiorWOEmZ3Ko9Hqlm+qOLqQEc0xVapR89KDE/Yx5f75LTdtNHCKLM+Z9K4Ji2l5lmq25V26seIXNnbKfvsgzjORXEJNWKhxUC4OcM7Y/qPjMyohDNk+6tZU7gv2gn1F7ILkVb0g0Liy31LwPfQFE1bkjN2aYET9gLtUJHGszjWRMMD12WXoeEwxTYob5raXnscUwOWaYW00LUaUAqkv6P14h15F5R1aojRWyPCg9Lwkkj9oZ61Rwv0cwEaZA6AoFLZNJA+kJ+4mCDaawI7EBq8yYgHbAo31Icyyhw5pz6Wrgf/zU1Gr1vFqt3qyws0vM1erGX8muY3rlK9K7QpT7cTh9QnWMTnpK9Vambk9ZgdwPrsjU6bnk3xTZM8/rv5NnovYB4/VfKZIh/osU3ULbiuvKFf7qxN9oBv7qvzzStiLmojdzOfTlgTZpW+rO3cpuWi8c4yeQ9qWSy946ZsToklL824nEyin105jeyXmZ6zmqFKqfaMNXMDeZwTQWMiKn5agawT5qw0kZDcYeUGwm3KUsOS3X0LPIuARdy7ZYc7eJPQk1K/7iLGx1q9AW7n3GF2VVkBQaxMzmNlUIjzJgX4lNAFkkGfB5AM3IBCVLVDuPUIqHjMlIVx40ven4gEAqSJ65qDwYZCY7cyo3Oz7jSgSWMGgIFKJzyGt8DmbRB2nt2n7jErZO9TZwZd47087lh1v8Vx9gFKYg2pIT1lZ4s5pfQADUOd3hExEYE5Yq7BLziCayiKxkMxMki79M7ueWdCQSHUuUUUoGbKiZala0pXYL/ukBgFoil3OloFBsTOjbA4tq8s20IisYEg4VKsxQoZsG2o8IoAu0ChpAtlCqff42XPpH/HxCnxcQPgfK2WgU6OE+eli3SocDXzaoU9i9YV2L1PKYKFCVTcTJlL+eKqEMV5zeS2J7dOL78i7rvvZE4m/kxwq9oMRdsP6I9Lc6ZPoy8V//XLMcmf8jGf6zevCPZvhP7cH/Wxn+P7n/aP+qDP9BPcQ/PcP/4h7i52f4t993tP++HHO2iMxTirKTvRwW5+TCwTh5TLPHX+hgdnBQ6GB50IkTcAcn1AwOoOuQxnq8HcB9MK8xB1VKC/GVBXD9CfrCnIKvVAWhGpcwOmoxZPCr5PxVc5KZTkcl9Lg0S01vCA/kdaLxXL/YDXNEHP3TjO+j7zn5/u5wF3db3rKEsedetQj/FLE5O8yEaQo1283gdDRPVwvnMwjmg0oo5nuMQmmr9yszQnsdNX1xqH7scOfSAYjvGlvsvO04fEAl+WwxQGwSY0fVHpS6t55t56h3M9RRbnuX8ceWJv12pfzanEu3UZF0yWI0U5E5eEV4OFxiWTH+g9mhjUWhTZVidl+PmF3Y0dxqBfA4WMtboU68fw//dR8G8zx1HwVzlCVHG1r/bXuwHwjeG8SkAjbAhVnKjHH86wBe7BPPk8e47x4e1sJxcD8U+c/G3L7GhnLJTRHjnIZGQ2gelLhK39/sCF5ulm9h/XsaV48JVdCrzRcvSH4l0oKBNtWYAm2vJyTtdCPgHlencylP//tBngs2tEBD+/A3U+10TaJApeRFjPhuBFV+/84EQ3L/utaekg8fl41P7k/lyBk=
*/