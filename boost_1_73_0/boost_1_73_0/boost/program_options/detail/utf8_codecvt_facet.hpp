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
dGEvdGVzdDEyMjdVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSo6j8sdcBAADTAwAAHwAJAAAAAAABAAAAAAAOZjUAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTIyOFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKvCzukpwIAAMgGAAAfAAkAAAAAAAEAAAAAACtoNQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMjI5VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUu9ZiBc+AQAAIQIAAB4ACQAAAAAAAQAAAAAAGGs1AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEyM1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKjZpbl7wEAAHwEAAAfAAkAAAAAAAEAAAAAAJtsNQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMjMwVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUhafP1WSAQAAYQMAAB8ACQAAAAAAAQAAAAAA0G41AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEyMzFVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSsmmYI/4BAAC0BAAAHwAJAAAAAAABAAAAAACo
*/