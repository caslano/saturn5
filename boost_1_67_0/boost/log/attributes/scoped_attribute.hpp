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
            m_pLogger = 0; // if there already is a same-named attribute, don't register anything
    }
    //! Move constructor
    scoped_logger_attribute(BOOST_RV_REF(scoped_logger_attribute) that) :
        m_pLogger(that.m_pLogger),
        m_itAttribute(that.m_itAttribute)
    {
        that.m_pLogger = 0;
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
    scoped_logger_attribute(scoped_logger_attribute const& that) : m_pLogger(that.m_pLogger), m_itAttribute(that.m_itAttribute)
    {
        const_cast< scoped_logger_attribute& >(that).m_pLogger = 0;
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