/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   fallback_policy_fwd.hpp
 * \author Andrey Semashev
 * \date   18.08.2012
 *
 * The header contains forward declaration of fallback policies when attribute value visitation or extraction fails.
 */

#ifndef BOOST_LOG_ATTRIBUTES_FALLBACK_POLICY_FWD_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_FALLBACK_POLICY_FWD_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * The \c fallback_to_none policy results in returning an empty value reference if the attribute value cannot be extracted.
 */
struct fallback_to_none;

/*!
 * The \c fallback_to_throw policy results in throwing an exception if the attribute value cannot be extracted.
 */
struct fallback_to_throw;

/*!
 * The \c fallback_to_default policy results in a default value if the attribute value cannot be extracted.
 */
template< typename DefaultT >
struct fallback_to_default;

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_ATTRIBUTES_FALLBACK_POLICY_FWD_HPP_INCLUDED_

/* fallback_policy_fwd.hpp
dTbadQVi4DOg9nMMinV3RjWCLd4G6YNCfZpXNVuZDLHSelZtH/U9vLkcG+CJsbRbiq5ffT6V6TEfhahadCwy73qcT38TKSebo8UMa9Kf/T5n0bXI6hX7tBVtR6EWbdCgVE1i2M/doEZD7mRxoe+iH2AUF6NsgTmJNlIZ4Vf8RJQjDtBchBrBMEbJUKzHl8jdh6Z5g+Ni4bckfRY/FaIjMxRTJ8qn20wAM3jiSbptXwDC+6PHnHmw35XEJqMOJXveY5YwG+1Y9mBWUmBFXAR5RRlVgVQK19NW4QFJWM9f1brViVOIkt0SIX715VNqrfnqPBHO95kt+/M0Q/dvFIcZRRA0R1yFSdwpjDbbPv1NDJdOsFTuQ9/PYNmrO066U8/6AwJ73fGAceT7r0w/nkPmbB7QLK9M4nZPOqHZ/Z6090R6YjXgwRXP+krydTZqX5ZKK+NFAfMikhvVM5vN0DeverdyhRPewcmg0UF61SfWDh/1AqU8JNFU3fo9anP+3CXIvPLRvNtxcHX5/cL62pBv//Fp0M5umN2vLOSHpuTBveM/vlRXG+e69g9+2q5iO2DR2Qw7M+ggcfD5KByaaDReZbUXIL/XZ551o1Xrr7v3884+Op+n40fi5KA9qZ/EWMoqWyq513yLszUc4u1ceXFVNzfzqwtys4BsKHY4Ws2BoWgq3C90FfPiIdJHnMgFxbwKiPKR0ZPk57waINlR
*/