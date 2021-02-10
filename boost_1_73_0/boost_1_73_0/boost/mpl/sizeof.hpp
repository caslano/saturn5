
#ifndef BOOST_MPL_SIZEOF_HPP_INCLUDED
#define BOOST_MPL_SIZEOF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/size_t.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct sizeof_
    : mpl::size_t< sizeof(T) >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,sizeof_,(T))
};

BOOST_MPL_AUX_NA_SPEC_NO_ETI(1, sizeof_)

}}

#endif // BOOST_MPL_SIZEOF_HPP_INCLUDED

/* sizeof.hpp
woS2paNni6ej8yok7CPP2PhrMU+z/PczfUvfV0zw61rwlsHuYYn+gL4ftEImPO7MidahGRa1Sthiks1XsJz9TGA4fATrIOyLCkptCM9vgIJ3bBIdG402dqJF01xUE1bG3YXawD3+7bVHULjebyA4iJWMIA0pHAoopAXyvQVHeNgZqS04o2CaU0hhZY1NXjjqWEEbFgLGB9hgjNpuQEKtQzhXneuWI6JzJmFGrwevgycatz0ZdnUtrWqMjjjvTdNlPstGPfokSxc5ty72Y4UeeUe8EKjswlKqb/S6PIGSUYIsI3knEpyvBpUMsEa0cBcqF++YODRYEkDvnS+cIn/PL6R30wt+QfHr7f8BUEsDBAoAAAAIAC1nSlJv7cHyVQEAACcCAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTkxNFVUBQABtkgkYE2SX2/CIBTF3/kUN1t8m2FmMdsM6cP8E010bbRb4tOC5dYSW3CAGr/9rq2rPsGFc37cA4iAPmTSY8SENrmlYYfnk3XKR2ySJmz4tZzHSfrzGX/Eo3VbTmbzcTpbjJngN73gDYI9wgrdEV3Xa4VMONyXZ9r29WJWqYgtx8l8DYtRuoB+/xmMBX/ICsh1SXp+JxT86ibosNRowhWa
*/