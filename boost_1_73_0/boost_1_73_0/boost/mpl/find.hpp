
#ifndef BOOST_MPL_FIND_HPP_INCLUDED
#define BOOST_MPL_FIND_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/find_if.hpp>
#include <boost/mpl/same_as.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct find
    : find_if< Sequence,same_as<T> >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,find,(Sequence,T))
};

BOOST_MPL_AUX_NA_SPEC(2, find)

}}

#endif // BOOST_MPL_FIND_HPP_INCLUDED

/* find.hpp
/1T2C3anq9Kdn+0tFHYPhTVS2GMU1tLuh6qRtNK1CWIvrmF/dW/rClzLcDtE+wqg7w5MTPJtY1+BOdX1NYvnVM+trZzf0t6yaoVCiNG5N8rPkGGIPJ5JbEemybA6j1g1d61H7JY/V87vTqEzlsLPRIzCVlGYtZJNd1aLENVQlW82x5s25zhfPBOSc2RC+CVHTePm70wJdVoc5aErG3xsSRfF8vUx+30H8MtxvrArZ23EJ+Ix+jQjlv3actzwrNM=
*/