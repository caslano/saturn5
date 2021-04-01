
#ifndef BOOST_MPL_AUX_CLEAR_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_CLEAR_IMPL_HPP_INCLUDED

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

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/mpl/aux_/config/eti.hpp>

namespace boost { namespace mpl {

// no default implementation; the definition is needed to make MSVC happy

template< typename Tag >
struct clear_impl
{
    template< typename Sequence > struct apply;
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1, clear_impl)

}}

#endif // BOOST_MPL_AUX_CLEAR_IMPL_HPP_INCLUDED

/* clear_impl.hpp
OVWCkbROXXWMOkLGwwvOJysZorKC4be2qcYrkOX0yPGw0zkJcFKm44s+awz+NW/HdkHFEqkCyKmAJqxxDCTwuGVN7MlSJhggwrR47iMFk1yC81tDwOzO9fgflzG56Gvlh7I8davqfixeIG27mIhmaaaEcalqp39XC+OlbKWLrC+zWNIux6sxE3QousQaxyVYQHHMZr+IgUxHJwbKDnuYKX3VXEGcwBGXcoVIVYWCBTEOGKjM6B07xArVDjQahnMVxBOUjSAy2e9cNjVVo39qhUW9zsUmAb9cvbcK4ZzBJ/xGb7DQgBye76YR0IkH1i1Mm9HRtirOW8KtH1YI7C9Odsx1qnixQS0hOhxlJbIqwzqxGTj57UfORK8MmPW7f+lx5Xdh4DelYKa+2fjvzM3lkVeaJW4ZePSHYK+P8Wg1NQNn0/0e6WTnKUAwQLYTdGzIH2NPtcubzuF17clYd5bbYsu+Oe41XxiKOfsjVVlgdhnv0M0gLwGYkFGURIP+Xn5sauJIJytMp8kQqQllZqsHLqdXiI/sbb7Jyz/WwvYrFUrBUFUHs2PX/Qf2rw==
*/