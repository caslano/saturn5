//----------------------------------------------------------------------------
/// @file merge_vector.hpp
/// @brief In this file have the functions for to do a stable merge of
//         ranges, in a vector
///
/// @author Copyright (c) 2016 Francisco Jose Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanying file LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __BOOST_SORT_PARALLEL_DETAIL_UTIL_MERGE_VECTOR_HPP
#define __BOOST_SORT_PARALLEL_DETAIL_UTIL_MERGE_VECTOR_HPP

#include <boost/sort/common/merge_four.hpp>
#include <functional>
#include <iterator>
#include <memory>
#include <type_traits>
#include <vector>

namespace boost
{
namespace sort
{
namespace common
{

//############################################################################
//                                                                          ##
//                       F U S I O N     O F                                ##
//                                                                          ##
//              A  V E C T O R   O F    R A N G E S                         ##
//                                                                          ##
//############################################################################

//
//-----------------------------------------------------------------------------
//  function : merge_level4
/// @brief merge the ranges in the vector v_input with the full_merge4 function.
///        The v_output vector is used as auxiliary memory in the internal
///        process. The final results is in the dest range.
///        All the ranges of v_output are inside the range dest
/// @param dest : range where move the elements merged
/// @param v_input : vector of ranges to merge
/// @param v_output : vector of ranges obtained
/// @param comp : comparison object
/// @return range with all the elements moved
//-----------------------------------------------------------------------------
template<class Iter1_t, class Iter2_t, class Compare>
void merge_level4(range<Iter1_t> dest, std::vector<range<Iter2_t> > &v_input,
                  std::vector<range<Iter1_t> > &v_output, Compare comp)
{
    typedef range<Iter1_t> range1_t;
    typedef util::value_iter<Iter1_t> type1;
    typedef util::value_iter<Iter2_t> type2;
    static_assert (std::is_same< type1, type2 >::value,
                    "Incompatible iterators\n");

    v_output.clear();
    if (v_input.size() == 0) return;
    if (v_input.size() == 1)
    {
        v_output.emplace_back(move_forward(dest, v_input[0]));
        return;
    };

    uint32_t nrange = v_input.size();
    uint32_t pos_ini = 0;
    while (pos_ini < v_input.size())
    {
        uint32_t nmerge = (nrange + 3) >> 2;
        uint32_t nelem = (nrange + nmerge - 1) / nmerge;
        range1_t rz = full_merge4(dest, &v_input[pos_ini], nelem, comp);
        v_output.emplace_back(rz);
        dest.first = rz.last;
        pos_ini += nelem;
        nrange -= nelem;
    };
    return;
};
//
//-----------------------------------------------------------------------------
//  function : uninit_merge_level4
/// @brief merge the ranges moving the objects and constructing them in
///        uninitialized memory, in the vector v_input
///        using full_merge4. The v_output vector is used as auxiliary memory
///        in the internal process. The final results is in the dest range.
///        All the ranges of v_output are inside the range dest
///
/// @param dest : range where move the elements merged
/// @param v_input : vector of ranges to merge
/// @param v_output : vector of ranges obtained
/// @param comp : comparison object
/// @return range with all the elements moved and constructed
//-----------------------------------------------------------------------------
template<class Value_t, class Iter_t, class Compare>
void uninit_merge_level4(range<Value_t *> dest,
                         std::vector<range<Iter_t> > &v_input,
                         std::vector<range<Value_t *> > &v_output, Compare comp)
{
    typedef range<Value_t *> range1_t;
    typedef util::value_iter<Iter_t> type1;
    static_assert (std::is_same< type1, Value_t >::value,
                    "Incompatible iterators\n");

    v_output.clear();
    if (v_input.size() == 0) return;
    if (v_input.size() == 1)
    {
        v_output.emplace_back(move_construct(dest, v_input[0]));
        return;
    };

    uint32_t nrange = v_input.size();
    uint32_t pos_ini = 0;
    while (pos_ini < v_input.size())
    {
        uint32_t nmerge = (nrange + 3) >> 2;
        uint32_t nelem = (nrange + nmerge - 1) / nmerge;
        range1_t rz = uninit_full_merge4(dest, &v_input[pos_ini], nelem, comp);
        v_output.emplace_back(rz);
        dest.first = rz.last;
        pos_ini += nelem;
        nrange -= nelem;
    };
    return;
};
//
//-----------------------------------------------------------------------------
//  function : merge_vector4
/// @brief merge the ranges in the vector v_input using the merge_level4
///        function. The v_output vector is used as auxiliary memory in the
///        internal process
///        The final results is in the range_output range.
///        All the ranges of v_output are inside the range range_output
///        All the ranges of v_input are inside the range range_input
/// @param range_input : range including all the ranges of v_input
/// @param ange_output : range including all the elements of v_output
/// @param v_input : vector of ranges to merge
/// @param v_output : vector of ranges obtained
/// @param comp : comparison object
/// @return range with all the elements moved
//-----------------------------------------------------------------------------
template<class Iter1_t, class Iter2_t, class Compare>
range<Iter2_t> merge_vector4(range<Iter1_t> range_input,
                             range<Iter2_t> range_output,
                             std::vector<range<Iter1_t> > &v_input,
                             std::vector<range<Iter2_t> > &v_output,
                             Compare comp)
{
    typedef range<Iter2_t> range2_t;
    typedef util::value_iter<Iter1_t> type1;
    typedef util::value_iter<Iter2_t> type2;
    static_assert (std::is_same< type1, type2 >::value,
                    "Incompatible iterators\n");

    v_output.clear();
    if (v_input.size() == 0)
    {
        return range2_t(range_output.first, range_output.first);
    };
    if (v_input.size() == 1)
    {
        return move_forward(range_output, v_input[0]);
    };
    bool sw = false;
    uint32_t nrange = v_input.size();

    while (nrange > 1)
    {
        if (sw)
        {
            merge_level4(range_input, v_output, v_input, comp);
            sw = false;
            nrange = v_input.size();
        }
        else
        {
            merge_level4(range_output, v_input, v_output, comp);
            sw = true;
            nrange = v_output.size();
        };
    };
    return (sw) ? v_output[0] : move_forward(range_output, v_input[0]);
};

//****************************************************************************
};//    End namespace common
};//    End namespace sort
};//    End namespace boost
//****************************************************************************
//
#endif

/* merge_vector.hpp
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
*/