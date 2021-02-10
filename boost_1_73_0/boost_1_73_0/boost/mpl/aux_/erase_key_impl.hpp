
#ifndef BOOST_MPL_AUX_ERASE_KEY_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_ERASE_KEY_IMPL_HPP_INCLUDED

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

#include <boost/mpl/erase_key_fwd.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>

namespace boost { namespace mpl {

template< typename Tag >
struct erase_key_impl
{
    template< typename Sequence, typename Key > struct apply;
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2, erase_key_impl)

}}

#endif // BOOST_MPL_AUX_ERASE_KEY_IMPL_HPP_INCLUDED

/* erase_key_impl.hpp
AAAAfAEAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyMDFVVAUAAbZIJGBNkEFrwzAMhe/+FaJlx86HHQbDBMbaQqGHsbHt7NlKY+bYxRJd8+8nJ2m7k/z0PksPGUZiZwkbZUJqs5QfHH5z8dSo7W6/Udvn3f7jbaOMvhlGT6xawjuWE5YVBY/KFDzGQWxv2VbqUue+4C8xYOIZd6MQgMYhjWpDlLa+SDDJ9pKsD0QhHaDaT1qPVUw9uWBc7nub/PRfgJidjV0m1nevX2uRB51yWuE5ENftFbvnM8uq61d5zmkk5SeW0A5Q44NtGQtwh1BPBZ0l+EZMsKAu80KZ08jKACwlF5e9RHp4lHn/tNFXSt8O/gdQSwMECgAAAAgALWdKUpZFKT2cBAAAwQoAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyMDEwVVQFAAG2SCRg5VZtTyM3EP6+Ev9hulfuALFxEpJA9jY5nYA7aKEgSK+VTtfK8XoTi429WjuEfOlv74w3r3C9qu3HSiiJx+NnHj/zYhInrRPcyn6QKJ0Z/HqQ85kpU9sPrqXjudIPwcVgcOs/4OP5IPhweXUeJGztl7DqaPAqeAX3snyUZWRVKoOklEU+R4eUOw7a
*/