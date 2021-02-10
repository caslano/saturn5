
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
+DSqvtV+XIf0tk1mh/4+O/bx2/0DUEsDBAoAAAAIAC1nSlI6hAu6EQEAALYBAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0ODYwVVQFAAG2SCRgVZE9a8MwEIb3A/+HIyHQDkZDtiAMwRiaobUS2aWrap+JqWMZSUmbf19ZShM66Q6e94MTd2RdoyxlwPux0/75ouu3Nq3NQJRiDflAymBFPw7eylJAXsuqfD0U+7qQFXD2wDmLDrCEJUoyFzKp7VsCbmgarjNwGwKRDz2N7kY0YfGIDboMJj2tveBvRT6qE8VKOPfAp39Fnj3BIoK80aeTGttosmFs9VLKaic2q1ktykOF6RnP3npjqTHkMP2InunOR97Vfry1Cn3fyfTdFVvlFKrOkUF3JJzvh0dl8ZNoxIU9arcAfgmst5iMdrrRQwb5VmwTqGVxCNEJiK2UGAsk4bQJ7Otdlfjch4qzuxV7fNUvUEsDBAoAAAAIAC1nSlI0b1XSdAEAAGkCAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0ODYxVVQFAAG2SCRgVVLfS+swFH4/0P/h4BAUHMVtL3eEwqiTO7iyurbqa0zObLFrSpKq++9N0tHtPqVpvh/n+xJmyVjBDSXA
*/