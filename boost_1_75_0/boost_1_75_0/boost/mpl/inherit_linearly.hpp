
#ifndef BOOST_MPL_INHERIT_FRONT_TO_BACK_HPP_INCLUDED
#define BOOST_MPL_INHERIT_FRONT_TO_BACK_HPP_INCLUDED

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

#include <boost/mpl/fold.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Types_)
    , typename BOOST_MPL_AUX_NA_PARAM(Node_)
    , typename Root_ = empty_base
    >
struct inherit_linearly
    : fold<Types_,Root_,Node_>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,inherit_linearly,(Types_,Node_,Root_))
};

BOOST_MPL_AUX_NA_SPEC(2, inherit_linearly)

}}

#endif // BOOST_MPL_INHERIT_FRONT_TO_BACK_HPP_INCLUDED

/* inherit_linearly.hpp
9nW8zNTEvJL5IEy73D/8OhSyMkbusC9KkjtdmLx7mG2qIPcVy3fxbagraqwj9C7e6NVWfqN1gIsZe1U3SCBvTPm6fsK7E05hn9ZNohXodcTVawh93rr8Jqex7YCb2C+U4yJokhuz5WASU9g+PreDVHv+dMhq8FYnIQJ03uUYtYBuDHAAxUY4ABW4HPpxWOkV/UmavArP6RdgGYXMI4kEJWao568dJi0DV118p1sDqTYDC88xgc88PQVELhdp3hU3jpLcW0hoQJDCykTQ8nb0iMGMA5XKzfOTaO/XxbDAoF89OZrUnJNKEFKXqk/hzYAihkmHJSfYY3HQzcVlGXfiWHKb6TGQ1q0mtSREm//6OF0RHlTN8mzrpyH+Diu9aSTI0Ne277DW6DCawLbyMxlx/9rFKx+OHRhmNqo5TFRrmLJ0IJDiiHf5MD2ZvxPtvZ5rAaDdvW2CfkCltHp+xy36UcdER8ekd9zATE/Qx7w+CYf7EOpb0iBGZH7qGhPZxWGmjBu2vvG7mtr7PfNNspBRD1KPhRlO3uqyVEtxt9KJ+GXvqw6l8o4EmffM+9KjWZ3L3P7CD0mn0mPBeICZnxR48+tBLZnt1givi3JpInRhVqM+HqOvrNNxalG0I4YCXT/Oo4Vq7cfZ/GLwJOb3CKsJ5fuLKMDK5eBPgrlMdDetmDatZx9pBzomLFzBVZu0GUqC6j99w/gOotEPmgYO
*/