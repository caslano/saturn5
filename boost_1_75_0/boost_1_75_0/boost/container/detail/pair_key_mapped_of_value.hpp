//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_PAIR_KEY_MAPPED_OF_VALUE_HPP
#define BOOST_CONTAINER_PAIR_KEY_MAPPED_OF_VALUE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

namespace boost {
namespace container {

template<class Key, class Mapped>
struct pair_key_mapped_of_value
{
   typedef Key    key_type;
   typedef Mapped mapped_type;

   template<class Pair>
   const key_type & key_of_value(const Pair &p) const
   {  return p.first;  }

   template<class Pair>
   const mapped_type & mapped_of_value(const Pair &p) const
   {  return p.second;  }

   template<class Pair>
   key_type & key_of_value(Pair &p) const
   {  return const_cast<key_type&>(p.first);  }

   template<class Pair>
   mapped_type & mapped_of_value(Pair &p) const
   {  return p.second;  }

};

}}

#include <boost/container/detail/config_end.hpp>

#endif   // BOOST_CONTAINER_PAIR_KEY_MAPPED_OF_VALUE_HPP

/* pair_key_mapped_of_value.hpp
PhsMBu5WCiGcLtIEtl3eo8PDP2dVLQXMtNYHWuuDP/zqV3eVUjcevHz5t4UQbwMvYU7pnX3wgx98N4/wUpjovjsW4bcuhJxXoMEqxK/N4yXXIvAaiO/fLKp/GUFYgPh+2SxNuPmt77L3/Av4p+D4tgHlXfthwnJ7i0arVYjX1gYghCBNU27eOgIRrWmN8fupnOMfQ41sHCmhJSAdNJDqgDQLmGQSpraRvRRETBjEBGJGMzyk3Tig0zii17nJoPM6/c7XuLgt2NlusjXosr3d4+KFbQb9Lltbfd73/qcQQiBlgJABUhgCIaUJUDo4OFx7kdEqIpCPW82zunKDrS1XRmIk1TZwxeU9PDj4C5ZYzTAEYv+P//iPd1WW3VBK7WdpevvRxx//dYwePgESKWXyvve97z2n7jr58uSwlOOux/UXI37lZhXiL2pjGdevIzI1dMAh/+7zz5diApxHIEd2Xdkhx1nY+z2arVbuXnO/gZSMRkMODhPMZ6gK1qcF10MrOQhhCYVLl0ADaJISkmrJLA44iq3Rbz8DkSBlihQpUsyI5DFhMKYdJbSaKd32Lv3OO2z1UrZ6KTuDGTt9RbcDnVZAr9fkox/9GM1Wk067S6vVtTYIK0kgODo8NDaIqpeigvB+mn+/iEAsyufD1va2K9PESA8DIcQTfp6D/f1f1BCjday1HgPDr33ta1O0nmoYXbly5ZsYUf4NKeVr
*/