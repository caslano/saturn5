// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2017-2020.
// Modifications copyright (c) 2017-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_GET_PIECE_TURNS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_BUFFER_GET_PIECE_TURNS_HPP

#include <boost/core/ignore_unused.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

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
    typename Strategy,
    typename RobustPolicy
>
class piece_turn_visitor
{
    Pieces const& m_pieces;
    Rings const& m_rings;
    Turns& m_turns;
    Strategy const& m_strategy;
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

            unique_sub_range_from_piece<ring_type> unique_sub_range1(ring1, prev1, it1);

            iterator it2 = it2_first;
            for (iterator prev2 = it2++;
                    it2 != it2_beyond;
                    prev2 = it2++, the_model.operations[1].seg_id.segment_index++)
            {
                unique_sub_range_from_piece<ring_type> unique_sub_range2(ring2, prev2, it2);

                typedef detail::overlay::get_turn_info
                    <
                        detail::overlay::assign_policy_only_start_turns
                    > turn_policy;

                turn_policy::apply(unique_sub_range1, unique_sub_range2,
                                   the_model,
                                   m_strategy,
                                   m_robust_policy,
                                   std::back_inserter(m_turns));
            }
        }
    }

public:

    piece_turn_visitor(Pieces const& pieces,
            Rings const& ring_collection,
            Turns& turns,
            Strategy const& strategy,
            RobustPolicy const& robust_policy)
        : m_pieces(pieces)
        , m_rings(ring_collection)
        , m_turns(turns)
        , m_strategy(strategy)
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
                                                m_strategy) )
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