
#ifndef BOOST_MPL_AUX_FIND_IF_PRED_HPP_INCLUDED
#define BOOST_MPL_AUX_FIND_IF_PRED_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Eric Friedman 2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

#include <boost/mpl/aux_/iter_apply.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace mpl { namespace aux {

template< typename Predicate >
struct find_if_pred
{
    template< typename Iterator >
    struct apply
    {
        typedef not_< aux::iter_apply1<Predicate,Iterator> > type;
    };
};

}}}

#endif // BOOST_MPL_AUX_FIND_IF_PRED_HPP_INCLUDED

/* find_if_pred.hpp
ezJljr6MYgxxy5yXt6tQX+TYpb2HIYCCjOZ0HxwSRblxvyn38UERkQHKDTZ/s91zSvpw/xCLOcRscrxHDCOjA6Nt5xNn2Rb2exl7ehnSv7Ptj8wj3NLF17tzsMVitrcfPJS/BfiHh9nPbo7nIiXvHLytJ9VKpD2yjU8+WYAPbwngVPimP7DS1nMh41x3WJ6PchqwL9T4PgkyagqXdzNQZ66x4Y5TiBOmUqYOda4849ISqH7P
*/