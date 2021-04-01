/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_TRACKING_TAG_HPP
#define BOOST_FLYWEIGHT_TRACKING_TAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/parameter/parameters.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

namespace boost{

namespace flyweights{

/* Three ways to indicate that a given class T is a tracking policy:
 *   1. Make it derived from tracking_marker.
 *   2. Specialize is_tracking to evaluate to boost::mpl::true_.
 *   3. Pass it as tracking<T> when defining a flyweight type.
 */

struct tracking_marker{};

template<typename T>
struct is_tracking:is_base_and_derived<tracking_marker,T>
{};

template<typename T=parameter::void_>
struct tracking:parameter::template_keyword<tracking<>,T>
{};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* tracking_tag.hpp
4Y2s6GHtL/r3XFQCI1SPlZNfrIwJy65DPD+PsWleCTMx2sjgQ2JZLQP/7cfKgqBZyEu+KCxmqNMtK0KGgJj4B3BMUlLO2w0KDlSwFO6HCDxijO/1xGoruVc1Ndri/zFIRuw5ykwIGEas3PyHjradPfg4a8B1IbY1qohuqMU5fFr0BG8l5hpwywz2BnVzVB9NXfFVHQ0ffpuioI7bDMfVm/MiS1sV7EegAHevmZtPxYJqw1Ua2Buz1QdoSYRxayhEbsv9qeZdMGG/j2z7nNtid3cmBj7RTtTdFSI4aIOtux7GRjSChJQ0JmcTNc3kXACbUHnhiE2YxGaD/DbB4vDp/IH77znyOYYfHPzEQcgbeQSWDBHvJXHk4YJx0/sFrNCtplMJuKrLcu6acS9uL7eLJeRCvtPT0rHjBWZ72J3q0zl5hwU/QScNW7btDGYmjb412uXVC6dntn0ME0IvfrvEvwLSVTjOThOGmuC+hXcREOK+Id+ewaU1TBCZNPNnAh+uLn/WYf6GzvCRdoDiTzkc8L23qpkIZf0mUGpRz4gTbF5cO8nqID+U2lSI6A==
*/