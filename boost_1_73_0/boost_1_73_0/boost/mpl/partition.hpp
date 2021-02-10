
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
xpBK7yvrQnTyFoKRG5zdLtPO8/XeSp3NR+vKGk8o48YSVec/YXQS6ISv2gpjCPgSRBE25QdQhXQew0x7yy8uzt7zaMImbFVoD/QYG4CIgUNZQiXXJFwMigfl0U/SN9bulf9S72/x2TnfUGJDEUN03nFUwy7k1kFr6y2zaEdNFaie/r/K/GPp3maZrO1A0JxclboLH+ZE9cactlnie4JzVoRQUcTOTHKUoXZI06ZcWwVLZ+MWJF3K5uO8AufZMKyB1PcYfZ86/FZrp6nC0rT9IIOkgS5LghADBiTKbjbSZAOHWIija0JcpPFRB5/e3a9E9O4MeE3xBB3LigrdZOOVPIPp19o8Yam7z5So7iFpuRVLah/Q6byFLkcg80AcuznqfpWgkJ46EQ1MfWEDQTz3vgRQORussiXpMdiU2uBs2qKfzlkvvOe2awBqBetDDAcKJuwLUeeXa6ISg6pdKY4ePt0vF3efqZuVwoq2j8XxYaEPGkVWVbltfPHCm6bhVP0NJ0g0ymaYdY3xV6hF0R9x+6FUVJ5dertS7XMuxn+K71BLAwQKAAAACAAtZ0pSJ6HWxLECAADyBgAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE3NlVUBQABtkgkYN1VXU/bMBR9
*/