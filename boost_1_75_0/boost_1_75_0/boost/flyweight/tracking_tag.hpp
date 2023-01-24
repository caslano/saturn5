/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_TRACKING_TAG_HPP
#define BOOST_FLYWEIGHT_TRACKING_TAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/parameter/parameters.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

namespace boost{

namespace flyweights{

/* Three ways to indicate that a given class T is a tracking policy:
 *   1. Make it derived from tracking_marker.
 *   2. Specialize is_tracking to evaluate to boost::mpl::true_.
 *   3. Pass it as tracking<T> when defining a flyweight type.
 */

struct tracking_marker{};

template<typename T>
struct is_tracking:is_base_and_derived<tracking_marker,T>
{};

template<typename T=parameter::void_>
struct tracking:parameter::template_keyword<tracking<>,T>
{};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* tracking_tag.hpp
8O3lB8Pybacf+falPzzfvP0j8u21L87Gt+Gcb1VfRMO3Ew+E49sl/oh8298vMt/MX4Tm2/BAvg0PzbeGiHwbrudbw9n4dsfGaPj2R11YvmX/gnxr/0t4vn1ZFJFvhz+PxLe+cr9S4tqaz6PhWmFdOK5N/1lbpwTx7FIdjXIwywZ9HoJl8vRSwbB5sHs2pzQ0v1YH8Ws68SuHsatUz67VZ2PXpxuiYZdtcVh2Tf0J2TXxpwht0bkwYlv02RCyLUYa22Jk6LZYE6ktRurbYs3Z2uLdpmjaoueisG0x4Udsi9E/hlm/tu8bsd9e3XQ2eVPG5U1SUzQ9d4EvXM/9+IeI8mZqn8jy5oHG0PKmLFDelIXm2dqI8qZMz7S1Z2Pa6fXRMO3ehWGZ9s4BZNqrB3T2HhUH4DZ7JOxi7/pIDLtW4gDBN6+PhlvfySEgizMOhNtv3WSL2Jd+/yycjbXCaGOtCLKxvv5ZNOReKoeznI3ZH8nGarVFtrH2+iykjbXC2fvov7OxVhhtrBWhbayN/9LGWmG0sVbobayN5n9lY+277n+ysb7vjWBj/WEvdubv9urHt0EGPXJdxH7z4dpQ/WY8Ori9y96hQ3w52FlZzzm6s8MGz/4Y7+AktVJT1kbTeQ7VhpNMF+wNOY/MO0jASvHbr1XPQxAgCm5WHmEp1fMQf60RTnIYNrasUD5S7ukda6k5EmMyFdyV5O7okBPz
*/