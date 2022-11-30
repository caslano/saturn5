//----------------------------------------------------------------------------
/// @file atomic.hpp
/// @brief Basic layer for to simplify the use of atomic functions
/// @author Copyright(c) 2016 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanying file LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __BOOST_SORT_PARALLEL_DETAIL_UTIL_ATOMIC_HPP
#define __BOOST_SORT_PARALLEL_DETAIL_UTIL_ATOMIC_HPP

#include <atomic>
#include <cassert>
#include <type_traits>

namespace boost
{
namespace sort
{
namespace common
{
namespace util
{
//-----------------------------------------------------------------------------
//  function : atomic_read
/// @brief make the atomic read of an atomic variable, using a memory model
/// @param at_var : atomic variable to read
/// @return value obtained
//-----------------------------------------------------------------------------
template<typename T>
inline T atomic_read(std::atomic<T> &at_var)
{
    return std::atomic_load_explicit < T > (&at_var, std::memory_order_acquire);
};
//
//-----------------------------------------------------------------------------
//  function : atomic_add
/// @brief Add a number to an atomic variable, using a memory model
/// @param at_var : variable to add
/// @param num : value to add to at_var
/// @return result of the operation
//-----------------------------------------------------------------------------
template<typename T, typename T2>
inline T atomic_add(std::atomic<T> &at_var, T2 num)
{
    static_assert (std::is_integral< T2 >::value, "Bad parameter");
    return std::atomic_fetch_add_explicit <T> 
                               (&at_var, (T) num, std::memory_order_acq_rel);
};
//
//-----------------------------------------------------------------------------
//  function : atomic_sub
/// @brief Atomic subtract of an atomic variable using memory model
/// @param at_var : Varibale to subtract
/// @param num : value to sub to at_var
/// @return result of the operation
//-----------------------------------------------------------------------------
template<typename T, typename T2>
inline T atomic_sub(std::atomic<T> &at_var, T2 num)
{
    static_assert (std::is_integral< T2 >::value, "Bad parameter");
    return std::atomic_fetch_sub_explicit <T> 
                                (&at_var, (T) num, std::memory_order_acq_rel);
};
//
//-----------------------------------------------------------------------------
//  function : atomic_write
/// @brief Write a value in an atomic variable using memory model
/// @param at_var : varible to write
/// @param num : value to write in at_var
//-----------------------------------------------------------------------------
template<typename T, typename T2>
inline void atomic_write(std::atomic<T> &at_var, T2 num)
{
    static_assert (std::is_integral< T2 >::value, "Bad parameter");
    std::atomic_store_explicit <T> 
                                (&at_var, (T) num, std::memory_order_release);
};
template<typename T>
struct counter_guard
{
    typedef std::atomic<T> atomic_t;
    atomic_t &count;

    counter_guard(atomic_t & counter): count(counter) { };
    ~counter_guard() {atomic_sub(count, 1); };
};
//
//****************************************************************************
};// End namespace util
};// End namespace common
};// End namespace sort
};// End namespace boost
//****************************************************************************
#endif

/* atomic.hpp
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
*/