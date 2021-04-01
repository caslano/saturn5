
#ifndef BOOST_MPL_SET_AUX_CLEAR_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_CLEAR_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/set/aux_/set0.hpp>
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct clear_impl< aux::set_tag >
{
    template< typename Set > struct apply
    {
        typedef set0<> type;
    };
};

}}

#endif // BOOST_MPL_SET_AUX_CLEAR_IMPL_HPP_INCLUDED

/* clear_impl.hpp
7WWOsHBIieKZc/Lqu+H6MjUwPftj7SbZln3idyu8gj/X/pqckooXFJr9w8ROThxZ5HO2+2S9s1QgvIuPmM/hLUDdu+DJZMob53rVBD+orjWUAk/GrNHC+qEj9Ua3lDQcAUJQmJTcCWSZ7hdcl7YIPA1SRXb389/40az0TMkyu2hQvv609C6AbF7EPTRbzzbszknMMCw4KbWeyTtPeyjtGoJFqj41OoULkH/CwZVwUTBKcqwEaUw6TTfaQ2OHUCfrRytPzeXLRX8bjBYaxbqgoIBEN/yR21yq42KRCHQd3ld4ctfJUCEHlajtLfVVFC9pc82AFovw0SCQUzZXJ2YMjHOUijR+osBBznExfCNzkBZ4LsphsosVG+V7KCnIN4xdLCy+eQF0lsSwThnfTXaf0Jr/Pvl8YCze3ewDV5I5niZbhCLol6stYFFCgCXHXpjMoxrC0XKidfH6y04KpYF13C5F5eDwdq6VjZ/h0BI5cMR2AC5McIVcGPYEO3AcEIaz8mYiOBD1zruSzVlaBAD6MEXHBiI4pmP2FAgguhc+51biqL97TDWoiR2VZg==
*/