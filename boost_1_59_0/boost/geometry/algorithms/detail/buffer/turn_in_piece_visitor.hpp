// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2020 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2016-2022.
// Modifications copyright (c) 2016-2022 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_TURN_IN_PIECE_VISITOR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_TURN_IN_PIECE_VISITOR_HPP

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/config.hpp>

#include <boost/geometry/algorithms/comparable_distance.hpp>
#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/algorithms/detail/disjoint/point_box.hpp>
#include <boost/geometry/algorithms/detail/disjoint/box_box.hpp>
#include <boost/geometry/algorithms/detail/dummy_geometries.hpp>
#include <boost/geometry/algorithms/detail/buffer/buffer_policies.hpp>
#include <boost/geometry/geometries/box.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL

namespace detail { namespace buffer
{

template
<
    typename CsTag,
    typename Turns,
    typename Pieces,
    typename DistanceStrategy,
    typename UmbrellaStrategy

>
class turn_in_piece_visitor
{
    Turns& m_turns; // because partition is currently operating on const input only
    Pieces const& m_pieces; // to check for piece-type
    DistanceStrategy const& m_distance_strategy; // to check if point is on original or one_sided
    UmbrellaStrategy const& m_umbrella_strategy;

    template <typename Operation, typename Piece>
    inline bool skip(Operation const& op, Piece const& piece) const
    {
        if (op.piece_index == piece.index)
        {
            return true;
        }
        Piece const& pc = m_pieces[op.piece_index];
        if (pc.left_index == piece.index || pc.right_index == piece.index)
        {
            if (pc.type == strategy::buffer::buffered_flat_end)
            {
                // If it is a flat end, don't compare against its neighbor:
                // it will always be located on one of the helper segments
                return true;
            }
            if (pc.type == strategy::buffer::buffered_concave)
            {
                // If it is concave, the same applies: the IP will be
                // located on one of the helper segments
                return true;
            }
        }

        return false;
    }

    template <typename NumericType>
    inline bool is_one_sided(NumericType const& left, NumericType const& right) const
    {
        static NumericType const zero = 0;
        return geometry::math::equals(left, zero)
            || geometry::math::equals(right, zero);
    }

    template <typename Point>
    inline bool has_zero_distance_at(Point const& point) const
    {
        return is_one_sided(m_distance_strategy.apply(point, point,
                strategy::buffer::buffer_side_left),
            m_distance_strategy.apply(point, point,
                strategy::buffer::buffer_side_right));
    }

public:

    inline turn_in_piece_visitor(Turns& turns, Pieces const& pieces,
                                 DistanceStrategy const& distance_strategy,
                                 UmbrellaStrategy const& umbrella_strategy)
        : m_turns(turns)
        , m_pieces(pieces)
        , m_distance_strategy(distance_strategy)
        , m_umbrella_strategy(umbrella_strategy)        
    {}

    template <typename Turn, typename Piece>
    inline bool apply(Turn const& turn, Piece const& piece)
    {
        if (! turn.is_turn_traversable)
        {
            // Already handled
            return true;
        }

        if (piece.type == strategy::buffer::buffered_flat_end
            || piece.type == strategy::buffer::buffered_concave)
        {
            // Turns cannot be located within flat-end or concave pieces
            return true;
        }

        if (skip(turn.operations[0], piece) || skip(turn.operations[1], piece))
        {
            return true;
        }

        return apply(turn, piece, piece.m_piece_border);
    }

    template <typename Turn, typename Piece, typename Border>
    inline bool apply(Turn const& turn, Piece const& piece, Border const& border)
    {
        if (! geometry::covered_by(turn.point, border.m_envelope, m_umbrella_strategy))
        {
            // Easy check: if turn is not in the (expanded) envelope
            return true;
        }

        if (piece.type == geometry::strategy::buffer::buffered_point)
        {
            // Optimization for a buffer around points: if distance from center
            // is not between min/max radius, it is either inside or outside,
            // and more expensive checks are not necessary.
            auto const d = geometry::comparable_distance(piece.m_center, turn.point,
                                                         m_umbrella_strategy);

            if (d < border.m_min_comparable_radius)
            {
                Turn& mutable_turn = m_turns[turn.turn_index];
                mutable_turn.is_turn_traversable = false;
                return true;
            }
            if (d > border.m_max_comparable_radius)
            {
                return true;
            }
        }

        // Check if buffer is one-sided (at this point), because then a point
        // on the original is not considered as within.
        bool const one_sided = has_zero_distance_at(turn.point);

        typename Border::state_type state;
        if (! border.point_on_piece(turn.point, m_umbrella_strategy, one_sided,
                                    turn.is_linear_end_point, state))
        {
            return true;
        }

        if (state.code() == 1)
        {
            // It is WITHIN a piece, or on the piece border, but not
            // on the offsetted part of it.

            // TODO - at further removing rescaling, this threshold can be
            // adapted, or ideally, go.
            // This threshold is minimized to the point where fragile
            // unit tests of hard cases start to fail (5 in multi_polygon)
            // But it is acknowlegded that such a threshold depends on the
            // scale of the input.
            if (state.m_min_distance > 1.0e-4 || ! state.m_close_to_offset)
            {
                Turn& mutable_turn = m_turns[turn.turn_index];
                mutable_turn.is_turn_traversable = false;

                // Keep track of the information if this turn was close
                // to an offset (without threshold). Because if it was,
                // it might have been classified incorrectly and in the
                // pretraversal step, it can in hindsight be classified
                // as "outside".
                mutable_turn.close_to_offset = state.m_close_to_offset;
            }
        }

        return true;
    }
};


}} // namespace detail::buffer
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_TURN_IN_PIECE_VISITOR_HPP

/* turn_in_piece_visitor.hpp
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
*/