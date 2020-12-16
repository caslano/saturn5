// Copyright (C) 2006 Douglas Gregor <doug.gregor -at- gmail.com>

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/** @file config.hpp
 *
 *  This header provides auto-linking and configuration support for the 
 *  Boost.MPI python bindings.
 */
#ifndef BOOST_MPI_PYTHON_CONFIG_HPP
#define BOOST_MPI_PYTHON_CONFIG_HPP

#include <boost/mpi/config.hpp>

/*****************************************************************************
 *                                                                           *
 *  DLL import/export options                                                *  
 *                                                                           *
 *****************************************************************************/

#if (defined(BOOST_MPI_PYTHON_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)) && !defined(BOOST_MPI_PYTHON_STATIC_LINK)
#  if defined(BOOST_MPI_PYTHON_SOURCE)
#     define BOOST_MPI_PYTHON_DECL BOOST_SYMBOL_EXPORT
#     define BOOST_MPI_PYTHON_BUILD_DLL
#  else
#     define BOOST_MPI_PYTHON_DECL BOOST_SYMBOL_IMPORT
#  endif
#endif

#ifndef BOOST_MPI_PYTHON_DECL
#  define BOOST_MPI_PYTHON_DECL
#endif

#if !defined(BOOST_MPI_PYTHON_NO_LIB) && !defined(BOOST_MPI_PYTHON_SOURCE) && !defined(BOOST_ALL_NO_LIB)
#  define BOOST_LIB_NAME boost_mpi_python
#  if defined(BOOST_MPI_PYTHON_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)
#     define BOOST_DYN_LINK
#  endif
#  ifdef BOOST_MPI_PYTHON_DIAG
#     define BOOST_LIB_DIAGNOSTIC
#  endif
#  include <boost/config/auto_link.hpp>
#endif

#endif // BOOST_MPI_PYTHON_CONFIG_HPP

/* config.hpp
2nQ5mRmCkG7a7Lgl3UDsotqbXRJEmE8nyXV4av110FVxLpot7bTkqPLWbOw0b81oZ+eJkbc6whtKNryM0RXjlyFTzlxxcL8z12h/RQC+Y8ZARlTAU+/RwM10YziG3bS78/0U0kjeymZtW5bWcomb+uUKdDiO0/JVb6RyCPoGlxVW8u5bomOKUHb4MmxDrr3LrBaU0USgq3UbAXUmGkgHxtTtd2vI7RQsbqbdQF7PZm5wd9KPvPem7tvgWeKRMEXObe95N9N9XtTnb9Iv/38S/pffF275Zva3Lf1x8WMx69uY+IHtoOfd4wfquIJ2SMCOJp8zJGBHG792Y6TEJaCnkdGR7JIW27Hl3tJTPI3bH5ZLn2MjdLPbZLEXqaE6ftwqE425h56p2fCppXbQlPk2DEmIQJaGWbrUZtUrNQBCgQVyCAbMWe2AOdsRss9HIfsIBq3/kQPmGAlQp4PMFei6ThKYqBPI38yZEDv+1s0z9jr+1vjayL7E31reIzrelj9D3p3t8eAGC65s5Dr7QAC57Q6V1+ARgdUZ5qgcuTSxA6n2l08z/eUPjHWXT643Ys9TTEX7YubLRjrFE+yDSoNeNWhN1HTZO5glOcV0MChNeUGomXtjaNTtY+ci0RoHmt89Zm3Ud5esdXr5HkhA8D1K3vP9E6b/6yP2fK9OEPMRDm7rtGXXOT4JAYn8Mrp8HLWxJFO8M1+83yzph+GpXIVujHR2zf9V5vehaA8JjFY7agzJRR1TQZXcaq85OVA+YkPKCfNWOUtb+azt786hhGUeL7hfLxVx6tRf5TddCXDWSQ0bmSHHbGlK7yunoDrsPjj9GdO/oC2wkKoTEtN+Eel3IhPdMKP+P3SOyzwfpLhPytWGR2LUIfTX/AOi49Gt6oiNZ9ZO5RLHM1u4G/zGL4Vv3w1+4ZfCj+2MhQ98Of7PnPHGZjyTmHsFflsU/Kg9wg/qcML33yP8wi+i4p/F8eON5/9I+rD6yTTL00Y889XkpzTZsgz7kT5rB9K88DHLZMCEHBObRExv9/4BlgcOwwJCu/keS0+UK/BmSgKAt1/bZVtDVPyVVedx/JVtNXb8FU5hpfkJ0GFgyvl4zX4i0oX4K+b9J2RDlMNZiEB2XENlNn1hVtwvFzjaKsZZy/DF4QtnkUyU7dDTG/V2aFg24xpwgg+2lv4r0PJ1TUmkdzgrCLp0FZr5reHtDsU7d+97bPfva8L4/zEqnkbtEGICiLHa4dbTWOtpvPU00nrKs54GmU/U4HUqqb52KsvB2nFW/vnW0xTrqYieWDzXrGHozNAh8pAVMuQhGx4pv+ou+lmVVy3HXlsm9yyVu5LUDjzg9vXT17Wkrnsjla4wRhCFs2liKFzAWK7MCo4KDOnZz6C74KppZjvubu3VU0SYqbsL0dirujc08v/1ZVkyp/hJIC+qUOvPgLRVTzxKdePTa9bwX7ZFv9GNevH31ZwxBRlTzIyNlNGwgN9Gq16PC7UDhPy/povmXjuJVehGTqxQB+hE7nhdcNcvzESOJqyLN+vEsY7if9eJ5Y7ij+nEXEfxu3XieEfxeToxgI8ImB+RRB8hlyePVksWc4BCAmAkb91nK7evpfLo+DmUdm0B5WK9kIZnoYdGfqpvzEfLBvHzghw0iP9CsSTviXvMTcLabAuMrzKWhzWUiAZdwXWtYUyuUP8GjJqM0TPz7WjwZamyS+RH7aAAmmsXSTCSj4ZjMJ3JjdPRB686c2reobpD9EDuZ7X8PwcTkIc1/Nc1/eiGRn64kS7XnrneLUB1dA+3JGc8Qum1W2h+9oQfZ/06kz6U90MdFatLnrbvsVmY4jJXfwS3YDrDyPdJs09zgE5OYdZBK+g=
*/