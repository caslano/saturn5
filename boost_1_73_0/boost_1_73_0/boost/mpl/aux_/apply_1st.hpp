
#ifndef BOOST_MPL_AUX_APPLY_1ST_HPP_INCLUDED
#define BOOST_MPL_AUX_APPLY_1ST_HPP_INCLUDED

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

#include <boost/mpl/apply.hpp>

namespace boost { namespace mpl { namespace aux {

struct apply_1st
{
    template< typename Pair, typename T > struct apply
        : apply2<
              typename Pair::first
            , typename Pair::second
            , T
            >
    {
    };
};

}}}

#endif // BOOST_MPL_AUX_APPLY_1ST_HPP_INCLUDED

/* apply_1st.hpp
sfCYzogp2nRfqHYMstSik8zaLsFIfsWO5KfdSIajIUP6krYOc3o5JulZ5TF/yi5ncjbZRDYGkb0sYLuhY8ei4NsnB9gGGVWMV0k6XjC8S46uBg0pqRGDdmMizcDBUmKOKeghThrHEFySbqayZmwwA4w3w2s8C/lfCoyHo5wZUdsF+8FTJnrUMnTOOrICr/4IdkNY1ZO/0Ya7dC6+TDXJkW+7eWjMsXp0ySWMRvq651sgaHVseICbu6nvKNNN/Rw=
*/