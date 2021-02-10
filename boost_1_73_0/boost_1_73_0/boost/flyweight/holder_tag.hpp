/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_HOLDER_TAG_HPP
#define BOOST_FLYWEIGHT_HOLDER_TAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/parameter/parameters.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

namespace boost{

namespace flyweights{

/* Three ways to indicate that a given class T is a holder specifier:
 *   1. Make it derived from holder_marker.
 *   2. Specialize is_holder to evaluate to boost::mpl::true_.
 *   3. Pass it as holder<T> when defining a flyweight type.
 */

struct holder_marker{};

template<typename T>
struct is_holder:is_base_and_derived<holder_marker,T>
{};

template<typename T=parameter::void_>
struct holder:parameter::template_keyword<holder<>,T>
{};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* holder_tag.hpp
LIP9BkjvzIYbBtFgFk7jcDJ2hkQTWORhc2KRTw1MA7iFaxvRYs4rkda9FOa2C1Hs5oiD9t9GvpyPB8Z597hn/NWUuXVP4r9x2jKDXvY4hzszLpTDxLrS7QD4qAvs0btqRYVusbSseY7TQMik2NOg1jTFXgPynFxYWndKm8WS8q3RrPGT0ZxU3OwhCEG48yy/BmpmqFlhJWGJnQr3hLPM+rez4jIcBajobkqUhbdXM73Xe8K2hy1TKSbuoJUVDigCGyaOj2A4Grk2gUV+cT2PYkOUoZO8QSar08bq1yBrck0PmeUNQzKxr2jJqEipk5YER4DymrJf+vNR7Fxs2/x3NSFtPpiJ0hkTtcl0Nokng8kocuLmYGWEnGM4pBjWpdQylVzhIKICQYnMpGuIq+2Dv/3r6ShwPJE7tVItD79/o2MmmO6iMHGuVPhGvd5aRRpcZw7Lu+ZgD/514Hvpm4Wd5PHmQqcd3/SB4EihXipXHXSO5v39WtWt8nSB0x51p9ruNLKzKnPsK/K1GuyEtd9/G9GuCX826dQwdjZYJORxVWd45vzneDmzpPlf/HDkX4SjML6teW+KvEH9SCwrfBVyI2C5tVqW3Ax1QVb0KXI4NtV07bbZeKkpg6rRk/GJhJQyq9KahBPv1DupyzcL
*/