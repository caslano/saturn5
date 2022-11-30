/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   scoped_attribute.hpp
 * \author Andrey Semashev
 * \date   13.05.2007
 *
 * The header contains definition of facilities to define scoped attributes.
 */

#ifndef BOOST_LOG_ATTRIBUTES_SCOPED_ATTRIBUTE_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_SCOPED_ATTRIBUTE_HPP_INCLUDED_

#include <cstddef>
#include <utility>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/core/addressof.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/core/core.hpp>
#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/attribute_set.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/constant.hpp>
#include <boost/log/utility/unused_variable.hpp>
#include <boost/log/utility/unique_identifier_name.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! A base class for all scoped attribute guards
class attribute_scope_guard
{
};

} // namespace aux

//! Scoped attribute guard type
typedef aux::attribute_scope_guard const& scoped_attribute;

namespace aux {

//! A scoped logger attribute guard
template< typename LoggerT >
class scoped_logger_attribute :
    public attribute_scope_guard
{
    BOOST_COPYABLE_AND_MOVABLE_ALT(scoped_logger_attribute)

private:
    //! Logger type
    typedef LoggerT logger_type;

private:
    //! A reference to the logger
    logger_type* m_pLogger;
    //! An iterator to the added attribute
    attribute_set::iterator m_itAttribute;

public:
    //! Constructor
    scoped_logger_attribute(logger_type& l, attribute_name const& name, attribute const& attr) :
        m_pLogger(boost::addressof(l))
    {
        std::pair<
            attribute_set::iterator,
            bool
        > res = l.add_attribute(name, attr);
        if (res.second)
            m_itAttribute = res.first;
        else
            m_pLogger = NULL; // if there already is a same-named attribute, don't register anything
    }
    //! Move constructor
    scoped_logger_attribute(BOOST_RV_REF(scoped_logger_attribute) that) BOOST_NOEXCEPT :
        m_pLogger(that.m_pLogger),
        m_itAttribute(that.m_itAttribute)
    {
        that.m_pLogger = NULL;
    }

    //! Destructor
    ~scoped_logger_attribute()
    {
        if (m_pLogger)
            m_pLogger->remove_attribute(m_itAttribute);
    }

#ifndef BOOST_LOG_BROKEN_REFERENCE_FROM_RVALUE_INIT
    BOOST_DELETED_FUNCTION(scoped_logger_attribute(scoped_logger_attribute const&))
#else // BOOST_LOG_BROKEN_REFERENCE_FROM_RVALUE_INIT
    scoped_logger_attribute(scoped_logger_attribute const& that) BOOST_NOEXCEPT : m_pLogger(that.m_pLogger), m_itAttribute(that.m_itAttribute)
    {
        const_cast< scoped_logger_attribute& >(that).m_pLogger = NULL;
    }
#endif // BOOST_LOG_BROKEN_REFERENCE_FROM_RVALUE_INIT

    BOOST_DELETED_FUNCTION(scoped_logger_attribute& operator= (scoped_logger_attribute const&))
};

} // namespace aux

//  Generator helper functions
/*!
 * Registers an attribute in the logger
 *
 * \param l Logger to register the attribute in
 * \param name Attribute name
 * \param attr The attribute. Must not be NULL.
 * \return An unspecified guard object which may be used to initialize a \c scoped_attribute variable.
 */
template< typename LoggerT >
BOOST_FORCEINLINE aux::scoped_logger_attribute< LoggerT > add_scoped_logger_attribute(LoggerT& l, attribute_name const& name, attribute const& attr)
{
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    return aux::scoped_logger_attribute< LoggerT >(l, name, attr);
#else
    aux::scoped_logger_attribute< LoggerT > guard(l, name, attr);
    return boost::move(guard);
#endif
}

#ifndef BOOST_LOG_DOXYGEN_PASS

#define BOOST_LOG_SCOPED_LOGGER_ATTR_INTERNAL(logger, attr_name, attr, sentry_var_name)\
    BOOST_LOG_UNUSED_VARIABLE(::boost::log::scoped_attribute, sentry_var_name,\
        = ::boost::log::add_scoped_logger_attribute(logger, attr_name, (attr)));

#endif // BOOST_LOG_DOXYGEN_PASS

//! The macro sets a scoped logger-wide attribute in a more compact way
#define BOOST_LOG_SCOPED_LOGGER_ATTR(logger, attr_name, attr)\
    BOOST_LOG_SCOPED_LOGGER_ATTR_INTERNAL(\
        logger,\
        attr_name,\
        attr,\
        BOOST_LOG_UNIQUE_IDENTIFIER_NAME(_boost_log_scoped_logger_attr_sentry_))

//! The macro sets a scoped logger-wide tag in a more compact way
#define BOOST_LOG_SCOPED_LOGGER_TAG(logger, attr_name, attr_value)\
    BOOST_LOG_SCOPED_LOGGER_ATTR(logger, attr_name, ::boost::log::attributes::make_constant(attr_value))

namespace aux {

//! A scoped thread-specific attribute guard
class scoped_thread_attribute :
    public attribute_scope_guard
{
    BOOST_COPYABLE_AND_MOVABLE_ALT(scoped_thread_attribute)

private:
    //! A pointer to the logging core
    core_ptr m_pCore;
    //! An iterator to the added attribute
    attribute_set::iterator m_itAttribute;

public:
    //! Constructor
    scoped_thread_attribute(attribute_name const& name, attribute const& attr) :
        m_pCore(core::get())
    {
        std::pair<
            attribute_set::iterator,
            bool
        > res = m_pCore->add_thread_attribute(name, attr);
        if (res.second)
            m_itAttribute = res.first;
        else
            m_pCore.reset(); // if there already is a same-named attribute, don't register anything
    }
    //! Move constructor
    scoped_thread_attribute(BOOST_RV_REF(scoped_thread_attribute) that) : m_itAttribute(that.m_itAttribute)
    {
        m_pCore.swap(that.m_pCore);
    }

    //! Destructor
    ~scoped_thread_attribute()
    {
        if (!!m_pCore)
            m_pCore->remove_thread_attribute(m_itAttribute);
    }

#ifndef BOOST_LOG_BROKEN_REFERENCE_FROM_RVALUE_INIT
    BOOST_DELETED_FUNCTION(scoped_thread_attribute(scoped_thread_attribute const&))
#else // BOOST_LOG_BROKEN_REFERENCE_FROM_RVALUE_INIT
    scoped_thread_attribute(scoped_thread_attribute const& that) : m_itAttribute(that.m_itAttribute)
    {
        m_pCore.swap(const_cast< scoped_thread_attribute& >(that).m_pCore);
    }
#endif // BOOST_LOG_BROKEN_REFERENCE_FROM_RVALUE_INIT

    BOOST_DELETED_FUNCTION(scoped_thread_attribute& operator= (scoped_thread_attribute const&))
};

} // namespace aux

//  Generator helper functions
/*!
 * Registers a thread-specific attribute
 *
 * \param name Attribute name
 * \param attr The attribute. Must not be NULL.
 * \return An unspecified guard object which may be used to initialize a \c scoped_attribute variable.
 */
BOOST_FORCEINLINE aux::scoped_thread_attribute add_scoped_thread_attribute(attribute_name const& name, attribute const& attr)
{
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    return aux::scoped_thread_attribute(name, attr);
#else
    aux::scoped_thread_attribute guard(name, attr);
    return boost::move(guard);
#endif
}

#ifndef BOOST_LOG_DOXYGEN_PASS

#define BOOST_LOG_SCOPED_THREAD_ATTR_INTERNAL(attr_name, attr, sentry_var_name)\
    BOOST_LOG_UNUSED_VARIABLE(::boost::log::scoped_attribute, sentry_var_name,\
        = ::boost::log::add_scoped_thread_attribute(attr_name, (attr)));

#endif // BOOST_LOG_DOXYGEN_PASS

//! The macro sets a scoped thread-wide attribute in a more compact way
#define BOOST_LOG_SCOPED_THREAD_ATTR(attr_name, attr)\
    BOOST_LOG_SCOPED_THREAD_ATTR_INTERNAL(\
        attr_name,\
        attr,\
        BOOST_LOG_UNIQUE_IDENTIFIER_NAME(_boost_log_scoped_thread_attr_sentry_))

//! The macro sets a scoped thread-wide tag in a more compact way
#define BOOST_LOG_SCOPED_THREAD_TAG(attr_name, attr_value)\
    BOOST_LOG_SCOPED_THREAD_ATTR(attr_name, ::boost::log::attributes::make_constant(attr_value))

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_ATTRIBUTES_SCOPED_ATTRIBUTE_HPP_INCLUDED_

/* scoped_attribute.hpp
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
*/