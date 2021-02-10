
#ifndef BOOST_MPL_AUX_CONTAINS_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_CONTAINS_IMPL_HPP_INCLUDED

// Copyright Eric Friedman 2002
// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/contains_fwd.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

template< typename Tag >
struct contains_impl
{
    template< typename Sequence, typename T > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : not_< is_same<
              typename find<Sequence,T>::type
            , typename end<Sequence>::type
            > >
    {
#else
    {
        typedef not_< is_same<
              typename find<Sequence,T>::type
            , typename end<Sequence>::type
            > > type;

        BOOST_STATIC_CONSTANT(bool, value = 
              (not_< is_same<
                  typename find<Sequence,T>::type
                , typename end<Sequence>::type
                > >::value)
            );
#endif
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2,contains_impl)

}}

#endif // BOOST_MPL_AUX_CONTAINS_IMPL_HPP_INCLUDED

/* contains_impl.hpp
bW/bNhD+LsD/4aYubVJEZmTHjqPKLookbbIlS5B43YCiG2iJsonIpCBScfxlv313lF+TrMO2jwMC2zwen3v43AsTW2Fswo0YeLFUmcavezGf6TI1A+9KWJ5Lde+dD4c37gM+nQ29jxeXZ17M1n4xq496r7xXcCfKB1EGRqbCi0tR5HN0SLnloHQyEcl9358L4w8cHgubIbQODuD6R++UWxHBcFLtQyuEHyqFG2ELwk7UakeHPfh0NfRq8AiIdWDcgmX8XngnWlmhbHAp1NhOIjhsk0mJxEqtIkhybdZOw3khCOPRsomd5iv7qTSFNrI+kslcKD4VffpAir13kEx4aYTtZ5VS83egC/LsG1tyNRbeR7IGE8HTCPCG+Od5d3oqwNgqyyAVuUS6IoWs1FPgCpygpTC6KhPUipFIJOZCNKfmSS6JWa1m4hbokgluKzw58IjlOk8xW+/EtTwDb2JtgTvLJcR0oXVyIdcJz+HXq0t35f1tWvtQGanGEGjI6BwEp84NYViNEyd6OuUqXcrhKx3oyhaV3cdfUiV5lQpMdxBMlxEJIGJs5+aXU5brMaNsksLNlQeGow3EIV/ao8BkIn0NGfBKi8gD1Km+xFYEmJXSYl5hJDJdClczsCRbVsqgjuTmkuy/yANpx+8f
*/