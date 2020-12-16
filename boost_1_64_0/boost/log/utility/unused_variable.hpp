/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   unused_variable.hpp
 * \author Andrey Semashev
 * \date   10.05.2008
 *
 * The header contains definition of a macro to suppress compiler warnings about unused variables.
 */

#ifndef BOOST_LOG_UTILITY_UNUSED_VARIABLE_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_UNUSED_VARIABLE_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(__GNUC__)

//! The macro suppresses compiler warnings for \c var being unused
#define BOOST_LOG_UNUSED_VARIABLE(type, var, initializer) __attribute__((unused)) type var initializer

#else

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

template< typename T >
BOOST_FORCEINLINE void no_unused_warnings(T const&) BOOST_NOEXCEPT {}

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

//! The macro suppresses compiler warnings for \c var being unused
#define BOOST_LOG_UNUSED_VARIABLE(type, var, initializer) type var initializer; ::boost::log::aux::no_unused_warnings(var)

#endif

#endif // BOOST_LOG_UTILITY_UNUSED_VARIABLE_HPP_INCLUDED_

/* unused_variable.hpp
oAJ+BhrBz8FI8Auh/5fififF/b4Cm4J/AZPAr8Fk8BTYFvwW7ASeBZ8Cz4Hp4HlwAPgDmAVeAIeCfwUng1fAmeDP4ALwF6HHhrw1ZLFOPlK0f8uFHpniLNoJYDY4FXwBnAmuBV8BL0k4WxYcgIzeARJvpAP4rA/GQ2CUCftpwN3+GBOAzdDw7QG/QoLtBSeGoo0BfXH/t8De4LvgIvAAuA88KOLrzBvvgS1EusswFUV8q4t0d4ryVhuMB+sK/83yxlPgWuFfhYE9v+KE/6agHxgPBorfieL3GjBB38Muxiig0cM3divDOpcxoA/o0P2JsYQ+LsnvzyL8FRf1p4zuT/TloI8Hf6OFvzGgAXzGzV9OIf4aCH/NhL9k4a+D3t+IOiP6GejPryzhbzDI51FEfRoq6tMwsAI4HKwCjgAbgSPBHPEtT/8jBlLxiOGxvulJcvfuP+Z5tXgv/5Fn1mI//iPPreX77v+B82r5PnpPe+gf85zaZkibJY9xRm1h59O673UX77rr+9y7I/wxMEtg9sB8CXMdJvQ9A6kL0wamH8zk94r2wBddRVfRVXQVXUXXv+P6d+7/T/sn7f8/gHmTm0vc3v932/9/EHbOpW52bvv/e7vt/48R+/+fhmFiXP0y/Hav6LZfO+3R+/9f4u4DPc7LICx9XmZLgb3ePbjdIE/zL7q/4mJ//xsU32jM2/9vMWre918BIO7vAHwJN335OwDJRkOBdwD6/RPeAdjyiHcAgmFSYHLgjlRyT0PxDkCBNAjJzS/uzuUx7RCGnnYfiHcA8tZrzdC5Gn8HQOis1uD6Crnb/v/ofPv/+4u94Y3dy/9jrFcI3fU1iA8K2f+/DiZQPPtth7vsfGmh7//3WCbWc7ezPKUHwils/7+wx90H5t//D/mj9/+v4m4WeNr/Df+F7/9fxO1XPXT//2pu/2yh+/+vVcq//38Z/90fs5M20tFt/79/tPhGmND5HndXk/y9nMM8wf7/Lf/g/v/GbxB+Ne2A9WcwGjya24bweI4XDZC+/98tz1N03Sdxt1EdPLYfsHvIXn/P7Ub04+/rh9uH7usPFt9Qm87dlOjwF2h9lVxul5vuN/+4d690Zb723D5Xn/fE3v7BbvvvJW7/XHuJfiR9Lw+URnnNkUKMDaVsv2FSaGB7aV3wCKlaeDNpR7GxUoOSw6RDUaOlVuVaSCcqjJVSKydJ56uMlgbVaCldqzVWmlAvSWINxknzG7eQApuNkF5skSSVaTlaeqX1ftl9P/6LPK4yWanvx8cVw9coWxlRKxaRFtiDPkWaoTUj32g1pTI+PaUXTM3INVMpqax5jLTL0oxowWWkOmHDpHetzUhwsXJScuQQ6TNbM1I+qrTUvWyW9J29GalRoZyUFT1E+tXRjDSvUloaXz1LYrWakXa1yknZdQdK3nFtSO+40tKqRllSqabNyPCm5aSc+CFS9aRmZEZSacl9T/4GEef6Iu14meZxtiSVJVatk0a0Mabb6rOWn9XV1uvqDts19aD9Z/Uzx031G+ct9dfYn1Wl6c9qfbf98GOr8TqSlEQuqsO1S+oI02fqc5aD6irrB/B/SH3LflQ94TiinnZ+pV6LPaSSpkdU933z2/KnI2QwDt4utSpFkjDvU186JD0jdddak7e0KOmvhn7SMFM8OWoKla4ETJZmWeLJGUtJyYR0fN6aSK5bQ6XQyLHSy7Z4IkdFSBXKjpbesieSkAoWKSG6j/ShI55EVYmQWlQfJ33tbElq1rJIHeqOlf4aG08ax0VIfRuNlv5wJZL2TS3SyPixkikpnmQkRejp6A+zW8SZl0Ehu8rjXK5NWTJX+kIaKKVpg6UbhqekEaau0o2A/tI=
*/