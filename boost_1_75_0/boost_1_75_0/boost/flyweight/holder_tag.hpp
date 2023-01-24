/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_HOLDER_TAG_HPP
#define BOOST_FLYWEIGHT_HOLDER_TAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/parameter/parameters.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

namespace boost{

namespace flyweights{

/* Three ways to indicate that a given class T is a holder specifier:
 *   1. Make it derived from holder_marker.
 *   2. Specialize is_holder to evaluate to boost::mpl::true_.
 *   3. Pass it as holder<T> when defining a flyweight type.
 */

struct holder_marker{};

template<typename T>
struct is_holder:is_base_and_derived<holder_marker,T>
{};

template<typename T=parameter::void_>
struct holder:parameter::template_keyword<holder<>,T>
{};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* holder_tag.hpp
3SnbmVizVzl6NCB5W++5jDZ2xq9B47RDTm7AImE13J2tFrPj3MmWD9kV10kt8TgPUo9jxFwZh+2bDw3bEUvm5RYYy70muNyLw5d7AZSb5EokY2BMXoNa3ppYrby3xqj4VhTjkBXNmn8X7hQYSss7wki4EurKiuMlQV/EM5U1DTNbXQst776iJcOdVl5wlSsZw/S2JCFDLMs3l3vbsJ6GlmLQhDBOu2dd7pi15d48Rki3MTqdJvsGwxi7oj7A9Zr1BAejrX+V6CBbLdWwc12Up9R8RR5J7JEPDjkX4kbG+G9Z/9nF5XcOX8qfY8alfI7NUv0t7HThkTi5P8s4eaemQ5QKd0272P7g3YoWk+WFBQWu2Yr1+2usaAUGgQznknHf/xrukGn3jZiNpzsWY2dnNTgJFqJeTARfVww2+x0IxZYq+QAqLNXT5sSwDK93XbhyNvYQJqpG8k+YPrsVRnMbh/hA4UKKKZXnYO4F1/ChJPDv2P075paYKxvUjr/eTPoNgUGLMT1qrf/iH09iPO2nR5Et6RGQwAb5+/qHGhcCB/GW3sGDWDNtBK+6tJHYy2wUr18Uy01OtirxWTt83N7UvLLslCL2pz0blUOW1Tfle1rMbgsakZ2y2TfMbFdKcjQwfOzvLJ09X2lYq8WUm6wdMqZTxZJ8sSQXYXDmXNrKkTe1FPLZpSS7WD7H2eNztmCK6WdZntm6qMca8D1Y
*/