
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_DETAIL_CONFIG_H
#define BOOST_COROUTINES2_DETAIL_CONFIG_H

#include <boost/config.hpp>
#include <boost/context/detail/config.hpp>
#include <boost/detail/workaround.hpp>

#ifdef BOOST_COROUTINES2_DECL
# undef BOOST_COROUTINES2_DECL
#endif

#if (defined(BOOST_ALL_DYN_LINK) || defined(BOOST_COROUTINES2_DYN_LINK) ) && ! defined(BOOST_COROUTINES2_STATIC_LINK)
# if defined(BOOST_COROUTINES2_SOURCE)
#  define BOOST_COROUTINES2_DECL BOOST_SYMBOL_EXPORT
# else
#  define BOOST_COROUTINES2_DECL BOOST_SYMBOL_IMPORT
# endif
#endif

#if ! defined(BOOST_COROUTINES2_DECL)
# define BOOST_COROUTINES2_DECL
#endif

#endif // BOOST_COROUTINES2_DETAIL_CONFIG_H

/* config.hpp
X4etdLfn/ANQSwMECgAAAAgALWdKUlbezw0RBAAAuAgAADUACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX0ZSRVNIX0NPTk5FQ1QuM1VUBQABtkgkYK1U227jNhB911cM3Ic6gSInTYF022BRxVE26jqWIcm7NWBAoCUqYkuRBknFMZr+e4e0vLk0QPKwMiRKY86c4ZkzEywHcPjdLi+w4eDNq3B3gReue6eZkn/R0rzuUBQPsPuh4xLXd0CN4NHroTiAd3k9wNB5FT3WuX0vinfALW2S9jGyzsvCvqJl59n7j+V6q9htY2A4PoCTDx9+gSP46fjkzIdLIhjlkBkqVlTd+nBeOcvvDbm/DzT96AM1QHjwLGDeMA1a1mZDFAV856ykQtMKiIaK6lKxFX4wAaahUDNOYZzMFvH0kw+bhpVNH2crO9CN7HgFDbmjoGhJ2d0uzJooA7LGCBi/YtpgzM4wKQKEp2CoanUfxiZBuJZA7gjjZIVwxEBjzFr/OhqVneJ4klElSz0q91QEjWlfnGqB2bRkC3JtwEjoNPXB7vehlRWr7YoUoXHdrTjTjf+YFgKKaiQVaMp5Hw5dGdW7I1DIerZ8uxPWmD0zdtFSaIu2aWT7bCPS2geqOyUQ
*/