
#ifndef BOOST_MPL_MAP_AUX_KEY_TYPE_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_KEY_TYPE_IMPL_HPP_INCLUDED

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
#include <boost/mpl/pair.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost {
namespace mpl {

template<>
struct key_type_impl< aux::map_tag >
{
    template< typename Map, typename T > struct apply
        : first<T>
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_KEY_TYPE_IMPL_HPP_INCLUDED

/* key_type_impl.hpp
c6wHWEHTPaCVL8dhd01fKxLxX10SgA7pXoNIWcx2Zcl6otywNQGXA7YYsh1Yk1h/G4h0dp2SSR17jddcPk4n3whXqjz4HPQ2eO7/TcmmQx25wf3Ymg4/I7PJlwQdO7YfZHi479SEK4Wy6ceBj26SKLWhwvpWyIiM22X4fPvn0R9OYnFwVbtaIHRpVQAkDMQwzLrYDvBHnqPUKce/CG0YjcZ9gnRnBofQUKejQu6oiO2gbgrvEdAwiYo/wh0jRPzv1ZsZQ41EIC8Fo64961qpjfcHb4+AixshPK+pSat+jGiOaHDrswBJlmRsie+OZ69c9TkXzWUcNefSrwgytoKSjZaxEUc+g6NFA6RZhngybjvG+lfyr8fpGJs3eflP27aP1FEo4xKxfhP1jHumVHJrVqg1f0HeSsRuLfPsBlpxefOqs0rFVUALwnGrYRd9MyKfRvpqGaxeDIav2xjoCgOxgZOieFyOn9D1yCUVYvMMUxx4XVvIkejQCBy1kLv0pr+suweh6LGyaaTq6Le7lo2nRg7NcQGZ8xHMKKUNC4gBzrL3oZPVjrk7FV9hww==
*/