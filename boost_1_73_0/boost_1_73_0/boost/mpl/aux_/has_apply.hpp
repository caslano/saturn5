
#ifndef BOOST_MPL_AUX_HAS_APPLY_HPP_INCLUDED
#define BOOST_MPL_AUX_HAS_APPLY_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/aux_/config/has_apply.hpp>

namespace boost { namespace mpl { namespace aux {
#if !defined(BOOST_MPL_CFG_NO_HAS_APPLY)
BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(has_apply, apply, false)
#else
template< typename T, typename fallback_ = false_ >
struct has_apply
    : fallback_
{
};
#endif
}}}

#endif // BOOST_MPL_AUX_HAS_APPLY_HPP_INCLUDED

/* has_apply.hpp
vcxM4+2bn+L4f5uVvcnIM3RGztEZOVdn5EbJyI2ecb0Y6xDskGCvC5bRqcB+1O5WSukXUqybBpKdAwNP3cynqGvHXgeD2b6QJ00DAahZsh07o5942ns48n2PlyiydtDvgGQpOqGS/ORAep+edWxLXKfLQTnQfGDO7zdo108UyeXnDNpVwyryBw3aBSN8Be/LxyH3oFtW6G9x+LYj68hijx0bumED70AogPFvDcXnHP2osC2Vx2dnEJ0aoEk+H4Y=
*/