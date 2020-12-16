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
        boost::log::aux::exclusive_lock_guard< threading_model >
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
        m_ChannelAttr(that.m_ChannelAttr)
    {
        base_type::attributes()[boost::log::aux::default_attribute_names::channel()] = m_ChannelAttr;
    }
    /*!
     * Move constructor
     */
    basic_channel_logger(BOOST_RV_REF(basic_channel_logger) that) :
        base_type(boost::move(static_cast< base_type& >(that))),
        m_ChannelAttr(boost::move(that.m_ChannelAttr))
    {
        base_type::attributes()[boost::log::aux::default_attribute_names::channel()] = m_ChannelAttr;
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
LtXM4+4H5v1gvNhd4i1kJegcb6SlHm3+C0ydnCV2V3jneqN07q7uyfHFzkETjprr+6UZf3xvaDXuu3HOFzeLvEmeLh7rGROTFlPP5lsLZ4vdLC9PF9p7qjfb66WH67PnXJ/dSzLr9U00u8G+cAQcC6fDhbAYroQXwyvhjfA2uBc+Cn8A/XLy10qYiZiEO4O0Te0Xs2dwGe+kokahZqKWo9ajtqMeQNWFQcmL+/5OG8IJGFu1njdLntI8vrYZe9JnZCxgrDkP9zABOcINdX+nT5sxbISjZiX1ZkP9ZrnGbOhov1lWvdlIv1lavdkwv1nrerNMv9mxc/1mQ0b5zV6tNxvuN9tTb2bSsr/eTPp+ova5VaiOrn5h7p1xywsZfYH4izPPD9POAsbVD5Md+f1Ky/NVVBTP2qrFpo9yPWvg86Oz1st6cfND6s2LaYbzNLTOZxc3Po5uFLunZT50Hq3xcftdfO4w9L1mrJE7fUXsFju2e6BeFru2pi29KfoMtedtbIm824rfo52lKZk54i/EbYFrPM0PuKPobbHvpf3Wo2HnE1ovt5+Ae4veFTc99BmAH42jFWYuPwH3J/1B3KSqXv2QYt/z9zwy9XCyvree0dM1Z5XqNv30BvGzj9yVi3xhGob7UPJe2ydmAK+1vWMGxkzhFTMszHGafKf1y6HfJuHewbxkhXmP9fXT8BDmspGNP0NM+zzcuc7jNTrP2YL6VrpPsMLfPotWBT33jbzZ5eJmk8znLrXLtRGO5S4/Lfc3xM5r7q06IvqeTld8plCGnxBJ6866NjEqZlCkNywZ8cxWvnBDWZ9Igt+TMPuRxq71z2Qxm0QfieK5GS7l2lnj20x8d+AxNjYhpq0vsraOzNFiMd+oacEuti3m/rnnnZb4/Xm8S+KKO2ncMtfT+Hd19s/12oid5FNl/fc1Y453oWWOd6yLyldoXS/TOW1mnta1zmZdY5EpxxG48elnWetZw9B7eo+Qhx1d6tp0WFxMOsXYob2rzopTZL4q/WsO7rahJM/eOHd5SDj7/HYRUa41ldDuWT7ZO9AjXQPnXzGod7KIz18WsgOzrCx/eY17XLXmHT/B7zy2MRZ3n2fttuCk7ylF3eo8DtEAMlG/Z8zaH5CPqvzq/PIarNzjV0lpYYkZa58V9wPt+0tNp9u1Bq/p1PDdZR6eUueYajX7EokiUONOqyyou8cbk8ZwcZdoSyNhhJZGW/8w5/VS6xyOUg8jtU2kmfSx3s9LsWw0WddM8CturfdxEk7DdmL2p8RumK3d4M/yXqzPu9PErpvqkd0WfVizy+FkbWyflksb1zvLO7SxKne5VBQvz68tXV0cwtpi1ReoK39byk0Lakuapg3uNFUWFTVWTxvFXWv7M+sUpK919zqHmkwnVdO3KyB9FRSXva3vFnddbenTMDx14ycRHELtZ57B7FzGyC+U7h5mHJHfYN33OuhOt3RRe7oPibsBtnQTRuN7Xq+KXR/7eQJXfmO7M1ahJL/dPl9+T7YXtqOHva3H5bvyv664ujKEdh6X32Q7mtpUfSztpTKyuje3Qvfm0kx6yop1d866N7dR3EV6UojlT/a9OcI6+d7c9vzAvbmtov/IaYVZPPtdN9v35gj35Htzg8X+PNmbuxg1yb83Z/wu9DwcuDeHeeN7c1eK3RHSdXPjaW1kb+474u78BntzaQWyzmj25p4Wdz+x7s0li9tM9I3vzY0S/wuse3OPit1Pne/q3twtPTDM+Px7c9PyG+7NrRezUfRQ3ZvTeDZnmL252/x7c+GYbUTV7c3d+YX25j7KD9ybOyT6x917c5KODzP8e3MZzd6byyk4+d7crIJ/397cVhUkKNOAV+g=
*/