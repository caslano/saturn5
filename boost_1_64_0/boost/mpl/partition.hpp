
#ifndef BOOST_MPL_PARTITION_HPP_INCLUDED
#define BOOST_MPL_PARTITION_HPP_INCLUDED

// Copyright Eric Friedman 2002-2003
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

#include <boost/mpl/stable_partition.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>

namespace boost { namespace mpl {

namespace aux {
 
template <
      typename Sequence
    , typename Pred
    , typename In1
    , typename In2
    >
struct partition_impl
    : stable_partition_impl<Sequence,Pred,In1,In2>
{
};

template <
      typename Sequence
    , typename Pred
    , typename In1
    , typename In2
    >
struct reverse_partition_impl
    : reverse_stable_partition_impl<Sequence,Pred,In1,In2>
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(4, partition)

}}

#endif // BOOST_MPL_PARTITION_HPP_INCLUDED

/* partition.hpp
5rI7fylxCQI495RwQTgJygcMsIp83beBY1CUrSIKV6NMGAiAsXOzawBEo0pBmc3JnJ5MHY/G/sFH7LJ2yNc8yuxqYk7LPskn4IyL0NHsbO3lfpHqWNTtwcX0bHr1kjTvkWy3hROGRxpdDnL+CVR1BTZoAY315hHpATTzB15feFQHvb7zK7PXEPSpRpyry4U437L8xSmMDSEQZE3mPdAbdysWZnXmweGBeYesGKJwmm9jo18M79TaSVP3D8ESGGslH9YwHlfq+seOTVI6/4AOn2//tbCHuP2HRBgkcYKwcyJ35dgRCnfMLUu+SYJZr3JedJA0YeeFtDwLp5P1yl6zCpsIitx5+cltIzHVxq6aquPWn4L0QoN4hYuuHd6V4lPce/0nWsxmBNM34F/4O1oJ3lU1dpt5d5pkyqAsiHgemvjPnMev+8/peXQw8DUKCU2Xf58HGlAP2YwFpPGPo3Syra/qEveakfAWxl9Eksc2vM+GV8tR1AW3cAlyrGuN1NBWc+50Hj6HMhTvWkhXIjVdiEEKVUr7f8XunyIvXu74LmMFsy6L/C/uvCYafw==
*/