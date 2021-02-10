
#ifndef BOOST_MPL_MAP_AUX_ERASE_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_ERASE_IMPL_HPP_INCLUDED

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

#include <boost/mpl/erase_fwd.hpp>
#include <boost/mpl/map/aux_/erase_key_impl.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct erase_impl< aux::map_tag >
{
    template< 
          typename Map
        , typename Pos
        , typename unused_
        > 
    struct apply
        : erase_key_impl<aux::map_tag>
            ::apply<Map,typename Pos::type::first>
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_ERASE_IMPL_HPP_INCLUDED

/* erase_impl.hpp
Z7j9p3RnWdrCwDJZVaLO27gFpePXOOVRshg3OUm85jA5wtEuWWjMFBqYfMJNF/84m99Yg2uELTtJp/+BqthdIBdGgNgZVGD2CM2Dwl5o2CLWMNR7aYaEnRxrIw5KGpnJ0iP+dDqDwE/8p2gZ8a9B05jDMn6J3pwQtEKufw+9kms8NGC84QMr1Ucyet1D+4/9BVBLAwQKAAAACAAtZ0pSRJ9OCjIBAADsAQAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDgxM1VUBQABtkgkYFWR0WrCMBSG7wO+w0ERtwupziFDQqErZSuo7do4tsvYHrGsbSSJTt9+adopXiU5fOc/XxKqUemMK3QJLeqdMMsPXn6FzJVLwpUXE79ELoHhWZMkWHurgPiblEWrJPjYBCkj1Lk1UKfNIAMygBTlCeVYFTkSKvFQXhqg21jCLwusdUdk9mAQZftcUlT8YBr+j0BrXmErBa0JVLwot+IMD3dKj4Z1WhhoJqqK13kbt3Cc4XuUsjBeDJucOEoYjI9wNEMWCjOJGsZfMOri5/M5vExnI2NxjTHbTtRe4RNlsbtAzjUHvtMoQe8RmkeFPVewRayhr/ZC9wk9WdZEHKTQIhOlS7zJZAq+F3uv4TJk372m8ATL6C1c
*/