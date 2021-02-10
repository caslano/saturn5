
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
S538hKXOFXhg+xgkInQlIk4YJdBWL+DtGwgop7a0kOkozOD366sq64N9Wgewli7VpYM0tCke5vXpINJ5Hqp4q4On9AC9itId4J1UUVbGAus8GOTbOITuc969u5/yTK84lZGkHeYtzQZ1gpnXtPZOw9pIh2rCZ5FoI6pGgC0RUyqLCpBbVTnvuzGQUvDuMc8ABbMV8dHw0AOhIh1LtRp7pUsGv3rv0G0Xeud6TK54WNmxR9JjNuv1eoctzFCbFfdIY+JBYsO3jGK9VpkOY2JFnuiB+DKRUUhC1hb+3LQtiIU8fIx23Y1MRjUMBKXJwGF31+Q8KIxIsOFUhJY3h96kody9vF0sZ3d+lwp9dztfcuIScDzeRN/FqhLglAHlxJukAr7NmO7rtwHOjqsmfMIKgUS6i/nZdDbnmfxMReBK48hJ6+ywyICEqOabbrYjhlhPQLAXmm6v5uATCbKBapWEiRMGXNo0ADYmNgR2hWdT7TxW60mLpzDa6UhjWri0oI64XTwddonBfHimRof9hvM0OF1hcNwdqArvfjqfL2a3Nx12GkWiQPNr/rrDOsR4F6Iq9OjvK/1vt0EF18AePYG1LsZBa0Brt6PG7XjfTRhTuUGuY7TSyvPaufehwIWGPQ+9f5zM/m4OOe6J4XD4
*/