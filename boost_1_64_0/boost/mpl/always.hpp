
#ifndef BOOST_MPL_ALWAYS_HPP_INCLUDED
#define BOOST_MPL_ALWAYS_HPP_INCLUDED

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

#include <boost/mpl/aux_/preprocessor/default_params.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/arity_spec.hpp>

namespace boost { namespace mpl {

template< typename Value > struct always
{
    template<
        BOOST_MPL_PP_DEFAULT_PARAMS(BOOST_MPL_LIMIT_METAFUNCTION_ARITY, typename T, na)
        >
    struct apply
    {
        typedef Value type;
    };
};

BOOST_MPL_AUX_ARITY_SPEC(0, always)

}}

#endif // BOOST_MPL_ALWAYS_HPP_INCLUDED

/* always.hpp
bhbCN6j4dPctfwdprOf9Xw/L2bsAn4SlcVxIS3NIAju62uAsFWRhabEFa91dYnJLUQvO/uSKL+Kq2debNxbwTgowZbG0xGDS3Rncu4m2lDWg6/QNdaSYh5zMeCbUsiQTRpdkHcRY2C1l4YUHDdTQfXaHzyxYUIqhRCXdVfT86mzBzI/6L2L1CDfCz9mmi0XP7RS24BxX/c+dh8cy+VDJVnDDENZlxv19za5r6x613TzKlud1n7dLkQfpslyGpTRu/MZ6t4jvlk/ShtCif0wmaIlS8sJDtmKF12K3zIGVFgNa3o2yUsYlnaw6ICKKoXKAFNywQJyBb3xZ0gXixOwDBnQqIM+pvoPUny0hK2X9f3w8LKcWwFRTzSmo4iogNZiNAr59S1DI8SB1PpzV8a6MSlo81iYpyzABU/f0A8MszM5gv1SQfvG6wlOiNKm0VjVPm0NNbSWp2Hjt/DfIEDQ8CrgBipBvcVoF01L3XpgSli3qTWffn2+1riMHCTgynqasnfWgWLyVjVik+Hoym7l8A9ox6DSRE5swEpkPQWpgmO1ZjC0XuBrldp7TBA==
*/