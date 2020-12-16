// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_LINEAR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_LINEAR_HPP

#include <algorithm>
#include <deque>

#include <boost/range.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/range.hpp>

#include <boost/geometry/policies/predicate_based_interrupt_policy.hpp>
#include <boost/geometry/policies/robustness/no_rescale_policy.hpp>
#include <boost/geometry/policies/robustness/segment_ratio.hpp>

#include <boost/geometry/algorithms/intersects.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/algorithms/detail/check_iterator_range.hpp>
#include <boost/geometry/algorithms/detail/signed_size_type.hpp>

#include <boost/geometry/algorithms/detail/disjoint/linear_linear.hpp>
#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_turn_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/self_turn_points.hpp>
#include <boost/geometry/algorithms/detail/is_valid/has_duplicates.hpp>
#include <boost/geometry/algorithms/detail/is_valid/has_spikes.hpp>

#include <boost/geometry/algorithms/detail/is_simple/debug_print_boundary_points.hpp>
#include <boost/geometry/algorithms/detail/is_simple/failure_policy.hpp>
#include <boost/geometry/algorithms/detail/is_valid/debug_print_turns.hpp>

#include <boost/geometry/algorithms/dispatch/is_simple.hpp>

#include <boost/geometry/strategies/intersection.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace is_simple
{


template <typename Turn>
inline bool check_segment_indices(Turn const& turn,
                                  signed_size_type last_index)
{
    return
        (turn.operations[0].seg_id.segment_index == 0
         && turn.operations[1].seg_id.segment_index == last_index)
        ||
        (turn.operations[0].seg_id.segment_index == 0
         && turn.operations[1].seg_id.segment_index == last_index);
}


template
<
    typename Geometry,
    typename EqPPStrategy,
    typename Tag = typename tag<Geometry>::type
>
class is_acceptable_turn
    : not_implemented<Geometry>
{};

template <typename Linestring, typename EqPPStrategy>
class is_acceptable_turn<Linestring, EqPPStrategy, linestring_tag>
{
public:
    is_acceptable_turn(Linestring const& linestring)
        : m_linestring(linestring)
        , m_is_closed(geometry::detail::equals::equals_point_point(range::front(linestring),
                                                                   range::back(linestring),
                                                                   EqPPStrategy()))
    {}

    template <typename Turn>
    inline bool apply(Turn const& turn) const
    {
        BOOST_GEOMETRY_ASSERT(boost::size(m_linestring) > 1);
        return m_is_closed
            && turn.method == overlay::method_none
            && check_segment_indices(turn, boost::size(m_linestring) - 2)
            && turn.operations[0].fraction.is_zero();
    }

private:
    Linestring const& m_linestring;
    bool const m_is_closed;
};

template <typename MultiLinestring, typename EqPPStrategy>
class is_acceptable_turn<MultiLinestring, EqPPStrategy, multi_linestring_tag>
{
private:
    template <typename Point1, typename Point2>
    static inline bool equals_point_point(Point1 const& point1, Point2 const& point2)
    {
        return geometry::detail::equals::equals_point_point(point1, point2,
                                                            EqPPStrategy());
    }

    template <typename Point, typename Linestring>
    static inline bool is_boundary_point_of(Point const& point,
                                            Linestring const& linestring)
    {
        BOOST_GEOMETRY_ASSERT(boost::size(linestring) > 1);
        return
            !equals_point_point(range::front(linestring), range::back(linestring))
            &&
            (equals_point_point(point, range::front(linestring))
             || equals_point_point(point, range::back(linestring)));
    }

    template <typename Turn, typename Linestring>
    static inline bool is_closing_point_of(Turn const& turn,
                                           Linestring const& linestring)
    {
        BOOST_GEOMETRY_ASSERT(boost::size(linestring) > 1);
        return
            turn.method == overlay::method_none
            &&
            check_segment_indices(turn, boost::size(linestring) - 2)
            &&
            equals_point_point(range::front(linestring), range::back(linestring))
            &&
            turn.operations[0].fraction.is_zero();
            ;
    }

    template <typename Linestring1, typename Linestring2>
    static inline bool have_same_boundary_points(Linestring1 const& ls1,
                                                 Linestring2 const& ls2)
    {
        return
            equals_point_point(range::front(ls1), range::front(ls2))
            ?
            equals_point_point(range::back(ls1), range::back(ls2))
            :
            (equals_point_point(range::front(ls1), range::back(ls2))
             &&
                equals_point_point(range::back(ls1), range::front(ls2)))
            ;
    }

public:
    is_acceptable_turn(MultiLinestring const& multilinestring)
        : m_multilinestring(multilinestring)
    {}

    template <typename Turn>
    inline bool apply(Turn const& turn) const
    {
        typedef typename boost::range_value<MultiLinestring>::type linestring_type;
        
        linestring_type const& ls1 =
            range::at(m_multilinestring, turn.operations[0].seg_id.multi_index);

        linestring_type const& ls2 =
            range::at(m_multilinestring, turn.operations[1].seg_id.multi_index);

        if (turn.operations[0].seg_id.multi_index
            == turn.operations[1].seg_id.multi_index)
        {
            return is_closing_point_of(turn, ls1);
        }

        return
            is_boundary_point_of(turn.point, ls1)
            && is_boundary_point_of(turn.point, ls2)
            &&
            ( boost::size(ls1) != 2
              || boost::size(ls2) != 2
              || ! have_same_boundary_points(ls1, ls2) );
    }

private:
    MultiLinestring const& m_multilinestring;
};


template <typename Linear, typename Strategy>
inline bool has_self_intersections(Linear const& linear, Strategy const& strategy)
{
    typedef typename point_type<Linear>::type point_type;

    // compute self turns
    typedef detail::overlay::turn_info<point_type> turn_info;

    std::deque<turn_info> turns;

    typedef detail::overlay::get_turn_info
        <
            detail::disjoint::assign_disjoint_policy
        > turn_policy;

    typedef is_acceptable_turn
        <
            Linear,
            typename Strategy::equals_point_point_strategy_type
        > is_acceptable_turn_type;

    is_acceptable_turn_type predicate(linear);
    detail::overlay::predicate_based_interrupt_policy
        <
            is_acceptable_turn_type
        > interrupt_policy(predicate);

    // TODO: skip_adjacent should be set to false
    detail::self_get_turn_points::get_turns
        <
            false, turn_policy
        >::apply(linear,
                 strategy,
                 detail::no_rescale_policy(),
                 turns,
                 interrupt_policy, 0, true);

    detail::is_valid::debug_print_turns(turns.begin(), turns.end());
    debug_print_boundary_points(linear);

    return interrupt_policy.has_intersections;
}


template <typename Linestring, bool CheckSelfIntersections = true>
struct is_simple_linestring
{
    template <typename Strategy>
    static inline bool apply(Linestring const& linestring,
                             Strategy const& strategy)
    {
        simplicity_failure_policy policy;
        return ! boost::empty(linestring)
            && ! detail::is_valid::has_duplicates
                    <
                        Linestring, closed, typename Strategy::cs_tag
                    >::apply(linestring, policy)
            && ! detail::is_valid::has_spikes
                    <
                        Linestring, closed
                    >::apply(linestring, policy, strategy.get_side_strategy());
    }
};

template <typename Linestring>
struct is_simple_linestring<Linestring, true>
{
    template <typename Strategy>
    static inline bool apply(Linestring const& linestring,
                             Strategy const& strategy)
    {
        return is_simple_linestring
                <
                    Linestring, false
                >::apply(linestring, strategy)
            && ! has_self_intersections(linestring, strategy);
    }
};


template <typename MultiLinestring>
struct is_simple_multilinestring
{
private:
    template <typename Strategy>
    struct per_linestring
    {
        per_linestring(Strategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Linestring>
        inline bool apply(Linestring const& linestring) const
        {
            return detail::is_simple::is_simple_linestring
                <
                    Linestring,
                    false // do not compute self-intersections
                >::apply(linestring, m_strategy);
        }

        Strategy const& m_strategy;
    };

public:
    template <typename Strategy>
    static inline bool apply(MultiLinestring const& multilinestring,
                             Strategy const& strategy)
    {
        typedef per_linestring<Strategy> per_ls;

        // check each of the linestrings for simplicity
        // but do not compute self-intersections yet; these will be
        // computed for the entire multilinestring
        if ( ! detail::check_iterator_range
                 <
                     per_ls, // do not compute self-intersections
                     true // allow empty multilinestring
                 >::apply(boost::begin(multilinestring),
                          boost::end(multilinestring),
                          per_ls(strategy))
             )
        {
            return false;
        }

        return ! has_self_intersections(multilinestring, strategy);
    }
};



}} // namespace detail::is_simple
#endif // DOXYGEN_NO_DETAIL



#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

// A linestring is a curve.
// A curve is simple if it does not pass through the same point twice,
// with the possible exception of its two endpoints
//
// Reference: OGC 06-103r4 (6.1.6.1)
template <typename Linestring>
struct is_simple<Linestring, linestring_tag>
    : detail::is_simple::is_simple_linestring<Linestring>
{};


// A MultiLinestring is a MultiCurve
// A MultiCurve is simple if all of its elements are simple and the
// only intersections between any two elements occur at Points that
// are on the boundaries of both elements.
//
// Reference: OGC 06-103r4 (6.1.8.1; Fig. 9)
template <typename MultiLinestring>
struct is_simple<MultiLinestring, multi_linestring_tag>
    : detail::is_simple::is_simple_multilinestring<MultiLinestring>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_SIMPLE_LINEAR_HPP

/* linear.hpp
mzdx557OBeXBqWIuaK5px3u31WaTatN+4umHK/0EfEseu2r9ZAF46D9q/SD5i+wLShJzdqZlp755y+i6Vdra41TE0dceK/T98nMXLI/LViMO3XSGp8usbtL1pJcto/m214H3uLZ1bL7qmv95mNovvnwZzQOhE/I3xxsDlXPGrxD1sGb0ZMNNP8i4O9f6x5zeWTE3Ouv+KoUzJd5hek2MO5+P388POdH63+tDHA0zbXONYsJ+09kKh31+7m/fkOFhTsGn8aYQC/xnmZ+3RDz2oXst55yQ05IfndVV6COLd2IUHjrLYjlNtTAm57TPU7jklxoi896p8KR/ulivb8VH5TTfrXHZT+W3VBQeNSaqviWt8cxobTyYo435dDQEJXecC5jj9oeYMWMFa5Ze7geZQ9ssiuVRk8yuUn0HVyfb827wUW/ZOuEz64RzPYix+TRhUT4vQjjGMDzvbTejyLq+mDjRPHD2DNTHRN+Hr/3AmlHqG52sj0c49YtS1ifU/pPXYl1an1R5tHbqOJ8ijpjG8enwfsOIE66/XmHxrUO5jWsz+y0+KzFlP8UXJZ7ZT/EliZFI3nMnscxei2sIO24AF15jYWBT/8YBii3s86vqNzq8w/5alUOyZP9ZT9jO7apiU5zshmV8nXHaz+Z7V+ZcTxzRTrh79Xv4mMMOFrdzKQfNplKArXIbSaDXmOfPV3TxewzA+PsvbmVv6c47/rY2G3Ocon5bbzB9AM8BkhNaKtQqyPfsnMnJ0h44SdH0XOzr3pjhJLEsncOydI4i69vE8XUm+12/hzHDqVd2FuX8yc2MZ767zPkuc6L+3XG+LzlBOjw39QPpJ/JDBpEPs3APfJIv3tRpwqvDQGV6t8Y8Lo7oY28L/VQ3MPRl/WmIy8EhdKavnQCM3oG7PZPO9mjOT5XnB4wunTsUnAeNrKdfNOfhUwEfZc/pucGjl32nwuUBJNvQr1Re+E74r3VOInX2G4XDAzWuo7sUHg3WOK3fKRyeP2Te3TGPB3ZcRlWmnEfUOeTXyPq+R+MkeV+2eyOcB5Euz38IOZE/7Hh/ini6Pu+LeLE+7484uj7/GvEUfeoypT51jqLPBxWO1OffI5z1acaBDy+jceCF4D6h7XEgnQqM91GdrX6rOpYjL9SP2pjs0zr97R1x+BEV2W8/OuJR9y85j1lOfidsKBp3OnmPA6dUNjpT0+J74ZbHvqD0TZ8U4d435bmG5bHvJffvzonxaD/pXHCQV3KHyJCDux7nCZyMmO/Dmi8xMkov+wCJ0WAompNfIDlSoYlc32KO/JgG+4htOtg8hoeleB7K35FJuNnV5+rLYfBfGaP8cboHUzzhLtSD71YX4fQgmB/lTAVn3Q8hjjUDSG/xnQ60CRGtPhO3iQ+qbWKhs+MTaQOMewkX/rCvm0XgSGSER/aes1hyglkR5hwpOYFHDh1qHJ710HHvtTP+7AgP9x4tjXCUxd6D1LwsfFGRa7c9GsebEsvrU3kJrjlr7e72uvmOj9GfeA3mMnVOcbmRefJobu1qNySBtRb5fdKVjAfz6kdxOB1EoXi+/R7tcd677NJ8LmMQOc53Uvlw2jQo+75jgU3u8OccaAhMHl/Q7ldrPMq6T2utyqFs7llmrYglseK02Ou2brl2BoN2+jrO+ojDGXPyBnWOnA/Q5fF8QEvrdI0S/lPXBK8+fI9rglsG/Zqg+SafgLx8BN/kx+6F74rdH3kiwm5D2EgHh51qw+aJsHEb1peGtXaGm/KurTFep+Z9AjKQZXQwpsCVmns0McZp/otgrtsdEq82YOmVCjqi4Hv7kgwnK2PS4XTCh3oQYbNlxqlTtglIGduIg4EnsEbBrE5WpsQ=
*/