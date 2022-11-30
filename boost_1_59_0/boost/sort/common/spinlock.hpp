//----------------------------------------------------------------------------
/// @file spinlock_t.hpp
/// @brief
///
/// @author Copyright (c) 2010 2015 Francisco José Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanyingfile LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
/// @remarks
//-----------------------------------------------------------------------------
#ifndef __BOOST_SORT_PARALLEL_DETAIL_UTIL_SPINLOCK_HPP
#define __BOOST_SORT_PARALLEL_DETAIL_UTIL_SPINLOCK_HPP

#include <atomic>
#include <ctime>
#include <functional>
#include <memory>
#include <mutex>
#include <thread>

namespace boost
{
namespace sort
{
namespace common
{
//
//---------------------------------------------------------------------------
/// @class spinlock_t
/// @brief This class implement, from atomic variables, a spinlock
/// @remarks This class meet the BasicLockable requirements ( lock, unlock )
//---------------------------------------------------------------------------
class spinlock_t
{
  private:
    //------------------------------------------------------------------------
    //             P R I V A T E      V A R I A B L E S
    //------------------------------------------------------------------------
    std::atomic_flag af;

  public:
    //
    //-------------------------------------------------------------------------
    //  function : spinlock_t
    /// @brief  class constructor
    /// @param [in]
    //-------------------------------------------------------------------------
    explicit spinlock_t ( ) noexcept { af.clear ( ); };
    //
    //-------------------------------------------------------------------------
    //  function : lock
    /// @brief  Lock the spinlock_t
    //-------------------------------------------------------------------------
    void lock ( ) noexcept
    {
    	while (af.test_and_set (std::memory_order_acquire))
        {
            std::this_thread::yield ( );
        };
    };
    //
    //-------------------------------------------------------------------------
    //  function : try_lock
    /// @brief Try to lock the spinlock_t, if not, return false
    /// @return true : locked
    ///         false: not previous locked
    //-------------------------------------------------------------------------
    bool try_lock ( ) noexcept
    {
        return not af.test_and_set (std::memory_order_acquire);
    };
    //
    //-------------------------------------------------------------------------
    //  function : unlock
    /// @brief  unlock the spinlock_t
    //-------------------------------------------------------------------------
    void unlock ( ) noexcept { af.clear (std::memory_order_release); };

}; // E N D    C L A S S     S P I N L O C K
//
//***************************************************************************
}; // end namespace common
}; // end namespace sort
}; // end namespace boost
//***************************************************************************
#endif

/* spinlock.hpp
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
*/