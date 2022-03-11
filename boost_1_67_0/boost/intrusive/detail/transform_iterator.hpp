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