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
DV3D72QCCgEBzieX49YJP30U3rjYnbOOUDy+QSffnoaARmmiybOgwNN0BBCe03g7dXdAavuSJ5qBxgnFkHap4UypZCouV2fPp7+ps3dR9Dh+2KkbHCaeS3PGK7pYmiscGJikXmu4B/4lX7Dvj8X8cIZ+/4Zoxm/cHPgZCNCL3gA5h/fZEdqk9AhOj+RYhv28TRD/CZMnRdqSVrIoX73o9py++bqXexyxcvpZ7IorTPlZwnmANCA42MfoPmTSxaBx3+gbWFjauF1lQcrOd+SfX1uRF+xk5S6eRK+OV0npYb2KWRgdHqHK/F9k4hi32dqazy6MuUdKDS8xuc0qp63g51+DB0ezKzHl6Z+R+Ge63XKW7KEhMH58sl2X7O3bjD7a15xBX7rDbZQqFUL3+fGSF8QfVRiqxSkNtQsj02NdlKu9YYONMUR9QHmBcCb6gpFFP8MYlRuzveKwYGGQ2dmhU+L27jB/NQEIV1FvqNNnXM5t3PMwINiC4/5tpf/rERfpuQwH7ziGf8bKnxbqYFDppX08XO8ErxCH/mnQNfTlhJIfaSufr7B64BtFX6zLBOCt+XkbH9nZdlndHXPgWencjL/R6TcCuwqvd0ncqf/K5Gz4L9/X/ij6NL1GJTgKvvklOoU1EhyOBfUIArkxdAeTJRVcVLnNKhh+iT6B6g9AkbtUqJmxFOlJRmBFdX6nMDx42G+hvmK6lbF6KlpJVWBCSbHNas3QvIC7RONttwJ/X9inlorRY3tDw4JS6QQn+Sgnb/HirJK52bpbLwbUXlv3fSfOgBIhx85MvssuykDNfg25138OvzQfl3Yjz6uyDJFznp+lnmcH69bx2OYQtrramGD0D1ba0wQi9aUokmYlvJRQ2YpSGNalTctVudNXT1Va2Jub6WInlMWT3nUexZrhCQYzkAgNenaWxhrPXBPdIvDT+W6O27BvjX7OiSl4ox/E1fKOxm27JCH4a2rBp8VdjWq7CdPuo2Gtkr2/+Zp8diY77Cg7NsWrP58AYHmYvooRqVOzh90WWIUGJnnDsz++RIZfuw8ictr3dkuLnQeF8fKPXeJdq1mNfJ8oFrwyk9b1/OIBwS8fwPg4rO93M1ykiK00Yoks6wwAAYLh/3gYZprA5NEm/6V2ljtYNEwfCv/ibcK0Cwm3w3/7Yj9j9umJA7GIbmp3os9b1c96SyiWy8V9g0uZKMa9Ruelz9mcPGd3++DxyvAkeZGpNB+xhFcHbHWEKEbdFp2Z33nZCmLSOqrnUO7RxRX8dtDpwzBVlru2ox7Mwa/AOifmunWJxgv3G38/F4t6sMeasFJZX8KzVMSRu03kVVFVL1PZI9MFF+oCzv90vPpxD+t5gIxHgf2zDKHqoNBwu5Gl5CtoQgLWf7N/uLqN5DIB3UiRuMqWPjPIcMlAtEREuXZgICGZeqhvDEy5n7XANFCYdQ9/3TRy5ps8nj/5Xvzf0kXlCP532wftO/gvyx77xktPfmLwtV5WE+qiH/U0qB9/Bdk2dP89n+fd6x6yL+szaH45fNDTbB/ppOM//KXo2Pg0ZIAcz9BjMffHbZssPWibFZ53w/8zJvIdnnOUZi6ZXvZeHUW5ab/6YqfS5f8v4wcnUJV/TNZb/4aG5kuUtMj6e9VAnZ8t104LdCBZaflAwKGC69KE8yCNtaUj/2ZuyP9GUhcjvLx5ephCnPfa5SMLU1/rDRl609O/53MMSEf76ne/EJ4/4alltAOxVq+jSmWdtTT4yFgHD5GARzJrSH6j03QXOnhk6L8zwaRDA/Sv3wiEt34sb0eq4MFi/bvOl0NXYxDvrq7grwe4lP9WHSvwv5Ff5GZDo9JTf7l2jXVhnq7Sxuwr2zZdbaBv/ngyTqk/FGb2Z4ZRjpON8qPPgDyEdZWP9dSsaZVod90ol791HH80NftMw3yp84paghUFryLjmL5zaUkREZQi5U/26f8/mjYQUuk9xMBkdB7/ucgMMakUUqF/N1meT1ngKETEYgxHeooXP81FouoGBE76/pABaQWvTBqsQXnl3SdnPjdupTggfuppaCGx/SuG9KXW6BzA9muamo/D7boOsVVts0zOT0z18aqGKrV2Pe6kFfAjEbFJe0elgy5e/M9Ui1LkGDC+u9rUQG9RvqxL+7HB7zpFejC+4ICGLjaISP/9l/RLYpsDCceRM7LIBl/xII/06AeQiD4dv572+SO6NSwPFBOT0HLVwClF9CCiourU/UY6B/3C+PvukKBXgFeniLAaTWTAUIGPo8BWFeaRLuE/QtG/5jIkZF/JOPlQAyplfCCaUJ6WRiez69sz3P9PC75PYn6v9icy+aJ8Sbqr30Hd/Cdza8E/mEIk0PdSYcExFe9JvWlAV0+gEqbjc2na/ODPjyO5KHRQO7YVdR6G33gkuq0q/1poHZt3P/Z1kXqMilx+qMNxP12z/UCXMfb1qyMW7BbMWfH5uy2jiaeCE/b5j1unbNKCXKmEx0Gt+DU7plK9H7hEKisEQHJv/1WWcA0ZO3WSfSIM/DPeT0HwvvDHHq9fVM2gyPdlOED+/bI573/5oOO42biJIB9YGgDwlQ6xeQrnIq3MXdSoWphYJ6mgM4kPdHcXynld+T+SC2cUI/AhIfV3CQ9A68tgNJ9iSRo58XoiLt+nPZyn7Lhl2RZNqGON9kAx87Az/KC143iagP/VBatE6dsdra5e2tf1E5a2Ow10dPjaPQydSos0sLM1oG+BARwi6tsBBTPL+O1//OD22Yw+zyfpXaJQW3zfD+vdIhjVBZSpq/xixsoxH7TlMiQkaT3g33WQJRVILfhLjn6+/mld021X1PFxn+jhMRFqdx0xNzLqVnEtNuVHWkT+Lw6JmQE3Dm0GMkYWxJ+ckZ5yHZ2n0pe7qpr52EDLROxY+t+Omx5AtE8Krzk+g5I5Tz5s/7e7PaXRQhU0rRAkoFG6jRkZ1IUGJQGByhBo0Y23r22B7tnxct/QL19MC747rW4Ls4Yg87s14fJVKpDFk/jXvwh5jnJLjLeFzB5+ZwnyvyKYgNQlLvPDMlNFbd2HzaYmNyZh+oFjOz+6yV+66uEbNQz8cwfrn1U3Tl1d/Dxv57Uv66DA6J6UP+hZsYGi6hmkHM0DSRnbT4p2Ixu1gS9b/0D59af+AiSMPm+zDmD3Ps3WEYxSRA0V8ZzOmBCpAz8d54mOVRC1uVs2pC9vab8JCPneZrqXccDT8vyzGcGmyqTUSRnnRP9enAP2zeBD5jJPhoPZ4WhjEInANMsx4obK68wc/KpxwLBixNz/yr3HWpqjnV31wnb8ae8YjfNM1k/C2ym9caVV7EtF2zwKS5Vxms/9BsoZn+eoN7dKKiucg/4vE1IpmkP77LseRXrLNuLSRxtM3/OKSbT+tCaA+ngc25DYABiW9O3/MJRXdDmReN5Ce+YvgP/hBJLCjU1shZMS+78a2hFoClHTDo5d4X6tpY+uGuuLGo5zuTgA+ur5fPShT6j8o9LbVoHD922tnmVIDULg2b7b/zd7FlyeRv/YeTgCRv1+J9Pf8OHHo/RbVMe6dfBTkV85qe/nUON57VZSzTwEO35zWFgMhhkxi/QrNVNPhJpp1dbDhONPBbIFXJ3XWaW9TGouXt4dr3l9roO+5GovGsaVShoftHD42L0HgACAQ0sBAID/f371b6ImiE7AnM46na3wP3sEHs8Abhu7uIvbcO1i03M6BqfcxnOjrH1PGTz7vz3eVBj/rxuobAdEN4S7svpvyOwGk/0D5hXTYt9pSfjBZZ8PO/Z7PKdenEshBEUJYQy+d+ag7yf0p8n/TyulbcUE/dP554mRT3tmqay+HYA5O7oERn1C+Z/3d5kYV8d5zQOjD/T9mWHmP5tTzJ3shUOYhILUZJdMZzpuWekENDDbH+DR31dJsGkQPmAG9O2epktymT8aZsu+G/c4IMBaIPPFWPMO9cFyU25ERfyKO0D2pxACYjMUa2kEs1CoWs1WoU7OAY01iV//wPz40VhQAU62o6dwcu5wwkD5RxYgvYjPK6irQaCXv+/+z3Tn6JXP7dmvsFErOHXOZ87/1Q/pgf7OF9RA4Ajs7DONIujPA/VIBji1ToYVSwCoUBeyMLJnmYxUUB/D8eVjH0X9dbQk2UfiRAFGBUMDcOKW+ue+Dt5qgVrQInzuJ+RsQgtyHaM6d6STVt1/EPCrAbg9X7F2JX258vuApXs8BTE0vkHTviHLWCk0Jn+4x2U8dYBOJjAgeTD+tDvCDqyQVoPr/uoyb5eeR5Go9te2y7EGwf4je4kV21D7wOV5MpFFKXv1C1veHppL3xv3kPX9N3fL+vvVKDx7Wh+HYxsNnL7cv7+/B1jUGrO0c9ot915dEhi3IG7yLCKt1yD9bThjvf83VD+qDvn18mbRhU9/ROpz8D86H1c19dC+XzO8V9qrIelh0y7Q0B0FY0UUax31r83+ST7rDvqy+f90FxC2ll+p9MdG77+1MEElhlCoEV9V/xYcy6pDVm8I2lua8rgozJKyeKZVw6IqnE2RD2BRNkE6CINokcvkWjJyQiRqaxLA2XQm0UA9TBfzifgQ22iQDvedgtQ9J9U1p4La+sq5GYAyrpvGgjy/tA8FMcUsYy96mjw54naVy6yoR9bNjcGNu7Qr5UcMZm9VAMHSHkZfHbSvfh3YHqRgNu7UanDzgAalUhUtlJrDrypyXLbuBEHhEwEVrAm2/m0sPjDEazBWASUOij/4byguujt5e55JMgKp8G/Fe6F+95BdUK1oQCSRNhwDALLD3T/S/zOq7V8VKswTbsCoUz5C6/9tYYxsw8HjWYD84cKg7Nk7x+q6gAO8Nr/yQLG2vn0U9fMUngigktKa35Wjq9IT239SA3QagSX46X87YbApPRzA2tdDDXJ7hNwSPQ6s/Eg/hEgiODOOAhMMwNKqzANPdxO9v/9k75H1GtFyWn2OD4cobt9PDeIVl/+6AWBpknsf8qN9+fj2/yEXlUFGHEGA90uC3Foo+GFj6xPTQoyBCoyaCmEYmzn1Ay2AoY/QfddMClLCiSvMg/4vdDJ+PbXD/loMNlemMM8Cvv8hvK6Gg/yWHX/mIwtOjVut08S/ImTFShJidoRVmuNVnP+uapIGoS0Y/3fwbv698u92Sg8kEwZ9z+9MVLz/veeqG5QrRta49f+IgpMgRE13ZyhfTWXe22RsIVKFWwaLJcL1U9Qfwz+m1k3ECfqzsaroEGgQaV1p2q7yD7cwT+Nte3mh21agjUXc4OoXUmgz4eGZukWZvS3DQptWc8B8GMp/RXdu/YIzy9X3+xPSA3W2t3jW22bYP4no9xqheEoO8BQoy/KfZ3otbefJu3MgyjBtEZhzZNy0Ax9+HnvaiFUb7Oiwl8KW6d2J26GnwORTK8mTHbrjXpJy6oXsG0I9dWXpdFUro7kvomt+uK57EvNYhZoZoP+p9iCkpFFD/pdEHoxxQYK4oLwpkDelckOVm9P0Zay/mJUSSE6oc+lfD2nUgTkZFlM9mRIgt3xvU3/vob+x5LrnnZFHimkX/7OpnAjhr4cvmtpCb261aQ7+bg9ebPvueHD6USPWyBd6TMJuv4HFUp7GUOvaqhIZdFWFPgAcKB8+Mi+WCrXblwsV/2vwPC2Q00X2RHQjQ0mMMxjCAXGikNTtozlz6zl703VO3fdsrxr2rAv3pqmLZgp1myDwh6GYcalcNZY17uHUwSkNgaX2ouRY/U5x1K/qKblqkw1Hz7iVzP/UJENYv/skgWg2PdqZUisxNmF8yztCe3nZOVvXREbuZ0lS0DXbGSxb1pKEVGNZWNSp90eJKJyeQpqm08g8adwWTCeRCkXxj23GnX325wLq5FMqJHqJU25ft4w1SJ/RNtRTkJYO154x7guf7ya+WT9pjK/FEGHUUoDo3eJzChvbvu8GU/oggIGNqJ9RgxT0Qwa1t2CbrK7mLpIapmDU+dwnblj7jZBbPF7mkXt2Z1Rl3RGKzsN2G6eb26HdNbljLJ2KSF7iU/luwJVKnfhcWYUMk5oy//3deo2Zscduqsp1fX/dtMwnFfgl2LCuK6NucbIReIxMtzejMaeb/GrRdg2CHJoNWcsz+g3ECYq0stmSZXhvcX3ngv9sFYVCT5emv8NzAtvJIoXFOIoQ2E6uxXVePNddhTjy0CNJbQB6yTJkS3RBb9rX1qa7CDFakdn6VoKs6kqyvG46dDlB8TR4CTCtVojSXjkGiXaFhLXTH+1qXB1IPizdrsQq3PIQTTje+U0ykLwCyTM9luro7KYw3c7u4BkBX/bDdyQFwIhl7jDRNFHWkzjL4N8bFB1sLIp8oQWJLml8ofxgt/AK4ns5FQi8ugwsSf1o991uYtMtz3p34zI/Hq6hqz8+QBSIoh6pbwPPAcTF5acsnG8Qj7rlITR57w7qgGj8KXW2eZH9GJOl0QKY/JinWQsU6Rritis3yZICD5MlQekTpWUehVsR4+OUUwdccoAhJmBrmS5jErsp0e9LKeUWGZRzL5RoKN6d2QkCZ7ex8G78ml1rWgYsgP2q3D/2QIl23wejSI3F3wBxesfch4IRmLtUYFGZJEfWwrvBIBJ0UDnzDp0k69J6DBI/GsydTKYMdqlc0yHdDbfx6YgAa02dyHL+YLc+eSnlQHTVoTk8KOtWYQ7iPaTHoWQplVVeFlzVRzzAm0mFrO++6unNo9oooCuRyrRXg9FXXqT0DZXGnplumIixYufeCp0msTnkCjK9wu2wS+4eerHA+tiVUXxi1XI3JuzKVrNxe4xV5RY1T9Vfl0rWggfjt/b9pKvIpbHrgROPWpZ23gmqqgvbb8LY+xPrbh4XYcjXg4Ho9ZTO9ciYOwZuH19alXZ8jJml8+gnNB4ROMppopJ/S98cPXF0bIl7ntRauFKLqPSCclFbL32Ij9FjboFIrHPLfJ1tYS278l/V3PMy0kkpRBt4iXSsPQ/0rgupz0JMp2W5YB8GkdcvHKA+3qrTN+FqhiJUtWB8gpJkgmKe3CBqd/JjVL3L+8fUCSpnNt0BSfPhEH9d36HdXnt8rpYTKOq/BEJRPpU7jHHrOP2f83FgoxxniQkf1UscjCG4QoM/qx6z3Om8ZMowWhogACoqSIxfsn1vaQHUviWIRIURKBuKZAfGWMYcFaEHAIJFn5qppxe4uICfUomnvCrBUtdgCgVWf8mMKdp3nj0UkhfnYml0eQcMZvfD8GhsFUbeqeIT5uCclIsDW1Ql+Dhmg0sXUZibqlaexDyXV/HLhZO9Q4eyozdZ2IfmgNSnImRRCukt8OCpxkvJO9UofXxHhK0Wgrta9rBxUfIvYQDx71EHIWaw/OjFRh2E251yTHbe10mTaAxs+pFNq+e+3/J5tSfIqFOQ5ZZbEaBuiOKtZzOpow8auZm6tlCPlqXcMgpAd1f51wVgA9XX5PJfK/dzDO42cokcENvEwnJyNzb69VlG1tf7KisffGcdeA+lksB5Htjzz1/br8twOufIieRcadyR5xJYbHMayep02L0dlQMnNLQnjYW7B+9SWFbV7dCLTKR22Ru3NwbmIRHH9QrIqFKo+JJKN3hzH+ExQNUvbWnCXxVEL7Q/Xv6ccYKcQZnru9si/idTSqGurLs1nekj1F6fdNfP3VGiymMaYvEkwhGh7kdrXdF7bhiP0dh58ZJ1KlUmOFItZLfUTL612wumeqYYXARpo6jIY372gOzBpPOqsjNyYGoHvbof8p104RRTm893ufm9JOnm6VADifYYIt5V1sOy/2X6KgrH+8mUen83x/jy3GjMn5k8rY+3VVVTSKWntdbCDs8Jlwc7ghIXyOzmHmYGdaLgsaj08i5PQsw+L9pL8nozrM6ZyM8pQcUVflJUO7NerZWKq14ay6ffTtFysty6EpQsyttqYp9ExC5OoWpwQQ2tU7/3vrYidNz5ur7S5T8izJ7axf0xpv+PkmF7cCRWt2DTMWO/NTSfuxfW32HTsE1p8iLIRXjj8U95XVIG6eeMakwo2fV0UaxRT2rpuBW7qkG29KfEseimCrPkqsL1HNlN5TCI5JGHGESKmfA3c5DY6BUuqw3X8CgFU+JIv+cfJcojMADCa9vM3bwjni1mGEIADSzy09O7iUcCayKZf2sChucpIEdyCOERuDI37qRiPPddWxZ+Vv2VO0geVWshIXXEaVLznaBQmAWkcPgJ3kTRN7S7HgFcdEFrAJ88n2Oe1RYvAtGFH6wMPOBIsRBXwTVhq+Bc8enKILHityaxrxEIeNklgPMyXavCbkxEUhtUaPOVgW8szKbktDNsbhR2CPxN43bHRqryaEKnFgaquzUEjwIhC0cSiJmR0i1R5u4fEYmh6qVaKpUrIWBuDC9qBSlZ/nhUSqlDZUt5Bq3jUnA/I5L2WcLqx9lqKhJU9g+/8TGRNlK1Dq7JS0RF5IEnfPfeVk1eHpENogR9fDfxwx605m2HHtj/VqkckSgHsJayq3BtqD8x7WIWYz67qDgffteRKHT3uicin7fCfNNz8UdQCmmYzDaqo2zt+SWeGMxWc2qBc76QbF9WXpLOL1K91aEApEF1QuU8HCbhodFTHhyjNX9sn0YnB2C4hyky5zxb8K9Z9448VPRbh/p6nCQI5fYTK5QGIzALHeuaVLc3Jse8HDJx9x1hWcb08Q3QO8PDS8VsJyMZaOlB8Ms+oppf7+KOuuelXQ/wUERvK2DZBftr11tn/mgzl6kxKmctFEV1Yb2vb19K/I777SUP4wEVdBK81foduFLn4Ms28fkqbmRtjdfeysIZJbwzITNDijgbXFt3Q1OE+/I5ufbwVPoeyGYZKRK0X8XPjTug5NiMqZPlGesKIFKwTRYwOdVylVEzLDjO2IfdU7i1ZcgqfrIBXskfTsyCZ1PjON5YVElW+trVB3v6mqIBWdzmtSZjVmEtkR7ILycZ0Rsbinha0+fxxVDvfvmCqKZCa/ykjPb6XfxXXo+PECkBySJ1n6wXRE8CtU0pzHGekhSxhmv+CBAWaSBoGPyrfCjlXPtuzL42JAaBVcg64pL94D3ayUXd9GrDZk8Kg1b/YxdSKcLJvOYtZ+Uj1kZERIbyiGCjKcNVqdYYXsV5EyuXsW6T01iHqHdBEpmRKwXrjzwbLX0CJPFckWoflhJQZO7p0EwaBbjmuSkdqOeP5Tb7F9ppgHZbvf/yfDzydSQTyhhfKn/+9kgXSp9w2mk=
*/