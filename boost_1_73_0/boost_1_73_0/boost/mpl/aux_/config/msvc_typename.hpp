
#ifndef BOOST_MPL_AUX_CONFIG_MSVC_TYPENAME_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_MSVC_TYPENAME_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
#   define BOOST_MSVC_TYPENAME
#else
#   define BOOST_MSVC_TYPENAME typename
#endif

#endif // BOOST_MPL_AUX_CONFIG_MSVC_TYPENAME_HPP_INCLUDED

/* msvc_typename.hpp
TsBzcR8Mt5+8hRwmJiGGfRNFMPH+yVwFVB+cWZhKJd+L49ZKXB7wyenrxPUygl89aSXdSvRJk7SPobUqrltH2u6zZrW0D+Er4lLOZHLUCmwKo/lSHExstFvERjSI9/2Y4D0O4HuZyvGNDB2zWI7fz/jUwJKTTI6HlM+v8KcszsJvu8FvfNFnolYWCpOKQI7XEiYIKPTRhNeWYSifUtJRXsaj2Khj6mKCoxXKbbCtKB3ceCkycF+CdLD9XzG+/vo=
*/