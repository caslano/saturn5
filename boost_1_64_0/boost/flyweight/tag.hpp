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
UjjNzJ1vafAq3a6ROoNNbydsyLJyygamgM+W69N3o5SrvwLuzMJUcGC8Sos4t/IpUEWZGmOnVt2HFx2ajvy0M0AmmALASnOYNznc81U7yH+240wwazuW0jaDsLwyvUOfFizobWwJfr/0F6CwAREqb0/JB6QOvq6E0DV5naxrSYt++FnZ6W6uY83spYaL/W5ZgGXavS8t5srXSzdNJr2VtOPq7ADul2kyi3IrLVgU1EO+r3LbTtc2aj0J4jDV2RAhu61pm0n07gv+XSWg2oiNq9cPpnGDnHsbghF181b1LMAh8UyYW6IuSHv+As63g1XAUbvzJgdCpGpLal7ieKQHj3PE3mmtiyejw6LNR1nnbDXGbPXKa9BUzGJhpAepVUrOCedrM0v6KZySlk3cqqSNAB2bz/JizScGyv9cxPXcW153z/X1dyzz6grZS++PMi3fdg2KzAp62G4maUGfTD5z4vjChcMva2dEH0q5p481elryhrK83OTnIGL5duWPqsdVEJHLiOSpd2urfeWvnGMWWG8i2KvruWA3XDjh8FFJxw+cRYfvQZrRctlzsA==
*/