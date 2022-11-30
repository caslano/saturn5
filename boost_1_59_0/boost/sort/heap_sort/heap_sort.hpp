//----------------------------------------------------------------------------
/// @file heap_sort.hpp
/// @brief Insertion Sort algorithm
///
/// @author Copyright (c) 2016 Francisco Jose Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanying file LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __BOOST_SORT_INTROSORT_DETAIL_HEAP_SORT_HPP
#define __BOOST_SORT_INTROSORT_DETAIL_HEAP_SORT_HPP

#include <cassert>
#include <cstdint>
#include <iterator>
#include <stdexcept>
#include <utility> // for std::swap
#include <boost/sort/common/util/traits.hpp>

namespace boost
{
namespace sort
{
namespace heap_detail
{
namespace bscu = boost::sort::common::util;
//
//---------------------------------------------------------------------------
//  struct : heap_sort
/// @brief : Heap sort algorithm
/// @remarks This algorithm is O(NLogN)
//---------------------------------------------------------------------------
template < class Iter_t, class Compare >
struct heap_sort
{
    typedef bscu::value_iter<Iter_t> value_t;

    //
    //------------------------------------------------------------------------
    //  function : sort3
    /// @brief Sort and signal the changes of three values
    /// @param val_0 : first value to compare
    /// @param val_1 : second value to compare
    /// @param val_2 : third value to compare
    /// @param [out] bool_0 : if true indicates val_0 had been changed
    /// @param [out] bool_1 : if true indicates val_1 had been changed
    /// @param [out] bool_2 : if true indicates val_2 had been changed
    /// @return if true , some value had changed
    /// @remarks
    //------------------------------------------------------------------------
    bool sort3 (value_t &val_0, value_t &val_1, value_t &val_2, bool &bool_0,
                bool &bool_1, bool &bool_2)
    {
        bool_0 = bool_1 = bool_2 = false;
        int value = 0;
        if (val_0 < val_1) value += 4;
        if (val_1 < val_2) value += 2;
        if (val_0 < val_2) value += 1;

        switch (value)
        {
            case 0: break;

            case 2:
                std::swap (val_1, val_2);
                bool_1 = bool_2 = true;
                break;

            case 3:
                if (not(val_0 > val_1)) {
                    std::swap (val_0, val_2);
                    bool_0 = bool_2 = true;
                }
                else
                {
                    auto aux = std::move (val_2);
                    val_2 = std::move (val_1);
                    val_1 = std::move (val_0);
                    val_0 = std::move (aux);
                    bool_0 = bool_1 = bool_2 = true;
                };
                break;

            case 4:
                std::swap (val_0, val_1);
                bool_0 = bool_1 = true;
                break;

            case 5:
                if (val_1 > val_2) {
                    auto aux = std::move (val_0);
                    val_0 = std::move (val_1);
                    val_1 = std::move (val_2);
                    val_2 = std::move (aux);
                    bool_0 = bool_1 = bool_2 = true;
                }
                else
                {
                    std::swap (val_0, val_2);
                    bool_0 = bool_2 = true;
                };
                break;

            case 7:
                std::swap (val_0, val_2);
                bool_0 = bool_2 = true;
                break;

            default: abort ( );
        };
        return (bool_0 or bool_1 or bool_2);
    };
    //
    //-----------------------------------------------------------------------
    //  function : make_heap
    /// @brief Make the heap for to extract the sorted elements
    /// @param first : iterator to the first element of the range
    /// @param nelem : number of lements of the range
    /// @param comp : object for to compare two elements
    /// @remarks This algorithm is O(NLogN)
    //------------------------------------------------------------------------
    void make_heap (Iter_t first, size_t nelem, Compare comp)
    {
        size_t pos_father, pos_son;
        Iter_t iter_father = first, iter_son = first;
        bool sw = false;

        for (size_t i = 1; i < nelem; ++i)
        {
            pos_father = i;
            iter_father = first + i;
            sw = false;
            do
            {
                iter_son = iter_father;
                pos_son = pos_father;
                pos_father = (pos_son - 1) >> 1;
                iter_father = first + pos_father;
                if ((sw = comp (*iter_father, *iter_son)))
                    std::swap (*iter_father, *iter_son);
            } while (sw and pos_father != 0);
        };
    };
    //
    //------------------------------------------------------------------------
    //  function : heap_sort
    /// @brief : Heap sort algorithm
    /// @param first: iterator to the first element of the range
    /// @param last : iterator to the next element of the last in the range
    /// @param comp : object for to do the comparison between the elements
    /// @remarks This algorithm is O(NLogN)
    //------------------------------------------------------------------------
    heap_sort (Iter_t first, Iter_t last, Compare comp)
    {
        assert ((last - first) >= 0);
        size_t nelem = last - first;
        if (nelem < 2) return;

        //--------------------------------------------------------------------
        // Creating the initial heap
        //--------------------------------------------------------------------
        make_heap (first, nelem, comp);

        //--------------------------------------------------------------------
        //  Sort the heap
        //--------------------------------------------------------------------
        size_t pos_father, pos_son;
        Iter_t iter_father = first, iter_son = first;

        bool sw = false;
        for (size_t i = 1; i < nelem; ++i)
        {
            std::swap (*first, *(first + (nelem - i)));
            pos_father = 0;
            pos_son = 1;
            iter_father = first;
            sw = true;
            while (sw and pos_son < (nelem - i))
            {
                // if the father have two sons must select the bigger
                iter_son = first + pos_son;
                if ((pos_son + 1) < (nelem - i) and
                    comp (*iter_son, *(iter_son + 1)))
                {
                    ++pos_son;
                    ++iter_son;
                };
                if ((sw = comp (*iter_father, *iter_son)))
                    std::swap (*iter_father, *iter_son);
                pos_father = pos_son;
                iter_father = iter_son;
                pos_son = (pos_father << 1) + 1;
            };
        };
    };
}; // End class heap_sort
}; // end namespace heap_sort

namespace bscu = boost::sort::common::util;

template < class Iter_t, typename Compare = bscu::compare_iter < Iter_t > >
void heap_sort (Iter_t first, Iter_t last, Compare comp = Compare())
{
	heap_detail::heap_sort<Iter_t, Compare> ( first, last, comp);
}
//
//****************************************************************************
}; //    End namespace sort
}; //    End namespace boost
//****************************************************************************
//
#endif

/* heap_sort.hpp
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
*/