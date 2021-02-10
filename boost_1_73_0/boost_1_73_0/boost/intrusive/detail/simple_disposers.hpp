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
hXhM3oePDSF/65JpWRScqB/PUdyXToAbV2dVtZzfFddK2zgjLumTnzhQW5HbJn3MRkARve8E6JrVqyqGWeHKZSppe57DE4kqzlXVUL2+TxxM+S0hcUOxbcKbRU7DF9os5wuVWmDl4tu66xAXVyPX4jcrdz5yEzN8WF13LSeyhwMlOOBDZVZwTVG/yhoNti7PiEW9wLsKc4PpzJna75dJ1V/G9Uym5DF9TVyzP4/NZhA4vHip+PAmKx8EN8WBrLjHTYp96lk4CDyq4SumzmTYda1y0jk9OunohqbXT7uGfqJ2WsZRx6x0G81KnRmNSLN8bjJHNeV8eNGtxcLNkLKnssm0Kx7OdqtTiW+wyQpHkzWY342Ki3rOUL0GvsWOQdzvDypfIOqyLHG7nN9Pmop8n7JRmCGiYeSfINfFdLxWMtdKwK2nkGYSURB6/RNu1MIm0srxXs0zmzNFren1yhe99OthrlDVv1W0L/XGw/IaZlNmMwATFmLRez8sFXfYVOV+ODbyB+mg2E2S7B9G98kFm+vRRTK/O4PnKHl2ubGNP2bCCgdYtLVjO8kY+JiY6VHcx26InKFNz9XsaDDJfE4YfYqFPgaOMWxKs9yZlZLe4lC9wdb3IOqP91Hv+x4Nh/b24WMb0WssFDJIx+rg
*/