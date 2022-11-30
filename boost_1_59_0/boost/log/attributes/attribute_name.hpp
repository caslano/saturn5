/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   attribute_name.hpp
 * \author Andrey Semashev
 * \date   28.06.2010
 *
 * The header contains attribute name interface definition.
 */

#ifndef BOOST_LOG_ATTRIBUTE_NAME_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTE_NAME_HPP_INCLUDED_

#include <iosfwd>
#include <string>
#include <boost/assert.hpp>
#include <boost/cstdint.hpp>
#include <boost/core/explicit_operator_bool.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * \brief The class represents an attribute name in containers used by the library
 *
 * The class mostly serves for optimization purposes. Each attribute name that is used
 * with the library is automatically associated with a unique identifier, which is much
 * lighter in terms of memory footprint and operations complexity. This is done
 * transparently by this class, on object construction. Passing objects of this class
 * to other library methods, such as attribute lookup functions, will not require
 * this translation and/or string copying and thus will result in a more efficient code.
 */
class attribute_name
{
public:
    //! String type
    typedef std::string string_type;
#ifdef BOOST_LOG_DOXYGEN_PASS
    //! Associated identifier
    typedef unspecified id_type;
#else
    typedef uint32_t id_type;

private:
    class repository;
    friend class repository;

private:
    //! Associated identifier
    id_type m_id;
    //! A special identifier value indicating unassigned attribute name
    static BOOST_CONSTEXPR_OR_CONST id_type uninitialized = ~static_cast< id_type >(0u);
#endif

public:
    /*!
     * Default constructor. Creates an object that does not refer to any attribute name.
     */
    BOOST_CONSTEXPR attribute_name() BOOST_NOEXCEPT : m_id(uninitialized)
    {
    }
    /*!
     * Constructs an attribute name from the specified string
     *
     * \param name An attribute name
     * \pre \a name is not NULL and points to a zero-terminated string
     */
    attribute_name(const char* name) :
        m_id(get_id_from_string(name))
    {
    }
    /*!
     * Constructs an attribute name from the specified string
     *
     * \param name An attribute name
     */
    attribute_name(string_type const& name) :
        m_id(get_id_from_string(name.c_str()))
    {
    }

    /*!
     * Compares the attribute names
     *
     * \return \c true if <tt>*this</tt> and \c that refer to the same attribute name,
     *         and \c false otherwise.
     */
    bool operator== (attribute_name const& that) const BOOST_NOEXCEPT { return m_id == that.m_id; }
    /*!
     * Compares the attribute names
     *
     * \return \c true if <tt>*this</tt> and \c that refer to different attribute names,
     *         and \c false otherwise.
     */
    bool operator!= (attribute_name const& that) const BOOST_NOEXCEPT { return m_id != that.m_id; }

    /*!
     * Compares the attribute names
     *
     * \return \c true if <tt>*this</tt> and \c that refer to the same attribute name,
     *         and \c false otherwise.
     */
    bool operator== (const char* that) const { return (m_id != uninitialized) && (this->string() == that); }
    /*!
     * Compares the attribute names
     *
     * \return \c true if <tt>*this</tt> and \c that refer to different attribute names,
     *         and \c false otherwise.
     */
    bool operator!= (const char* that) const { return !operator== (that); }

    /*!
     * Compares the attribute names
     *
     * \return \c true if <tt>*this</tt> and \c that refer to the same attribute name,
     *         and \c false otherwise.
     */
    bool operator== (string_type const& that) const { return (m_id != uninitialized) && (this->string() == that); }
    /*!
     * Compares the attribute names
     *
     * \return \c true if <tt>*this</tt> and \c that refer to different attribute names,
     *         and \c false otherwise.
     */
    bool operator!= (string_type const& that) const { return !operator== (that); }

    /*!
     * Checks if the object was default-constructed
     *
     * \return \c true if <tt>*this</tt> was constructed with an attribute name, \c false otherwise
     */
    BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()
    /*!
     * Checks if the object was default-constructed
     *
     * \return \c true if <tt>*this</tt> was default-constructed and does not refer to any attribute name,
     *         \c false otherwise
     */
    bool operator! () const BOOST_NOEXCEPT { return (m_id == uninitialized); }

    /*!
     * \return The associated id value
     * \pre <tt>(!*this) == false</tt>
     */
    id_type id() const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(m_id != uninitialized);
        return m_id;
    }
    /*!
     * \return The attribute name string that was used during the object construction
     * \pre <tt>(!*this) == false</tt>
     */
    string_type const& string() const { return get_string_from_id(m_id); }

private:
#ifndef BOOST_LOG_DOXYGEN_PASS
    static BOOST_LOG_API id_type get_id_from_string(const char* name);
    static BOOST_LOG_API string_type const& get_string_from_id(id_type id);
#endif
};

template< typename CharT, typename TraitsT >
BOOST_LOG_API std::basic_ostream< CharT, TraitsT >& operator<< (
    std::basic_ostream< CharT, TraitsT >& strm,
    attribute_name const& name);

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_ATTRIBUTE_NAME_HPP_INCLUDED_

/* attribute_name.hpp
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
*/