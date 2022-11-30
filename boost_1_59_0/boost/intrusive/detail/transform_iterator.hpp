/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2007-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_TRANSFORM_ITERATOR_HPP
#define BOOST_INTRUSIVE_DETAIL_TRANSFORM_ITERATOR_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/detail/iterator.hpp>

namespace boost {
namespace intrusive {
namespace detail {

template <class PseudoReference>
struct operator_arrow_proxy
{
   BOOST_INTRUSIVE_FORCEINLINE operator_arrow_proxy(const PseudoReference &px)
      :  m_value(px)
   {}

   BOOST_INTRUSIVE_FORCEINLINE PseudoReference* operator->() const { return &m_value; }
   // This function is needed for MWCW and BCC, which won't call operator->
   // again automatically per 13.3.1.2 para 8
//   operator T*() const { return &m_value; }
   mutable PseudoReference m_value;
};

template <class T>
struct operator_arrow_proxy<T&>
{
   BOOST_INTRUSIVE_FORCEINLINE operator_arrow_proxy(T &px)
      :  m_value(px)
   {}

   BOOST_INTRUSIVE_FORCEINLINE T* operator->() const { return &m_value; }
   // This function is needed for MWCW and BCC, which won't call operator->
   // again automatically per 13.3.1.2 para 8
//   operator T*() const { return &m_value; }
   T &m_value;
};

template <class Iterator, class UnaryFunction>
class transform_iterator
{
   public:
   typedef typename Iterator::iterator_category                                           iterator_category;
   typedef typename detail::remove_reference<typename UnaryFunction::result_type>::type   value_type;
   typedef typename Iterator::difference_type                                             difference_type;
   typedef operator_arrow_proxy<typename UnaryFunction::result_type>                      pointer;
   typedef typename UnaryFunction::result_type                                            reference;
   
   explicit transform_iterator(const Iterator &it, const UnaryFunction &f = UnaryFunction())
      :  members_(it, f)
   {}

   explicit transform_iterator()
      :  members_()
   {}

   BOOST_INTRUSIVE_FORCEINLINE Iterator get_it() const
   {  return members_.m_it;   }

   //Constructors
   BOOST_INTRUSIVE_FORCEINLINE transform_iterator& operator++()
   { increment();   return *this;   }

   BOOST_INTRUSIVE_FORCEINLINE transform_iterator operator++(int)
   {
      transform_iterator result (*this);
      increment();
      return result;
   }

   BOOST_INTRUSIVE_FORCEINLINE friend bool operator== (const transform_iterator& i, const transform_iterator& i2)
   { return i.equal(i2); }

   BOOST_INTRUSIVE_FORCEINLINE friend bool operator!= (const transform_iterator& i, const transform_iterator& i2)
   { return !(i == i2); }

   BOOST_INTRUSIVE_FORCEINLINE friend typename Iterator::difference_type operator- (const transform_iterator& i, const transform_iterator& i2)
   { return i2.distance_to(i); }

   //Arithmetic
   transform_iterator& operator+=(typename Iterator::difference_type off)
   {  this->advance(off); return *this;   }

   BOOST_INTRUSIVE_FORCEINLINE transform_iterator operator+(typename Iterator::difference_type off) const
   {
      transform_iterator other(*this);
      other.advance(off);
      return other;
   }

   BOOST_INTRUSIVE_FORCEINLINE friend transform_iterator operator+(typename Iterator::difference_type off, const transform_iterator& right)
   {  return right + off; }

   BOOST_INTRUSIVE_FORCEINLINE transform_iterator& operator-=(typename Iterator::difference_type off)
   {  this->advance(-off); return *this;   }

   BOOST_INTRUSIVE_FORCEINLINE transform_iterator operator-(typename Iterator::difference_type off) const
   {  return *this + (-off);  }

   BOOST_INTRUSIVE_FORCEINLINE typename UnaryFunction::result_type operator*() const
   { return dereference(); }

   BOOST_INTRUSIVE_FORCEINLINE operator_arrow_proxy<typename UnaryFunction::result_type>
      operator->() const
   { return operator_arrow_proxy<typename UnaryFunction::result_type>(dereference());  }

   private:
   struct members
      :  UnaryFunction
   {
      BOOST_INTRUSIVE_FORCEINLINE members(const Iterator &it, const UnaryFunction &f)
         :  UnaryFunction(f), m_it(it)
      {}

      BOOST_INTRUSIVE_FORCEINLINE members()
      {}

      Iterator m_it;
   } members_;


   BOOST_INTRUSIVE_FORCEINLINE void increment()
   { ++members_.m_it; }

   BOOST_INTRUSIVE_FORCEINLINE void decrement()
   { --members_.m_it; }

   BOOST_INTRUSIVE_FORCEINLINE bool equal(const transform_iterator &other) const
   {  return members_.m_it == other.members_.m_it;   }

   BOOST_INTRUSIVE_FORCEINLINE bool less(const transform_iterator &other) const
   {  return other.members_.m_it < members_.m_it;   }

   typename UnaryFunction::result_type dereference() const
   { return members_(*members_.m_it); }

   void advance(typename Iterator::difference_type n)
   {  boost::intrusive::iterator_advance(members_.m_it, n); }

   typename Iterator::difference_type distance_to(const transform_iterator &other)const
   {  return boost::intrusive::iterator_distance(other.members_.m_it, members_.m_it); }
};

} //namespace detail
} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_DETAIL_TRANSFORM_ITERATOR_HPP

/* transform_iterator.hpp
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
*/