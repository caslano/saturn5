/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   process_id.hpp
 * \author Andrey Semashev
 * \date   12.09.2009
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_PROCESS_ID_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_PROCESS_ID_HPP_INCLUDED_

#include <iosfwd>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/id.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! The process id descriptor
struct process
{
    typedef unsigned long native_type;
    typedef boost::log::aux::id< process > id;
};

namespace this_process {

//! The function returns current process identifier
BOOST_LOG_API process::id get_id();

} // namespace this_process

template< typename CharT, typename TraitsT >
BOOST_LOG_API std::basic_ostream< CharT, TraitsT >&
operator<< (std::basic_ostream< CharT, TraitsT >& strm, process::id const& pid);

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_PROCESS_ID_HPP_INCLUDED_

/* process_id.hpp
8Hgx7B0WwS8j7xGwE16G8nAg5Od9NgW89KLHeDGaoXwKwlcAoZNCL/C1OVLBkGHVO2P7SsPgmpPwDnB1S1JTvWF71AHjq02kVhrqivscaG2dAS+iJm/kO3IRMOGCT5V+39PmHFjzBHDUu+gSvEYZgUGudYiovxVIOYm0ZYJksV7qY1l6lUq4Q1XwnKlFh0panFv7mdVAeKEICfqaPtRZNQx6J6od5jaHkg2ACJddwO9o345kzOdyj3ERZzHXHRYziU+j93QJRjg7IAf9kLUK398/+3jInrKjjwIxFo3pwhny6X9WRlDVOMn7/1rifm6SRNotHjstom+VkUOdp09zotSOCsxmUR/MFhmMONQcIgYpe/z0KQYg5HI41I1UNAMpJ7kUX0p60R21+73BL3tb4OxfqCs1DI5h7M8kjNODb0XDZx8bimwNNWTZvMGUjK0h0KlqJQhR8QnQbxMYvI+mNbCJL6S4MD2hhsGccs0elrn7Xftq0Bu8kfaduINJ3NUkWyTqIoAlrtamNpSEmfNaqgCHEjbwDcUT0BSgyd2UT5tKTX0uyiNUamNxF7VpDGPXQRIhbrGsxrCeV2PMqxJ6Tb3skfQ+acYnEgo0wFAZSS6gzxuZSqm0p6pF9Mohg+4kkYhPhITpDV5fous6
*/