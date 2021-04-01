
#ifndef BOOST_MPL_LIST_AUX_O1_SIZE_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_O1_SIZE_HPP_INCLUDED

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

#include <boost/mpl/O1_size_fwd.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct O1_size_impl< aux::list_tag >
{
    template< typename List > struct apply
        : List::size
    {
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_O1_SIZE_HPP_INCLUDED

/* O1_size.hpp
MKzYxAdXwSat1Q7CX940GFv8I5067YyptxDIComZPub4UVZ+E7CXYB2dOzqBIc2QiCWvYcB1f9cbCnkHpNqRzHxG8ZqPfD6bDuXqfnoti3e5oGShnjp1Aki0EuoOzumSEf7avw+kHdbJlLXHghqTzcfwUTgWN3JB1z5Q4sdUGG0cL7cpyAZJZ12H0N8/6XwB1zDPV6hkAgePVK3EHdqt9xBmTi18cOC7TF4JUxkbn72YWC9bzkTrJS4W+JOFDflHhngpGGuMmcW7jEvESjUDO4umzfBideqqTvj6on168QUG+B7dJMsx9xMnvVoK23FZC51IjGio0UfJ/eFvOpCtzgWE0CXjRPiTgdrB3fEA+JRjN8KUYe5gi8YONFd5OmFk9k09VN9m5nTHE+MSd+rYLWygue65ReRMk7IWMlXNVTlKXOABEvqh0bYIzNhtriNb9/iJwls8kfNYwmMm7Rg2UqV9eabKBj20K+qAkFEw1TsFE4yudtlJ90Mn/k9lg1aIj4iWKk3SrdX+WZx7NtIftrm5rBDeFQf7GgJeIL+riduC1KW3RxhuyDWRPA==
*/