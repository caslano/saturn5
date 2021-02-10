
#ifndef BOOST_MPL_AUX_NTTP_DECL_HPP_INCLUDED
#define BOOST_MPL_AUX_NTTP_DECL_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/nttp.hpp>

#if defined(BOOST_MPL_CFG_NTTP_BUG)

typedef bool        _mpl_nttp_bool;
typedef int         _mpl_nttp_int;
typedef unsigned    _mpl_nttp_unsigned;
typedef long        _mpl_nttp_long;

#   include <boost/preprocessor/cat.hpp>
#   define BOOST_MPL_AUX_NTTP_DECL(T, x) BOOST_PP_CAT(_mpl_nttp_,T) x /**/

#else

#   define BOOST_MPL_AUX_NTTP_DECL(T, x) T x /**/

#endif

#endif // BOOST_MPL_AUX_NTTP_DECL_HPP_INCLUDED

/* nttp_decl.hpp
xnNVPU0uwEw9i9yYpk8hkvpbuTYs1o9b1ocD/SJ2G83e0dA7oIXK5fisfaFXeW1Sd/457Zy/v7zi3fqoqMZqoaheXA5d9d23L1ErdLSW4qiXk0/a5aR34l872of7ENB+kYrr2j8EFfXvqajdoKKCseEWcy4uwj0HK6qb03uqTnJ9pagf5Ml9VNR/OxUfZgYPR8WG9/7YsY2vnc7R6dh4mxvotX+79knjm5dvktN3pz3cHDfGFS7zj05UJ/aHin1ueYrablYnjY/nfW1jKhq/fQ0eZgZPTw7EE2/2lDLl+aNLXvw7w39QSwMECgAAAAgALWdKUo299+3NBAAAWhcAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyMDI5VVQFAAG2SCRg5Vhtc+I2EP7uGf6DkptM764hxhjSC3WYMYS3FAgHBpJ+uRG2sN0Yi5NEOPLru7IBpyShlzakzcWTMZYtafd5dveRIkMQLmzMSVEx/HBM4eeaLOaUObyo1C2rE91QrWLFDyXMfRvhmfDidttqtuKmoSYDDTWe6x3qEXZDWJr7DlEMRqbBoqgoxl46jcxAEBZiQZDwCIJxhMETFisToRNP7hEMnzjC0ynBDPkhYoRPacgJR4IqJOQzRuKRyUQOJTz8
*/