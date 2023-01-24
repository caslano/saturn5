
#ifndef BOOST_MPL_MAP_AUX_CONTAINS_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_CONTAINS_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/contains_fwd.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/map/aux_/at_impl.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

template<>
struct contains_impl< aux::map_tag >
{
    template< typename Map, typename Pair > struct apply
        : is_same< 
              typename at_impl<aux::map_tag>::apply<
                  Map
                , typename Pair::first
                >::type
            , typename Pair::second
            >
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_CONTAINS_IMPL_HPP_INCLUDED

/* contains_impl.hpp
4cLXOlTD+/nf3YaHjPvk4NXRo/sJVFhfgjl5mtCCmpvHytQcNpNEWSPbiEsInJ02zeQ/eDBIjNc1O/Ka9FTnX3BnVGs8BEdPYl/edNMe6BQVAc6GU5ZG3eEWfCUCvRrwo3wJDcFaQ88vDP0u7/tdYuQYYjU6cd8t2z8u8pHOTVlyBta59nhIekqnjg7gywD/NIVOsejFW25rojShrupAsyU++Yy0rbj8K14IpKN+k7NCPjjijrWUHOxbt8FZacy2HmxH2ScfLI2e16YmcY+fbAJzScUaBqjt9TqicVoUw1Ra9E0Tb+RhoMynZVoNJqPOs9kBSIpS9B+ScLP3tdkz0nMcbr4Gde11LwtAt+v4VhbhOVJzbkYrp1tWUn+oH63+9U9u73KO8c2GFQTn8K3tOqd9IdapbxknOpdxUtHmJjyfRDpbtZTzWxZTuPA0fPVyeLXkBn4DN4sVnQ2ZKy6gTf0BFa1dk07U8dKQeBQ6hqia9i6aRSM+iM5q5HCeiHlYd5Ivhtv5aQFP7AleAhf7h01P+O2AJ7qa6qR7LZVzgaCjlVAtyZ3+VMNk0IMT+728Z0Ro9bv2Pko3QThBHZ7HfvmjelzDEO/h+vYRQRn+5aiCnJVdfEUfEjk6T3dSjWNXUdIqnwD0bRz/2q50GkX9pzH0mU6a7gLKsoErpsRpH6HWY+/2dsl7Z0GkfLVNhCfk5py3d5VMZfkkJgh2
*/