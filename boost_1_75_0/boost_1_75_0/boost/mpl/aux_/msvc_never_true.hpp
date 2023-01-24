
#ifndef BOOST_MPL_AUX_MSVC_NEVER_TRUE_HPP_INCLUDED
#define BOOST_MPL_AUX_MSVC_NEVER_TRUE_HPP_INCLUDED

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

namespace boost { namespace mpl { namespace aux {

template< typename T >
struct msvc_never_true
{
    enum { value = false };
};

}}}

#endif // BOOST_MSVC

#endif // BOOST_MPL_AUX_MSVC_NEVER_TRUE_HPP_INCLUDED

/* msvc_never_true.hpp
bc1M4Y2DRJs6/9bmDr3ISaZnHZYrOmennvzgk/4jaWeGKdByZid6skFfXp6J7KljUhXolviQth7E3b2dyhlVWoW5ntlQOZRw7ET/bug2njuUe7/L8NTPebvZlxArXTf2MeCyDvmnaUOAIGwYug+MSz8lrpTwaVnq0g6wjjW6LPVdLis/OHEcaGOoiZFwO9Rt3luacmQHC2/zwn+2M4UqnSbwCpbxRKBsNq12BT+Xoq7uKsBffe5iqwvTag8HxJIlok+IpyFnA7jtmJupRRMgzSsKFi7q2XdG/Vk7+3LuwzrVjkkp0wED4Ec7OA2loIQJOczumiy1oW/z/vNP7Hfts0wtd2EnYVmTBz9GkWIszKLr34GcsnkL+xc7Zz7ldB+Gy+Jaauum/ry7TGWAUYnauiqm79umL/VYOyw2lKKKQZwm6YxeHtUFT3cF10OAjSUx1ylQQJPkvfwSaNgv7kf0g/X1aprpC3Vxw9zXX3ZhJ35n9VtRUZizRVP/+jkaf6ITK0ZjOJfnhWq97EtAT4Pr06Tq4Qd9Tm+vr6ebqboqEjaXS4TZbD3FQRqXO4td6dUnOB7IhA77oVlYN9YBf2HKcYvvjraSVLBcSSkoRnps2fisOnXz95UTENcB6fAPLsiVNjR/xakvy0tos7CDLBcbviwMszwejWuiAYz6Fi+Y/IWKw+D/u3MlDbVTiFR49qws7v91rj79L9zBzcUr
*/