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
a3lBMS4WmOMAp1cEhwq1M741H1TjAC14u518BzirKKm7Zvzpi2EXTHvFOXc833nv+V68Npw87/+o+uGgE0I3XoULOHf8lWuEuttCS3OT4KPOMCPXBcePApwY78PnOggmuhlM4z9QSwMECgAAAAgALWdKUsdjhVXHBAAAlgsAAD8ACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1JFU09MVkVSX1NUQVJUX0ZVTkNUSU9OLjNVVAUAAbZIJGCtVm1v2zYQ/q5fcdAwzA4UuV03rF1fMNVxVqOubUhyugAGBFqiIq4yqYlUUm/tf98dJTmvbTKsChyZR95zb88d7a9dOPhmj+MTHNz7JPaT4IPvXmlZqz95au5WSJJP0P6h4hrfDzA1gkutT8kQHqT1CQZWK+lsvaDvSfIAc2tykv6NSHmd0FeUtJqd/lhVu1qcFQYG4yE8fvbsKRzCj48eP/XgiEnBS4gMlxten3nwIrOS3wr28aOv+SsPuAFW+tcA40Jo0Co3F6zmgN9LkXKpeQZMQ8Z1WosNLoQEU3DIRclhvFieTue/e3BRiLTocHaqAV2opsygYOccap5ycd7CVKw2oHJEQPxMaIOYjRFK+mieg+H1Vncw5AQrtQJ2zkTJ
*/