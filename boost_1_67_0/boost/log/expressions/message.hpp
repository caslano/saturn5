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
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
*/