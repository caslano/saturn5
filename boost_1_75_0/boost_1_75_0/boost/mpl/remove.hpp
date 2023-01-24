
#ifndef BOOST_MPL_REMOVE_HPP_INCLUDED
#define BOOST_MPL_REMOVE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
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

#include <boost/mpl/remove_if.hpp>
#include <boost/mpl/same_as.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>

namespace boost { namespace mpl {

namespace aux {

template<
      typename Sequence
    , typename T
    , typename Inserter 
    >
struct remove_impl
    : remove_if_impl< Sequence, same_as<T>, Inserter >
{
};

template<
      typename Sequence
    , typename T
    , typename Inserter 
    >
struct reverse_remove_impl
    : reverse_remove_if_impl< Sequence, same_as<T>, Inserter >
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(3, remove)

}}

#endif // BOOST_MPL_REMOVE_HPP_INCLUDED

/* remove.hpp
vBOFb8PF71zN7x2xp+L2Zun0wUXThXRxppQYpjzxXNgXt72Ba+XNFBVtrSBqHe62zTLD4/IltORow1nawSZW22unrmba+Q9euZEcGCFM4UQamHLGoBbvKmiABoguprk9T3eGW7+kelRV2lXjBK3o84G9C96giQvZ4FXObm5760+6ywA6eB8rG0ObXmpo4BtRpUPMyuBv2xiI0UJ/k7cFU+h4nBm93CR+5ycmZqS6Q4waphRkoMGnY1Lr4afPw9gYyIL2SeaAlitXU4W4S4oSqbnM1l5fxequmbBcSAFEVuexGjacdrjyBR+PXKeFMl7trnO6RBR123vRgPz461mOMb0a9zMvGW0paN9DFtNNWMAwBMs4qoT402MryST7uFV6ipblN+5MQ0xH/2j71GeShhgSmaoZdhQOkHts+cbl2ijPp5Armk7aS1ZxD3blbm66O8QJJ6WfFUdxeKfRTSqz/eiA6WihH0kDXJ+Mjzl+wLS8I+twyxuD6Te4zFEdB5eCEeNp/Bm0VG4k7oxSJup36y+g/OvjyUftGPPO6kGZRPrzWUkNB/f9paobc/UQpD+OnHqNQnU4BDi4tnf/oxTA9oWd95+lAI5/Z+zL1TOtJ3al2kXVM0V26CcWWEceCB8XV6U1fTL/pnZM7f3V0LJN/kLiz8b+Gb7EH439yTBuSjSpM/s8ToygPuYYKMMMuX3AJ+dZPBl0pN/McIrF
*/