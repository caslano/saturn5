// Copyright (c) 2001 Ronald Garcia, Indiana University (garcia@osl.iu.edu)
// Andrew Lumsdaine, Indiana University (lums@osl.iu.edu). Permission to copy, 
// use, modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided "as is"
// without express or implied warranty, and with no claim as to its suitability
// for any purpose.

#ifndef BOOST_PROGRAM_OPTIONS_UTF8_CODECVT_FACET_HPP
#define BOOST_PROGRAM_OPTIONS_UTF8_CODECVT_FACET_HPP

#include <boost/program_options/config.hpp>

#define BOOST_UTF8_BEGIN_NAMESPACE \
     namespace boost { namespace program_options { namespace detail {

#define BOOST_UTF8_END_NAMESPACE }}}
#define BOOST_UTF8_DECL BOOST_PROGRAM_OPTIONS_DECL

#include <boost/detail/utf8_codecvt_facet.hpp>

#undef BOOST_UTF8_BEGIN_NAMESPACE
#undef BOOST_UTF8_END_NAMESPACE
#undef BOOST_UTF8_DECL

#endif

/* utf8_codecvt_facet.hpp
aBbQySpju+QZW+FmxlvP8FbiSqw90qfCEv/s9783Bsr1Qnhz7bwtyhTLIZrZWNaIfxEWjqEJf7SYcJaBm/C8lAYtKipWvlSUoOVXnvHZeLKttEJuAb0WNBvmEOrJ+CGKuSD9CBTc3sN7YT2vtBuuUM3uBy1RRy+BvYHV5uei3QS1FzByIFj/nl0gO4DgubtALErFkHMINdAPCCTOuRo6o26/T9acK6JSchNLmcU1WQo3pobC
*/