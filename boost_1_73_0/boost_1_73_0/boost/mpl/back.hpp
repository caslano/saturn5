
#ifndef BOOST_MPL_BACK_HPP_INCLUDED
#define BOOST_MPL_BACK_HPP_INCLUDED

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

#include <boost/mpl/back_fwd.hpp>
#include <boost/mpl/aux_/back_impl.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct back
    : back_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,back,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, back)

}}

#endif // BOOST_MPL_BACK_HPP_INCLUDED

/* back.hpp
SgUhitdieIfY+NdcjV8ouBafufGrMjW+jymXs/Ubna0XylAjjmt7E8BeI4C9PntRV/FWG16aZyAHhqC7XM2uEFRwd7NpMlRANv3qTM2ur15SXt9UV9dH09P1M/NvE+mbucc0c49sUtzwmg0v457o2fxdnqvHw8Ju+o+FWp5xb0Ty9vhPhKoePcTqTE1vaGqsOdQet7dGq80M3Bpt/EHEcS/LbxPpRfOVEc1XUgzrDW+D4R22aN50iYZPvKO9iCY=
*/