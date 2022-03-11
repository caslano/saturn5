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