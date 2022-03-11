/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   utility/strictest_lock.hpp
 * \author Andrey Semashev
 * \date   30.05.2010
 *
 * The header contains definition of the \c strictest_lock metafunction that
 * allows to select a lock with the strictest access requirements.
 */

#ifndef BOOST_LOG_UTILITY_STRICTEST_LOCK_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_STRICTEST_LOCK_HPP_INCLUDED_

#include <boost/mpl/integral_c.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/locks.hpp>
#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/repetition/enum_trailing.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/log/detail/pp_identity.hpp>
#endif
#if defined(BOOST_LOG_BROKEN_CONSTANT_EXPRESSIONS)
#include <boost/mpl/less.hpp>
#endif
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#if !defined(BOOST_LOG_STRICTEST_LOCK_LIMIT)
/*!
 * The macro defines the maximum number of template arguments that the \c strictest_lock
 * metafunction accepts. Should not be less than 2.
 */
#define BOOST_LOG_STRICTEST_LOCK_LIMIT 10
#endif // BOOST_LOG_STRICTEST_LOCK_LIMIT
#if BOOST_LOG_STRICTEST_LOCK_LIMIT < 2
#error The BOOST_LOG_STRICTEST_LOCK_LIMIT macro should not be less than 2
#endif
#endif // defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! Access modes for different types of locks
enum lock_access_mode
{
    unlocked_access,    //!< A thread that owns this kind of lock doesn't restrict other threads in any way
    shared_access,      //!< A thread that owns this kind of lock requires that no other thread modify the locked data
    exclusive_access    //!< A thread that owns this kind of lock requires that no other thread has access to the locked data
};

//! The trait allows to select an access mode by the lock type
template< typename LockT >
struct thread_access_mode_of;

template< typename MutexT >
struct thread_access_mode_of< no_lock< MutexT > > : mpl::integral_c< lock_access_mode, unlocked_access >
{
};

#if !defined(BOOST_LOG_NO_THREADS)

template< typename MutexT >
struct thread_access_mode_of< lock_guard< MutexT > > : mpl::integral_c< lock_access_mode, exclusive_access >
{
};

template< typename MutexT >
struct thread_access_mode_of< shared_lock_guard< MutexT > > : mpl::integral_c< lock_access_mode, shared_access >
{
};

template< typename MutexT >
struct thread_access_mode_of< unique_lock< MutexT > > : mpl::integral_c< lock_access_mode, exclusive_access >
{
};

template< typename MutexT >
struct thread_access_mode_of< shared_lock< MutexT > > : mpl::integral_c< lock_access_mode, shared_access >
{
};

template< typename MutexT >
struct thread_access_mode_of< upgrade_lock< MutexT > > : mpl::integral_c< lock_access_mode, shared_access >
{
};

template< typename MutexT >
struct thread_access_mode_of< boost::log::aux::exclusive_lock_guard< MutexT > > : mpl::integral_c< lock_access_mode, exclusive_access >
{
};

template< typename MutexT >
struct thread_access_mode_of< boost::log::aux::shared_lock_guard< MutexT > > : mpl::integral_c< lock_access_mode, shared_access >
{
};

#endif // !defined(BOOST_LOG_NO_THREADS)

namespace aux {

//! The metafunction selects the most strict lock type of the two
template<
    typename LeftLockT,
    typename RightLockT,
#if !defined(BOOST_LOG_BROKEN_CONSTANT_EXPRESSIONS)
    bool CondV = (thread_access_mode_of< LeftLockT >::value < thread_access_mode_of< RightLockT >::value)
#else
    bool CondV = mpl::less< thread_access_mode_of< LeftLockT >, thread_access_mode_of< RightLockT > >::value
#endif
>
struct strictest_lock_impl
{
    typedef RightLockT type;
};
template< typename LeftLockT, typename RightLockT >
struct strictest_lock_impl< LeftLockT, RightLockT, false >
{
    typedef LeftLockT type;
};

} // namespace aux

#if defined(BOOST_LOG_DOXYGEN_PASS)

/*!
 * \brief The metafunction selects the most strict lock type of the specified.
 *
 * The template supports all lock types provided by the Boost.Thread
 * library (except for \c upgrade_to_unique_lock), plus additional
 * pseudo-lock \c no_lock that indicates no locking at all.
 * Exclusive locks are considered the strictest, shared locks are weaker,
 * and \c no_lock is the weakest.
 */
template< typename... LocksT >
struct strictest_lock
{
    typedef implementation_defined type;
};

#else // defined(BOOST_LOG_DOXYGEN_PASS)

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

template< typename LockT, typename... LocksT >
struct strictest_lock;

template< typename LockT >
struct strictest_lock< LockT >
{
    typedef LockT type;
};

template< typename LeftLockT, typename RightLockT >
struct strictest_lock< LeftLockT, RightLockT >
{
    typedef typename aux::strictest_lock_impl< LeftLockT, RightLockT >::type type;
};

template< typename LeftLockT, typename RightLockT, typename... LocksT >
struct strictest_lock< LeftLockT, RightLockT, LocksT... >
{
    typedef typename strictest_lock<
        typename aux::strictest_lock_impl< LeftLockT, RightLockT >::type,
        LocksT...
    >::type type;
};

#else // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

#   define BOOST_LOG_TYPE_INTERNAL(z, i, data) BOOST_PP_CAT(T, BOOST_PP_INC(i))

template<
    typename T,
    BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_PP_DEC(BOOST_LOG_STRICTEST_LOCK_LIMIT), typename T, void)
>
struct strictest_lock
{
    typedef typename strictest_lock<
        typename boost::log::aux::strictest_lock_impl< T, T0 >::type
        BOOST_PP_ENUM_TRAILING(BOOST_PP_SUB(BOOST_LOG_STRICTEST_LOCK_LIMIT, 2), BOOST_LOG_TYPE_INTERNAL, ~)
    >::type type;
};

template< typename T >
struct strictest_lock<
    T
    BOOST_PP_ENUM_TRAILING(BOOST_PP_DEC(BOOST_LOG_STRICTEST_LOCK_LIMIT), BOOST_LOG_PP_IDENTITY, void)
>
{
    typedef T type;
};

#   undef BOOST_LOG_TYPE_INTERNAL

#endif // !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

#endif // defined(BOOST_LOG_DOXYGEN_PASS)

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_STRICTEST_LOCK_HPP_INCLUDED_

/* strictest_lock.hpp
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
*/