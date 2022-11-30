//----------------------------------------------------------------------------
/// @file indirect.hpp
/// @brief Indirect algorithm
///
/// @author Copyright (c) 2016 Francisco Jose Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanying file LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __BOOST_SORT_PARALLEL_COMMON_INDIRECT_HPP
#define __BOOST_SORT_PARALLEL_COMMON_INDIRECT_HPP

//#include <boost/sort/common/atomic.hpp>
#include <boost/sort/common/util/traits.hpp>
#include <functional>
#include <iterator>
#include <type_traits>
#include <vector>

namespace boost
{
namespace sort
{
namespace common
{

//
//---------------------------------------------------------------------------
/// @struct less_ptr_no_null
///
/// @remarks this is the comparison object for pointers. Compare the objects
///          pointed by the iterators
//---------------------------------------------------------------------------
template<class Iter_t, class Compare = util::compare_iter<Iter_t> >
struct less_ptr_no_null
{
    //----------------------------- Variables -----------------------
    Compare comp; // comparison object of the elements pointed by Iter_t

    //------------------------------------------------------------------------
    //  function : less_ptr_no_null
    /// @brief constructor from a Compare object
    /// @param C1 : comparison object
    //-----------------------------------------------------------------------
    less_ptr_no_null(Compare C1 = Compare()): comp(C1) { };

    //------------------------------------------------------------------------
    //  function : operator ( )
    /// @brief Make the comparison of the objects pointed by T1 and T2, using
    //         the internal comp
    //
    /// @param  T1 : first iterator
    /// @param  T2 : second iterator
    /// @return bool result of the comparison
    //-----------------------------------------------------------------------
    bool operator( )(Iter_t T1, Iter_t T2) const
    {
        return comp(*T1, *T2);
    };
};
//
//-----------------------------------------------------------------------------
//  function : create_index
/// @brief From a vector of objects, create a vector of iterators to
///        the objects
///
/// @param first : iterator to the first element of the range
/// @param last : iterator to the element after the last of the range
/// @param index : vector where store the iterators
//-----------------------------------------------------------------------------
template<class Iter_t>
static void create_index(Iter_t first, Iter_t last, std::vector<Iter_t> &index)
{
    auto nelem = last - first;
    assert(nelem >= 0);
    index.clear();
    index.reserve(nelem);
    for (; first != last; ++first) index.push_back(first);
};
//
//-----------------------------------------------------------------------------
//  function : sort_index
/// @brief This function transform a logical sort of the elements in the index
///        in a physical sort
//
/// @param global_first : iterator to the first element of the data
/// @param [in] index : vector of the iterators
//-----------------------------------------------------------------------------
template<class Iter_t>
static void sort_index(Iter_t global_first, std::vector<Iter_t> &index)
{
    typedef util::value_iter<Iter_t> value_t;

    size_t pos_dest = 0;
    size_t pos_src = 0;
    size_t pos_in_vector = 0;
    size_t nelem = index.size();
    Iter_t it_dest, it_src;

    while (pos_in_vector < nelem)
    {
        while (pos_in_vector < nelem and
               (size_t(index[pos_in_vector] - global_first)) == pos_in_vector)
        {
            ++pos_in_vector;
        };

        if (pos_in_vector == nelem) return;
        pos_dest = pos_src = pos_in_vector;
        it_dest = global_first + pos_dest;
        value_t Aux = std::move(*it_dest);

        while ((pos_src = (size_t(index[pos_dest] - global_first)))
               != pos_in_vector)
        {
            index[pos_dest] = it_dest;
            it_src = global_first + pos_src;
            *it_dest = std::move(*it_src);
            it_dest = it_src;
            pos_dest = pos_src;
        };

        *it_dest = std::move(Aux);
        index[pos_dest] = it_dest;
        ++pos_in_vector;
    };
};

template<class func, class Iter_t, class Compare = compare_iter<Iter_t> >
static void indirect_sort(func method, Iter_t first, Iter_t last, Compare comp)
{
    auto nelem = (last - first);
    assert(nelem >= 0);
    if (nelem < 2) return;
    std::vector<Iter_t> index;
    index.reserve((size_t) nelem);
    create_index(first, last, index);
    less_ptr_no_null<Iter_t, Compare> index_comp(comp);
    method(index.begin(), index.end(), index_comp);
    sort_index(first, index);
};

//
//****************************************************************************
};//    End namespace common
};//    End namespace sort
};//    End namespace boost
//****************************************************************************
//
#endif

/* indirect.hpp
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
*/