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
Oc+vwqtktQFmzxM8KXZ4FDOu+qpiBaMcW0pJh/NACjo0yU3DEII4TXCKPqz+Kzz8eJYm88swA3dyPMXanX8BUEsDBAoAAAAIAC1nSlLauO1dRAYAAPcMAAAtAAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9SQU5HRS4zVVQFAAG2SCRgrVbbcts2EH3nV+yoD5VcmpLttk6aNFPFkWM1uo0oJVHHMxqIBE3UFMkSoC9p+u89C0JRnGaaPIS2RBLC3s6e3UVw2aKDb3Z5AaujL15r+1njwn0nNKuKP2VkPi+wXr+n5g+Cl7h/haku7aXerzv0VVLvqW2l1s7WU35er7/C3CU7yV9dFr5c8yNWGkknf1aU95W6Sg21zzp09PjxIzqk497RY59eiFzJjEIj842srnx6GtuV31Jxdxdo+cwnaUhkwQOFi1Rp0kVibkUlCc+ZimSuZUxCUyx1VKkNXlROJpWUqEzS2XS2Gk5e+nSbqih1eu6LmnRa1FlMqbiRVMlIqptGTSkqQ0UCDdAfK22gszaqyAOYl2RktdVODTshMl2QuBEqExuYE4ZSY0r9S7cb1VWGSLpxEelutIMiSM32k6hW8GYr7qkoDZmCai194v0+bYtYJXwHRFgs
*/