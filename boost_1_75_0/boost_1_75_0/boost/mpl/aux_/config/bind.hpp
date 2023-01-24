
#ifndef BOOST_MPL_AUX_CONFIG_BIND_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_BIND_HPP_INCLUDED

// Copyright David Abrahams 2002
// Copyright Aleksey Gurtovoy 2002-2004
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

#if    !defined(BOOST_MPL_CFG_NO_BIND_TEMPLATE) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && (   BOOST_WORKAROUND(BOOST_MSVC, <= 1300) \
        || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610)) \
        )

#   define BOOST_MPL_CFG_NO_BIND_TEMPLATE

#endif

//#define BOOST_MPL_CFG_NO_UNNAMED_PLACEHOLDER_SUPPORT

#endif // BOOST_MPL_AUX_CONFIG_BIND_HPP_INCLUDED

/* bind.hpp
lbLh1D5LqSCujwFX6Y83oqS7MXO8lHFuE9QSbwcudUtJvTUDi+YMHncbnZSW1zzDI4uFSYqIbnvE5+bUqDF7ve1qt6UO+1yjHYagOjF+LoLQh8wgwYG7ZZKbrBBBi7NSS3/6vWIZj+k1V+yiAxGS4qfDV24zIenlpNPV4RTFslMaZ725eaIFGsnFogRFsodJMMZHPBilDf3dgfHXS+KZw3rXbyKycdMRYsdgNf6kLrG4WbyCOTnVGY2tsdmHO5no67T40+oark8hRvtjMLIu+2LWi/HqgnlIHtpIK7Eez4fieyE/5BmuOecliyUqzw1vL0QfsDXc16DRptilp7vofMpD/OG89pijn+ZFjj3/1mKLc0J0+u4w9xANhgF/A2fu4pktr0E9byV05D7k7V3BPpSFOeY55fyFkA4oecmDHJagOI0aTMlzN3Dh+ekETZ5uPH58ZB9+VJQSo27LbDGf0K9PTd4N3ZViq8xuKHZBUG3iNTMtIeBdBHthshOKHNe1Nrw6panefhIq8uwwY4/+xuUuheQ+HXW2Jew1tuBqlDokcpBdug17b0HBnz4tZaTQj6WqLAzFrR2+1P4IHqgl7Cp26fMUAemXfCo1HBylJZ+0ELtUUomxU919VV25gb2s0GzpTDwc/VMG4ICvOeWyiHtXaDdTIGJXmNLQlwML+mImMLQtM5yqSC5HzFhajaMcvD7+bZVp6LX2cMIY
*/