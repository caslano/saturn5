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
SPp70e898i2n46/WewjDufCbhlvLJdM6ucDv0W09jNzhNPXjD5yLi32wRikn2ubxFZPAHje39F+SE+OY8JFOqCO3D8RI7zprffy5FzLZ8zJCpWiN70ajZtvd92Tou7ZrfLmD8b9F1m26XjAdu7Gg1KbbcK6NVl3z88s/fi/v/N9WW9sbQ/3FUatn3SOngtMYxod6YtP/e8slsSxEsYb1tO1nko8jMT4SNKz9bb8wRCvLXDh/Gbv6uxpaSq0Sjdc=
*/