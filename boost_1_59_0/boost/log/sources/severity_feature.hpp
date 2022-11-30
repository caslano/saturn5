/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   severity_feature.hpp
 * \author Andrey Semashev
 * \date   08.03.2007
 *
 * The header contains implementation of a severity level support feature.
 */

#ifndef BOOST_LOG_SOURCES_SEVERITY_FEATURE_HPP_INCLUDED_
#define BOOST_LOG_SOURCES_SEVERITY_FEATURE_HPP_INCLUDED_

#include <boost/cstdint.hpp>
#include <boost/static_assert.hpp>
#include <boost/core/swap.hpp>
#include <boost/smart_ptr/intrusive_ptr.hpp>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/type_traits/is_nothrow_move_constructible.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/locks.hpp>
#include <boost/log/detail/default_attribute_names.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/attribute_cast.hpp>
#include <boost/log/attributes/attribute_value_impl.hpp>
#include <boost/log/utility/strictest_lock.hpp>
#include <boost/log/utility/type_dispatch/type_dispatcher.hpp>
#include <boost/log/keywords/severity.hpp>
#include <boost/log/core/record.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sources {

namespace aux {

    //! The method returns the storage for severity level for the current thread
    BOOST_LOG_API uintmax_t& get_severity_level();

    //! Severity level attribute implementation
    template< typename LevelT >
    class severity_level :
        public attribute
    {
        typedef severity_level this_type;
        BOOST_COPYABLE_AND_MOVABLE(this_type)

    public:
        //! Stored level type
        typedef LevelT value_type;
        BOOST_STATIC_ASSERT_MSG(sizeof(value_type) <= sizeof(uintmax_t), "Boost.Log: Unsupported severity level type, the severity level must fit into uintmax_t");

    protected:
        //! Factory implementation
        class BOOST_SYMBOL_VISIBLE impl :
            public attribute_value::impl
        {
        public:
            //! The method dispatches the value to the given object
            bool dispatch(type_dispatcher& dispatcher) BOOST_OVERRIDE
            {
                type_dispatcher::callback< value_type > callback = dispatcher.get_callback< value_type >();
                if (callback)
                {
                    callback(reinterpret_cast< value_type const& >(get_severity_level()));
                    return true;
                }
                else
                    return false;
            }

            //! The method is called when the attribute value is passed to another thread
            intrusive_ptr< attribute_value::impl > detach_from_thread() BOOST_OVERRIDE
            {
    #if !defined(BOOST_LOG_NO_THREADS)
                return new attributes::attribute_value_impl< value_type >(
                    reinterpret_cast< value_type const& >(get_severity_level()));
    #else
                // With multithreading disabled we may safely return this here. This method will not be called anyway.
                return this;
    #endif
            }
        };

    public:
        //! Default constructor
        severity_level() : attribute(new impl())
        {
        }
        //! Copy constructor
        severity_level(severity_level const& that) BOOST_NOEXCEPT : attribute(static_cast< attribute const& >(that))
        {
        }
        //! Move constructor
        severity_level(BOOST_RV_REF(severity_level) that) BOOST_NOEXCEPT : attribute(boost::move(static_cast< attribute& >(that)))
        {
        }
        //! Constructor for casting support
        explicit severity_level(attributes::cast_source const& source) :
            attribute(source.as< impl >())
        {
        }

        /*!
         * Copy assignment
         */
        severity_level& operator= (BOOST_COPY_ASSIGN_REF(severity_level) that) BOOST_NOEXCEPT
        {
            attribute::operator= (static_cast< attribute const& >(that));
            return *this;
        }

        /*!
         * Move assignment
         */
        severity_level& operator= (BOOST_RV_REF(severity_level) that) BOOST_NOEXCEPT
        {
            this->swap(that);
            return *this;
        }

        //! The method sets the actual level
        void set_value(value_type level)
        {
            reinterpret_cast< value_type& >(get_severity_level()) = level;
        }
    };

} // namespace aux

/*!
 * \brief Severity level feature implementation
 */
template< typename BaseT, typename LevelT = int >
class basic_severity_logger :
    public BaseT
{
    //! Base type
    typedef BaseT base_type;
    typedef basic_severity_logger this_type;
    BOOST_COPYABLE_AND_MOVABLE_ALT(this_type)

public:
    //! Character type
    typedef typename base_type::char_type char_type;
    //! Final type
    typedef typename base_type::final_type final_type;
    //! Threading model being used
    typedef typename base_type::threading_model threading_model;

    //! Severity level type
    typedef LevelT severity_level;
    //! Severity attribute type
    typedef aux::severity_level< severity_level > severity_attribute;

#if defined(BOOST_LOG_DOXYGEN_PASS)
    //! Lock requirement for the \c open_record_unlocked method
    typedef typename strictest_lock<
        typename base_type::open_record_lock,
        no_lock< threading_model >
    >::type open_record_lock;
#endif // defined(BOOST_LOG_DOXYGEN_PASS)

    //! Lock requirement for the \c swap_unlocked method
    typedef typename strictest_lock<
        typename base_type::swap_lock,
#ifndef BOOST_LOG_NO_THREADS
        boost::log::aux::multiple_unique_lock2< threading_model, threading_model >
#else
        no_lock< threading_model >
#endif // !defined(BOOST_LOG_NO_THREADS)
    >::type swap_lock;

private:
    //! Default severity
    severity_level m_DefaultSeverity;
    //! Severity attribute
    severity_attribute m_SeverityAttr;

public:
    /*!
     * Default constructor. The constructed logger will have a severity attribute registered.
     * The default level for log records will be 0.
     */
    basic_severity_logger() :
        base_type(),
        m_DefaultSeverity(static_cast< severity_level >(0))
    {
        base_type::add_attribute_unlocked(boost::log::aux::default_attribute_names::severity(), m_SeverityAttr);
    }
    /*!
     * Copy constructor
     */
    basic_severity_logger(basic_severity_logger const& that) :
        base_type(static_cast< base_type const& >(that)),
        m_DefaultSeverity(that.m_DefaultSeverity),
        m_SeverityAttr(that.m_SeverityAttr)
    {
        // Our attributes must refer to our severity attribute
        base_type::attributes()[boost::log::aux::default_attribute_names::severity()] = m_SeverityAttr;
    }
    /*!
     * Move constructor
     */
    basic_severity_logger(BOOST_RV_REF(basic_severity_logger) that) BOOST_NOEXCEPT_IF(boost::is_nothrow_move_constructible< base_type >::value &&
                                                                                      boost::is_nothrow_move_constructible< severity_level >::value &&
                                                                                      boost::is_nothrow_move_constructible< severity_attribute >::value) :
        base_type(boost::move(static_cast< base_type& >(that))),
        m_DefaultSeverity(boost::move(that.m_DefaultSeverity)),
        m_SeverityAttr(boost::move(that.m_SeverityAttr))
    {
    }
    /*!
     * Constructor with named arguments. Allows to setup the default level for log records.
     *
     * \param args A set of named arguments. The following arguments are supported:
     *             \li \c severity - default severity value
     */
    template< typename ArgsT >
    explicit basic_severity_logger(ArgsT const& args) :
        base_type(args),
        m_DefaultSeverity(args[keywords::severity | severity_level()])
    {
        base_type::add_attribute_unlocked(boost::log::aux::default_attribute_names::severity(), m_SeverityAttr);
    }

    /*!
     * Default severity value getter
     */
    severity_level default_severity() const { return m_DefaultSeverity; }

protected:
    /*!
     * Severity attribute accessor
     */
    severity_attribute const& get_severity_attribute() const { return m_SeverityAttr; }

    /*!
     * Unlocked \c open_record
     */
    template< typename ArgsT >
    record open_record_unlocked(ArgsT const& args)
    {
        m_SeverityAttr.set_value(args[keywords::severity | m_DefaultSeverity]);
        return base_type::open_record_unlocked(args);
    }

    //! Unlocked \c swap
    void swap_unlocked(basic_severity_logger& that)
    {
        base_type::swap_unlocked(static_cast< base_type& >(that));
        boost::swap(m_DefaultSeverity, that.m_DefaultSeverity);
        m_SeverityAttr.swap(that.m_SeverityAttr);
    }
};

/*!
 * \brief Severity level support feature
 *
 * The logger with this feature registers a special attribute with an integral value type on construction.
 * This attribute will provide severity level for each log record being made through the logger.
 * The severity level can be omitted on logging record construction, in which case the default
 * level will be used. The default level can also be customized by passing it to the logger constructor.
 *
 * The type of the severity level attribute can be specified as a template parameter for the feature
 * template. By default, \c int will be used.
 */
template< typename LevelT = int >
struct severity
{
    template< typename BaseT >
    struct apply
    {
        typedef basic_severity_logger<
            BaseT,
            LevelT
        > type;
    };
};

} // namespace sources

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

//! The macro allows to put a record with a specific severity level into log
#define BOOST_LOG_STREAM_SEV(logger, lvl)\
    BOOST_LOG_STREAM_WITH_PARAMS((logger), (::boost::log::keywords::severity = (lvl)))

#ifndef BOOST_LOG_NO_SHORTHAND_NAMES

//! An equivalent to BOOST_LOG_STREAM_SEV(logger, lvl)
#define BOOST_LOG_SEV(logger, lvl) BOOST_LOG_STREAM_SEV(logger, lvl)

#endif // BOOST_LOG_NO_SHORTHAND_NAMES

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SOURCES_SEVERITY_FEATURE_HPP_INCLUDED_

/* severity_feature.hpp
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
*/