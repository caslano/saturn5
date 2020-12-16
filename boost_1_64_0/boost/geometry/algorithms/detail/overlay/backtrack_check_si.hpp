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
FP9nnn63gh+LF0usose3GxP29kVrsbnqW9ftTm/Ms4m3qvG7765wLke2x+jvTXnk20niN896+gh7wUduCNsCczUD/9ku1n3LxM6p1Vvj+KMqZCrmLTeOPSzGLh/T3ufZzs/o3LPylEr8WT55nHEf3oQtsu9RzhIsjfOeJ+UN+n1tLfc0k0vvE2u+on1qalHkt/hNcdzX5COOeVNcQk2CKqXlLyciyUVM77r709CzfPQl0TpDNu8fJqZma9/23Bs8q11G8+Ql8vP7EWMbMUe7zeV4McWqoepu88Q3N9nj5vy7eB/78CUy5xOrIStyohBaoV5lMVgmtR/5XzdzetKTkfa10U82pQNZRrDbpY7JNfLR694Rvuuj3R/KRzPJK4+on7xIrunUy9TV8ptjH5o3sXxBpPtzrDCnVprr7lm7U57LX6QWNx7+RPxvTsSyN8+KZ6obtxri9NP8y5K3yTeSv2svN+1CL+T+73UQE4iTS7QSk7cSP0bLlRPVBaxhTeDv3lhN33z2C+cVC8Xm37KxrY1/XnazIN8cskdngti5CZmG/YZco9CHchJya3rO3PhOThRLjt/y8fKKDA+TGVty9qyaYn26NFeMxX7yUcGj5DAHT2AhlmIx3kbyg55dzLn9alNF1Ttmqw1vIne5U2IVuvsGH1DT/rDS5+uojV+T47DBaay3luWTR0Sxy3KZr1rwe+bNXfKS5/iZ2ZnJbbja1iE1u9tDch52UttrNOeX1KjiZ9PPEP3YqF7TnB6zJ6/sl5fukHca+4/Ym6/NhTH2mr3Ix5d6k1yPh6wrk31RtodPOLlfzPI9fTDvN9HhtD6LbjW3zMsIMXF8O37qLvF2afb9LeOcgQxXi3XY22xiw3ZrvbcjvxjeU12Xj2osDhCXz2MzZt5ivpfUjrbiA+/u1kWtepC8ay87zqY/Ro9ve1k/N9EhMeUXteQS3v1TUbpzml2jM1PJtvoCssxkbVuO0f5rsaj77pEjbZor/1zPf6ol7hhM59XMpqqRluFbdg2NlGeLXeUGoQ5soVxoc2v+le0TuwaFw34iZO29kbUftj39HWLEbXyZNY4j5uZs+ds0MVBjMUnI/O3GJtxMZnuKsvve/b7YpnBfa6pHyElOlTBJXCN+7GRN6JlbxezGf0pFNcZALVI8XJu9PSU3b9ZXnvqjeS7+vLurtd55Yta5ge94kYtYf5T+dXP9/mJ0hx/Ia+3xcFay/RN/EWGPpjm462nrnmxp97R0YrU4pFbA14frft5lvtR+UjxdxP6uxmLVXsYttxp32IeKEQ7R7Yxp6bJ8b1wVcZycOJ18qjq9/IE9rvex+/nnNQ/yQ7XFIPt9P7s7HWf/r13KXoX454Vyl5rmbTFrOnnldxnMabHkSHK+Sbyy5fj5OXw2Wl/pyI7K8jDx1Z1041Q2vuRr+x1LGaNX9X0AHzKGHqgdftlMCLWEm+ohJ+Hr+rk/1MT6VxnrtSPluQXpjGvLzjn/306x9mK/iLFgO5eH3LuPvYsTd291jQN/YLd3xvC3R/ngJXymn2+hm4lL+RI2rY4YImaAOS7OHScP2lzb3DK/+j4vr1HXmj9AreKMtQjrV3noREtr3eP9HJ1ajlGAPhjvkHY1nawND8mL1XX24Au8fdh4s61xYr32C+hSD/Z5p9xps1z3uFred2SQVZyywzqPZzWaLKY6q45gLXeaOVdzpee9Sh/p18wz5rp52bEd2181EEeIk7Z7TyFzSrz0Mzu9ZDV7vYy+8K2d3uWv6NDQ3XTpY/73CTFSRjEd/918h7hPjNZTH/pf49hKcV17+QcZlxX3fUcXS35iXfI+cZOxfZ28toRtyI7wuqW9qWxrE74wQdw=
*/