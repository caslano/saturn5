
#ifndef BOOST_MPL_ERASE_HPP_INCLUDED
#define BOOST_MPL_ERASE_HPP_INCLUDED

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

#include <boost/mpl/erase_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/erase_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/msvc_typename.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(First)
    , typename BOOST_MPL_AUX_NA_PARAM(Last)
    >
struct erase
    : erase_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,First,Last >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,erase,(Sequence,First,Last))
};

BOOST_MPL_AUX_NA_SPEC(3,erase)

}}

#endif // BOOST_MPL_ERASE_HPP_INCLUDED

/* erase.hpp
Pu48Au342LxzRv0sbzuFEqwWDNiArnlcKG2FaoQxUwUODFKJAmFdURpCrxmhIUxGka/FclWnKtDqjJ1Pz2uBl/QhdbR2gRvlkYkreQhhzHZwT+Q0cP0L2wKV9qyekA77KDYDCJPwXUG+QW9/WLjVlacWQwCeJehUnCFFotU5tfbAItcGOYXAoUeZRR4k/LOqCG7NtyJXTpZzzHDOxdnKZsX3m7Xpp0CUqAEz9ZpE0BU2IT4qBh69Q8cc+BAXrun/PuT5f2WcMzYgGadNAWaFe4Ue0HZjStyx1zYsXsz0QmOrtx2P5vQLhs/cYO89z6SqHcua5Yb9vcyHMKVoFhFjmbyHK8Euly19dW95GIe71D8OIQOquaIQL+CJT4OxII9akaC990L4ZoiYb177bgbBCXvP9XTl46keMGNO4NwnL9Wx8kWVRUqgBRTL/Prl6AJ1dPh6r6BnmpZC+TPwOCAc6BK/1dP1cwhdss3ZvfBGbg2MkU4epCB0df6JL9IjQWSgAiFaE/CZSR2Hq0ozzm1ZQXy8k6Etbr1xVbvOX8J3nJLVwVdLPgtmzE5xew==
*/