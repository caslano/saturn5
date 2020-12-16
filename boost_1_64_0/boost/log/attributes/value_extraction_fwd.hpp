/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   value_extraction_fwd.hpp
 * \author Andrey Semashev
 * \date   01.03.2008
 *
 * The header contains forward declaration of tools for extracting attribute values
 * from the view.
 */

#ifndef BOOST_LOG_ATTRIBUTES_VALUE_EXTRACTION_FWD_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_VALUE_EXTRACTION_FWD_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/fallback_policy_fwd.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace result_of {

/*!
 * \brief A metafunction that allows to acquire the result of the value extraction
 */
template< typename T, typename DefaultT = T, typename TagT = void >
struct extract_or_default;

/*!
 * \brief A metafunction that allows to acquire the result of the value extraction
 */
template< typename T, typename TagT = void >
struct extract_or_throw;

/*!
 * \brief A metafunction that allows to acquire the result of the value extraction
 */
template< typename T, typename TagT = void >
struct extract;

} // namespace result_of

/*!
 * \brief Generic attribute value extractor
 */
template< typename T, typename FallbackPolicyT = fallback_to_none, typename TagT = void >
class value_extractor;

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_ATTRIBUTES_VALUE_EXTRACTION_FWD_HPP_INCLUDED_

/* value_extraction_fwd.hpp
GnEdd6frIYjPzygPEwtTDyYJphVMZ5i+hp8P30GVy32kpdwzRLlP0oxZPUPd+/RVlPubotzpi99yG9WWM+StbVJXrpD7ff3KrS1hf9+HFBb2FNVS9yMv4XdMXuY6eQnmN+TpclGesqcMzXJrS1Hk2SGzTZdH9m9K/jJEG/yJ3HZr83zZQ1uisia3Utq2dLmYtmRzpvN3tw1ce2ob4r2BVTH8zjhky4G9QTMJ6VrC5UgPLMOm4phWtzEswtEv8fCD1OueTTgMuIpnk2yjKectYRnc8AXGMIyadWDS8GWm8Qh1Lv5eiZGhkRmK8+aCcHZcdWMp+ByM6z0wY6nDb0NbrHmK5pmBIq4UP1f8bCf2MJcnu1GpAD8LOH8fUViVjGjYufrH80v5/V/4qMTPNlHsVmElPUdRPlMm4a0BzK3OkfxgxO2KZ/jQiROnJnNcyC/HRWXlr8TffDnFJezsMFMoPDvZRbJdQ5KbwvG2MY4i3nUkV9HmSstl2N1Lcp+YUp7jrOkYS+kIUNIRw3axUjk0Wua8P4VhtlMHpqkRo6TpcXKPFWWxA/HPI7u9Nin+BMCoIcW1lmRMWzjCrI2ybIkW2R7vh3LY9PuUZEKV+C6SXTkR35uI7zzZDbJZyj7VmufAle5lv2O5M45IUfawozLtbws0brO5yroA8Vwh+1qirK/B7iXy/6Bc1vGAESvFEUT+HsVZ1yGwx30BpzI40lCR3RPJfYLpCvcYwm1BdqXtljzFWdtuDaqzPiKfdpiJZFdKKbdYKqPKou0UIo4VZLfJWm4pHIdo7z1WkJwSxw8riuomgu2yqCzsSvvcT3Zz5fJJpDmclIdWlNcGRgj+xbieb9ltL8UzT0lPBskvE+X1LuKZRHZv+0nxJFnLah2F1VCkmea6jvTBJlaqjxCya482X9qohf+bGjYln73gLrf5i4i/J9n9aFrKMtHaBrdo+v9lqocK1AajOI40Z/2jD+0R+TyHePwpnrbWOuO8FuWhPZebXGevauoslMILFHV2CHEMJLsL1rykWfPSmPuTXJ51KS92pT9dpbw8hL9biDI7hXgaONukXGdNrHVmUhy3KWPScUpfJ6MMxo7qaNNtUT/yuFF6hfu4EbVCGTeoP0eSXbzcNtOs8UdRGqso94bzlJ8EyIUYNWDkuFtwmbjiuY54alAYta33Bsqr7Lc+peeGUmc1KbxAJS9vWuosEHZ1yG91OS8p1ry8q2n/SyisCCNW6l8juf3T2IxSbob8yG1mM7nXEHm8ijxuJLuV1jYTb20z961wbzMLqXyiqc1U5DiCqYxPmIHGY6L9n3bEA1nEI99bkgGlfsZZ6kfuF5co/jtE2k8izK0kv8RaP3TPksei65THPKV+VmjaWv4ydRw8iDiukl1vWzT0VSswb+2Dh9fX8Owa4BdiPhCI/zELcsRfk+LH+fg4OcJadkEURjDpvWI5nFUcTog58yNHKBH0n+E1rKuUl9JKWBdFWDMOOIIp4/ivvPew3qTyK6WE1SRapCvbEUyUj+laKKWrBod1FGH9g8Ka4syiLSQwJCQsLMQe4TW8FZS2sjweOX+PkF244/QBpR2uZll5HvYM2ZVX8hZRWeStkiinMO95u4XyVkYJa4gIq52r+hCU97D6LXVvC5tFWA/kO8Kp7GOZv0ntKkAJ65oIK5Ky6Gu6anG65PobGOOqvwfqOsKpj/8QrL2Y+hN1Mp7SFqn0ryyyq8HpLRfW1fN7d/rnS6F7zVaeg/Jj+VvG/H7rOPBqIuroaddzEPSp6RMpjfT+omvNRr+uBn/WZ+Vp4jlyIrnN0j1HCn+hQqeO9yo5jnyMJZJ9vMt+jmov3ikdotrHuexPwt51HtA=
*/