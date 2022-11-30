//----------------------------------------------------------------------------
/// @file range.hpp
/// @brief Define a range [first, last), and the associated operations
///
/// @author Copyright (c) 2016 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __BOOST_SORT_PARALLEL_DETAIL_UTIL_RANGE_HPP
#define __BOOST_SORT_PARALLEL_DETAIL_UTIL_RANGE_HPP

#include <boost/sort/common/util/algorithm.hpp>
#include <boost/sort/common/util/merge.hpp>
#include <boost/sort/common/util/traits.hpp>
#include <cassert>
#include <functional>
#include <memory>
#include <vector>

namespace boost
{
namespace sort
{
namespace common
{

///---------------------------------------------------------------------------
/// @struct range
/// @brief this represent a range between two iterators
/// @remarks
//----------------------------------------------------------------------------
template <class Iter_t>
struct range
{
    Iter_t first, last;
    //
    //------------------------------------------------------------------------
    //  function : range
    /// @brief  empty constructor
    //------------------------------------------------------------------------
    range(void) { };
    //
    //------------------------------------------------------------------------
    //  function : range
    /// @brief  constructor with two parameters
    /// @param frs : iterator to the first element
    /// @param lst : iterator to the last element
    //-----------------------------------------------------------------------
    range(const Iter_t &frs, const Iter_t &lst): first(frs), last(lst) { };
    //
    //-----------------------------------------------------------------------
    //  function : empty
    /// @brief indicate if the range is empty
    /// @return  true : empty false : not empty
    //-----------------------------------------------------------------------
    bool empty(void) const { return (first == last); };
    //
    //-----------------------------------------------------------------------
    //  function : not_empty
    /// @brief indicate if the range is not empty
    /// @return  true : not empty false : empty
    //-----------------------------------------------------------------------
    bool not_empty(void) const {return (first != last); };
    //
    //-----------------------------------------------------------------------
    //  function : valid
    /// @brief  Indicate if the range is well constructed, and valid
    /// @return true : valid,  false : not valid
    //-----------------------------------------------------------------------
    bool valid(void) const { return ((last - first) >= 0); };
    //
    //-----------------------------------------------------------------------
    //  function : size
    /// @brief  return the size of the range
    /// @return size
    //-----------------------------------------------------------------------
    size_t size(void) const { return (last - first); };
    //
    //------------------------------------------------------------------------
    //  function : front
    /// @brief return an iterator to the first element of the range
    /// @return iterator
    //-----------------------------------------------------------------------
    Iter_t front(void) const { return first; };
    //
    //-------------------------------------------------------------------------
    //  function : back
    /// @brief return an iterator to the last element of the range
    /// @return iterator
    //-------------------------------------------------------------------------
    Iter_t back(void) const {return (last - 1); };
};

//
//-----------------------------------------------------------------------------
//  function : concat
/// @brief concatenate two contiguous ranges
/// @param it1 : first range
/// @param it2 : second range
/// @return  range resulting of the concatenation
//-----------------------------------------------------------------------------
template<class Iter_t>
inline range<Iter_t> concat(const range<Iter_t> &it1, const range<Iter_t> &it2)
{
    return range<Iter_t>(it1.first, it2.last);
}
;
//
//-----------------------------------------------------------------------------
//  function : move_forward
/// @brief Move initialized objets from the range src to dest
/// @param dest : range where move the objects
/// @param src : range from where move the objects
/// @return range with the objects moved and the size adjusted
//-----------------------------------------------------------------------------
template <class Iter1_t, class Iter2_t>
inline range<Iter2_t> move_forward(const range<Iter2_t> &dest,
                                   const range<Iter1_t> &src)
{
    assert(dest.size() >= src.size());
    Iter2_t it_aux = util::move_forward(dest.first, src.first, src.last);
    return range<Iter2_t>(dest.first, it_aux);
};
//
//-----------------------------------------------------------------------------
//  function : move_backward
/// @brief Move initialized objets from the range src to dest
/// @param dest : range where move the objects
/// @param src : range from where move the objects
/// @return range with the objects moved and the size adjusted
//-----------------------------------------------------------------------------
template <class Iter1_t, class Iter2_t>
inline range<Iter2_t> move_backward(const range<Iter2_t> &dest,
                                    const range<Iter1_t> &src)
{
    assert(dest.size() >= src.size());
    Iter2_t it_aux = util::move_backward(dest.first + src.size(), src.first,
                    src.last);
    return range<Iter2_t>(dest.first, dest.src.size());
};

//-----------------------------------------------------------------------------
//  function : uninit_move
/// @brief Move uninitialized objets from the range src creating them in  dest
///
/// @param dest : range where move and create the objects
/// @param src : range from where move the objects
/// @return range with the objects moved and the size adjusted
//-----------------------------------------------------------------------------
template<class Iter_t, class Value_t = util::value_iter<Iter_t> >
inline range<Value_t*> move_construct(const range<Value_t*> &dest,
                                      const range<Iter_t> &src)
{
    Value_t *ptr_aux = util::move_construct(dest.first, src.first, src.last);
    return range<Value_t*>(dest.first, ptr_aux);
};
//
//-----------------------------------------------------------------------------
//  function : destroy
/// @brief destroy a range of objects
/// @param rng : range to destroy
//-----------------------------------------------------------------------------
template<class Iter_t>
inline void destroy(range<Iter_t> rng)
{
    util::destroy(rng.first, rng.last);
};
//
//-----------------------------------------------------------------------------
//  function : initialize
/// @brief initialize a range of objects with the object val moving across them
/// @param rng : range of elements not initialized
/// @param val : object used for the initialization
/// @return range initialized
//-----------------------------------------------------------------------------
template<class Iter_t, class Value_t = util::value_iter<Iter_t> >
inline range<Iter_t> initialize(const range<Iter_t> &rng, Value_t &val)
{
    util::initialize(rng.first, rng.last, val);
    return rng;
};
//
//-----------------------------------------------------------------------------
//  function : is_mergeable
/// @brief : indicate if two ranges have a possible merge
/// @param src1 : first range
/// @param src2 : second range
/// @param comp : object for to compare elements
/// @return true : they can be merged
///         false : they can't be merged
//-----------------------------------------------------------------------------
template<class Iter1_t, class Iter2_t, class Compare>
inline bool is_mergeable(const range<Iter1_t> &src1, const range<Iter2_t> &src2,
                         Compare comp)
{
    //------------------------------------------------------------------------
    //                  Metaprogramming
    //------------------------------------------------------------------------
    typedef util::value_iter<Iter1_t> type1;
    typedef util::value_iter<Iter2_t> type2;
    static_assert (std::is_same< type1, type2 >::value,
                    "Incompatible iterators\n");
    //------------------------------------------------------------------------
    //                 Code
    //------------------------------------------------------------------------
    return comp(*(src2.front()), *(src1.back()));
};
//
//-----------------------------------------------------------------------------
//  function : is_mergeable_stable
/// @brief : indicate if two ranges have a possible merge
/// @param src1 : first range
/// @param src2 : second range
/// @param comp : object for to compare elements
/// @return true : they can be merged
///         false : they can't be merged
//-----------------------------------------------------------------------------
template<class Iter1_t, class Iter2_t, class Compare>
inline bool is_mergeable_stable(const range<Iter1_t> &src1,
                                const range<Iter2_t> &src2, Compare comp)
{
    //------------------------------------------------------------------------
    //                  Metaprogramming
    //------------------------------------------------------------------------
    typedef util::value_iter<Iter1_t> type1;
    typedef util::value_iter<Iter2_t> type2;
    static_assert (std::is_same< type1, type2 >::value,
                    "Incompatible iterators\n");
    //------------------------------------------------------------------------
    //                 Code
    //------------------------------------------------------------------------
    return not comp(*(src1.back()), *(src2.front()));
};
//
//-----------------------------------------------------------------------------
//  function : merge
/// @brief Merge two contiguous ranges src1 and src2, and put the result in
///        the range dest, returning the range merged
///
/// @param dest : range where locate the lements merged. the size of dest
///               must be  greater or equal than the sum of the sizes of
///               src1 and src2
/// @param src1 : first range to merge
/// @param src2 : second range to merge
/// @param comp : comparison object
/// @return range with the elements merged and the size adjusted
//-----------------------------------------------------------------------------
template<class Iter1_t, class Iter2_t, class Iter3_t, class Compare>
inline range<Iter3_t> merge(const range<Iter3_t> &dest,
                            const range<Iter1_t> &src1,
                            const range<Iter2_t> &src2, Compare comp)
{
    Iter3_t it_aux = util::merge(src1.first, src1.last, src2.first, src2.last,
                    dest.first, comp);
    return range<Iter3_t>(dest.first, it_aux);
};

//-----------------------------------------------------------------------------
//  function : merge_construct
/// @brief Merge two contiguous uninitialized ranges src1 and src2, and create
///        and move the result in the uninitialized range dest, returning the
///        range merged
//
/// @param dest : range where locate the elements merged. the size of dest
///               must be  greater or equal than the sum of the sizes of
///               src1 and src2. Initially is uninitialize memory
/// @param src1 : first range to merge
/// @param src2 : second range to merge
/// @param comp : comparison object
/// @return range with the elements merged and the size adjusted
//-----------------------------------------------------------------------------
template<class Iter1_t, class Iter2_t, class Value_t, class Compare>
inline range<Value_t *> merge_construct(const range<Value_t *> &dest,
                                        const range<Iter1_t> &src1,
                                        const range<Iter2_t> &src2,
                                        Compare comp)
{
    Value_t * ptr_aux = util::merge_construct(src1.first, src1.last, src2.first,
                    src2.last, dest.first, comp);
    return range<Value_t*>(dest.first, ptr_aux);
};
//
//---------------------------------------------------------------------------
//  function : half_merge
/// @brief : Merge two initialized buffers. The first buffer is in a separate
///          memory
//
/// @param dest : range where finish the two buffers merged
/// @param src1 : first range to merge in a separate memory
/// @param src2 : second range to merge, in the final part of the
///               range where deposit the final results
/// @param comp : object for compare two elements of the type pointed
///               by the Iter1_t and Iter2_t
/// @return : range with the two buffers merged
//---------------------------------------------------------------------------
template<class Iter1_t, class Iter2_t, class Compare>
inline range<Iter2_t> merge_half(const range<Iter2_t> &dest,
                                 const range<Iter1_t> &src1,
                                 const range<Iter2_t> &src2, Compare comp)
{
    Iter2_t it_aux = util::merge_half(src1.first, src1.last, src2.first,
                    src2.last, dest.first, comp);
    return range<Iter2_t>(dest.first, it_aux);
};
//
//-----------------------------------------------------------------------------
//  function : merge_uncontiguous
/// @brief : merge two non contiguous ranges src1, src2, using the range
///          aux as auxiliary memory. The results are in the original ranges
//
/// @param src1 : first range to merge
/// @param src2 : second range to merge
/// @param aux : auxiliary range used in the merge
/// @param comp : object for to compare elements
/// @return true : not changes done, false : changes in the buffers
//-----------------------------------------------------------------------------
template<class Iter1_t, class Iter2_t, class Iter3_t, class Compare>
inline bool merge_uncontiguous(const range<Iter1_t> &src1,
                               const range<Iter2_t> &src2,
                               const range<Iter3_t> &aux, Compare comp)
{
    return util::merge_uncontiguous(src1.first, src1.last, src2.first,
                    src2.last, aux.first, comp);
};
//
//-----------------------------------------------------------------------------
//  function : merge_contiguous
/// @brief : merge two contiguous ranges ( src1, src2) using buf as
///          auxiliary memory. The results are in the same ranges
/// @param src1 : first range to merge
/// @param src1 : second range to merge
/// @param buf : auxiliary memory used in the merge
/// @param comp : object for to compare elements
/// @return true : not changes done,   false : changes in the buffers
//-----------------------------------------------------------------------------
template<class Iter1_t, class Iter2_t, class Compare>
inline range<Iter1_t> merge_contiguous(const range<Iter1_t> &src1,
                                       const range<Iter1_t> &src2,
                                       const range<Iter2_t> &buf, Compare comp)
{
    util::merge_contiguous(src1.first, src1.last, src2.last, buf.first, comp);
    return concat(src1, src2);
};
//
//-----------------------------------------------------------------------------
//  function : merge_flow
/// @brief : merge two ranges, as part of a merge the ranges in a list. This
///         function reduce the number of movements compared with inplace_merge
///         when you need to merge a sequence of ranges.
///         This function merge the ranges rbuf and rng2, and the results
///          are in rng1 and rbuf
//
/// @param rng1 : range where locate the first elements of the merge
/// @param rbuf : range which provide the first elements, and where store
///               the last results of the merge
/// @param rng2 : range which provide the last elements to merge
/// @param comp : object for to compare elements
/// @return true : not changes done,  false : changes in the buffers
//-----------------------------------------------------------------------------
template<class Iter1_t, class Iter2_t, class Compare>
static void merge_flow(range<Iter1_t> rng1, range<Iter2_t> rbuf,
                       range<Iter1_t> rng2, Compare cmp)
{
    //-------------------------------------------------------------------------
    //                       Metaprogramming
    //-------------------------------------------------------------------------
    typedef util::value_iter<Iter1_t> type1;
    typedef util::value_iter<Iter2_t> type2;
    static_assert (std::is_same< type1, type2 >::value,
                    "Incompatible iterators\n");

    //-------------------------------------------------------------------------
    //                       Code
    //-------------------------------------------------------------------------
    range<Iter2_t> rbx(rbuf);
    range<Iter1_t> rx1(rng1), rx2(rng2);
    assert(rbx.size() == rx1.size() and rx1.size() == rx2.size());
    while (rx1.first != rx1.last)
    {
        *(rx1.first++) = (cmp(*rbx.first, *rx2.first)) ?
                                                    std::move(*(rbx.first++)):
                                                    std::move(*(rx2.first++));
    };
    if (rx2.first == rx2.last) return;
    if (rbx.first == rbx.last) move_forward(rbuf, rng2);
    else                       merge_half(rbuf, rx2, rbx, cmp);
};

//****************************************************************************
};//    End namespace common
};//    End namespace sort
};//    End namespace boost
//****************************************************************************
//
#endif

/* range.hpp
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
*/