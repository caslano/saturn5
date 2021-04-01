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
LU6Y1iVFkGBeYXd62DwCcZz/ChAhXLjcf4tZ0KOYOdIJ5qxxz0805lyUSG1ILlrcPq2tcdbLnva8ptIKP2TWNz8I4Bf3tndbCHSE4AhybxWgfRl2b2Y7rXiOQVAR5YSYdo6A+E20cFJJvLmZdoJZltNfGTboORk7m402tVKGmxen5nvPSHpH13kcyT/+6ifkh/ROMxSGfSnRiTQ9kPd8Rp0t+i5a2JIXU0V1pv2qavT+P79PquabTcN8uu0UDtberuMdVUXUZl09Tejt/T3ejr72gkEFEhm2DBkhqAUfXlDkU6OFd3vqv4P9mKRVDGignnifvXXby3L/4uuTgf/L5CYJTSLzBdCpnBPZ8AKm+C8aPPot0OzTyLvGv2UV/fiH6rucQ7dQ5ip20VzLa8U9n3c3sjP9k6GSLceYrRGXpltx7Dte2Z1Turr5YuViV88wcnVemdfbnsEfZGIAMpsToDfkZQ69pKbgkWeserDgMYCPljIApJV9mD6NNpUyG+L5iLBUd60XcDFxxw0iY3Vzy+RlGwRNydr6uSwhSd7R9hlQBP4a6dED8MEMgw==
*/