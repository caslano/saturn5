
#ifndef BOOST_MPL_AUX_COUNT_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_COUNT_IMPL_HPP_INCLUDED

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

#include <boost/mpl/count_fwd.hpp>
#include <boost/mpl/count_if.hpp>
#include <boost/mpl/same_as.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>

namespace boost { namespace mpl {

template< typename Tag > struct count_impl
{
    template< typename Sequence, typename T > struct apply
#if BOOST_WORKAROUND(__BORLANDC__,BOOST_TESTED_AT(0x561))
    {
        typedef typename count_if< Sequence,same_as<T> >::type type;
        BOOST_STATIC_CONSTANT(int, value = BOOST_MPL_AUX_VALUE_WKND(type)::value);
#else
        : count_if< Sequence,same_as<T> >
    {
#endif
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2,count_impl)

}}

#endif // BOOST_MPL_AUX_COUNT_IMPL_HPP_INCLUDED

/* count_impl.hpp
b01tX8/WhtzT+4+oM3Gs3w9n+vjXVF3kvhzq8+6uDQkvycL4d1MxB+ly1fLRMUQsSQp4Qw/LwlMkXqZk0h/maiAme1MljZw8KH5u6KG/X4+pU0JD993umxImDD1Q2XmdN5vLkcccjlfCpBIGbwdkdMW9DhEkmPy62vpIccEzVOQuW3658B5fv/zs7ROUkI6voWj9EU57H66NIcLXYgLePThXojMoVsEivcOHMuOwchKAu6udIDZavckaB6LnAsVPsopXkIXfxbWyYNrSQrm9/xGR+ChmzD01jLGbIb+SJo9Ez5ZfwE4TTtRX3jhgr0/hWSsoCMUfttm0KHfB2Bfpmuj/NggKyxbarF6jVUvrKH20DF9vl9sXYljrh7eQdKwjMZGB4HaWOK7qn7XjiY6n/s3FGrL5vlulfinKArplQCjw+P/s3b8kIy1e3WWZsE0KAPb20NCJkh6Hp32vmFilx3X0aJPfoJ09FR+5ALAzmKsjroqQTtOgTao9yBWPaT5wAgKxa2n7vXg4/WD0n1cK2/SPhyc0bhyqHaBJoS1E/2n6zPCF9P8WPwfNmQ==
*/