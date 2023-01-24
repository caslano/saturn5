
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
s9HeLxTeyz8ztlDEVrCZDJAC6iRz4W/6KddiX98zp0hfAommH/mjCP44IfzjK7gne0s68lhABqf2GCTJcbysSFUCziQJpAxV7ZXfLg8qpzIxCoQjddIkfO9FBXw85pi0RfPh3XIBpwpq5t8yxmuupgoeTPFZ2aprr3r+ISx7cqjl9ussm3f182VuwIgQeOrzzjBoSnGnlLzv0/vLo7nft7QFUNK9JbniiNZ7N3HGfBvISLSHBA6zlK3VyXKiApvAlIP+G/VvWeHnWgRgN+H5nw6A9t5Eynq/WzdnMr5IWRR9Q7bOBldpcFPJGTFc7/ATceHcyTRW4KetTR99z8HtRMKfcFlJEIx6KPpsqpljs/yn8oGQQdHUEw91FOWZ2gxT5+Gzfk7XVWxZ0yRd9qXo0rHWYI3G7/e0I2JoXQ2Ja/LbA81ClzLi4qdxWAmccVxxRIpnHMmQQIIR9hSLMmOGl4rZs0aNK8O0V/2LYd2DIuEt8sT4OnLZIbL2H5G0zkX7rVJZYRPvGWkQWuegVl2aOngDhqUou2HXiiajGsKJP/dX6clPRUEFQen+h72xSRSmabooogC5PK47qSw7cyP6O9OsjLFuLStctEsc0/x7hO+dezPjadPfWAiswGRyLIEuiO89uQwndExMj571eUrAm+L30EUqgKHS2bL/rV28PV1EDORFfEdHcRNFVOoUc4dbwwsln8kj/1pMwwu1
*/