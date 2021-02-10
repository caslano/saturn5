
#ifndef BOOST_MPL_AUX_RANGE_C_FRONT_HPP_INCLUDED
#define BOOST_MPL_AUX_RANGE_C_FRONT_HPP_INCLUDED

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

#include <boost/mpl/front_fwd.hpp>
#include <boost/mpl/aux_/range_c/tag.hpp>

namespace boost { namespace mpl {

template<>
struct front_impl< aux::half_open_range_tag >
{
    template< typename Range > struct apply
    {
        typedef typename Range::start type;
    };
};

}}

#endif // BOOST_MPL_AUX_RANGE_C_FRONT_HPP_INCLUDED

/* front.hpp
mmaTZR42Z41c7O+/Jf9gMsiUaDFkBlrZYqetAxSm6QHVQOBVQokuxEcePLhAVui2FaoMmlLON06pc84u0w3PdnnxKefhrEdcVskGwbsfjhp9zb1JkG1370ZzltcUBf2GAyujW6CFEMTgF5+kVTaGTvyMRlZ9gIvKoQFX41AlqIWFBaKCka21G7HsdsD6NDoju04YIrH82/TJ64uYfo+ns68T/jTGX5xoFnqpSmH6w+fJnoUGTqrvWueYGtNRYEN9KcKwJdU1iIW+RTDY0mIh2YFFT+GH3CGF3IMuqPwGVYG+lORNbCsNA5FnoTpb6SF7DyDKvPFNNBy30GUPRehmuwV3JAA9zau9SbLzGg4PYT9+OLhBa1nWGe104dvLv0nANwGsJi9ip9RgKfzWKhF7VxTY0daETyKWG6FsRe+ZE1XoklTSXNVLdYPlr5PVLhsnfaJ4pU079d1wAP+U5oid3HfU1SkkcTz1EUq1RD+gBen8e9nXKo6lpZmRYfZ/khC6vJLYlMnIk5bLtu1flHdn4I3Y3iP5LPH2Cx7xZnQwzODq0Xpe//iG6xohVRC1O4uenujnNHqVEYv9LePrfsr44xzz9aftB1BLAwQKAAAACAAtZ0pS5mveJBcCAACgBAAAHgAJAGN1cmwtbWFz
*/