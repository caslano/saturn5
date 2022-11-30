//----------------------------------------------------------------------------
/// @file merge.hpp
/// @brief low level merge functions
///
/// @author Copyright (c) 2016 Francisco Jose Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanying file LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __BOOST_SORT_COMMON_UTIL_MERGE_HPP
#define __BOOST_SORT_COMMON_UTIL_MERGE_HPP

#include <algorithm>
#include <functional>
#include <iterator>
#include <memory>

#include <boost/sort/common/util/algorithm.hpp>
#include <boost/sort/common/util/traits.hpp>
#include <boost/sort/common/util/circular_buffer.hpp>

namespace boost
{
namespace sort
{
namespace common
{
namespace util
{
namespace here = boost::sort::common::util;
//----------------------------------------------------------------------------
//
//           F U N C T I O N S    I N    T H E     F I L E
//----------------------------------------------------------------------------
//
// template < class Iter1_t, class Iter2_t, class Compare >
// Iter2_t merge (Iter1_t buf1, const Iter1_t end_buf1, Iter1_t buf2,
//                const Iter1_t end_buf2, Iter2_t buf_out, Compare comp)
//
// template < class Iter_t, class Value_t, class Compare >
// Value_t *merge_construct (Iter_t first1, const Iter_t last1, Iter_t first2,
//                           const Iter_t last2, Value_t *it_out, Compare comp)
//
// template < class Iter1_t, class Iter2_t, class Compare >
// Iter2_t merge_half (Iter1_t buf1, const Iter1_t end_buf1, Iter2_t buf2,
//                     const Iter2_t end_buf2, Iter2_t buf_out, Compare comp)
//
// template < class Iter1_t, class Iter2_t, class Compare >
// Iter2_t merge_half_backward (Iter1_t buf1,  Iter1_t end_buf1,
//                              Iter2_t buf2, Iter2_t end_buf2,
//                              Iter1_t end_buf_out, Compare comp)
//
// template < class Iter1_t, class Iter2_t, class Iter3_t, class Compare >
// bool merge_uncontiguous (Iter1_t src1, const Iter1_t end_src1,
//                          Iter2_t src2, const Iter2_t end_src2,
//                          Iter3_t aux, Compare comp)
//
// template < class Iter1_t, class Iter2_t, class Compare >
// bool merge_contiguous (Iter1_t src1, Iter1_t src2, Iter1_t end_src2,
//                        Iter2_t buf, Compare comp)
//
// template < class Iter_t, class Circular ,class Compare >
// bool merge_circular  (Iter_t buf1, Iter_t end_buf1,
//                       Iter_t buf2, Iter_t end_buf2,
//                       Circular &circ, Compare comp, Iter_t &it_aux)
//
//----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
//  function : merge
/// @brief Merge two contiguous buffers pointed by buf1 and buf2, and put
///        in the buffer pointed by buf_out
///
/// @param buf1 : iterator to the first element in the first buffer
/// @param end_buf1 : final iterator of first buffer
/// @param buf2 : iterator to the first iterator to the second buffer
/// @param end_buf2 : final iterator of the second buffer
/// @param buf_out : buffer where move the elements merged
/// @param comp : comparison object
//-----------------------------------------------------------------------------
template<class Iter1_t, class Iter2_t, class Iter3_t, class Compare>
static Iter3_t merge(Iter1_t buf1, const Iter1_t end_buf1, Iter2_t buf2,
                     const Iter2_t end_buf2, Iter3_t buf_out, Compare comp)
{
    //-------------------------------------------------------------------------
    //                       Metaprogramming
    //------------------------------------------------------------------------- 
    typedef value_iter<Iter1_t> value1_t;
    typedef value_iter<Iter2_t> value2_t;
    typedef value_iter<Iter3_t> value3_t;
    static_assert (std::is_same< value1_t, value2_t >::value,
                    "Incompatible iterators\n");
    static_assert (std::is_same< value3_t, value2_t >::value,
                    "Incompatible iterators\n");

    //-------------------------------------------------------------------------
    //                       Code
    //-------------------------------------------------------------------------
    const size_t MIN_CHECK = 1024;

    if (size_t((end_buf1 - buf1) + (end_buf2 - buf2)) >= MIN_CHECK)
    {
        if (buf1 == end_buf1) return move_forward(buf_out, buf2, end_buf2);
        if (buf2 == end_buf2) return move_forward(buf_out, buf1, end_buf1);

        if (not comp(*buf2, *(end_buf1 - 1)))
        {
            Iter3_t mid = move_forward(buf_out, buf1, end_buf1);
            return move_forward(mid, buf2, end_buf2);
        };

        if (comp(*(end_buf2 - 1), *buf1))
        {
            Iter3_t mid = move_forward(buf_out, buf2, end_buf2);
            return move_forward(mid, buf1, end_buf1);
        };
    };
    while ((buf1 != end_buf1) and (buf2 != end_buf2))
    {
        *(buf_out++) = (not comp(*buf2, *buf1)) ?
                        std::move(*(buf1++)) : std::move(*(buf2++));
    };

    return (buf1 == end_buf1) ?
                    move_forward(buf_out, buf2, end_buf2) :
                    move_forward(buf_out, buf1, end_buf1);
}
;
//
//-----------------------------------------------------------------------------
//  function : merge_construct
/// @brief Merge two contiguous buffers pointed by first1 and first2, and put
///        in the uninitialized buffer pointed by it_out
///
/// @param first1 : iterator to the first element in the first buffer
/// @param last1 : last iterator of the first buffer
/// @param first2 : iterator to the first element to the second buffer
/// @param last2 : final iterator of the second buffer
/// @param it_out : uninitialized buffer where move the elements merged
/// @param comp : comparison object
//-----------------------------------------------------------------------------
template<class Iter1_t, class Iter2_t, class Value_t, class Compare>
static Value_t *merge_construct(Iter1_t first1, const Iter1_t last1,
                                Iter2_t first2, const Iter2_t last2,
                                Value_t *it_out, Compare comp)
{
    //-------------------------------------------------------------------------
    //                       Metaprogramming
    //------------------------------------------------------------------------- 
    typedef value_iter<Iter1_t> type1;
    typedef value_iter<Iter2_t> type2;
    static_assert (std::is_same< Value_t, type1 >::value,
                    "Incompatible iterators\n");
    static_assert (std::is_same< Value_t, type2 >::value,
                    "Incompatible iterators\n");

    //-------------------------------------------------------------------------
    //                       Code
    //-------------------------------------------------------------------------
    const size_t MIN_CHECK = 1024;

    if (size_t((last1 - first1) + (last2 - first2)) >= MIN_CHECK)
    {
        if (first1 == last1) return move_construct(it_out, first2, last2);
        if (first2 == last2) return move_construct(it_out, first1, last1);

        if (not comp(*first2, *(last1 - 1)))
        {
            Value_t* mid = move_construct(it_out, first1, last1);
            return move_construct(mid, first2, last2);
        };

        if (comp(*(last2 - 1), *first1))
        {
            Value_t* mid = move_construct(it_out, first2, last2);
            return move_construct(mid, first1, last1);
        };
    };
    while (first1 != last1 and first2 != last2)
    {
        construct_object((it_out++),
                        (not comp(*first2, *first1)) ?
                                        std::move(*(first1++)) :
                                        std::move(*(first2++)));
    };
    return (first1 == last1) ?
                    move_construct(it_out, first2, last2) :
                    move_construct(it_out, first1, last1);
};
//
//---------------------------------------------------------------------------
//  function : merge_half
/// @brief : Merge two buffers. The first buffer is in a separate memory.
///          The second buffer have a empty space before buf2 of the same size
///          than the (end_buf1 - buf1)
///
/// @param buf1 : iterator to the first element of the first buffer
/// @param end_buf1 : iterator to the last element of the first buffer
/// @param buf2 : iterator to the first element of the second buffer
/// @param end_buf2 : iterator to the last element of the second buffer
/// @param buf_out : iterator to the first element to the buffer where put
///                  the result
/// @param comp : object for Compare two elements of the type pointed
///                by the Iter1_t and Iter2_t
//---------------------------------------------------------------------------
template<class Iter1_t, class Iter2_t, class Compare>
static Iter2_t merge_half(Iter1_t buf1, const Iter1_t end_buf1, Iter2_t buf2,
                          const Iter2_t end_buf2, Iter2_t buf_out, Compare comp)
{
    //-------------------------------------------------------------------------
    //                         Metaprogramming
    //------------------------------------------------------------------------- 
    typedef value_iter<Iter1_t> value1_t;
    typedef value_iter<Iter2_t> value2_t;
    static_assert (std::is_same< value1_t, value2_t >::value,
                    "Incompatible iterators\n");

    //-------------------------------------------------------------------------
    //                         Code
    //-------------------------------------------------------------------------
#ifdef __BS_DEBUG
    assert ( (buf2 - buf_out) == ( end_buf1 - buf1));
#endif
    const size_t MIN_CHECK = 1024;

    if (size_t((end_buf1 - buf1) + (end_buf2 - buf2)) >= MIN_CHECK)
    {
        if (buf1 == end_buf1) return end_buf2;
        if (buf2 == end_buf2) return move_forward(buf_out, buf1, end_buf1);

        if (not comp(*buf2, *(end_buf1 - 1)))
        {
            move_forward(buf_out, buf1, end_buf1);
            return end_buf2;
        };

        if (comp(*(end_buf2 - 1), *buf1))
        {
            Iter2_t mid = move_forward(buf_out, buf2, end_buf2);
            return move_forward(mid, buf1, end_buf1);
        };
    };
    while ((buf1 != end_buf1) and (buf2 != end_buf2))
    {
        *(buf_out++) = (not comp(*buf2, *buf1)) ?
                        std::move(*(buf1++)) : std::move(*(buf2++));
    };
    return (buf2 == end_buf2)? move_forward(buf_out, buf1, end_buf1) : end_buf2;
};

//
//---------------------------------------------------------------------------
//  function : merge_half_backward
/// @brief : Merge two buffers. The first buffer is in a separate memory.
///          The second buffer have a empty space before buf2 of the same size
///          than the (end_buf1 - buf1)
///
/// @param buf1 : iterator to the first element of the first buffer
/// @param end_buf1 : iterator to the last element of the first buffer
/// @param buf2 : iterator to the first element of the second buffer
/// @param end_buf2 : iterator to the last element of the second buffer
/// @param buf_out : iterator to the first element to the buffer where put
///                  the result
/// @param comp : object for Compare two elements of the type pointed
///                by the Iter1_t and Iter2_t
//---------------------------------------------------------------------------
template<class Iter1_t, class Iter2_t, class Compare>
static Iter2_t merge_half_backward(Iter1_t buf1, Iter1_t end_buf1, Iter2_t buf2,
                                   Iter2_t end_buf2, Iter1_t end_buf_out,
                                   Compare comp)
{
    //-------------------------------------------------------------------------
    //                         Metaprogramming
    //-------------------------------------------------------------------------
    typedef value_iter<Iter1_t> value1_t;
    typedef value_iter<Iter2_t> value2_t;
    static_assert (std::is_same< value1_t, value2_t >::value,
                    "Incompatible iterators\n");

    //-------------------------------------------------------------------------
    //                         Code
    //-------------------------------------------------------------------------
#ifdef __BS_DEBUG
    assert ((end_buf_out - end_buf1) == (end_buf2 - buf2) );
#endif
    const size_t MIN_CHECK = 1024;

    if (size_t((end_buf1 - buf1) + (end_buf2 - buf2)) >= MIN_CHECK)
    {
        if (buf2 == end_buf2) return buf1;
        if (buf1 == end_buf1)
            return here::move_backward(end_buf_out, buf2, end_buf2);

        if (not comp(*buf2, *(end_buf1 - 1)))
        {
            here::move_backward(end_buf_out, buf2, end_buf2);
            return buf1;
        };

        if (comp(*(end_buf2 - 1), *buf1))
        {
            Iter1_t mid = here::move_backward(end_buf_out, buf1, end_buf1);
            return here::move_backward(mid, buf2, end_buf2);
        };
    };
    while ((buf1 != end_buf1) and (buf2 != end_buf2))
    {
        *(--end_buf_out) =
                        (not comp(*(end_buf2 - 1), *(end_buf1 - 1))) ?
                                        std::move(*(--end_buf2)):
                                        std::move(*(--end_buf1));
    };
    return (buf1 == end_buf1) ?
                    here::move_backward(end_buf_out, buf2, end_buf2) : buf1;
};

//
//-----------------------------------------------------------------------------
//  function : merge_uncontiguous
/// @brief : merge two uncontiguous buffers, placing the results in the buffers
///          Use an auxiliary buffer pointed by aux
///
/// @param src1 : iterator to the first element of the first buffer
/// @param end_src1 : last iterator  of the first buffer
/// @param src2 : iterator to the first element of the second buffer
/// @param end_src2 : last iterator  of the second buffer
/// @param aux  : iterator to the first element of the auxiliary buffer
/// @param comp : object for to Compare elements
/// @return true : not changes done,  false : changes in the buffers
/// @remarks
//-----------------------------------------------------------------------------
template<class Iter1_t, class Iter2_t, class Iter3_t, class Compare>
static bool merge_uncontiguous(Iter1_t src1, const Iter1_t end_src1,
                               Iter2_t src2, const Iter2_t end_src2,
                               Iter3_t aux, Compare comp)
{
    //-------------------------------------------------------------------------
    //                    Metaprogramming
    //------------------------------------------------------------------------- 
    typedef value_iter<Iter1_t> type1;
    typedef value_iter<Iter2_t> type2;
    typedef value_iter<Iter3_t> type3;
    static_assert (std::is_same< type1, type2 >::value,
                    "Incompatible iterators\n");
    static_assert (std::is_same< type3, type2 >::value,
                    "Incompatible iterators\n");

    //-------------------------------------------------------------------------
    //                    Code
    //-------------------------------------------------------------------------
    if (src1 == end_src1 or src2 == end_src2
                    or not comp(*src2, *(end_src1 - 1))) return true;

    while (src1 != end_src1 and not comp(*src2, *src1))
        ++src1;

    Iter3_t const end_aux = aux + (end_src1 - src1);
    Iter2_t src2_first = src2;
    move_forward(aux, src1, end_src1);

    while ((src1 != end_src1) and (src2 != end_src2))
    {
        *(src1++) = std::move((not comp(*src2, *aux)) ? *(aux++) : *(src2++));
    }

    if (src2 == end_src2)
    {
        while (src1 != end_src1)
            *(src1++) = std::move(*(aux++));
        move_forward(src2_first, aux, end_aux);
    }
    else
    {
        merge_half(aux, end_aux, src2, end_src2, src2_first, comp);
    };
    return false;
};

//
//-----------------------------------------------------------------------------
//  function : merge_contiguous
/// @brief : merge two contiguous buffers,using an auxiliary buffer pointed
///          by buf. The results are in src1 and src2
///
/// @param src1: iterator to the first position of the first buffer
/// @param src2: final iterator of the first buffer and first iterator
///              of the second buffer
/// @param end_src2 : final iterator of the second buffer
/// @param buf  : iterator to buffer used as auxiliary memory
/// @param comp : object for to Compare elements
/// @return true : not changes done,  false : changes in the buffers
//-----------------------------------------------------------------------------
template<class Iter1_t, class Iter2_t, class Compare>
static bool merge_contiguous(Iter1_t src1, Iter1_t src2, Iter1_t end_src2,
                             Iter2_t buf, Compare comp)
{
    //-------------------------------------------------------------------------
    //                      Metaprogramming
    //------------------------------------------------------------------------- 
    typedef value_iter<Iter1_t> type1;
    typedef value_iter<Iter2_t> type2;
    static_assert (std::is_same< type1, type2 >::value,
                    "Incompatible iterators\n");

    //-------------------------------------------------------------------------
    //                         Code
    //-------------------------------------------------------------------------
    if (src1 == src2 or src2 == end_src2 or not comp(*src2, *(src2 - 1)))
        return true;

    Iter1_t end_src1 = src2;
    while (src1 != end_src1 and not comp(*src2, *src1))
        ++src1;

    if (src1 == end_src1) return false;

    size_t nx = end_src1 - src1;
    move_forward(buf, src1, end_src1);
    merge_half(buf, buf + nx, src2, end_src2, src1, comp);
    return false;
};
//
//-----------------------------------------------------------------------------
//  function : merge_circular
/// @brief : merge two buffers,using a circular buffer
///          This function don't check the parameters
/// @param buf1: iterator to the first position of the first buffer
/// @param end_buf1: iterator after the last element of the first buffer
/// @param buf2: iterator to the first element of the secind buffer
/// @param end_buf2: iterator to the first element of the secind buffer
/// @param circ : circular buffer
/// @param comp : comparison object
/// @return true : finished buf1,  false : finished buf2
/// @comments : be carefully because the iterators buf1 and buf2 are modified
//-----------------------------------------------------------------------------
template<class Iter1_t, class Iter2_t, class Circular, class Compare>
static bool merge_circular(Iter1_t buf1, Iter1_t end_buf1, Iter2_t buf2,
                           Iter2_t end_buf2, Circular &circ, Compare comp,
                           Iter1_t &it1_out, Iter2_t &it2_out)
{
    //-------------------------------------------------------------------------
    //                      Metaprogramming
    //-------------------------------------------------------------------------
    typedef value_iter<Iter1_t> type1;
    typedef value_iter<Iter2_t> type2;
    static_assert (std::is_same< type1, type2 >::value,
                    "Incompatible iterators\n");
    typedef typename Circular::value_t type3;
    static_assert (std::is_same<type1, type3>::value,
                    "Incompatible iterators\n");

    //-------------------------------------------------------------------------
    //                      Code
    //-------------------------------------------------------------------------
#ifdef __BS_DEBUG
    assert ( circ.free_size() >= size_t ((end_buf1-buf1) + (end_buf2-buf2)));
#endif

    if (not comp(*buf2, *(end_buf1 - 1)))
    {
        circ.push_move_back(buf1, (end_buf1 - buf1));
        it1_out = end_buf1;
        it2_out = buf2;
        return true;
    };
    if (comp(*(end_buf2 - 1), *buf1))
    {
        circ.push_move_back(buf2, (end_buf2 - buf2));
        it1_out = buf1;
        it2_out = end_buf2;
        return false;
    }
    while (buf1 != end_buf1 and buf2 != end_buf2)
    {
        circ.push_back(comp(*buf2, *buf1) ? std::move(*(buf2++))
                                          : std::move(*(buf1++)));
    };
    it2_out = buf2;
    it1_out = buf1;
    bool ret = (buf1 == end_buf1);
    return ret;
};
//
//****************************************************************************
};//    End namespace util
};//    End namespace common
};//    End namespace sort
};//    End namespace boost
//****************************************************************************
//
#endif

/* merge.hpp
+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
*/