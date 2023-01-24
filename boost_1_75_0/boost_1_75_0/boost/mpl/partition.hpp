
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
6hiMGqYscp6413dHF0WhzwlhjRkCNPJ0/21uSNfAh6ZDDLzr80gFqhULZrnmucLO/DjuYDyw7UuxD27hehv1HvVW8MvtS1RzZV7ZeqxkfnZcfb41yIf0Qf66WVq/CSjMX06ykWmKF+SyjWMsS/m+uJjATPdsbLrBbaP22Y2J6i1NEl1zcbhqH+XHHSmFy0tg/Gw3V9ERSznznHZeeQTjjcjH7WkLZ25qGXlCn4rhuPTHlS2AdzFL8Fqw41/4WfXZdK+5H1zjFNv0zp4QJRVrPOQfnzCgX/kG14K3L3T/LBFfoRqc6Z95YJJ8h9vQ96rqVL3tK/pyf/8K0NYuoFvEAmJey8p8ZVNoiPoZSzE5D7CLewsbj20ghRgYy85/Yit9AElt9/E0rIPZ0xfpB/6t+DoC1mMoRXJnH0CA9I2SB/vKs8X3T8oJlEWvumWOTROurtgtiQTjCPXH8XfR3RbVhUyRA1AXkKQhXTHzoz9eROdD9ss9JDbW0quMze/G4DN1l4HbrPv/VLz3cQW7pNgI0F0WbhgoFgKnezXJ3DZcP/2H4AAUONvvkWCDcGNkEbJnmR2NZ+9nEipHIhHd8H9ca3C+p5BCFbxz9IPjdRJefXKXmnwIaJ0ihPsP47HA+/7J+Mz3S7SOGP+P8az/lfG8/3lD1zY3lXG0+2nu/B/IW/8iHXPzF/lbRHDJX0k7VJFjn0rE1aglLrBp+0l8
*/