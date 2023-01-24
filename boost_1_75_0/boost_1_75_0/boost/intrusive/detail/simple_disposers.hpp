/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_SIMPLE_DISPOSERS_HPP
#define BOOST_INTRUSIVE_DETAIL_SIMPLE_DISPOSERS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {
namespace detail {

class null_disposer
{
   public:
   template <class Pointer>
   void operator()(Pointer)
   {}
};

template<class NodeAlgorithms>
class init_disposer
{
   typedef typename NodeAlgorithms::node_ptr node_ptr;

   public:
   BOOST_INTRUSIVE_FORCEINLINE void operator()(const node_ptr & p)
   {  NodeAlgorithms::init(p);   }
};

}  //namespace detail{
}  //namespace intrusive{
}  //namespace boost{

#endif //BOOST_INTRUSIVE_DETAIL_SIMPLE_DISPOSERS_HPP

/* simple_disposers.hpp
ZZvlEBsfDh09Jm1K/c+EtflGbJ/Ca31kquN8/IJetZD14H/X8SyvfOPsluqToYX/4ctBlhDPIZelxVTGxrDqpO/BfcchNGCoOEZLisOS+XdTvopVfHlsQEG38dQP7tU/E5XH71NgyJycDnfelNWeN9lpCGMI7wMUPr/P14coJZNNzcJ+Pr8o6migCSnwX6u9u+DEjtvAoFd2Gck0uLGluaioTL3DrTyokVofpvLzhtbSqKJjjl1lVEwpbBAWSf7IK+4i/XaKImeqR0AnMdYrf8RBA4kWs2QWrUWa4NNq63+5V/bLqcxO8y5jdzGtoJeuG+hUKVXYwk5X1XvOWstzqXbbOsvghxbuG2PoZiUB5kv9cgNeMmMY1itLC4KF/8Fjrn/wONkcC3o/n4tZJgeyehISSy2CSz7M1WhPGWR7dCwLErvCVpqrGNkPPvtvUtlY/7kBZTJ61FgcT3sYQsTPVi+YYoVPGjyflolmDm+ylAOnnb+Ott3DyTQapj4eI77jgOglS0hYEJz8OhLt+dbzFOAVgPll9RWxR6rnUwB2HckMmi5i6ztHvHz5uGasi/2AKASWN2lvMhFYEHBieEgF+abMPYFIS0j87174/8p6QxGgEgMh49mEpzUtCljZP5yhpxtI+dUHHN+/IBbAzvqlS1kIw7HfblgUC5xSRT5L904Z+bdL9YpLELeESEtbCAr73pHXXD/IoHaWggAf
*/