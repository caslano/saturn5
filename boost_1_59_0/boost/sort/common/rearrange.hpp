//----------------------------------------------------------------------------
/// @file rearrange.hpp
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
#ifndef __BOOST_SORT_COMMON_REARRANGE_HPP
#define __BOOST_SORT_COMMON_REARRANGE_HPP

//#include <boost/sort/common/atomic.hpp>
#include <boost/sort/common/util/traits.hpp>
#include <functional>
#include <iterator>
#include <type_traits>
#include <vector>
#include <cassert>

namespace boost
{
namespace sort
{
namespace common
{

template<class Iter_data>
struct filter_iterator
{
    //-----------------------------------------------------------------------
    //                   Variables
    //-----------------------------------------------------------------------
    Iter_data origin;

    //-----------------------------------------------------------------------
    //                   Functions
    //-----------------------------------------------------------------------
    filter_iterator(Iter_data global_first): origin(global_first) { };
    size_t operator ()(Iter_data itx) const
    {
        return size_t(itx - origin);
    }
};

struct filter_pos
{
    size_t operator ()(size_t pos) const {  return pos; };
};

//
//-----------------------------------------------------------------------------
//  function : rearrange
/// @brief This function transform a logical sort of the elements in the index  
///        of iterators in a physical sort. 
//
/// @param global_first : iterator to the first element of the data
/// @param [in] index : vector of the iterators
//-----------------------------------------------------------------------------
template<class Iter_data, class Iter_index, class Filter_pos>
void rearrange(Iter_data global_first, Iter_index itx_first,
               Iter_index itx_last, Filter_pos pos)
{
    //-----------------------------------------------------------------------
    //                    Metaprogramming
    //-----------------------------------------------------------------------
    typedef util::value_iter<Iter_data>     value_data;
    typedef util::value_iter<Iter_index>    value_index;

    //-------------------------------------------------------------------------
    //                     Code
    //-------------------------------------------------------------------------	
    assert((itx_last - itx_first) >= 0);
    size_t pos_dest, pos_src, pos_ini;
    size_t nelem = size_t(itx_last - itx_first);
    Iter_data data = global_first;
    Iter_index index = itx_first;

    pos_ini = 0;
    while (pos_ini < nelem)
    {
        while (pos_ini < nelem and pos(index[pos_ini]) == pos_ini)
            ++pos_ini;
        if (pos_ini == nelem) return;
        pos_dest = pos_src = pos_ini;
        value_data aux = std::move(data[pos_ini]);
        value_index itx_src = std::move(index[pos_ini]);

        while ((pos_src = pos(itx_src)) != pos_ini)
        {
            data[pos_dest] = std::move(data[pos_src]);
            std::swap(itx_src, index[pos_src]);
            pos_dest = pos_src;
        };

        data[pos_dest] = std::move(aux);
        index[pos_ini] = std::move(itx_src);
        ++pos_ini;
    };
};

/*
 //
 //-----------------------------------------------------------------------------
 //  function : rearrange_pos
 /// @brief This function transform a logical sort of the elements in the index  
 ///        of iterators in a physical sort. 
 //
 /// @param global_first : iterator to the first element of the data
 /// @param [in] index : vector of the iterators
 //-----------------------------------------------------------------------------
 template < class Iter_t, class Number >
 void rearrange_pos (Iter_t global_first, std::vector< Number> &index)
 {	
 //-------------------------------------------------------------------------
 //          METAPROGRAMMING AND DEFINITIONS
 //-------------------------------------------------------------------------
 static_assert ( std::is_integral<Number>::value, "Incompatible Types");
 typedef iter_value< Iter_t > value_t;

 //-------------------------------------------------------------------------
 //                     CODE
 //-------------------------------------------------------------------------
 size_t pos_dest = 0;
 size_t pos_src = 0;
 size_t pos_ini = 0;
 size_t nelem = index.size ( );
 Iter_t it_dest (global_first), it_src(global_first);

 while (pos_ini < nelem)
 {
 while (pos_ini < nelem and
 index[pos_ini] == pos_ini)
 {
 ++pos_ini;
 };

 if (pos_ini == nelem) return;
 pos_dest = pos_src = pos_ini;
 it_dest = global_first + pos_dest;
 value_t Aux = std::move (*it_dest);

 while ((pos_src = index[pos_dest]) != pos_ini)
 {
 index[pos_dest] = it_dest - global_first;
 it_src = global_first + pos_src;
 *it_dest = std::move (*it_src);
 it_dest = it_src;
 pos_dest = pos_src;
 };

 *it_dest = std::move (Aux);
 index[pos_dest] = it_dest - global_first;
 ++pos_ini;
 };
 };
 */
//
//****************************************************************************
};//    End namespace common
};//    End namespace sort
};//    End namespace boost
//****************************************************************************
//
#endif

/* rearrange.hpp
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
*/