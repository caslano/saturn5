//----------------------------------------------------------------------------
/// @file parallel_stable_sort.hpp
/// @brief This file contains the class parallel_stable_sort
///
/// @author Copyright (c) 2016 Francisco Jose Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanying file LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __BOOST_SORT_PARALLEL_DETAIL_PARALLEL_STABLE_SORT_HPP
#define __BOOST_SORT_PARALLEL_DETAIL_PARALLEL_STABLE_SORT_HPP

#include <ciso646>
#include <functional>
#include <future>
#include <iterator>
#include <memory>
#include <type_traits>
#include <vector>
#include <boost/sort/sample_sort/sample_sort.hpp>
#include <boost/sort/common/util/traits.hpp>


namespace boost
{
namespace sort
{
namespace stable_detail
{

//---------------------------------------------------------------------------
//                    USING SENTENCES
//---------------------------------------------------------------------------
namespace bsc = boost::sort::common;
namespace bss = boost::sort::spin_detail;
using bsc::range;
using bsc::merge_half;
using boost::sort::sample_detail::sample_sort;
//
///---------------------------------------------------------------------------
/// @struct parallel_stable_sort
/// @brief This a structure for to implement a parallel stable sort, exception
///        safe
//----------------------------------------------------------------------------
template <class Iter_t, class Compare = compare_iter <Iter_t> >
struct parallel_stable_sort
{
    //-------------------------------------------------------------------------
    //                      DEFINITIONS
    //-------------------------------------------------------------------------
    typedef value_iter<Iter_t> value_t;

    //-------------------------------------------------------------------------
    //                     VARIABLES
    //-------------------------------------------------------------------------
    // Number of elements to sort
    size_t nelem;
    // Pointer to the auxiliary memory needed for the algorithm
    value_t *ptr;
    // Minimal number of elements for to be sorted in parallel mode
    const size_t nelem_min = 1 << 16;

    //------------------------------------------------------------------------
    //                F U N C T I O N S
    //------------------------------------------------------------------------
    parallel_stable_sort (Iter_t first, Iter_t last)
    : parallel_stable_sort (first, last, Compare(),
                            std::thread::hardware_concurrency()) { };

    parallel_stable_sort (Iter_t first, Iter_t last, Compare cmp)
    : parallel_stable_sort (first, last, cmp,
                            std::thread::hardware_concurrency()) { };

    parallel_stable_sort (Iter_t first, Iter_t last, uint32_t num_thread)
    : parallel_stable_sort (first, last, Compare(), num_thread) { };

    parallel_stable_sort (Iter_t first, Iter_t last, Compare cmp,
                          uint32_t num_thread);

    //
    //-----------------------------------------------------------------------------
    //  function : destroy_all
    /// @brief The utility is to destroy the temporary buffer used in the
    ///        sorting process
    //-----------------------------------------------------------------------------
    void destroy_all()
    {
        if (ptr != nullptr) std::return_temporary_buffer(ptr);
    };
    //
    //-----------------------------------------------------------------------------
    //  function :~parallel_stable_sort
    /// @brief destructor of the class. The utility is to destroy the temporary
    ///        buffer used in the sorting process
    //-----------------------------------------------------------------------------
    ~parallel_stable_sort() {destroy_all(); } ;
};
// end struct parallel_stable_sort

//
//############################################################################
//                                                                          ##
//                                                                          ##
//            N O N     I N L I N E      F U N C T I O N S                  ##
//                                                                          ##
//                                                                          ##
//############################################################################
//
//-----------------------------------------------------------------------------
//  function : parallel_stable_sort
/// @brief constructor of the class
///
/// @param first : iterator to the first element of the range to sort
/// @param last : iterator after the last element to the range to sort
/// @param comp : object for to compare two elements pointed by Iter_t
///                    iterators
/// @param nthread : Number of threads to use in the process. When this value
///                  is lower than 2, the sorting is done with 1 thread
//-----------------------------------------------------------------------------
template <class Iter_t, class Compare>
parallel_stable_sort <Iter_t, Compare>
::parallel_stable_sort (Iter_t first, Iter_t last, Compare comp,
                        uint32_t nthread) : nelem(0), ptr(nullptr)
{
    range<Iter_t> range_initial(first, last);
    assert(range_initial.valid());

    nelem = range_initial.size();
    size_t nptr = (nelem + 1) >> 1;

    if (nelem < nelem_min or nthread < 2)
    {
        bss::spinsort<Iter_t, Compare>
            (range_initial.first, range_initial.last, comp);
        return;
    };

    //------------------- check if sort --------------------------------------
    bool sw = true;
    for (Iter_t it1 = first, it2 = first + 1;
         it2 != last and (sw = not comp(*it2, *it1)); it1 = it2++);
    if (sw) return;

    //------------------- check if reverse sort ---------------------------
    sw = true;
    for (Iter_t it1 = first, it2 = first + 1;
         it2 != last and (sw = comp(*it2, *it1)); it1 = it2++);
    if (sw)
    {
        size_t nelem2 = nelem >> 1;
        Iter_t it1 = first, it2 = last - 1;
        for (size_t i = 0; i < nelem2; ++i)
            std::swap(*(it1++), *(it2--));
        return;
    };

    ptr = std::get_temporary_buffer<value_t>(nptr).first;
    if (ptr == nullptr) throw std::bad_alloc();

    //---------------------------------------------------------------------
    //     Parallel Process
    //---------------------------------------------------------------------
    range<Iter_t> range_first(range_initial.first, range_initial.first + nptr);

    range<Iter_t> range_second(range_initial.first + nptr, range_initial.last);

    range<value_t *> range_buffer(ptr, ptr + nptr);

    try
    {
        sample_sort<Iter_t, Compare>
            (range_initial.first, range_initial.first + nptr,
             comp, nthread, range_buffer);
    } catch (std::bad_alloc &)
    {
        destroy_all();
        throw std::bad_alloc();
    };

    try
    {
        sample_sort<Iter_t, Compare>
            (range_initial.first + nptr,
             range_initial.last, comp, nthread, range_buffer);
    } catch (std::bad_alloc &)
    {
        destroy_all();
        throw std::bad_alloc();
    };

    range_buffer = move_construct(range_buffer, range_first);
    range_initial = merge_half(range_initial, range_buffer, range_second, comp);
    destroy (range_buffer);


    
}; // end of constructor

//
//****************************************************************************
};//    End namespace stable_detail
//****************************************************************************
//

//---------------------------------------------------------------------------
//                    USING SENTENCES
//---------------------------------------------------------------------------
namespace bsc = boost::sort::common;
namespace bscu = bsc::util;
namespace bss = boost::sort::spin_detail;
using bsc::range;
using bsc::merge_half;
//
//############################################################################
//                                                                          ##
//                                                                          ##
//            P A R A L L E L _ S T A B L E _ S O R T                       ##
//                                                                          ##
//                                                                          ##
//############################################################################
//
//-----------------------------------------------------------------------------
//  function : parallel_stable_sort
/// @brief : parallel stable sort with 2 parameters
///
/// @param first : iterator to the first element of the range to sort
/// @param last : iterator after the last element to the range to sort
//-----------------------------------------------------------------------------
template<class Iter_t>
void parallel_stable_sort(Iter_t first, Iter_t last)
{
    typedef bscu::compare_iter<Iter_t> Compare;
    stable_detail::parallel_stable_sort<Iter_t, Compare>(first, last);
};
//
//-----------------------------------------------------------------------------
//  function : parallel_stable_sort
/// @brief parallel stable sort with 3 parameters. The third is the number 
///        of threads
///
/// @param first : iterator to the first element of the range to sort
/// @param last : iterator after the last element to the range to sort
/// @param nthread : Number of threads to use in the process. When this value
///                  is lower than 2, the sorting is done with 1 thread
//-----------------------------------------------------------------------------
template<class Iter_t>
void parallel_stable_sort(Iter_t first, Iter_t last, uint32_t nthread)
{
    typedef bscu::compare_iter<Iter_t> Compare;
    stable_detail::parallel_stable_sort<Iter_t, Compare>(first, last, nthread);
};
//
//-----------------------------------------------------------------------------
//  function : parallel_stable_sort
/// @brief : parallel stable sort with 3 parameters. The thisrd is the 
///          comparison object
///
/// @param first : iterator to the first element of the range to sort
/// @param last : iterator after the last element to the range to sort
/// @param comp : object for to compare two elements pointed by Iter_t
///               iterators
//-----------------------------------------------------------------------------
template <class Iter_t, class Compare,
          bscu::enable_if_not_integral<Compare> * = nullptr>
void parallel_stable_sort(Iter_t first, Iter_t last, Compare comp)
{
    stable_detail::parallel_stable_sort<Iter_t, Compare>(first, last, comp);
};

//
//-----------------------------------------------------------------------------
//  function : parallel_stable_sort
/// @brief : parallel stable sort with 3 parameters. 
///
/// @param first : iterator to the first element of the range to sort
/// @param last : iterator after the last element to the range to sort
/// @param comp : object for to compare two elements pointed by Iter_t
///               iterators
/// @param nthread : Number of threads to use in the process. When this value
///                  is lower than 2, the sorting is done with 1 thread
//-----------------------------------------------------------------------------
template<class Iter_t, class Compare>
void parallel_stable_sort (Iter_t first, Iter_t last, Compare comp,
                          uint32_t nthread)
{
    stable_detail::parallel_stable_sort<Iter_t, Compare>
                                                (first, last, comp, nthread);
}
//
//****************************************************************************
};//    End namespace sort
};//    End namespace boost
//****************************************************************************
//
#endif

/* parallel_stable_sort.hpp
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
*/