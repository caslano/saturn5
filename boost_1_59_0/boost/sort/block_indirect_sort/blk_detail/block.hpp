//----------------------------------------------------------------------------
/// @file block.hpp
/// @brief This file contains the internal data structures used in the
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
#ifndef __BOOST_SORT_PARALLEL_DETAIL_BLOCK_HPP
#define __BOOST_SORT_PARALLEL_DETAIL_BLOCK_HPP

#include <boost/sort/common/range.hpp>

namespace boost
{
namespace sort
{
namespace blk_detail
{
//---------------------------------------------------------------------------
//                 USING SENTENCES
//---------------------------------------------------------------------------
using namespace boost::sort::common;
//
//---------------------------------------------------------------------------
/// @struct block_pos
/// @brief represent a pair of values, a position represented as an unsigned
///        variable ( position ), and a bool variable ( side ). They are packed
///        in a size_t variable. The Least Significant Bit is the bool variable,
///        and the others bits are the position
//----------------------------------------------------------------------------
class block_pos
{
    //------------------------------------------------------------------------
    //                   VARIABLES
    //-----------------------------------------------------------------------
    size_t num; // number which store a position and a bool side

  public:
    //----------------------------- FUNCTIONS ------------------------------
    block_pos (void) : num (0){};
    //
    //-------------------------------------------------------------------------
    //  function : block_pos
    /// @brief constructor from a position and a side
    /// @param position : position to sotre
    /// @param side : side to store
    //-------------------------------------------------------------------------
    block_pos (size_t position, bool side = false)
    {
        num = (position << 1) + ((side) ? 1 : 0);
    };
    //
    //-------------------------------------------------------------------------
    //  function : pos
    /// @brief obtain the position stored inside the block_pos
    /// @return position
    //-------------------------------------------------------------------------
    size_t pos (void) const { return (num >> 1); };
    //
    //-------------------------------------------------------------------------
    //  function : pos
    /// @brief store a position inside the block_pos
    /// @param position : value to store
    //-------------------------------------------------------------------------
    void set_pos (size_t position) { num = (position << 1) + (num & 1); };
    //
    //-------------------------------------------------------------------------
    //  function : side
    /// @brief obtain the side stored inside the block_pos
    /// @return bool value
    //-------------------------------------------------------------------------
    bool side (void) const { return ((num & 1) != 0); };
    //
    //-------------------------------------------------------------------------
    //  function : side
    /// @brief store a bool value the block_pos
    /// @param sd : bool value to store
    //-------------------------------------------------------------------------
    void set_side (bool sd) { num = (num & ~1) + ((sd) ? 1 : 0); };
}; // end struct block_pos

//
//---------------------------------------------------------------------------
/// @struct block
/// @brief represent a group of Block_size contiguous elements, beginning
///        with the pointed by first
//----------------------------------------------------------------------------
template < uint32_t Block_size, class Iter_t >
struct block
{
    //----------------------------------------------------------------------
    //                     VARIABLES
    //----------------------------------------------------------------------
    Iter_t first; // iterator to the first element of the block

    //-------------------------------------------------------------------------
    //  function : block
    /// @brief constructor from an iterator to the first element of the block
    /// @param it : iterator to the first element of the block
    //-------------------------------------------------------------------------
    block (Iter_t it) : first (it){};

    //-------------------------------------------------------------------------
    //  function : get_range
    /// @brief convert a block in a range
    /// @return range
    //-------------------------------------------------------------------------
    range< Iter_t > get_range (void)
    {
        return range_it (first, first + Block_size);
    };

}; // end struct block

//
//-------------------------------------------------------------------------
//  function : compare_block
/// @brief compare two blocks using the content of the pointed by first
/// @param block1 : first block to compare
/// @param block2 : second block to compare
/// @param cmp : comparison operator
//-------------------------------------------------------------------------
template < uint32_t Block_size, class Iter_t, class Compare >
bool compare_block (block< Block_size, Iter_t > block1,
                    block< Block_size, Iter_t > block2,
                    Compare cmp = Compare ( ))
{
    return cmp (*block1.first, *block2.first);
};
//
///---------------------------------------------------------------------------
/// @struct compare_block_pos
/// @brief This is a object for to compare two block_pos objects
//----------------------------------------------------------------------------
template < uint32_t Block_size, class Iter_t, class Compare >
struct compare_block_pos
{
    //-----------------------------------------------------------------------
    //                        VARIABLES
    //-----------------------------------------------------------------------
    Iter_t global_first; // iterator to the first element to sort
    Compare comp;        // comparison object for to compare two elements

    //-------------------------------------------------------------------------
    //  function : compare_block_pos
    /// @brief constructor
    /// @param g_first : itertor to the first element to sort
    /// @param cmp : comparison operator
    //-------------------------------------------------------------------------
    compare_block_pos (Iter_t g_first, Compare cmp)
        : global_first (g_first), comp (cmp){};
    //
    //-------------------------------------------------------------------------
    //  function : operator ()
    /// @brief compare two blocks using the content of the pointed by
    ///        global_first
    /// @param block_pos1 : first block to compare
    /// @param block_pos2 : second block to compare
    //-------------------------------------------------------------------------
    bool operator( ) (block_pos block_pos1, block_pos block_pos2) const
    {
        return comp (*(global_first + (block_pos1.pos ( ) * Block_size)),
                     *(global_first + (block_pos2.pos ( ) * Block_size)));
    };

}; // end struct compare_block_pos

//****************************************************************************
}; //    End namespace blk_detail
}; //    End namespace sort
}; //    End namespace boost
//****************************************************************************
//
#endif

/* block.hpp
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
*/