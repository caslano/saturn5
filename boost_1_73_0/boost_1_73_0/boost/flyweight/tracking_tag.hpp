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
NmiOGSiMqfSvo1Ha1CVGMspUqkdpnwq/MNsbUZ2iN1u2A1UZMAoazT2g8x5sVSZyemOKUFg1m1Lowrt0Cw3KbKRq0LwsOzhUFVy3IXCIumx5dBIq9F4YemklNVm7KNT22kFMaweUN7VEc5gWPJcpTLwHjcx4bc/bRPRWuizblN9TskvfM1ASvQI3iGAaubBhWmgP3k/jN4tVDO+DMAzm8SksjiGYn3Z4b6fzI+SGQKs18I9VzTV6UYPYVqXg2TXj37TTHT9+A+NVOFss4yScRIvZySRMojgI4+R4NR/H08UcnoD7+Cc45htLcxfcUmyIB/CL//Mz/xEKaJVwpneJ5oYqjh8kl0b86A3Mg3cT5z4j60Mst4GUleWGpR+oOhtul5jSDc8V0RIkv0Bea1Vafv/VcG0o/dogv3lmrUWn88UymkaOL3PnOyHTssk4vCAXW/YWrxxHSNPj1InVTtLN4FyJDA6uyg1SbC/lNXZTv0ZC1xkzbPjcsbGlCq3czMOAduCgQJaW3HO+PHjuyc7XVG+FgR5RHo4m0TicLkndWTLkE4NKYdzEdEXDor5Mdt7IlArWDZR+jGyZwQW1QlUro8yu4g5uXSDBN+oce8KxjXALBs640fva7aDnC0c3d2DElt9ZUed2RdHEOp9e
*/