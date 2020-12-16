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
0K0yn1Zme+aTXhNWgA6mpFUtK4G8iuReJ/InCeksedblR86zEzIn0zx/9fSdBVXdb0bVnZ9ce7mP+599PfS6q7Yl7DijyaAXV/3+nanVn2drnh/r/c3OPC/33/dtzjw/3PsbonmecNXf7BYE6i2pi0uROo49+ibI2GMmjITZsL7MYW0Mc2AqnAbPgtPhIHgOHAxnwSFyLXNV5PlDV/zTc1VkDprNfjAO9odN4ADYCg6GSTAdJsOhcDQcBjNlbuVkOBpOgaPgNLnODgttrJTxKdMYKeOj5rFR73HR6p074vxG6R7zbAkHII5xTvMYp2t803WGCJlT9TjmMETGLo3jliV6rLLqc0GKERmbdHwbRRdxjkV6j0PqMUg9/qjHHKtxvoeMM3qOK75h/r4qY4jBY4el8s31ECxDivn2uq3m+2vNr+ZX86v51fx+5N+P8/5vv9TZXwC+3/u/Pf5/hI7iZnsPNotThIv9Lq+wx3sxewOzUvphYZY9bD9hdFZ2bkbm6PHDc3v2w8Sv8zZ/re5v0ElN7RXQeQedUWcZdNL6ap330SkZYNDpndrTcoQnfVBAJ6df7pmpFQGakqp1TnrqpCmdo+jsHmzSSU3rN6Wn1tmc7qWTqnXyzvbQEb+OodN3iFGn95ni1yfoJA4N6GQNHzoyEOSeqZyprHW2eumk+nX+DuOGmXRS++KO1tnqpSPunICJw006Z6aMFXe+sNPQQyfToZMzwkNH/PoKWiMNOmRXwK9/oLPdpEMZC+hYaeTFKIMOyYyOKuvh6KSMDuhMzR6Xlcs0T8wkztuDzfoFzCJte2OcZqSWlMlozI6Kmfg7dNTZmankSxrpoHUWjPXQkXSItd0x6qT1xB2ts3qcWceZd1Hjg54j0TkzbaxVobN1vMEddPBL6yRNMLszRNw5g/DwbmVwpx/uVOisnmjU0XFvgE7fDINfqWk6zDxrLPIx6xAe7c6RSQa/eBwD5aQxOtszTe701X41RWdzllFH+9XC1sk26PRK6RdwJwGdQ5PNOgF32thla6pBp3efngF32qNTnmPWwR39rB2YHlzP6AyjngnoFM3w0knVOk1neuhIndaJ8JSadfpQp+l6OG+WUadfT4dO03M8dBz1+SEvHQlPFzsvck06qSl9p1bU5+l5Bh1Xnd8036DjqvPLvXQkPN0Iz4HZRp0+qRKeFHR2zzHppKX0Ep00W2euUad3IMxn2vVGgVHnzEDc+6HTdL5Jp5dduei6sWhBcB1n8UvAbABmZdpsdEYW//fs3Tt39LA0zP11+IJCl3lf27yX1VbsR50bMJ+9PL9wSdHSpYsyaAaW44nWKTHrFCsd8afpQoNOv9TlTp19Zh2/O1Kf5yyqrENzstypE7fYqKPdsex8NujQ5Cx36mxdYtTR7gy224ellXXSUkkfp06RUUe7M8TWWWbQ6SvxEp2ty4062p3hdrxWVNbp3VPSWXRyVpp0SGdpN0fZZXOVreMfhVhEDzMwdzS7taX3YHpcvsS/Fu5f2/EyHGP3PUe7xzPcu8Fb7v3g9b4ozyu7T4bvCY+QPerEPXyJDWvt3KOO+1WPPYwY499XrJZV13+PqxnjuccX0U7craP3ZynUY0bvj5b9j2U/5DJ1vS28lrUu/CH2M04mouOI92TSITasN5sZR9SOjIiNjIyNio6pG9kgPCIyLLwx+xwnx3TjrxaRUeG1YtrFjIThkXXCc2KSYtpi2j0mOaYA804xyZH10OAa01rcqc9f2EGGcdUcaRqziKs+/BVvuxgzJCZJ6XWIbBwehklsTI/IVuFh2Bsd26JW5OrwVjGdUepc8Y9QxvLB+SeMrRBsxlP8UhYv+/5o8d+fgkxF2As=
*/