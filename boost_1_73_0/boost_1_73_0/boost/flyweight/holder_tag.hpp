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
9kFs0ZBptLqeOvAYUJ/VtAqxOyU1Jr3Iv0zPLUQHn+lFbwzkTHGor8mqFqfaXOhep5LL/2zJ8crJgKeXnjBkmLAaKVRdn0KiosjhdZBfSktt9EzTtgz7OZFchTY11djOo+59tDGeTgUNLPV7JbydhGNDx9mNI8PpLGWvm2Uyd3uROvUW/q58rzSZbog9yLn1rNEJnchlSLXoZn+OQrRkTrGTabxF21qkxgCn8XzQyP+coUXxPt38r/yUiQ8cNHU=
*/