// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017-2020.
// Modifications copyright (c) 2017-2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_BACKTRACK_CHECK_SI_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_BACKTRACK_CHECK_SI_HPP

#include <cstddef>
#include <string>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

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