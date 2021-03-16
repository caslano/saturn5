
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
Uqpq2l5mMThkl1wk/S4/6T0elGaSCxKD6TIxICWH8B3PGZCbAkm7qyuOfmiy/N0aEufRRbZ3uMaZrzVh4ZD2klkL6K/VWWb6u6bQGMvdVrBj/R7jUrDl4rKUeFT6TQZ8cLJn1rHZ6wDIQGdDsHIvmyBPeB1ntW+lQaL51uHIS3u+GG8NG1EzVW1DZ1km0T9Y6i8OOJOrYiA5gfn+y2gHhRZF4jUMWTytdxhM/jEYeVnLMdsg+43X2q/VKfJkd9o=
*/