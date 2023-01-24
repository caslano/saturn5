
#ifndef BOOST_MPL_ITER_APPLY_HPP_INCLUDED
#define BOOST_MPL_ITER_APPLY_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/apply.hpp>
#include <boost/mpl/deref.hpp>

namespace boost { namespace mpl { namespace aux {

template<
      typename F
    , typename Iterator
    >
struct iter_apply1
    : apply1< F,typename deref<Iterator>::type >
{
};

template<
      typename F
    , typename Iterator1
    , typename Iterator2
    >
struct iter_apply2
    : apply2<
          F
        , typename deref<Iterator1>::type
        , typename deref<Iterator2>::type
        >
{
};

}}}

#endif // BOOST_MPL_ITER_APPLY_HPP_INCLUDED

/* iter_apply.hpp
vo4EF7PkqleGm/KKYnwHnjZFTYSK24szIizaU8DKxbdsYRQvqt0eUdUPw6mdB46sOVLrpxJmr4a5Ka6t/QjBfMQHiueGAAHQt7hYmUhmuybMm9Dr+QT59rNniBDok7j7LKGddvjInYZV+IjIPb2eFS3PSauxYXBTr7nG/nEdp/f0ogBQxICkPDZaozdUHpyeNt9/Ktjv06MwOGtwFIArxCvxGhPm4Nh3jwla+b7oQXNIShcJm+r1RZKZJPpOJxYNOrhd0Km8wKgoB4QEXJLnI89PbZ7e43Os0WOaQe9vVdFLD3Dhzr1InLWAxxeb77Ti7kxFe8+64KmTQp0teqEIiJWX+Z+MVO7tUSuKwlm2Hnh9dd/uoJnW36QUZ7Fq6hHpD383/3lmPot621O2QOxN/c7+5gdJupyuWl5f2BrPoSYHOeoFko2XdJANq4Gnrmhd+is5KoRJiXH4eZuJtrkafnx5DPZb7yoGyoqpQysGa/byYl39waaQNCx+nkBwxYRx4Cj4pdFL53JSIy0zq5dtv+GHDvNhsg6QlLd8wcJpRKFq5VFxLpVnHomXJ7xw1zVld2EBhu3fjxHAmYClywE36y3PFFnUaqi/59jxemL3OydkywoYFYn5WPlByGXuw1XdWunLzDcoONsQ1eP+bpiPnOGfe+NsTF2f2ZwEvglVeLiQOJLVQA2izkbyysf6odVysf732JOiaNYpv3k3
*/