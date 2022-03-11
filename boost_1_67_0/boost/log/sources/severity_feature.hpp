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
#include <boost/smart_ptr/intrusive_ptr.hpp>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
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
            bool dispatch(type_dispatcher& dispatcher)
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
            intrusive_ptr< attribute_value::impl > detach_from_thread()
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
        severity_level(severity_level const& that) : attribute(static_cast< attribute const& >(that))
        {
        }
        //! Move constructor
        severity_level(BOOST_RV_REF(severity_level) that) : attribute(boost::move(static_cast< attribute& >(that)))
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
        severity_level& operator= (BOOST_COPY_ASSIGN_REF(severity_level) that)
        {
            attribute::operator= (that);
            return *this;
        }

        /*!
         * Move assignment
         */
        severity_level& operator= (BOOST_RV_REF(severity_level) that)
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
        boost::log::aux::exclusive_lock_guard< threading_model >
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
        base_type::attributes()[boost::log::aux::default_attribute_names::severity()] = m_SeverityAttr;
    }
    /*!
     * Move constructor
     */
    basic_severity_logger(BOOST_RV_REF(basic_severity_logger) that) :
        base_type(boost::move(static_cast< base_type& >(that))),
        m_DefaultSeverity(boost::move(that.m_DefaultSeverity)),
        m_SeverityAttr(boost::move(that.m_SeverityAttr))
    {
        base_type::attributes()[boost::log::aux::default_attribute_names::severity()] = m_SeverityAttr;
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
        severity_level t = m_DefaultSeverity;
        m_DefaultSeverity = that.m_DefaultSeverity;
        that.m_DefaultSeverity = t;
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