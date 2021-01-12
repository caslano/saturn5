
#ifndef BOOST_MPL_LIST_AUX_EMPTY_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_EMPTY_HPP_INCLUDED

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

#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct empty_impl< aux::list_tag >
{
    template< typename List > struct apply
        : not_<typename List::size>
    {
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_EMPTY_HPP_INCLUDED

/* empty.hpp
4Oknl44af72t97hu68GITOOe50z9bWGGMNsNIS+6QkwRxdY3x5kHWOPaRplCfmi+PcJqzjQbYtJDtg4wjYtJe8ZjjkjjieFyyzBr9OuW2rRe48xvGiN6RaxdXjMibHNNeNpAU5+08yExP3LGD40+c9hS0z/OZKiN6FNiaTfobzDEBNUjtwfUJK/y/tQ+qDb5du93NAJqlB/z1yhXffJ41ShPh4KAOuXVqlW+FppUr7zzP9Qs
*/