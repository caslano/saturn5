
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
OpV7rJRPkJi2daAAFZ0EtqvDumPk23C8OWwLi0UZFXKFk4RQDRaKDU0pa4ZaTsEnDsk3KTu97PX5IW0+04iwtMbn/1UCCVoSWtAaEDIEcVTFKVblk9wvAXKNkkcjKTYv96YZlyrzkJ91bCQ7DsiilBTVu0fN1j+lYzoh0z+S2KKKlOnsrunAFQOlQ12mnxrIURjUnE5g8hPv9fF6G0itgJqgGI06M17kP6cCEl/+ZDS1IPJGxYdyImRZDtatVeh6abq24x4a1H5ATMLhqZ4ziTavELfHCo7iPJ3Sc2WgNtBhAkfg3oGep37aN/V0R6irVl7PhQQxOo12HH8JiRbZQqeSWQgvOdhVAQ29o60H9dd0LhOp8udfiRfeZAvYqzrPoufIDsMJ8E90NeICKbLGe4piy1NnekfwvhxsRJebxBhgasuyF9P/CAtxctP+qtqXYNL5y9gOknOHOyb/xo3ekmYZFyZCf85+WUfGc/I95oIWLwH3qCLN9Ij5CJ9UpS5G3k0dfvkzUHCsaewlPy/6ZEJtpxC0Y1zyf3j8Vao3/I4KnxpknHn/itADsA==
*/