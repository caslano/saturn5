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
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
*/