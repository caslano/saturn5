// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_ENABLE_IF_STREAM_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_ENABLE_IF_STREAM_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/config.hpp>                // BOOST_NO_SFINAE.
#include <boost/utility/enable_if.hpp>                  
#include <boost/iostreams/traits_fwd.hpp>  // is_std_io.

#if !defined(BOOST_NO_SFINAE) && \
    !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x592))
# define BOOST_IOSTREAMS_ENABLE_IF_STREAM(T) \
    , typename boost::enable_if< boost::iostreams::is_std_io<T> >::type* = 0 \
    /**/
# define BOOST_IOSTREAMS_DISABLE_IF_STREAM(T) \
    , typename boost::disable_if< boost::iostreams::is_std_io<T> >::type* = 0 \
    /**/
#else 
# define BOOST_IOSTREAMS_ENABLE_IF_STREAM(T)
# define BOOST_IOSTREAMS_DISABLE_IF_STREAM(T)
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_ENABLE_IF_STREAM_HPP_INCLUDED

/* enable_if_stream.hpp
mIXk/GzVPqCK/DOCzimuTsarcJb+rrvnfxuCxueikXrrgPwZ0nkqUmJpdouOBol1Y82tBM9fNcni/te1RMCfYI+G1o1P2fe8dl19C+IRKBadnwZYjLtFF8/I3jDfYGJly41487P5ccC36k4OS+YtF7MAB6QI5b6Nhvt6uS2VDgqAjihOmExdcIQivoq2lwey+kLVorh+u/WJ2JyTyyfaNYygm3Op0+XfvPgN6r8CE45H9u6h4WRkJIl2rWblC/P83vhKzOxsTHyOFvl5hL++zGG8RzG+KYYMH7fKJVfOTWi3h4hfLFn0U2Ra+IXgpDlGeaUfphAm1jaHslFMUYNOy1SvBZs/d4JDKqbpuNSjy1c84MfnO7LHQcbJuxZU4Mdkk/7evETaxNyAJIu7o2Yc7Pp5VcAoDkxQTs8NiOmXLbXLyF0RptzQ8YRBATCUdztw3tuD23wv4GIrkpV4AYnqDIrReMOQkIAeN0QLoZobzirSZKgdH88Sm+upbUoHNsCPrdMC+aa0r3JMJyZDNfdkadEHOLCDM53iXTbJ0Hd/7SVF3I5OvV/1X3lCZw==
*/