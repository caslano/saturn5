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
8p5OUZF1V7To9bQs4X4dTPwMW6J5BztB8x5mq3Ov7Xgs20uxiAZgu6mKZckBP3sWKEwFkBLwdXK03/AiJBFgqR+d4wYlxWgK50PmpP6QUtQX+cAarqWH09kFXxXXSqGa0QwRMTVKoX4MNv4dXagggpwI5iIsoVKoE6c/l0f3tAKOPefcJhe61Ld+2J6bbdTFJy9V9wd0yf03lFGj+Q/vHyg1x9Kv1PKaD4++QGmOgY0CdcK9e0d+rCKmSn/lRFJUTXk4FYb+3foVkxbf0J4ovHxWTgKfznYM784ix30kyIY6914MigjqT6TtC+mISH6apMMjo17kZwMyjo7T+7C5ldTADVpyjGZIzUL6t5iej3ymCtMJGvXESnQ+cK29FpbbOAa/AeGv2AZHxC7mZWlzAAuliq2Hor6+6KnvB9aGP3CLwv19N+ryjiVnmkq7X0E/7ypNuCFCXsJd3Fi3JZE99NkMWSH14eHH6Wmoi0CgOTXpggk1OrJ/tMjJZrWriQhniJg/j0IedVte8S3PgdgLmGF2dA43Hh+TeoJdVScBOIFUBuQgscyghk5fMjI2eoEl/J10lQXqYaa+5pUWnfAgOY6UJgfE1ctFZ63ODY/rQyV1EJ4OqqaObkCz3McsFdaRMO3LxlYY1vJiQz49l25i+IGi9s1w/R3Pi2Si5tplcnNrIXh+47yJTcgG+aULqH3/Kb7LWE6PnMRDLPPN
*/