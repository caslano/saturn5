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
#if defined(BOOST_GCC) && BOOST_GCC >= 40600
#pragma GCC diagnostic push
// type attributes ignored after type is already defined
#pragma GCC diagnostic ignored "-Wattributes"
#endif
namespace winapi {
struct BOOST_LOG_MAY_ALIAS _SECURITY_ATTRIBUTES;
}
#if defined(BOOST_GCC) && BOOST_GCC >= 40600
#pragma GCC diagnostic pop
#endif
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