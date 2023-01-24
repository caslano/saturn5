
#ifndef BOOST_MPL_AT_HPP_INCLUDED
#define BOOST_MPL_AT_HPP_INCLUDED

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

#include <boost/mpl/at_fwd.hpp>
#include <boost/mpl/aux_/at_impl.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(N)
    >
struct at
    : at_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,N >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,at,(Sequence,N))
};

template<
      typename Sequence
    , BOOST_MPL_AUX_NTTP_DECL(long, N)
    >
struct at_c
    : at_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,mpl::long_<N> >
{
};

BOOST_MPL_AUX_NA_SPEC(2, at)

}}

#endif // BOOST_MPL_AT_HPP_INCLUDED

/* at.hpp
ixsU+P7LNwHLy8uGQdMfNR3EPnL7vhIjVSBcNl67fNKeTkjkHcvY4U8cWmmYmNlx0Xw/IYVY6rtX2w9KvL4Bikytro+PGAn6x/3Z2LvYgw/Fo/MArldbO4FWSBNRpKgs29JG+FfQgcP6yixxy28rVnlweGYJ2apIpaKEryO9I6Ei5RA4m3/SSwNn+TLqME9ahO/o4MiD25RjD43cq9vrxr0zPhIDx39CcqRbC+IP5tWgYnS8HPV0Q08RkNt12fut8c2/1Sbr8ZEdOmEweLy7mixPvL+3sw+e4HHZR3bgPARdDL++Na+5hOXEReaz89/xEidGP4SVDNj1W9r2bq1oJp2hn1/Ld346ChDcv0A3O3eFm3dYc9nOx3D9qfJ/T/T5XjujyM36irx6L5mSvyCGaSrP2Kw9SbeWnEwcPG2YDlDFP8t6OfHJpXqSmzv6CjuH607bl+UTbPz5ZRKZ2vtdrTx0hP97qSA45CcCUc8zmy1uYfpbwxY7rO/6GveriCy21aNQJuCjrSCwBiirz5M/VJl2mNuszTrErtgEH5+3XDawnSn+KieJlNfo8ss7WmAmrRV79V1GkbL7DZuNaMnpozM8e4SbKv75MnyZx9E4QUEHbvyx7BgxaRskIQY7OpqKJDh0z0s3/jYjkcwhPcEUIHu5bJvqgeWUdMhWPJIfmdjfqdP393iaZYcz3NS0cuq8n7HUyVHTe+fTs1vk
*/