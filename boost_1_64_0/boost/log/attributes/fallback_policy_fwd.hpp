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
sMPC6BLU4OSa9tN663rAb75IJOEY2srvsy7bqNmWe598LeW3e3QOdNdv+axB8Z7maYulG1GFExJITmoVbbqOLDO/UdoksRg00YEp2X3UYyKMJw2IUC+kEA5Xt4FNzlBqIrKgKwhLZl92hhwBOBfkk2FOvP1rsFzNXOudiB+cQd9+kVCyCyXrhzL5lAEhHwnTtrHLnGaJqlFSXsWjh/3JOPzULZckbqsIwmQCLphiUryKAM/BEEFVTlCD/XrX7Hc3RLQLz9EAXjaobDcmK7jwcir1EB8jQj/pDtBLo1eKg+xsoc58YzyUgGfT8BQ0I+q3y/RCX9wDuMZhEu38HYQ5ncyDVET8I4h1gVZdZxctL28K8czCnMzPn0a6PexaAFwGNnfqGslHpu1eApAogIaPxsARqO+waCTrs6+ioGLT31+CkkCct9UqEcGQdqwENcxzLbPAoTA1VTAU8wFc98/sMK96JPkuilOqqtYZgaRE8q5X2xV97AGrUjKelKtqxeLZH/m1w6RC9sm0EfKSx1PdptB33A93SadmP6122vaac1Mqf9l0/lksCCAltg==
*/