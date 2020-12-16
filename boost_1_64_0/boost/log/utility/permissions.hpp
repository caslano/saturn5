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
dOdB1LZgEycQl+QcxzrwOXHpzrVxxzvPx2U7X/N30/jjnMHxSc70+KuczITpzr0Jh8fEAgn7TLNuOvpPIf0eZyj/WcZF0uE/Lj64JyQPmrXcJjtD+oOBVqxsZ2qYB8SPyxPaskfru0CvuPAYV3u3jGfBFOerQHiM+p34d76TqXtra4p/Y+Ovc84IzAtOMGuqE/eKW+94auLxpPj9HWu+jwQaaDzGiF/nJ+Q6dwTODM4LNIwPBMJle7vILjHj78QdZvw1cZknds6If9I5J/BcsIl37dXcEfOh2NsdH3Q2xYfjUyjpWh5o44wPhN/lD0ocvw9McgpNPF6VcJuZOjZ8l/Ydmj+LRL6EGpEbaKDxekrM0hJP4KvzrYPFgYHxO6K20wux6x3TL8LMb0z/FXLvmH7pjsrH9OnY8Y7pl2Pm14/MQe4d02/FzDum/wYzvzH9fuR+Y/qDyL1j+qM7Kh/Tb9xhH9OXYu43pu9C7jem70DuHdO/x8w7pgd2Vj6mv40775i+DzO/Mb3eTv8xva7IO0Tk1zFi1tc3v/ZLuIUVxvRjd0aO6aF6/N4O//HsNHGTFpFHQzDzrlcN2+k/zk8WeVLUObyLRJ4b4ef1YlbPN60Dxc6p2G8SkdZpYp4SNT73irxW1HTfg9z7PvWgmPWw1QOTjvu1TN1xeVzT7n7veFj9j7qvAbnf3Hm5yjV+8hzEzLt+8FUV6u4bYqdj5B4JMWsUNX4pu6zz1qZcaiH3rgs2F7M0W3maNLwv4Z5DLc2OiE+dXRXzcLvYXRWMFscuu/zbVyfk3v6o2y57f+ROW96uim29u5ilR9/nLvKUCH8uErPGEXl08S7/Pm2uSZO9Hd2E3Pv++WD0fDdxmSp2BjhB4uNO1627/NvRM5XUg5XIvWuSG8Ssnm87Wi12jouIy5pd/uPPB8j92vT7lvL+VMxO8i3v/WInNyIuB7U+RotLg93WcjJ+NkTuXX84aXflvxMaiZ3mkWsMYpYRNS5nibxm1DozCLm3zozTuPjly9lip2VEXIbv9s+X6cj96sulyL3jwC27K68vV1niMrOSuDyC3O99ZYnIj4+oL4+LWS/ffHlsd8X6slzjEi2s7ci94+x7mHnH2Q92+4+z/0DuN84G9lQs66w9lfcPe8TfgRXG2YQ9/v3Dccj9yrudyDtFzhmIWR3f8u4gdtpGxKXjHv/yHoncr384B7m3f/ilmPX1Le9R/2LvTOBjPPo4PjPPlWw2m2STzbkIG9ciss51Jq5FJBHipsjlPuJW1H2fUdRRVNV9VOoqPbXOllZbvfRtlRZF66WlilLvL2PyvJtYQd/78+b5GN/sf45n/nM/M/PMw930yxeXHqcKr5PzThXev8+BfcH+fReXWfOl1Z5Tj24zxnM3sfnit+xU4WuM7z8i347BvmD//v2pR/fvq7mb9iQQerjH5wTkBfv3RVx27aFx/PVU4f37NQ/5eevUo/v330492L//fqrw/r3ctw/27zGQFezfa0BWWP/eAvaF9e+JsC+4/yGDy4IKrb/R3E3VB/r3Vlxe/qHxGQX7wtrIkdy+Qr40HstlDQqtv2O4G2O+uEyGrOCc43QuW/LQ+G3m9r4PLac7YV9wT8aJbx89Jt4ONwXn4/ZAVlidvgj7wtqXH2Bf8JniqohfYeXxr9xNWL643ICssP4k9PSDbYXtdOF9Rx1ub3xomLW4fY18c7Gxpx89F9vo9INzsU0hKzgXG8llzR8av6Gwd5+LXYbfhe5pgH3Bvm7h6Ue3l5mnH8z7kacLn0NZA/uCc7HbuCzoH35H3X1dvWJjUe9gKMwImL860Qd95zYX6+HcBf05nLvr63nvBOw8nIfA02Uwt8s=
*/