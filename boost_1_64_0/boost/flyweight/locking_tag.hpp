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
kJChq+nbG9iB0+kZx1LoyCfhIg1IFHyRgKL5WieZ4Yp/TVdu5WNNrsEb2a6XTS8WfNTrO5dhxKophGLxxP1lSywf5CQ1Jj+a2i/AMgvuYCo+2EV73YMwRHN8kbPqFYP0WcDGPWMFz6EYlj1gzd6botvrzaiGG7aYKLggrkwLjCQwQMRtE49waDjXgebckOObOxieCWPEmtlTDwtenIKj29O2U6Kr81WBzi/n9BjBVBHgRGiadFurkBFKtPUu9iZYUHDtFNGvpzjJzhQSeGToyw7MM/SBAc6qItZrAeN9aiKLiM1XRJzQPq3F8MqtyXYAoiHHAAU2lYu3+9oWMvDohWmwBcyD3ahmmuBvM/aSkPSexb6P3gZlMMlYwsZYGD/KE3mRpnZ79HEWv86cM7Yd2SP5sxu0oEfyC1x34rOopFTYMARbQ0OQn0NkQdMyxeJ0wtxJSHFWoucq0tFT9yVfgd9v6n3Edeq8o7XtXRn3csbJUJBum6A1eJTVGxvLFgtR8cAgcijH6NwaeU377StyPGojS46eEveKdfq0BX4+CVJ6mmUbTMHUS5qbAw==
*/