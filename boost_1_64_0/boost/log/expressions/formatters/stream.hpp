/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   stream.hpp
 * \author Andrey Semashev
 * \date   24.07.2012
 *
 * The header contains implementation of a stream placeholder in template expressions.
 */

#ifndef BOOST_LOG_EXPRESSIONS_FORMATTERS_STREAM_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_FORMATTERS_STREAM_HPP_INCLUDED_

#include <boost/phoenix/core/argument.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * Stream placeholder type in formatter template expressions.
 */
typedef phoenix::expression::argument< 2 >::type stream_type;

/*!
 * Stream placeholder in formatter template expressions.
 */
const stream_type stream = {};

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>
#if defined(BOOST_LOG_EXPRESSIONS_ATTR_HPP_INCLUDED_)
#include <boost/log/detail/attr_output_impl.hpp>
#endif

#endif // BOOST_LOG_EXPRESSIONS_FORMATTERS_STREAM_HPP_INCLUDED_

/* stream.hpp
q0CRPB9SUWMhE9oA0k7b/XJbV1LSN+MPQdHfbknsEqbGiOvzVlB2sC1nExaame7akp40f9x7G23Dcb8ayJ3+23W6RZxU5gee35GWnK0XjivAH1RvW6LZ8LdZYH2nTOX7bXjt/wf3UcY8cU0QEeUkXgyaoydH3NI8gvRiFov6LxGU9kjJLYx3g/MJ4rur1RSJfZV8CFPimhwThVSlPAs0psGoOholuhBvzYiSu3AANC+V2MpYdsYx/l3PjsirBBY/qjZFqi7YRJKENo66JkGmmwzxP3FRILo6ORJJW2j6ClVdrKdFmBOy6zbHkXsxzyLtNOhR2ji3AJ+IyhTDo53pE066I25nAM5CsUup1CJJU8d6DFUhGfb3FsFl8vfRCe5dM/umo4Jx66q12kYev9MAkEhoNmcWNAkFWM5NBu6aWU1iIeKELDXGvnqczkw5lBqNc5dFPkBc2YpK1V8wOtw+sHzcLUI8V8Ne/H/YKugSCA3KRkNVlmqcsJCq7FgMadWHwtg2x9yygJtwql2S6nv4ppM0PxBf2CyXlj5jWcbR6kLZBb83IbDvOTtoTQ==
*/