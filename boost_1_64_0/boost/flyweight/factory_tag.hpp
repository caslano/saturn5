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
Y0OAdLTs7QqV/QCOHnI5g0a28Nov0zioplMLIkeFSh8mtlOWaXLHfNlOkF/oNtJ+59ybDAo71AsKY3+fdmOVjpnVybgJfqEdoCBhhRgBVk4wIW24Yws6VcWZsTttPioyMAFHQDOSucaP7DPfSLTfZ1NzgNucCYyGpR2+WdL4sgjCgHYZfIyKeDi5NWhPaB1tvflFluVu3RHIgWYwgloz98s8qytcPtou0c/FNYe0WUix1R/qtMtLskeZ5BMMxgVhbac10ap5zIwSlWgpSkxb5ka1WjXrZywHbzGitXaaeRwXZxWnQ3O8qVkEgmBNeZTQ7C08kkIb8VYvUCs3NzQrjvFtVM23IrdQ/a7JHVHmCScBCbAvdPtT2ObaGQjmUe0LRm/umH+xCBWKgih2uQFhZpc7fnrz/bhOsyYH6hxMAo6ytzUgv4SXRgWlZfQzMTp8Dr2u0MEqCImi2BwG5CpkJ2TW0UsY5VLWH+35FWAr5XmcJsjOlwPsRYe6xInmVSBLXkMJdx3OycsfLEdsKu2o6mIImDZ/1OReo38IOXeLwDaLVWRyuXFZmOTcsA==
*/