/*
 *             Copyright Andrey Semashev 2019.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          https://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   sinks/auto_newline_mode.hpp
 * \author Andrey Semashev
 * \date   23.06.2019
 *
 * The header contains definition of auto-newline modes.
 */

#ifndef BOOST_LOG_SINKS_AUTO_NEWLINE_MODE_HPP_INCLUDED_HPP_
#define BOOST_LOG_SINKS_AUTO_NEWLINE_MODE_HPP_INCLUDED_HPP_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

//! The enum lists automatic trailing newline modes
enum auto_newline_mode
{
    disabled_auto_newline,  //!< Do not insert automatic trailing newline characters
    always_insert,          //!< Always insert automatic trailing newline characters
    insert_if_missing       //!< Insert automatic trailing newline characters, if not present already
};

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SINKS_AUTO_NEWLINE_MODE_HPP_INCLUDED_HPP_

/* auto_newline_mode.hpp
QrZ1zIAi/xytM7+Q8MdefPB3yerbqzjkHfeukywp0FLyuzk01aUa8n4gsfUL1MjF/3W78JapUmohLiK0YGKQoFinmrBz5a87rBrTHGuCru9e+pBo5GK1XGL2OabEoiOUBT5W1uJFgh9jXW8CJUaPMTuM8ByG4w98xp4pJ3+XuGqyjlS/NdFUXC6S81dfk7poDvNUQYv49EGJyN+VTwHj/PidC+q3+e/PuCQFOtnZ2aULCeIv90lwt1H+TmYt+scuXGhVRfelD6Mpktv9pcFgLict3NpW7us3tZu+HtyLhjssDu8WKv39ncXXp7y2mEvnzi2l5Y2OAZvn0xRQm2zZiyt0Rr+OOKbqJCoQJSJwZMg1lXKcx4knOOiy95v7jJM0FRV88/qF0w1mkFbuJa3R2asCA2wFdhnC6nqlHgHdgAPRm5d7urVu5OolAUnJerQ6oK6KklPylyAGLt+YVmu7q/z1nxSlDmt8LTGHo+wtrCzVPeUe1h7eEgbAWusnUHX9IJY3lqRk1OeWGVv2i5yvZYcdZxAfhQwrpxYe2EGHTl56kOL1WGXO2pnAtBsfk1zvQweiUnniQ530VtxroPk6Iv08/haB5wdcilSSAY5c8wcRMeyp19cBFFW43/Efo/A85Cdx8NQ+zttt+I4fRoLb96B06PR20PVFAfylgH+7rx09twr9gO3tNm4QG5co6DlAlsCfPqxPd1IzkO0K
*/