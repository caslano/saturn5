/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   value_visitation_fwd.hpp
 * \author Andrey Semashev
 * \date   01.03.2008
 *
 * The header contains forward declaration of convenience tools to apply visitors to an attribute value
 * in the view.
 */

#ifndef BOOST_LOG_ATTRIBUTES_VALUE_VISITATION_FWD_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_VALUE_VISITATION_FWD_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/fallback_policy_fwd.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * \brief The class represents attribute value visitation result
 */
class visitation_result;

/*!
 * \brief Generic attribute value visitor invoker
 */
template< typename T, typename FallbackPolicyT = fallback_to_none >
class value_visitor_invoker;

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_ATTRIBUTES_VALUE_VISITATION_FWD_HPP_INCLUDED_

/* value_visitation_fwd.hpp
Hx8fsx7IyQZfDMgtaB0/OLXYJ+ddy4S7b1r9Ya9vajfyy7l7oI/U78eAc/oxnpZF9FqCxEzYnfbAGsKRwqN3grV4b38JS4XDocPpnfxRPh0uHJR3X9YJnqqun+r8dFzVRmTj4rVYOoJxEhaqj/5/Ck/Kz7YJe7G7J67CYx7hgk+rcsjrwlIRuSTmVFErFGfKR4+RnFApeRAU3qSEpPshmAPxMkJBI8C5mkqmaDdZnbc15REp
*/