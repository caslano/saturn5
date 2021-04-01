
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
PJkNqOqMWmEqoMcUVidKzbxu2r/0fZ4rcirqx4ErvYqhF0c1jCYzsLKxgrM6GjleJVE+fg+Kupibtc/n5IFkJdNvGI3oFXXb9pp9mx8NHGc3rFYYg8x4NHIIWEKpMOMTWR5bo5/S/2ArcU8H05pqd7HDtiyx+dvRldHLZBR2O36Epbd+aypSzBJzTaLtMeROEJvfHlrBpV6ZJbQ1xjKdCJrk73nBVLosbB2t2mziB3cxcqIrEPMgLHwX1nzEA65OiPKEnQXLkPuVWFXW8FG1JYMICrmiImbexdDnCuyReR4LpPtyC8w6l5BWGrJMSfv3JPVloQjx9M/jzUz3hhoERkNj0Ed4tg1siqKpXnPLj25AWT/JXz50+pLqXIGrDymJWmvzYRpZnPuCU9WKsfb6EgtyV/NL/3ztKu4S83jOZJyALGd+y53QHRhDofMj4SWoibl7TrLs+p+0rYYkAlVhP0KwXkP6z6wBzj+/9aJQXY4yZ5FmoxnJXgnqGrjANipe5fW2/8rIrf7+xUw+anIEnvNtAzd8BiRCjPlOF0+QexJCZuOf1kMA9Q/+/Q==
*/