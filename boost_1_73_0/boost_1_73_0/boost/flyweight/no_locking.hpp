/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_NO_LOCKING_HPP
#define BOOST_FLYWEIGHT_NO_LOCKING_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/flyweight/no_locking_fwd.hpp>
#include <boost/flyweight/locking_tag.hpp>

/* null locking policy */

namespace boost{

namespace flyweights{

struct no_locking:locking_marker
{
  struct             mutex_type{};
  typedef mutex_type lock_type;
};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* no_locking.hpp
BGIJCZPLki+Q4AVUGYOU5wzGnn/vTN+bsMn4Mmv0bEUNMhN1nkAWPzIo2ZLxR61mHZcViBQ1oP6Eywp11hUXhYXmGVSsXMlGDTkR51JA/BjzPF6gubiCrKrW8s1otKzLHG8ySsRSjpZtKKysWvVudY/erOItiHUFlYBaMhOI34SVSHhKTwwRHq7rRc5lZu7dQoNFMhIlSJbnjToU5UzqKzAImmiZxAlr9J5X9JCikGRtk4nVASOGtVGU1mWB5jAsyJcIDLwJdZGwUvGrQLRWmiirkH8lZXvfExAFegUDOwAnGMAillyacOeE195tCHf2bGZPw3vwrsCe3jf6PjjTS8QGR6slsKd1ySR6UQJfrXPOkgPj37TSDSu8hvHtzPX8MJpNLp1Z5M+80Bt7bgBnMDg9h1/rAuF9+moAg5wvKP/w2jp7bZ3gAVERi+U2kqyiTOM/gkqi3uAapvbNxPiS8vkLTC8mrRSVWIpcIuZysdFpKVnCS+ojlVCKgvup5wdOYHzHi2VeJwzekWUNxuxnQxlZCjzvOzSkN3CcIUxyRMsXnDEhF8UDLHi1iuVfR2+V0ctJMJ45fuh4U8OPMR+x5qoyKgeRJ3TSiBBiSLfSGB1j1aa8YNICJyXkJ6YuvIbbyDniVSJK424A2uhS
*/