// Copyright (c) 2001 Ronald Garcia, Indiana University (garcia@osl.iu.edu)
// Andrew Lumsdaine, Indiana University (lums@osl.iu.edu).
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ARCHIVE_DETAIL_UTF8_CODECVT_FACET_HPP
#define BOOST_ARCHIVE_DETAIL_UTF8_CODECVT_FACET_HPP

#include <boost/config.hpp>

#ifdef BOOST_NO_STD_WSTREAMBUF
#error "wide char i/o not supported on this platform"
#endif

// use boost's utf8 codecvt facet
#include <boost/archive/detail/decl.hpp>
#define BOOST_UTF8_BEGIN_NAMESPACE \
     namespace boost { namespace archive { namespace detail {
#define BOOST_UTF8_DECL BOOST_ARCHIVE_DECL
#define BOOST_UTF8_END_NAMESPACE }}}

#include <boost/detail/utf8_codecvt_facet.hpp>

#undef BOOST_UTF8_END_NAMESPACE
#undef BOOST_UTF8_DECL
#undef BOOST_UTF8_BEGIN_NAMESPACE

#endif // BOOST_ARCHIVE_DETAIL_UTF8_CODECVT_FACET_HPP

/* utf8_codecvt_facet.hpp
YR1UUGb0NU5QnM7ezwEORpg5LATeGJSuNicp8Er3d+hmVjW+pptfGp3TYTdaAdZwT/TX4Zs3l4Tqh8bgzxgPCMdqcoj3M3ddkG3pUeoXv4xBlTT5tgFBl4Z2/hjde2e/fnlgv7L5NeRbyNwmYwqgrcSOen3/nBcVcseFiTB+EIGMwoHnn7G4URD97J2BT7d0ZEEHCSO7tBrEQQa+iQZ4vH+CZ1Ajhr56ucRS/cK1+3pu8cm7975HPTSp+0+4umQ12uehHkIfAmcuO2BVtoSAcmULnLtXjx9E2tReJOUOzz5NlDAMcaT7CEtMumFYjM9UmmD91kSSjHDDmDfBqiRfDCqESwO2ChlOwymRk9FHG1PERsnihC/hgwvG/Dm5uM4uOVyLpfTa1HobCp2e2ZkoPPEaD8AqQ/TvpTfuU2hx+I+UKrxqjJK+sbuk4+bmCMicXDLNSFe9w9nE/ItlbJnffdWYFjp9Ss4eI9f6bSDFMX48LwB3orwvK9zsYg8rbyDMaktKNt6bnYMmcQ6zoTCBqlNG3ee04HEtVy1eAb2HEHIHG7E/yMfN+9Fozw==
*/