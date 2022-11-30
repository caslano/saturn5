//----------------------------------------------------------------------------
/// @file parallel_sort.hpp
/// @brief Contains the parallel_sort class, which is part of the
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
#ifndef __BOOST_SORT_PARALLEL_DETAIL_PARALLEL_SORT_HPP
#define __BOOST_SORT_PARALLEL_DETAIL_PARALLEL_SORT_HPP

#include <boost/sort/block_indirect_sort/blk_detail/backbone.hpp>
#include <boost/sort/pdqsort/pdqsort.hpp>
#include <boost/sort/common/pivot.hpp>

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
using bscu::nbits64;
using bsc::pivot9;
using boost::sort::pdqsort;
//
///---------------------------------------------------------------------------
/// @struct parallel_sort
/// @brief This class do a parallel sort, using the quicksort filtering,
///        splitting the data until the number of elements is smaller than a
///        predefined value (max_per_thread)
//----------------------------------------------------------------------------
template<uint32_t Block_size, class Iter_t, class Compare>
struct parallel_sort
{
    //-------------------------------------------------------------------------
    //                  D E F I N I T I O N S
    //-------------------------------------------------------------------------
    typedef typename std::iterator_traits<Iter_t>::value_type value_t;
    typedef std::atomic<uint32_t> atomic_t;
    typedef std::function<void(void)> function_t;
    typedef backbone<Block_size, Iter_t, Compare> backbone_t;

    //------------------------------------------------------------------------
    //                V A R I A B L E S
    //------------------------------------------------------------------------
    // reference to a object with all the data to sort
    backbone_t &bk;

    // maximun number of element to sort woth 1 thread
    size_t max_per_thread;

    // atomic counter for to detect the end of the works created inside
    // the object
    atomic_t counter;

    //------------------------------------------------------------------------
    //                F U N C T I O N S
    //------------------------------------------------------------------------
    parallel_sort(backbone_t &bkbn, Iter_t first, Iter_t last);

    void divide_sort(Iter_t first, Iter_t last, uint32_t level);
    //
    //------------------------------------------------------------------------
    //  function : function_divide_sort
    /// @brief create a function_t with a call to divide_sort, and inser in
    ///        the stack of the backbone
    //
    /// @param first : iterator to the first element of the range to divide
    /// @param last : iterator to the next element after the last element of
    ///               the range to divide
    /// @param level : level of depth in the division.When zero call to
    ///                pdqsort
    /// @param counter : atomic variable which is decremented when finish
    ///                  the function. This variable is used for to know
    ///                  when are finished all the function_t created
    ///                  inside an object
    /// @param error : global indicator of error.
    //------------------------------------------------------------------------
    void function_divide_sort(Iter_t first, Iter_t last, uint32_t level,
                              atomic_t &counter, bool &error)
    {
        bscu::atomic_add(counter, 1);
        function_t f1 = [this, first, last, level, &counter, &error]( )
        {
            if (not error)
            {
                try
                {
                    this->divide_sort (first, last, level);
                }
                catch (std::bad_alloc &)
                {
                    error = true;
                };
            };
            bscu::atomic_sub (counter, 1);
        };
        bk.works.emplace_back(f1);
    };

//--------------------------------------------------------------------------
};// end struct parallel_sort
//--------------------------------------------------------------------------
//
//############################################################################
//                                                                          ##
//                                                                          ##
//            N O N     I N L I N E      F U N C T I O N S                  ##
//                                                                          ##
//                                                                          ##
//############################################################################
//
//------------------------------------------------------------------------
//  function : parallel_sort
/// @brief constructor of the class
/// @param [in] bkbn : backbone struct with all the information to sort
/// @param [in] first : iterator to the first element to sort
/// @param [in] last : iterator to the next element after the last
//------------------------------------------------------------------------
template<uint32_t Block_size, class Iter_t, class Compare>
parallel_sort<Block_size, Iter_t, Compare>
::parallel_sort(backbone_t &bkbn, Iter_t first, Iter_t last)
 : bk(bkbn), counter(0)
{
    assert((last - first) >= 0);
    size_t nelem = size_t(last - first);

    //------------------- check if sort --------------------------------------
    bool sorted = true;
    for (Iter_t it1 = first, it2 = first + 1;
         it2 != last and (sorted = not bk.cmp(*it2, *it1)); it1 = it2++);
    if (sorted) return;

    //------------------- check if reverse sort ---------------------------
    sorted = true;
    for (Iter_t it1 = first, it2 = first + 1;
         it2 != last and (sorted = not bk.cmp(*it1, *it2)); it1 = it2++);

    if (sorted)
    {
        size_t nelem2 = nelem >> 1;
        Iter_t it1 = first, it2 = last - 1;
        for (size_t i = 0; i < nelem2; ++i)
            std::swap(*(it1++), *(it2--));
        return;
    };

    //-------------------max_per_thread ---------------------------
    uint32_t nbits_size = (nbits64(sizeof(value_t))) >> 1;
    if (nbits_size > 5) nbits_size = 5;
    max_per_thread = 1 << (18 - nbits_size);

    uint32_t level = ((nbits64(nelem / max_per_thread)) * 3) / 2;

    //---------------- check if only single thread -----------------------
    if (nelem < (max_per_thread))
    {
        pdqsort(first, last, bk.cmp);
        return;
    };
    if (not bk.error) divide_sort(first, last, level);

    // wait until all the parts are finished
    bk.exec(counter);
};

//------------------------------------------------------------------------
//  function : divide_sort
/// @brief this function divide the data in two part, for to be sorted in
///        a parallel mode
/// @param first : iterator to the first element to sort
/// @param last : iterator to the next element after the last
/// @param level : level of depth before call to pdqsort
//------------------------------------------------------------------------
template<uint32_t Block_size, class Iter_t, class Compare>
void parallel_sort<Block_size, Iter_t, Compare>
::divide_sort(Iter_t first, Iter_t last, uint32_t level)
{
    //------------------- check if sort -----------------------------------
    bool sorted = true;
    for (Iter_t it1 = first, it2 = first + 1;
         it2 != last and (sorted = not bk.cmp(*it2, *it1)); it1 = it2++);
    if (sorted) return;

    //---------------- check if finish the subdivision -------------------
    size_t nelem = last - first;
    if (level == 0 or nelem < (max_per_thread))
    {
        return pdqsort(first, last, bk.cmp);
    };

    //-------------------- pivoting  ----------------------------------
    pivot9(first, last, bk.cmp);
    const value_t &val = const_cast<value_t &>(*first);
    Iter_t c_first = first + 1, c_last = last - 1;

    while (bk.cmp(*c_first, val))   ++c_first;
    while (bk.cmp(val, *c_last))    --c_last;

    while (c_first < c_last)
    {
        std::swap(*(c_first++), *(c_last--));
        while (bk.cmp(*c_first, val))
            ++c_first;
        while (bk.cmp(val, *c_last))
            --c_last;
    };

    std::swap(*first, *c_last);

    // insert  the work of the second half in the stack of works
    function_divide_sort(c_first, last, level - 1, counter, bk.error);
    if (bk.error) return;

    // The first half is done by the same thread
    function_divide_sort(first, c_last, level - 1, counter, bk.error);
};
//
//****************************************************************************
};//    End namespace blk_detail
};//    End namespace sort
};//    End namespace boost
//****************************************************************************
//
#endif

/* parallel_sort.hpp
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
*/