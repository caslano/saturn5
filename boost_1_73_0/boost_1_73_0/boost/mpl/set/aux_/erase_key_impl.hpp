
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
2IBAnqqqEnU2cAaMzb52cbKNgllHFu32Cft4e0f/ghenFhhKNVkn/YC57eiu9/1DWuYtdu9CkVvSaAvCbo6wEAaPRDVOTKHsBPi173UUjVZWpaoMYb2KVh4c4s2+1/MgWsUxDqpeP2Lo7HjwfdgmXX5PJGcPOvYc219QSwMECgAAAAgALWdKUtm8qh8eAQAAxgEAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q4NThVVAUAAbZIJGBVkd9rgzAQx98P/B+OlsL2IHkog1KCIE5YYUPbaNlrptdVpkaStFv/+8XYtewpd/D5/uDCLRlbSUMR8KY/KPd80eVb6dpEkGf5EpKWpMaCfiw8p68pJKUosrddui1TUQBnd5yzyQHmMEdB+kw6NE1NwDUN7WUEroMnkrah3l6Jyi8OMV4XwaCGpRP8rch72dFUCcce2JEx8pPw4V+hR0eyCUVeqa6TfT2ZrRlbvGSi2OTrxeiSZ7uCrZ5WGJ7w5GLWhipNFsP3yT/cuPibgxuvDX33PenmcMFaWonyYEmjPRKOt8SjNPhB1OPMHJWdAT971lkMWllVqTaCJM7jAEqR7nx0AHksBE4FAn9mdM0C2JabInDZdyVnNzt2/7pfUEsDBAoAAAAIAC1nSlJ8
*/