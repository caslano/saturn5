//----------------------------------------------------------------------------
/// @file   stack_cnc.hpp
/// @brief  This file contains the implementation concurrent stack
///
/// @author Copyright (c) 2010 2015 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __BOOST_SORT_PARALLEL_DETAIL_UTIL_STACK_CNC_HPP
#define __BOOST_SORT_PARALLEL_DETAIL_UTIL_STACK_CNC_HPP

#include <boost/sort/common/spinlock.hpp>
#include <vector>

namespace boost
{
namespace sort
{
namespace common
{

//
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
/// @class  stack_cnc
/// @brief This class is a concurrent stack controled by a spin_lock
/// @remarks
//---------------------------------------------------------------------------
template<typename T, typename Allocator = std::allocator<T> >
class stack_cnc
{
public:
    //------------------------------------------------------------------------
    //                     D E F I N I T I O N S
    //------------------------------------------------------------------------
    typedef std::vector<T, Allocator> vector_t;
    typedef typename vector_t::size_type size_type;
    typedef typename vector_t::difference_type difference_type;
    typedef typename vector_t::value_type value_type;
    typedef typename vector_t::pointer pointer;
    typedef typename vector_t::const_pointer const_pointer;
    typedef typename vector_t::reference reference;
    typedef typename vector_t::const_reference const_reference;
    typedef typename vector_t::allocator_type allocator_type;
    typedef Allocator alloc_t;

protected:
    //-------------------------------------------------------------------------
    //                   INTERNAL VARIABLES
    //-------------------------------------------------------------------------
    vector_t v_t;
    mutable spinlock_t spl;

public:
    //
    //-------------------------------------------------------------------------
    //  function : stack_cnc
    /// @brief  constructor
    //-------------------------------------------------------------------------
    explicit stack_cnc(void): v_t() { };

    //
    //-------------------------------------------------------------------------
    //  function : stack_cnc
    /// @brief  Move constructor
    //-------------------------------------------------------------------------
    stack_cnc(stack_cnc &&) = delete;
    //
    //-------------------------------------------------------------------------
    //  function : ~stack_cnc
    /// @brief  Destructor
    //-------------------------------------------------------------------------
    virtual ~stack_cnc(void) { v_t.clear(); };

    //-------------------------------------------------------------------------
    //  function : emplace_back
    /// @brief Insert one element in the back of the container
    /// @param args : group of arguments for to build the object to insert. Can
    ///               be values, references or rvalues
    //-------------------------------------------------------------------------
    template<class ... Args>
    void emplace_back(Args &&... args)
    {
        std::lock_guard < spinlock_t > guard(spl);
        v_t.emplace_back(std::forward< Args > (args)...);
    };

    //
    //-------------------------------------------------------------------------
    //  function :pop_move_back
    /// @brief if exist, move the last element to P, and delete it
    /// @param P : reference to a variable where move the element
    /// @return  true  - Element moved and deleted
    ///          false - Empty stack_cnc
    //-------------------------------------------------------------------------
    bool pop_move_back(value_type &P)
    {
        std::lock_guard < spinlock_t > S(spl);
        if (v_t.size() == 0) return false;
        P = std::move(v_t.back());
        v_t.pop_back();
        return true;
    };
    //-------------------------------------------------------------------------
    //  function : push_back
    /// @brief Insert one vector at the end of the container
    /// @param v_other : vector to insert
    /// @return reference to the stack_cnc after the insertion
    //-------------------------------------------------------------------------
    template<class Allocator2>
    stack_cnc &push_back(const std::vector<value_type, Allocator2> &v_other)
    {
        std::lock_guard < spinlock_t > guard(spl);
        for (size_type i = 0; i < v_other.size(); ++i)
        {
            v_t.push_back(v_other[i]);
        }
        return *this;
    };
};
// end class stack_cnc

//***************************************************************************
};// end namespace common
};// end namespace sort
};// end namespace boost
//***************************************************************************
#endif

/* stack_cnc.hpp
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
*/