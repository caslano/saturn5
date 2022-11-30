//----------------------------------------------------------------------------
/// @file sort_basic.hpp
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
#ifndef __BOOST_SORT_COMMON_SORT_BASIC_HPP
#define __BOOST_SORT_COMMON_SORT_BASIC_HPP

//#include <boost/sort/spinsort/util/indirect.hpp>
#include <boost/sort/insert_sort/insert_sort.hpp>
#include <boost/sort/common/util/traits.hpp>
#include <boost/sort/common/range.hpp>
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
namespace common
{

//----------------------------------------------------------------------------
//                USING SENTENCES
//----------------------------------------------------------------------------
using boost::sort::insert_sort;

//-----------------------------------------------------------------------------
//  function : is_stable_sorted_forward
/// @brief examine the elements in the range first, last if they are stable
///        sorted, and return an iterator to the first element not sorted
/// @param first : iterator to the first element in the range
/// @param last : ierator after the last element of the range
/// @param comp : object for to compare two elements
/// @return iterator to the first element not stable sorted. The number of
///         elements sorted is the iterator returned minus first
//-----------------------------------------------------------------------------
template<class Iter_t, class Compare = std::less<value_iter<Iter_t> > >
inline Iter_t is_stable_sorted_forward (Iter_t first, Iter_t last,
                                        Compare comp = Compare())
{
#ifdef __BS_DEBUG
    assert ( (last- first) >= 0);
#endif
    if ((last - first) < 2) return first;
    Iter_t it2 = first + 1;
    for (Iter_t it1 = first; it2 != last and not comp(*it2, *it1); it1 = it2++);
    return it2;
}
//-----------------------------------------------------------------------------
//  function : is_reverse_stable_sorted_forward
/// @brief examine the elements in the range first, last if they are reverse
///        stable sorted, and return an iterator to the first element not
///        reverse stable sorted
/// @param first : iterator to the first element in the range
/// @param last : ierator after the last element of the range
/// @param comp : object for to compare two elements
/// @return iterator to the first element not  reverse stable sorted. The number
///         of elements sorted is the iterator returned minus first
//-----------------------------------------------------------------------------
template<class Iter_t, class Compare = std::less<value_iter<Iter_t> > >
inline Iter_t is_reverse_stable_sorted_forward(Iter_t first, Iter_t last,
                                               Compare comp = Compare())
{
#ifdef __BS_DEBUG
    assert ( (last- first) >= 0);
#endif
    if ((last - first) < 2) return first;
    Iter_t it2 = first + 1;
    for (Iter_t it1 = first; it2 != last and comp(*it2, *it1); it1 = it2++);
    return it2;
};
//-----------------------------------------------------------------------------
//  function : number_stable_sorted_forward
/// @brief examine the elements in the range first, last if they are stable
///        sorted, and return the number of elements sorted
/// @param first : iterator to the first element in the range
/// @param last : ierator after the last element of the range
/// @param comp : object for to compare two elements
/// @param min_process : minimal number of elements to be consideer
/// @return number of element sorted. I f the number is lower than min_process
///         return 0
//-----------------------------------------------------------------------------
template<class Iter_t, class Compare = std::less<value_iter<Iter_t> > >
size_t number_stable_sorted_forward (Iter_t first, Iter_t last,
		                             size_t min_process,
                                     Compare comp = Compare())
{
#ifdef __BS_DEBUG
    assert ( (last- first) >= 0);
#endif
    if ((last - first) < 2) return 0;

    // sorted elements
    Iter_t it2 = first + 1;
    for (Iter_t it1 = first; it2 != last and not comp(*it2, *it1); it1 = it2++);
    size_t nsorted = size_t ( it2 - first);
    if ( nsorted != 1)
    	return (nsorted >= min_process) ? nsorted: 0;

    // reverse sorted elements
    it2 = first + 1;
    for (Iter_t it1 = first; it2 != last and comp(*it2, *it1); it1 = it2++);
    nsorted = size_t ( it2 - first);

    if ( nsorted < min_process) return 0 ;
    util::reverse ( first , it2);
    return nsorted;
};

//-----------------------------------------------------------------------------
//  function : is_stable_sorted_backward
/// @brief examine the elements in the range first, last beginning at end, and
///        if they are stablesorted, and return an iterator to the last element
///        sorted
/// @param first : iterator to the first element in the range
/// @param last : ierator after the last element of the range
/// @param comp : object for to compare two elements
/// @return iterator to the last element stable sorted. The number of
///         elements sorted is the last minus the iterator returned
//-----------------------------------------------------------------------------
template<class Iter_t, class Compare = std::less<value_iter<Iter_t> > >
inline Iter_t is_stable_sorted_backward(Iter_t first, Iter_t last,
                                        Compare comp = Compare())
{
#ifdef __BS_DEBUG
    assert ( (last- first) >= 0);
#endif
    if ((last - first) < 2) return first;
    Iter_t itaux = last - 1;
    while (itaux != first and not comp(*itaux, *(itaux - 1))) {--itaux; };
    return itaux;
}
//-----------------------------------------------------------------------------
//  function : is_reverse_stable_sorted_backward
/// @brief examine the elements in the range first, last beginning at end, and
///        if they are stablesorted, and return an iterator to the last element
///        sorted
/// @param first : iterator to the first element in the range
/// @param last : ierator after the last element of the range
/// @param comp : object for to compare two elements
/// @return iterator to the last element stable sorted. The number of
///         elements sorted is the last minus the iterator returned
//-----------------------------------------------------------------------------
template<class Iter_t, class Compare = std::less<value_iter<Iter_t> > >
inline Iter_t is_reverse_stable_sorted_backward (Iter_t first, Iter_t last,
                                                 Compare comp = Compare())
{
#ifdef __BS_DEBUG
    assert ( (last- first) >= 0);
#endif
    if ((last - first) < 2) return first;
    Iter_t itaux = last - 1;
    for (; itaux != first and comp(*itaux, *(itaux - 1)); --itaux);
    return itaux;
}

//-----------------------------------------------------------------------------
//  function : number_stable_sorted_backward
/// @brief examine the elements in the range first, last if they are stable
///        sorted, and return the number of elements sorted
/// @param first : iterator to the first element in the range
/// @param last : ierator after the last element of the range
/// @param comp : object for to compare two elements
/// @param min_process : minimal number of elements to be consideer
/// @return number of element sorted. I f the number is lower than min_process
///         return 0
//-----------------------------------------------------------------------------
template<class Iter_t, class Compare = std::less<value_iter<Iter_t> > >
size_t number_stable_sorted_backward (Iter_t first, Iter_t last,
		                             size_t min_process,
                                     Compare comp = Compare())
{
#ifdef __BS_DEBUG
    assert ( (last- first) >= 0);
#endif
    if ((last - first) < 2) return 0;
    Iter_t itaux = last - 1;
    while (itaux != first and not comp(*itaux, *(itaux - 1))) {--itaux; };
    size_t nsorted = size_t ( last - itaux);
    if ( nsorted != 1)
    	return ( nsorted >= min_process)?nsorted: 0 ;

    itaux = last - 1;
    for (; itaux != first and comp(*itaux, *(itaux - 1)); --itaux);
    nsorted = size_t ( last - itaux);
    if ( nsorted < min_process) return 0 ;
    util::reverse ( itaux, last );
    return nsorted;
}
//-----------------------------------------------------------------------------
//  function : internal_sort
/// @brief this function divide r_input in two parts, sort it,and merge moving
///        the elements to range_buf
/// @param range_input : range with the elements to sort
/// @param range_buffer : range with the elements sorted
/// @param comp : object for to compare two elements
/// @param level : when is 1, sort with the insertionsort algorithm
///                if not make a recursive call splitting the ranges
//
//-----------------------------------------------------------------------------
template <class Iter1_t, class Iter2_t, class Compare>
inline void internal_sort (const range<Iter1_t> &rng1,
		                   const range<Iter2_t> &rng2,
                           Compare comp, uint32_t level, bool even = true)
{
    //-----------------------------------------------------------------------
    //                  metaprogram
    //-----------------------------------------------------------------------
    typedef value_iter<Iter1_t> value_t;
    typedef value_iter<Iter2_t> value2_t;
    static_assert (std::is_same< value_t, value2_t>::value,
                    "Incompatible iterators\n");

    //-----------------------------------------------------------------------
    //                  program
    //-----------------------------------------------------------------------
#ifdef __BS_DEBUG
    assert (rng1.size ( ) == rng2.size ( ) );
#endif
    size_t nelem = (rng1.size() + 1) >> 1;

    range<Iter1_t> rng1_left(rng1.first, rng1.first + nelem), 
                   rng1_right(rng1.first + nelem, rng1.last);

    range<Iter2_t> rng2_left(rng2.first, rng2.first + nelem), 
                   rng2_right(rng2.first + nelem, rng2.last);

    if (nelem <= 32 and (level & 1) == even)
    {
        insert_sort(rng1_left.first, rng1_left.last, comp);
        insert_sort(rng1_right.first, rng1_right.last, comp);
    }
    else
    {
        internal_sort(rng2_left, rng1_left, comp, level + 1, even);
        internal_sort(rng2_right, rng1_right, comp, level + 1, even);
    };
    merge(rng2, rng1_left, rng1_right, comp);
};
//-----------------------------------------------------------------------------
//  function : range_sort_data
/// @brief this sort elements using the range_sort function and receiving a
///        buffer of initialized memory
/// @param rng_data : range with the elements to sort
/// @param rng_aux : range of at least the same memory than rng_data used as
///                  auxiliary memory in the sorting
/// @param comp : object for to compare two elements
//-----------------------------------------------------------------------------
template<class Iter1_t, class Iter2_t, class Compare>
static void range_sort_data (const range<Iter1_t> & rng_data,
                             const range<Iter2_t> & rng_aux, Compare comp)
{
    //-----------------------------------------------------------------------
    //                  metaprogram
    //-----------------------------------------------------------------------
    typedef value_iter<Iter1_t> value_t;
    typedef value_iter<Iter2_t> value2_t;
    static_assert (std::is_same< value_t, value2_t>::value,
                    "Incompatible iterators\n");

    //------------------------------------------------------------------------
    //                    program
    //------------------------------------------------------------------------
#ifdef __BS_DEBUG
    assert ( rng_data.size() == rng_aux.size());
#endif
    // minimal number of element before to jump to insertionsort
    const uint32_t sort_min = 32;
    if (rng_data.size() <= sort_min)
    {
        insert_sort(rng_data.first, rng_data.last, comp);
        return;
    };

    internal_sort(rng_aux, rng_data, comp, 0, true);
};
//-----------------------------------------------------------------------------
//  function : range_sort_buffer
/// @brief this sort elements using the range_sort function and receiving a
///        buffer of initialized memory
/// @param rng_data : range with the elements to sort
/// @param rng_aux : range of at least the same memory than rng_data used as
///                  auxiliary memory in the sorting
/// @param comp : object for to compare two elements
//-----------------------------------------------------------------------------
template<class Iter1_t, class Iter2_t, class Compare>
static void range_sort_buffer(const range<Iter1_t> & rng_data,
                              const range<Iter2_t> & rng_aux, Compare comp)
{
    //-----------------------------------------------------------------------
    //                  metaprogram
    //-----------------------------------------------------------------------
    typedef value_iter<Iter1_t> value_t;
    typedef value_iter<Iter2_t> value2_t;
    static_assert (std::is_same< value_t, value2_t>::value,
                    "Incompatible iterators\n");

    //------------------------------------------------------------------------
    //                    program
    //------------------------------------------------------------------------
#ifdef __BS_DEBUG
    assert ( rng_data.size() == rng_aux.size());
#endif
    // minimal number of element before to jump to insertionsort
    const uint32_t sort_min = 32;
    if (rng_data.size() <= sort_min)
    {
        insert_sort(rng_data.first, rng_data.last, comp);
        move_forward(rng_aux, rng_data);
        return;
    };

    internal_sort(rng_data, rng_aux, comp, 0, false);
};
//****************************************************************************
};//    End namespace common
};//    End namespace sort
};//    End namepspace boost
//****************************************************************************
//
#endif

/* sort_basic.hpp
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
*/