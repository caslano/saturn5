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
BnaHa+GRan+rR+a2GJVJYrQ589fJ3XbchJwNeVvk5oBpiup+83+3zG3Vr1yv/r8gaxtCGsxDrbi5TtZWd9VddVfdVXfVXXVX3VV31V11V91Vd9Vdxvzy/P+/df//0gnjyiqraib/f4O5/3qeuf858d8A6J6nd3yzl7l/DZDP/qd27uFe3Pt/B6B+e+b+83Jd9ev3MX1JxRgTUJmo8Sh37n/TN3Fz/xr+fd1fdtM3+77eG7t7
*/