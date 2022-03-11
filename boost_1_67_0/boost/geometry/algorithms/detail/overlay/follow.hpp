// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014, 2017, 2018, 2019, 2020.
// Modifications copyright (c) 2014-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_FOLLOW_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_FOLLOW_HPP

#include <cstddef>

#include <boost/range.hpp>
#include <boost/mpl/assert.hpp>

#include <boost/geometry/algorithms/detail/point_on_border.hpp>
#include <boost/geometry/algorithms/detail/overlay/append_no_duplicates.hpp>
#include <boost/geometry/algorithms/detail/overlay/copy_segments.hpp>
#include <boost/geometry/algorithms/detail/overlay/turn_info.hpp>

#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/algorithms/clear.hpp>
#include <boost/geometry/algorithms/detail/relate/turns.hpp>
#include <boost/geometry/algorithms/detail/tupled_output.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

namespace following
{

template <typename Turn, typename Operation>
inline bool is_entering(Turn const& /* TODO remove this parameter */, Operation const& op)
{
    // (Blocked means: blocked for polygon/polygon intersection, because
    // they are reversed. But for polygon/line it is similar to continue)
    return op.operation == operation_intersection
        || op.operation == operation_continue
        || op.operation == operation_blocked
        ;
}

template
<
    typename Turn,
    typename Operation,
    typename LineString,
    typename Polygon,
    typename PtInPolyStrategy
>
inline bool last_covered_by(Turn const& /*turn*/, Operation const& op,
                LineString const& linestring, Polygon const& polygon,
                PtInPolyStrategy const& strategy)
{
    return geometry::covered_by(range::at(linestring, op.seg_id.segment_index), polygon, strategy);
}


template
<
    typename Turn,
    typename Operation,
    typename LineString,
    typename Polygon,
    typename PtInPolyStrategy
>
inline bool is_leaving(Turn const& turn, Operation const& op,
                bool entered, bool first,
                LineString const& linestring, Polygon const& polygon,
                PtInPolyStrategy const& strategy)
{
    if (op.operation == operation_union)
    {
        return entered
            || turn.method == method_crosses
            || (first
                && op.position != position_front
                && last_covered_by(turn, op, linestring, polygon, strategy))
            ;
    }
    return false;
}


template
<
    typename Turn,
    typename Operation,
    typename LineString,
    typename Polygon,
    typename PtInPolyStrategy
>
inline bool is_staying_inside(Turn const& turn, Operation const& op,
                bool entered, bool first,
                LineString const& linestring, Polygon const& polygon,
                PtInPolyStrategy const& strategy)
{
    if (turn.method == method_crosses)
    {
        // The normal case, this is completely covered with entering/leaving
        // so stay out of this time consuming "covered_by"
        return false;
    }

    if (is_entering(turn, op))
    {
        return entered || (first && last_covered_by(turn, op, linestring, polygon, strategy));
    }

    return false;
}

template
<
    typename Turn,
    typename Operation,
    typename Linestring,
    typename Polygon,
    typename PtInPolyStrategy
>
inline bool was_entered(Turn const& turn, Operation const& op, bool first,
                Linestring const& linestring, Polygon const& polygon,
                PtInPolyStrategy const& strategy)
{
    if (first && (turn.method == method_collinear || turn.method == method_equal))
    {
        return last_covered_by(turn, op, linestring, polygon, strategy);
    }
    return false;
}

template
<
    typename Turn,
    typename Operation
>
inline bool is_touching(Turn const& turn, Operation const& op,
                        bool entered)
{
    return (op.operation == operation_union || op.operation == operation_blocked)
        && (turn.method == method_touch || turn.method == method_touch_interior)
        && !entered
        && !op.is_collinear;
}


template
<
    typename GeometryOut,
    typename Tag = typename geometry::tag<GeometryOut>::type
>
struct add_isolated_point
{};

template <typename LineStringOut>
struct add_isolated_point<LineStringOut, linestring_tag>
{
    template <typename Point, typename OutputIterator>
    static inline void apply(Point const& point, OutputIterator& out)
    {
        LineStringOut isolated_point_ls;
        geometry::append(isolated_point_ls, point);

#ifndef BOOST_GEOMETRY_ALLOW_ONE_POINT_LINESTRINGS
        geometry::append(isolated_point_ls, point);
#endif // BOOST_GEOMETRY_ALLOW_ONE_POINT_LINESTRINGS

        *out++ = isolated_point_ls;
    }
};

template <typename PointOut>
struct add_isolated_point<PointOut, point_tag>
{
    template <typename Point, typename OutputIterator>
    static inline void apply(Point const& point, OutputIterator& out)
    {
        PointOut isolated_point;

        geometry::detail::conversion::convert_point_to_point(point, isolated_point);

        *out++ = isolated_point;
    }
};


// Template specialization structure to call the right actions for the right type
template <overlay_type OverlayType, bool RemoveSpikes = true>
struct action_selector
{
    // If you get here the overlay type is not intersection or difference
    // BOOST_MPL_ASSERT(false);
};

// Specialization for intersection, containing the implementation
template <bool RemoveSpikes>
struct action_selector<overlay_intersection, RemoveSpikes>
{
    template
    <
        typename OutputIterator,
        typename LineStringOut,
        typename LineString,
        typename Point,
        typename Operation,
        typename Strategy,
        typename RobustPolicy
    >
    static inline void enter(LineStringOut& current_piece,
                LineString const& ,
                segment_identifier& segment_id,
                signed_size_type , Point const& point,
                Operation const& operation,
                Strategy const& strategy,
                RobustPolicy const& ,
                OutputIterator& )
    {
        // On enter, append the intersection point and remember starting point
        // TODO: we don't check on spikes for linestrings (?). Consider this.
        detail::overlay::append_no_duplicates(current_piece, point, strategy.get_equals_point_point_strategy());
        segment_id = operation.seg_id;
    }

    template
    <
        typename OutputIterator,
        typename LineStringOut,
        typename LineString,
        typename Point,
        typename Operation,
        typename Strategy,
        typename RobustPolicy
    >
    static inline void leave(LineStringOut& current_piece,
                LineString const& linestring,
                segment_identifier& segment_id,
                signed_size_type index, Point const& point,
                Operation const& ,
                Strategy const& strategy,
                RobustPolicy const& robust_policy,
                OutputIterator& out)
    {
        // On leave, copy all segments from starting point, append the intersection point
        // and add the output piece
        detail::copy_segments::copy_segments_linestring
            <
                false, RemoveSpikes
            >::apply(linestring, segment_id, index, strategy, robust_policy, current_piece);
        detail::overlay::append_no_duplicates(current_piece, point, strategy.get_equals_point_point_strategy());
        if (::boost::size(current_piece) > 1)
        {
            *out++ = current_piece;
        }

        geometry::clear(current_piece);
    }

    template
    <
        typename LineStringOrPointOut,
        typename Point,
        typename OutputIterator
    >
    static inline void isolated_point(Point const& point,
                                      OutputIterator& out)
    {
        add_isolated_point<LineStringOrPointOut>::apply(point, out);
    }

    static inline bool is_entered(bool entered)
    {
        return entered;
    }

    static inline bool included(int inside_value)
    {
        return inside_value >= 0; // covered_by
    }

};

// Specialization for difference, which reverses these actions
template <bool RemoveSpikes>
struct action_selector<overlay_difference, RemoveSpikes>
{
    typedef action_selector<overlay_intersection, RemoveSpikes> normal_action;

    template
    <
        typename OutputIterator,
        typename LineStringOut,
        typename LineString,
        typename Point,
        typename Operation,
        typename Strategy,
        typename RobustPolicy
    >
    static inline void enter(LineStringOut& current_piece,
                LineString const& linestring,
                segment_identifier& segment_id,
                signed_size_type index, Point const& point,
                Operation const& operation,
                Strategy const& strategy,
                RobustPolicy const& robust_policy,
                OutputIterator& out)
    {
        normal_action::leave(current_piece, linestring, segment_id, index,
                    point, operation, strategy, robust_policy, out);
    }

    template
    <
        typename OutputIterator,
        typename LineStringOut,
        typename LineString,
        typename Point,
        typename Operation,
        typename Strategy,
        typename RobustPolicy
    >
    static inline void leave(LineStringOut& current_piece,
                LineString const& linestring,
                segment_identifier& segment_id,
                signed_size_type index, Point const& point,
                Operation const& operation,
                Strategy const& strategy,
                RobustPolicy const& robust_policy,
                OutputIterator& out)
    {
        normal_action::enter(current_piece, linestring, segment_id, index,
                    point, operation, strategy, robust_policy, out);
    }

    template
    <
        typename LineStringOrPointOut,
        typename Point,
        typename OutputIterator
    >
    static inline void isolated_point(Point const&,
                                      OutputIterator const&)
    {
    }

    static inline bool is_entered(bool entered)
    {
        return ! normal_action::is_entered(entered);
    }

    static inline bool included(int inside_value)
    {
        return ! normal_action::included(inside_value);
    }

};

} // namespace following

/*!
\brief Follows a linestring from intersection point to intersection point, outputting which
    is inside, or outside, a ring or polygon
\ingroup overlay
 */
template
<
    typename GeometryOut,
    typename LineString,
    typename Polygon,
    overlay_type OverlayType,
    bool RemoveSpikes,
    bool FollowIsolatedPoints
>
class follow
{
    typedef geometry::detail::output_geometry_access
        <
            GeometryOut, linestring_tag, linestring_tag
        > linear;
    typedef geometry::detail::output_geometry_access
        <
            GeometryOut, point_tag, linestring_tag
        > pointlike;

public :

    static inline bool included(int inside_value)
    {
        return following::action_selector
            <
                OverlayType, RemoveSpikes
            >::included(inside_value);
    }

    template
    <
        typename Turns,
        typename OutputIterator,
        typename RobustPolicy,
        typename Strategy
    >
    static inline OutputIterator apply(LineString const& linestring, Polygon const& polygon,
                detail::overlay::operation_type ,  // TODO: this parameter might be redundant
                Turns& turns,
                RobustPolicy const& robust_policy,
                OutputIterator out,
                Strategy const& strategy)
    {
        typedef typename boost::range_iterator<Turns>::type turn_iterator;
        typedef typename boost::range_value<Turns>::type turn_type;
        typedef typename boost::range_iterator
            <
                typename turn_type::container_type
            >::type turn_operation_iterator_type;

        typedef following::action_selector<OverlayType, RemoveSpikes> action;

        typedef typename Strategy::cs_tag cs_tag;

        typename Strategy::template point_in_geometry_strategy
            <
                LineString, Polygon
            >::type const pt_in_poly_strategy
            = strategy.template get_point_in_geometry_strategy<LineString, Polygon>();

        // Sort intersection points on segments-along-linestring, and distance
        // (like in enrich is done for poly/poly)
        // sort turns by Linear seg_id, then by fraction, then
        // for same ring id: x, u, i, c
        // for different ring id: c, i, u, x
        typedef relate::turns::less
            <
                0, relate::turns::less_op_linear_areal_single<0>, cs_tag
            > turn_less;
        std::sort(boost::begin(turns), boost::end(turns), turn_less());

        typename linear::type current_piece;
        geometry::segment_identifier current_segment_id(0, -1, -1, -1);

        // Iterate through all intersection points (they are ordered along the line)
        bool entered = false;
        bool first = true;
        for (turn_iterator it = boost::begin(turns); it != boost::end(turns); ++it)
        {
            turn_operation_iterator_type iit = boost::begin(it->operations);

            if (following::was_entered(*it, *iit, first, linestring, polygon, pt_in_poly_strategy))
            {
                debug_traverse(*it, *iit, "-> Was entered");
                entered = true;
            }

            if (following::is_staying_inside(*it, *iit, entered, first, linestring, polygon, pt_in_poly_strategy))
            {
                debug_traverse(*it, *iit, "-> Staying inside");

                entered = true;
            }
            else if (following::is_entering(*it, *iit))
            {
                debug_traverse(*it, *iit, "-> Entering");

                entered = true;
                action::enter(current_piece, linestring, current_segment_id,
                    iit->seg_id.segment_index, it->point, *iit,
                    strategy, robust_policy,
                    linear::get(out));
            }
            else if (following::is_leaving(*it, *iit, entered, first, linestring, polygon, pt_in_poly_strategy))
            {
                debug_traverse(*it, *iit, "-> Leaving");

                entered = false;
                action::leave(current_piece, linestring, current_segment_id,
                    iit->seg_id.segment_index, it->point, *iit,
                    strategy, robust_policy,
                    linear::get(out));
            }
            else if (FollowIsolatedPoints
                  && following::is_touching(*it, *iit, entered))
            {
                debug_traverse(*it, *iit, "-> Isolated point");

                action::template isolated_point
                    <
                        typename pointlike::type
                    >(it->point, pointlike::get(out));
            }

            first = false;
        }

        if (action::is_entered(entered))
        {
            detail::copy_segments::copy_segments_linestring
                <
                    false, RemoveSpikes
                >::apply(linestring,
                         current_segment_id,
                         static_cast<signed_size_type>(boost::size(linestring) - 1),
                         strategy, robust_policy,
                         current_piece);
        }

        // Output the last one, if applicable
        std::size_t current_piece_size = ::boost::size(current_piece);
        if (current_piece_size > 1)
        {
            *linear::get(out)++ = current_piece;
        }
        else if (FollowIsolatedPoints
              && current_piece_size == 1)
        {
            action::template isolated_point
                <
                    typename pointlike::type
                >(range::front(current_piece), pointlike::get(out));
        }

        return out;
    }

};


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_FOLLOW_HPP

/* follow.hpp
F0kjTvBDep/03qMe09EgKGXg/RDmAY3C6wlxkY5/1SRRwzOz0S5Rcwo4RM7CeNL8DApbT6SDy2emY47i3l+nuGsr40K6N5XF3c+kL02I3tyGsteWo6553aiOumvnwlrmw9KiqgquuosdjDN6aEpOLSBb7DXS5za47R00RZxHAVswVATmcjGWpgqinl71Bf/WD1RGD6wX5xRXitUILAvFq86zWl9bSo62QV/6Ay25L7OAynqnsPfJrec4E5YsICJvfTUXRbEY0jWae3Pfe43HgFddWRk+Rx7kEYouAsltmuQKovGnzUKaEVr+SVRg1EDvUIfaPda/wkPSBQ0HvGqhCGvMKosoqHLnf18TO9JdvcBr/dg9nXPkgVF/TwpD8v5puebphuH8vcvvMTFRzQjGNUsqUMhGTV697eaxvIzYm9HnpCMtZzfyaK7npVPtUiWYBDlmJIvTyIWTNog7W/g2a1463RuUwggfPUY9rRPmCKPpg58LElRYcZwmksnd35/QJpQuj1dTtd02EKq2cWNjdqrMbFeFbhE5odrDQTApy9PRf7acw3nyNOvgU46NPjh6B0suxogTKmxSEhN8zTeXu01QpCOe2onXp4HdZCFfdbec+W9lSfx/RrQRP21pwwP/Ad6+kPTORGdpBc9S+NWMh2BULeUvJ462KpcR2pOolp3LVxSHtrOQK3/0K28kL29JfOncFXXY5c7WAYIgs22Qn0HSXMCRSYpaGZ/S8A6GtWkuSrLgBzV/lmYyqSjoKxyR+mwWdMV2ILwf2cHQBK6Gi89QjFOVVo3Bd67zqlppT6EQe8BbA3XEikLh4i8NrdbY+1CIRDoRvt8gbgo59Pe+iD/cXgUHHX0g0G+We0uQYk7WzZJWUP214cZOU9xsTupLJeslKqPvxSO9nYkwupUUDwwH1DnfgOxVAetUpf9bFWrWPOgtWQcQOii4YA7osHdShjJ4eaiMEGO19kqtEefLlrjsyYpa6K5x79HjYmrQ9XZtALyjPai61fX3mEN5yGv3MNthD042suGU69HRVV+BN3N25nZo7Itq8YPg9ISgCka8sEn8Zq/P3F5m4Qn+qZa3LdT4dK8sCTdmx55/fCsBxKcY1ue+ke1oG+bWnTGxdwbsNVOh17ad7pVZfJe3VTBgx90euxNjF08cjBdn94eJGeNzEipQNxXEpwjWRx/o07cR/rWHtBdNiMc9rfeHETYHxM9uSefueyUxzaeKCmo5EDdpuUDCsqbTbMWhNtEP4ArfRH5jra8KHH7aCyf7JYwe7YLSUe2w4IGzJtb5+gPU+/MphLRJ2OrtzT46MYqtG0WSYd8VYgaVC8bIBcsq88YsHMvfG0pN991/Li7fYC2xSAyrQk1O6BxaxwC4z6koT8Yr1PKpFIV0H2aQ9VaV+EKDhNvfa9BtnAmhTEJV4AV34m+aHKb0HzwYxOj5paHCfkhY1oony0u0vj2TNwvlGoaZQpUOwRL57BumMpG8Yw6OD/aly5DztXC9ljQDlm/GBQheXGxCXdogMTaZdOVXuRBNLZY0o8yXTCJbAxJX6bxkJg5ZQrs1KaD29thnQoc+baeSPnybmSUKQHnyGzCGo6rasQOEUBpMIsA8hWmG0agXoHl63zy3A83BYABTv8j+Szijuf37Nmzm4GtMP7fiDQDDt6o4ctrIKWXgfFMJq5uFzDpY/Umkp3CaCUJZoLePYjqM8qMF8VSDe0WsyRUtiU8tZ/Vq+/Skd+C9d+CmPQ9J6s6KqIfwZbphXBdAhR35c8/BQ2kRwQYOH0mcze9ni7xy78vdrUol4dPFU5obuuHqnQbJ9sBiOeXqPzza4kbSsbQCBLMXW7gtoXBBWUVtXgZuW3IP2whbHRCDnOe55O5ZC+CTaYS/OxereAAdoDrrWKPKlYWEpd+vZFR2hIyB2uIhRfUNPGdYgRFiruZbWRPlnjAr4jSwxgkNZoNCSUsOi73U6NZQ5dEwsAi9NqlDzCfmy6Eq4KMaFGuHeDL/iqX5yJqDA/qaOebXcjGF2x2IE6svErHz4tmYLjs3AAgs99NzPtlfNrogxZknk/kn6O1By/rYsW7GeH0Sp24m+NvpO/OG9UEX/Ez8lVM7s03eFqnWjBEvusm0AtBGgANpy0b86rm8sJpG5repWBwVLx01/sJzW9qWTllBGEUA7QPLg0sv3IFpjF5syII5cGlMp9RpFf2NjK6564csYPg5p7uO6nPjwRgO8YUBJjXSsNf4luQwe0PLWDonjOc14sP3FTelrDSd6NxjEdoidJtMFu3nBNerJAeydEymSKWAcZcQTJfAMhQbNvLz55oGdOQeDCftw+PxJtJSnA5viMWAmdMyQh8PGuC4Xg1ddEVRTX+l+MvhEhOBRcT90Pj6jJWBauNUOjJUEUuwTSLbKeS7hGVhODqYz78b/grM/U3lXk+Ai50I2A8AAPQL+BfIL9BfYL/Af0H8+vML8hfUL+hfML9gf8H9gv+F8AvxF9Iv5F8ov1B/of1C/4XxC/MX1i/sXzi/cH/h/cL/RfCL8BfRL+JfJL9If5H9Iv9F8evvL8pfVL+of9H8ov1F94v+F8Mvxl9Mv5h/sfxi/cX2i/0Xxy/OX1y/uH/x/OL9xfeL/5fAL8FfQr+Ef4n8Ev0l9kv8l8QvyV9Sv6R/yfyS/SX3S/6Xwi/FX0q/lH+p/FL9pfZL/ZfGL81fWr+0f+n80v2l90v/l8Evw19Gv4x/mfwy/WX2y/yXxS/LX1a/rH/Z/LL9ZffL/pfDL8dfTr+cf7n8cv3l9sv9l8cvz19ev7x/+fzy/eX/C8zFvg07Syf2nPIcsiOngV+nbI2tgI8pkTgz1Fyha7RS9KF9fabdyVf9oBQz1oWOcD2DbLNVJRCc6F4GB2xs4TvKHcHnVfvsApPphYigExM7X3APO+nahdpN/iN+9+9ZtSpldtDHihjPtzBzAxv3qZ2nZaLBj3mDmO1KIk1X2zqKNno55uzqRkc6bBIH23PHmnPVinSWkCxrlcytGGtfJXrQqeUi1JkFmZGRNnTOtbTmcqtbEG8IOAqZDFEMPpR6ebnsQDMI3MGPvuwBwdfX3FtxFzmua1Q25GLmiWRLQH2rLXo1cgUVYVWC4Tlx3LBRAS3OP6+1Z/IFJ7rMHiupQXFciW6zRPrzvGOBMc1Is140+5nHInjYiWqBLdDw6DiYZel382vaaKN8gF4dLDLbxU7CA2YM8Wmb7DX9gj73QxWIB+KHFhGxS1UNzn6945PB1C42Q7HJWDlPtpP2CDVNquDFm3HBbDHVdLQ/T9qttDwaE3XSN0AimYLmlArrEsnNXEVVUlIbE4OO2RL5APrS4J0VYkWM28rlCbD+0guSmiIiwqKDE7jEP4j/EMazF0vWd/UkbSjwlNzZMsxSU/BydZLvvf/BKRQpgm7Q616+wSA6v9hVDGyew7dw9FY95xWWAl8NYqXhslID7bhPw90mI43UdKQ+0UpQOGBIeuZ7prpUtCZxhX7cZBzmynCHCMPJWUl1uUqB1sksaRMZG/W640c5iO8qUYPixjBfjxLflzEU8A1Gzy1orDp4w3DX2Eee/GyGJt3ldbHEyv37EcLiDzPYGjBtlGsYgLeYZnTquLeW3ZpjIMS7si2pskV4UxnkJa+xz8HUFkBFwzoq8twdnqWziJh2nCXtBAEUXsqoMGpro55yr/f2nUhKkHC8INbSUmOJq3SIq5mY+g2l1a/WiknLHVvtF8suNbYxugLEF6+fpYWfzEHulXcNH4fuQW6MmqezcE+Rlrhwz3eXl2ipTcaDq4W7QW715LFwT5lJQndNb+qc1pNcs+9lDOlNVgJU+14dnOJZnirFoywb9TxUDVoki/hCDhd4RnEoGPO+ytkjCPJeQs/+iSYGkqkKniRVBX0byRFax/t12WY1SVy6FpOyBqlyc1FDwUdv+w/vcAV5qtQTgupKMVK32RUENuK5a2bHy7pRDV0AdRIdeYRgV5o9tN0nUyRzreZPpHll1PiArC3r1Qxv0ch5AwUNK4lIYXP6CaYZMQThgLUgTGt2CS4dXi8NIlj4jvo4Rj/ACmZ3Dxgmg/b9A331lHHJAlgt3OrFcYluSIMzfIMx6rapTQ71rxQKpfc0Aj0nhIdXeFaw7P2LHTGKiKKUg9fZhwpd5Hoso9X+KRstJFp+m75hBFZrLwy7NBHa7sKsl3w/3416/UNbNKoSqxJRKEhF3OhQzsqt2xsUZREK6HOUlc5rErpJaEJiShJJNUQHdNWtnsbwuuQdd+JFZ/Q1jwY3j3dONpawLaqUfLHBv8ix/PqQiGMNhMNMCxnfJUavcsltIn+xbHTFS57mnrLGRxEaUVgPQUtqGdnvNiPMuLsP+l/xBczKH7Iws3kiJ60ZJafBTOdeEqaVoSRN0jW3LKLL3N5bAlm82pS9M820x3SwbOgVMhk8ms/xu/QKaPW84dK79gfXFjSErRKZ54xSnMDmkwi3CCYM4CNvpPOA1BmAqkVUgzWoh3eVtgBXndkWuYJag88HQEILiWwH+Qai2pXRgO55qoSrStypWVMa0zRNA5i/1Jm5/2REdfnC9mgFGaDEkJlT4sgAJZPw3Cb2w7hFRyZi9334JJznj8XAX5Zds0aiuRCuuZblcRbI1a/+VDUU7SCb+9O49k9mtTrXciLFsXVB9wc4ht+gsqJW1sa/L67aMG1injOkMqFyvZZNZ7MgAe2bGh7QrxWP1pECtUxNrpulv44zaGPhLDbN3a1HAFkL57SqJKrUySGN4S+9SRh3qzGwMFdCMkj4twwqY3Zute3YwjoXel8tjixHe8p4s9noRr/WePLOCVTPMxnlU6gVqhDVXuVzd53ZBFRf94HX0PlCLFsWkL3PivsAGHYibGcsgUqc8Rj8GS/3JnVOyGDBO/vQBh1Tzr2Mp92N6LVYvjEE00+0cfEtt+938U1HTGqCselh1clgqSqkpNs+IGhWDvar82Ya/rJ6LUMnXMrxyZqMh+/f0ubpPbu2xg7zifFRL12OFxKXGNJyxo1XlMQd/YB0hs22sxyYiJZIlgsAvtxRNgYDufvQj1H/qHIbB19BckwYnwa1NlXep9tLMFJvHBogtsUowBjcD0vVIzbcbL3e9/4pY2n0gDaFesdnRGiAx2ilu0sX2ouk3994/xH1omTcH2x5Ehh8uWtJf5UaGzQlAxlUTicqBWsCt9Q9vGi1t+jkkVQfOI1TUgUMqxiXXDTG5NeG23LUOZeIlFfFlF/x9aHLaMdsO3b0Px9TlNqJ90aSZs46UYPfn7P999IJn3+z8c+xjkpooL0QCraHyMEB5pLXME0kXNQVinByGbBoO6p8jNNLKkOgJoOrujlF7GFdv+1NzPCKhncylI7w4D3pXafo26z1nO7EcPxw1sCoOHOPSx2Ra93DfuxOGUn8dAnSFZ7FgIzfXvjnL4016flB76FCRnVy8b4kcOFy+mK5/62VI0+TExRocGT75BzPIjikiTzcfh1SSdOp8XreKWetLQ6FO5lMR5D74ab16LqTUMiqSRkU9d44IQnleIypYroBzICpaixgC3IMPVGBlR528EgXhCrUVJefrOTymcGQh8Vpi8Z3HTKBPVxmfmLctbbXxU2J8dT4WJ4N47gAGCiaXI+aJ++7bmmUmjHUDM2oTFbXHP2fmKoasZfKzbxF60Cc3jY2fXThoby/T60p5/fTKWCx5N51sp5bj3WPNcrWdtyBg6f8eytWXXRmTKpeah9lw8lVCliD9cFvDgj6nzhC6LwpNAvMXuV2NI0u1LtOoQOiCEPn2pLlhzRcR1AzURrWaDmJXud9WTDlV6/jeZbEfrrb2BxdxHGSPzpYaUI/2+i1sz2MQBiPNwZasUVtlTVpmRsv4LxxvsCsof/gQXYzBD9NAHvehH0W+mx1IliB2yxDEXYWLCxVqMxBgnVcAMc3iAUdx1vsaAOCsg0+MtDb12m4JCDLAKu7PCpvKoqyPE7PH5Grc6/5r+ckEh19W/L0OOM9i6TLCsFRixg0y34jA+osaDXRzFxh899CqwpmuhSYba561XFE8sLREql1tar+3zz2GXkx6AqWJQeVgOBIscyaepCfEoFyjTs8iTPwk+8Ebn/JxXrQoaU1OxFGsGJU1ZN9RY1eDXktY1jc+SJUxrPGMZuRSi7cQN0CitsiI6kwuKR/lG8PEeaPdNebVLDLGNAtFYJ9svlnFpkwx2FB+mO2MU5EgGvIB+gsiKr2CB53QcMaL+h3RZwh7Ogm/+Tihj9poP7qhk2JsOAMZHxuh4Ystgt0RROvf3Zy+MTrx3wC4XRaiZ3l0i33+dfAWU6/dGtc6sBn8XV9usODjpvBLXzTtlA0z2qzAI83ayWe1lFsF+icHvE8pnHSHmW4XfVeNqp1m3a7qaVBXaUczK72EH04C1VRyuKPdxi99lHRiC/9QBX6oPGCQG2ExDkE9vedWTLDX48T+VSxbPoE4Lptasj8k3KlcFjGPyLK4ZBFhHnxC0m3Eral9Dk7Gr3X5sZ+7P7zR8StBcURK4F1w9PJIwYViXsi2w1jL+9SAMTT3s5j9y93WjbsMtnBTSIyPf81KHfxy5EGtSm/i+EE85YEJ+GlMYhn661+0Wg7rHHu0gqAsHfAywwLSCeWwAZARKPwMdLelBt5s6AwrgOuupLD8vq3Z+fo3J0F+m21yaqIYeuscicGLWh5/5XnEXysw3BA15035cBda+lmgdWp4aAzIPsf52RA8k+hYqxaHgY453XNEqzKi5w9VuOLWyS15LesjWHbWZcx9B9MzhI/27h0kPZxEyzlnNo57mB2T74f2kS+cdLw46/Y2HcENVFf2kRogNButYBgt1CwN3HqhWj6ElwGTCOJcUx2lHZ10kwZaTBBaJ8Em4CFPtL8pIEEjxgAsFg57PzYPxxnnf6nhZw+RE+3I63x81t7XsFscOMpczEfU6akge2zIRLZQm9Vaxbe1ZiNoc1P9/0LpEpu+Of9Z5COts55A1VB7iRuqmHRQuDTL0bzIQms5jXr4geK7krjgwm8cRrM6jAHUwktZw+DCYyPN0kJssDq01/CyQ32a1wEPAS+1vSEWu/hwFzODqrmzG2DQDR7SqZSyvkdsaM8ij5zpkFoUTFHG3qDSYuQbK/4wF0Th++1L+/JWdmkmzwA9bfc9GIMBfaJFM98YTmMxPhFFTV/3Hkk0gjBFOkmmf4g6SZNPgx8Lh38SctENyluT09Us+Kc7J0f0Pcq3Tvk5NJXc+UitA8Y6CtzRaJ37tgs1OJ++yPV5eh7F2gilS3TnH+XNXZbvIX/Fqrmkea2Y8mdwLjnmuCZfhDm2S0iZdcfQNz8AbF6TW0qzbGRHFzi8g/sJLdJqzZoef747pV5FEkSxUIwypuWueQAzOr58YMI3ZPUQy37tA8xPewvqS8X0o1/0BsgRL5OdZMkptSY/aGv2mRwPd5lSQ6nfbI2ecgOIzoL06TKeduC+2nSKpdCdgo2XFq7VoP4C7zB0UdrEF/dnX27PpZJ2L4HoNfpiXDQTPghwk40gurQHQJ4qJO/KBxlfSegY2izfc3jhaxj/R61B/NOxHBoBRrfhHah6oKXBUGFCmp3Tphp0/Xu7d+7V4xEfSEfvGuPPvgsh4tEgZmfT3CB6qNGcRPFUJB274TK9H1dXB8cGV7imHifp0cc4nNsASevNvbGlfnsNmzVl4t/+x7mP0YaYxof2l7C2yG3Hg0I+UH1uKrcUxFtntzV77YPVfwmLopQ42y9z5EDMUZF3QukAz+KUcceAHGr4dR4BweOFXHEzXm+06YnjUkOm6ioiXHz3UuonUxOwX22FY6cL77SY1IK7VKSuRVGt9HTVM5AZxOFZvEOJpLWzyND/8wWLTZzYqWYy5Od5L3sIs0/niritXgCHZcSuH0Zi3YqwRr0f+bn1S3qMUSWA9MYXL3zcYNoqeXhDLILwrvjlZKVkPNJqHWQ9xGJA1xc4qBTRSJZN+TFfjjl9vHNllTze/VOe/51qU6JWHJCjpzz5hYva4V2HcMcxj63b2UhpOtMrWyLjkchFvCr0N5mfoHJ0FSBYoPet2AnyWARYTG1fYX4+HfkrcVovevsPr/fbZ6kqNPP4rZZsqMCtmGz2pjIGb9S0FF/u3nOG1p2EF5wS6W+xRxEu5D1bPDFpraaQ4MaGMQl7VbFMJvXF7TZDDOPxA3dTAtHCfl84mmZhvvYudsMphfgHbkyJ2fsYnNqzpaQtMtCJ+esvf1kCUw/Wmmn5tFnWXHTM/6EyJ6/D9TziHa3d4v6ZMjMQt1NC8PfvJZFLO2nfImko1iCj7hrbJiiyzeuWVnPBBveT6wK5BXBgqdYtbdy8c1vWImWaa5dqaWiZpaVvE5PrXfT+4z4eRCA8nJSb9zfdiyzw2dmkk4Sb86jRXFk68wU6D54hZp5bO2vaOrL184mEraoah+NlmzRLhgvVIKTyV8Qsg9fr8F2yMcQwjU8Lzd5e+Xh92EO0bzjahzVYgW0vDH7xthu0Rsg/3z1m8PsUa+QTrnTbPscamjx+/k3+dmaoZS6+KsV9PTLxElnG5eMTbe6bzV1CgU7lMwtALHHP47h/tvcFD4vcOgYxST9QcsyPnuPFf1v1E+2N5yX4tLTq2Ric54QItMQAEoASFVARIVvBmhdk7Rm8jIfAcXBzYq+aoENynbgexO1cY1wzgyAI0c2g1MmR/Ob7XcBpIAkBgUS4NwfaDvlcxdLDpiIpuT+j2zHa8mMRvKPb56vzuOvNt+Zrv9P+TnO9+kXbCx0eK4tCJUeE6E9RHVZTveRVpeOJ1clugb2eJcDw0ltqDrZQy/rssIo5LcRJrtQtd4NccTI1KtSUsPD8YIWOPKBQCoCgadzGOcPZOsWwkbIZ2PhcRnByws9YO9/rHNl6VsQcyDB83ReI+X2+TzEFWhhuTO4ghHI8pvF801GRzXUAQkErHiFlU4/Jsu+Hp79pO0O4MFTQQXIaGlQgQJqh0w+EGB4Zs5dfProHzaXHaHjngSO8jNXJtE0m1DBDT1cw24cAJcqH8Uyq/ijqENFQjUi7+WfpiJY3QGzLKqBnI6pyaQc/0GB2Sb9XucJ1aZMBTMGAuJkn7U2GRsdeufaKxLc6aI7atlX09v117l2GtvN7qqJkuEvgqoBhKMwKnTnLIKHPp3KyDcQ8geqFNGUwJVfLv9P8eJa42RVZ74=
*/