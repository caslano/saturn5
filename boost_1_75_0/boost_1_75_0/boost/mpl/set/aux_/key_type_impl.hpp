
#ifndef BOOST_MPL_SET_AUX_KEY_TYPE_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_KEY_TYPE_IMPL_HPP_INCLUDED

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

#include <boost/mpl/key_type_fwd.hpp>
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct key_type_impl< aux::set_tag >
{
    template< typename Set, typename T > struct apply
    {
        typedef T type;
    };
};

}}

#endif // BOOST_MPL_SET_AUX_KEY_TYPE_IMPL_HPP_INCLUDED

/* key_type_impl.hpp
IJtL1brtKDMTC6Jl8myfcclLJ8Xb5DXHyzX5wiF158TwICgeyulIQg6lpO2a4LmUsqNKq428+aAm50wXv01pdmxY/b5oT9Gd+ZyUZGfj/SrGyYuf+eONxP6VFoJU78kY6wvmY/Tp+x6LPvmxElHj9/Yh16YJdYo5WjpYm0gKflP1+ohBVSu7i5JxrcvpjVIB1oMyqebJKnbyPGk1X7SXhDJuELxF64JXVlYO6uxcukkHV2TSe+//gr/JovqSqFYSYDNh7zLCdjNpmyh4qf7Tg3GIrUw8UxxTV9CaUS/J+1Lu2EaCoK1adfeKKYE/Ugt175oZbgE11UZQl9ZRaLl0JJKHx+HgLvahgMO1BN+vrKPRxmxtfsoh/kE/xpCrx2K+H1pgjroBgbqJEga3ZxojBq/5gdpYG8szzF9sjJnMMU9a5Lg03sBh1LIdKR3pyaYFUj4Rj8Te4OSCiGpwSy2cy/K78v6zObxFFLBFj+EdPFHn9F+dcC1VGmj6B4AbaNlWGAZkBM3hzdHo8LLJR6hTvLyOf7sIo55IS0jICBwOWZN1IN0o0rhVgSgw7Bfj4Dl3sN68+mZCuoixlWw6Hnsu1wj/HCfmWIwDHPWX+7RskaOH1Cm23yE5peXFLu3FDb/oc4chsdwiP4OMZLR7l7khYF/k49++Se7wNu8vhn7C0mOo8aioichoHzSqD6pwLVuj4TiZt4/SO11okVs3
*/