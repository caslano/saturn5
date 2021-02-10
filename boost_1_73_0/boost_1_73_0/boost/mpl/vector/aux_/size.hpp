
#ifndef BOOST_MPL_VECTOR_AUX_SIZE_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_SIZE_HPP_INCLUDED

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

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/vector/aux_/O1_size.hpp>
#include <boost/mpl/vector/aux_/tag.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template<>
struct size_impl< aux::vector_tag >
    : O1_size_impl< aux::vector_tag >
{
};

#else

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< long N >
struct size_impl< aux::vector_tag<N> >
    : O1_size_impl< aux::vector_tag<N> >
{
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_VECTOR_AUX_SIZE_HPP_INCLUDED

/* size.hpp
tC+DrcZC5rfLCwwm1mtEpsS0pWknMix71DqRYI4uJg6qH6hpkQ7GFLVkQW5zDtCC2sfB2BsyNniCKIefeaudY9hnaWiHBthtywNM/opH/jIHSZ97R5ICR4/GuEXDsXseeyJ5rhi3RdvCmUgEE8G5gpCCDHY3aXD6oLsW/C6jinKJiajERcetIi7t5MqaTO2LYUUhjPENvn6pvZRs/wajxzaF98TJlNPaFLZNjl9njxNWoZRdQmaobvKaSY273kdlZoWSEmKTXvHClgLLv4jdE7ZJOuO7wY2lD+7sT0cT7Nw0vLiRNm5qK/f9x3bUH/z0ummuqRj2Okv7/U1vErDGRGf1q3zWuMrnXe+WNcbfDsthxf4HqPBtxv91SjxoeA9IjZmkRuOr1LDY++asd8Hnpy6tO+1R1vFW+aWd9m7Myx7r0weghlSdnVIY2l4+tMP/vL8BUEsDBAoAAAAIAC1nSlKjQc2fSgEAAFMCAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0OTAwVVQFAAG2SCRgjZJfb8IgFMXfSfodbjQ+VnxdQ5oZN6OJpp2yvWO5jWQtNMDc+u1H/6hZtoc9wYXfPedwA/PofCEcpoQpXZqwvGP7aax0KTnueU4YvR8wOjBkSqZw
*/