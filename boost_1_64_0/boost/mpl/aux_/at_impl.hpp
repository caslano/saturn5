
#ifndef BOOST_MPL_AUX_AT_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_AT_IMPL_HPP_INCLUDED

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

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>

namespace boost { namespace mpl {

// default implementation; conrete sequences might override it by 
// specializing either the 'at_impl' or the primary 'at' template

template< typename Tag >
struct at_impl
{
    template< typename Sequence, typename N > struct apply
    {
        typedef typename advance<
              typename begin<Sequence>::type
            , N
            >::type iter_;

        typedef typename deref<iter_>::type type;
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2, at_impl)

}}

#endif // BOOST_MPL_AUX_AT_IMPL_HPP_INCLUDED

/* at_impl.hpp
cngcdsnOy8yaWNrWkzZt6yDDXCJ9/duinkR/P44UwstEr8MMc2uM/SI01BjzNjUQ+rlicT64LeMHrCWd75GgfGnGGBXkfTLn838ozqHDZ9nGW8xPO8j/WwXrL7106OSIcfoEXAf5QIgAqw4xxATGkeXPoMdJm4UbhYsSs6xrKZwU1ACvpBRS5hwLfd9A/Dr0edJmUvllvA6582cxkHgNktHG5S9j5xIJcPNCKzH6Kf7BqE6g5npoBFkl2TGouksdiL3rwQKDX6CTDVYc05oSHyIqDQi4LHolKvmSQvI7Ax8CPZWXpJm708ku28J7kKJlmvVyxPVmKE2M2NxFWIN0v6Wk6M+uz2hyTVHwVwn7BhoH1Yr55hdsZLSGivDkJBtUAC/ZpScws/ApxGPu42x+HHhAN4baAN7cpL5Sbd2cOd1EJnHbOqaacwzNARITGpToHCj8/4xjaujukc3YgESJuZ/HDzKOq5c34mWi7dK9tPVZu3Sfxkff17e3hH0JXz5gAHbSmVU7UA9vA7UhVKsG2dX2aeNQXuIu091WbEsZ1z5mdu+GQt+FZ2qFkmL6JK6VLeAQhHfSZkq8ortlrKT/pc6QnB9GfFCCvntMYS7eTf5ACXb8KY5JSpN8QnKc3zgUx/mw0B9tLpMc5wlMG3vUdEsvzW4rLrYFEoYpGQY0tTcppTmQdxYLlvxuEf53ABlSW2EMJlMOSPGbmHmfFVcAsIbaUgLssRKR4mbp2JlidvheJDApAZwlZQjly8T9sMAKc3DhD2gk7EkRkwW9X1DHggpTEdbLSWqeWGMN4Jn9aHns8ObQf+bujH+Gdkrs7l3lsZgVT1tyJHl4cly/3H3lPegeaa4je8Rg3DbsIPbHVhEtUs1LXCJZKcyfSqFMLhW3jNU6LDKirDGsG8sYOPa1PpWwZcv5O2Hlq2MkMfcdHCkIDSoOvWnXcTk06xA70do68sN3h2l4iTK5K1rvlq/7C6Or2b2TK7jIrZBUZZYlUNGqjlBx2n5z/lmdIX3+fNyMxt8WWdV8gja25YM9lQRPpsVg9oETYaJ/vpOytqinVzRmZIqTQaxjRDfU+hakU+6qdXpX9RO7auRfi23iJ3MUrV+6I2OVn8A2OEETBx9xSx/Ywsx0ikqPS+exzOPC7fu4SPg1lcJPUW9Lsz1SFkmnt/QiLIYikXSPA/wAUYhAbW1OijkVvE6ssCYdWIFz6jN6jd5zKWKf3enQqwYG8+qNWjdol4M8oqUU3qnWDpIROB+vnhtoJcb2KZvTr2J2egWQDXCuV2zhtVRyxGx9MCuBvuBAKgl8oeqRC6gEC8hWmZeYMdA+KLm4O17aR7F9qDv9KmZ8LwqmLn3Ml16PXUvwRIzuE4LE61cQtJZz1XCeU3XqwLicsr8r7xru1zCi1bGZZXN6Vszuc4oos+zXKdmvUtEv63s39FEJxD7kiqxdUmp18hoXeskBSuVGoVfCxuGsbpR/0cfy/0ypZA+ym8Uw2tubgYwB4wYzHGtzNLCWP7RUs5jmsSQoO1FPqhIkImzSHebFiKNj4RINpqqZscdxX+Ykk+M2xrLuTTge+wOM2RZINg7SI5iZ3MaPuAIGj+OmQApUjejh0T8aD6dD40rjs2it0nbWhtwcpOZmTWoSBan5tgSkBtsstJCyrFu6JydFiPYzabs4FRlI7rZbcKtUIYhEOYzpYaEGsjc1DTnKKQftnQbIVU65ZvwgN9sh4AeV5wjlDxxWUFP5tAR6TkaefnGJqVpp592z+1QIjQQrAlGfsMedNjGDGI6kzY9s6ypM3Wcupv/obhcPqyr6Ukt86URf4gB9RV/ApKXRF3BKjemLEztHXclhNNqVthVXTHU=
*/