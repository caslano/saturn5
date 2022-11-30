//----------------------------------------------------------------------------
/// @file insert_sort.hpp
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
#ifndef __BOOST_SORT_INTROSORT_DETAIL_INSERT_SORT_HPP
#define __BOOST_SORT_INTROSORT_DETAIL_INSERT_SORT_HPP

#include <functional>
#include <iterator>
#include <algorithm>
#include <utility> // std::swap
#include <boost/sort/common/util/traits.hpp>
#include <boost/sort/common/util/insert.hpp>

namespace boost
{
namespace sort
{
using common::util::compare_iter;
using common::util::value_iter;
//
//-----------------------------------------------------------------------------
//  function : insert_sort
/// @brief : Insertion sort algorithm
/// @param first: iterator to the first element of the range
/// @param last : iterator to the next element of the last in the range
/// @param comp : object for to do the comparison between the elements
/// @remarks This algorithm is O(N^2)
//-----------------------------------------------------------------------------
template < class Iter_t, typename Compare = compare_iter < Iter_t > >
static void insert_sort (Iter_t first, Iter_t last,
                         Compare comp = Compare())
{
    //--------------------------------------------------------------------
    //                   DEFINITIONS
    //--------------------------------------------------------------------
    typedef value_iter< Iter_t > value_t;

    if ((last - first) < 2) return;

    for (Iter_t it_examine = first + 1; it_examine != last; ++it_examine)
    {
        value_t Aux = std::move (*it_examine);
        Iter_t it_insertion = it_examine;

        while (it_insertion != first and comp (Aux, *(it_insertion - 1)))
        {
            *it_insertion = std::move (*(it_insertion - 1));
            --it_insertion;
        };
        *it_insertion = std::move (Aux);
    };
};

/*
//
//-----------------------------------------------------------------------------
//  function : insert_partial_sort
/// @brief : Insertion sort of elements sorted
/// @param first: iterator to the first element of the range
/// @param mid : last pointer of the sorted data, and first pointer to the
///               elements to insert
/// @param last : iterator to the next element of the last in the range
/// @param comp : object for to do the comparison between the elements
/// @remarks This algorithm is O(N^2)
//-----------------------------------------------------------------------------
template < class Iter_t, typename Compare = compare_iter < Iter_t > >
void insert_partial_sort (Iter_t first, Iter_t mid, Iter_t last,
                          Compare comp = Compare())
{
    //--------------------------------------------------------------------
    //                   DEFINITIONS
    //--------------------------------------------------------------------
    typedef value_iter< Iter_t > value_t;

    if ( mid == last ) return ;
    insert_sort ( mid, last, comp);
    if (first == mid) return ;

    // creation of the vector of elements to insert and their position in the
    // sorted part
    std::vector<Iter_t> viter ;
    std::vector<value_t> vdata ;

    for ( Iter_t alpha = mid ; alpha != last ; ++alpha)
        vdata.push_back ( std::move ( *alpha));

    Iter_t linf = first , lsup = mid ;
    for ( uint32_t i= 0 ; i < vdata.size() ; ++i)
    {   Iter_t it1 = std::upper_bound ( linf, lsup , vdata[i], comp);
        viter.push_back ( it1 );
        linf = it1 ;
    };

    // moving the elements
    viter.push_back ( mid) ;
    for ( uint32_t i = viter.size() -1 ; i!= 0 ; --i)
    {   Iter_t src = viter[i], limit = viter[i-1];
        Iter_t dest = src + ( i);
        while ( src != limit) * (--dest) = std::move ( *(--src));
        *(viter[i-1] + (i -1)) = std::move (vdata[i-1]);
    };
}
*/
//
//****************************************************************************
}; //    End namespace sort
}; //    End namespace boost
//****************************************************************************
//
#endif

/* insert_sort.hpp
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
*/