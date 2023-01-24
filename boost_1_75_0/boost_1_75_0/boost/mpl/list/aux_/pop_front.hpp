
#ifndef BOOST_MPL_LIST_AUX_POP_FRONT_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_POP_FRONT_HPP_INCLUDED

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

#include <boost/mpl/pop_front_fwd.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct pop_front_impl< aux::list_tag >
{
    template< typename List > struct apply
    {
        typedef typename mpl::next<List>::type type;
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_POP_FRONT_HPP_INCLUDED

/* pop_front.hpp
SKhzw3QDf2iWShUCepQTkO9C+3zMKm50+uPeSfsDh4G/oAVY/eOpRvevXpUButkBwCNPHvIOz2PpAr/xGdF+tn0wfK3GdMKWE//ryM0+zgtla0XJ2JHjlpz0G3/BheALwtY7X0Lr97Ynb2nbsY1SDR9vj2qXkim3cAs9a/luuFFZwuzDWcLHk6aE2nyhRo6jR7dZikHTzks7zlCYN+se7OnLT4JlpHXUdSwBOFuUVriuOwoE9O1vxoz1iuWC159n3tkSdLWFLr8XQDlHcP/g1nou2YVlidAViGWJ8iryYQatGf4lyH3bKR+RB44U92+BN90Msisi/Kd3IXCbYefNuTON3h+F3wsgk6LEwkkHmfY5bVtthxwKRjzizpTdTn8SQhT4kI08FZHxt8A7KS/q48JwYFTfrQipTMdqNCUUIX7OnGsX3fE9ISpz1OD0btFhudsc6Q896UTxjJ94kRnX+1ejEayM6dFAKRxKRsH0yJiVBrNCn/iA4NEBlWgc1bPQ6BTC5tiyRFPAWK7n4cTJcrwgdoNJP7V7m12ZCSLRmlxeM/OaYKoVUA0Aa1iIT4mkDUNsCMnIPGbfI5IhIpP/szpkYyuHeCqaijIjcrBbfNDsc2ojyoWZdSGM3mb3p1Wc8Wd3BiIt8UtQ+1vRH4QNu6Z8RqR16nV7V7Su9AHfM5pzSDWbov5krxA9pua0Xanckvnji/OC3+DCaDpZ
*/