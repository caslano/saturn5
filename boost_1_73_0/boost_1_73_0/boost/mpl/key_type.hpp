
#ifndef BOOST_MPL_KEY_TYPE_HPP_INCLUDED
#define BOOST_MPL_KEY_TYPE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/key_type_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(AssociativeSequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct key_type
    : apply_wrap2< 
          key_type_impl< typename sequence_tag<AssociativeSequence>::type >
        , AssociativeSequence, T>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,key_type,(AssociativeSequence,T))
};

BOOST_MPL_AUX_NA_SPEC(2, key_type)

}}

#endif // BOOST_MPL_KEY_TYPE_HPP_INCLUDED

/* key_type.hpp
dzW7/Ucb5LYqB+J9q1Q3ylmmIXXc4HcI/sBqbfOQTgdiAHpPxX1GBaJQn+yJyRgBTB+KjEmqlC7SDfBa7JLO6E6vCtVoRTPTNhqsU2nlVFzRVja00kZRoTxwx9LQ5LtXZ8P9SlLYzkF80uZh6G4krbVOKZNVUXZDxOh2nZPSVmDT5tJSoltlDfaqLpPAMLTiQq3xZqYNF2uFFcS+NVyxGtI21yBjbclALUxjSVpx2ZblmOiSkc3uc0Jj9IRWHVVskhw8i4aHjm7JcuNS6Cwjp5M1MkXfymLDqZCZZbOVsAyQd0QyoytkZpUwgWUuU6qkMQVqqACvXdm+NMjMpbQFNKYt7oWSFYL2ig5RG9rQPRell+65EK7EXUZcvOwikSUYP3Xm2nBr/1CSzRtatXboWDr926aVJZCMaWtXhVPO299lmat1Ceyh2KLrhtGFLfW4f//5l5IdKnaPpFvTcLmBGVwlW1NARayR44LI3hVv/GajIYBIdFVL5UnLciu7ZgcL4cfwZW+fKDgM2qwsnH/7+Uv8AwJ6j05FZmuRW1s3T0O836HI1eDHHHSN99Lzcaco6AMIk1pVqHAqRjWNHsnjhUFwdHm7jK8W4ZF/bXF3+8unxe1dTMiJXVzHDeiOAd6O/TtjjxweIaULDGD3
*/