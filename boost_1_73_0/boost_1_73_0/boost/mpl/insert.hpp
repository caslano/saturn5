
#ifndef BOOST_MPL_INSERT_HPP_INCLUDED
#define BOOST_MPL_INSERT_HPP_INCLUDED

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

#include <boost/mpl/insert_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/insert_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Pos_or_T)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct insert
    : insert_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,Pos_or_T,T >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,insert,(Sequence,Pos_or_T,T))
};

BOOST_MPL_AUX_NA_SPEC(3, insert)

}}

#endif // BOOST_MPL_INSERT_HPP_INCLUDED

/* insert.hpp
jLcy2gQ3jdcmfpe8q/8tpGNHywSZF1nbDg0MialGsDkCbXAHOoN/tnSotdWq8aaVQ6sOl9F7bKmNDeAPhMeelMIDpQZ84DGPIK46gl8wqKvfn+0HUEsDBAoAAAAIAC1nSlIq/djYfwEAAHYCAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTU5NFVUBQABtkgkYGVS0U7jMBB8t9R/WFHxgsi5CRSpkalUlYoGXUnV+p5PPntDLdI4sl2gf39OHejpeIl3vbMzk0mYR+elcDglTDeVCccrHt+NVW5KlpyvTw94XPBYWGxrIVHBDoVC68j81+Znuea/ebFazMvnh4IX5TMpqmRllK40qmSrG4mE0TMvo1GKDGGL9g1t4rQKkI78GMZKeAGNkTuUr/cXR3QX0QtNf6QwHt3AwlpjyYPwmAPfHa4hTeHpUEM2SicwyvLsLh9P4HHFSeTPoXvNxJ0a6t6drI1DskFvj8ms8h0iy0gw1kl3BnsrQ5jXGhvfG5SnJswj05TsvG8D+rNljdhj9Ar/kPdhQSus080LiEYBfngrpNemCftxjXlj6imp9Z90PLkN17Fn0uz3YSWq5ZReLsstL9b5ZaezLjec9vgvYCh7p4QFY7rqUm2t8UZ2jOFrwmkH
*/