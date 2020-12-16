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
MMr9xzj1fV2+MS+CPbhsJ51kO2bZ8U9vcMLs4d/wb1v4ddnvUDh327nfwdsfhb6bil69e+PRhnwd+3uY9uejXzP8bKOcww+Sl9GSVhKC/2EoLs2r7U2i0ZL7Upn4NL3WyFj0RSb6ZGKi8++TTPRcyUQ/XI/MbOM98KyfTonTyN5KfAdrYMVZiKkfYfrxXsQ004hpEmDKqz2V6HkHSvCQMG4mhRhBGytuuhTaqobd89TeeJ0IBmuO0wj0Pgl6OIU7WTqe+zHr68Ug/5ICmGLtwEfUclxxfHm1ZxJhifdSHz+2lvcxtuONA/gVzqISHy2jEn/kJfw8Oo6by0gvxT7Moz5cu0x+jVtkH3YEVbQ0hLlzmeiIL5MbIPkcSq7gyX7tnWTWtaNF15IntgC1oSu0QQ8iRgCDv0b0ownPEIl+cTK3pzq2/azMFd8hlVdJ41OPM75CE8z8pP1+d71dfc7+L5tB2l4glbN70+scs439oOrL/8J+YGZ10qhSIaTnW6Ow9TIa2V0Ba61iLFakiwsJohNCkPUIjeVscB+XvRRS53QXT8FL58FTctCHf7oGx+GfYPCM8CQs0DcBCozGp73wVDkKn97CpyHh4Ugh+rNVPEKG2Wm9LZ6Su+JTET61xad8qXkohCfuOmh9vRKkbHpBDTwP2gtZ/bR9icwRZVEIkoTz3+Rgd/xzQrAz/jmH3oLBznPhD2tIt3CO6oEy3Jm/pbK3dP7WCt/+i64fidUyreq9kV+SkRfpoq9fO3M7Cb5KoSQd9ErwKYfHR0zFFy97KYArVeiHCecz993Za019xM7MNY+3ZZ9LUgoFKT7tuW1cGifrLCwAAuhvXpbqNPQsYBSoL+O0H+1ONWsXvabWVUB1cEYmgDXcvY4zuPHh3xIm/J/jyQOY/EAZWyP9zGWpk8l6c2k+0bJRtMPRTt5lSlrN7CIoYQ8N2BdOTHCQDKi3dvHLMYj+uDYerrwZ/fdBasVHMDiAI1a4u5edVoxKgZVocy0hIcGjrjQrlbLMUhBxFyNAACrAt62FgIPaVDoahgWiLdIO4pfgAgo5SGfJQeqXoyUAHjv5aKHwMnywzHmmPhKfzMw8dcKN+tRRmlIsTfeLRVNyiYvhTfEXYCnRlIB2EjTFOMV8kvpcTr2fUx8Q1Nfbm2P2xmd3aokWbog1/te2bPxrhH/21hj4hwr8ttevqwm17Hi/6HjWhwHtpmebXsn8hmUMHW6qXXz503F2sXk92/mZvp7JMVEoSMvV3n+G94bFdy9UCMrlBIXer4/rlG+mZ3gMegpUekg6pc+dPL9KytsbbJDS9Hh45lMaD+9/ItbDAiXklY0l0eOMWhJXZulL4uubYoyzN55rwZIYpf//hFpxxSbzevj8Uc7axe4P9mUeJEzUkJM/VjXqxD2eTtzjVN2HqLF5JWxJwb6QkQLnfGPjE8Ver5M/Udfrcqv1eu6WxZCqLNlzt9KqrKzaXlq1G/b/wlX71VXxrtpNr999P1bX73Kr9Zuapizh1DTDKu6lVTxxf/yr+Lp34lximm3PpH8aWDmvaEIVTRPtVeCkeGCuSfE0VOvznmiaeWHIpQZJ1u/FF35Bg6Lsvz9i7Slg9dAZvf2O1ZBWk1Gxpz6iffxjfVzyneEW+G4ifKcivn7748MX/jAa3yWHGL4P/g748uOkb5kFviTCV4P4Fr0XH74xFvj2vsTwBTXAt/KH+PAdORCN7xbCl434Pn83PnyrLPAtfoThe+szwJcYJ32TLPD5Cd98xFcQJ31phE/783NkzZIr41Y+UcsxNX//oYGfKqLg39huBz7UEN2e3d+x9kxaieP/+/jaM9wCXyXhS0N8/d6JD1+4Phpfp80=
*/