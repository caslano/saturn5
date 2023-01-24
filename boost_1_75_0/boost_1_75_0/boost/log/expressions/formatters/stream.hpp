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
IEBRCvpW//HmLygh4xrfaEzIiHovWzYbNGoWMQjaRK+5ystsidzod86vAvOnWr9SW2jdqz3UG7f2NgJ8uP0r0agdrnfFXQ8ldQ115TXO5EoSzqTs43xjWSfu/Gi/93/3CbW092zKx7wYulZ1FTzxPagaWeKJf/yo5HNiv/EvdZiuNwameB4y19X//eXOr8+sati/4wXyeDrSv+E+Zg2Zdj0Y9y5440X5q021GAsjzH08nQaOGWowszL09I6/CDR82j+yJuDh/Ge+zDCXoAyhCZTU1f2upDuFHzTIqQMOhpH0PTzsMvQoHiWUIRl8eDUS5ipHWal5Y1yu0mdC5vvDUPCOTBqdlg3st7my71UMl8Qz0BTvKh3Y5bbGzi/kq6XEtnqe/c7sxlnriDvE4emUjBlAxt7tXRyVA4mO7TmWSc8rYScJhuX00E9QsAliqVph4BbI8byIdK2Rv3bZ2NGDedcCiuldBcidACNCm6NkuNgC6/rqh+4IadqpgHHr7jiX7ARYyTC3ULZLIf67QdkwKGvIa+nV49fCsld2tNXSNXy6WxoV9k51x1HaH1wxmeKv+jvYaIGd+OtBXKZqRspB2u2MkTHf+1PerR8HvORTtprGX53Ce31A2KVA1ptt0bEguR9Tt4I4VcL8hoM+rt6lBb5D8ZXtMlNjqNfHigVRkv163849cchDFFah7ekvgV3Mkd/889Hc270f4Ukw
*/