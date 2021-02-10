/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   support/exception.hpp
 * \author Andrey Semashev
 * \date   18.07.2009
 *
 * This header enables Boost.Exception support for Boost.Log.
 */

#ifndef BOOST_LOG_SUPPORT_EXCEPTION_HPP_INCLUDED_
#define BOOST_LOG_SUPPORT_EXCEPTION_HPP_INCLUDED_

#include <string>
#include <boost/type_index.hpp>
#include <boost/exception/info.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * Attribute name exception information
 */
typedef error_info< struct attribute_name_info_tag, attribute_name > attribute_name_info;

/*!
 * Type info exception information
 */
typedef error_info< struct type_info_info_tag, typeindex::type_index > type_info_info;

/*!
 * Parse position exception information
 */
typedef error_info< struct position_info_tag, unsigned int > position_info;

/*!
 * Current scope exception information
 */
typedef error_info< struct current_scope_info_tag, attributes::named_scope_list > current_scope_info;

/*!
 * The function returns an error information object that contains current stack of scopes.
 * This information can then be attached to an exception and extracted at the catch site.
 * The extracted scope list won't be affected by any scope changes that may happen during
 * the exception propagation.
 *
 * \note See the \c named_scope attribute documentation on how to maintain scope list.
 */
inline current_scope_info current_scope()
{
    return current_scope_info(attributes::named_scope::get_scopes());
}

namespace ipc {

class object_name;

/*!
 * System resource name
 */
typedef error_info< struct object_name_tag, object_name > object_name_info;

} // namespace ipc

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SUPPORT_EXCEPTION_HPP_INCLUDED_

/* exception.hpp
NKCaONnLv68RNJwe8aiLXw5+PT7u7fa+v5pejw61K7XbYadpCHMLZ1c9XTYotBiqYnlvb4/7ywVWasxqmHCMrLVPKiIVjoFCQikeVc+emZZJskt7njjFSu9WE4EPVPsTXk+ZNB36hc/49QD6dvTD9TsdqiYJ6dKMWQijEPPau/OrQ3gub1Ksz1qmo0YWZllWOP2p6UOyTNVyoC+drS7d31AlNp2f0uRWn9fm50wgUBUN1+mXaUJ7KF4GhBYzRru8S7jp9pxmF6XO10hd6rOIDD9A3tJA2ImgaV4Ak5eWnKjM1KQEfYFT0pFSm2HZwqSaHFpONNqCT2WhKld9SZuwmTnJ5+tz/bssDp3GBkVZw+xLmui4nf3jidQcnk0JW+P5c+HlWAJtWN2Kj4aetFG3RYgVX8Z3MgiRQ6x7S2zz/Ft04Zko2OSSugaOnVz0pIqfKEP9rWnYbRhg0/51WKC+TWg0IL4wwbeKvi3R06clNbdkeOtm2nITawV3gqosNRl/4luYVkXkl0lx2Di19vM06lfj6O4bNY3y0H/4PDzkA6jIQ+g9lz1q2CSUqQ68bgOV+nRRZYVgXZqaytrjnRPt5QOfNrsyDsWuiCI0qdyhxNWCqm7LVK9gJbf60GNL9FB06t1h09acHnibDmb/
*/