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
mA6T4GzYAM6BB+n68qPh2XCIynWGqVxnJOxJOCepeQWcD6vhhfBSXW9+LVyocp+L4J3wYniX7vXwMFwMH1N50NNwKXxF5T6v6x4PX8ObVQ50K9yl8qSf4N0wzEs+BHPgw3A/+AhsAO+HzfR+c73fSu+3hU/BAfAZWKl7QSzQvSCWwOfhX3QviDvga/A++Dp8FK6Fj8N1cBVcDzfADfB9+Bb8CG6En8P3dE/0h+D+8GF4AHwE
*/