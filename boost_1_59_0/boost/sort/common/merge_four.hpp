//----------------------------------------------------------------------------
/// @file merge_four.hpp
/// @brief This file have the functions for to merge 4 buffers
///
/// @author Copyright (c) 2016 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanying file LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __BOOST_SORT_PARALLEL_DETAIL_UTIL_MERGE_FOUR_HPP
#define __BOOST_SORT_PARALLEL_DETAIL_UTIL_MERGE_FOUR_HPP

#include <boost/sort/common/util/traits.hpp>
#include <boost/sort/common/range.hpp>
#include <functional>
#include <iterator>
#include <memory>
#include <vector>

namespace boost
{
namespace sort
{
namespace common
{

//
//############################################################################
//                                                                          ##
//                       F U S I O N     O F                                ##
//                                                                          ##
//              F O U R     E L E M E N T S    R A N G E                    ##
//                                                                          ##
//############################################################################
//

//-----------------------------------------------------------------------------
//  function : less_range
/// @brief Compare the elements pointed by it1 and it2, and if they
///        are equals, compare their position, doing a stable comparison
///
/// @param it1 : iterator to the first element
/// @param pos1 : position of the object pointed by it1
/// @param it2 : iterator to the second element
/// @param pos2 : position of the element pointed by it2
/// @param comp : comparison object
/// @return result of the comparison
//-----------------------------------------------------------------------------
template<class Iter_t, class Compare = typename util::compare_iter<Iter_t> >
inline bool less_range(Iter_t it1, uint32_t pos1, Iter_t it2, uint32_t pos2,
                       Compare comp = Compare())
{
    return (comp(*it1, *it2)) ? true :
           (pos2 < pos1) ? false : not (comp(*it2, *it1));
};

//-----------------------------------------------------------------------------
//  function : full_merge4
/// @brief Merge four ranges
///
/// @param dest: range where move the elements merged. Their size must be
///              greater or equal than the sum of the sizes of the ranges
///              in vrange_input
/// @param vrange_input : array of ranges to merge
/// @param nrange_input : number of ranges in vrange_input
/// @param comp : comparison object
/// @return range with all the elements moved with the size adjusted
//-----------------------------------------------------------------------------
template<class Iter1_t, class Iter2_t, class Compare>
range<Iter1_t> full_merge4(const range<Iter1_t> &rdest,
                           range<Iter2_t> vrange_input[4],
                           uint32_t nrange_input, Compare comp)
{
    typedef range<Iter1_t> range1_t;
    typedef util::value_iter<Iter1_t> type1;
    typedef util::value_iter<Iter2_t> type2;
    static_assert (std::is_same< type1, type2 >::value,
                    "Incompatible iterators\n");

    size_t ndest = 0;
    uint32_t i = 0;
    while (i < nrange_input)
    {
        if (vrange_input[i].size() != 0)
        {
            ndest += vrange_input[i++].size();
        }
        else
        {
            for (uint32_t k = i + 1; k < nrange_input; ++k)
            {
                vrange_input[k - 1] = vrange_input[k];
            };
            --nrange_input;
        };
    };

    if (nrange_input == 0) return range1_t(rdest.first, rdest.first);
    if (nrange_input == 1) return move_forward(rdest, vrange_input[0]);
    if (nrange_input == 2)
    {
        return merge(rdest, vrange_input[0], vrange_input[1], comp);
    };

    //------------------------------------------------------------------------
    // Initial sort
    //------------------------------------------------------------------------
    uint32_t pos[4] =
    { 0, 1, 2, 3 }, npos = nrange_input;

    //-----------------------------------------------------------------------
    // thanks to Steven Ross by their suggestion about the optimal
    // sorting networks
    //-----------------------------------------------------------------------
    if (less_range(vrange_input[pos[1]].first, pos[1],
                    vrange_input[pos[0]].first, pos[0], comp))
    {
        std::swap(pos[0], pos[1]);
    };
    if (npos == 4 and less_range(vrange_input[pos[3]].first, pos[3],
                                 vrange_input[pos[2]].first, pos[2], comp))
    {
        std::swap(pos[3], pos[2]);
    };
    if (less_range (vrange_input[pos[2]].first, pos[2],
                    vrange_input[pos[0]].first, pos[0], comp))
    {
        std::swap(pos[0], pos[2]);
    };
    if (npos == 4
                    and less_range (vrange_input[pos[3]].first, pos[3],
                                    vrange_input[pos[1]].first, pos[1], comp))
    {
        std::swap(pos[1], pos[3]);
    };
    if (less_range (vrange_input[pos[2]].first, pos[2],
                    vrange_input[pos[1]].first, pos[1], comp))
    {
        std::swap(pos[1], pos[2]);
    };

    Iter1_t it_dest = rdest.first;
    while (npos > 2)
    {
        *(it_dest++) = std::move(*(vrange_input[pos[0]].first++));
        if (vrange_input[pos[0]].size() == 0)
        {
            pos[0] = pos[1];
            pos[1] = pos[2];
            pos[2] = pos[3];
            --npos;
        }
        else
        {
            if (less_range(vrange_input[pos[1]].first, pos[1],
                            vrange_input[pos[0]].first, pos[0], comp))
            {
                std::swap(pos[0], pos[1]);
                if (less_range(vrange_input[pos[2]].first, pos[2],
                                vrange_input[pos[1]].first, pos[1], comp))
                {
                    std::swap(pos[1], pos[2]);
                    if (npos == 4
                                    and less_range(vrange_input[pos[3]].first,
                                                    pos[3],
                                                    vrange_input[pos[2]].first,
                                                    pos[2], comp))
                    {
                        std::swap(pos[2], pos[3]);
                    };
                };
            };
        };
    };

    range1_t raux1(rdest.first, it_dest), raux2(it_dest, rdest.last);
    if (pos[0] < pos[1])
    {
        return concat(raux1,merge(raux2, vrange_input[pos[0]], 
                                  vrange_input[pos[1]], comp));
    }
    else
    {
        return concat(raux1, merge (raux2, vrange_input[pos[1]], 
                                    vrange_input[pos[0]], comp));
    };
};

//-----------------------------------------------------------------------------
//  function : uninit_full_merge4
/// @brief Merge four ranges and put the result in uninitialized memory
///
/// @param dest: range where create and move the elements merged. Their
///              size must be greater or equal than the sum of the sizes
///              of the ranges in the array R
/// @param vrange_input : array of ranges to merge
/// @param nrange_input : number of ranges in vrange_input
/// @param comp : comparison object
/// @return range with all the elements move with the size adjusted
//-----------------------------------------------------------------------------
template<class Value_t, class Iter_t, class Compare>
range<Value_t *> uninit_full_merge4(const range<Value_t *> &dest,
                                    range<Iter_t> vrange_input[4],
                                    uint32_t nrange_input, Compare comp)
{
    typedef util::value_iter<Iter_t> type1;
    static_assert (std::is_same< type1, Value_t >::value,
                    "Incompatible iterators\n");

    size_t ndest = 0;
    uint32_t i = 0;
    while (i < nrange_input)
    {
        if (vrange_input[i].size() != 0)
        {
            ndest += vrange_input[i++].size();
        }
        else
        {
            for (uint32_t k = i + 1; k < nrange_input; ++k)
            {
                vrange_input[k - 1] = vrange_input[k];
            };
            --nrange_input;
        };
    };
    if (nrange_input == 0) return range<Value_t *>(dest.first, dest.first);
    if (nrange_input == 1) return move_construct(dest, vrange_input[0]);
    if (nrange_input == 2)
    {
        return merge_construct(dest, vrange_input[0], vrange_input[1], comp);
    };

    //------------------------------------------------------------------------
    // Initial sort
    //------------------------------------------------------------------------
    uint32_t pos[4] = { 0, 1, 2, 3 }, npos = nrange_input;

    //-----------------------------------------------------------------------
    // thanks to Steven Ross by their suggestion about the optimal
    // sorting networks
    //-----------------------------------------------------------------------
    if (less_range(vrange_input[pos[1]].first, pos[1],
                    vrange_input[pos[0]].first, pos[0], comp))
    {
        std::swap(pos[0], pos[1]);
    };
    if (npos == 4  and less_range(vrange_input[pos[3]].first, pos[3],
                                  vrange_input[pos[2]].first, pos[2], comp))
    {
        std::swap(pos[3], pos[2]);
    };
    if (less_range(vrange_input[pos[2]].first, pos[2],
                    vrange_input[pos[0]].first, pos[0], comp))
    {
        std::swap(pos[0], pos[2]);
    };
    if (npos == 4 and less_range(vrange_input[pos[3]].first, pos[3],
                                 vrange_input[pos[1]].first, pos[1], comp))
    {
        std::swap(pos[1], pos[3]);
    };
    if (less_range(vrange_input[pos[2]].first, pos[2],
                    vrange_input[pos[1]].first, pos[1], comp))
    {
        std::swap(pos[1], pos[2]);
    };

    Value_t *it_dest = dest.first;
    while (npos > 2)
    {
        util::construct_object(&(*(it_dest++)),
                        std::move(*(vrange_input[pos[0]].first++)));
        if (vrange_input[pos[0]].size() == 0)
        {
            pos[0] = pos[1];
            pos[1] = pos[2];
            pos[2] = pos[3];
            --npos;
        }
        else
        {
            if (less_range (vrange_input[pos[1]].first, pos[1],
                            vrange_input[pos[0]].first, pos[0], comp))
            {
                std::swap(pos[0], pos[1]);
                if (less_range (vrange_input[pos[2]].first, pos[2],
                                vrange_input[pos[1]].first, pos[1], comp))
                {
                    std::swap(pos[1], pos[2]);
                    if (npos == 4 and less_range(vrange_input[pos[3]].first,
                                                 pos[3],
                                                 vrange_input[pos[2]].first,
                                                 pos[2], comp))
                    {
                        std::swap(pos[2], pos[3]);
                    };
                };
            };
        };
    }; // end while (npos > 2)

    range<Value_t *> raux1(dest.first, it_dest), raux2(it_dest, dest.last);
    if (pos[0] < pos[1])
    {
        return concat(raux1,
                      merge_construct(raux2, vrange_input[pos[0]],
                                      vrange_input[pos[1]], comp));
    }
    else
    {
        return concat(raux1,
                      merge_construct(raux2, vrange_input[pos[1]],
                                      vrange_input[pos[0]], comp));
    };
};

//****************************************************************************
};//    End namespace common
};//    End namespace sort
};//    End namespace boost
//****************************************************************************
//
#endif

/* merge_four.hpp
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
*/