/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   channel_feature.hpp
 * \author Andrey Semashev
 * \date   28.02.2008
 *
 * The header contains implementation of a channel support feature.
 */

#ifndef BOOST_LOG_SOURCES_CHANNEL_FEATURE_HPP_INCLUDED_
#define BOOST_LOG_SOURCES_CHANNEL_FEATURE_HPP_INCLUDED_

#include <string>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/type_traits/is_nothrow_move_constructible.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/locks.hpp>
#include <boost/log/detail/default_attribute_names.hpp>
#include <boost/log/keywords/channel.hpp>
#include <boost/log/attributes/mutable_constant.hpp>
#include <boost/log/utility/strictest_lock.hpp>
#include <boost/log/core/record.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sources {

/*!
 * \brief Channel feature implementation
 */
template< typename BaseT, typename ChannelT >
class basic_channel_logger :
    public BaseT
{
    //! Base type
    typedef BaseT base_type;
    typedef basic_channel_logger this_type;
    BOOST_COPYABLE_AND_MOVABLE_ALT(this_type)

public:
    //! Character type
    typedef typename base_type::char_type char_type;
    //! Final type
    typedef typename base_type::final_type final_type;
    //! Threading model being used
    typedef typename base_type::threading_model threading_model;

    //! Channel type
    typedef ChannelT channel_type;
    //! Channel attribute type
    typedef attributes::mutable_constant< channel_type > channel_attribute;

    //! Lock requirement for the \c open_record_unlocked method
    typedef typename strictest_lock<
        typename base_type::open_record_lock,
#ifndef BOOST_LOG_NO_THREADS
        boost::log::aux::exclusive_lock_guard< threading_model >
#else
        no_lock< threading_model >
#endif // !defined(BOOST_LOG_NO_THREADS)
    >::type open_record_lock;

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
    //! Default channel name generator
    struct make_default_channel_name
    {
        typedef channel_type result_type;
        result_type operator() () const { return result_type(); }
    };

private:
    //! Channel attribute
    channel_attribute m_ChannelAttr;

public:
    /*!
     * Default constructor. The constructed logger has the default-constructed channel name.
     */
    basic_channel_logger() : base_type(), m_ChannelAttr(channel_type())
    {
        base_type::add_attribute_unlocked(boost::log::aux::default_attribute_names::channel(), m_ChannelAttr);
    }
    /*!
     * Copy constructor
     */
    basic_channel_logger(basic_channel_logger const& that) :
        base_type(static_cast< base_type const& >(that)),
        m_ChannelAttr(that.m_ChannelAttr.get())
    {
        // Our attributes must refer to our channel attribute
        base_type::attributes()[boost::log::aux::default_attribute_names::channel()] = m_ChannelAttr;
    }
    /*!
     * Move constructor
     */
    basic_channel_logger(BOOST_RV_REF(basic_channel_logger) that) BOOST_NOEXCEPT_IF(boost::is_nothrow_move_constructible< base_type >::value && boost::is_nothrow_move_constructible< channel_attribute >::value) :
        base_type(boost::move(static_cast< base_type& >(that))),
        m_ChannelAttr(boost::move(that.m_ChannelAttr))
    {
    }
    /*!
     * Constructor with arguments. Allows to register a channel name attribute on construction.
     *
     * \param args A set of named arguments. The following arguments are supported:
     *             \li \c channel - a string that represents the channel name
     */
    template< typename ArgsT >
    explicit basic_channel_logger(ArgsT const& args) :
        base_type(args),
        m_ChannelAttr(args[keywords::channel || make_default_channel_name()])
    {
        base_type::add_attribute_unlocked(boost::log::aux::default_attribute_names::channel(), m_ChannelAttr);
    }

    /*!
     * The observer of the channel name
     *
     * \return The channel name that was set by the logger
     */
    channel_type channel() const
    {
        BOOST_LOG_EXPR_IF_MT(boost::log::aux::shared_lock_guard< const threading_model > lock(this->get_threading_model());)
        return m_ChannelAttr.get();
    }

    /*!
     * The setter of the channel name
     *
     * \param ch The channel name to be set for the logger
     */
    void channel(channel_type const& ch)
    {
        BOOST_LOG_EXPR_IF_MT(boost::log::aux::exclusive_lock_guard< threading_model > lock(this->get_threading_model());)
        m_ChannelAttr.set(ch);
    }

protected:
    /*!
     * Channel attribute accessor
     */
    channel_attribute const& get_channel_attribute() const { return m_ChannelAttr; }

    /*!
     * Unlocked \c open_record
     */
    template< typename ArgsT >
    record open_record_unlocked(ArgsT const& args)
    {
        return open_record_with_channel_unlocked(args, args[keywords::channel | parameter::void_()]);
    }

    /*!
     * Unlocked swap
     */
    void swap_unlocked(basic_channel_logger& that)
    {
        base_type::swap_unlocked(static_cast< base_type& >(that));
        m_ChannelAttr.swap(that.m_ChannelAttr);
    }

private:
    //! The \c open_record implementation for the case when the channel is specified in log statement
    template< typename ArgsT, typename T >
    record open_record_with_channel_unlocked(ArgsT const& args, T const& ch)
    {
        m_ChannelAttr.set(ch);
        return base_type::open_record_unlocked(args);
    }
    //! The \c open_record implementation for the case when the channel is not specified in log statement
    template< typename ArgsT >
    record open_record_with_channel_unlocked(ArgsT const& args, parameter::void_)
    {
        return base_type::open_record_unlocked(args);
    }
};

/*!
 * \brief Channel support feature
 *
 * The logger with this feature automatically registers an attribute with the specified
 * on construction value, which is a channel name. The channel name can be modified
 * through the logger life time, either by calling the \c channel method or by specifying
 * the name in the logging statement.
 *
 * The type of the channel name can be customized by providing it as a template parameter
 * to the feature template. By default, a string will be used.
 */
template< typename ChannelT = std::string >
struct channel
{
    template< typename BaseT >
    struct apply
    {
        typedef basic_channel_logger<
            BaseT,
            ChannelT
        > type;
    };
};

} // namespace sources

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

//! The macro allows to put a record with a specific channel name into log
#define BOOST_LOG_STREAM_CHANNEL(logger, chan)\
    BOOST_LOG_STREAM_WITH_PARAMS((logger), (::boost::log::keywords::channel = (chan)))

#ifndef BOOST_LOG_NO_SHORTHAND_NAMES

//! An equivalent to BOOST_LOG_STREAM_CHANNEL(logger, chan)
#define BOOST_LOG_CHANNEL(logger, chan) BOOST_LOG_STREAM_CHANNEL(logger, chan)

#endif // BOOST_LOG_NO_SHORTHAND_NAMES

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SOURCES_CHANNEL_FEATURE_HPP_INCLUDED_

/* channel_feature.hpp
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
*/