/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   once_block.hpp
 * \author Andrey Semashev
 * \date   23.06.2010
 *
 * \brief  The header defines classes and macros for once-blocks.
 */

#ifndef BOOST_LOG_UTILITY_ONCE_BLOCK_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_ONCE_BLOCK_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/utility/unique_identifier_name.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#ifndef BOOST_LOG_NO_THREADS

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * \brief A flag to detect if a code block has already been executed.
 *
 * This structure should be used in conjunction with the \c BOOST_LOG_ONCE_BLOCK_FLAG
 * macro. Usage example:
 *
 * <code>
 * once_block_flag flag = BOOST_LOG_ONCE_BLOCK_INIT;
 *
 * void foo()
 * {
 *     BOOST_LOG_ONCE_BLOCK_FLAG(flag)
 *     {
 *         puts("Hello, world once!");
 *     }
 * }
 * </code>
 */
struct once_block_flag
{
#ifndef BOOST_LOG_DOXYGEN_PASS
    // Do not use, implementation detail
    enum
    {
        uninitialized = 0, // this must be zero, so that zero-initialized once_block_flag is equivalent to the one initialized with uninitialized
        being_initialized,
        initialized
    };
    unsigned char status;
#endif // BOOST_LOG_DOXYGEN_PASS
};

/*!
 * \def BOOST_LOG_ONCE_BLOCK_INIT
 *
 * The static initializer for \c once_block_flag.
 */
#define BOOST_LOG_ONCE_BLOCK_INIT { boost::log::once_block_flag::uninitialized }

namespace aux {

class once_block_sentry
{
private:
    once_block_flag& m_flag;

public:
    explicit once_block_sentry(once_block_flag& f) BOOST_NOEXCEPT : m_flag(f)
    {
    }

    ~once_block_sentry() BOOST_NOEXCEPT
    {
        if (BOOST_UNLIKELY(m_flag.status != once_block_flag::initialized))
            rollback();
    }

    bool executed() const BOOST_NOEXCEPT
    {
        return (m_flag.status == once_block_flag::initialized || enter_once_block());
    }

    BOOST_LOG_API void commit() BOOST_NOEXCEPT;

private:
    BOOST_LOG_API bool enter_once_block() const BOOST_NOEXCEPT;
    BOOST_LOG_API void rollback() BOOST_NOEXCEPT;

    //  Non-copyable, non-assignable
    BOOST_DELETED_FUNCTION(once_block_sentry(once_block_sentry const&))
    BOOST_DELETED_FUNCTION(once_block_sentry& operator= (once_block_sentry const&))
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#else // BOOST_LOG_NO_THREADS

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

struct once_block_flag
{
    bool status;
};

#define BOOST_LOG_ONCE_BLOCK_INIT { false }

namespace aux {

class once_block_sentry
{
private:
    once_block_flag& m_flag;

public:
    explicit once_block_sentry(once_block_flag& f) BOOST_NOEXCEPT : m_flag(f)
    {
    }

    bool executed() const BOOST_NOEXCEPT
    {
        return m_flag.status;
    }

    void commit() BOOST_NOEXCEPT
    {
        m_flag.status = true;
    }

    //  Non-copyable, non-assignable
    BOOST_DELETED_FUNCTION(once_block_sentry(once_block_sentry const&))
    BOOST_DELETED_FUNCTION(once_block_sentry& operator= (once_block_sentry const&))
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_NO_THREADS

#ifndef BOOST_LOG_DOXYGEN_PASS

#define BOOST_LOG_ONCE_BLOCK_FLAG_INTERNAL(flag_var, sentry_var)\
    for (boost::log::aux::once_block_sentry sentry_var((flag_var));\
        BOOST_UNLIKELY(!sentry_var.executed()); sentry_var.commit())

// NOTE: flag_var deliberately doesn't have an initializer so that it is zero-initialized at the static initialization stage
#define BOOST_LOG_ONCE_BLOCK_INTERNAL(flag_var, sentry_var)\
    static boost::log::once_block_flag flag_var;\
    BOOST_LOG_ONCE_BLOCK_FLAG_INTERNAL(flag_var, sentry_var)

#endif // BOOST_LOG_DOXYGEN_PASS

/*!
 * \def BOOST_LOG_ONCE_BLOCK_FLAG(flag_var)
 *
 * Begins a code block to be executed only once, with protection against thread concurrency.
 * User has to provide the flag variable that controls whether the block has already
 * been executed.
 */
#define BOOST_LOG_ONCE_BLOCK_FLAG(flag_var)\
    BOOST_LOG_ONCE_BLOCK_FLAG_INTERNAL(\
        flag_var,\
        BOOST_LOG_UNIQUE_IDENTIFIER_NAME(_boost_log_once_block_sentry_))

/*!
 * \def BOOST_LOG_ONCE_BLOCK()
 *
 * Begins a code block to be executed only once, with protection against thread concurrency.
 */
#define BOOST_LOG_ONCE_BLOCK()\
    BOOST_LOG_ONCE_BLOCK_INTERNAL(\
        BOOST_LOG_UNIQUE_IDENTIFIER_NAME(_boost_log_once_block_flag_),\
        BOOST_LOG_UNIQUE_IDENTIFIER_NAME(_boost_log_once_block_sentry_))

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_ONCE_BLOCK_HPP_INCLUDED_

/* once_block.hpp
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
*/