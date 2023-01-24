
#ifndef BOOST_MPL_FOLD_HPP_INCLUDED
#define BOOST_MPL_FOLD_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
// Copyright David Abrahams 2001-2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/O1_size.hpp>
#include <boost/mpl/aux_/fold_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(State)
    , typename BOOST_MPL_AUX_NA_PARAM(ForwardOp)
    >
struct fold
{
    typedef typename aux::fold_impl<
          ::boost::mpl::O1_size<Sequence>::value
        , typename begin<Sequence>::type
        , typename end<Sequence>::type
        , State
        , ForwardOp
        >::state type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,fold,(Sequence,State,ForwardOp))
};

BOOST_MPL_AUX_NA_SPEC(3, fold)

}}

#endif // BOOST_MPL_FOLD_HPP_INCLUDED

/* fold.hpp
i8KcjPAX2TmFqZzMq2dR04iD1G4aqpMYT370NhkrdnfXKmrlK9EdES4NOC6Sjnpe4GFd+3eKwtMdQXB+6/Nape7L1FTzjs/RbG8+Nu+0BHprQv50zMpM/aHrizzUe+Nv9flkCD3QNJN6Zvmrko2Uqvt25cDdzOJA1cUlOv9UVLQQtVh+qr/sVEog/9fB+oPjeixR0i58UeI8Cs+iLsGx/vqfok/OfKj3+z0c1u4vtG8LZAaG92C4oq+XHxffzf4rxGwbY9tob+X5nyactADHUDFvWjfCX+TKyRTFBeV6k6EL3YfDhcCFuwF/+a0DWtsbgxDHAbYBr23tbT5ea/Sbf3pxo4GNAfaFtNFg38Nz4qx5Ijbffqp9xADKQOiA1IDxNsrAUJUJ1Q16CGKAduBBNeuSmIuCRyU7YCSyAzgQV7prNfZ5915ta6yBpAVSCY5MyCT3qPm21ESwEfqMtRqZMfzDeJSSj8J7D4FL0Wh2UfnTFjvXrdtoqVGlxJB7xTrP3U9pSFnwYICa0QqgbfbJlB7LumTrZznn0/E3oW8M6yFO1p88SVFXKtV6ObQ/hbOOkns4WltsB7qXLLmohqAuNUIoq1FOHLc//k128rHBl+Mq01kH+IhVloLr7E/3s2ivrl/tpHm9I5NqyVxQnv/1/WdV0kqfHV4bOrQ/He+bB1yatjySCnq2vmCVxlC796d6oNwLqg4S9PY8BFCn
*/