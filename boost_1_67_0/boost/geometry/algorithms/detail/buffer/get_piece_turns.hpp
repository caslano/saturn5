// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2017, 2018.
// Modifications copyright (c) 2017-2018 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_GET_PIECE_TURNS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_GET_PIECE_TURNS_HPP

#include <boost/core/ignore_unused.hpp>
#include <boost/range.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/algorithms/equals.hpp>
#include <boost/geometry/algorithms/detail/disjoint/box_box.hpp>
#include <boost/geometry/algorithms/detail/overlay/segment_identifier.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_turn_info.hpp>
#include <boost/geometry/algorithms/detail/sections/section_functions.hpp>
#include <boost/geometry/algorithms/detail/buffer/buffer_policies.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace buffer
{

// Implements a unique_sub_range for a buffered piece,
// the range can return subsequent points
// known as "i", "j" and "k" (and further),  indexed as 0,1,2,3
template <typename Ring>
struct unique_sub_range_from_piece
{
    typedef typename boost::range_iterator<Ring const>::type iterator_type;
    typedef typename geometry::point_type<Ring const>::type point_type;

    unique_sub_range_from_piece(Ring const& ring,
                                iterator_type iterator_at_i, iterator_type iterator_at_j)
        : m_ring(ring)
        , m_iterator_at_i(iterator_at_i)
        , m_iterator_at_j(iterator_at_j)
        , m_point_retrieved(false)
    {}

    static inline bool is_first_segment() { return false; }
    static inline bool is_last_segment() { return false; }

    static inline std::size_t size() { return 3u; }

    inline point_type const& at(std::size_t index) const
    {
        BOOST_GEOMETRY_ASSERT(index < size());
        switch (index)
        {
            case 0 : return *m_iterator_at_i;
            case 1 : return *m_iterator_at_j;
            case 2 : return get_point_k();
            default : return *m_iterator_at_i;
        }
    }

private :

    inline point_type const& get_point_k() const
    {
        if (! m_point_retrieved)
        {
            m_iterator_at_k = advance_one(m_iterator_at_j);
            m_point_retrieved = true;
        }
        return *m_iterator_at_k;
    }

    inline void circular_advance_one(iterator_type& next) const
    {
        ++next;
        if (next == boost::end(m_ring))
        {
            next = boost::begin(m_ring) + 1;
        }
    }

    inline iterator_type advance_one(iterator_type it) const
    {
        iterator_type result = it;
        circular_advance_one(result);

        // TODO: we could also use piece-boundaries
        // to check if the point equals the last one
        while (geometry::equals(*it, *result))
        {
            circular_advance_one(result);
        }
        return result;
    }

    Ring const& m_ring;
    iterator_type m_iterator_at_i;
    iterator_type m_iterator_at_j;
    mutable iterator_type m_iterator_at_k;
    mutable bool m_point_retrieved;
};

template
<
    typename Pieces,
    typename Rings,
    typename Turns,
    typename IntersectionStrategy,
    typename RobustPolicy
>
class piece_turn_visitor
{
    Pieces const& m_pieces;
    Rings const& m_rings;
    Turns& m_turns;
    IntersectionStrategy const& m_intersection_strategy;
    RobustPolicy const& m_robust_policy;

    template <typename Piece>
    inline bool is_adjacent(Piece const& piece1, Piece const& piece2) const
    {
        if (piece1.first_seg_id.multi_index != piece2.first_seg_id.multi_index)
        {
            return false;
        }

        return piece1.index == piece2.left_index
            || piece1.index == piece2.right_index;
    }

    template <typename Piece>
    inline bool is_on_same_convex_ring(Piece const& piece1, Piece const& piece2) const
    {
        if (piece1.first_seg_id.multi_index != piece2.first_seg_id.multi_index)
        {
            return false;
        }

        return ! m_rings[piece1.first_seg_id.multi_index].has_concave;
    }


    template <std::size_t Dimension, typename Iterator, typename Box>
    inline void move_begin_iterator(Iterator& it_begin, Iterator it_beyond,
                                    signed_size_type& index, int dir,
                                    Box const& this_bounding_box,
                                    Box const& other_bounding_box)
    {
        for(; it_begin != it_beyond
                && it_begin + 1 != it_beyond
                && detail::section::preceding<Dimension>(dir, *(it_begin + 1),
                                                         this_bounding_box,
                                                         other_bounding_box,
                                                         m_robust_policy);
            ++it_begin, index++)
        {}
    }

    template <std::size_t Dimension, typename Iterator, typename Box>
    inline void move_end_iterator(Iterator it_begin, Iterator& it_beyond,
                                  int dir, Box const& this_bounding_box,
                                  Box const& other_bounding_box)
    {
        while (it_beyond != it_begin
            && it_beyond - 1 != it_begin
            && it_beyond - 2 != it_begin)
        {
            if (detail::section::exceeding<Dimension>(dir, *(it_beyond - 2),
                        this_bounding_box, other_bounding_box, m_robust_policy))
            {
                --it_beyond;
            }
            else
            {
                return;
            }
        }
    }

    template <typename Piece, typename Section>
    inline void calculate_turns(Piece const& piece1, Piece const& piece2,
        Section const& section1, Section const& section2)
    {
        typedef typename boost::range_value<Rings const>::type ring_type;
        typedef typename boost::range_value<Turns const>::type turn_type;
        typedef typename boost::range_iterator<ring_type const>::type iterator;

        signed_size_type const piece1_first_index = piece1.first_seg_id.segment_index;
        signed_size_type const piece2_first_index = piece2.first_seg_id.segment_index;
        if (piece1_first_index < 0 || piece2_first_index < 0)
        {
            return;
        }

        // Get indices of part of offsetted_rings for this monotonic section:
        signed_size_type const sec1_first_index = piece1_first_index + section1.begin_index;
        signed_size_type const sec2_first_index = piece2_first_index + section2.begin_index;

        // index of last point in section, beyond-end is one further
        signed_size_type const sec1_last_index = piece1_first_index + section1.end_index;
        signed_size_type const sec2_last_index = piece2_first_index + section2.end_index;

        // get geometry and iterators over these sections
        ring_type const& ring1 = m_rings[piece1.first_seg_id.multi_index];
        iterator it1_first = boost::begin(ring1) + sec1_first_index;
        iterator it1_beyond = boost::begin(ring1) + sec1_last_index + 1;

        ring_type const& ring2 = m_rings[piece2.first_seg_id.multi_index];
        iterator it2_first = boost::begin(ring2) + sec2_first_index;
        iterator it2_beyond = boost::begin(ring2) + sec2_last_index + 1;

        // Set begin/end of monotonic ranges, in both x/y directions
        signed_size_type index1 = sec1_first_index;
        move_begin_iterator<0>(it1_first, it1_beyond, index1,
                    section1.directions[0], section1.bounding_box, section2.bounding_box);
        move_end_iterator<0>(it1_first, it1_beyond,
                    section1.directions[0], section1.bounding_box, section2.bounding_box);
        move_begin_iterator<1>(it1_first, it1_beyond, index1,
                    section1.directions[1], section1.bounding_box, section2.bounding_box);
        move_end_iterator<1>(it1_first, it1_beyond,
                    section1.directions[1], section1.bounding_box, section2.bounding_box);

        signed_size_type index2 = sec2_first_index;
        move_begin_iterator<0>(it2_first, it2_beyond, index2,
                    section2.directions[0], section2.bounding_box, section1.bounding_box);
        move_end_iterator<0>(it2_first, it2_beyond,
                    section2.directions[0], section2.bounding_box, section1.bounding_box);
        move_begin_iterator<1>(it2_first, it2_beyond, index2,
                    section2.directions[1], section2.bounding_box, section1.bounding_box);
        move_end_iterator<1>(it2_first, it2_beyond,
                    section2.directions[1], section2.bounding_box, section1.bounding_box);

        turn_type the_model;
        the_model.operations[0].piece_index = piece1.index;
        the_model.operations[0].seg_id = piece1.first_seg_id;
        the_model.operations[0].seg_id.segment_index = index1; // override

        iterator it1 = it1_first;
        for (iterator prev1 = it1++;
                it1 != it1_beyond;
                prev1 = it1++, the_model.operations[0].seg_id.segment_index++)
        {
            the_model.operations[1].piece_index = piece2.index;
            the_model.operations[1].seg_id = piece2.first_seg_id;
            the_model.operations[1].seg_id.segment_index = index2; // override
            geometry::recalculate(the_model.rob_pi, *prev1, m_robust_policy);
            geometry::recalculate(the_model.rob_pj, *it1, m_robust_policy);

            unique_sub_range_from_piece<ring_type> unique_sub_range1(ring1, prev1, it1);

            iterator it2 = it2_first;
            for (iterator prev2 = it2++;
                    it2 != it2_beyond;
                    prev2 = it2++, the_model.operations[1].seg_id.segment_index++)
            {
                unique_sub_range_from_piece<ring_type> unique_sub_range2(ring2, prev2, it2);
                geometry::recalculate(the_model.rob_qi, *prev2, m_robust_policy);
                geometry::recalculate(the_model.rob_qj, *it2, m_robust_policy);

                // TODO: internally get_turn_info calculates robust points.
                // But they are already calculated.
                // We should be able to use them.
                // this means passing them to this visitor,
                // and iterating in sync with them...
                typedef detail::overlay::get_turn_info
                    <
                        detail::overlay::assign_null_policy
                    > turn_policy;

                turn_policy::apply(unique_sub_range1, unique_sub_range2,
                                   the_model,
                                   m_intersection_strategy,
                                   m_robust_policy,
                                   std::back_inserter(m_turns));
            }
        }
    }

public:

    piece_turn_visitor(Pieces const& pieces,
            Rings const& ring_collection,
            Turns& turns,
            IntersectionStrategy const& intersection_strategy,
            RobustPolicy const& robust_policy)
        : m_pieces(pieces)
        , m_rings(ring_collection)
        , m_turns(turns)
        , m_intersection_strategy(intersection_strategy)
        , m_robust_policy(robust_policy)
    {}

    template <typename Section>
    inline bool apply(Section const& section1, Section const& section2,
                    bool first = true)
    {
        boost::ignore_unused(first);

        typedef typename boost::range_value<Pieces const>::type piece_type;
        piece_type const& piece1 = m_pieces[section1.ring_id.source_index];
        piece_type const& piece2 = m_pieces[section2.ring_id.source_index];

        if ( piece1.index == piece2.index
          || is_adjacent(piece1, piece2)
          || is_on_same_convex_ring(piece1, piece2)
          || detail::disjoint::disjoint_box_box(section1.bounding_box,
                                                section2.bounding_box,
                                                m_intersection_strategy.get_disjoint_box_box_strategy()) )
        {
            return true;
        }

        calculate_turns(piece1, piece2, section1, section2);

        return true;
    }
};


}} // namespace detail::buffer
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_GET_PIECE_TURNS_HPP

/* get_piece_turns.hpp
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
*/