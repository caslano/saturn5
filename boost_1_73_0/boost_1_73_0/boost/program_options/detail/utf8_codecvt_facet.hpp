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
STgDXeYuA4VLlBfrhTkvEnIceTXTz1vIgDtH49a6lHcmH9mWX6gG/WKxFDGWhw53GvwNGh86CH7zqVcikb76XDUW+nVLQF1H2cOEn+vyzRI7Hv+gc77at9wxT7A9tI1das92yK8OltieE+ZDWww3Z+eNAmseBaYhbP+ceKnaEYLZv+Q8d43THMOZFsOxMVw59O3eUeXYNU5zDCcuh43BdZW3lPXxjgRY1AC8zdpYo82Il7ErvtOWO6JrY1lyt8U=
*/