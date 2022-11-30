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

template< typename MutexT1, typename MutexT2 >
struct thread_access_mode_of< boost::log::aux::multiple_unique_lock2< MutexT1, MutexT2 > > : mpl::integral_c< lock_access_mode, exclusive_access >
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