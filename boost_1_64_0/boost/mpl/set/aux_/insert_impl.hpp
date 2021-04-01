
#ifndef BOOST_MPL_SET_AUX_INSERT_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_INSERT_IMPL_HPP_INCLUDED

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

#include <boost/mpl/insert_fwd.hpp>
#include <boost/mpl/set/aux_/has_key_impl.hpp>
#include <boost/mpl/set/aux_/item.hpp>
#include <boost/mpl/set/aux_/tag.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/base.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/aux_/na.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

namespace aux {
template<  typename Set, typename T > struct set_insert_impl
    : eval_if< 
          has_key_impl<aux::set_tag>::apply<Set,T>
        , identity<Set>
        , eval_if< 
              is_same< T,typename Set::last_masked_ > 
            , base<Set>
            , identity< s_item<T,typename Set::item_> >
            >
        >
{
};
}

template<>
struct insert_impl< aux::set_tag >
{
    template< 
          typename Set
        , typename PosOrKey
        , typename KeyOrNA
        > 
    struct apply
        : aux::set_insert_impl<
              Set
            , typename if_na<KeyOrNA,PosOrKey>::type
            >
    {
    };
};

}}

#endif // BOOST_MPL_SET_AUX_INSERT_IMPL_HPP_INCLUDED

/* insert_impl.hpp
69Ewsv6+QqrIIk5EyctbPnLlNdlFJfyvKnQjF8ndbuO3VJRFO3FLSZZs9aNSMJmXGc1MhUJ7MABjpw2ip58imd8yYClE4hbZO6LkBgwmXMcrB/iu2Fps68NlMw8vUCvZQN2gQe5D8yuWBU8Jr/k5NLubqhF3Pgmd+4Eeumxz+HkVFuVqG11vMxR/AJxzUR9qk2AbBDOOA8p9D5/uZdfOnL22jDIg5+XjK0f0SWaovCmbVN3Mw3sJc9rBldwArcRkFFBlEVkAdohUcHzQ/6aEN60NcM7W6Nto3CQg41lAEt/ZNBHkI++gDhal7Gi23JGO0fdkpm2l+P6GcXYK/4zyito5aWGCYk+5lNG3dO0ywu9GfmOm4EPugIOBrKklK391rjAKcng5uKRoddqJNaij5HUuU3keUw3R7v4kqkqLbMYzCl65YkuHo7/SjZJx+rInPKU/LOkaHPyMxw9/ZFjiAN4Z4r49kImXkkxdnGfTJCM/9ugdeVtIsgCJHUS4wD3BgOTOMUWs+rfDT1jZLQoetDSQncY9s3u5af38OZh+t05nTmj7490yfJXslA==
*/