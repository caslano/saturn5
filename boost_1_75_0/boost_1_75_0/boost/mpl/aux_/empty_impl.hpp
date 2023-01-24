
#ifndef BOOST_MPL_AUX_EMPTY_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_EMPTY_IMPL_HPP_INCLUDED

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

#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

// default implementation; conrete sequences might override it by 
// specializing either the 'empty_impl' or the primary 'empty' template

template< typename Tag >
struct empty_impl
{
    template< typename Sequence > struct apply
        : is_same<
              typename begin<Sequence>::type
            , typename end<Sequence>::type
            >
    {
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1,empty_impl)

}}

#endif // BOOST_MPL_AUX_EMPTY_IMPL_HPP_INCLUDED

/* empty_impl.hpp
cVlp+AASg8AbtFbFLCAucfBsOq8MJsmoz4j9exBR/LKt70io9T0Lc9gvJ45o/pd1dB9PXD4FBmx1U3H4mz6hrOKoWuSsZJ7JQUyJ9FZ0y9zhu2k6flob0qaC5K2HkFYJ9wY7yCrO5Qvn6iadvdtgpNaGaGo89TdkjYHzKimC+l4eJMy2TzLJFkRkQJZixXl86fxp8I9AO3LkPMu9itFSwtZKOQLFkALAe8w2bBv7/XZIfxpiwIvATWunohrJFgsvwzyoB0PqfddcC25bK3xaxns18nQyW6J8Z087TCypUmJBIGbE/dEJyVRH/VvjcNYEkvhCLahTSU1o0KKEjtI58mdsFklJh+9XJi3NP6CY3329R+RnSEfF5LcP1HmoDQGWMskDnUobzsUUhZS/xjEX18kZvIlSO1P7ybNdqZDGfPc0RjM79BaP17Xj3WI2IvFPwl4ypaAvMsJjBEpL1vMs1j35s3Pj50qS+ASPyQNNCuHpiWEQgGpTdrbdUIDN8y/hoG1bcq4zh4LhPtqwEvzmJWFsBWHEvO9SendbYiVvlFzTcvSL8L6+ldYPkLHSgQUkIc/1P5ERTl1DEuY5wp5WFAoNHpHhe54uLIlwDYnxuTX0MwQ+R/UFjw+VYpNEz7Nrr+Of/TUBX0YDdR8Wd4yLOGZvZgLrXl11TUMs6tj4EFDt/bmS/D7p8m+GYEusW8x+qr0e05x6Vn6238yy
*/