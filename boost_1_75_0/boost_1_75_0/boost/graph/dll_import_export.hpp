//=======================================================================
// Copyright 2001 University of Notre Dame.
// Copyright 2003 Jeremy Siek
// Authors: Lie-Quan Lee, Jeremy Siek, and Douglas Gregor
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_DLL_IMPORT_EXPORT_HPP
#define BOOST_GRAPH_DLL_IMPORT_EXPORT_HPP

#include <boost/config.hpp>

#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_GRAPH_DYN_LINK)
#ifdef BOOST_GRAPH_SOURCE
#define BOOST_GRAPH_DECL BOOST_SYMBOL_EXPORT
#else
#define BOOST_GRAPH_DECL BOOST_SYMBOL_IMPORT
#endif // BOOST_GRAPH_SOURCE
#endif // DYN_LINK

#ifndef BOOST_GRAPH_DECL
#define BOOST_GRAPH_DECL
#endif

#endif // BOOST_GRAPH_DLL_IMPORT_EXPORT_HPP

/* dll_import_export.hpp
iUcIj454lzYhqBAEKE/avW6UXfKiSOoXt1P5G6sh4Jw0fnqOXtz9Usbx6MYFrBIYUhOBOFY6hwXq/qG0fJoPGQUO7GZJfZcuvcZCB+LB1QaC8dIVDR6fabopYBFaUTV5RxGH5SdKufvuw8xx/nqzSsIl0yOgvsSFbKTI6dF6WsWJUUquapaJW0MKt9mK0M8YQLBUhUinpkagUFvD20VoS5Nz/zt+FWpINVVNw4+Oi/33TCZHmdpKknDPZjznSjhXDy0QUw8FEVtoP8P+qWKGrbEblnH0c9PId/n3DMCqJWJ3hApgQI4fsAxaWxDxEAi48uQIuHIiFff+IvZkXkUY3bswrRQwnrG5d5QLKbXPMx8ORusOHfcCniBFiN7iFrykxqJwchwFXm7rOTZZQ33FQWll7S+CVoEQUXLcfmhWAqMPAFYvO/m6vo2uJhfyL28L6PSHoKbpOOWiDq+AonepguJdlcg/9IOhjx+LchSH2yzGpePkXmXsVjIMw6lptqRm2BC3wbsI3BfgSPSJN/HXIj3X7CoN56YaXWDvw+ypbBHEPt7H29RgDMOk/YK6+OmKPZHxK9vfBWmKToFF8WAGc5CUurq/x5L0Oz1i+s2SH/1eiTegiaVn4ll5WQXG8pIahc7PsmeM5cCaDQcHZmuefcI3z+cGsA6mN4anN0xH7W63y0vPw2PVN88FIc/VGJbDN8lubYHr3UxGj0/p
*/