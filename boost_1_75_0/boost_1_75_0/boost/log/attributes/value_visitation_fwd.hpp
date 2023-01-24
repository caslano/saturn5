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
JQmg8fl4f9L5fBc+GvCMirj6lWFzCcvCqb7yRpCEtF0AWWTP17cDfZqQQEbPF6RXqKEJ2m7d/QtJKSRKqHOBYiwERaiBEiu4h3rvaldggfYMebGfjYtv27Ygy3drGxRhddALlPNlCR3S19RvrwdE7SIXArlERWHAz8U3xSg7SQOYJiWwFXWCJcE1FoRIsb/29fqRujcm+F4IMf/9o5DR/U1UbpjuMeLu7+lzqotaCcz/ueOM+p+s9nJ3cfjX5NnKxcrF0dOe28rR8aSLIEBTbl5SgquE9N3XP6RC0O3ff22MaFRdIcUTqBP4c/ckpkYjXoHiilR2H0tEaKvOrqqcnFxFjAHWQmW59ld1dfVJOTlrsib22uofI7Xl2q5yNcegbv47ViEn9NPnZ+jVSZDEba+LOzQri5/HdiI3S8TdeRjL8DO9zGd8AsiT/JDJb1TMUBvKwP4NYDPrl5UaSkjjVp4S9pl3QSSAL3HB+LhpfrSyhjtjhcfQJsOX2ogvSrmUi3/4aE3wsVE67EUxrm+nAf9xyjEiSzDWPAm4sDd+0rYhCuCgmfMMzjjGaXCKZg28huvLIWhZtAU/+Lnw+SsmEpJzhjzBSN8+l5brId5I3ac8pSnw+9wW2iH0qN6yvqZfg8kGvUBZhZ+ASWkJST6nBjTLn+zCBOrGj8q4NohfknJhDpsSPwmNH1/pkBQ4NsZZuQnAd7gvzklXPF4R
*/