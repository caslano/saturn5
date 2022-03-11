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