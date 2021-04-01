
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
DCYHTizCjXiOMr/Hdm+p9AGr15oZHXSwVZ/095JyaW/6L7fQWD2RQWcjAhjgRRFU+7O0gME/78q92yv5Kpwe/af2AJg7p96qdJoPr/Kz/b0Qwx2m8z3HKWZ6nfVv1QXmhhxYAroyqiIKZG17ql8W2FcGsUXXGSwpQmuxjBadbgbfC32KGJw31h1AmpgA/K2wQyxbEVP0EwDAeC/W1O9+LvJUk3U7elkWS6mL3oo5vflGgqNflnOpJFTlI7Libugf219Ipdz9QOnGr0p/wQn2pmr3LSmT9du2EUmBX61YAE04Q3jjX3ay3LRQA4jZ49wTHipVah2PF86mwFGfM3MV4H0yIBRUUHF8FqL9mT3R7pXtFcHhYmjyR6+ZSQl73uixznSbLfqrP4hLSRfNaEN/XcF19wQIgR17JHLfVJsXZqTGkBVhoKmLLlZ3YD14/1rOSsjhMcF5pJsPsiDm48LmJMhiwsaYmFClxuH1qUQ8eIypbab9khcWXp3XkuNoM/AFKTaLADzC1CxSxdlcTxFTdxKHc5z/HHtocjgQaLmtXjiD8d2zXUByIFLo2A==
*/