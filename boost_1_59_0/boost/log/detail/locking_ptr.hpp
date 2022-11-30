/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   locking_ptr.hpp
 * \author Andrey Semashev
 * \date   15.07.2009
 *
 * This header is the Boost.Log library implementation, see the library documentation
 * at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_LOCKING_PTR_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_LOCKING_PTR_HPP_INCLUDED_

#include <cstddef>
#include <boost/move/core.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/thread/lock_options.hpp>
#include <boost/core/explicit_operator_bool.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! A pointer type that locks the backend until it's destroyed
template< typename T, typename LockableT >
class locking_ptr
{
    typedef locking_ptr this_type;
    BOOST_COPYABLE_AND_MOVABLE_ALT(this_type)

public:
    //! Pointed type
    typedef T element_type;

private:
    //! Lockable type
    typedef LockableT lockable_type;

private:
    //! The pointer to the backend
    shared_ptr< element_type > m_pElement;
    //! Reference to the shared lock control object
    lockable_type* m_pLock;

public:
    //! Default constructor
    locking_ptr() BOOST_NOEXCEPT : m_pLock(NULL)
    {
    }
    //! Constructor
    locking_ptr(shared_ptr< element_type > const& p, lockable_type& l) : m_pElement(p), m_pLock(&l)
    {
        m_pLock->lock();
    }
    //! Constructor
    locking_ptr(shared_ptr< element_type > const& p, lockable_type& l, try_to_lock_t const&) : m_pElement(p), m_pLock(&l)
    {
        if (!m_pLock->try_lock())
        {
            m_pElement.reset();
            m_pLock = NULL;
        }
    }
    //! Copy constructor
    locking_ptr(locking_ptr const& that) : m_pElement(that.m_pElement), m_pLock(that.m_pLock)
    {
        if (m_pLock)
            m_pLock->lock();
    }
    //! Move constructor
    locking_ptr(BOOST_RV_REF(this_type) that) BOOST_NOEXCEPT : m_pLock(that.m_pLock)
    {
        m_pElement.swap(that.m_pElement);
        that.m_pLock = NULL;
    }

    //! Destructor
    ~locking_ptr()
    {
        if (m_pLock)
            m_pLock->unlock();
    }

    //! Assignment
    locking_ptr& operator= (locking_ptr that) BOOST_NOEXCEPT
    {
        this->swap(that);
        return *this;
    }

    //! Indirection
    element_type* operator-> () const BOOST_NOEXCEPT { return m_pElement.get(); }
    //! Dereferencing
    element_type& operator* () const BOOST_NOEXCEPT { return *m_pElement; }

    //! Accessor to the raw pointer
    element_type* get() const BOOST_NOEXCEPT { return m_pElement.get(); }

    //! Checks for null pointer
    BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()
    //! Checks for null pointer
    bool operator! () const BOOST_NOEXCEPT { return !m_pElement; }

    //! Swaps two pointers
    void swap(locking_ptr& that) BOOST_NOEXCEPT
    {
        m_pElement.swap(that.m_pElement);
        lockable_type* p = m_pLock;
        m_pLock = that.m_pLock;
        that.m_pLock = p;
    }
};

//! Free raw pointer getter to assist generic programming
template< typename T, typename LockableT >
inline T* get_pointer(locking_ptr< T, LockableT > const& p) BOOST_NOEXCEPT
{
    return p.get();
}
//! Free swap operation
template< typename T, typename LockableT >
inline void swap(locking_ptr< T, LockableT >& left, locking_ptr< T, LockableT >& right) BOOST_NOEXCEPT
{
    left.swap(right);
}

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_LOCKING_PTR_HPP_INCLUDED_

/* locking_ptr.hpp
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
*/