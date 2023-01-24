
#ifndef BOOST_MPL_BACK_HPP_INCLUDED
#define BOOST_MPL_BACK_HPP_INCLUDED

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

#include <boost/mpl/back_fwd.hpp>
#include <boost/mpl/aux_/back_impl.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct back
    : back_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,back,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, back)

}}

#endif // BOOST_MPL_BACK_HPP_INCLUDED

/* back.hpp
xLwPRBb78IjwqaQCr1RDOQrCMXabhT4IfbBRNb3GMzhqOEjbEbnGW9f1xP/8QqXNNcKDUI3EcGpH+bevbBzZPfqt8ZDw2XWlkO7QfB2/T3LkoiX6MWYFebdcXCIuTrAbc0uVReYSpc8PGgvJVb0amRb+eoAx1RLRnp/ib0d9dqOJpjrspmj/JXSfGKzXRZ9qeHfRgdLTBNuOBS0cdrex6h2Z/vqswuOPzqTltmO5yA8+4gGhfHidYqq/fNTHxsjf4c5QGZAZjepyZbvYtS+KNeU01qs2fdWpe+/8fqW3qTbbmdPJgriOSHe0fUnU1OzgAT5iqVbLRGWrhuH40VQJ35sEybGjxRSeqJ5dZ0sKaPv+6cYw01Uxh2q/5u3ElsUNrnDVqwqRbEHRsZzYU4Ndsge9yBger4Gk9HdfM/1n1r84Bo75kSGOLcnQ4smOP3pNTjDY59sItA8DFrFyR7D1xYUjnyhhJjCNPT+t7Bgq75jD4782BP5yWyH0+35dawqZI+/PNNEv8SnAMlu60ST1ty+P0cApJftZFF8tVvG65cPqSkItx7lo32TdLzQxuYQeTrW6IfSAwbPCe/vqCFlOfNAq9PSigCn226PR4e8G4o8fTwfuTGhvizihbS+uiAubi8VjllNq7N9XqOFbEP/5y794NE3Krnh2l5+VxAdIWOfF9p3CIyzbVk3CqoxzQTd8Hmfx8223bt0hJfLF
*/