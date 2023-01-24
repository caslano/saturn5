/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/delimiter.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c delimiter keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_DELIMITER_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_DELIMITER_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword for passing delimiter between scopes to the \c named_scope formatter
BOOST_PARAMETER_KEYWORD(tag, delimiter)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_DELIMITER_HPP_INCLUDED_

/* delimiter.hpp
ajVpG1PnT4bUmHa58hkq+6w4Bp2tZ97lTsOTsIM5jlfQ3U+rSdntVqPwasOdaZ/yeNfyNNPTVvVJW9ZNLBS8H5ggrfGeduAF/2POeAcAkKMYa+6vfIB3+cIBTD5Mcxrp8rqWwrwu4+X7XMPG4fNTv2C/trRwvqyComwx03yi4eTX3er2wVydyJ6wysBkA9GdCNGWgg0lW33eHdAZb5FUGh0qm621I7oWatcQdO/0A3k6+Dx8GpPk6tp/KaqhoriB4WGA+zK2V9YZu+u+qVuVqg6vxFGmlTakrtn1VpzBwGE0K/7gYpu4GS0gUGqnFE7Y0omrl3/LUM+GaiwrZhM6bXGU6IrPREecaf8pXGN0wF40GVfFh4mymst1PwnEbyFuqxa2IpG0rNQ27i/XQpU5vq1HroZ5Ncv2zfQ5BfrVS36+X1MlUtv3o1eYTSkrBTtLaDyhHsjB6FF7pptiSWNx3LO6bdkQRHqpTMHEqVFYqyWZVk1sj7E6Kl5OONZgjyspVO1zJ/TQluQk/FiYVPdlDGoalTGauWS12OvJW83Ch8VRNJh0cmY7UdueVGHmVcM5PiG6BNQOnu7WroP9UhVz8E3F+WS8jvaxOrXuu2Ac57eyJdHGSAdrB3vysm8e9nQGIxTL8o0xDbWz2sBfHZE4teZnKAf69iVZo+FjUtmwpIIkUEknzQfSh88Vu4RDzCS6WOUS9tyb7Z/1pCzY
*/