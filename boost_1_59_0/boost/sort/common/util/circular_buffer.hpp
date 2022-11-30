//----------------------------------------------------------------------------
/// @file   circular_buffer.hpp
/// @brief  This file contains the implementation of the circular buffer
///
/// @author Copyright (c) 2010 2015 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __BOOST_SORT_COMMON_UTIL_CIRCULAR_BUFFER_HPP
#define __BOOST_SORT_COMMON_UTIL_CIRCULAR_BUFFER_HPP

#include <memory>
#include <cassert>
#include <exception>
#include <boost/sort/common/util/algorithm.hpp>
#include <boost/sort/common/util/traits.hpp>

namespace boost
{
namespace sort
{
namespace common
{
namespace util
{

//---------------------------------------------------------------------------
/// @class  circular_buffer
/// @brief  This class implement a circular buffer
/// @remarks
//---------------------------------------------------------------------------
template <class Value_t, uint32_t Power2 = 11>
struct circular_buffer
{
    //------------------------------------------------------------------------
    //                          STATIC CHECK
    //------------------------------------------------------------------------
    static_assert ( Power2 != 0, "Wrong Power2");

    //------------------------------------------------------------------------
    //                          DEFINITIONS
    //------------------------------------------------------------------------
    typedef Value_t value_t;

    //------------------------------------------------------------------------
    //                          VARIABLES
    //------------------------------------------------------------------------
    const size_t NMAX = (size_t) 1 << Power2;
    const size_t MASK = (NMAX - 1);
    const size_t BLOCK_SIZE = NMAX >> 1;
    const size_t LOG_BLOCK = Power2 - 1;
    Value_t * ptr = nullptr;

    //------------------------------------------------------------------------
    // first and last are  the position of the first and last elements
    // always are in the range [0, NMAX - 1]
    //------------------------------------------------------------------------
    size_t nelem, first_pos;
    bool initialized;

    //
    //------------------------------------------------------------------------
    //  function : circular_buffer
    /// @brief  constructor of the class
    //-----------------------------------------------------------------------
    circular_buffer(void)
    : ptr(nullptr), nelem(0), first_pos(0), initialized(false)
    {
        ptr = std::get_temporary_buffer < Value_t > (NMAX).first;
        if (ptr == nullptr) throw std::bad_alloc();
    };
    //
    //------------------------------------------------------------------------
    //  function : ~circular_buffer
    /// @brief destructor of the class
    //-----------------------------------------------------------------------
    ~circular_buffer()
    {
        if (initialized)
        {   for (size_t i = 0; i < NMAX; ++i) (ptr + i)->~Value_t();
            initialized = false;
        };
        std::return_temporary_buffer(ptr);
    }
    ;
    //
    //------------------------------------------------------------------------
    //  function : initialize
    /// @brief : initialize the memory of the buffer from the uninitialize
    //           memory obtained from the temporary buffer
    /// @param val : value used to initialize the memory
    //-----------------------------------------------------------------------
    void initialize(Value_t & val)
    {
        assert (initialized == false);
        ::new (static_cast<void*>(ptr)) Value_t(std::move(val));
        for (size_t i = 1; i < NMAX; ++i)
            ::new (static_cast<void*>(ptr + i)) Value_t(std::move(ptr[i - 1]));
        val = std::move(ptr[NMAX - 1]);
        initialized = true;
    };
    //
    //------------------------------------------------------------------------
    //  function : destroy_all
    /// @brief : destroy all the objects in the internal memory
    //-----------------------------------------------------------------------
    void destroy_all(void) { destroy(ptr, ptr + NMAX); };
    //
    //------------------------------------------------------------------------
    //  function : get_buffer
    /// @brief return the internal memory of the circular buffer
    /// @return pointer to the internal memory of the buffer
    //-----------------------------------------------------------------------
    Value_t * get_buffer(void) { return ptr; };
    //
    //------------------------------------------------------------------------
    //  function : empty
    /// @brief return if the buffer is empty
    /// @return true : empty
    //-----------------------------------------------------------------------
    bool empty(void) const {return (nelem == 0); };
    //
    //------------------------------------------------------------------------
    //  function : full
    /// @brief return if the buffer is full
    /// @return true : full
    //-----------------------------------------------------------------------
    bool full(void) const { return (nelem == NMAX); };
    //
    //------------------------------------------------------------------------
    //  function : size
    /// @brief return the number of elements stored in the buffer
    /// @return number of elements stored
    //-----------------------------------------------------------------------
    size_t size(void) const { return nelem;};
    //
    //------------------------------------------------------------------------
    //  function : capacity
    /// @brief : return the maximun capacity of the buffer
    /// @return number of elements
    //-----------------------------------------------------------------------
    size_t capacity(void) const { return NMAX;};
    //
    //------------------------------------------------------------------------
    //  function : free_size
    /// @brief return the free positions in the buffer
    /// @return number of elements
    //-----------------------------------------------------------------------
    size_t free_size(void) const  { return (NMAX - nelem); };
    //
    //------------------------------------------------------------------------
    //  function : clear
    /// @brief clear the buffer
    //-----------------------------------------------------------------------
    void clear(void)  { nelem = first_pos = 0; };
    //
    //------------------------------------------------------------------------
    //  function : front
    /// @brief return the first element of the buffer
    /// @return reference to the first value
    //-----------------------------------------------------------------------
    Value_t & front(void)
    {
#ifdef __BS_DEBUG
        assert (nelem > 0);
#endif
        return (ptr[first_pos]);
    };
    //
    //------------------------------------------------------------------------
    //  function :front
    /// @brief return the first element of the buffer
    /// @return const reference to the first value
    //-----------------------------------------------------------------------
    const Value_t & front(void) const
    {
#ifdef __BS_DEBUG
        assert ( nelem > 0 );
#endif
        return (ptr[first_pos]);
    };
    //
    //------------------------------------------------------------------------
    //  function : back
    /// @brief reference to the last value of the buffer
    /// @return reference to the last value
    //-----------------------------------------------------------------------
    Value_t & back(void)
    {
#ifdef __BS_DEBUG
        assert ( nelem > 0 );
#endif
        return (ptr[(first_pos + nelem - 1) & MASK]);
    };
    //
    //------------------------------------------------------------------------
    //  function : back
    /// @brief reference to the last value of the buffer
    /// @return const reference to the last value
    //-----------------------------------------------------------------------
    const Value_t & back(void) const
    {
#ifdef __BS_DEBUG
        assert ( nelem > 0 );
#endif
        return (ptr[(first_pos + nelem - 1) & MASK]);
    };
    //
    //------------------------------------------------------------------------
    //  function : operator []
    /// @brief positional access to the elements
    /// @param pos rquested
    /// @return reference to the element
    //-----------------------------------------------------------------------
    Value_t & operator[](uint32_t pos)
    {
#ifdef __BS_DEBUG
        assert ( nelem > 0 );
#endif
        return ptr[(first_pos + pos) & MASK];
    };
    //
    //------------------------------------------------------------------------
    //  function : operator []
    /// @brief positional access to the elements
    /// @param pos rquested
    /// @return const reference to the element
    //-----------------------------------------------------------------------
    const Value_t & operator[](uint32_t pos) const
    {

#ifdef __BS_DEBUG
        assert ( nelem > 0 );
#endif
        return ptr[(first_pos + pos) & MASK];
    };
    //
    //------------------------------------------------------------------------
    //  function : push_front
    /// @brief insert an element in the first position of the buffer
    /// @param val : const value to insert
    //-----------------------------------------------------------------------
    void push_front(const Value_t & val)
    {
#ifdef __BS_DEBUG
        assert ( nelem != NMAX);
#endif
        ++nelem;
        first_pos = ((first_pos + MASK) & MASK);
        ptr[first_pos] = val;

    };
    //
    //------------------------------------------------------------------------
    //  function : push_front
    /// @brief insert an element in the first position of the buffer
    /// @param val : rvalue to insert
    //-----------------------------------------------------------------------
    void push_front(Value_t && val)
    {
#ifdef __BS_DEBUG
        assert ( nelem != NMAX);
#endif
        ++nelem;
        first_pos = ((first_pos + MASK) & MASK);
        ptr[first_pos] = val;
    };
    //
    //------------------------------------------------------------------------
    //  function : push_back
    /// @brief insert an element in the last position of the buffer
    /// @param val : value to insert
    //-----------------------------------------------------------------------
    void push_back(const Value_t & val)
    {
#ifdef __BS_DEBUG
        assert ( nelem != NMAX);
#endif
        ptr[(first_pos + (nelem++)) & MASK] = val;
    };
    //
    //------------------------------------------------------------------------
    //  function : push_back
    /// @brief insert an element in the last position of the buffer
    /// @param val : value to insert
    //-----------------------------------------------------------------------
    void push_back(Value_t && val)
    {
#ifdef __BS_DEBUG
        assert ( nelem != NMAX);
#endif
        ptr[(first_pos + (nelem++)) & MASK] = std::move(val);
    };
    //
    //------------------------------------------------------------------------
    //  function : pop_front
    /// @brief remove the first element of the buffer
    //-----------------------------------------------------------------------
    void pop_front(void)
    {
#ifdef __BS_DEBUG
        assert ( nelem > 0 );
#endif
        --nelem;
        (++first_pos) &= MASK;
    };
    //
    //------------------------------------------------------------------------
    //  function : pop_back
    /// @brief remove the last element of the buffer
    //-----------------------------------------------------------------------
    void pop_back(void)
    {
#ifdef __BS_DEBUG
        assert ( nelem > 0 );
#endif
        --nelem;
    };

    template<class iter_t>
    void pop_copy_front(iter_t it_dest, size_t num);

    template<class iter_t>
    void pop_move_front(iter_t it_dest, size_t num);

    template<class iter_t>
    void pop_copy_back(iter_t it_dest, size_t num);

    template<class iter_t>
    void pop_move_back(iter_t it_dest, size_t num);

    template<class iter_t>
    void push_copy_front(iter_t it_src, size_t num);

    template<class iter_t>
    void push_move_front(iter_t it_src, size_t num);

    template<class iter_t>
    void push_copy_back(iter_t it_src, size_t num);

    template<class iter_t>
    void push_move_back(iter_t it_src, size_t num);

//---------------------------------------------------------------------------
};//               End of class circular_buffer
//---------------------------------------------------------------------------
//
//
//############################################################################
//                                                                          ##
//             N O N    I N L I N E    F U N C T I O N S                    ##
//                                                                          ##
//############################################################################
//
//------------------------------------------------------------------------
//  function : pop_copy_front
/// @brief copy and delete num elements from the front of the buffer
/// @param it_dest : iterator to the first position where copy the elements
/// @param num : number of elements to copy
//-----------------------------------------------------------------------
template <class Value_t, uint32_t Power2>
template<class iter_t>
void circular_buffer<Value_t, Power2>
::pop_copy_front(iter_t it_dest, size_t num)
{
    static_assert ( std::is_same <value_iter<iter_t>, Value_t>::value,
                    "Incompatible iterator");
    if (num == 0) return;
#ifdef __BS_DEBUG
    assert ( num <= nelem);
#endif
    nelem -= num;
    size_t pos = first_pos;
    first_pos = (first_pos + num) & MASK;
    for (size_t i = 0; i < num; ++i)
    {
        *(it_dest++) = ptr[pos++ & MASK];
    };
    first_pos &= MASK;
};
//
//------------------------------------------------------------------------
//  function : pop_move_front
/// @brief move num elements from the front of the buffer to the place
//         pointed by it_dest
/// @param it_dest : iterator to the first position where move the elements
/// @param num : number of elements to move
//-----------------------------------------------------------------------
template <class Value_t, uint32_t Power2>
template<class iter_t>
void circular_buffer<Value_t, Power2>
:: pop_move_front(iter_t it_dest, size_t num)
{
    static_assert ( std::is_same <value_iter<iter_t>, Value_t>::value,
                    "Incompatible iterator");
    if (num == 0) return;
#ifdef __BS_DEBUG
    assert ( num <= nelem);
#endif
    nelem -= num;
    size_t pos = first_pos;
    first_pos = (first_pos + num) & MASK;
    for (size_t i = 0; i < num; ++i)
    {
        *(it_dest++) = std::move(ptr[pos++ & MASK]);
    };
    first_pos &= MASK;
};
//
//------------------------------------------------------------------------
//  function : pop_copy_back
/// @brief copy and delete num elements from the back of the buffer
/// @param p1 : iterator where begin to copy the elements
/// @param num : number of elements to copy
//-----------------------------------------------------------------------
template <class Value_t, uint32_t Power2>
template<class iter_t>
void circular_buffer<Value_t, Power2>
::pop_copy_back(iter_t it_dest, size_t num)
{
    static_assert ( std::is_same <value_iter<iter_t>, Value_t>::value,
                    "Incompatible iterator");
    if (num == 0) return;
#ifdef __BS_DEBUG
    assert ( num <= nelem);
#endif
    nelem -= num;
    size_t pos = (first_pos + nelem) & MASK;
    for (size_t i = 0; i < num; ++i)
    {
        *(it_dest++) = ptr[pos++ & MASK];
    };
};
//
//------------------------------------------------------------------------
//  function : pop_move_back
/// @brief move and delete num elements from the back of the buffer
/// @param p1 : iterator where begin to move the elements
/// @param num : number of elements to move
//-----------------------------------------------------------------------
template <class Value_t, uint32_t Power2>
template<class iter_t>
void circular_buffer<Value_t, Power2>
::pop_move_back(iter_t it_dest, size_t num)
{
    static_assert ( std::is_same <value_iter<iter_t>, Value_t>::value,
                    "Incompatible iterator");
    if (num == 0) return;
#ifdef __BS_DEBUG
    assert ( num <= nelem);
#endif
    nelem -= num;
    size_t pos = (first_pos + nelem) & MASK;
    for (size_t i = 0; i < num; ++i)
    {
        *(it_dest++) = std::move(ptr[pos++ & MASK]);
    };
};
//
//------------------------------------------------------------------------
//  function : push_copy_front
/// @brief copy num elements in the front of the buffer
/// @param it_src : iterator from where begin to copy the elements
/// @param mun : number of element to copy
//-----------------------------------------------------------------------
template <class Value_t, uint32_t Power2>
template<class iter_t>
void circular_buffer<Value_t, Power2>
::push_copy_front(iter_t it_src, size_t num)
{
    static_assert ( std::is_same <value_iter<iter_t>, Value_t>::value,
                    "Incompatible iterator");
    if (num == 0) return;
#ifdef __BS_DEBUG
    assert ( free_size() >= num);
#endif
    nelem += num;

    first_pos = (first_pos + NMAX - num) & MASK;
    size_t pos = first_pos;
    for (size_t i = 0; i < num; ++i)
    {
        ptr[(pos++) & MASK] = *(it_src++);
    };
};
//
//------------------------------------------------------------------------
//  function : push_move_front
/// @brief move num elements in the front of the buffer
/// @param p1 : iterator from where begin to move the elements
/// @param mun : number of element to move
//-----------------------------------------------------------------------
template <class Value_t, uint32_t Power2>
template<class iter_t>
void circular_buffer<Value_t, Power2>
::push_move_front(iter_t it_src, size_t num)
{
    static_assert ( std::is_same <value_iter<iter_t>, Value_t>::value,
                    "Incompatible iterator");
    if (num == 0) return;
#ifdef __BS_DEBUG
    assert ( free_size() >= num);
#endif
    nelem += num;
    size_t pos = first_pos;
    for (size_t i = 0; i < num; ++i)
    {
        ptr[(pos++) & MASK] = std::move(*(it_src++));
    };
};
//
//------------------------------------------------------------------------
//  function : push_copy_back
/// @brief copy num elements in the back of the buffer
/// @param p1 : iterator from where begin to copy the elements
/// @param mun : number of element to copy
//-----------------------------------------------------------------------
template <class Value_t, uint32_t Power2>
template<class iter_t>
void circular_buffer<Value_t, Power2>
::push_copy_back(iter_t it_src, size_t num)
{
    static_assert ( std::is_same <value_iter<iter_t>, Value_t>::value,
                    "Incompatible iterator");
    if (num == 0) return;
#ifdef __BS_DEBUG
    assert ( free_size() >= num);
#endif
    size_t pos = first_pos + nelem;
    nelem += num;
    for (size_t i = 0; i < num; ++i)
    {
        ptr[(pos++) & MASK] = *(it_src++);
    };
};
//
//------------------------------------------------------------------------
//  function : push_move_back
/// @brief move num elements in the back of the buffer
/// @param p1 : iterator from where begin to move the elements
/// @param mun : number of element to move
//-----------------------------------------------------------------------
template <class Value_t, uint32_t Power2>
template<class iter_t>
void circular_buffer<Value_t, Power2>
::push_move_back(iter_t it_src, size_t num)
{
    static_assert ( std::is_same <value_iter<iter_t>, Value_t>::value,
                    "Incompatible iterator");
    if (num == 0) return;
#ifdef __BS_DEBUG
    assert ( free_size() >= num);
#endif
    size_t pos = first_pos + nelem;
    nelem += num;
    for (size_t i = 0; i < num; ++i)
    {
        ptr[(pos++) & MASK] = std::move(*(it_src++));
    };
};

//****************************************************************************
};// End namespace util
};// End namespace common
};// End namespace sort
};// End namespace boost
//****************************************************************************
#endif

/* circular_buffer.hpp
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
*/