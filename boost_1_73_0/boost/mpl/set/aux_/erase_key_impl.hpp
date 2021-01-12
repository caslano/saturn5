
#ifndef BOOST_MPL_SET_AUX_ERASE_KEY_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_ERASE_KEY_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2007
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

#include <boost/mpl/erase_key_fwd.hpp>
#include <boost/mpl/set/aux_/has_key_impl.hpp>
#include <boost/mpl/set/aux_/item.hpp>
#include <boost/mpl/set/aux_/tag.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/base.hpp>
#include <boost/mpl/eval_if.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

template<>
struct erase_key_impl< aux::set_tag >
{
    template< 
          typename Set
        , typename T
        > 
    struct apply
        : eval_if< 
              has_key_impl<aux::set_tag>::apply<Set,T>
            , eval_if< 
                  is_same< T,typename Set::item_type_ > 
                , base<Set>
                , identity< s_mask<T,typename Set::item_> >
                >
            , identity<Set>
            >
    {
    };
};

}}

#endif // BOOST_MPL_SET_AUX_ERASE_KEY_IMPL_HPP_INCLUDED

/* erase_key_impl.hpp
zrVBHEwHtmWleRAnktkxiioJbH6bn0YrR72NHqwyb7fsFN3Mak7Ln4ezxhSry8pYY1+Jwnab6Q76mnoaNc/eqxgFE1BR3dP7OTl8stEan2zP8mmTNMh/j+pKbSLekpgZ51+wPMzjxvlrRe/LKp8HlKiZqItScawTMNHPskd/tj2NML5/prLyQdsY0S9wvcAHgjFsDK4GxjK+rAN2jNQA17b5u4Zmjn8TZlG05f/3DOUYR4rJ
*/