/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   message.hpp
 * \author Andrey Semashev
 * \date   13.07.2012
 *
 * The header contains log message keyword declaration.
 */

#ifndef BOOST_LOG_EXPRESSIONS_MESSAGE_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_MESSAGE_HPP_INCLUDED_

#include <string>
#include <boost/mpl/vector.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/default_attribute_names.hpp>
#include <boost/log/expressions/keyword.hpp>
#include <boost/log/expressions/is_keyword_descriptor.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

namespace tag {

/*!
 * Generic log message attribute descriptor.
 */
struct message :
    public keyword_descriptor
{
    // The attribute value type here is not essential since message attributes are not intended to be created via the keyword
    typedef void attribute_type;

#if defined(BOOST_LOG_USE_CHAR) && defined(BOOST_LOG_USE_WCHAR_T)
    typedef mpl::vector2< std::string, std::wstring > value_type;
#elif defined(BOOST_LOG_USE_CHAR)
    typedef std::string value_type;
#elif defined(BOOST_LOG_USE_WCHAR_T)
    typedef std::wstring value_type;
#endif

    static attribute_name get_name() { return boost::log::aux::default_attribute_names::message(); }
};

#if defined(BOOST_LOG_USE_CHAR)
/*!
 * Narrow character log message attribute descriptor.
 */
struct smessage :
    public keyword_descriptor
{
    // The attribute value type here is not essential since message attributes are not intended to be created via the keyword
    typedef void attribute_type;
    typedef std::string value_type;

    static attribute_name get_name() { return boost::log::aux::default_attribute_names::message(); }
};
#endif

#if defined(BOOST_LOG_USE_WCHAR_T)
/*!
 * Wide character log message attribute descriptor.
 */
struct wmessage :
    public keyword_descriptor
{
    // The attribute value type here is not essential since message attributes are not intended to be created via the keyword
    typedef void attribute_type;
    typedef std::wstring value_type;

    static attribute_name get_name() { return boost::log::aux::default_attribute_names::message(); }
};
#endif

} // namespace tag

/*!
 * Generic message keyword type.
 */
typedef attribute_keyword< tag::message > message_type;
/*!
 * Generic message keyword.
 */
const message_type message = {};

#if defined(BOOST_LOG_USE_CHAR)
/*!
 * Narrow message keyword type.
 */
typedef attribute_keyword< tag::smessage > smessage_type;
/*!
 * Narrow message keyword.
 */
const smessage_type smessage = {};
#endif

#if defined(BOOST_LOG_USE_WCHAR_T)
/*!
 * Wide message keyword type.
 */
typedef attribute_keyword< tag::wmessage > wmessage_type;
/*!
 * Wide message keyword.
 */
const wmessage_type wmessage = {};
#endif

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_MESSAGE_HPP_INCLUDED_

/* message.hpp
ugkTW3MQOZxsOkncEQWduIhwROuMyQfkmcmfhYmo3gWTCrVeajLrwTDBZmABuhAWk4Qs3qZXVgbF4bC5gkTDDtKLYwkavXpF1dCxDNE/qAYbK8C634EnKgfVAxqifzMs8SQAHpCnL3WY672XRGWDvTMzm3TCk+MkVbmJzKqr2GwwOT+Y4ateC70dFly4KIVSdvi5k6ZdOoHrbUwqnKB+oylUXJ2lZhWcuV0alidWDhkKVWt82VqJrLt721qxEq5wbS5eOAAnbtVzsV20TEVoNioSx1P6V6lKsk+7XDqX9Z8ksQ8abbnybolpNcfqI5u6A3X5S08Yr/Si11Dq9D/nV1eKrye+10bPL7lDaVq85iZJpS+Bg5dObmt+UFGK8v7gZ8oPHdTg78ekJtP+VA3Hl6cD+l5+G/w2OFEX/fPhyWrodHjNvLDu/cTWEPtD+xqUPLYOkexRiF0+d95x82iL/zF1jnob9QKKPnJuSoMpQvnm5HLsuGwBeluTT7XvsN9KMbCIldtagbkHiSgkOvcpxzS9vhn01kpsIsOpRq/6s/Vk7uLBQXxA+oq5V/3r/mg0GKnTwVn/ZjTtlf7oc/ZzkWNvBNY5VJ7OdrrFNl3Hq++hI18joZFGHnzTiV8B6FL0YGkWQ82KLDZ01arL
*/