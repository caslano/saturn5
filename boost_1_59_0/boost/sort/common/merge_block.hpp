//----------------------------------------------------------------------------
/// @file merge_block.hpp
/// @brief This file constains the class merge_block, which is part of the
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
#ifndef __BOOST_SORT_COMMON_MERGE_BLOCK_HPP
#define __BOOST_SORT_COMMON_MERGE_BLOCK_HPP

#include <boost/sort/common/range.hpp>
#include <boost/sort/common/rearrange.hpp>
#include <boost/sort/common/util/merge.hpp>
#include <boost/sort/common/util/traits.hpp>

namespace boost
{
namespace sort
{
namespace common
{
///---------------------------------------------------------------------------
/// @struct merge_block
/// @brief This contains all the information shared betwen the classes of the
///        block indirect sort algorithm

//----------------------------------------------------------------------------
template<class Iter_t, class Compare, uint32_t Power2 = 10>
struct merge_block
{
    //-------------------------------------------------------------------------
    //                  D E F I N I T I O N S
    //-------------------------------------------------------------------------
    typedef util::value_iter<Iter_t>                    value_t;
    typedef range<size_t>                               range_pos;
    typedef range<Iter_t>                               range_it;
    typedef range<value_t *>                            range_buf;
    typedef typename std::vector<size_t>::iterator      it_index;
    typedef util::circular_buffer<value_t, Power2 + 1>  circular_t;

    //------------------------------------------------------------------------
    //                          CONSTANTS
    //------------------------------------------------------------------------
    const size_t BLOCK_SIZE = (size_t) 1 << Power2;
    const size_t LOG_BLOCK = Power2;

    //------------------------------------------------------------------------
    //                V A R I A B L E S
    //------------------------------------------------------------------------
    // range with all the element to sort
    range<Iter_t> global_range;

    // index vector of block_pos elements
    std::vector<size_t> index;

    // Number of elements to sort
    size_t nelem;

    // Number of blocks to sort
    size_t nblock;

    // Number of elements in the last block (tail)
    size_t ntail;

    // object for to compare two elements
    Compare cmp;

    // range  of elements of the last block (tail)
    range_it range_tail;

    // circular buffer
    circular_t * ptr_circ;

    // indicate  if the circulr buffer is owned  by the data structure
    // or is received as parameter
    bool owned;

    //
    //------------------------------------------------------------------------
    //                F U N C T I O N S
    //------------------------------------------------------------------------
    //
    //------------------------------------------------------------------------
    //  function : merge_block
    /// @brief constructor of the class
    //
    /// @param first : iterator to the first element of the range to sort
    /// @param last : iterator after the last element to the range to sort
    /// @param comp : object for to compare two elements pointed by Iter_t
    ///               iterators
    //------------------------------------------------------------------------
    merge_block (Iter_t first, Iter_t last, Compare comp,
                 circular_t *pcirc_buffer)
    : global_range(first, last), cmp(comp), ptr_circ(pcirc_buffer),
      owned(pcirc_buffer == nullptr)
    {
        assert((last - first) >= 0);
        if (first == last) return; // nothing to do

        nelem = size_t(last - first);
        nblock = (nelem + BLOCK_SIZE - 1) / BLOCK_SIZE;
        ntail = (nelem % BLOCK_SIZE);
        index.reserve(nblock + 1);

        for (size_t i = 0; i < nblock; ++i)
            index.emplace_back(i);

        range_tail.first = first + ((nblock - 1) << LOG_BLOCK);
        range_tail.last = last;
        if (owned)
        {
            ptr_circ = new circular_t;
            ptr_circ->initialize(*first);
        };
    }

    merge_block(Iter_t first, Iter_t last, Compare comp)
                    : merge_block(first, last, comp, nullptr) { };

    ~ merge_block()
    {
        if (ptr_circ != nullptr and owned)
        {
            delete ptr_circ;
            ptr_circ = nullptr;
        };
    };
    //-------------------------------------------------------------------------
    //  function : get_range
    /// @brief obtain the range in the position pos
    /// @param pos : position of the range
    /// @return range required
    //-------------------------------------------------------------------------
    range_it get_range(size_t pos) const
    {
        Iter_t it1 = global_range.first + (pos << LOG_BLOCK);
        Iter_t it2 = (pos == (nblock - 1)) ?
                        global_range.last : it1 + BLOCK_SIZE;
        return range_it(it1, it2);
    };
    //-------------------------------------------------------------------------
    //  function : get_group_range
    /// @brief obtain the range of the contiguous blocks beginning in the
    //         position pos
    /// @param pos : position of the first range
    /// @param nrange : number of ranges of the group
    /// @return range required
    //-------------------------------------------------------------------------
    range_it get_group_range(size_t pos, size_t nrange) const
    {
        Iter_t it1 = global_range.first + (pos << LOG_BLOCK);

        Iter_t it2 = ((pos + nrange) == nblock)?global_range.last: global_range.first + ((pos + nrange) << LOG_BLOCK);
        //Iter_t it2 = global_range.first + ((pos + nrange) << LOG_BLOCK);
        //if ((pos + nrange) == nblock) it2 = global_range.last;

        return range_it(it1, it2);
    };
    //-------------------------------------------------------------------------
    //  function : is_tail
    /// @brief indicate if a block is the tail
    /// @param pos : position of the block
    /// @return true : taiol  false : not tail
    //-------------------------------------------------------------------------
    bool is_tail(size_t pos) const
    {
        return (pos == (nblock - 1) and ntail != 0);
    };
    //-------------------------------------------------------------------------
    //  function :
    /// @brief
    /// @param
    /// @return
    //-------------------------------------------------------------------------
    void merge_range_pos(it_index itx_first, it_index itx_mid,
                         it_index itx_last);

    //-------------------------------------------------------------------------
    //  function : move_range_pos_backward
    /// @brief Move backward the elements of a range of blocks in a index
    /// @param itx_first : iterator to the position of the first block
    /// @param  itx_last : itertor to the position of the last block
    /// @param  npos : number of positions to move. Must be less than BLOCK_SIZE
    /// @return
    //-------------------------------------------------------------------------
    void move_range_pos_backward(it_index itx_first, it_index itx_last,
                                 size_t npos);

    //-------------------------------------------------------------------------
    //  function : rearrange_with_index
    /// @brief rearrange the blocks with the relative positions of the index
    /// @param
    /// @param
    /// @param
    /// @return
    //-------------------------------------------------------------------------
    void rearrange_with_index(void);

//---------------------------------------------------------------------------
};// end struct merge_block
//---------------------------------------------------------------------------
//
//############################################################################
//                                                                          ##
//           N O N     I N L I N E     F U N C T IO N S                     ##
//                                                                          ##
//############################################################################
//
//-------------------------------------------------------------------------
//  function :
/// @brief
/// @param
/// @return
//-------------------------------------------------------------------------
template<class Iter_t, class Compare, uint32_t Power2>
void merge_block<Iter_t, Compare, Power2>
::merge_range_pos(it_index itx_first, it_index itx_mid,it_index itx_last)
{
    assert((itx_last - itx_mid) >= 0 and (itx_mid - itx_first) >= 0);

    size_t nelemA = (itx_mid - itx_first), nelemB = (itx_last - itx_mid);
    if (nelemA == 0 or nelemB == 0) return;

    //-------------------------------------------------------------------
    // Create two index with the position of the blocks to merge
    //-------------------------------------------------------------------
    std::vector<size_t> indexA, indexB;
    indexA.reserve(nelemA + 1);
    indexB.reserve(nelemB);

    indexA.insert(indexA.begin(), itx_first, itx_mid);
    indexB.insert(indexB.begin(), itx_mid, itx_last);

    it_index itx_out = itx_first;
    it_index itxA = indexA.begin(), itxB = indexB.begin();
    range_it rngA, rngB;
    Iter_t itA = global_range.first, itB = global_range.first;
    bool validA = false, validB = false;

    while (itxA != indexA.end() and itxB != indexB.end())
    {   //----------------------------------------------------------------
        // Load valid ranges from the itxA and ItxB positions
        //----------------------------------------------------------------
        if (not validA)
        {
            rngA = get_range(*itxA);
            itA = rngA.first;
            validA = true;
        };
        if (not validB)
        {
            rngB = get_range(*itxB);
            itB = rngB.first;
            validB = true;
        };
        //----------------------------------------------------------------
        // If don't have merge betweeen the  blocks, pass directly the
        // position of the block to itx_out
        //----------------------------------------------------------------
        if (ptr_circ->size() == 0)
        {
            if (not cmp(*rngB.front(), *rngA.back()))
            {
                *(itx_out++) = *(itxA++);
                validA = false;
                continue;
            };
            if (cmp(*rngB.back(), *rngA.front()))
            {
                if (not is_tail(*itxB))
                    *(itx_out++) = *itxB;
                else ptr_circ->push_move_back(rngB.first, rngB.size());
                ++itxB;
                validB = false;
                continue;
            };
        };
        //----------------------------------------------------------------
        // Normal merge
        //----------------------------------------------------------------
        bool side = util::merge_circular(itA, rngA.last, itB, rngB.last,
                        *ptr_circ, cmp, itA, itB);
        if (side)
        {   // rngA is finished
            ptr_circ->pop_move_front(rngA.first, rngA.size());
            *(itx_out++) = *(itxA++);
            validA = false;
        }
        else
        {   // rngB is finished
            if (not is_tail(*itxB))
            {
                ptr_circ->pop_move_front(rngB.first, rngB.size());
                *(itx_out++) = *itxB;
            };
            ++itxB;
            validB = false;
        };
    }; // end while

    if (itxA == indexA.end())
    {   // the index A is finished
        rngB = get_range(*itxB);
        ptr_circ->pop_move_front(rngB.first, ptr_circ->size());
        while (itxB != indexB.end())
            *(itx_out++) = *(itxB++);
    }
    else
    {   // The list B is finished
        rngA = get_range(*itxA);
        if (ntail != 0 and indexB.back() == (nblock - 1)) // exist tail
        {   // add the tail block to indexA, and shift the element
            indexA.push_back(indexB.back());
            size_t numA = size_t(itA - rngA.first);
            ptr_circ->pop_move_back(rngA.first, numA);
            move_range_pos_backward(itxA, indexA.end(), ntail);
        };

        ptr_circ->pop_move_front(rngA.first, ptr_circ->size());
        while (itxA != indexA.end())
            *(itx_out++) = *(itxA++);
    };
};

//-------------------------------------------------------------------------
//  function : move_range_pos_backward
/// @brief Move backward the elements of a range of blocks in a index
/// @param itx_first : iterator to the position of the first block
/// @param  itx_last : itertor to the position of the last block
/// @param  npos : number of positions to move. Must be less than BLOCK_SIZE
/// @return
//-------------------------------------------------------------------------
template<class Iter_t, class Compare, uint32_t Power2>
void merge_block<Iter_t, Compare, Power2>
::move_range_pos_backward(it_index itx_first, it_index itx_last, size_t npos)
{
    assert((itx_last - itx_first) >= 0 and npos <= BLOCK_SIZE);

    //--------------------------------------------------------------------
    // Processing the last block. Must be ready fore to accept npos
    // elements from the upper block
    //--------------------------------------------------------------------
    range_it rng1 = get_range(*(itx_last - 1));
    assert(rng1.size() >= npos);
    if (rng1.size() > npos)
    {
        size_t nmove = rng1.size() - npos;
        util::move_backward(rng1.last, rng1.first, rng1.first + nmove);
    };
    //--------------------------------------------------------------------
    // Movement of elements between blocks
    //--------------------------------------------------------------------
    for (it_index itx = itx_last - 1; itx != itx_first;)
    {
        --itx;
        range_it rng2 = rng1;
        rng1 = get_range(*itx);
        Iter_t it_mid1 = rng1.last - npos, it_mid2 = rng2.first + npos;
        util::move_backward(it_mid2, it_mid1, rng1.last);
        util::move_backward(rng1.last, rng1.first, it_mid1);
    };
};
//-------------------------------------------------------------------------
//  function : rearrange_with_index
/// @brief rearrange the blocks with the relative positions of the index
/// @param
/// @param
/// @param
/// @return
//-------------------------------------------------------------------------
template<class Iter_t, class Compare, uint32_t Power2>
void merge_block<Iter_t, Compare, Power2>
::rearrange_with_index(void)
{   //--------------------------------------------------------------------
    //                     Code
    //--------------------------------------------------------------------
    size_t pos_dest, pos_src, pos_ini;
    size_t nelem = index.size();

    ptr_circ->clear();
    value_t * aux = ptr_circ->get_buffer();
    range_buf rng_buf(aux, aux + ptr_circ->NMAX);

    pos_ini = 0;
    while (pos_ini < nelem)
    {
        while (pos_ini < nelem and index[pos_ini] == pos_ini)
            ++pos_ini;
        if (pos_ini == nelem) return;
        pos_dest = pos_src = pos_ini;
        rng_buf = move_forward(rng_buf, get_range(pos_ini));
        pos_src = index[pos_ini];

        while (pos_src != pos_ini)
        {
            move_forward(get_range(pos_dest), get_range(pos_src));
            index[pos_dest] = pos_dest;
            pos_dest = pos_src;
            pos_src = index[pos_src];
        };
        move_forward(get_range(pos_dest), rng_buf);
        index[pos_dest] = pos_dest;
        ++pos_ini;
    };
};

//****************************************************************************
};//    End namespace common
};//    End namespace sort
};//    End namespace boost
//****************************************************************************
#endif

/* merge_block.hpp
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
*/