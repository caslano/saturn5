
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
BAAAeQkAADwACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX0ROU19VU0VfR0xPQkFMX0NBQ0hFLjNVVAUAAbZIJGCtVVFv2zYQftevuHovcaDISTM0S5sVU2y11uJIhiU3M2BAoCUq4kCLgkjZCZr99x0peZ6zrslDZdgSKd53d999d3aWPTj+YZflaDh48UrMN8EL7zujaS3+pKn6tkGSPEH7QcMl3l/hagB7q6ekD6+yeoIjY5V0vq70c5K8wt1SB6l/Btp4mehH3GktO/uhqB5rdl8oOBr24ezy8hc4gbenZ5c2jEjJKIdI0XJF63sbrjKz81tBHh4cST/aQBUQ7hwAxgWTIEWutqSmgM+cpbSUNAMiIaMyrdkKF6wEVVDIGacwDKcLP/hsw7ZgadHhPIoGZCEankFBNhRqmlK2aWEqUisQOSIgfsakQsxGMVE66J6CovVadjA6CMKlALIhjJMVuiMKCqUq+X4wSJuaYyaDTKRykO6ocAq1fpbVAqNZk0cQlQIloJHUBn3ehrXIWK7vSBFuVs2KM1nY+7DQYZkNRA2Sct7BoSmjsk2BQtSxZeuTUGH0TOmbFKXU3raFWB8cRFo7oLypS3SHtOC5TCDxNjRlRmtz3hCx89Kx
*/