//----------------------------------------------------------------------------
/// @file block_indirect_sort.hpp
/// @brief block indirect sort algorithm
///
/// @author Copyright (c) 2016 Francisco Jose Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanying file LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __BOOST_SORT_PARALLEL_DETAIL_BLOCK_INDIRECT_SORT_HPP
#define __BOOST_SORT_PARALLEL_DETAIL_BLOCK_INDIRECT_SORT_HPP

#include <atomic>
#include <boost/sort/block_indirect_sort/blk_detail/merge_blocks.hpp>
#include <boost/sort/block_indirect_sort/blk_detail/move_blocks.hpp>
#include <boost/sort/block_indirect_sort/blk_detail/parallel_sort.hpp>
#include <boost/sort/pdqsort/pdqsort.hpp>
#include <boost/sort/common/util/traits.hpp>
#include <boost/sort/common/util/algorithm.hpp>
#include <future>
#include <iterator>

// This value is the minimal number of threads for to use the
// block_indirect_sort algorithm
#define BOOST_NTHREAD_BORDER 6

namespace boost
{
namespace sort
{
namespace blk_detail
{
//---------------------------------------------------------------------------
//         USING SENTENCES
//---------------------------------------------------------------------------
namespace bs = boost::sort;
namespace bsc = bs::common;
namespace bscu = bsc::util;
using bscu::compare_iter;
using bscu::value_iter;
using bsc::range;
using bsc::destroy;
using bsc::initialize;
using bscu::nbits64;
using bs::pdqsort;
using bscu::enable_if_string;
using bscu::enable_if_not_string;
using bscu::tmsb;
//
///---------------------------------------------------------------------------
/// @struct block_indirect_sort
/// @brief This class is the entry point of the block indirect sort. The code
///        of this algorithm is divided in several classes:
///        bis/block.hpp : basic structures used in the algorithm
///        bis/backbone.hpp : data used by all the classes
///        bis/merge_blocks.hpp : merge the internal blocks
///        bis/move_blocks.hpp : move the blocks, and obtain all the elements
///                              phisicaly sorted
///        bis/parallel_sort.hpp : make the parallel sort of each part in the
///                                initial division of the data
///
//----------------------------------------------------------------------------
template<uint32_t Block_size, uint32_t Group_size, class Iter_t,
                class Compare = compare_iter<Iter_t> >
struct block_indirect_sort
{
    //------------------------------------------------------------------------
    //                  D E F I N I T I O N S
    //------------------------------------------------------------------------
    typedef typename std::iterator_traits<Iter_t>::value_type value_t;
    typedef std::atomic<uint32_t> atomic_t;
    typedef range<size_t> range_pos;
    typedef range<Iter_t> range_it;
    typedef range<value_t *> range_buf;
    typedef std::function<void(void)> function_t;

    // classes used in the internal operations of the algorithm
    typedef block_pos block_pos_t;
    typedef block<Block_size, Iter_t> block_t;
    typedef backbone<Block_size, Iter_t, Compare> backbone_t;
    typedef parallel_sort<Block_size, Iter_t, Compare> parallel_sort_t;

    typedef merge_blocks<Block_size, Group_size, Iter_t, Compare> merge_blocks_t;
    typedef move_blocks<Block_size, Group_size, Iter_t, Compare> move_blocks_t;
    typedef compare_block_pos<Block_size, Iter_t, Compare> compare_block_pos_t;
    //
    //------------------------------------------------------------------------
    //       V A R I A B L E S   A N D  C O N S T A N T S
    //------------------------------------------------------------------------
    // contains the data and the internal data structures of the algorithm for
    // to be shared between the classes which are part of the algorithm
    backbone_t bk;
    // atomic counter for to detect the end of the works created inside
    // the object
    atomic_t counter;
    // pointer to the uninitialized memory used for the thread buffers
    value_t *ptr;
    // indicate if the memory pointed by ptr is initialized
    bool construct;
    // range from extract the buffers for the threads
    range_buf rglobal_buf;
    // number of threads to use
    uint32_t nthread;
    //
    //------------------------------------------------------------------------
    //                F U N C T I O N S
    //------------------------------------------------------------------------

    block_indirect_sort(Iter_t first, Iter_t last, Compare cmp, uint32_t nthr);

    block_indirect_sort(Iter_t first, Iter_t last) :
                        block_indirect_sort(first, last, Compare(),
                        std::thread::hardware_concurrency()) { }


    block_indirect_sort(Iter_t first, Iter_t last, Compare cmp) :
                        block_indirect_sort(first, last, cmp,
                        std::thread::hardware_concurrency()) { }


    block_indirect_sort(Iter_t first, Iter_t last, uint32_t nthread) :
                        block_indirect_sort(first, last, Compare(), nthread){}


    //
    //------------------------------------------------------------------------
    //  function :destroy_all
    /// @brief destructor all the data structures of the class (if the memory
    ///        is constructed, is destroyed) and  return the uninitialized
    ///        memory
    //------------------------------------------------------------------------
    void destroy_all(void)
    {
        if (ptr != nullptr)
        {
            if (construct)
            {
                destroy(rglobal_buf);
                construct = false;
            };
            std::return_temporary_buffer(ptr);
            ptr = nullptr;
        };
    }
    //
    //------------------------------------------------------------------------
    //  function :~block_indirect_sort
    /// @brief destructor of the class (if the memory is constructed, is
    ///        destroyed) and  return the uninitialized memory
    //------------------------------------------------------------------------
    ~block_indirect_sort(void)
    {
        destroy_all();
    }

    void split_range(size_t pos_index1, size_t pos_index2,
                    uint32_t level_thread);

    void start_function(void);

//-------------------------------------------------------------------------
}; // End class block_indirect_sort
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
//  function : block_indirect_sort
/// @brief begin with the execution of the functions stored in works
/// @param first : iterator to the first element of the range to sort
/// @param last : iterator after the last element to the range to sort
/// @param comp : object for to compare two elements pointed by Iter_t
///               iterators
/// @param nthr : Number of threads to use in the process.When this value
///               is lower than 2, the sorting is done with 1 thread
//-------------------------------------------------------------------------
template<uint32_t Block_size, uint32_t Group_size, class Iter_t, class Compare>
block_indirect_sort<Block_size, Group_size, Iter_t, Compare>
::block_indirect_sort(Iter_t first, Iter_t last, Compare cmp, uint32_t nthr)
: bk(first, last, cmp), counter(0), ptr(nullptr), construct(false),
  nthread(nthr)
{
    try
    {
        assert((last - first) >= 0);
        size_t nelem = size_t(last - first);
        if (nelem == 0) return;

        //------------------- check if sort -----------------------------------
        bool sorted = true;
        for (Iter_t it1 = first, it2 = first + 1; it2 != last and (sorted =
                        not bk.cmp(*it2, *it1)); it1 = it2++);
        if (sorted) return;

        //------------------- check if reverse sort ---------------------------
        sorted = true;
        for (Iter_t it1 = first, it2 = first + 1; it2 != last and (sorted =
                        not bk.cmp(*it1, *it2)); it1 = it2++);

        if (sorted)
        {
            size_t nelem2 = nelem >> 1;
            Iter_t it1 = first, it2 = last - 1;
            for (size_t i = 0; i < nelem2; ++i)
            {
                std::swap(*(it1++), *(it2--));
            };
            return;
        };

        //---------------- check if only single thread -----------------------
        size_t nthreadmax = nelem / (Block_size * Group_size) + 1;
        if (nthread > nthreadmax) nthread = (uint32_t) nthreadmax;

        uint32_t nbits_size = (nbits64(sizeof(value_t)) >> 1);
        if (nbits_size > 5) nbits_size = 5;
        size_t max_per_thread = 1 << (18 - nbits_size);

        if (nelem < (max_per_thread) or nthread < 2)
        {
            //intro_sort (first, last, bk.cmp);
            pdqsort(first, last, bk.cmp);
            return;
        };

        //----------- creation of the temporary buffer --------------------
        ptr = std::get_temporary_buffer<value_t>(Block_size * nthread).first;
        if (ptr == nullptr)
        {
            bk.error = true;
            throw std::bad_alloc();
        };

        rglobal_buf = range_buf(ptr, ptr + (Block_size * nthread));
        initialize(rglobal_buf, *first);
        construct = true;

        // creation of the buffers for the threads
        std::vector<value_t *> vbuf(nthread);
        for (uint32_t i = 0; i < nthread; ++i)
        {
            vbuf[i] = ptr + (i * Block_size);
        };

        // Insert the first work in the stack
        bscu::atomic_write(counter, 1);
        function_t f1 = [&]( )
        {
            start_function ( );
            bscu::atomic_sub (counter, 1);
        };
        bk.works.emplace_back(f1);

        //---------------------------------------------------------------------
        //                    PROCESS
        //---------------------------------------------------------------------
        std::vector<std::future<void> > vfuture(nthread);

        // The function launched with the futures is "execute the functions of
        // the stack until this->counter is zero
        // vbuf[i] is the memory from the main thread for to configure the
        // thread local buffer
        for (uint32_t i = 0; i < nthread; ++i)
        {
            auto f1 = [=, &vbuf]( )
            {   bk.exec (vbuf[i], this->counter);};
            vfuture[i] = std::async(std::launch::async, f1);
        };
        for (uint32_t i = 0; i < nthread; ++i)
            vfuture[i].get();
        if (bk.error) throw std::bad_alloc();
    }
    catch (std::bad_alloc &)
    {
        destroy_all();
        throw;
    }
};
//
//-----------------------------------------------------------------------------
//  function : split_rage
/// @brief this function splits a range of positions in the index, and
///        depending of the size, sort directly or make to a recursive call
///        to split_range
/// @param pos_index1 : first position in the index
/// @param pos_index2 : position after the last in the index
/// @param level_thread : depth of the call. When 0 sort the blocks
//-----------------------------------------------------------------------------
template<uint32_t Block_size, uint32_t Group_size, class Iter_t, class Compare>
void block_indirect_sort<Block_size, Group_size, Iter_t, Compare>
::split_range(size_t pos_index1, size_t pos_index2, uint32_t level_thread)
{
    size_t nblock = pos_index2 - pos_index1;

    //-------------------------------------------------------------------------
    // In the blocks not sorted, the physical position is the logical position
    //-------------------------------------------------------------------------
    Iter_t first = bk.get_block(pos_index1).first;
    Iter_t last = bk.get_range(pos_index2 - 1).last;

    if (nblock < Group_size)
    {
        pdqsort(first, last, bk.cmp);
        return;
    };

    size_t pos_index_mid = pos_index1 + (nblock >> 1);
    atomic_t son_counter(1);

    //-------------------------------------------------------------------------
    // Insert in the stack the work for the second part, and the actual thread,
    // execute the first part
    //-------------------------------------------------------------------------
    if (level_thread != 0)
    {
        auto f1 = [=, &son_counter]( )
        {
            split_range (pos_index_mid, pos_index2, level_thread - 1);
            bscu::atomic_sub (son_counter, 1);
        };
        bk.works.emplace_back(f1);
        if (bk.error) return;
        split_range(pos_index1, pos_index_mid, level_thread - 1);
    }
    else
    {
        Iter_t mid = first + ((nblock >> 1) * Block_size);
        auto f1 = [=, &son_counter]( )
        {
            parallel_sort_t (bk, mid, last);
            bscu::atomic_sub (son_counter, 1);
        };
        bk.works.emplace_back(f1);
        if (bk.error) return;
        parallel_sort_t(bk, first, mid);
    };
    bk.exec(son_counter);
    if (bk.error) return;
    merge_blocks_t(bk, pos_index1, pos_index_mid, pos_index2);
};

//
//-----------------------------------------------------------------------------
//  function : start_function
/// @brief this function init the process. When the number of threads is lower
///        than a predefined value, sort the elements with a parallel pdqsort.
//-----------------------------------------------------------------------------
template<uint32_t Block_size, uint32_t Group_size, class Iter_t, class Compare>
void block_indirect_sort<Block_size, Group_size, Iter_t, Compare>
::start_function(void)
{
    if (nthread < BOOST_NTHREAD_BORDER)
    {
        parallel_sort_t(bk, bk.global_range.first, bk.global_range.last);
    }
    else
    {
        size_t level_thread = nbits64(nthread - 1) - 1;
        split_range(0, bk.nblock, level_thread - 1);
        if (bk.error) return;
        move_blocks_t k(bk);
    };
};

///---------------------------------------------------------------------------
//  function block_indirect_sort_call
/// @brief This class is select the block size in the block_indirect_sort
///        algorithm depending of the type and size of the data to sort
///
//----------------------------------------------------------------------------
template <class Iter_t, class Compare,
         enable_if_string<value_iter<Iter_t>> * = nullptr>
inline void block_indirect_sort_call(Iter_t first, Iter_t last, Compare cmp,
                uint32_t nthr)
{
    block_indirect_sort<128, 128, Iter_t, Compare>(first, last, cmp, nthr);
};

template<size_t Size>
struct block_size
{
    static constexpr const uint32_t BitsSize =
                    (Size == 0) ? 0 : (Size > 256) ? 9 : tmsb[Size - 1];
    static constexpr const uint32_t sz[10] =
    { 4096, 4096, 4096, 4096, 2048, 1024, 768, 512, 256, 128 };
    static constexpr const uint32_t data = sz[BitsSize];
};
//
///---------------------------------------------------------------------------
/// @struct block_indirect_sort_call
/// @brief This class is select the block size in the block_indirect_sort
///        algorithm depending of the type and size of the data to sort
///
//----------------------------------------------------------------------------
template <class Iter_t, class Compare,
          enable_if_not_string<value_iter<Iter_t>> * = nullptr>
inline void block_indirect_sort_call (Iter_t first, Iter_t last, Compare cmp,
                                      uint32_t nthr)
{
    block_indirect_sort<block_size<sizeof (value_iter<Iter_t> )>::data, 64,
                        Iter_t, Compare> (first, last, cmp, nthr);
};

//
//****************************************************************************
}; //    End namespace blk_detail
//****************************************************************************
//
namespace bscu = boost::sort::common::util;
//
//############################################################################
//                                                                          ##
//                                                                          ##
//               B L O C K _ I N D I R E C T _ S O R T                      ##
//                                                                          ##
//                                                                          ##
//############################################################################
//
//-----------------------------------------------------------------------------
//  function : block_indirect_sort
/// @brief invocation of block_indirtect_sort with 2 parameters
///
/// @param first : iterator to the first element of the range to sort
/// @param last : iterator after the last element to the range to sort
//-----------------------------------------------------------------------------
template<class Iter_t>
void block_indirect_sort(Iter_t first, Iter_t last)
{
    typedef bscu::compare_iter<Iter_t> Compare;
    blk_detail::block_indirect_sort_call (first, last, Compare(),
                                          std::thread::hardware_concurrency());
}

//
//-----------------------------------------------------------------------------
//  function : block_indirect_sort
/// @brief invocation of block_indirtect_sort with 3 parameters. The third is 
///        the number of threads
///
/// @param first : iterator to the first element of the range to sort
/// @param last : iterator after the last element to the range to sort
/// @param nthread : Number of threads to use in the process. When this value
///                  is lower than 2, the sorting is done with 1 thread
//-----------------------------------------------------------------------------
template<class Iter_t>
void block_indirect_sort(Iter_t first, Iter_t last, uint32_t nthread)
{
    typedef bscu::compare_iter<Iter_t> Compare;
    blk_detail::block_indirect_sort_call(first, last, Compare(), nthread);
}
//
//-----------------------------------------------------------------------------
//  function : block_indirect_sort
/// @brief invocation of block_indirtect_sort with 3 parameters. The third is 
///        the comparison object
///
/// @param first : iterator to the first element of the range to sort
/// @param last : iterator after the last element to the range to sort
/// @param comp : object for to compare two elements pointed by Iter_t
///               iterators
//-----------------------------------------------------------------------------
template <class Iter_t, class Compare,
          bscu::enable_if_not_integral<Compare> * = nullptr>
void block_indirect_sort(Iter_t first, Iter_t last, Compare comp)
{
    blk_detail::block_indirect_sort_call (first, last, comp,
                                      std::thread::hardware_concurrency());
}

//
//-----------------------------------------------------------------------------
//  function : block_indirect_sort
/// @brief invocation of block_indirtect_sort with 4 parameters. 
///
/// @param first : iterator to the first element of the range to sort
/// @param last : iterator after the last element to the range to sort
/// @param comp : object for to compare two elements pointed by Iter_t
///               iterators
/// @param nthread : Number of threads to use in the process. When this value
///                  is lower than 2, the sorting is done with 1 thread
//-----------------------------------------------------------------------------
template<class Iter_t, class Compare>
void block_indirect_sort (Iter_t first, Iter_t last, Compare comp,
                          uint32_t nthread)
{
    blk_detail::block_indirect_sort_call(first, last, comp, nthread);
}
//
//****************************************************************************
}; //    End namespace sort
}; //    End namespace boost
//****************************************************************************
//
#endif

/* block_indirect_sort.hpp
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
*/