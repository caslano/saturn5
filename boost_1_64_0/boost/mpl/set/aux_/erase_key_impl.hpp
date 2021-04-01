
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
58HAsfv78QXznE4udDszFrcpkMv2McMi6Sl/ugRvKl0obJnf6DBh8huuYC6xT4PxMqfHME5Oshu3mfyq5nIC1R3bO5gkoYgeP7gnv/VbkSIVZSFoy1bY3eOKjixg5sVbSX/KPrACm1/YK7F4L6ZP323Avch8DKzeyuw69gNsWVKU0RkI7pju6y5FytNweKmk99TUFaKGG0e5F+GxNrnOT+NeAbkv9bL5Y8C0ua93NWhmDclCu9CzweoFgSbdN/HUPSQVIAnRHtLKFAo9r0I0sX9pUrAnTXxVuKtvo53FGqVnJn6NRnW28rG0YA6Q9pJ5waZaCGutAVrje4upr3s/rvkQ1iljlK7lBb81XE8zNa1yHXVXzvVNJitQg8kJrRQdAT3N+Sd4SeAEQNs9SgGOIUnVVspAIMSSynfkdXWe1SogPlKw6TrMAYRI6awh7m+qWgrf3VaA7VDaRlSjcygqplSgS4cOsPSNDHxgM7TTF/w3G44bAabkGhpeshRoMLZ8n822ZpOXmloZLtJoKo8EWWLtz7j7ruNcYKpNEZjjyIjp0wLLtkUzWZtaRQ==
*/