
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
gML/OJldr9LAE7HPJsATY1yHZ+YbnJubj9tPYbZ5DJUbwMGbXI7+k/21laWM/JCjggoIt3GLg3GwxaBghqTwBDFapLlaziqKyjw7j9hl0Og2+Dn4txFptbF+K1WHTmbFf2DDRWSyrvCxocyj8j7EQiwUJxITE6N6B/tjmpQb9tlDMHIW9BgoEUWad0kJ6iEcw6BGQ2JfHbdchXUr6z/5YXlzh0X6HNkO9Lp0x1uMI1+TFlwU0BgJfbo15YJLKKBldvAzRqWWhzAezBgLf5zXord3EN6lSN3OiOA+ZfMTJG0m5ae3VdIVq1D0IK4gGfeL7zs9mkWQUJ+Ub0aR0jdEyP3b9CzxS76tfR4zQ57UBo0Jsk9zAspAkuwYopjZSQt8mSAH1dcGuCjsqvMvUTTEP7Tkm5/aPy8+rNQDP67JhrWCOad6mJUUpkjI4PP+8BqX3jfQOVZvr3pLpCtNgaTXnbLUHsZSHjXsu1dvCEo0JCw7MvS9gpc+76NRazl3tGGY53T/16ZFZzWUreRF29sos/fmRrf6uuSwgrOxpfhWYrtyZEg5jSoj7vfFmg==
*/