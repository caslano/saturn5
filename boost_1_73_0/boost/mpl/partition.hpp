
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
c3hd4hoGG4t/v6G58c86/nPj36hwnv17ANcQtc/If+xXjBovGcZ/rj/7nN/SkB9lfyI/KhZwnbDrh8h7keH3IU6P92H6HtObVMmenpyYvY4dpoe8apmdf+/nTsssT8MjbYIflpVnc4bmxn/7D/mPSXmd79zRr8Tf/s40FYcWZxR0zk1ISYqfcMDn+QLy7SfP/foYzBw+PVh5DY51MluYJx4pE+MTI3FJjU+enH1srzvo110/
*/