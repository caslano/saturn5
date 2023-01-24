
#ifndef BOOST_MPL_MAP_AUX_ERASE_KEY_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_ERASE_KEY_IMPL_HPP_INCLUDED

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

#include <boost/mpl/erase_key_fwd.hpp>
#include <boost/mpl/map/aux_/has_key_impl.hpp>
#include <boost/mpl/map/aux_/item.hpp>
#include <boost/mpl/map/aux_/tag.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/base.hpp>
#include <boost/mpl/eval_if.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

template<>
struct erase_key_impl< aux::map_tag >
{
    template< 
          typename Map
        , typename Key
        > 
    struct apply
        : eval_if< 
              has_key_impl<aux::map_tag>::apply<Map,Key>
            , eval_if< 
                  is_same< Key,typename Map::key_ > 
                , base<Map>
                , identity< m_mask<Key,Map> >
                >
            , identity<Map>
            >
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_ERASE_KEY_IMPL_HPP_INCLUDED

/* erase_key_impl.hpp
Hl/IrIHog0cRCXC0RxMROCLWqwMR5jWASIUTtH+dWM27yxTL9gjHZi9gxYON7pMjFF7s27DN72gOge4pscsiK1Yt9RRPYemQnMehM99G/rzdWylpqGM4BEsVqxiMfNjCAoqKzh5arx+qL2V4q0N6e1aPQUmNYXCrN6eOyOAQj1VaLrsGWdYUb2qaJ3YNlGh2iR40PV7Wz3oA1hQ9bRUYWxx32r9B24GodpxyXR8Rq9J2QUv3lJRCkCtF8JPTa4lqzoIIORbhVJUd6hgFl/gvH6At29IcFXnxjfGK5OqvS8dzaxwcbwpk6PtjVR5q39yBqgGQW/tGdNpVAC1fjPG7xDZD5uxSwVhiF5XqtbU9JnkDXgcNjXEzR68hq/iYKi/GMS14m/m6/El2SxHAkb8u6DT/tvEs/xshzNFFxNiYk5IZULAASk+qzeeV/WhObvQeFANTZN82AuSpqb9mRjhL4Gtz+de59kPtKSEVnk03N0AYRwPr6ODL1S7dcGHzIrvsC+Nt+SVCYu/8DewqNTUij9zvHgTxC4958No/baG/2CSgd5FYJ6PCdf7w+F34u+/Bl0bhxiWWcvQAt6yvS3VzZwQcb+1MFLM/ISf2srWjERvp0RoQv4WqyDNaDo7JdUL42z8EQninSLm76w4dg248kTGGI24tFJFWT1fxvGowZSuozl1ofny7nNW4UXxbpeDvfQ//eO2cyzlDWjb/
*/