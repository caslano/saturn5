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
LzBr+xmwvthfaM0X/NK6bdqpcZsJG4m8RPXUYLVvyzu3X2WH7y8z7S4BOT44Kfa9Krj35v3FTqb2GXVFtog8OoN5jwzrmpYJX93zZt7Bcd3dlCTycfQY8bSEvmoecFqJ+Vz6xf7O1UiTTTsvk/ZF+PK0E3u1MDvcLo8XszZR3fQSeWpEO+0jZq2juhmmbtzhnCNmHdUsEDLTeNeI6s9ES9hTxKyh6Qcwq3L67zT+He6zFlrCeETMEpxMVxjzxKwZNmtXuk8iI7Jf0b0MEX0LZp5vnmhd0z5G29PFEe1p0lF6v08At3AL7Bw6dxHRnsZOnTxmdCfE7rHVtKVvNmCXX9YNdPxMF/25gRr0Tu24nfNa5yUzjs5/U+qGfW1F66oJg/4yV+t6H/GzMJBMiXRgpLiRXLuXWYPXmS15l94wPtCIu3BSuXempQnrBnGTY+bOE0Xf1dJObWGPMXcMjhR3NUybXSr6F0nFMDGTdVgxeykwyOkYyNDwporZfcxdDLe27QMV22aue01wleRVkul3Hhb/LpIx6TvGiKDIX3a77+i4+paGYr8/PqQZP1qJm194+wOzb2q2yHsY+0PFj6FR63+KyJPFLEPLsZaYNargpp66aSDyM8SsjrppLmZprnhNmOjur9tu8G/XrUReOyIeuRus/ZB5/zhF64e77Z4mZulR414k8hYRbkrELDVq3GeJPCVq3K8UeWZE3G8Us5ZR436nps0dj3vFrG7UuD8r8pMi3LwgZnW8bsw73HaRN4lw8270spKwvqqkrL4QeVZEX/6dmHWPmt50qZcdI+JxrJjVi5rePJHnRbjp9aZ/PRuG3C/ug0VeJ6KsztNwosWjWOStI+JxiZjVjRqP2yuJx03IvXXmrjf9x91HtD9xx+NpzY/Q+BP/b7zXone/16KvuLfiULYjz1k16JvgGTA0xvTcWGGMyfOOMQ00P05/K2R3WUIHpzyQG5wR2B93U+B47Z9Hiz+bE814w2rHrwMLnC7BOwLvxU0OFCXMcP6esN7Uz1FvRx2DiFPFMWiH9se3iWxX4g9j0HAdg5o468jTbfxu+Qe5lhWo7eQGmjrD2ZF5ET+1bwykOUtQL2P+XmCEc3KwpjM4mOZMQl0XrO3cG2zqrMNse/AY5/tgPSc7rqbTKS7NGYS6IK62MzuuhbMUs3Vxmc6HmAXi05yGqBPjaztD4ls6l8XXdG6Lz3L+EN/Q2c7fn2KekjDYGZ+Q5sxKqO0sSmjqvJIwwMlKbOn0SqzpjEzMci5PbOQsSkx1nsIs3O9ftFV+z5p71XdIWtMTcpgW3hv4NhgeQ4djbh1DrXk3xvymflhkXyTUcPYlHK9h/uMHvxLbMPv+HOU2LjDAOS440KkVN9TZETfcuTl+iNMiYZMZY/PFfrcag5xHE8PxLJd68UR8B6dp8MbgnkBLjecLYrdBImMvb8i1AzsCDzl3B28LnB0/26mZ8LltPCb+9vG4gYb/jcgHJ5Y53QPTgs8FtsU3DoTH4lVbQrI7vWOxuTt6krhtXIOxmBF5QWKm+lks8f9r/FxnWmBPcG4gQ/3rsjlkfntwIzfZ2cbqdDhb6nGSid/9EsYpiUO5JS0u+HTgkvjBxr94id+c4EpuSovWP/xiY8Wx/PyN/mP5Bci9Y3nZRv8+9jLkfn3bxci9Y/msjf5j+c3IvWP5/I3+Y/nTyL1j+Usb/cfyzcj9xvKNyL398u6N/mP5x8i9Y/kXG/3H8uS3Ko7lR7/lP5a3Ru4dyzu85T+W90PuV1a9NEz3WH6mmHWOmt7zRN4hIh5FYpYVNb0zRd48ws0NGvdo6V0o8q4RbpaIWa2ocXtW5J0i3Lz8ln99flvkNaPm0RY=
*/