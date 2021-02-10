
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
56IwjKboBqJTo7Whxmo2oRQvASy1DdyDYSIYzTG7DQ9V/j88hnXKl8K1N4QzNsUmWShXu7UXbofbbqIsnRtMdYpWou2v37IICiRF79Xu374xe6vXguHb12w2/yUKJmt9MBPY2+7k0+7Yq/tg95sDa2+bxn9F2+b2gN84W17G2w78TVf4gs9DgO/DV8Kvs3U42Gg2XHz/O/ThzRuQGezu4uK7P4D9tsZne/D6NSw3MKe6ZHLLNuOlQtPeZstRELYafGz9n+ufUEsDBAoAAAAIAC1nSlJiu/PupQQAANQKAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MjAwOVVUBQABtkgkYOVWbU8bRxD+vhL/YXIpCUSclzPGhsvZURSSAIWCwE0rRWm1vtuzV5x3T7drjL/0t3dmz69AU7X9WAnZ3tnZZ5595mVJnLQuFVb2WKJ0bvDrTs6mpspsj11KJwql79hpv3/tP+Dzxz4Lz9mns4uPLOEr14TXp9lL9hJuZXUvq9CqTLKkkmUxQ4dMOAHapCOZ3nWDmbRBz0PyqBFBc38frn5kJ8LJGPqjyR40IzifaNyImhC142Ynjjrw+bLPavAYiHho/YLn4k6yD0Y7qV14IfXQjWJotcmkZeqU0TGkhbEr
*/