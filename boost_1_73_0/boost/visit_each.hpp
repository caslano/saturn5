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
JEojzZWYQ/cY/wP0zLc3Tx6FRV0NrsNI07nq4J3LJBzTXOibKu2ee7hvODsA3eriOg+6/axaM/ilBsx8/QgKrWqZ7rnrAq1/pcr70lEmDRTe3Q6nY7iCdfFBUlvl1t74u2zcffqgfPdbsTR0Tq5jniFqFuIvJpoRQGyYJVX7vudds1Wyex3TaZZcCFTebNTTO2gkhc+icE470odzep9Y+gBOP/EPPQz/ISZqmCJVAykDvmQG
*/