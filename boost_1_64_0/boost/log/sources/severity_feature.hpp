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
EjtJ2PGbd+8mEo+AvhuXhtOdu4lX0/YfaEqdSqUOrFod7fPXERWICSTWmBSEnwuKa1WN9scEavNX9SoxVUkWMz/SONUo7/tVmvbb8r3lMU9Xc/nmCN5f3Ax/mO9gHMT0j2a+ZatnvLa/5V3HOi9Lezmtz7/eXh5pbAQzKfPUK8yoV9qG9tI29HpdnL9e+9MrUIyXsOa8TBu6qGD+4pm5C0umzXAq0K9mVbBfjbRnfzfCnrXNsfetWUfpL0V+fvn9pciXlt9finyetb+88xj7y+1Z/2z+l/+u1Ffzdk9rR36TydgacCIMvvfuP0LeypR9BfJ3v0ljk7+59vdfsRvZ95jzKQ6JbIi/Bb7egbqB7+N6fp2XN25zwvsye1kwZ2526BuUN/SvZByiiHM4PvVF2fuxrMh35iUZ/GfOvujaDzm3sswndcvrM1oNCO8zuoo+WuJ/AD+qSVz6+0vDKJpd4GlX/yphVJUwPwkLswbpZeLlJGu7PjLoH080mTBGutHceXSV84yP8EQeCj8W/eHzJcaJ/b/7PH2MiXubfmpX/W7RHz27rBL0WT4StyfzzTQk0n9zHsZbYqfI95yzxHOe6vSCkvxi0867YieT/Klp3NUUsz7+l1ivE3H2qa5t8KZFU09aTDNlo4/4UdNfKluuc/2ssxLZL77p9FknulWcPb4qznrqa3OdJ4/8rqX9NuPfGXp2Ku28qJs8/CGR+q12vO7npIgfuA93e7O6Q+G/KHUf/n1c7yjfx10HVPS7alruP/NddX3bcvqBgWXbioUV+D5OG1jB9n9gBdv/gcfQ/g88Svs/8Cjt/8CjtP8Dy2//txxr+z/w12//Q99HW3VjYScCqAI7Qmn/rXlasXGP/WXz1bQfSYOCsoO2fMZdxcZA9tvz2bwXfyfyNm5P5xV7m27Pe/Ne+oPIU92Bzo1mHLKPxDva+s6eHpQRlucd25STKiKr62o5KOedsCLrSqPi47KPvRxUtG6v6Giv24XZtnJQfNQyUJhdsbpdmF2xul2YXfG6jd0jz8FnH7lun5995Lq9Mbv8ur3jGOv2l/9Enla0bk9Ik7CwiTmqQMc00wZb8zRYuY+ar2mDK5avas+6RrmLyGY7Sfb5dtweeYzzRJEPsuW9urXX7UTYVeSnOImR85+at9NF3l3zNvw94DZUg9SK19d1g489bytaX7MzStdBR+u6/NeD49XheRtcJ56h+WryK1HT4mmxe5ZTR96ea9jHsE0+Sl0IW9Pccwgyz/rLuqKvYR/fjsgXV+ucLf/VrrWtfVdkY73jIWZewz9E52h1Xmu/2J0op5/Z5koS0P0idjrjBr3HTS3MPGtXTd/wnMhP5y01YM4HmhJfkfJgP/eeNNX89p79QtqY/I6V/E45Tvzi24cyDs+FE7pRt4fouS9alxnDTF+a7j0TrQhdadv1vNjv6VryWv1yvW7TvGuZPxZ5E9eWv7g1eXYwTsqZJW9t9vJMu7tJZCNcW7027kw+zjb5flBk9TzjTNMyvfNdj4k8weN2fun6BpFVcY2Mvrujlo1qQ4OyJ3HHPCGqO2o0ai7qTNRG1F1ODRPOZ+JXrKRf3aYYyF0FtnEjptMyStcaXCTuGpoy+bqEy9yvzmVfLfLF3ufTPNX11CInVqVyaR1C/m0ReZ6U0dYVHHcKP4dOylDEmUVaNrTckpemXMepXu9zkGcnPdCTHhHlet3xjvwW63lXJahxlOuVw8qU64ylPFX10rJpyvTLYrelSY+LRZ9obc/wV8u4Kafp3jJ+nsg7Wtowq1tNA741jXyop7zb3OSF1cezRd5N/Iiz+BFn9yPNm/+b1Y1t3FzdRo5lmvBeEHk7rzzd+0wqt4w=
*/