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
157zmioW/Q8te34ZRQRlUxUKU+uw+L91b3IjoijBqzcvUZ0VrT8ArbdQ7PmR1vujMdyGQv/gn0Ypgzn1K0YMp1LWhTs9J+sgIxVRxCGpC5wYaLdPFKk1BH01oizMq7HOboL+AC8d44tij6pO86s9CPkk5Upe8Ef5w/7ZakUJ54fj6C7OPnCSrd/ePZYDrT4B/lZl9WWPB54RICkOzJtBzCIIHk+mJBnsClJ1oQZIQvxBZ3onLX+6815WM/RMTre30VtNqiWvJx/9FNfXbI62knUpN7BTNkr62KDfd9BrpSGU/H1FYNz9fEk9BO4va/L1Ty5gPI9hQzfav0g53lzjl38gVIWXU1Q5E35Yyb+R8ifQrehcAn8RR0Ct1Kirx3nworkl/hQ6r0dv1nCRPeuJNT1q9BCXj74sDa33xZvAac162lR5CUuvu0GJrKKQ3MI0XEA9NdPZ3HVRmsd81rooKdWE0zrKClfURpSX5AlLjTwka3Ssaou4B02Qy6b/D0MfpTFWJS7BxMpepD+FW624yNwZjS8b6NiJdstKwyzGIcfvD10zi8bXFbEt3vsxr5b1AvYyLPoF5Pj5JJK3+aN0FL1TCWod1Vcyx07baAca3uof/5FTVTINT8HyUGJm6oQBCC2EdCWpAma53uYUA9PAFGf6J5+TdwnH5BZfP+ac41KlumakZIwye/PhYWUQNQMs9p6GK+VPTj+zUnDH
*/