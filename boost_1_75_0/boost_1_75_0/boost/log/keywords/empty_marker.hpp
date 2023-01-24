/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/empty_marker.hpp
 * \author Andrey Semashev
 * \date   15.03.2014
 *
 * The header contains the \c empty_marker keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_EMPTY_MARKER_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_EMPTY_MARKER_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword for passing the marker for the empty list of scopes to the \c named_scope formatter
BOOST_PARAMETER_KEYWORD(tag, empty_marker)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_EMPTY_MARKER_HPP_INCLUDED_

/* empty_marker.hpp
Vxnx9MFcXlFFN4I+w2lR7m8W59a4jQgrIzuO8PGNA3A416Ie5/vPz2gZp1W/9pwqN/JgNCrwC4evhy/hC3bj1hg1j93X+urh+ZRf6lxro3Z48p22fiClNelRM557dnIUHxi3X/EX3E6qjVoPfGJm2dEwLFI8H4nbJ8eTN8SjRb3ITQhZznbMzC+O2eVTsRVFZknT4jiPUHFpZx0wv7W2DtDYKgqMWv/YNVyC5Du3/Pnh5We/aqjGcvTP8+XPy9iu7Ykp7hIlHGkNlPuazAvuXkxZ6lxzx9ItLJM0wtca+x9Z1uMPzpO09SfvNFj8rhM9WKOKaPKlMlSylfWEq0oyPwL4WgBjBKzFwnFnjCCtyull1IbgFkpb/m3NljUVhrk7gMIfSk6QYlAc86Qs/xCHulrCL0oR60TQ52E7lqKt7JEAncqvqlsj5xIqxUrJQjFlqRgY7O/XLX6CG96RekTWiAycsvJYJ0pfet0m4T/hP9BxWbMYiQSJZu/pyxwrHsqEL2PDvqqiP//mkNdNe6AoFLHKtMvQ5lsIPNV4zB/Ox3hGWWJ091juzShmFZfbEq8VdpsnPWEpapsVIJVPDCVDhfZTu2P4r5dLB3zvL56JNkmlWUJyaO4D9Fw8LJkdyUqJITGbocubEtGEoSOa/nwz2QNo/iOuF6WdeiPI3xt/AzWuT9OZXOJaNl66qv2H/yOPNy71OeoDNhC38w+T
*/