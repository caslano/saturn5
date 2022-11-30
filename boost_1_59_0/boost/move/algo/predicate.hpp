//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_MOVE_ALGO_PREDICATE_HPP
#define BOOST_MOVE_ALGO_PREDICATE_HPP

#include <boost/move/algo/move.hpp>
#include <boost/move/adl_move_swap.hpp>
#include <boost/move/algo/detail/basic_op.hpp>
#include <boost/move/detail/iterator_traits.hpp>
#include <boost/move/detail/destruct_n.hpp>
#include <boost/assert.hpp>

namespace boost {
namespace movelib {

template<class Comp>
struct antistable
{
   BOOST_MOVE_FORCEINLINE explicit antistable(Comp &comp)
      : m_comp(comp)
   {}

   BOOST_MOVE_FORCEINLINE antistable(const antistable & other)
      : m_comp(other.m_comp)
   {}

   template<class U, class V>
   BOOST_MOVE_FORCEINLINE bool operator()(const U &u, const V & v)
   {  return !m_comp(v, u);  }

   BOOST_MOVE_FORCEINLINE const Comp &get() const
   {  return m_comp; }

   private:
   antistable & operator=(const antistable &);
   Comp &m_comp;
};

template<class Comp>
Comp unantistable(Comp comp)
{   return comp;  }

template<class Comp>
Comp unantistable(antistable<Comp> comp)
{   return comp.get();  }

template <class Comp>
class negate
{
   public:
   BOOST_MOVE_FORCEINLINE negate()
   {}

   BOOST_MOVE_FORCEINLINE explicit negate(Comp comp)
      : m_comp(comp)
   {}

   template <class T1, class T2>
   BOOST_MOVE_FORCEINLINE bool operator()(const T1& l, const T2& r)
   {
      return !m_comp(l, r);
   }

   private:
   Comp m_comp;
};


template <class Comp>
class inverse
{
   public:
   BOOST_MOVE_FORCEINLINE inverse()
   {}

   BOOST_MOVE_FORCEINLINE explicit inverse(Comp comp)
      : m_comp(comp)
   {}

   template <class T1, class T2>
   BOOST_MOVE_FORCEINLINE bool operator()(const T1& l, const T2& r)
   {
      return m_comp(r, l);
   }

   private:
   Comp m_comp;
};

}  //namespace movelib {
}  //namespace boost {

#endif   //#define BOOST_MOVE_ALGO_PREDICATE_HPP

/* predicate.hpp
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
*/