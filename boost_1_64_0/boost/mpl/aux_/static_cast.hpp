
#ifndef BOOST_MPL_AUX_STATIC_CAST_HPP_INCLUDED
#define BOOST_MPL_AUX_STATIC_CAST_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/workaround.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x561)) \
 || BOOST_WORKAROUND(__GNUC__, < 3) \
 || BOOST_WORKAROUND(__MWERKS__, <= 0x3001)
#   define BOOST_MPL_AUX_STATIC_CAST(T, expr) (T)(expr)
#else
#   define BOOST_MPL_AUX_STATIC_CAST(T, expr) static_cast<T>(expr)
#endif

#endif // BOOST_MPL_AUX_STATIC_CAST_HPP_INCLUDED

/* static_cast.hpp
KfdXAo2IoQeq7swNvO+zvTjf99H3POUuLIFu0me4Jx/XAe2Z1ivOmWtyQl+c1pv/ymiA52bT1ec6Q2xn5j0++zwhqgRLzfJaf/5lxqbFe248EtkEnzew7l3jFL7D6sbSvKluqh4ENh8y0O6hX9pjsPTAfjFcy91V3yNtrvJUKNDMv04cXwZdVq1UNV/OPMlRVg7P5radICWixAvrmQn0W/iiRsFGDUZ6fQ9c1pt9c69khBJr2AqMBmkjIbpaH39nY1cih9nAMNLhfaURvLPHTxoeCLlG3UdorufNX8C6Xhe4SssXmUhmDTUFuvpDMlryX/U1IGpMqYrrMeNitpbaRBq/XbS4AXVPlXQEvO6gPM/TuhcrqFmzx1lsrXuB03MLq2SLyLfVHSOkuaJvg5QT6AuKdZcHWs0Gqr3TU2/63H0jQrzZmt4SQySKoL8C4I1AXizaYsEslaah+Owu/uhhk97sNZ8BP32tXsZzn6twF8eunY54bRtbzcfdBUEinarRHQQj8ubSpKqoXMm9OtiajltRZ5Md15ImjA8GftK3wgdagklnzxRIc2lUwg==
*/