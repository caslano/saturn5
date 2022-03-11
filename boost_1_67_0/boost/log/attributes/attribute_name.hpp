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