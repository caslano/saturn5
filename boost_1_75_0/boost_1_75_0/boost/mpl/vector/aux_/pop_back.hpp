
#ifndef BOOST_MPL_VECTOR_AUX_POP_BACK_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_POP_BACK_HPP_INCLUDED

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

#include <boost/mpl/pop_back_fwd.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   include <boost/mpl/vector/aux_/item.hpp>
#   include <boost/mpl/vector/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct pop_back_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
    {
        typedef v_mask<Vector,0> type;
    };
};

}}

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#endif // BOOST_MPL_VECTOR_AUX_POP_BACK_HPP_INCLUDED

/* pop_back.hpp
/RRehpaxckXpqkNUCz5k6+nkXIwsOMDWjgIHgKQdL6H/lewxGsVXaRQDB7C+JdDOGS9hMNTd68jfbW22kJqcAS9Opb4FDiiOZdpLlHAJ0PwOi/ZyhvYSZWdiILz84UX1pYu9zGy2ZPBmFcfsdZbk9R7CAQazYLwiJ6hAG9KT7+fMJG08d85VqCn23UFL2Yrj00f5UqD86O3wiJFb+W2MTupub2/TgOo3971RD/vwYTQT2jSomQoFLfyjCiqmIG4rewHDhQYNojdCazVCuJ/RomFW6t/ZTO/I37MppPK0mBiUFwoW5u5F9XleOi6KRM3vshKh3+CKCTy/wGKm31PFGMYI7xEja/KsywBDNk/DIDat2D3HCsO09nHEZyhfK3Cpp8HMCnw1x0pTcEfocYZzkLkLo5m1B1l0GXXrxUcwnCxD4muqhSnGJo9hee/HTNLRlbT5SjeALLXEh4W3tdPTiNbXQjpa1SCxb1PDagoeaR9WQ6ZiM3TiDSS94sfrOHbJZcywSzN+ZtCbH/jEgF0rChwVu++ZGHaXsxKhi3wYodwif2Bm2B3mKisPnSbGgm4xchNDX29mJ5z3KAZZQDW+aKb0o4auWx9m6FqVjC5aqW7W0LX+h8zkbWqErI8ihKz0Wha3xfZy8f0vyzVMFfqlt3GbE+5jESNDAcx9YRs2bYGm30DKTixBCiwA8NJQHoO+dPz4R1xq28HNXxdN
*/