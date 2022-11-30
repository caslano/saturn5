//----------------------------------------------------------------------------
/// @file insert.hpp
/// @brief
///
/// @author Copyright (c) 2016 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanying file LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __BOOST_SORT_COMMON_UTIL_INSERT_HPP
#define __BOOST_SORT_COMMON_UTIL_INSERT_HPP

//#include <boost/sort/spinsort/util/indirect.hpp>
#include <boost/sort/common/util/insert.hpp>
#include <boost/sort/common/util/traits.hpp>
#include <boost/sort/common/util/algorithm.hpp>
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
namespace util
{
namespace here = boost::sort::common::util;
//
//############################################################################
//
//          D E F I N I T I O N S    O F    F U N C T I O N S
//    
// template < class Iter1_t, class Iter2_t, typename Compare>
// void insert_sorted (Iter1_t first, Iter1_t mid, Iter1_t last,
//                     Compare comp, Iter2_t  it_aux)
//
//############################################################################
//
//-----------------------------------------------------------------------------
//  function : insert_sorted
/// @brief : Insertion sort of elements sorted
/// @param first: iterator to the first element of the range
/// @param mid : last pointer of the sorted data, and first pointer to the
///               elements to insert
/// @param last : iterator to the next element of the last in the range
/// @param comp :
/// @comments : the two ranges are sorted and in it_aux there is spave for 
///             to store temporally the elements to insert
//-----------------------------------------------------------------------------
template<class Iter1_t, class Iter2_t, typename Compare>
static void insert_sorted(Iter1_t first, Iter1_t mid, Iter1_t last,
                          Compare comp, Iter2_t it_aux)
{
    //------------------------------------------------------------------------
    //                 metaprogram
    //------------------------------------------------------------------------
    typedef value_iter<Iter1_t> value_t;
    typedef value_iter<Iter2_t> value2_t;
    static_assert (std::is_same< value_t, value2_t>::value,
                    "Incompatible iterators\n");

    //--------------------------------------------------------------------
    //                   program
    //--------------------------------------------------------------------
    if (mid == last) return;
    if (first == mid) return;

    //------------------------------------------------------------------------
    // creation of the vector of elements to insert and their position in the
    // sorted part
    // the data are inserted in it_aux
    //-----------------------------------------------------------------------
    move_forward(it_aux, mid, last);

    // search of the iterators where insert the new elements
    size_t ndata = last - mid;
    Iter1_t mv_first = mid, mv_last = mid;

    for (size_t i = ndata; i > 0; --i)
    {
        mv_last = mv_first;
        mv_first = std::upper_bound(first, mv_last, it_aux[i - 1], comp);
        Iter1_t it1 = here::move_backward(mv_last + i, mv_first, mv_last);
        *(it1 - 1) = std::move(it_aux[i - 1]);
    };
};

template<class Iter1_t, class Iter2_t, typename Compare>
static void insert_sorted_backward(Iter1_t first, Iter1_t mid, Iter1_t last,
                                   Compare comp, Iter2_t it_aux)
{
    //------------------------------------------------------------------------
    //                 metaprogram
    //------------------------------------------------------------------------
    typedef value_iter<Iter1_t> value_t;
    typedef value_iter<Iter2_t> value2_t;
    static_assert (std::is_same< value_t, value2_t>::value,
                    "Incompatible iterators\n");

    //--------------------------------------------------------------------
    //                   program
    //--------------------------------------------------------------------
    if (mid == last) return;
    if (first == mid) return;
    //------------------------------------------------------------------------
    // creation of the vector of elements to insert and their position in the
    // sorted part
    // the data are inserted in it_aux
    //-----------------------------------------------------------------------
    move_forward(it_aux, first, mid);

    // search of the iterators where insert the new elements
    size_t ndata = mid - first;
    Iter1_t mv_first = mid, mv_last = mid;

    for (size_t i = 0; i < ndata; ++i)
    {
        mv_first = mv_last;
        mv_last = std::lower_bound(mv_first, last, it_aux[i], comp);
        Iter1_t it1 = move_forward(mv_first - (ndata - i), mv_first, mv_last);
        *(it1) = std::move(it_aux[i]);
    };

};
//
//****************************************************************************
};//    End namespace util
};//    End namepspace common
};//    End namespace sort
};//    End namepspace boost
//****************************************************************************
//
#endif

/* insert.hpp
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
*/