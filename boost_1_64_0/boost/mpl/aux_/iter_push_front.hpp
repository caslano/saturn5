
#ifndef BOOST_MPL_ITER_PUSH_FRONT_HPP_INCLUDED
#define BOOST_MPL_ITER_PUSH_FRONT_HPP_INCLUDED

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

#include <boost/mpl/push_front.hpp>
#include <boost/mpl/deref.hpp>

namespace boost { namespace mpl { namespace aux {

template<
      typename Sequence
    , typename Iterator
    >
struct iter_push_front
{
    typedef typename push_front<
          Sequence
        , typename deref<Iterator>::type
        >::type type;
};

}}}

#endif // BOOST_MPL_ITER_PUSH_FRONT_HPP_INCLUDED

/* iter_push_front.hpp
qjyuSs6DDnrRWqZkYIfCDmDWmIVMNWHqv4rhTJeBltJOcH+hsPZUGxndkN2Jh6JZ4lvFWjWSt+6Q3EcvY7aJJLMoRei1ABoX38x3qa1kfinv1uFDa2ryvAVCF8ZFrraQdPi1PcIss9JK90QK8ybNQC68mMNLCvtoQ0PPpkOrRBYeM1IglXGnVazTFuMTIzmkVHdQ1jOXi6/QcCEyiPyJTSQb5ADXSuFO31a9bGTX+8e1e9J62/bcqm+sOo1moUik5IHRqhvnFv8cqKHYNx6gdsPY/bOTc09yvslM/kUhGAkzfDoccqS7wSUWVkoCqxOIWzpI/B9e41LBex0vvUcynxJQ21QhU8POY3d9puGZ2GiWOm29wOi+8lRT+oKedT2gXu37I5hE0UxOqtqQ8cRKUHbZ1QyvXq4qFo1p5pw8pdKYA+1LOfEl8D/MUoRpLuVh7o0rWzoZUdNFu6FfkegCEc8ve0YbZZxupDvc2Z4dE+TSUrBERXhU73pQJC5kVY70J+7FC1BCzQgiZepiAAmX1RXqeaFzUIxCy3IUamEq6W0yPwySA0vgC1EBeg==
*/