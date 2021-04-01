
#ifndef BOOST_MPL_AUX_FOLD_OP_HPP_INCLUDED
#define BOOST_MPL_AUX_FOLD_OP_HPP_INCLUDED

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

#include <boost/mpl/apply.hpp>

namespace boost { namespace mpl { namespace aux {

// hand-written version is more efficient than bind/lambda expression
template< typename Op >
struct fold_op
{
    template< typename T1, typename T2 > struct apply
    {
        typedef typename apply2<
              Op
            , T1
            , typename T2::type
            >::type type;
    };
};

}}}

#endif // BOOST_MPL_AUX_FOLD_OP_HPP_INCLUDED

/* fold_op.hpp
f+T15lH0NthROkqrYjyt3JhbKfVefgZzhxy12r0et1xX6k9W6sSANBqWREzzLhv19FmrvWZqlwR4wex24iHIk0DZGJoE5LtE3CI6UrVfOtLaqAUU9HIZdEHc58RrpkIbjTH3j8brMQbKyd40FOfGG9LsGIM3LYelv9Wg+JqHXFAMeTfwIblOJWwazsxQhm8HQFc7zZPhJSmkBj3anxCuq1tqUDSp658Z3iDCfHN5EuC/cQyyQtsedEATSF9rB07TI2vUGrDTQF1mmZ+8UxbA83JAWejlyvCAnr95daqOt8aLmU4wYcAuo7eGZsFEGfrdVzVTpXvYAoQhR7nVi066h/OQpRbgcvOR9TQ+KSRBGb3GDpVIW39jpAW3GceKJcgvp9nC077t+crvog4CcXDP9PiYIc0DH/pP55s2dMZjJyPYYVqVSQam/0/fLYfqry8UJ0QW24MIzsXOY5dh4YAvS7bbV8tObzY21QKHTHms96IhKc9vFAmHRm/qFt9as9FVGJQaypD+aKYlXthyifjypKOe6LmIQdD+7UK3K+s0ciJCBGTKsBvAebSjWg==
*/