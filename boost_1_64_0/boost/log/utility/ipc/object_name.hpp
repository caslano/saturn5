/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   utility/ipc/object_name.hpp
 * \author Andrey Semashev
 * \date   05.03.2016
 *
 * The header contains declaration of a system object name wrapper.
 */

#ifndef BOOST_LOG_UTILITY_IPC_OBJECT_NAME_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_IPC_OBJECT_NAME_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <cstddef>
#include <iosfwd>
#include <string>
#include <boost/move/core.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace ipc {

/*!
 * \brief A system object name class
 *
 * In order to identify a system-wide object such as a shared memory segment or a named synchronization primitive the object has to be given a name.
 * The format of the name is specific to the operating system and the \c object_name class provides an abstraction for names of objects. It also
 * provides means for scoping, which allows to avoid name clashes between different processes.
 *
 * The object name is a UTF-8 encoded string. The portable object name should consist of the following characters:
 *
 * <pre>
 * A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
 * a b c d e f g h i j k l m n o p q r s t u v w x y z
 * 0 1 2 3 4 5 6 7 8 9 . _ -
 * </pre>
 *
 * \note The character set corresponds to the POSIX Portable Filename Character Set (http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap03.html#tag_03_278).
 *
 * Use of other characters may result in non-portable system-specific behavior.
 *
 * The name can have one of the following scopes:
 *
 * \li \c global - objects within this scope are visible to any process on the system. In order to use this scope the process may need to have
 *                 extended privileges. This scope is not available for Windows Store applications.
 * \li \c user - objects within this scope can be opened by processes running under the same user as the current process.
 * \li \c session - objects within this scope are visible to processes within the session of the current process. The definition of a session may vary between
 *                  operating systems. On POSIX, a session is typically a group of processes attached to a single virtual terminal device. On Windows a session is
 *                  started when a user logs into the system. There is also a separate session for Windows services.
 * \li \c process_group - objects within this scope are visible to processes within the process group of the current process. Currently, on Windows all processes
 *                        running in the current session are considered members of the same process group. This may change in future.
 *
 * The scopes are not overlapping. For instance, if an object is created in the global scope, the object cannot be opened with the same name but in user's scope.
 *
 * Note that name scoping is not a security feature. On some systems any process on the system has technical capability to open objects within any scope.
 * The scope is only used to help avoid name clashes between processes using \c object_name to identify objects.
 */
class object_name
{
public:
    //! Name scopes
    enum scope
    {
        global,        //!< The name has global scope; any process in the system has the potential to open the resource identified by the name
        user,          //!< The name is limited to processes running under the current user
        session,       //!< The name is limited to processes running in the current login session
        process_group  //!< The name is limited to processes running in the current process group
    };

#if !defined(BOOST_LOG_DOXYGEN_PASS)

    BOOST_COPYABLE_AND_MOVABLE(object_name)

private:
    std::string m_name;

#endif // !defined(BOOST_LOG_DOXYGEN_PASS)

public:
    /*!
     * Default constructor. The method creates an empty object name.
     *
     * \post <tt>empty() == true</tt>
     */
    object_name() BOOST_NOEXCEPT
    {
    }

    /*!
     * Move constructor.
     */
    object_name(BOOST_RV_REF(object_name) that) BOOST_NOEXCEPT
    {
        m_name.swap(that.m_name);
    }

    /*!
     * Copy constructor.
     */
    object_name(object_name const& that) : m_name(that.m_name)
    {
    }

    /*!
     * Constructor from the native string.
     *
     * \param str The object name string, must not be \c NULL. The string format is specific to the operating system.
     */
    static object_name from_native(const char* str)
    {
        object_name name;
        name.m_name = str;
        return name;
    }

    /*!
     * Constructor from the native string.
     *
     * \param str The object name string. The string format is specific to the operating system.
     */
    static object_name from_native(std::string const& str)
    {
        object_name name;
        name.m_name = str;
        return name;
    }

    /*!
     * Constructor from the object name
     * \param ns The scope of the object name
     * \param str The object name, must not be NULL.
     */
    BOOST_LOG_API object_name(scope ns, const char* str);

    /*!
     * Constructor from the object name
     * \param ns The scope of the object name
     * \param str The object name
     */
    BOOST_LOG_API object_name(scope ns, std::string const& str);

    /*!
     * Move assignment
     */
    object_name& operator= (BOOST_RV_REF(object_name) that) BOOST_NOEXCEPT
    {
        m_name.clear();
        m_name.swap(that.m_name);
        return *this;
    }

    /*!
     * Copy assignment
     */
    object_name& operator= (BOOST_COPY_ASSIGN_REF(object_name) that)
    {
        m_name = that.m_name;
        return *this;
    }

    /*!
     * Returns \c true if the object name is empty
     */
    bool empty() const BOOST_NOEXCEPT { return m_name.empty(); }

    /*!
     * Returns length of the name, in bytes
     */
    std::size_t size() const BOOST_NOEXCEPT { return m_name.size(); }

    /*!
     * Returns the name string
     */
    const char* c_str() const BOOST_NOEXCEPT { return m_name.c_str(); }

    /*!
     * Swaps the object name with another object name
     */
    void swap(object_name& that) BOOST_NOEXCEPT { m_name.swap(that.m_name); }

    /*!
     * Swaps two object names
     */
    friend void swap(object_name& left, object_name& right) BOOST_NOEXCEPT
    {
        left.swap(right);
    }

    /*!
     * Returns string representation of the object name
     */
    friend std::string to_string(object_name const& name)
    {
        return name.m_name;
    }

    /*!
     * Equality operator
     */
    friend bool operator== (object_name const& left, object_name const& right) BOOST_NOEXCEPT
    {
        return left.m_name == right.m_name;
    }
    /*!
     * Inequality operator
     */
    friend bool operator!= (object_name const& left, object_name const& right) BOOST_NOEXCEPT
    {
        return left.m_name != right.m_name;
    }
    /*!
     * Less operator
     */
    friend bool operator< (object_name const& left, object_name const& right) BOOST_NOEXCEPT
    {
        return left.m_name < right.m_name;
    }
    /*!
     * Greater operator
     */
    friend bool operator> (object_name const& left, object_name const& right) BOOST_NOEXCEPT
    {
        return left.m_name > right.m_name;
    }
    /*!
     * Less or equal operator
     */
    friend bool operator<= (object_name const& left, object_name const& right) BOOST_NOEXCEPT
    {
        return left.m_name <= right.m_name;
    }
    /*!
     * Greater or equal operator
     */
    friend bool operator>= (object_name const& left, object_name const& right) BOOST_NOEXCEPT
    {
        return left.m_name >= right.m_name;
    }

    /*!
     * Stream ouput operator
     */
    template< typename CharT, typename TraitsT >
    friend std::basic_ostream< CharT, TraitsT >& operator<< (std::basic_ostream< CharT, TraitsT >& strm, object_name const& name)
    {
        strm << name.c_str();
        return strm;
    }
};

} // namespace ipc

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_IPC_OBJECT_NAME_HPP_INCLUDED_

/* object_name.hpp
2+MOOeZ77mbok06QiyBjIVdB5kOWop8Go592o5/e0/uRo+vSNkg7VPbjPE0TUMfKl/h0GaOKi79JdGEy/r5t5+X1ZnK8PCf1+EWvjPQpaK0WwCzgEOB4XD3OdAH19toKPcLvmGPH+B9zvfRFIy0Z9WqPuR1j9H+GrKWCtRPs6y3igP66E3N1Fff/KzkfX3hrqs8X4MJUxaVvebZGXU+frq3Sdfbp2ihdI5+uldJ9lqJ0mc3NdCl2XwB3ip33/0E1pWsr4XXVrLz/Tal/DO9flYW+NnRy/dgmx8Y85N7lOxn+geHPGT7E8OFq5vVGwjFyfrA/MD6N4Z8Y7svwQV7PhpQJjykTXsjwL8y/JsV6vO0M/8r4PWXCK6tbr585qdb6j0u1lndVqkpvXb+30jR2Ea+fgxUXOc1cv8v/toek6x/AN0KV4zrh9a2MX4LU+ZU06zm9mabOyXoOHXhzks3rWj+1x4nvGhRwHx61PidK2ubw7/c4nQfKCn5vnrhqwfsqWNPa7xuqS3xHrU5QbRge38FILx8QODVuv9HeTTgHfmP7d2L4yjPL+LxFB/jeim8Mlf+9lbRyvreSFtxeKCfa76eYnPthHCNDyWkvSTbrGHC/n2TW80FJ20m+SJUJsddXlWfnuyer657EXyQeKOdD7OPHLMPGaxdfXYmLRlvD1yga6XFeNxo+JmHVPBGes+Bg1C9Cjw53e9oaUNk+rngur0k5qVID8Rs6Tdx4Y5y8JGXj194bfpfhB+uV8QXlER/i2rOO83Z9ktknQp4PxM/eJOlWa8vw/4pA/Oyk8jn0z0n8WTisbu8LyR/8PkbWtPY2/1zio+RIiiN/UHQTtDFWX2vIiX2tT5Yjb/TJx0ncN4R99CXDq+p5w3qyde2NSbZeT+okO19P9sXzQYEVPZ+c+2xfnzrur6Tm2CBJ111riNh2AeaYlGXn3Jtr+UiJb6adEWB+SX47D99ccy+R+LpoL5e9n2357f18RZI5t+xrdpB+DvFBfJ/l0iTrPLs+Sc2zvzY3/Qfhpu883vLpWH3JOSO25X998eiXZoc4FJ8EwU1Xg/VG8tFXkY++Xb3Dkvdq9u+LdOEeQ12B8eRvN+X3MNqQr94H2Iv8w77k/Q0E3gEcRN5fDnAh+eyPUv849Zv5Lf9XyV/fQ/76+4z/gPz1L8hb/5HfxTgq8eo7H+pdDfrF4Tsfo8nHzCcPczJ52xPIG59IPuYk8h0n+/NLawXktQuPVZ48yWu/RPG7dT6f891JKes4j+8wNzPf0+RbPsvjP0fe50Asqr3J6xzK8DDgDoRHk785jfpi4KsIX83wNeRz3gjcBVxE/WLyOdcwvBa4h/3xDvAx8ji3kZf5HXmZ/wJ+BQx3efnoGcABwp/2ltMQ+D30LYEHge2BpcDzma4v0/UDHoJ+JPV51I8BRgEnAj3AmcBo4JXAKsASYBxwATAeuByYAHwAWBX4EDAR+DgwCbid/PDdwFrAQ+R/h+u4DQFWA2YAawDrAFsD6wL7A+sBJwD7ASfp3noW6t56XgJsDPw79TdSfxMwBXgf861k/BrGPwhsYdQP2BK4hfFPMf5pYFvgs9S/RP0OYHvgLurfpn4PsCOwFNgZeASYBYx1Y74a5wU8F9jS7a1PW7c3f3u35JfxOVc9w/EZsZT+V7Mgii8tzwT0u7iKPPd55LnPpt/FHGA6+bj1ycfNBP6d/g/X0V/hevo/3ADMpl/HYCnPW5/x6pkJmM36REGGsz6DycceCqxKHvZZQIwdmT/5wKZAjC05bi4wCzga2Jvp+kk6rhfyDBL4u0DFnJ/TuffbDO79din3aruM5z2Tfh+Xq/Mw7/NRR4fzGM/zmASsBpw=
*/