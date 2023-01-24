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
vZzzlsML2w2uZPFzaNbHObB33nQ1b5fQux6M13TI45+ZnAdEpwfB+zUYM7t02EeL+4e48y2ODOA2zwBu200BnKAvQZbAZ18iUSwINxbh12upBuslN5NXwp4bW0CK5xuIc7QIeeRcWOZS2+lsZ5fGA36XDOvjn96m64gaqulJ0Rbmm1SFc59fp3WlIT1HQbzTs6Db7VwvnB11o4U48K04ihhf53G604PPU88MnIk8921EerpGFu9gNky6bjodiZ54Vr9LCRm50cGhXH9B+iYlzoxv3R+hLEhugS83fwrKM3wmyiPoR/watETowvdqsha2wdd+FNQPVT7AT7H9sT+Php5mFTagAJcznn19PoMb3czOtzNFtJv+cGogE6Ec2wswZ3x1jM+7Bi3zAzsddRtTz2GcsQFPZ3X2PcHhWrbZDvjx2eC1wigOD1YAPuwKM7A+eu9uST3ZXAtcuh75KZq4kRqng/mnWA0dpM+nkjRBe3SKN2MeVs79ONgmvP2Ba2Y6YjZwHn8pxrqTweumQT5W1DN4iC7L0xE1xtv5ixi+hDamwxOIwe5z0Djtcsyl/f8hJQr4MTh3I08sEC9NALbUgL2D/rkcVmL1rii3e4V7gMDX6aAvrF8dgp+/jOFiDKCT/Z5AnunMDJ4BuKEzeIfDx+B7C6EbfJBYYrc5rEL+S/OgB/1yqXCyH7jPAZxTj3l89wjx9AC+Ec8YMI9/
*/