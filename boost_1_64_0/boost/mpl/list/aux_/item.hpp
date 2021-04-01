
#ifndef BOOST_MPL_LIST_AUX_NODE_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_NODE_HPP_INCLUDED

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

#include <boost/mpl/long.hpp>
#include <boost/mpl/list/aux_/tag.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

namespace boost { namespace mpl {

template<
      typename Size
    , typename T
    , typename Next
    >
struct l_item
{
// agurt, 17/jul/03: to facilitate the deficient 'is_sequence' implementation 
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
    typedef int begin;
#endif
    typedef aux::list_tag tag;
    typedef l_item type;

    typedef Size size;
    typedef T item;
    typedef Next next;
};

struct l_end
{
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
    typedef int begin;
#endif
    typedef aux::list_tag tag;
    typedef l_end type;
    typedef long_<0> size;
};

}}

#endif // BOOST_MPL_LIST_AUX_NODE_HPP_INCLUDED

/* item.hpp
Jj1GH5IUJmdBTyL2dEociuJKMQkV0l3+ERBYyimNTYH0i7CN8M2WOUUu+8oz0SZjPsmuOlXRDipPzJ64doMO2dRFxrJ9wBgNsCp5gMG20F9vDvQy1wXtAUC5aTfty27GEYTZg/ZAsyN3C7Ib6xdxhakV7+W2/or2863/0OItMQCROKDWYt29H9aHGPDRjGpVkyYK6V9HGoUn0ogqHGJyy9v3QnqzGUChW+V/0JrQABFHirK6KC2dMQhzogGZCNOGuu/E/r5qFHPDfAxRJmiq8PPhIg+SnHBAkQtBH5PxKqAOxIPQ/TvT5gVCqADzyeCHLV2Yfdm9cFL1aJICk7WU+t6DArWg5GFq0s4frAm7hnMq/2mZd7Xk7tSaY/v2A87ApexuKWM/RdO4kNzAWZ4hUCiKzqDrXPSUWQdg3HwmPUt6ZfGIlNGm69L/ubqMtt+Suhkr//CH+KNCJ6Ef40/vXrunSmeTJoKNauk9n/C7cBNHJy79v0iQkcV6sKli+yLBYeyz5nUPEYjhzHe6MfcrWU6NQG5o+P7gFNC847CKbjmgQJxI9XwEHixcVw==
*/