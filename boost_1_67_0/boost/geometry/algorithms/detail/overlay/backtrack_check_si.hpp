// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017.
// Modifications copyright (c) 2017, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_BACKTRACK_CHECK_SI_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_BACKTRACK_CHECK_SI_HPP

#include <cstddef>
#include <string>

#include <boost/range.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>
#include <boost/geometry/algorithms/detail/has_self_intersections.hpp>
#if defined(BOOST_GEOMETRY_DEBUG_INTERSECTION) || defined(BOOST_GEOMETRY_OVERLAY_REPORT_WKT)
#  include <boost/geometry/algorithms/detail/overlay/debug_turn_info.hpp>
#  include <boost/geometry/io/wkt/wkt.hpp>
#endif

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

template <typename Turns>
inline void clear_visit_info(Turns& turns)
{
    typedef typename boost::range_value<Turns>::type tp_type;

    for (typename boost::range_iterator<Turns>::type
        it = boost::begin(turns);
        it != boost::end(turns);
        ++it)
    {
        for (typename boost::range_iterator
            <
                typename tp_type::container_type
            >::type op_it = boost::begin(it->operations);
            op_it != boost::end(it->operations);
            ++op_it)
        {
            op_it->visited.clear();
        }
    }
}

struct backtrack_state
{
    bool m_good;

    inline backtrack_state() : m_good(true) {}
    inline void reset() { m_good = true; }
    inline bool good() const { return m_good; }
};


enum traverse_error_type
{
    traverse_error_none,
    traverse_error_no_next_ip_at_start,
    traverse_error_no_next_ip,
    traverse_error_dead_end_at_start,
    traverse_error_dead_end,
    traverse_error_visit_again,
    traverse_error_endless_loop
};

inline std::string traverse_error_string(traverse_error_type error)
{
    switch (error)
    {
        case traverse_error_none : return "";
        case traverse_error_no_next_ip_at_start : return "No next IP at start";
        case traverse_error_no_next_ip : return "No next IP";
        case traverse_error_dead_end_at_start : return "Dead end at start";
        case traverse_error_dead_end : return "Dead end";
        case traverse_error_visit_again : return "Visit again";
        case traverse_error_endless_loop : return "Endless loop";
        default : return "";
    }
    return "";
}


template
<
    typename Geometry1,
    typename Geometry2
>
class backtrack_check_self_intersections
{
    struct state : public backtrack_state
    {
        bool m_checked;
        inline state()
            : m_checked(true)
        {}
    };
public :
    typedef state state_type;

    template
    <
        typename Operation,
        typename Rings, typename Ring, typename Turns,
        typename Strategy,
        typename RobustPolicy,
        typename Visitor
    >
    static inline void apply(std::size_t size_at_start,
                             Rings& rings,
                             Ring& ring,
                             Turns& turns,
                             typename boost::range_value<Turns>::type const& turn,
                             Operation& operation,
                             traverse_error_type traverse_error,
                             Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy,
                             RobustPolicy const& robust_policy,
                             state_type& state,
                             Visitor& visitor)
    {
        visitor.visit_traverse_reject(turns, turn, operation, traverse_error);

        state.m_good = false;

        // Check self-intersections and throw exception if appropriate
        if (! state.m_checked)
        {
            state.m_checked = true;
            has_self_intersections(geometry1, strategy, robust_policy);
            has_self_intersections(geometry2, strategy, robust_policy);
        }

        // Make bad output clean
        rings.resize(size_at_start);
        geometry::traits::clear<typename boost::range_value<Rings>::type>::apply(ring);

        // Reject this as a starting point
        operation.visited.set_rejected();

        // And clear all visit info
        clear_visit_info(turns);
    }
};

#ifdef BOOST_GEOMETRY_OVERLAY_REPORT_WKT
template
<
    typename Geometry1,
    typename Geometry2
>
class backtrack_debug
{
public :
    typedef backtrack_state state_type;

    template <typename Operation, typename Rings, typename Turns>
    static inline void apply(std::size_t size_at_start,
                Rings& rings, typename boost::range_value<Rings>::type& ring,
                Turns& turns, Operation& operation,
                std::string const& reason,
                Geometry1 const& geometry1,
                Geometry2 const& geometry2,
                state_type& state
                )
    {
        std::cout << " REJECT " << reason << std::endl;

        state.m_good = false;

        rings.resize(size_at_start);
        ring.clear();
        operation.visited.set_rejected();
        clear_visit_info(turns);

        int c = 0;
        for (int i = 0; i < turns.size(); i++)
        {
            for (int j = 0; j < 2; j++)
            {
                if (turns[i].operations[j].visited.rejected())
                {
                    c++;
                }
            }
        }
        std::cout << "BACKTRACK (" << reason << " )"
            << " " << c << " of " << turns.size() << " rejected"
            << std::endl;
        std::cout
            << geometry::wkt(geometry1) << std::endl
            << geometry::wkt(geometry2) << std::endl;
    }
};
#endif // BOOST_GEOMETRY_OVERLAY_REPORT_WKT

}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_BACKTRACK_CHECK_SI_HPP

/* backtrack_check_si.hpp
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
*/