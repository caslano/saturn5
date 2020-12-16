// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2014 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018.
// Modifications copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_BUFFER_POLICIES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_BUFFER_POLICIES_HPP

#include <cstddef>

#include <boost/range.hpp>

#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/algorithms/detail/overlay/backtrack_check_si.hpp>
#include <boost/geometry/algorithms/detail/overlay/traversal_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>

#include <boost/geometry/strategies/buffer.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace buffer
{


enum intersection_location_type
{
    location_ok, inside_buffer, location_discard
};

class backtrack_for_buffer
{
public :
    typedef detail::overlay::backtrack_state state_type;

    template
        <
            typename Operation,
            typename Rings,
            typename Turns,
            typename Geometry,
            typename Strategy,
            typename RobustPolicy,
            typename Visitor
        >
    static inline void apply(std::size_t size_at_start,
                Rings& rings, typename boost::range_value<Rings>::type& ring,
                Turns& turns,
                typename boost::range_value<Turns>::type const& /*turn*/,
                Operation& operation,
                detail::overlay::traverse_error_type /*traverse_error*/,
                Geometry const& ,
                Geometry const& ,
                Strategy const& ,
                RobustPolicy const& ,
                state_type& state,
                Visitor& /*visitor*/
                )
    {
#if defined(BOOST_GEOMETRY_COUNT_BACKTRACK_WARNINGS)
extern int g_backtrack_warning_count;
g_backtrack_warning_count++;
#endif
//std::cout << "!";
//std::cout << "WARNING " << traverse_error_string(traverse_error) << std::endl;

        state.m_good = false;

        // Make bad output clean
        rings.resize(size_at_start);
        ring.clear();

        // Reject this as a starting point
        operation.visited.set_rejected();

        // And clear all visit info
        clear_visit_info(turns);
    }
};

struct buffer_overlay_visitor
{
public :
    void print(char const* /*header*/)
    {
    }

    template <typename Turns>
    void print(char const* /*header*/, Turns const& /*turns*/, int /*turn_index*/)
    {
    }

    template <typename Turns>
    void print(char const* /*header*/, Turns const& /*turns*/, int /*turn_index*/, int /*op_index*/)
    {
    }

    template <typename Turns>
    void visit_turns(int , Turns const& ) {}

    template <typename Clusters, typename Turns>
    void visit_clusters(Clusters const& , Turns const& ) {}

    template <typename Turns, typename Turn, typename Operation>
    void visit_traverse(Turns const& /*turns*/, Turn const& /*turn*/, Operation const& /*op*/, const char* /*header*/)
    {
    }

    template <typename Turns, typename Turn, typename Operation>
    void visit_traverse_reject(Turns const& , Turn const& , Operation const& ,
            detail::overlay::traverse_error_type )
    {}

    template <typename Rings>
    void visit_generated_rings(Rings const& )
    {}
};


// Should follow traversal-turn-concept (enrichment, visit structure)
// and adds index in piece vector to find it back
template <typename Point, typename SegmentRatio>
struct buffer_turn_operation
    : public detail::overlay::traversal_turn_operation<Point, SegmentRatio>
{
    signed_size_type piece_index;
    signed_size_type index_in_robust_ring;

    inline buffer_turn_operation()
        : piece_index(-1)
        , index_in_robust_ring(-1)
    {}
};

// Version for buffer including type of location, is_opposite, and helper variables
template <typename Point, typename RobustPoint, typename SegmentRatio>
struct buffer_turn_info
    : public detail::overlay::turn_info
        <
            Point,
            SegmentRatio,
            buffer_turn_operation<Point, SegmentRatio>
        >
{
    typedef Point point_type;
    typedef RobustPoint robust_point_type;

    std::size_t turn_index; // TODO: this might go if partition can operate on non-const input

    RobustPoint robust_point;

    inline RobustPoint const& get_robust_point() const
    {
        return robust_point;
    }

    intersection_location_type location;

    robust_point_type rob_pi, rob_pj, rob_qi, rob_qj;

    std::size_t count_within;

    bool within_original;
    signed_size_type count_in_original; // increased by +1 for in ext.ring, -1 for int.ring

    std::size_t count_on_offsetted;
    std::size_t count_on_helper;
    std::size_t count_within_near_offsetted;

    inline buffer_turn_info()
        : turn_index(0)
        , location(location_ok)
        , count_within(0)
        , within_original(false)
        , count_in_original(0)
        , count_on_offsetted(0)
        , count_on_helper(0)
        , count_within_near_offsetted(0)
    {}
};

struct buffer_operation_less
{
    template <typename Turn>
    inline bool operator()(Turn const& left, Turn const& right) const
    {
        segment_identifier const& sl = left.seg_id;
        segment_identifier const& sr = right.seg_id;

        // Sort them descending
        return sl == sr
            ? left.fraction < right.fraction
            : sl < sr;
    }
};

}} // namespace detail::buffer
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_BUFFER_POLICIES_HPP

/* buffer_policies.hpp
r/A+p9pNEofT24gZnC3xc/ZIYwfmebswbuvNzQ/vT7oTDcjze9biwHw7Aq/SKK9F71H69agGZ//ULqTvi3Pd98WWMLZPdHfyncr4t0SEvjFWkcnJdf56EOV8XF7a978nafZ1vW/WURvX9N7xcftkSFUQo8OxaIdW6TrJscuBz34raZeqcK35nNlPDa+KrzUjqmwZyY/kAIzX7z0Jf7+xWfx9xwJfx6j4+qq0/q5P4B4hZDX1zzd8pyX44EYpPJyvxtJYHGPgjjfbVfsI3NrAbP/tW2XfZA35j9k39CXyWz/jqqw9kBDXWeCRfi/U8644F2zKrkkoe5DqK+wnIqfg4F0no6+JVXFfwnvQh/zv6RwS709aX/nfww8lOK9Nh2kdBE42zRFVhhfHqYAtaWPSl1TZvoo79Po+VthXS0keqbuHy/+eRrlpn9dwH9LdAVkyEmdE7TtWkezAtbJXqyygg3ffccbdy1ITyQIcwFU301B/B8Obw9bHoDwLgP8RQ++5cr7XI749lVfgJG8tlYUsWnamgT+TIGud0hY40Z6Deki+tmO3rAG7jHEYi+qbWxYsXFAXbHPpIT7d0LhwfkOzzOc+bxefd3xdY/3sJVHeUJ83Y+HCeXW1C4Iwb5jP84d8fHpXn65rbFzYKPPvbv57v5P32CrHVdwlfe4zunsHNu3m3hMqKXP69NBPdOWk7Lw2r2pQ542EEp8IQTadBVkAet1RTGlJByYu2EJJDw9CqdKBOaPp75Zhj4/4XYUJ8buKsL5G5YoRG2sSzj80VNnzD/0dkS/N/2XOYX73sPh83Cjl/FnmKrM2Aa+f+sYi4B4PXIwLwU26WyPnWIG/BPg3B8kx9pq9bkTSnt5UtxwvS5szJCcIbKSDrZajwSk0q4OhXKGDLe/sl/OEil/k8tyR1wj99Sx+sYOJGyidUkYetrQKehPnkpTqb8uIm0huBGQQc3c3d9bX6LhGcBH5TFWtGXrmyNpi4lxxLq6uDnHsnJayMSGGKax1jcKMzSYdzseHqMY5nU9W7ZzdNhtyhN+EWtsy3vWVSrcFlk/PKS1tK1v70gHyvM3WKvZTJ/KVf4vhXzgI/uXgf6IrhzFg+/dJPn9ZT09nqrUbPrIS3F1udW28w7vL04NV4HFclb4JbevWn6G+kAnCe329AglHluSjbxaiPbzWgb/M96sWPZtUg/FYjfHXZnQyXfoG2Gnf0Az0DTvOOCZPqgpxAAzc/gTPy2ljtayowr03lDF4/n+OQdEh+FYG+Hv0XsQpKkMuemGelaGrKu7bkbLbMP41Tte3Jul3R6zPnr6+AzEUZ63t+txn1qRvUeyoTBXSZj6z8ZpWjY7XM0PxiddE5fPi5cP5m++sAB+ygb7i2/KuH1q4m3usvEspfYKmIS/q6srZvvE5gi8l+BcIfgLBz0La6YLPHc1XWCjL2XZtwJ3v4/E3dK54Zi1IjN91AfW3+arnUK4vWRpYe9hP+ZUqxCMaYFyI3hPGx4jgIhofufCFrx8fXyNejM/jwPK61NQF37/Mugt/KuovdoFtB2dHqI1yOe29rqC+d6XRqaOzZjTFpyY4r+ffjeCgLfnQQQj/PsbzKMR9EJbblsdix3cjGOtrJnZ8d70Ep5WvIzP9ouHzETt+Zqav84TWU1L9vfMlBmegZfZ0sB65wtPTeVxqbZMLFREcjxiuV8fWupaZCxc0ianY0lhXOwt/u7zmxoXz/Dw7EIKfd49Psvf+D3Rde/0I7aXznN3rYEzwnZPrMMZ+rGUNLt0d+QlwrydcBx+F+Ffyv8e9Ebg3ARd7RIyt5G8eP0V7nxpkYx5ijnbyQP5Qrmuq4nP0JvD7OfjpOuChoINxg7E=
*/