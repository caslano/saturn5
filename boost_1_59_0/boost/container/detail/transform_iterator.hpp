//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013.
// (C) Copyright Gennaro Prota 2003 - 2004.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_TRANSFORM_ITERATORS_HPP
#define BOOST_CONTAINER_DETAIL_TRANSFORM_ITERATORS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>
#include <boost/container/detail/type_traits.hpp>
#include <boost/container/detail/iterator.hpp>

namespace boost {
namespace container {

template <class PseudoReference>
struct operator_arrow_proxy
{
   operator_arrow_proxy(const PseudoReference &px)
      :  m_value(px)
   {}

   typedef PseudoReference element_type;

   PseudoReference* operator->() const { return &m_value; }

   mutable PseudoReference m_value;
};

template <class T>
struct operator_arrow_proxy<T&>
{
   operator_arrow_proxy(T &px)
      :  m_value(px)
   {}

   typedef T element_type;

   T* operator->() const { return const_cast<T*>(&m_value); }

   T &m_value;
};

template <class Iterator, class UnaryFunction>
class transform_iterator
   : public UnaryFunction
   , public boost::container::iterator
      < typename Iterator::iterator_category
      , typename dtl::remove_reference<typename UnaryFunction::result_type>::type
      , typename Iterator::difference_type
      , operator_arrow_proxy<typename UnaryFunction::result_type>
      , typename UnaryFunction::result_type>
{
   public:
   explicit transform_iterator(const Iterator &it, const UnaryFunction &f = UnaryFunction())
      :  UnaryFunction(f), m_it(it)
   {}

   explicit transform_iterator()
      :  UnaryFunction(), m_it()
   {}

   //Constructors
   transform_iterator& operator++()
   { increment();   return *this;   }

   transform_iterator operator++(int)
   {
      transform_iterator result (*this);
      increment();
      return result;
   }

   friend bool operator== (const transform_iterator& i, const transform_iterator& i2)
   { return i.equal(i2); }

   friend bool operator!= (const transform_iterator& i, const transform_iterator& i2)
   { return !(i == i2); }

/*
   friend bool operator> (const transform_iterator& i, const transform_iterator& i2)
   { return i2 < i; }

   friend bool operator<= (const transform_iterator& i, const transform_iterator& i2)
   { return !(i > i2); }

   friend bool operator>= (const transform_iterator& i, const transform_iterator& i2)
   { return !(i < i2); }
*/
   friend typename Iterator::difference_type operator- (const transform_iterator& i, const transform_iterator& i2)
   { return i2.distance_to(i); }

   //Arithmetic
   transform_iterator& operator+=(typename Iterator::difference_type off)
   {  this->advance(off); return *this;   }

   transform_iterator operator+(typename Iterator::difference_type off) const
   {
      transform_iterator other(*this);
      other.advance(off);
      return other;
   }

   friend transform_iterator operator+(typename Iterator::difference_type off, const transform_iterator& right)
   {  return right + off; }

   transform_iterator& operator-=(typename Iterator::difference_type off)
   {  this->advance(-off); return *this;   }

   transform_iterator operator-(typename Iterator::difference_type off) const
   {  return *this + (-off);  }

   typename UnaryFunction::result_type operator*() const
   { return dereference(); }

   operator_arrow_proxy<typename UnaryFunction::result_type>
      operator->() const
   { return operator_arrow_proxy<typename UnaryFunction::result_type>(dereference());  }

   Iterator & base()
   {  return m_it;   }

   const Iterator & base() const
   {  return m_it;   }

   private:
   Iterator m_it;

   void increment()
   { ++m_it; }

   void decrement()
   { --m_it; }

   bool equal(const transform_iterator &other) const
   {  return m_it == other.m_it;   }

   bool less(const transform_iterator &other) const
   {  return other.m_it < m_it;   }

   typename UnaryFunction::result_type dereference() const
   { return UnaryFunction::operator()(*m_it); }

   void advance(typename Iterator::difference_type n)
   {  boost::container::iterator_advance(m_it, n); }

   typename Iterator::difference_type distance_to(const transform_iterator &other)const
   {  return boost::container::iterator_distance(other.m_it, m_it); }
};

template <class Iterator, class UnaryFunc>
transform_iterator<Iterator, UnaryFunc>
make_transform_iterator(Iterator it, UnaryFunc fun)
{
   return transform_iterator<Iterator, UnaryFunc>(it, fun);
}

}  //namespace container {
}  //namespace boost {

#include <boost/container/detail/config_end.hpp>

#endif   //#ifndef BOOST_CONTAINER_DETAIL_TRANSFORM_ITERATORS_HPP

/* transform_iterator.hpp
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
*/