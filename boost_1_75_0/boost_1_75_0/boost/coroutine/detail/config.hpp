
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_CONFIG_H
#define BOOST_COROUTINES_DETAIL_CONFIG_H

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#ifdef BOOST_COROUTINES_DECL
# undef BOOST_COROUTINES_DECL
#endif

#if (defined(BOOST_ALL_DYN_LINK) || defined(BOOST_COROUTINES_DYN_LINK) ) && ! defined(BOOST_COROUTINES_STATIC_LINK)
# if defined(BOOST_COROUTINES_SOURCE)
#  define BOOST_COROUTINES_DECL BOOST_SYMBOL_EXPORT
#  define BOOST_COROUTINES_BUILD_DLL
# else
#  define BOOST_COROUTINES_DECL BOOST_SYMBOL_IMPORT
# endif
#endif

#if ! defined(BOOST_COROUTINES_DECL)
# define BOOST_COROUTINES_DECL
#endif

#if ! defined(BOOST_COROUTINES_SOURCE) && ! defined(BOOST_ALL_NO_LIB) && ! defined(BOOST_COROUTINES_NO_LIB)
# define BOOST_LIB_NAME boost_coroutine
# if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_COROUTINES_DYN_LINK)
#  define BOOST_DYN_LINK
# endif
# include <boost/config/auto_link.hpp>
#endif

#define BOOST_COROUTINES_UNIDIRECT
#define BOOST_COROUTINES_SYMMETRIC

#endif // BOOST_COROUTINES_DETAIL_CONFIG_H

/* config.hpp
0x3IL0HWx+Cjp4bdPgt5YsrcI9Tt4tz4Hey1wirWGV30NW0tPEoGweiKEb763hqPrvcI5i0KFzjPxcpWy8GdzRVC55B6QYUCAZ/ISi/WAY/4HT1KNUns8/51Chht8yXpp4AUOS0BwBhbEheiag/+0n4QhmGaCGg4lHDcL4Efs+14p+DRS2786eb14i0UbxxKWAOSuRUrWO2UUYEkN0IY5CG07RBSGnzv2G781EWxt7aPCOpi70/uNARnocjNRbBT+4DYnQ4avOr+X0qwlaSb+FvaKYqC90m7odxs/UJOcowyh5DSTlpjmsuzVNC7HK5uuF0ADR7OUzb9Ei9mAOwKgVZPwTYp4kbQXy5zi+501nHp/nRsfWcT8FyupMT402ljYQf+6UEiXchQiEw3BCQOh9BGxb4G+vv6JZ+F7uQ8d/r7zEqAQOwQya7dMuyyeLg1faz6qIY9NSjGuNh4/Z18GZ3SLt1d0LI0G4LkScy/WCE+5Q5h1//oD4POLoTGGuJqTfxl47+M9qUDNnhZzRphrCVSIRXWAkai8XGwQW9iqLZHWn/m9TnE4OGHLNWtMdtcShQImDuxLnFFV3gGlPnO1dxrgY50nn4ZX1f8u3EfVDNYI4jywvx3c7ERIPeH2KDJxXOq6G0dLLVlc3YVMA05P3h6O4QO9Y2DPIDhgYphOxNtNKgPXMpPlB2ft7q7sJncUa6i+EJ2BFL93rKd
*/