//----------------------------------------------------------------------------
/// @file   scheduler.hpp
/// @brief  This file contains the implementation of the scheduler for
///         dispatch the works stored
///
/// @author Copyright (c) 2010 2015 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __BOOST_SORT_COMMON_SCHEDULER_HPP
#define __BOOST_SORT_COMMON_SCHEDULER_HPP

#include <boost/sort/common/spinlock.hpp>
#include <boost/sort/common/search.hpp>
#include <boost/sort/common/compare_traits.hpp>
#include <scoped_allocator>
#include <utility>
#include <vector>
#include <deque>
#include <iostream>
#include <unordered_map>

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
//    #           C L A S S      S C H E D U L E R                   #     ##
//    #                                                              #     ##
//    ################################################################     ##
//                                                                         ##
//###########################################################################

//
//---------------------------------------------------------------------------
/// @class  scheduler
/// @brief This class is a concurrent stack controled by a spin_lock
/// @remarks
//---------------------------------------------------------------------------
template<typename Func_t, typename Allocator = std::allocator<Func_t> >
struct scheduler
{
    //-----------------------------------------------------------------------
    //                     D E F I N I T I O N S
    //-----------------------------------------------------------------------
    typedef std::scoped_allocator_adaptor <Allocator>   scoped_alloc;
    typedef std::deque <Func_t, scoped_alloc>           deque_t;
    typedef typename deque_t::iterator                  it_deque;
    typedef std::thread::id                             key_t;
    typedef std::hash <key_t>                           hash_t;
    typedef std::equal_to <key_t>                       equal_t;
    typedef std::unique_lock <spinlock_t>               lock_t;
    typedef std::unordered_map <key_t, deque_t, hash_t, 
                        equal_t, scoped_alloc>          map_t;
    typedef typename map_t::iterator                    it_map;

    //-----------------------------------------------------------------------
    //                     V A R I A B L E S
    //-----------------------------------------------------------------------
    map_t mp;
    size_t nelem;
    mutable spinlock_t spl;

    //------------------------------------------------------------------------
    //  function : scheduler
    /// @brief  constructor
    //------------------------------------------------------------------------
    scheduler(void) : mp(), nelem(0)  { };
    //
    //-----------------------------------------------------------------------
    //  function : scheduler
    /// @brief  Copy & move constructor
    /// @param [in] VT : stack_cnc from where copy the data
    //-----------------------------------------------------------------------
    scheduler(scheduler && VT) = delete;
    scheduler(const scheduler & VT) = delete;
    //
    //------------------------------------------------------------------------
    //  function : ~scheduler
    /// @brief  Destructor
    //------------------------------------------------------------------------
    virtual ~scheduler(void) {mp.clear();};
    //
    //------------------------------------------------------------------------
    //  function : operator =
    /// @brief Asignation operator
    /// @param [in] VT : stack_cnc from where copy the data
    /// @return Reference to the stack_cnc after the copy
    //------------------------------------------------------------------------
    scheduler & operator=(const scheduler &VT) = delete;
    //
    //------------------------------------------------------------------------
    //  function : size
    /// @brief Asignation operator
    /// @param [in] VT : stack_cnc from where copy the data
    /// @return Reference to the stack_cnc after the copy
    //------------------------------------------------------------------------
    size_t size(void) const
    {
        lock_t s(spl);
        return nelem;
    };
    //
    //------------------------------------------------------------------------
    //  function : clear
    /// @brief Delete all the elements of the stack_cnc.
    //------------------------------------------------------------------------
    void clear_all(void)
    {
        lock_t s(spl);
        mp.clear();
        nelem = 0;
    };

    //
    //------------------------------------------------------------------------
    //  function : insert
    /// @brief Insert one element in the back of the container
    /// @param [in] D : value to insert. Can ve a value, a reference or an
    ///                 rvalue
    /// @return iterator to the element inserted
    /// @remarks This operation is O ( const )
    //------------------------------------------------------------------------
    void insert(Func_t & f)
    {
        lock_t s(spl);
        key_t th_id = std::this_thread::get_id();
        it_map itmp = mp.find(th_id);
        if (itmp == mp.end())
        {
            auto aux = mp.emplace(th_id, deque_t());
            if (aux.second == false) throw std::bad_alloc();
            itmp = aux.first;
        };
        itmp->second.emplace_back(std::move(f));
        nelem++;
    };

    //
    //------------------------------------------------------------------------
    //  function :emplace
    /// @brief Insert one element in the back of the container
    /// @param [in] args :group of arguments for to build the object to insert
    /// @return iterator to the element inserted
    /// @remarks This operation is O ( const )
    //------------------------------------------------------------------------
    template<class ... Args>
    void emplace(Args && ... args)
    {
        lock_t s(spl);
        key_t th_id = std::this_thread::get_id();
        it_map itmp = mp.find(th_id);
        if (itmp == mp.end())
        {
            auto aux = mp.emplace(th_id, deque_t());
            if (aux.second == false) throw std::bad_alloc();
            itmp = aux.first;
        };
        itmp->second.emplace_back(std::forward <Args>(args) ...);
        nelem++;
    };
    //
    //------------------------------------------------------------------------
    //  function : insert
    /// @brief Insert one element in the back of the container
    /// @param [in] D : value to insert. Can ve a value, a reference or an rvalue
    /// @return iterator to the element inserted
    /// @remarks This operation is O ( const )
    //------------------------------------------------------------------------
    template<class it_func>
    void insert_range(it_func first, it_func last)
    {
        //--------------------------------------------------------------------
        //                    Metaprogramming
        //--------------------------------------------------------------------
        typedef value_iter<it_func> value2_t;
        static_assert (std::is_same< Func_t, value2_t >::value,
                        "Incompatible iterators\n");

        //--------------------------------------------------------------------
        //                     Code
        //--------------------------------------------------------------------
        assert((last - first) > 0);

        lock_t s(spl);
        key_t th_id = std::this_thread::get_id();
        it_map itmp = mp.find(th_id);
        if (itmp == mp.end())
        {
            auto aux = mp.emplace(th_id, deque_t());
            if (aux.second == true) throw std::bad_alloc();
            itmp = aux.first;
        };
        while (first != last)
        {
            itmp->second.emplace_back(std::move(*(first++)));
            nelem++;
        };
    };
    //
    //------------------------------------------------------------------------
    //  function : extract
    /// @brief erase the last element of the tree and return a copy
    /// @param [out] V : reference to a variable where copy the element
    /// @return code of the operation
    ///         0- Element erased
    ///         1 - Empty tree
    /// @remarks This operation is O(1)
    //------------------------------------------------------------------------
    bool extract(Func_t & f)
    {
        lock_t s(spl);
        if (nelem == 0) return false;
        key_t th_id = std::this_thread::get_id();
        it_map itmp = mp.find(th_id);
        if (itmp != mp.end() and not itmp->second.empty())
        {
            f = std::move(itmp->second.back());
            itmp->second.pop_back();
            --nelem;
            return true;
        };
        for (itmp = mp.begin(); itmp != mp.end(); ++itmp)
        {
            if (itmp->second.empty()) continue;
            f = std::move(itmp->second.back());
            itmp->second.pop_back();
            --nelem;
            return true;
        }
        return false;
    };
};
// end class scheduler
//*************************************************************************
//               P R I N T      F U N C T I O N S
//************************************************************************
template<class ... Args>
std::ostream & operator <<(std::ostream &out, const std::deque<Args ...> & dq)
{
    for (uint32_t i = 0; i < dq.size(); ++i)
        out << dq[i] << " ";
    out << std::endl;
    return out;
}

template<typename Func_t, typename Allocator = std::allocator<Func_t> >
std::ostream & operator <<(std::ostream &out,
                           const scheduler<Func_t, Allocator> &sch)
{
    std::unique_lock < spinlock_t > s(sch.spl);
    out << "Nelem :" << sch.nelem << std::endl;
    for (auto it = sch.mp.begin(); it != sch.mp.end(); ++it)
    {
        out << it->first << "  :" << it->second << std::endl;
    }
    return out;
}

//***************************************************************************
};// end namespace common
};// end namespace sort
};// end namespace boost
//***************************************************************************
#endif

/* scheduler.hpp
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
*/