
#ifndef BOOST_MPL_AUX_SIZE_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_SIZE_IMPL_HPP_INCLUDED

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
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

namespace boost { namespace mpl {

// default implementation; conrete sequences might override it by 
// specializing either the 'size_impl' or the primary 'size' template

template< typename Tag >
struct size_impl
{
    template< typename Sequence > struct apply
#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x561))
        : distance<
              typename begin<Sequence>::type
            , typename end<Sequence>::type
            >
    {
#else
    {
        typedef typename distance<
              typename begin<Sequence>::type
            , typename end<Sequence>::type
            >::type type;
#endif
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1, size_impl)

}}

#endif // BOOST_MPL_AUX_SIZE_IMPL_HPP_INCLUDED

/* size_impl.hpp
aoc6F5LH+6leiPdnv5RL6Pds9gGgjv6a/VXdhPQORv0+FNX985yD91ZM34s6ftN8pv3XfW4N8EVkmOu1ASK7oJCmZ0OW6ILi2xUEOV+gNRh8kIXOZE6tu28dBnWmU9hbu2MPJCEUkX6GXJIGVG7By/IjxJlqrDM5JYdC4DaUEERyseB5HDLHsYTOJkG7kWQCQci5a5d+rz8E0jdy3d1vV9PZ+WS0S8ImV9czlzRv6AILM1lOus/AXTBWN2ZNpBCyNm7XtSR1OZbkeIUQKeSaTF2nhsN42gRFlaIGaMeAnFNfmgJpB0yNZso0DzFtsQV9d2KEtcgnAO9luPdGsP8y2KciTWnmQNtzsyd6iypLVmBOHHiiUW0GEs2pEu6RZlu3TKXusmBpY4miUFLLSIqQ3UzH1209HUanNN0WQ+u7s44drh02+z0Zw2nHTtkO+3lzTr+BuyUK3A27ux3XfwBQSwMECgAAAAgALWdKUh0/MNoCAQAA3AEAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyMDRVVAUAAbZIJGCNUcFOwzAMvecrrCCOJQhxQlkvAyQkDkggOKLQuDQijafEXdnfkzQbE9qFU/Sen9+zHc2YuDMJW6Fd6Ck/X7ibKdrUivuHxzuh
*/