//----------------------------------------------------------------------------
/// @file algorithm.hpp
/// @brief low level functions of create, destroy, move and merge functions
///
/// @author Copyright (c) 2017 Francisco Jose Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanying file LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __BOOST_SORT_COMMON_UTIL_ALGORITHM_HPP
#define __BOOST_SORT_COMMON_UTIL_ALGORITHM_HPP

#include <algorithm>
#include <functional>
#include <iterator>
#include <memory>
#include <type_traits>
#include <vector>
#include <boost/sort/common/util/traits.hpp>

namespace boost
{
namespace sort
{
namespace common
{
namespace util
{
//
//###########################################################################
//
//                       I M P O R T A N T
//
// The functions of this file are for internal use only
// All the operations are done with move operations, because the copy
// operations are unnecesary
//
//###########################################################################
//
//----------------------------------------------------------------------------
//
//         F U N C T I O N S   I N   T H E   F I L E
//
//----------------------------------------------------------------------------
//
// static inline uint32_t nbits32 (uint32_t num) noexcept
//
// static inline uint32_t nbits64 (uint64_t num)
//
// template < class Value_t, class... Args >
// inline void construct_object (Value_t *ptr, Args &&... args)
//
// template < class Value_t >
// inline void destroy_object (Value_t *ptr)
//
// template < class Iter_t, class Value_t = value_iter<Iter_t> >
// void initialize (Iter_t first, Iter_t last, Value_t && val)
//
// template < class Iter1_t, class Iter2_t >
// Iter2_t move_forward (Iter2_t it_dest, Iter1_t first, Iter1_t last)
//
// template < class Iter1_t, class Iter2_t >
// Iter2_t move_backward (Iter2_t it_dest, Iter1_t first, Iter1_t last)
//
// template < class Iter_t, class Value_t = value_iter< Iter_t > >
// Value_t * move_construct (Value_t *ptr, Iter_t first, Iter_t last)
//
// template < class Iter_t >
// void destroy (Iter_t first, const Iter_t last)
//
// template < class Iter_t >
// void reverse (Iter_t first, const Iter_t last)
//
//----------------------------------------------------------------------------
//
//--------------------------------------------------------------------------
//
//                    G L O B A L     V A R I B L E S
//
//--------------------------------------------------------------------------
//
// this array represent the number of bits needed for to represent the
// first 256 numbers
static constexpr const uint32_t tmsb[256] =
{ 0, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
                5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
                6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7,
                7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
                7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
                7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8,
                8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
                8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
                8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
                8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
                8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
                8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 };
//
//---------------------------------------------------------------------------
//
//                           F U N C T I O N S
//
//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
//  function : nbits32
/// @brief Obtain the number of bits of a number equal or greater than num
/// @param num : Number to examine
/// @return Number of bits
//---------------------------------------------------------------------------
static inline uint32_t nbits32 (uint32_t num) noexcept
{
    int Pos = (num & 0xffff0000U) ? 16 : 0;
    if ((num >> Pos) & 0xff00U) Pos += 8;
    return (tmsb[num >> Pos] + Pos);
}
//
//---------------------------------------------------------------------------
//  function : nbits64
/// @brief Obtain the number of bits of a number equal or greater than num
/// @param num : Number to examine
/// @exception none
/// @return Number of bits
//---------------------------------------------------------------------------
static inline uint32_t nbits64(uint64_t num)noexcept
{
    uint32_t Pos = (num & 0xffffffff00000000ULL) ? 32 : 0;
    if ((num >> Pos) & 0xffff0000ULL) Pos += 16;
    if ((num >> Pos) & 0xff00ULL) Pos += 8;
    return (tmsb[num >> Pos] + Pos);
}
//
//-----------------------------------------------------------------------------
//  function : construct_object
/// @brief create an object in the memory specified by ptr
///
/// @param ptr : pointer to the memory where to create the object
/// @param args : arguments to the constructor
//-----------------------------------------------------------------------------
template <class Value_t, class ... Args>
inline void construct_object (Value_t *ptr, Args &&... args)
{
    (::new (static_cast<void *>(ptr)) Value_t(std::forward< Args > (args)...));
};
//
//-----------------------------------------------------------------------------
//  function : destroy_object
/// @brief destroy an object in the memory specified by ptr
/// @param ptr : pointer to the object to destroy
//-----------------------------------------------------------------------------
template<class Value_t>
inline void destroy_object(Value_t *ptr)
{
    ptr->~Value_t();
};
//
//-----------------------------------------------------------------------------
//  function : initialize
/// @brief initialize a range of objects with the object val moving across them
///
/// @param first : itertor to the first element to initialize
/// @param last : iterator to the last element to initialize
/// @param val : object used for the initialization
//-----------------------------------------------------------------------------
template <class Iter_t, class Value_t = value_iter<Iter_t> >
inline void initialize (Iter_t first, Iter_t last, Value_t & val)
{
    //------------------------------------------------------------------------
    //                  Metaprogramming
    //------------------------------------------------------------------------
    typedef value_iter<Iter_t> value_t;
    static_assert (std::is_same< Value_t, value_t >::value,
                    "Incompatible iterators\n");

    //------------------------------------------------------------------------
    //                 Code
    //------------------------------------------------------------------------
    if (first == last) return;
    construct_object(&(*first), std::move(val));

    Iter_t it1 = first, it2 = first + 1;
    while (it2 != last)
    {
        construct_object(&(*(it2++)), std::move(*(it1++)));
    };
    val = std::move(*(last - 1));
};
//
//-----------------------------------------------------------------------------
//  function : move_forward
/// @brief Move initialized objets
/// @param it_dest : iterator to the final place of the objects
/// @param first : iterator to the first element to move
/// @param last : iterator to the last element to move
/// @return Output iterator to the element past the last element
///         moved (it_dest + (last - first))
//-----------------------------------------------------------------------------
template <class Iter1_t, class Iter2_t>
inline Iter2_t move_forward (Iter2_t it_dest, Iter1_t first, Iter1_t last)
{
    //------------------------------------------------------------------------
    //                  Metaprogramming
    //------------------------------------------------------------------------
    typedef value_iter<Iter1_t> value1_t;
    typedef value_iter<Iter2_t> value2_t;
    static_assert (std::is_same< value1_t, value2_t >::value,
                    "Incompatible iterators\n");

    //------------------------------------------------------------------------
    //                 Code
    //------------------------------------------------------------------------
    while (first != last)
    {   *it_dest++ = std::move(*first++);
    }
    return it_dest;

};
//
//-----------------------------------------------------------------------------
//  function : move_backard
/// @brief Move initialized objets in reverse order
/// @param it_dest : last iterator to the final place of the objects
/// @param first : iterator to the first element to move
/// @param last : iterator to the last element to move
//-----------------------------------------------------------------------------
template<class Iter1_t, class Iter2_t>
inline Iter2_t move_backward(Iter2_t it_dest, Iter1_t  first, Iter1_t last)
{
    //------------------------------------------------------------------------
    //                  Metaprogramming
    //------------------------------------------------------------------------
    typedef value_iter<Iter1_t> value1_t;
    typedef value_iter<Iter2_t> value2_t;
    static_assert (std::is_same< value1_t, value2_t >::value,
                    "Incompatible iterators\n");

    //------------------------------------------------------------------------
    //                 Code
    //------------------------------------------------------------------------
    while (first != last)
    {   *(--it_dest) = std::move (*(--last));
    }
    return it_dest;
};

//
//-----------------------------------------------------------------------------
//  function : move_construct
/// @brief Move objets to uninitialized memory
///
/// @param ptr : pointer to the memory where to create the objects
/// @param first : iterator to the first element to move
/// @param last : iterator to the last element to move
//-----------------------------------------------------------------------------
template<class Iter_t, class Value_t = value_iter<Iter_t> >
inline Value_t * move_construct(Value_t *ptr, Iter_t first, Iter_t last)
{
    //------------------------------------------------------------------------
    //                  Metaprogramming
    //------------------------------------------------------------------------
    typedef typename iterator_traits<Iter_t>::value_type value2_t;
    static_assert (std::is_same< Value_t, value2_t >::value,
                    "Incompatible iterators\n");

    //------------------------------------------------------------------------
    //                    Code
    //------------------------------------------------------------------------
    while (first != last)
    {
        ::new (static_cast<void *>(ptr++)) Value_t(std::move(*(first++)));
    };
    return ptr;
};
//
//-----------------------------------------------------------------------------
//  function : destroy
/// @brief destroy the elements between first and last
/// @param first : iterator to the first element to destroy
/// @param last : iterator to the last element to destroy
//-----------------------------------------------------------------------------
template<class Iter_t>
inline void destroy(Iter_t first, const Iter_t last)
{
    while (first != last)
        destroy_object(&(*(first++)));
};
//
//-----------------------------------------------------------------------------
//  function : reverse
/// @brief destroy the elements between first and last
/// @param first : iterator to the first element to destroy
/// @param last : iterator to the last element to destroy
//-----------------------------------------------------------------------------
template<class Iter_t>
inline void reverse(Iter_t first, Iter_t last)
{
    std::reverse ( first, last);
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

/* algorithm.hpp
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
*/