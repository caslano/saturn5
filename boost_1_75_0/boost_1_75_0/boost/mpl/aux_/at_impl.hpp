
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
E6js0EDw3kd/mmfWKxghaX1EIQCUQMS2tk033VLo98iIMLyKwYMDZYGFJIcmh8OHtqV5veT+u6tXPNHGxI3wlEBp9pBhn2dBOAucvFsRoYxIAhyA32TxDDAnc3hyPq7hVlwUmEgs6jRERDiAekoZ74pp9wU2BRK/26PfeWNtKrTSOUhWFqJefXTe+lvzjLgAoHzKXUeR2pI/EkA5ywQe/dGyS0zS05T+dGUO0Yv0Pqcx09FCkyqu+65uQpm1MdFLT7uPOx4EMRfOBM+GZJ1F/Llkg3dqUpQ3Q+qYOfZC6fLBO9MpmYukCph6Bu+pqwHOcsWEU6Rq3a0mVn/5Q/Dwj8uhqu1CUdvh1NZQ8GP8Jz+OoRvcw7TvZ1HLnLZ1HxQ+bwwmbhzHk7ofJsnTRApgsRLW4+ajus1tVVI6bNHuHFVL0IDEjHbuHIQyUl0oNfzv/wC5FWyOl5AQfifbTekiWoasqA0Ht+adl4fSf3CmMFZ43GXebJUrFgW1uil880Ntrqf/mptePlw8aYg2ArTIC2tOKH7AFAxwHf6LQyax9jf3tf2ZiAqUC9e3xYvUzUS0p5+2BtrzU6p++HFro/Zc3rEuPqpaaTM6euCzUOZKeaKJqk9R3H+L+/tfa8smS6VxK33hm6dJqAA8fR/XypTk2x6RZMqSEuvjjlQ+nRd1x/a0zkWXlJzr0Rm8vyh6oP2xrBIk4TWz7o7POVGW
*/