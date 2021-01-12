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
MnAHKZBJx+ycN9JIAI8C2Itlc4Nm+g0pbbrCUjsp7A3niBx2yywEdLDMgWn/oWUvHbHLHy4tM3nUvpGZ0rCPNGkOR1auuet071a2fhcTZatEBzUZc1xubhZwZvyjA/Y3AFtkVSp4Zdv3LwS7FMdT5HzE9nnHZgYXy+5/dJimlpswsfq86a6BDZo1m8Kg3DWGfvntOnh9qmqSopZReBGX13ruVpnp6X89mbAtxiZpsilem/wy
*/