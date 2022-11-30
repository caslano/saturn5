//----------------------------------------------------------------------------
/// @file move_blocks.hpp
/// @brief contains the class move_blocks, which is part of the
///        block_indirect_sort algorithm
///
/// @author Copyright (c) 2016 Francisco Jose Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanying file LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __BOOST_SORT_PARALLEL_DETAIL_MOVE_BLOCKS_HPP
#define __BOOST_SORT_PARALLEL_DETAIL_MOVE_BLOCKS_HPP

#include <atomic>
#include <boost/sort/block_indirect_sort/blk_detail/backbone.hpp>
#include <future>
#include <iostream>
#include <iterator>

namespace boost
{
namespace sort
{
namespace blk_detail
{
//----------------------------------------------------------------------------
//                          USING SENTENCES
//----------------------------------------------------------------------------
namespace bsc = boost::sort::common;
//
///---------------------------------------------------------------------------
/// @struct move_blocks
/// @brief This class move the blocks, trnasforming a logical sort by an index,
///        in physical sort
//----------------------------------------------------------------------------
template<uint32_t Block_size, uint32_t Group_size, class Iter_t, class Compare>
struct move_blocks
{
    //-------------------------------------------------------------------------
    //                  D E F I N I T I O N S
    //-------------------------------------------------------------------------
    typedef move_blocks<Block_size, Group_size, Iter_t, Compare> this_type;
    typedef typename std::iterator_traits<Iter_t>::value_type value_t;
    typedef std::atomic<uint32_t> atomic_t;
    typedef bsc::range<size_t> range_pos;
    typedef bsc::range<Iter_t> range_it;
    typedef bsc::range<value_t *> range_buf;
    typedef std::function<void(void)> function_t;
    typedef backbone<Block_size, Iter_t, Compare> backbone_t;

    //------------------------------------------------------------------------
    //                V A R I A B L E S
    //------------------------------------------------------------------------
    // Object with the elements to sort and all internal data structures of the
    // algorithm
    backbone_t &bk;

    //------------------------------------------------------------------------
    //                F U N C T I O N S
    //------------------------------------------------------------------------
    move_blocks(backbone_t &bkb);

    void move_sequence(const std::vector<size_t> &init_sequence);

    void move_long_sequence(const std::vector<size_t> &init_sequence);
    //
    //------------------------------------------------------------------------
    //  function : function_move_sequence
    /// @brief create a function_t with a call to move_sequence, and insert
    ///        in the stack of the backbone
    ///
    /// @param sequence :sequence of positions for to move the blocks
    /// @param counter : atomic variable which is decremented when finish
    ///                  the function. This variable is used for to know
    ///                  when are finished all the function_t created
    ///                  inside an object
    /// @param error : global indicator of error.
    //------------------------------------------------------------------------
    void function_move_sequence(std::vector<size_t> &sequence,
                                atomic_t &counter, bool &error)
    {
        bscu::atomic_add(counter, 1);
        function_t f1 = [this, sequence, &counter, &error]( ) -> void
        {
            if (not error)
            {
                try
                {
                    this->move_sequence (sequence);
                }
                catch (std::bad_alloc &)
                {
                    error = true;
                };
            }
            bscu::atomic_sub (counter, 1);
        };
        bk.works.emplace_back(f1);
    }

    //
    //------------------------------------------------------------------------
    //  function : function_move_long_sequence
    /// @brief create a function_t with a call to move_long_sequence, and
    ///        insert in the stack of the backbone
    //
    /// @param sequence :sequence of positions for to move the blocks
    /// @param counter : atomic variable which is decremented when finish
    ///                  the function. This variable is used for to know
    ///                  when are finished all the function_t created
    ///                  inside an object
    /// @param error : global indicator of error.
    //------------------------------------------------------------------------
    void function_move_long_sequence(std::vector<size_t> &sequence,
                                     atomic_t &counter, bool &error)
    {
        bscu::atomic_add(counter, 1);
        function_t f1 = [this, sequence, &counter, &error]( ) -> void
        {
            if (not error)
            {
                try
                {
                    this->move_long_sequence (sequence);
                }
                catch (std::bad_alloc &)
                {
                    error = true;
                };
            }
            bscu::atomic_sub (counter, 1);
        };
        bk.works.emplace_back(f1);
    }
    ;
//---------------------------------------------------------------------------
}; // end of struct move_blocks
//---------------------------------------------------------------------------
//
//############################################################################
//                                                                          ##
//                                                                          ##
//            N O N     I N L I N E      F U N C T I O N S                  ##
//                                                                          ##
//                                                                          ##
//############################################################################
//
//-------------------------------------------------------------------------
//  function : move_blocks
/// @brief constructor of the class for to move the blocks to their true
///        position obtained from the index
//
/// @param bkb : backbone with the index and the blocks
//-------------------------------------------------------------------------
template<uint32_t Block_size, uint32_t Group_size, class Iter_t, class Compare>
move_blocks<Block_size, Group_size, Iter_t, Compare>
::move_blocks(backbone_t &bkb) : bk(bkb)
{
    std::vector<std::vector<size_t> > vsequence;
    vsequence.reserve(bk.index.size() >> 1);
    std::vector<size_t> sequence;
    atomic_t counter(0);

    size_t pos_index_ini = 0, pos_index_src = 0, pos_index_dest = 0;
    while (pos_index_ini < bk.index.size())
    {
        while (pos_index_ini < bk.index.size()
                        and bk.index[pos_index_ini].pos() == pos_index_ini)
        {
            ++pos_index_ini;
        };

        if (pos_index_ini == bk.index.size()) break;

        sequence.clear();
        pos_index_src = pos_index_dest = pos_index_ini;
        sequence.push_back(pos_index_ini);

        while (bk.index[pos_index_dest].pos() != pos_index_ini)
        {
            pos_index_src = bk.index[pos_index_dest].pos();
            sequence.push_back(pos_index_src);

            bk.index[pos_index_dest].set_pos(pos_index_dest);
            pos_index_dest = pos_index_src;
        };

        bk.index[pos_index_dest].set_pos(pos_index_dest);
        vsequence.push_back(sequence);

        if (sequence.size() < Group_size)
        {
            function_move_sequence(vsequence.back(), counter, bk.error);
        }
        else
        {
            function_move_long_sequence(vsequence.back(), counter, bk.error);
        };
    };
    bk.exec(counter);
}
;
//
//-------------------------------------------------------------------------
//  function : move_sequence
/// @brief move the blocks, following the positions of the init_sequence
//
/// @param init_sequence : vector with the positions from and where move the
///                        blocks
//-------------------------------------------------------------------------
template<uint32_t Block_size, uint32_t Group_size, class Iter_t, class Compare>
void move_blocks<Block_size, Group_size, Iter_t, Compare>
::move_sequence(const std::vector<size_t> &init_sequence)
{
    range_buf rbuf = bk.get_range_buf();
    size_t pos_range2 = init_sequence[0];

    range_it range2 = bk.get_range(pos_range2);
    move_forward(rbuf, range2);

    for (size_t i = 1; i < init_sequence.size(); ++i)
    {
        pos_range2 = init_sequence[i];
        range_it range1(range2);
        range2 = bk.get_range(pos_range2);
        move_forward(range1, range2);
    };
    move_forward(range2, rbuf);
};
//
//-------------------------------------------------------------------------
//  function : move_long_sequence
/// @brief move the blocks, following the positions of the init_sequence.
///        if the sequence is greater than Group_size, it is divided in small
///        sequences, creating function_t elements, for to be inserted in the
///        concurrent stack
//
/// @param init_sequence : vector with the positions from and where move the
///                        blocks
//-------------------------------------------------------------------------
template<uint32_t Block_size, uint32_t Group_size, class Iter_t, class Compare>
void move_blocks<Block_size, Group_size, Iter_t, Compare>
::move_long_sequence(const std::vector<size_t> &init_sequence)
{
    if (init_sequence.size() < Group_size) return move_sequence(init_sequence);

    size_t npart = (init_sequence.size() + Group_size - 1) / Group_size;
    size_t size_part = init_sequence.size() / npart;
    atomic_t son_counter(0);

    std::vector<size_t> sequence;
    sequence.reserve(size_part);

    std::vector<size_t> index_seq;
    index_seq.reserve(npart);

    auto it_pos = init_sequence.begin();
    for (size_t i = 0; i < (npart - 1); ++i, it_pos += size_part)
    {
        sequence.assign(it_pos, it_pos + size_part);
        index_seq.emplace_back(*(it_pos + size_part - 1));
        function_move_sequence(sequence, son_counter, bk.error);
    };

    sequence.assign(it_pos, init_sequence.end());
    index_seq.emplace_back(init_sequence.back());
    function_move_sequence(sequence, son_counter, bk.error);

    bk.exec(son_counter);
    if (bk.error) return;
    move_long_sequence(index_seq);
}

//
//****************************************************************************
}; //    End namespace blk_detail
}; //    End namespace sort
}; //    End namespace boost
//****************************************************************************
//
#endif

/* move_blocks.hpp
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
*/