/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_LOCKING_TAG_HPP
#define BOOST_FLYWEIGHT_LOCKING_TAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/parameter/parameters.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

namespace boost{

namespace flyweights{

/* Three ways to indicate that a given class T is a locking policy:
 *   1. Make it derived from locking_marker.
 *   2. Specialize is_locking to evaluate to boost::mpl::true_.
 *   3. Pass it as locking<T> when defining a flyweight type.
 */

struct locking_marker{};

template<typename T>
struct is_locking:is_base_and_derived<locking_marker,T>
{};

template<typename T=parameter::void_>
struct locking:parameter::template_keyword<locking<>,T>
{};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* locking_tag.hpp
93N6uM7gOjxyIQ+ToNWhRJDf05KaKDa3BwdtbpNnklPdau97Yag6lQTVCfe5P23R1mLaeVbAvnWE71OvLo3Mjw3douVHRQA/5nf7F/yIaQnHj5525Mc2Se8fIahveTYi5nZyKOLlwUj3eUhDJRJdpMV/7voviC7+NdAidbmkwwFdv+z/jgPK5rdJTBudlVXMeEZKn0M+brcs9zsRwUfyzO5aabJUv4Cr5PjeQwAive9OjMK7nvUyNvkN3OePi6VzR7UmcTjHN1CCUJyrBkFMx4ElgOzzHvtd7p1UGgjfN1B/tEXyziqDxZZMKAEPLWsP1jM8GdOBT4iTYVDM7lrmFJy0Y9NkFamA6mOvp/2IePZI2xtQXmxvan5GCtobSIW9gXQ8Iyf2Bupg6auLlavf0zgOu2Ip3dmUJX+LeEJSQfwl7M7d1i5/KflSjrGJwN/S9xRbr6TEwcTG0hRqvlNM/0pj3Zl7VVG/4k5UtI0QxntqaKlux4MV8wArprn2ulMK1cUh76r5ypVY38YUM7elP0SJSKyHtmjpzci4h6VlVNdsABq3so+HA439icYymLi8bdivG18gapPIJMa+CKo/GC7GDAZbdKreFn3JYNUWfUhJ6XNJtsnf6x9hX66gXSn/C78E2ZcNNuK9g1Qb8XnCRpyh2oiRJTozsXGc9l0SyU48oXNIO/EgU4CduFfnqM7//Rw4Kp/uY5B/Bhse
*/