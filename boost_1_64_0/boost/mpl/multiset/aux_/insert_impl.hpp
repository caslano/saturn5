
#ifndef BOOST_MPL_MULTISET_AUX_INSERT_IMPL_HPP_INCLUDED
#define BOOST_MPL_MULTISET_AUX_INSERT_IMPL_HPP_INCLUDED

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

#include <boost/mpl/multiset/aux_/item.hpp>
#include <boost/mpl/multiset/aux_/tag.hpp>
#include <boost/mpl/insert_fwd.hpp>

namespace boost { namespace mpl {

template<>
struct insert_impl< aux::multiset_tag >
{
    template< typename Set, typename Key, typename unused_ > struct apply
    {
        typedef ms_item<Key,Set> type;
    };
};

}}

#endif // BOOST_MPL_MULTISET_AUX_INSERT_IMPL_HPP_INCLUDED

/* insert_impl.hpp
PFG9BsBWk938mtVwmy2fJ4gPqmM7mPtqUNQ5kVcIn1zo0e0k9DzPHXjpdRSEhNF6fd3pb6rNmsjjCNXwi3NaukB9YH3ndTJmAySNwddy9HNJtfM2dDI7jKWGMQvjEZrwJzhcSeBuD9XH1rDKx8C8V/n+YZN2QlL+8Tb9ZIZD7EcWSJRG/G5Ag9BH5DtUrjtw85UMntbrupHNiELq+4IoX5kpWuyfXHwDigTee8glgJYz6+1W0gkj6mLSnAyv+Eh9AivFXSFs8DJnzCyRSahF5glYRwHiLQCvMD4OEMRjxYFhsJxmgTq5BrBwNgeI6kIjmDgFPK58KRmi22rtb93bKhLR1PodkNLnQCd+Gs+PdFVgw8nFkO6gQNuTEH999rwOmM/eH6EwGBRRS+8yVJjkFtShKw3Jsy2n0m41yVq7XMNwja2gEAtqBEGF9Mr00bAFU6NkRugm6cbfOGFCQYdc3lSvRl18A5s2Yx6bZWolz+Po6uyXZDSKRqFyD5LOytIeyVpHuZtl/ayPT6FvWQ1vcyXpwzEYfdGGSqR4drltXvv1hpvYIotshSH0qw==
*/