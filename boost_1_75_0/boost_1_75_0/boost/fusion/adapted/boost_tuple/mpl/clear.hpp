/*=============================================================================
    Copyright (c) 2012 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CLEAR_10172012_0100)
#define BOOST_FUSION_CLEAR_10172012_0100

#include <boost/mpl/identity.hpp>
#include <boost/fusion/adapted/boost_tuple/tag_of.hpp>

namespace boost { namespace fusion { namespace detail {

  template <typename Tag>
  struct clear;

  template <>
  struct clear<boost_tuple_tag> : mpl::identity<boost::tuple<> > {};

}}}

#endif

/* clear.hpp
6PQ8FZTOvL86pHOOKzSdj3wRms6cdnRe90Vn6NzzZFA6K//skM4t40LT2VQfms7cdnS+V98ZOlOC02ntmM6zTkOn4zR05rWjs2un6FSeCEpnwR8d0jn36tB0Pl0Xms6CdnTeWNcZOvc/HpTOqt87pPOLLINORNBsR+eRHUHmOqJTqmB0Frajc+2OztCZHpzOxI7pHJrVvj39wAWuZsW2g9LxLMyzuHv4zaaAeTdTTLlkzsmm6bF5srdLc4TsNeBp/thu7QTagPuxoLV4synOErQOs+TQPFG6PTRPFLdr6+ztnWnrukeDUvl2S4dt/cnY06x/toWkU/e6YSL1pW2dIXVQcFLDWvzWK360JpyG1otOQ2tZIK1Ht3aG1uJHgtI6+XDHtM4aE3qslW4NOdbKywNpvbpTtG4rD0rrG791TOtaZ+h2/ebz0O26IpDW5z/vDK324LSePNQxrXGnofWC09C6MpDW37d0htaih4PSOjEErTdmhqZ18ZbQtK4OpHVMp2itXRaU1ld/7ZjW/45ujwXsT+tXtcH4leAi7eou99/CzxXQvlusYa/TCffVWk0gYOhLxy7rSGChq3PMF7Q6XzdDdcg30dGr/6FvonCzb6Ig7fHqqNB991nN/x/7QlB4aLcvzKzpDAdsfqijfWHbj7h7+Y/aMS+84Qg5/36++TTzL1Ld6fn37s2dmX//UoLywHk/djD//pwRuv+i
*/