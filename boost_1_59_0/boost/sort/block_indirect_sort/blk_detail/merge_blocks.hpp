//----------------------------------------------------------------------------
/// @file merge_blocks.hpp
/// @brief contains the class merge_blocks, which is part of the
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
#ifndef __BOOST_SORT_PARALLEL_DETAIL_MERGE_BLOCKS_HPP
#define __BOOST_SORT_PARALLEL_DETAIL_MERGE_BLOCKS_HPP

#include <atomic>
#include <boost/sort/block_indirect_sort/blk_detail/backbone.hpp>
#include <boost/sort/common/range.hpp>
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
namespace bscu = bsc::util;
using bsc::range;
using bsc::is_mergeable;
using bsc::merge_uncontiguous;
//
///---------------------------------------------------------------------------
/// @struct merge_blocks
/// @brief This class merge the blocks. The blocks to merge are defined by two
///        ranges of positions in the index of the backbone
//----------------------------------------------------------------------------
template<uint32_t Block_size, uint32_t Group_size, class Iter_t, class Compare>
struct merge_blocks
{
    //-----------------------------------------------------------------------
    //                  D E F I N I T I O N S
    //-----------------------------------------------------------------------
    typedef typename std::iterator_traits<Iter_t>::value_type value_t;
    typedef std::atomic<uint32_t> atomic_t;
    typedef range<size_t> range_pos;
    typedef range<Iter_t> range_it;
    typedef range<value_t *> range_buf;
    typedef std::function<void(void)> function_t;
    typedef backbone<Block_size, Iter_t, Compare> backbone_t;
    typedef compare_block_pos<Block_size, Iter_t, Compare> compare_block_pos_t;

    //------------------------------------------------------------------------
    //                V A R I A B L E S
    //------------------------------------------------------------------------
    // Object with the elements to sort and all internal data structures of the
    // algorithm
    backbone_t &bk;
    //
    //------------------------------------------------------------------------
    //                F U N C T I O N S
    //------------------------------------------------------------------------
    merge_blocks(backbone_t &bkb, size_t pos_index1, size_t pos_index2,
                    size_t pos_index3);

    void tail_process(std::vector<block_pos> &vblkpos1,
                    std::vector<block_pos> &vblkpos2);

    void cut_range(range_pos rng);

    void merge_range_pos(range_pos rng);

    void extract_ranges(range_pos range_input);
    //
    //------------------------------------------------------------------------
    //  function : function_merge_range_pos
    /// @brief create a function_t with a call to merge_range_pos, and insert
    ///        in the stack of the backbone
    //
    /// @param rng_input : range of positions of blocks in the index to merge
    /// @param son_counter : atomic variable which is decremented when finish
    ///                      the function. This variable is used for to know
    ///                      when are finished all the function_t created
    ///                      inside an object
    /// @param error : global indicator of error.
    ///
    //------------------------------------------------------------------------
    void function_merge_range_pos(const range_pos &rng_input, atomic_t &counter,
                    bool &error)
    {
        bscu::atomic_add(counter, 1);
        function_t f1 = [this, rng_input, &counter, &error]( ) -> void
        {
            if (not error)
            {
                try
                {
                    this->merge_range_pos (rng_input);
                }
                catch (std::bad_alloc &ba)
                {
                    error = true;
                };
            }
            bscu::atomic_sub (counter, 1);
        };
        bk.works.emplace_back(f1);
    }
    ;
    //
    //------------------------------------------------------------------------
    //  function : function_cut_range
    /// @brief create a function_t with a call to cut_range, and inser in
    ///        the stack of the backbone
    //
    /// @param rng_input : range of positions in the index to cut
    /// @param counter : atomic variable which is decremented when finish
    ///                  the function. This variable is used for to know
    ///                  when are finished all the function_t created
    ///                  inside an object
    /// @param error : global indicator of error.
    //------------------------------------------------------------------------
    void function_cut_range(const range_pos &rng_input, atomic_t &counter,
                    bool &error)
    {
        bscu::atomic_add(counter, 1);
        function_t f1 = [this, rng_input, &counter, &error]( ) -> void
        {
            if (not error)
            {
                try
                {
                    this->cut_range (rng_input);
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


//----------------------------------------------------------------------------
};
// end struct merge_blocks
//----------------------------------------------------------------------------
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
//  function : merge_blocks
/// @brief make the indirect merge of the two range_pos defined by their index
///        position [pos_index1, pos_index2 ) and [ pos_index2, pos_index3 )
//
/// @param bkb : backbone with all the data to sort , and the internal data
///              structures of the algorithm
/// @param pos_index1 : first position of the first range in the index
/// @param pos_index2 : last position of the first range and first position
///                     of the second range in the index
/// @param pos_index3 : last position of the second range in the index
//-------------------------------------------------------------------------
template<uint32_t Block_size, uint32_t Group_size, class Iter_t, class Compare>
merge_blocks<Block_size, Group_size, Iter_t, Compare>
::merge_blocks( backbone_t &bkb, size_t pos_index1, size_t pos_index2,
                size_t pos_index3) : bk(bkb)
{
    size_t nblock1 = pos_index2 - pos_index1;
    size_t nblock2 = pos_index3 - pos_index2;
    if (nblock1 == 0 or nblock2 == 0) return;

    //-----------------------------------------------------------------------
    // Merging of the two intervals
    //-----------------------------------------------------------------------
    std::vector<block_pos> vpos1, vpos2;
    vpos1.reserve(nblock1 + 1);
    vpos2.reserve(nblock2 + 1);

    for (size_t i = pos_index1; i < pos_index2; ++i)
    {
        vpos1.emplace_back(bk.index[i].pos(), true);
    };

    for (size_t i = pos_index2; i < pos_index3; ++i)
    {
        vpos2.emplace_back(bk.index[i].pos(), false);
    };
    //-------------------------------------------------------------------
    //  tail process
    //-------------------------------------------------------------------
    if (vpos2.back().pos() == (bk.nblock - 1)
                    and bk.range_tail.first != bk.range_tail.last)
    {
        tail_process(vpos1, vpos2);
        nblock1 = vpos1.size();
        nblock2 = vpos2.size();
    };

    compare_block_pos_t cmp_blk(bk.global_range.first, bk.cmp);
    if (bk.error) return;
    bscu::merge(vpos1.begin(), vpos1.end(), vpos2.begin(), vpos2.end(),
                    bk.index.begin() + pos_index1, cmp_blk);
    if (bk.error) return;
    // Extracting the ranges for to merge the elements
    extract_ranges(range_pos(pos_index1, pos_index1 + nblock1 + nblock2));
}


//
//-------------------------------------------------------------------------
//  function : tail_process
/// @brief make the process when the second vector of block_pos to merge is
///        the last, and have an incomplete block ( tail)
//
/// @param vblkpos1 : first vector of block_pos elements to merge
/// @param vblkpos2 : second vector of block_pos elements to merge
//-------------------------------------------------------------------------
template<uint32_t Block_size, uint32_t Group_size, class Iter_t, class Compare>
void merge_blocks<Block_size, Group_size, Iter_t, Compare>
::tail_process( std::vector<block_pos> &vblkpos1,
                std::vector<block_pos> &vblkpos2 )
{
    if (vblkpos1.size() == 0 or vblkpos2.size() == 0) return;

    vblkpos2.pop_back();

    size_t posback1 = vblkpos1.back().pos();
    range_it range_back1 = bk.get_range(posback1);

    if (bsc::is_mergeable(range_back1, bk.range_tail, bk.cmp))
    {
        bsc::merge_uncontiguous(range_back1, bk.range_tail, bk.get_range_buf(),
                        bk.cmp);
        if (vblkpos1.size() > 1)
        {
            size_t pos_aux = vblkpos1[vblkpos1.size() - 2].pos();
            range_it range_aux = bk.get_range(pos_aux);

            if (bsc::is_mergeable(range_aux, range_back1, bk.cmp))
            {
                vblkpos2.emplace_back(posback1, false);
                vblkpos1.pop_back();
            };
        };
    };
}

//
//-------------------------------------------------------------------------
//  function : cut_range
/// @brief when the rng_input is greather than Group_size, this function divide
///        it in several parts creating function_t elements, which are inserted
///        in the concurrent stack of the backbone
//
/// @param rng_input : range to divide
//-------------------------------------------------------------------------
template<uint32_t Block_size, uint32_t Group_size, class Iter_t, class Compare>
void merge_blocks<Block_size, Group_size, Iter_t, Compare>
::cut_range(range_pos rng_input)
{
    if (rng_input.size() < Group_size)
    {
        merge_range_pos(rng_input);
        return;
    };

    atomic_t counter(0);
    size_t npart = (rng_input.size() + Group_size - 1) / Group_size;
    size_t size_part = rng_input.size() / npart;

    size_t pos_ini = rng_input.first;
    size_t pos_last = rng_input.last;

    while (pos_ini < pos_last)
    {
        size_t pos = pos_ini + size_part;
        while (pos < pos_last
                        and bk.index[pos - 1].side() == bk.index[pos].side())
        {
            ++pos;
        };
        if (pos < pos_last)
        {
            merge_uncontiguous(bk.get_range(bk.index[pos - 1].pos()),
                            bk.get_range(bk.index[pos].pos()),
                            bk.get_range_buf(), bk.cmp);
        }
        else pos = pos_last;
        if ((pos - pos_ini) > 1)
        {
            range_pos rng_aux(pos_ini, pos);
            function_merge_range_pos(rng_aux, counter, bk.error);
        };
        pos_ini = pos;
    };
    bk.exec(counter); // wait until finish all the ranges
}


//
//-------------------------------------------------------------------------
//  function : merge_range_pos
/// @brief make the indirect merge of the blocks inside the rng_input
//
/// @param rng_input : range of positions of the blocks to merge
//-------------------------------------------------------------------------
template<uint32_t Block_size, uint32_t Group_size, class Iter_t, class Compare>
void merge_blocks<Block_size, Group_size, Iter_t, Compare>
::merge_range_pos(range_pos rng_input)
{
    if (rng_input.size() < 2) return;
    range_buf rbuf = bk.get_range_buf();

    range_it rng_prev = bk.get_range(bk.index[rng_input.first].pos());
    move_forward(rbuf, rng_prev);
    range_it rng_posx(rng_prev);

    for (size_t posx = rng_input.first + 1; posx != rng_input.last; ++posx)
    {
        rng_posx = bk.get_range(bk.index[posx].pos());
        bsc::merge_flow(rng_prev, rbuf, rng_posx, bk.cmp);
        rng_prev = rng_posx;

    };
    move_forward(rng_posx, rbuf);
}
//
//-------------------------------------------------------------------------
//  function : extract_ranges
/// @brief from a big range of positions of blocks in the index. Examine which
///        are mergeable, and generate a couple of ranges for to be merged.
///        With the ranges obtained generate function_t elements and are
///        inserted in the concurrent stack.
///        When the range obtained is smaller than Group_size, generate a
///        function_t calling to merge_range_pos, when is greater, generate a
///        function_t calling to cut_range
//
/// @param rpos range_input : range of the position in the index, where must
///                           extract the ranges to merge
//-------------------------------------------------------------------------
template<uint32_t Block_size, uint32_t Group_size, class Iter_t, class Compare>
void merge_blocks<Block_size, Group_size, Iter_t, Compare>
::extract_ranges(range_pos range_input)
{
    if (range_input.size() < 2) return;
    atomic_t counter(0);

    // The names with x are positions of the index
    size_t posx_ini = range_input.first;
    block_pos bp_posx_ini = bk.index[posx_ini];

    range_it rng_max = bk.get_range(bp_posx_ini.pos());
    bool side_max = bp_posx_ini.side();

    block_pos bp_posx;
    range_it rng_posx = rng_max;
    bool side_posx = side_max;

    for (size_t posx = posx_ini + 1; posx <= range_input.last; ++posx)
    {
        bool final = (posx == range_input.last);
        bool mergeable = false;

        if (not final)
        {
            bp_posx = bk.index[posx];
            rng_posx = bk.get_range(bp_posx.pos());
            side_posx = bp_posx.side();
            mergeable = (side_max != side_posx
                            and is_mergeable(rng_max, rng_posx, bk.cmp));
        };
        if (bk.error) return;
        if (final or not mergeable)
        {
            range_pos rp_final(posx_ini, posx);
            if (rp_final.size() > 1)
            {
                if (rp_final.size() > Group_size)
                {
                    function_cut_range(rp_final, counter, bk.error);
                }
                else
                {
                    function_merge_range_pos(rp_final, counter, bk.error);
                };
            };
            posx_ini = posx;
            if (not final)
            {
                rng_max = rng_posx;
                side_max = side_posx;
            };
        }
        else
        {
            if (bk.cmp(*(rng_max.back()), *(rng_posx.back())))
            {
                rng_max = rng_posx;
                side_max = side_posx;
            };
        };
    };
    bk.exec(counter);
}
//
//****************************************************************************
}; //    End namespace blk_detail
}; //    End namespace sort
}; //    End namespace boost
//****************************************************************************
//
#endif

/* merge_blocks.hpp
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
*/