
#ifndef BOOST_MPL_STABLE_PARTITION_HPP_INCLUDED
#define BOOST_MPL_STABLE_PARTITION_HPP_INCLUDED

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

#include <boost/mpl/fold.hpp>
#include <boost/mpl/reverse_fold.hpp>
#include <boost/mpl/protect.hpp>
#include <boost/mpl/aux_/partition_op.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>
#include <boost/mpl/aux_/na.hpp>

namespace boost { namespace mpl {

namespace aux {
 
template <
      typename Sequence
    , typename Pred
    , typename In
    , typename In2
    , typename In1 = typename if_na<In,In2>::type
    >
struct stable_partition_impl
    : fold<
          Sequence
        , pair< typename In1::state, typename In2::state >
        , protect< partition_op< 
              Pred
            , typename In1::operation
            , typename In2::operation
            > >
        >
{
};

template <
      typename Sequence
    , typename Pred
    , typename In
    , typename In2
    , typename In1 = typename if_na<In,In2>::type
    >
struct reverse_stable_partition_impl
    : reverse_fold<
          Sequence
        , pair< typename In1::state, typename In2::state >
        , protect< partition_op< 
              Pred
            , typename In1::operation
            , typename In2::operation
            > >
        >
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(4, stable_partition)

}}

#endif // BOOST_MPL_STABLE_PARTITION_HPP_INCLUDED

/* stable_partition.hpp
AT0gezLhRPFut1v1HhL2Zab3U1WtPZ57W5wJ+2L15BLLtgnp2ymn+8/bGiIE/brV/2tRfJWgRS/LRVn8fT2IxRGlhR0V+fKRfvvTYSNlFbW2d35maCumPtPcA//lPbCtAlO+CZdhB+0zE2vXgM+HmZqPY/G3nKCsgJc5sKujascNapTITZ1Yt/w1PyxsHCuTO1ikpKujsKE4wcmccWqSTtdPuU8d/IQC161hu5sWuZZ3VXxDOXCpJuiHOAhUDCrJD0jWX/N2XNXd3C8177FngsTRYfhg/JKwcvOOR0/1AQJuVPsBpWeYmEvxQQIjGfGmWBeS/EAtaj4VsDrwMx8r8VE8d0wgvlLhxV3A7itRSHvn++y9QhNhYTGoSs//4A7ob/8F36sq/xNVOCAgEgvSxvqDz2FxgNvkfS2QVEOaEiJLc4cD5UgPmEhBs94ekGGLUpQrhM1CMLShlGgopKr3dmIuYRdLek/W1z2BkCDrup8rgFTC1/r7/jJT+7CPEnLSOtXSqJgXF+LVlXcfkZhd2vc8xDNfvF6D6pmE6xEhuiNWJoaJb4EYUTJ2uA==
*/