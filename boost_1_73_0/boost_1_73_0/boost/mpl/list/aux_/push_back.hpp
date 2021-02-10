
#ifndef BOOST_MPL_LIST_AUX_PUSH_BACK_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_PUSH_BACK_HPP_INCLUDED

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

#include <boost/mpl/push_back_fwd.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template< typename Tag > struct has_push_back_impl;

template<>
struct has_push_back_impl< aux::list_tag >
{
    template< typename Seq > struct apply
        : false_
    {
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_PUSH_BACK_HPP_INCLUDED

/* push_back.hpp
I1PkuTI8BasgKW1toSVet1hBhTYVR7Di1gBF4DMuD9WtheQYw6AnT0hYarWp0GwtMMFalMD3/SfCdH0fJp9eI8LfcRMeuBnPn/Ny0hBTJ1gni6mwb/91G/3DQjXi4K0ZeuzL66rTml1Qtx0ug7p7R05mbY7m+2u85BQbneM2OZnPp2OH6V1uFVocH0As6YbXLQBbYbO9BO3JrN3oRp92BCJIDYGYqc2GyrQOHBFyejeZL8bT6LT0Np3MFqTfBa+AUscCs4rKQzk/4HlU7pqdd/CCx6YirPSea7HcQUkE0KXF4SxJKh1ARg1OMU6uazJlXSd+rGzRQa6VVUytRw7uVyij7/VFpZWxEfyWYsv5ipl5VysMHAEr9Jqc3t/O5uPJl5ZzxRjP8e82aZdyvcLpywukJKEkr27t8oad/UfNfgaFFkMXo1cIkytp0GKwZGkQhn7Y74cXPeoPkoQlYZh0WZJ0e0nqvqa8mBz5i8mBVHJ8o/0CUEsDBAoAAAAIAC1nSlKX9nMGZwIAAA0EAAAdAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NzNVVAUAAbZIJGB9VNFO2zAUfa6l/MNdJ14QqVMoA0JaCZVCq7G2owFNe5lc57bJSOModhv697tOAmxDW6TE
*/