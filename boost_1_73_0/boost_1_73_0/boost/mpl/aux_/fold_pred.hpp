
#ifndef BOOST_MPL_AUX_FOLD_PRED_HPP_INCLUDED
#define BOOST_MPL_AUX_FOLD_PRED_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/same_as.hpp>
#include <boost/mpl/apply.hpp>

namespace boost { namespace mpl { namespace aux {

template< typename Last >
struct fold_pred
{
    template<
          typename State
        , typename Iterator
        >
    struct apply
        : not_same_as<Last>::template apply<Iterator>
    {
    };
};

}}}

#endif // BOOST_MPL_AUX_FOLD_PRED_HPP_INCLUDED

/* fold_pred.hpp
9Mh8ROpZ1FSlGuutGH/MWOjl5dL1N+LKxzS9CbQA6C/i/Js4v4zzOazDcb5n91dAsfr9Os7X5b8d52Xt3wBFe/xWb9Sqk4JQR5l+SLDXBQtyH8uj3awm2Rv4mqK5oAKvKQe6bswS1Yn7vAtiTTM5u/X6cjLT+jJ5DglgT/Tdhi1vJd2ZvxLkEq2J/M7sNn2f6s65+X23L0xXJvKNB50UD1rXa/SakzooHjq9Odvylb9GvnKedUTelKIfKrfKox0=
*/