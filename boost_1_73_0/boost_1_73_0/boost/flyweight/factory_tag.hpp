/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_FACTORY_TAG_HPP
#define BOOST_FLYWEIGHT_FACTORY_TAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/parameter/parameters.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

namespace boost{

namespace flyweights{

/* Three ways to indicate that a given class T is a factory specifier:
 *   1. Make it derived from factory_marker.
 *   2. Specialize is_factory to evaluate to boost::mpl::true_.
 *   3. Pass it as factory<T> when defining a flyweight type.
 */

struct factory_marker{};

template<typename T>
struct is_factory:is_base_and_derived<factory_marker,T>
{};

template<typename T=parameter::void_>
struct factory:parameter::template_keyword<factory<>,T>
{};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* factory_tag.hpp
DlusfsDygHSCu0T/dOhTOzq2QKk9I7dQfP/oDVfDynDkJH+wkrOTNCtHaZy2IDD9SJFh/mVYM8pljT7QpvjfWpnrcBxAC7mXN2mO9AkYGvK9IedA0inlCM9FrLr0msO7vcLzhLNVE3pGKXKPapbWnJziE4bns4PQ6iYp9aJvH/fdh5vZ1tAI45sAHY6Eph5h+L1lFmsPQGHeKVMOe6wsv7Cdl+BZDFP4QBs9QPUprvWzpdxoqZWjUI6W9P40M3s=
*/