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