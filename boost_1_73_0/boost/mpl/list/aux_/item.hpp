
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
7d1gGEC/YLDqt1sgUzXcXarhXnOVOu6HVMv9/FVquaernntBUE33lVeo694GXdfTv6D67kOD6rsXq777ItV4r1Od9+agWu/dcDqg5ntMUM33ItV9r4Ja1X5vCKj/3q4a8D1XqAEfH1AH3qZa8B6oVi34tQH14Hf5a8KrHrzxRvp1hZrwbtWFXx5QG74xoD58h+rDn75YI57NFerE21Unvkq14terVvz2oHrxx65QM94M8aod
*/