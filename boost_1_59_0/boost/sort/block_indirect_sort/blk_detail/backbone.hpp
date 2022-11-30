//----------------------------------------------------------------------------
/// @file backbone.hpp
/// @brief This file constains the class backbone, which is part of the
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
#ifndef __BOOST_SORT_PARALLEL_DETAIL_BACKBONE_HPP
#define __BOOST_SORT_PARALLEL_DETAIL_BACKBONE_HPP

#include <atomic>
#include <boost/sort/pdqsort/pdqsort.hpp>
#include <boost/sort/common/util/atomic.hpp>
#include <boost/sort/common/util/algorithm.hpp>
#include <boost/sort/common/stack_cnc.hpp>
#include <future>
#include <iostream>
#include <iterator>

#include <boost/sort/block_indirect_sort/blk_detail/block.hpp>

namespace boost
{
namespace sort
{
namespace blk_detail
{

//---------------------------------------------------------------------------
//                 USING SENTENCES
//---------------------------------------------------------------------------
namespace bsc = boost::sort::common;
namespace bscu = bsc::util;
using bsc::stack_cnc;
using bsc::range;

///---------------------------------------------------------------------------
/// @struct backbone
/// @brief This contains all the information shared betwen the classes of the
///        block indirect sort algorithm

//----------------------------------------------------------------------------
template < uint32_t Block_size, class Iter_t, class Compare >
struct backbone
{
    //-------------------------------------------------------------------------
    //                  D E F I N I T I O N S
    //-------------------------------------------------------------------------
    typedef typename std::iterator_traits< Iter_t >::value_type value_t;
    typedef std::atomic< uint32_t >                             atomic_t;
    typedef range< size_t >                                     range_pos;
    typedef range< Iter_t >                                     range_it;
    typedef range< value_t * >                                  range_buf;
    typedef std::function< void(void) >                         function_t;
    typedef block< Block_size, Iter_t >                         block_t;

    //------------------------------------------------------------------------
    //                V A R I A B L E S
    //------------------------------------------------------------------------
    // range with all the element to sort
    range< Iter_t > global_range;

    // index vector of block_pos elements
    std::vector< block_pos > index;

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

    // thread local varible. It is a pointer to the buffer
    static thread_local value_t *buf;

    // concurrent stack where store the function_t elements
    stack_cnc< function_t > works;

    // global indicator of error
    bool error;
    //
    //------------------------------------------------------------------------
    //                F U N C T I O N S
    //------------------------------------------------------------------------
    backbone (Iter_t first, Iter_t last, Compare comp);

    //------------------------------------------------------------------------
    //  function : get_block
    /// @brief obtain the block in the position pos
    /// @param pos : position of the range
    /// @return block required
    //------------------------------------------------------------------------
    block_t get_block (size_t pos) const
    {
        return block_t (global_range.first + (pos * Block_size));
    };
    //-------------------------------------------------------------------------
    //  function : get_range
    /// @brief obtain the range in the position pos
    /// @param pos : position of the range
    /// @return range required
    //-------------------------------------------------------------------------
    range_it get_range (size_t pos) const
    {
        Iter_t it1 = global_range.first + (pos * Block_size);
        Iter_t it2 =
            (pos == (nblock - 1)) ? global_range.last : it1 + Block_size;
        return range_it (it1, it2);
    };
    //-------------------------------------------------------------------------
    //  function : get_range_buf
    /// @brief obtain the auxiliary buffer of the thread
    //-------------------------------------------------------------------------
    range_buf get_range_buf ( ) const
    {
        return range_buf (buf, buf + Block_size);
    };

    //-------------------------------------------------------------------------
    //  function : exec
    /// @brief Initialize the thread local buffer with the ptr_buf pointer,
    ///        and begin with the execution of the functions stored in works
    //
    /// @param ptr_buf : Pointer to the memory assigned to the thread_local
    ///                  buffer
    /// @param counter : atomic counter for to invoke to the exec function
    ///                  with only 1 parameter
    //-------------------------------------------------------------------------
    void exec (value_t *ptr_buf, atomic_t &counter)
    {
        buf = ptr_buf;
        exec (counter);
    };

    void exec (atomic_t &counter);

//---------------------------------------------------------------------------
}; // end struct backbone
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
// initialization of the thread_local pointer to the auxiliary buffer
template < uint32_t Block_size, class Iter_t, class Compare >
thread_local typename std::iterator_traits< Iter_t >
::value_type *backbone< Block_size, Iter_t, Compare >::buf = nullptr;

//------------------------------------------------------------------------
//  function : backbone
/// @brief constructor of the class
//
/// @param first : iterator to the first element of the range to sort
/// @param last : iterator after the last element to the range to sort
/// @param comp : object for to compare two elements pointed by Iter_t
///               iterators
//------------------------------------------------------------------------
template < uint32_t Block_size, class Iter_t, class Compare >
backbone< Block_size, Iter_t, Compare >
::backbone (Iter_t first, Iter_t last, Compare comp)
: global_range (first, last), cmp (comp), error (false)
{
    assert ((last - first) >= 0);
    if (first == last) return; // nothing to do

    nelem = size_t (last - first);
    nblock = (nelem + Block_size - 1) / Block_size;
    ntail = (nelem % Block_size);
    index.reserve (nblock + 1);

    for (size_t i = 0; i < nblock; ++i) index.emplace_back (block_pos (i));

    range_tail.first =
        (ntail == 0) ? last : (first + ((nblock - 1) * Block_size));
    range_tail.last = last;
};
//
//-------------------------------------------------------------------------
//  function : exec
/// @brief execute the function_t stored in works, until counter is zero
//
/// @param counter : atomic counter. When 0 exits the function
//-------------------------------------------------------------------------
template < uint32_t Block_size, class Iter_t, class Compare >
void backbone< Block_size, Iter_t, Compare >::exec (atomic_t &counter)
{
    function_t func_exec;
    while (bscu::atomic_read (counter) != 0)
    {
        if (works.pop_move_back (func_exec)) func_exec ( );
        else std::this_thread::yield ( );
    };
};
//
//****************************************************************************
}; //    End namespace blk_detail
}; //    End namespace sort
}; //    End namespace boost
//****************************************************************************
#endif

/* backbone.hpp
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
*/