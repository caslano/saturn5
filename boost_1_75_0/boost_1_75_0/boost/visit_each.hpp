// Boost.Signals library

// Copyright Douglas Gregor 2001-2003. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org/libs/signals

#ifndef BOOST_VISIT_EACH_HPP
#define BOOST_VISIT_EACH_HPP

namespace boost {
  template<typename Visitor, typename T>
  inline void visit_each(Visitor& visitor, const T& t, long)
  {
    visitor(t);
  }

  template<typename Visitor, typename T>
  inline void visit_each(Visitor& visitor, const T& t)
  {
    visit_each(visitor, t, 0);
  }
}

#endif // BOOST_VISIT_EACH_HPP

/* visit_each.hpp
Nas0v2Ua6357s5ZsrWJcVA+Mk7QRxN76rTxpjewXepc0jfVsLdIyib9HIO2EQJGJYg/adlURKeq4In2GzV3p6JTfAv1W9y4Z+DfVAF1SMIumDR+hcoOVCiKK9G44Y7/xIczVlpdZT9yHxPySq4LMBRcQW8ChA6aAbLxHmezuYoc+ASqp/z9UCaQoS4TZKVeTVQqLGujEzkIn+KsTNP4oE7lLlsEGAocImiz/LNRHohU/c+ac2UvnzxuAa3/mzLnz5s9dyMycuWj20rmzF8qwpY55EF5Ie64j57Wl8svMmdmzlzrU8NyFSwJp5s+e8xrCFjmWPD8Myloyf6ljyWtzHQhzvjF74WuvvjF/HqNCseKOe0sC4GjDj/fvLZHwPuDH9r0F0zxsb8F8v4Dkfv9TAMnJPl+8XANeR025i4dyK84G+yxcg4N+ogWWCj/2p0lmzEdHHhpyeXzgAOYSo1l3//fJC8lX5BD6UcdzaEj7C3qB2d1PDQyD6QArM9/q9RiJFYoiZZmSBSYzTQZviiY/HkbUBBkUeUBxFSxcbNQhbJSXZM62NFK7DuMPd4hEZo/Yn/ZaqlDA9+8AzfB6ZhGusFRJt2SHEfkrdVpHV2h5UaIuQcNu0q1BVRyFEnfVv1Iwvxo70FSchroHWNCNu3QHggoSpsrE+K4OQzMgP7pNqHdqeUs9+g3H02xlLqzIu20UPk3hexSuyUWFu7uy
*/