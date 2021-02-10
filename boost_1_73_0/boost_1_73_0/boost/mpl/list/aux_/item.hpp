
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
cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDcxM1VUBQABtkgkYFVSW0vsMBB+H+h/GFx8XIOKCEsoHnp6cFFsbbIrnhep7ZQW22Zp4qX/3tl0L/rSJjPfZS6RjqwrckshzF75V6KpKtwG8fr8AmTTVyYE+UbjpxlKG8I/nUL6R60hi3UGKonu1BVEq+w+SfVLlDw8xJF+0QlIceRIMcnMYIaKhg8a5rYpCeRAm3bkfJm7PATbtO2Ihekd9Y5JU1SKHcrTo7bh5I5e+AtDrBcNoXIbsKZ4s1dM2wdR9nlHvnKsyBU1fjauxvl8M5ivES05dAYn2kIIzPtyj+Baeirc3BlWEZMMysJ0HYO8HRP4e0Zfebdp6YxT4vr88hcVF4vT20TpZbo45RrSJNNH873rAeEn6jHcwsGJj7te/RTWNDTViNsBYV45GtDVNG2tzi2+EvV4YmvjTkB+eCxLsKMzhWlDWKk44zZNP3bm3QbbfSrkNm5+tMHRp78BxKlaB6Cf0xiXAajl/5jfxWXgtz+dHldLHXCBR3kpDp7i+Ly+AVBLAwQKAAAACAAtZ0pSyCx0ztgBAACAAwAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDcxNFVUBQABtkgkYI1TUW+bQAx+
*/