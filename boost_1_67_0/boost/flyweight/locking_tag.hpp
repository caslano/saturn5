/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_LOCKING_TAG_HPP
#define BOOST_FLYWEIGHT_LOCKING_TAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/parameter/parameters.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

namespace boost{

namespace flyweights{

/* Three ways to indicate that a given class T is a locking policy:
 *   1. Make it derived from locking_marker.
 *   2. Specialize is_locking to evaluate to boost::mpl::true_.
 *   3. Pass it as locking<T> when defining a flyweight type.
 */

struct locking_marker{};

template<typename T>
struct is_locking:is_base_and_derived<locking_marker,T>
{};

template<typename T=parameter::void_>
struct locking:parameter::template_keyword<locking<>,T>
{};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* locking_tag.hpp
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
*/