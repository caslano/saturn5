//----------------------------------------------------------------------------
/// @file   deque_cnc.hpp
/// @brief  This file contains the implementation of the several types of
///         recursive fastmutex for read and write
///
/// @author Copyright (c) 2010 2015 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __TOOLS_DEQUE_CNC_HPP
#define __TOOLS_DEQUE_CNC_HPP

#include <sort/tools/spinlock.hpp>
#include <vector>
#include <deque>

namespace sort
{
namespace tools
{

//###########################################################################
//                                                                         ##
//    ################################################################     ##
//    #                                                              #     ##
//    #                      C L A S S                               #     ##
//    #                   S T A C K _ C N C                          #     ##
//    #                                                              #     ##
//    ################################################################     ##
//                                                                         ##
//###########################################################################
//
//---------------------------------------------------------------------------
/// @class  deque_cnc
/// @brief This class is a concurrent stack controled by a spin_lock
/// @remarks
//---------------------------------------------------------------------------
template<typename T, typename Allocator = std::allocator<T> >
class deque_cnc
{
public:
    //-----------------------------------------------------------------------
    //                     D E F I N I T I O N S
    //-----------------------------------------------------------------------
    typedef std::deque<T, Allocator>                deque_t;
    typedef typename deque_t::size_type             size_type;
    typedef typename deque_t::difference_type       difference_type;
    typedef typename deque_t::value_type            value_type;
    typedef typename deque_t::pointer               pointer;
    typedef typename deque_t::const_pointer         const_pointer;
    typedef typename deque_t::reference             reference;
    typedef typename deque_t::const_reference       const_reference;
    typedef typename deque_t::allocator_type        allocator_type;

protected:
    //------------------------------------------------------------------------
    //                     VARIABLES
    //------------------------------------------------------------------------
    deque_t dq;
    mutable spinlock spl;

public:
    //
    //-----------------------------------------------------------------------
    //  C O N S T R U C T O R S     A N D    D E S T R U C T O R
    //-----------------------------------------------------------------------
    //
    //-----------------------------------------------------------------------
    //  function : deque_cnc
    /// @brief  constructor
    //----------------------------------------------------------------------
    explicit inline deque_cnc(void): dq() { };
//
    //----------------------------------------------------------------------
    //  function : deque_cnc
    /// @brief  constructor
    /// @param [in] ALLC : Allocator
    //----------------------------------------------------------------------
    explicit inline deque_cnc(const Allocator &ALLC): dq(ALLC){ };
    //
    //----------------------------------------------------------------------
    //  function : ~deque_cnc
    /// @brief  Destructor
    //----------------------------------------------------------------------
    virtual ~deque_cnc(void){ dq.clear(); };
    //
    //----------------------------------------------------------------------
    //  function : clear
    /// @brief Delete all the elements of the deque_cnc.
    //----------------------------------------------------------------------
    void clear(void)
    {
        std::lock_guard < spinlock > S(spl);
        dq.clear();
    };
    //
    //------------------------------------------------------------------------
    //  function : swap
    /// @brief swap the data between the two deque_cnc
    /// @param [in] A : deque_cnc to swap
    /// @return none
    //-----------------------------------------------------------------------
    void swap(deque_cnc & A) noexcept
    {
        if (this == &A) return;
        std::lock_guard < spinlock > S(spl);
        dq.swap(A.dq);
    };
    //
    //-----------------------------------------------------------------------
    //  S I Z E , M A X _ S I Z E , R E S I Z E
    //  C A P A C I T Y , E M P T Y , R E S E R V E
    //-----------------------------------------------------------------------
    //
    //------------------------------------------------------------------------
    //  function : size
    /// @brief return the number of elements in the deque_cnc
    /// @return number of elements in the deque_cnc
    //------------------------------------------------------------------------
    size_type size(void) const noexcept
    {
        std::lock_guard < spinlock > S(spl);
        return dq.size();
    };
    //
    //------------------------------------------------------------------------
    //  function :max_size
    /// @brief return the maximun size of the container
    /// @return maximun size of the container
    //------------------------------------------------------------------------
    size_type max_size(void) const noexcept
    {
        std::lock_guard < spinlock > S(spl);
        return (dq.max_size());
    };
    //
    //-------------------------------------------------------------------------
    //  function : shrink_to_fit
    /// @brief resize the current vector size and change to size.\n
    ///        If sz is smaller than the current size, delete elements to end\n
    ///        If sz is greater than the current size, insert elements to the
    ///        end with the value c
    /// @param [in] sz : new size of the deque_cnc after the resize
    /// @param [in] c : Value to insert if sz is greather than the current size
    /// @return none
    //------------------------------------------------------------------------
    void shrink_to_fit()
    {
        std::lock_guard < spinlock > S(spl);
        dq.shrink_to_fit();
    };
    //
    //------------------------------------------------------------------------
    //  function : empty
    /// @brief indicate if the map is empty
    /// @return true if the map is empty, false in any other case
    //------------------------------------------------------------------------
    bool empty(void) const noexcept
    {
        std::lock_guard < spinlock > S(spl);
        return (dq.empty());
    };
    //---------------------------------------------------------------------------
    //  function : push_back
    /// @brief Insert one element in the back of the container
    /// @param [in] D : value to insert. Can ve a value, a reference or an
    ///                 rvalue
    //---------------------------------------------------------------------------
    void push_back(const value_type & D)
    {
        std::lock_guard < spinlock > S(spl);
        dq.push_back(D);
    };

    //------------------------------------------------------------------------
    //  function : emplace_back
    /// @brief Insert one element in the back of the container
    /// @param [in] args :group of arguments for to build the object to insert
    //-------------------------------------------------------------------------
    template<class ... Args>
    void emplace_back(Args && ... args)
    {
        std::lock_guard < spinlock > S(spl);
        dq.emplace_back(std::forward <Args>(args) ...);
    };
    //------------------------------------------------------------------------
    //  function : push_back
    /// @brief Insert one element in the back of the container
    /// @param [in] D : deque to insert in the actual deque, inserting a copy
    ///                  of the elements
    /// @return reference to the deque after the insertion
    //------------------------------------------------------------------------
    template<class Allocator2>
    deque_cnc & push_back(const std::deque<value_type, Allocator2> & D)
    {
        std::lock_guard < spinlock > S(spl);
        for (size_type i = 0; i < D.size(); ++i)
            dq.push_back(D[i]);
        return *this;
    };
    //------------------------------------------------------------------------
    //  function : push_back
    /// @brief Insert one element in the back of the container
    /// @param [in] D : deque to insert in the actual deque, inserting a move
    ///                 of the elements
    /// @return reference to the deque after the insertion
    //------------------------------------------------------------------------
    deque_cnc & push_back(std::deque<value_type, Allocator> && D)
    {
        std::lock_guard < spinlock > S(spl);
        for (size_type i = 0; i < D.size(); ++i)
            dq.emplace_back(std::move(D[i]));
        return *this;
    };
    //
    //------------------------------------------------------------------------
    //  function :pop_back
    /// @brief erase the last element of the container
    //-----------------------------------------------------------------------
    void pop_back(void)
    {
        std::lock_guard < spinlock > S(spl);
        dq.pop_back();
    };
    //
    //------------------------------------------------------------------------
    //  function :pop_copy_back
    /// @brief erase the last element and return a copy over P
    /// @param [out] P : reference to a variable where copy the element
    /// @return code of the operation
    ///         true - Element erased
    ///         false - Empty tree
    //------------------------------------------------------------------------
    bool pop_copy_back(value_type & P)
    {   //-------------------------- begin -----------------------------
        std::lock_guard < spinlock > S(spl);
        if (dq.size() == 0) return false;
        P = dq.back();
        dq.pop_back();
        return true;
    };
    //
    //------------------------------------------------------------------------
    //  function :pop_move_back
    /// @brief erase the last element and move over P
    /// @param [out] P : reference to a variable where move the element
    /// @return code of the operation
    ///         true - Element erased
    ///         false - Empty tree
    //------------------------------------------------------------------------
    bool pop_move_back(value_type & P)
    {   //-------------------------- begin -----------------------------
        std::lock_guard < spinlock > S(spl);
        if (dq.size() == 0) return false;
        P = std::move(dq.back());
        dq.pop_back();
        return true;
    };

    //------------------------------------------------------------------------
    //  function : push_front
    /// @brief Insert one copy of the element in the front of the container
    /// @param [in] D : value to insert
    //------------------------------------------------------------------------
    void push_front(const value_type & D)
    {
        std::lock_guard < spinlock > S(spl);
        dq.push_front(D);
    };

    //------------------------------------------------------------------------
    //  function : emplace_front
    /// @brief Insert one element in the front of the container
    /// @param [in] args :group of arguments for to build the object to insert
    //-------------------------------------------------------------------------
    template<class ... Args>
    void emplace_front(Args && ... args)
    {
        std::lock_guard < spinlock > S(spl);
        dq.emplace_front(std::forward <Args>(args) ...);
    };
    //------------------------------------------------------------------------
    //  function : push_front
    /// @brief Insert a copy of the elements of the deque V1 in the front
    ///        of the container
    /// @param [in] V1 : deque with the elements to insert
    /// @return reference to the deque after the insertion
    //------------------------------------------------------------------------
    template<class Allocator2>
    deque_cnc & push_front(const std::deque<value_type, Allocator2> & V1)
    {
        std::lock_guard < spinlock > S(spl);
        for (size_type i = 0; i < V1.size(); ++i)
            dq.push_front(V1[i]);
        return *this;
    };
    //-----------------------------------------------------------------------
    //  function : push_front
    /// @brief Insert a move of the elements of the deque V1 in the front
    ///        of the container
    /// @param [in] V1 : deque with the elements to insert
    /// @return reference to the deque after the insertion
    //-----------------------------------------------------------------------
    deque_cnc & push_front(std::deque<value_type, Allocator> && V1)
    {
        std::lock_guard < spinlock > S(spl);
        for (size_type i = 0; i < V1.size(); ++i)
            dq.emplace_front(std::move(V1[i]));
        return *this;
    };
    //
    //-----------------------------------------------------------------------
    //  function :pop_front
    /// @brief erase the first element of the container
    //-----------------------------------------------------------------------
    void pop_front(void)
    {
        std::lock_guard < spinlock > S(spl);
        dq.pop_front();
    };
    //
    //-----------------------------------------------------------------------
    //  function :pop_copy_front
    /// @brief erase the first element of the tree and return a copy over P
    /// @param [out] P : reference to a variable where copy the element
    /// @return code of the operation
    ///         true- Element erased
    ///         false - Empty tree
    //-----------------------------------------------------------------------
    bool pop_copy_front(value_type & P)
    {   //-------------------------- begin -----------------------------
        std::lock_guard < spinlock > S(spl);
        if (dq.size() == 0) return false;
        P = dq.front();
        dq.pop_front();
        return true;
    };
    //
    //------------------------------------------------------------------------
    //  function :pop_move_front
    /// @brief erase the first element of the tree and return a move over P
    /// @param [out] P : reference to a variable where move the element
    /// @return code of the operation
    ///         true- Element erased
    ///         false - Empty tree
    //------------------------------------------------------------------------
    bool pop_move_front(value_type & P)
    {   //-------------------------- begin -----------------------------
        std::lock_guard < spinlock > S(spl);
        if (dq.size() == 0) return false;
        P = std::move(dq.front());
        dq.pop_front();
        return true;
    };
};
// end class deque_cnc

//***************************************************************************
};// end namespace tools
};// end namespace sort
//***************************************************************************
#endif

/* deque_cnc.hpp
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
*/