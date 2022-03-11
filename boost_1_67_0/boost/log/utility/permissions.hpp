/*
 *                 Copyright Lingxi Li 2015.
 *              Copyright Andrey Semashev 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   permissions.hpp
 * \author Lingxi Li
 * \author Andrey Semashev
 * \date   14.10.2015
 *
 * The header contains an abstraction wrapper for security permissions.
 */

#ifndef BOOST_LOG_UTILITY_PERMISSIONS_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_PERMISSIONS_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#ifdef BOOST_WINDOWS
extern "C" {
struct _SECURITY_ATTRIBUTES;
}
#endif // BOOST_WINDOWS

namespace boost {

#ifdef BOOST_WINDOWS
namespace winapi {
struct BOOST_LOG_MAY_ALIAS _SECURITY_ATTRIBUTES;
}
#endif

namespace interprocess {
class permissions;
} // namespace interprocess

BOOST_LOG_OPEN_NAMESPACE

/*!
 * \brief Access permissions wrapper.
 *
 * On Windows platforms, it represents a pointer to \c SECURITY_ATTRIBUTES. The user is responsible
 * for allocating and reclaiming resources associated with the pointer, \c permissions instance does
 * not own them.
 *
 * On POSIX platforms, it represents a \c mode_t value.
 */
class permissions
{
public:
#if defined(BOOST_LOG_DOXYGEN_PASS)
    //! The type of security permissions, specific to the operating system
    typedef implementation_defined native_type;
#elif defined(BOOST_WINDOWS)
    typedef ::_SECURITY_ATTRIBUTES* native_type;
#else
    // Equivalent to POSIX mode_t
    typedef unsigned int native_type;
#endif

#if !defined(BOOST_LOG_DOXYGEN_PASS)
private:
    native_type m_perms;
#endif

public:
    /*!
     * Default constructor. The method constructs an object that represents
     * a null \c SECURITY_ATTRIBUTES pointer on Windows platforms, and a
     * \c mode_t value \c 0644 on POSIX platforms.
     */
    permissions() BOOST_NOEXCEPT
    {
        set_default();
    }

    /*!
     * Copy constructor.
     */
    permissions(permissions const& that) BOOST_NOEXCEPT : m_perms(that.m_perms)
    {
    }

    /*!
     * Copy assignment.
     */
    permissions& operator=(permissions const& that) BOOST_NOEXCEPT
    {
        m_perms = that.m_perms;
        return *this;
    }

    /*!
     * Initializing constructor.
     */
    permissions(native_type perms) BOOST_NOEXCEPT : m_perms(perms)
    {
    }

#ifdef BOOST_WINDOWS
    permissions(boost::winapi::_SECURITY_ATTRIBUTES* perms) BOOST_NOEXCEPT : m_perms(reinterpret_cast< native_type >(perms))
    {
    }
#endif

    /*!
     * Initializing constructor.
     */
    BOOST_LOG_API permissions(boost::interprocess::permissions const& perms) BOOST_NOEXCEPT;

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    /*!
     * Move constructor.
     */
    permissions(permissions&& that) BOOST_NOEXCEPT : m_perms(that.m_perms)
    {
        that.set_default();
    }

    /*!
     * Move assignment.
     */
    permissions& operator=(permissions&& that) BOOST_NOEXCEPT
    {
        m_perms = that.m_perms;
        that.set_default();
        return *this;
    }
#endif

    /*!
     * Sets permissions from the OS-specific permissions.
     */
    void set_native(native_type perms) BOOST_NOEXCEPT
    {
        m_perms = perms;
    }

    /*!
     * Returns the underlying OS-specific permissions.
     */
    native_type get_native() const BOOST_NOEXCEPT
    {
        return m_perms;
    }

    /*!
     * Sets the default permissions, which are equivalent to \c NULL \c SECURITY_ATTRIBUTES
     * on Windows and \c 0644 on POSIX platforms.
     */
    void set_default() BOOST_NOEXCEPT
    {
#if defined(BOOST_WINDOWS)
        m_perms = 0;
#else
        m_perms = 0644;
#endif
    }

    /*!
     * Sets unrestricted permissions, which are equivalent to \c SECURITY_ATTRIBUTES with \c NULL DACL
     * on Windows and \c 0666 on POSIX platforms.
     */
    void set_unrestricted()
    {
#if defined(BOOST_WINDOWS)
        m_perms = get_unrestricted_security_attributes();
#else
        m_perms = 0666;
#endif
    }

    /*!
     * The method swaps the object with \a that.
     *
     * \param that The other object to swap with.
     */
    void swap(permissions& that) BOOST_NOEXCEPT
    {
        native_type perms = m_perms;
        m_perms = that.m_perms;
        that.m_perms = perms;
    }

    //! Swaps the two \c permissions objects.
    friend void swap(permissions& a, permissions& b) BOOST_NOEXCEPT
    {
        a.swap(b);
    }

#if !defined(BOOST_LOG_DOXYGEN_PASS) && defined(BOOST_WINDOWS)
private:
    static BOOST_LOG_API native_type get_unrestricted_security_attributes();
#endif
};

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_PERMISSIONS_HPP_INCLUDED_

/* permissions.hpp
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
*/