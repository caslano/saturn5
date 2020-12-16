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
OAq2gaNhW7gMtoMrYHt4H+wId8JO8NewC3wCdtN8TIX7YQ/4IkzTcO+x23rKvYY7HsEvOW7DXhi8U8N9l4b7bg33PfA8+GPYCd4LR8D74GS4CU6Dm+FVcCu8Gd4Pb4Hb4D3wQfgruB3ugT/TcO/Qcvcr+DzcCQ/BR+AR+GuY/k/OW4f24lR//vp/eS9OO+axByOZofnsb/34Xp7//cprv4X3//71/+0a8c5ujWlQekYGnrMyZi0uNmT9f1sGsLvc1wqzL88oog+T680a0u+vDVxf4rYg139KB56v14vd12Xu4UrHtwc26HigpqZjDeQMHUtmpD5bqPucorPuEbhQ3plz768ZO5+SsOfm8RYcd24dwdE+7/ul6/2sCOHwnHsSrPv1Xlv5/VZUcr98637FVbqfK37jve6n6XmHzuUkqcNGyFh/Jxq4X1ZqToaVpjLPMVSe02Z5Po/hxn5GOiG6knMWGZ7PYm67sbLGg9UK3rqMsevWt3B1/XPv/7D09xJe+da09cxKuDiXcIlZtBAzub/7OXay6k/4I2Ii+zVtNjrTRvODS870sZ8L3xS7HT3Ta2OF9MrP90wvh91YZ3rNK5pveKcZ9suvWcma75xH2ibXn5Y1K93UXru0gL1ih16C34m9+2ktfLgdU38D5eUQgb8qmfvE1YsOSzCc+YKtsfVVd7msaWmt8gjXNsSIVMi76GrlXSCNEtx5p2nhLttFNSuW7Y7EcWNtO/9yFhVlEOFA3rVPq7Rs46bqZXtj7aqX7Y21q1W2L3SmT/u06pdt6xvkERGa4Orx+UhrEqgswtINwrol15ot+h6WDuXkLbLnTk+J3QHMz9Rl/B3jmW74Z6fFBQ2ljC+ZlRucc4mX8pXgkY5ut58H0rzIs7y77eqaruxili55ruey7ZLmPrucVkx3vDnLGis7Pez0J36YS/zs9CfcmEm4MXOurZLwucrrMc2TBL1pPNKZPN4TKK85qVnutvjFytti3JT/9gQ6/Cspr3vKlcGSarSvL7rrqOpg517l2tJi/eb9SqQ2cpXG7agdN2db6j2HGws/Evudvb8v745z5e1pObsttN1bonYP6vcb2qh5sZqfUPNmEqPZti77w5jH0jYex+OySOqwv21ssMCRntoukqadKk/TyudaK+q2lzASbswId8BMwtdGzYrV7LD9XQQJr6u8jY+qWN664b40ysoTd/vYtfL2ETdVL2+lUdUqb642jzCctbydgpO/hznJn3bym9c9EL1mbsu3Bn76eI+H4xeOml/9ucqo203Mn212l7H2nuJf9xuZtvyNBceahuYq/1PnKk/LnJUcMgbaBscgVzt+n0Q45ZnE/f16E4lDDJ2/suyln8XeIIe9/LPYG+GwV6L2kjzstVN7ZfYYUca37u/Lq356E06AEXAirAOLYD04GbaDU2AnOBWmwWmwj9rrp/OoQ2AGHAMz4cVwDhwPs+BUmA0z4VyIyHzqIpijevUvgyVwAVwLc+EP4UJ4L1wEfwHz4C5YAPfBQrhfw6Ppw5ir8vQZo/aKrXECvEDtRSO5ai8Oe37Ga/okwAawoWP+sjFMgsmwMewKm2g6NYX91F5/2Byer+caTu2X8fss+Tjf6svgSrVXG5mOcMi8cW24HNZXnUGD4DWaL9fCC+F1cBa8Hs6Bq+ECuBZeBW9whIv2W8PlnX4bzjL/2OTuSHsOsje/b4OTYTHSv0mYkY4UrfOam8T9U/9b85NN9n63c5T99557njJ9b2CuMn/vf/985R2UoZ3IAeQEErGB770jg5HxSD6ybkNoLjN0hI7QETpCR+gIHaEjdISO0PH9Ht/P+3+23s//dtb/X2O/g9eJIY4UxES6Iqk=
*/