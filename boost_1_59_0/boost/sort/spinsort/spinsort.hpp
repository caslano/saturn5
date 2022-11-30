//----------------------------------------------------------------------------
/// @file spinsort.hpp
/// @brief Spin Sort algorithm
///
/// @author Copyright (c) 2016 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanying file LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __BOOST_SORT_PARALLEL_ALGORITHM_SPIN_SORT_HPP
#define __BOOST_SORT_PARALLEL_ALGORITHM_SPIN_SORT_HPP

//#include <boost/sort/spinsort/util/indirect.hpp>
#include <boost/sort/insert_sort/insert_sort.hpp>
#include <boost/sort/common/util/traits.hpp>
#include <boost/sort/common/util/algorithm.hpp>
#include <boost/sort/common/range.hpp>
#include <boost/sort/common/indirect.hpp>
#include <cstdlib>
#include <functional>
#include <iterator>
#include <memory>
#include <type_traits>
#include <vector>
#include <cstddef>

namespace boost
{
namespace sort
{
namespace spin_detail
{

//----------------------------------------------------------------------------
//                USING SENTENCES
//----------------------------------------------------------------------------
namespace bsc = boost::sort::common;
using bsc::range;
using bsc::util::nbits64;
using bsc::util::compare_iter;
using bsc::util::value_iter;
using boost::sort::insert_sort;

//
//############################################################################
//                                                                          ##
//          D E F I N I T I O N S    O F    F U N C T I O N S               ##
//                                                                          ##
//############################################################################
//
template <class Iter1_t, class Iter2_t, typename Compare>
static void insert_partial_sort (Iter1_t first, Iter1_t mid,
                                 Iter1_t last, Compare comp,
                                 const range<Iter2_t> &rng_aux);

template<class Iter1_t, class Iter2_t, class Compare>
static bool check_stable_sort (const range<Iter1_t> &rng_data,
                               const range<Iter2_t> &rng_aux, Compare comp);

template<class Iter1_t, class Iter2_t, class Compare>
static void range_sort (const range<Iter1_t> &range1,
                        const range<Iter2_t> &range2, Compare comp,
                        uint32_t level);

template<class Iter1_t, class Iter2_t, class Compare>
static void sort_range_sort (const range<Iter1_t> &rng_data,
                             const range<Iter2_t> &rng_aux, Compare comp);

//
//-----------------------------------------------------------------------------
//  function : insert_partial_sort
/// @brief : Insertion sort of elements sorted
/// @param first: iterator to the first element of the range
/// @param mid : last pointer of the sorted data, and first pointer to the
///               elements to insert
/// @param last : iterator to the next element of the last in the range
/// @param comp :
/// @comments : the two ranges are sorted
//-----------------------------------------------------------------------------
template<class Iter1_t, class Iter2_t, typename Compare>
static void insert_partial_sort (Iter1_t first, Iter1_t mid, Iter1_t last,
                                 Compare comp, const range<Iter2_t> &rng_aux)
{
    //------------------------------------------------------------------------
    //                 metaprogram
    //------------------------------------------------------------------------
    typedef value_iter<Iter1_t> value_t;
    typedef value_iter<Iter2_t> value2_t;
    static_assert (std::is_same<value_t, value2_t>::value,
                    "Incompatible iterators\n");

    //--------------------------------------------------------------------
    //                   program
    //--------------------------------------------------------------------
    assert(size_t(last - mid) <= rng_aux.size());

    if (mid == last) return;
    //insertionsort ( mid, last, comp);
    if (first == mid) return;

    //------------------------------------------------------------------------
    // creation of the vector of elements to insert and their position in the
    // sorted part
    // the data are inserted in rng_aux
    //-----------------------------------------------------------------------
    std::vector<Iter1_t> viter;
    Iter2_t beta = rng_aux.first, data = rng_aux.first;

    for (Iter1_t alpha = mid; alpha != last; ++alpha)
        *(beta++) = std::move(*alpha);

    size_t ndata = last - mid;

    Iter1_t linf = first, lsup = mid;
    for (uint32_t i = 0; i < ndata; ++i)
    {
        Iter1_t it1 = std::upper_bound(linf, lsup, *(data + i), comp);
        viter.push_back(it1);
        linf = it1;
    };

    // moving the elements
    viter.push_back(mid);
    for (uint32_t i = viter.size() - 1; i != 0; --i)
    {
        Iter1_t src = viter[i], limit = viter[i - 1];
        Iter1_t dest = src + (i);
        while (src != limit) *(--dest) = std::move(*(--src));
        *(viter[i - 1] + (i - 1)) = std::move(*(data + (i - 1)));
    };
}
;
//-----------------------------------------------------------------------------
//  function : check_stable_sort
/// @brief check if the elements between first and last are osted or reverse
///        sorted. If the number of elements not sorted is small, insert in
///        the sorted part
/// @param range_input : range with the elements to sort
/// @param range_buffer : range with the elements sorted
/// @param comp : object for to compare two elements
/// @param level : when is 1, sort with the insertionsort algorithm
///                if not make a recursive call splitting the ranges
//
/// @comments : if the number of levels is odd, the data are in the first
/// parameter of range_sort, and the results appear in the second parameter
/// If the number of levels is even, the data are in the second
/// parameter of range_sort, and the results are in the same parameter
//-----------------------------------------------------------------------------
template<class Iter1_t, class Iter2_t, class Compare>
static bool check_stable_sort(const range<Iter1_t> &rng_data,
                              const range<Iter2_t> &rng_aux, Compare comp)
{
    //------------------------------------------------------------------------
    //              metaprogramming
    //------------------------------------------------------------------------
    typedef value_iter<Iter1_t> value_t;
    typedef value_iter<Iter2_t> value2_t;
    static_assert (std::is_same<value_t, value2_t>::value,
                    "Incompatible iterators\n");

    //------------------------------------------------------------------------
    //                    program
    //------------------------------------------------------------------------
    // the maximun number of elements not ordered, for to be inserted in the
    // sorted part
    //const ptrdiff_t  min_insert_partial_sort = 32 ;
    const size_t ndata = rng_data.size();
    if (ndata < 32)
    {
        insert_sort(rng_data.first, rng_data.last, comp);
        return true;
    };
    const size_t min_insert_partial_sort =
                    ((ndata >> 3) < 33) ? 32 : (ndata >> 3);
    if (ndata < 2) return true;

    // check if sorted
    bool sw = true;
    Iter1_t it2 = rng_data.first + 1;
    for (Iter1_t it1 = rng_data.first;
                    it2 != rng_data.last and (sw = not comp(*it2, *it1)); it1 =
                                    it2++)
        ;
    if (sw) return true;

    // insert the elements between it1 and last
    if (size_t(rng_data.last - it2) < min_insert_partial_sort)
    {
        sort_range_sort(range<Iter1_t>(it2, rng_data.last), rng_aux, comp);
        insert_partial_sort(rng_data.first, it2, rng_data.last, comp, rng_aux);
        return true;
    };

    // check if reverse sorted
    if ((it2 != (rng_data.first + 1))) return false;
    sw = true;
    for (Iter1_t it1 = rng_data.first;
                    it2 != rng_data.last and (sw = comp(*it2, *it1)); it1 =
                                    it2++)
        ;
    if (size_t(rng_data.last - it2) >= min_insert_partial_sort) return false;

    // reverse the elements between first and it1
    size_t nreverse = it2 - rng_data.first;
    Iter1_t alpha(rng_data.first), beta(it2 - 1), mid(
                    rng_data.first + (nreverse >> 1));
    while (alpha != mid)
        std::swap(*(alpha++), *(beta--));

    // insert the elements between it1 and last
    if (it2 != rng_data.last)
    {
        sort_range_sort(range<Iter1_t>(it2, rng_data.last), rng_aux, comp);
        insert_partial_sort(rng_data.first, it2, rng_data.last, comp, rng_aux);
    };
    return true;
}
;
//-----------------------------------------------------------------------------
//  function : range_sort
/// @brief this function divide r_input in two parts, sort it,and merge moving
///        the elements to range_buf
/// @param range_input : range with the elements to sort
/// @param range_buffer : range with the elements sorted
/// @param comp : object for to compare two elements
/// @param level : when is 1, sort with the insertionsort algorithm
///                if not make a recursive call splitting the ranges
//
/// @comments : if the number of levels is odd, the data are in the first
/// parameter of range_sort, and the results appear in the second parameter
/// If the number of levels is even, the data are in the second
/// parameter of range_sort, and the results are in the same parameter
/// The two ranges must have the same size
//-----------------------------------------------------------------------------
template<class Iter1_t, class Iter2_t, class Compare>
static void range_sort(const range<Iter1_t> &range1,
                       const range<Iter2_t> &range2, Compare comp,
                       uint32_t level)
{
    //-----------------------------------------------------------------------
    //                  metaprogram
    //-----------------------------------------------------------------------
    typedef value_iter<Iter1_t> value_t;
    typedef value_iter<Iter2_t> value2_t;
    static_assert (std::is_same<value_t, value2_t>::value,
                    "Incompatible iterators\n");

    //-----------------------------------------------------------------------
    //                  program
    //-----------------------------------------------------------------------
    typedef range<Iter1_t> range_it1;
    typedef range<Iter2_t> range_it2;
    assert(range1.size() == range2.size() and level != 0);

    //------------------- check if sort --------------------------------------
    if (range1.size() > 1024)
    {
        if ((level & 1) == 0)
        {
            if (check_stable_sort(range2, range1, comp)) return;
        }
        else
        {
            if (check_stable_sort(range1, range2, comp))
            {
                move_forward(range2, range1);
                return;
            };
        };
    };

    //------------------- normal process -----------------------------------
    size_t nelem1 = (range1.size() + 1) >> 1;
    range_it1 range_input1(range1.first, range1.first + nelem1),
                           range_input2(range1.first + nelem1, range1.last);

    if (level < 2)
    {
        insert_sort(range_input1.first, range_input1.last, comp);
        insert_sort(range_input2.first, range_input2.last, comp);
    }
    else
    {
        range_sort (range_it2(range2.first, range2.first + nelem1),
                    range_input1, comp, level - 1);

        range_sort (range_it2(range2.first + nelem1, range2.last),
                    range_input2, comp, level - 1);
    };

    merge(range2, range_input1, range_input2, comp);
}
;
//-----------------------------------------------------------------------------
//  function : sort_range_sort
/// @brief this sort elements using the range_sort function and receiving a
///        buffer of initialized memory
/// @param rng_data : range with the elements to sort
/// @param rng_aux : range of at least the same memory than rng_data used as
///                  auxiliary memory in the sorting
/// @param comp : object for to compare two elements
//-----------------------------------------------------------------------------
template<class Iter1_t, class Iter2_t, class Compare>
static void sort_range_sort(const range<Iter1_t> &rng_data,
                            const range<Iter2_t> &rng_aux, Compare comp)
{
    //-----------------------------------------------------------------------
    //                  metaprogram
    //-----------------------------------------------------------------------
    typedef value_iter<Iter1_t> value_t;
    typedef value_iter<Iter2_t> value2_t;
    static_assert (std::is_same<value_t, value2_t>::value,
                    "Incompatible iterators\n");

    //------------------------------------------------------------------------
    //                    program
    //------------------------------------------------------------------------
    // minimal number of element before to jump to insertionsort
    static const uint32_t sort_min = 32;
    if (rng_data.size() <= sort_min)
    {
        insert_sort(rng_data.first, rng_data.last, comp);
        return;
    };

#ifdef __BS_DEBUG
    assert (rng_aux.size () >= rng_data.size ());
#endif

    range<Iter2_t> rng_buffer(rng_aux.first, rng_aux.first + rng_data.size());
    uint32_t nlevel =
                    nbits64(((rng_data.size() + sort_min - 1) / sort_min) - 1);
    //assert (nlevel != 0);

    if ((nlevel & 1) == 0)
    {
        range_sort(rng_buffer, rng_data, comp, nlevel);
    }
    else
    {
        range_sort(rng_data, rng_buffer, comp, nlevel);
        move_forward(rng_data, rng_buffer);
    };
}
;
//
//############################################################################
//                                                                          ##
//                              S T R U C T                                 ##
//                                                                          ##
//                           S P I N _ S O R T                              ##
//                                                                          ##
//############################################################################
//---------------------------------------------------------------------------
/// @struct spin_sort
/// @brief  This class implement s stable sort algorithm with 1 thread, with
///         an auxiliary memory of N/2 elements
//----------------------------------------------------------------------------
template<class Iter_t, typename Compare = compare_iter<Iter_t>>
class spinsort
{
    //------------------------------------------------------------------------
    //               DEFINITIONS AND CONSTANTS
    //------------------------------------------------------------------------
    typedef value_iter<Iter_t> value_t;
    typedef range<Iter_t> range_it;
    typedef range<value_t *> range_buf;
    // When the number of elements to sort is smaller than Sort_min, are sorted
    // by the insertion sort algorithm
    static const uint32_t Sort_min = 36;

    //------------------------------------------------------------------------
    //                      VARIABLES
    //------------------------------------------------------------------------
    // Pointer to the auxiliary memory
    value_t *ptr;

    // Number of elements in the auxiliary memory
    size_t nptr;

    // construct indicate if the auxiliary memory in initialized, and owner
    // indicate if the auxiliary memory had been created inside the object or
    // had
    // been received as a parameter
    bool construct = false, owner = false;

    //------------------------------------------------------------------------
    //                   PRIVATE FUNCTIONS
    //-------------------------------------------------------------------------
    spinsort (Iter_t first, Iter_t last, Compare comp, value_t *paux,
               size_t naux);

public:
    //------------------------------------------------------------------------
    //                   PUBLIC FUNCTIONS
    //-------------------------------------------------------------------------
    spinsort(Iter_t first, Iter_t last, Compare comp = Compare())
    : spinsort(first, last, comp, nullptr, 0) { };

    spinsort(Iter_t first, Iter_t last, Compare comp, range_buf range_aux)
    : spinsort(first, last, comp, range_aux.first, range_aux.size()) { };
    //
    //-----------------------------------------------------------------------
    //  function :~spinsort
    /// @brief destructor of the struct. Destroy the elements if construct is
    /// true,
    ///        and return the memory if owner is true
    //-----------------------------------------------------------------------
    ~spinsort(void)
    {
        if (construct)
        {
            destroy(range<value_t *>(ptr, ptr + nptr));
            construct = false;
        };
        if (owner and ptr != nullptr) std::return_temporary_buffer(ptr);
    };
};
//----------------------------------------------------------------------------
//        End of class spinsort
//----------------------------------------------------------------------------
//
//-------------------------------------------------------------------------
//  function : spinsort
/// @brief constructor of the struct
//
/// @param first : iterator to the first element of the range to sort
/// @param last : iterator after the last element to the range to sort
/// @param comp : object for to compare two elements pointed by Iter_t
///               iterators
/// @param paux : pointer to the auxiliary memory provided. If nullptr, the
///               memory is created inside the class
/// @param naux : number of elements pointed by paux
//------------------------------------------------------------------------
template <class Iter_t, typename Compare>
spinsort <Iter_t, Compare>
::spinsort (Iter_t first, Iter_t last, Compare comp, value_t *paux, size_t naux)
: ptr(paux), nptr(naux), construct(false), owner(false)
{
    range<Iter_t> range_input(first, last);
    assert(range_input.valid());

    size_t nelem = range_input.size();
    owner = construct = false;

    nptr = (nelem + 1) >> 1;
    size_t nelem_1 = nptr;
    size_t nelem_2 = nelem - nelem_1;

    if (nelem <= (Sort_min << 1))
    {
        insert_sort(range_input.first, range_input.last, comp);
        return;
    };

    //------------------- check if sort ---------------------------------
    bool sw = true;
    for (Iter_t it1 = first, it2 = first + 1; it2 != last
         and (sw = not comp(*it2, *it1)); it1 = it2++) ;
    if (sw) return;

    //------------------- check if reverse sort -------------------------
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

    if (ptr == nullptr)
    {
        ptr = std::get_temporary_buffer<value_t>(nptr).first;
        if (ptr == nullptr) throw std::bad_alloc();
        owner = true;
    };
    range_buf range_aux(ptr, (ptr + nptr));

    //---------------------------------------------------------------------
    //                  Process
    //---------------------------------------------------------------------
    uint32_t nlevel = nbits64(((nelem + Sort_min - 1) / Sort_min) - 1) - 1;
    assert(nlevel != 0);

    if ((nlevel & 1) == 1)
    {
        //----------------------------------------------------------------
        // if the number of levels is odd, the data are in the first
        // parameter of range_sort, and the results appear in the second
        // parameter
        //----------------------------------------------------------------
        range_it range_1(first, first + nelem_2), range_2(first + nelem_2,
                        last);
        range_aux = move_construct(range_aux, range_2);
        construct = true;

        range_sort(range_aux, range_2, comp, nlevel);
        range_buf rng_bx(range_aux.first, range_aux.first + nelem_2);

        range_sort(range_1, rng_bx, comp, nlevel);
        merge_half(range_input, rng_bx, range_2, comp);
    }
    else
    {
        //----------------------------------------------------------------
        // If the number of levels is even, the data are in the second
        // parameter of range_sort, and the results are in the same
        //  parameter
        //----------------------------------------------------------------
        range_it range_1(first, first + nelem_1), range_2(first + nelem_1,
                        last);
        range_aux = move_construct(range_aux, range_1);
        construct = true;

        range_sort(range_1, range_aux, comp, nlevel);

        range_1.last = range_1.first + range_2.size();
        range_sort(range_1, range_2, comp, nlevel);
        merge_half(range_input, range_aux, range_2, comp);
    };
};

//****************************************************************************
};//    End namepspace spin_detail
//****************************************************************************
//
namespace bsc = boost::sort::common;
//-----------------------------------------------------------------------------
//  function : spinsort
/// @brief this function implement a single thread stable sort
///
/// @param first : iterator to the first element of the range to sort
/// @param last : iterator after the last element to the range to sort
/// @param comp : object for to compare two elements pointed by Iter_t
///               iterators
//-----------------------------------------------------------------------------
template <class Iter_t, class Compare = compare_iter<Iter_t>>
inline void spinsort (Iter_t first, Iter_t last, Compare comp = Compare())
{
    spin_detail::spinsort <Iter_t, Compare> (first, last, comp);
};

template <class Iter_t, class Compare = compare_iter<Iter_t>>
inline void indirect_spinsort (Iter_t first, Iter_t last,
                               Compare comp = Compare())
{
    typedef typename std::vector<Iter_t>::iterator itx_iter;
    typedef common::less_ptr_no_null <Iter_t, Compare> itx_comp;
    common::indirect_sort (spinsort<itx_iter, itx_comp>, first, last, comp);
};

//****************************************************************************
};//    End namespace sort
};//    End namepspace boost
//****************************************************************************
//
#endif

/* spinsort.hpp
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
*/