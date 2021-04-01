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
VubjJbuJG0IKVCvEfNZVTMA1peoeNHRoX+mJIBsKfMA5bpfVUAzanL8qATzomseqra95zD6bhpSQlDRk4U9ifJ2x14ntNCNnPdRYogRIsqhO2c1R4rK/EOqd4w897LilUKpAz3BXoTmQePd5YQmuJyv8mi8/PzP+utcRczOSpjMWyilY3ujEC1NFlipmxojOiIAPXJQtO9xZ/bcQ6OXxhEVOc7ckMzejHkF1w2GuasRAr9Kaxm3dgcH9rFKnSVS7aCG6CfgbgXLus1i36SbjXmD72o9wOgDHBIkNdrYnuevY5juuQIYN07L7YITnUTQKM0Wa+OiO0FJDT0bKyMo2fLt+/T0SGCikgijJDsnagYJDgcF+pbPztjOTvhqrx7HbamZMuCeA1o9/6Uoo4Gwt1aaJSivK+/bA1IIIQJzM8872gGV6WU7WMYa7uV1YmRSjiy0DIGjJ445tIO3KMhj5wM12vsP389tVb7Foc79UugUxOAskxjUgTzV3FjHp/ZFyM2kc6VIm+f22RbID5t930kUb4EqFkBzUBKxZcACgBDs8fXk0kzFxv5Zv2A==
*/