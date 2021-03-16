/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_TAG_HPP
#define BOOST_FLYWEIGHT_TAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/parameter/parameters.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

/* A type T can be used as a tag in the specification of a flyweight
 * by passing it wrapped in the form tag<T>.
 */

namespace boost{

namespace flyweights{

namespace detail{

struct tag_marker{};

template<typename T>
struct is_tag:is_base_and_derived<tag_marker,T>
{};

} /* namespace flyweights::detail */

template<typename T=parameter::void_>
struct tag:parameter::template_keyword<tag<>,T>,detail::tag_marker
{};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* tag.hpp
UAah/BxlY5R7BL8PZTOUB0X4B5TBKI+gvAPlMcGfQBmC8qQIn0HZGuVfInxJhA1Yd21Q+iicN6NshzJAhGmCHY4yWIRboeyAso0It0fZEWUnEb4TZWeUMSLcA2VXlP1EOBHlnSgHizAtfUShHCXCo1HGoHxAhDNRxqHMFeEClN1RPirCs1D2RLlIhJei7IXyTZR9UNIGfl+UH6Hsh/IzlP1R7hDpd6NMQPkzykSUv6NMQnlKxJ9DOQClF7atgSg=
*/