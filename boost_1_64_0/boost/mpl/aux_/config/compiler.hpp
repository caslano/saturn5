
#ifndef BOOST_MPL_AUX_CONFIG_COMPILER_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_COMPILER_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_CFG_COMPILER_DIR)

#   include <boost/mpl/aux_/config/dtp.hpp>
#   include <boost/mpl/aux_/config/ttp.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   include <boost/mpl/aux_/config/msvc.hpp>
#   include <boost/mpl/aux_/config/gcc.hpp>
#   include <boost/mpl/aux_/config/workaround.hpp>

#   if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
#       define BOOST_MPL_CFG_COMPILER_DIR msvc60

#   elif BOOST_WORKAROUND(BOOST_MSVC, == 1300)
#       define BOOST_MPL_CFG_COMPILER_DIR msvc70

#   elif BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, BOOST_TESTED_AT(0x0304))
#       define BOOST_MPL_CFG_COMPILER_DIR gcc

#   elif BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610))
#       if !defined(BOOST_MPL_CFG_NO_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
#           define BOOST_MPL_CFG_COMPILER_DIR bcc551
#       elif BOOST_WORKAROUND(__BORLANDC__, >= 0x590)
#           define BOOST_MPL_CFG_COMPILER_DIR bcc
#       else
#           define BOOST_MPL_CFG_COMPILER_DIR bcc_pre590
#       endif

#   elif BOOST_WORKAROUND(__DMC__, BOOST_TESTED_AT(0x840))
#       define BOOST_MPL_CFG_COMPILER_DIR dmc

#   elif defined(__MWERKS__)
#       if defined(BOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
#           define BOOST_MPL_CFG_COMPILER_DIR mwcw
#       else
#           define BOOST_MPL_CFG_COMPILER_DIR plain
#       endif

#   elif defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#       define BOOST_MPL_CFG_COMPILER_DIR no_ctps

#   elif defined(BOOST_MPL_CFG_NO_TEMPLATE_TEMPLATE_PARAMETERS)
#       define BOOST_MPL_CFG_COMPILER_DIR no_ttp

#   else
#       define BOOST_MPL_CFG_COMPILER_DIR plain
#   endif

#endif // BOOST_MPL_CFG_COMPILER_DIR

#endif // BOOST_MPL_AUX_CONFIG_COMPILER_HPP_INCLUDED

/* compiler.hpp
TTdfGSfIUDI78VL6MumNlqb65LB9r4aMX9j8Ktht//uiis0yHem/UCqfM7jMa39BKQBd+emf7tmjjxPmYnDvHXWbf3bpJ0n+0Kb48wfkTz9If6u4SLFvysTB73my4fmvrQq83ZbaCcza9vsMTlexekIBw3XY3kfI0QprvFacX6CoE1O1gXVBbnOE15OweRcqtZdYZUmpay14cmPzhY4K+PnFq3bAoKqiTPLurv30vfzhwbQ97TusD5GW2491Hc+dOhfH2WpvC9oix9wc4Pp0xLOgI4rSzbID173OrrP6yVFvmerW+totQHukVMvX5JRJXr2qry0e9sLPNbZlafWpyz2OW0zuPWDGwFdur8d/ilmyaNzn9T2ud/jZOuhdf6W+Cm1rlHsS9yED4cVuE5+osAFaDjx7UaW/Wnaa3ayN1seur0lew/XIbbjUC0x/6Kpwmt6/+q9Ss/16DSfu/XijUNP2ESxTObsgfN1R0PJ+yeHclzM/6S+tmTBpHeDs8M8x2Pf4bvERlVm0w5a1D0YeiAwaBQAJrPDnr32z40v/Sdl3RyqoXZVt1dlHjKMqGkdv5YoA3fb6DjTSXb90Xhro+gROL8w/OTzcLzQy4jMjoFbHTjeKvqnZLyTc0Llx0lCQwAkvlFdftXr7g4CQz9UKW+e/sTz08Os2U9mW8x+z7x0clGO5fPTH8gm1eX3iptabmx1qmWGmb1qvuM25YrjqK8WWNNXvdvjRapti1rms8PKVJ47vJPiNzXMxjUaNw9vb6emaB9MG/MpvO7JevFd8fFlRWLRy2CtHSoyuz6I2Ur2qLEVmmd7JU9JHh+dkq45MWXpjLTgXcj6SZNXzYNEVdb0rUxauiNw396dewqb0uktPz5AHOjouCInu/6nq/cCZDzRtbAd/SnrjOCtsMX7X4Ou79Nhmht7wmqh0vrjfsvCq8Z9ocHEe5rdv+P6E6KG/8ptFknMN6rl82DBy0PLB8fdS43fH19fXz74c0zqoRefavMRFjY3LDk/+ErrqgZLpvvEDXo6e7lnnU+3otKh6oUv9wAUk354v2FZ7dB4HTLEeSFszafq6ydmW7MhbnjW7U+71S5Y9PSCwg2i9e6lF9DtzVG+x7XZ8O1aHl1tr53Ysj3uG9Bsqp226PSXkhaZh35nmm0Z+m+dk/e3HiPE3QjM3gUU/vz/bW7vyyerJb94nlVxNCPTWnfd6qcaNnUlAKfDIINn6v9afWyxN/Uy5Xzgw/fSBXSfkabOeAkAiFbdMW6t1IZml+dCwzWDGnYxTd2JSNY02Ets3ts+85bG+fZCoiDlOOdNYOL3reGMPGU1J8pPkUgJM+tm4HJPPCg/67Ohgu0x3YWxCv0kJ+XGJMvIf3z38tKKw39vGQ9ZGxk2mKb23fxp6bu75YXlLVSat4K77ttIwRWHNrZ9Tuezm559Lg2qjUlMWSM/3axhCu//ON/7c+DdfPmyN0ln2jHmuTOC9Z08MfXPZHlpoDwogkJKXQ1ut+wj3lR8q7oY9c8WXSxZeI3atM3qyo/2oVidcV3fW78vlYEyKn7Q7/NszrXVBGwSh2rf9lQvkwnToiUVBAS+ovqNfMezXXHtfOedg6QSja4bjv8b7zT/izDOSflVZ5KHXct07CzDLH7lumW/eGnfzOCi612jymbuZ0ttzW4+gcDNP54JPR7aM2bfx3oxRMXtWhgTNCvBv/sYellpuNiCQQGM5evO1c0ye/ngywGW4nwG+XArw2iTHaa+vWo3Nj+NbKPa/LxdJa6EgLDI8LjosrjnhRdxRZvbAsLAXC8OiF4ZdjNwcuUotvnhzpOPE7PwfE2VT7yz8rHbhzRH7Y8/s+1YPseN+abjupZc=
*/