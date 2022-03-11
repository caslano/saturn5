//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2012-2012.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//! \file

#ifndef BOOST_MOVE_ITERATOR_HPP
#define BOOST_MOVE_ITERATOR_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/detail/config_begin.hpp>
#include <boost/move/detail/workaround.hpp>  //forceinline
#include <boost/move/detail/iterator_traits.hpp>
#include <boost/move/utility_core.hpp>

namespace boost {

//////////////////////////////////////////////////////////////////////////////
//
//                            move_iterator
//
//////////////////////////////////////////////////////////////////////////////

//! Class template move_iterator is an iterator adaptor with the same behavior
//! as the underlying iterator except that its dereference operator implicitly
//! converts the value returned by the underlying iterator's dereference operator
//! to an rvalue reference. Some generic algorithms can be called with move
//! iterators to replace copying with moving.
template <class It>
class move_iterator
{
   public:
   typedef It                                                              iterator_type;
   typedef typename boost::movelib::iterator_traits<iterator_type>::value_type        value_type;
   #if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) || defined(BOOST_MOVE_DOXYGEN_INVOKED)
   typedef value_type &&                                                   reference;
   #else
   typedef typename ::boost::move_detail::if_
      < ::boost::has_move_emulation_enabled<value_type>
      , ::boost::rv<value_type>&
      , value_type & >::type                                               reference;
   #endif
   typedef It                                                              pointer;
   typedef typename boost::movelib::iterator_traits<iterator_type>::difference_type   difference_type;
   typedef typename boost::movelib::iterator_traits<iterator_type>::iterator_category iterator_category;

   BOOST_MOVE_FORCEINLINE move_iterator()
      : m_it()
   {}

   BOOST_MOVE_FORCEINLINE explicit move_iterator(const It &i)
      :  m_it(i)
   {}

   template <class U>
   BOOST_MOVE_FORCEINLINE move_iterator(const move_iterator<U>& u)
      :  m_it(u.m_it)
   {}

   BOOST_MOVE_FORCEINLINE reference operator*() const
   {
      #if defined(BOOST_NO_CXX11_RVALUE_REFERENCES) || defined(BOOST_MOVE_OLD_RVALUE_REF_BINDING_RULES)
      return *m_it;
      #else
      return ::boost::move(*m_it);
      #endif
   }

   BOOST_MOVE_FORCEINLINE pointer   operator->() const
   {  return m_it;   }

   BOOST_MOVE_FORCEINLINE move_iterator& operator++()
   {  ++m_it; return *this;   }

   BOOST_MOVE_FORCEINLINE move_iterator<iterator_type>  operator++(int)
   {  move_iterator<iterator_type> tmp(*this); ++(*this); return tmp;   }

   BOOST_MOVE_FORCEINLINE move_iterator& operator--()
   {  --m_it; return *this;   }

   BOOST_MOVE_FORCEINLINE move_iterator<iterator_type>  operator--(int)
   {  move_iterator<iterator_type> tmp(*this); --(*this); return tmp;   }

   move_iterator<iterator_type>  operator+ (difference_type n) const
   {  return move_iterator<iterator_type>(m_it + n);  }

   BOOST_MOVE_FORCEINLINE move_iterator& operator+=(difference_type n)
   {  m_it += n; return *this;   }

   BOOST_MOVE_FORCEINLINE move_iterator<iterator_type>  operator- (difference_type n) const
   {  return move_iterator<iterator_type>(m_it - n);  }

   BOOST_MOVE_FORCEINLINE move_iterator& operator-=(difference_type n)
   {  m_it -= n; return *this;   }

   BOOST_MOVE_FORCEINLINE reference operator[](difference_type n) const
   {
      #if defined(BOOST_NO_CXX11_RVALUE_REFERENCES) || defined(BOOST_MOVE_OLD_RVALUE_REF_BINDING_RULES)
      return m_it[n];
      #else
      return ::boost::move(m_it[n]);
      #endif
   }

   BOOST_MOVE_FORCEINLINE friend bool operator==(const move_iterator& x, const move_iterator& y)
   {  return x.m_it == y.m_it;  }

   BOOST_MOVE_FORCEINLINE friend bool operator!=(const move_iterator& x, const move_iterator& y)
   {  return x.m_it != y.m_it;  }

   BOOST_MOVE_FORCEINLINE friend bool operator< (const move_iterator& x, const move_iterator& y)
   {  return x.m_it < y.m_it;   }

   BOOST_MOVE_FORCEINLINE friend bool operator<=(const move_iterator& x, const move_iterator& y)
   {  return x.m_it <= y.m_it;  }

   BOOST_MOVE_FORCEINLINE friend bool operator> (const move_iterator& x, const move_iterator& y)
   {  return x.m_it > y.m_it;  }

   BOOST_MOVE_FORCEINLINE friend bool operator>=(const move_iterator& x, const move_iterator& y)
   {  return x.m_it >= y.m_it;  }

   BOOST_MOVE_FORCEINLINE friend difference_type operator-(const move_iterator& x, const move_iterator& y)
   {  return x.m_it - y.m_it;   }

   BOOST_MOVE_FORCEINLINE friend move_iterator operator+(difference_type n, const move_iterator& x)
   {  return move_iterator(x.m_it + n);   }

   private:
   It m_it;
};

//is_move_iterator
namespace move_detail {

template <class I>
struct is_move_iterator
{
   static const bool value = false;
};

template <class I>
struct is_move_iterator< ::boost::move_iterator<I> >
{
   static const bool value = true;
};

}  //namespace move_detail {

//////////////////////////////////////////////////////////////////////////////
//
//                            move_iterator
//
//////////////////////////////////////////////////////////////////////////////

//!
//! <b>Returns</b>: move_iterator<It>(i).
template<class It>
inline move_iterator<It> make_move_iterator(const It &it)
{  return move_iterator<It>(it); }

//////////////////////////////////////////////////////////////////////////////
//
//                         back_move_insert_iterator
//
//////////////////////////////////////////////////////////////////////////////


//! A move insert iterator that move constructs elements at the
//! back of a container
template <typename C> // C models Container
class back_move_insert_iterator
{
   C* container_m;

   public:
   typedef C                           container_type;
   typedef typename C::value_type      value_type;
   typedef typename C::reference       reference;
   typedef typename C::pointer         pointer;
   typedef typename C::difference_type difference_type;
   typedef std::output_iterator_tag    iterator_category;

   explicit back_move_insert_iterator(C& x) : container_m(&x) { }

   back_move_insert_iterator& operator=(reference x)
   { container_m->push_back(boost::move(x)); return *this; }

   back_move_insert_iterator& operator=(BOOST_RV_REF(value_type) x)
   {  reference rx = x; return this->operator=(rx);  }

   back_move_insert_iterator& operator*()     { return *this; }
   back_move_insert_iterator& operator++()    { return *this; }
   back_move_insert_iterator& operator++(int) { return *this; }
};

//!
//! <b>Returns</b>: back_move_insert_iterator<C>(x).
template <typename C> // C models Container
inline back_move_insert_iterator<C> back_move_inserter(C& x)
{
   return back_move_insert_iterator<C>(x);
}

//////////////////////////////////////////////////////////////////////////////
//
//                         front_move_insert_iterator
//
//////////////////////////////////////////////////////////////////////////////

//! A move insert iterator that move constructs elements int the
//! front of a container
template <typename C> // C models Container
class front_move_insert_iterator
{
   C* container_m;

public:
   typedef C                           container_type;
   typedef typename C::value_type      value_type;
   typedef typename C::reference       reference;
   typedef typename C::pointer         pointer;
   typedef typename C::difference_type difference_type;
   typedef std::output_iterator_tag    iterator_category;

   explicit front_move_insert_iterator(C& x) : container_m(&x) { }

   front_move_insert_iterator& operator=(reference x)
   { container_m->push_front(boost::move(x)); return *this; }

   front_move_insert_iterator& operator=(BOOST_RV_REF(value_type) x)
   {  reference rx = x; return this->operator=(rx);  }

   front_move_insert_iterator& operator*()     { return *this; }
   front_move_insert_iterator& operator++()    { return *this; }
   front_move_insert_iterator& operator++(int) { return *this; }
};

//!
//! <b>Returns</b>: front_move_insert_iterator<C>(x).
template <typename C> // C models Container
inline front_move_insert_iterator<C> front_move_inserter(C& x)
{
   return front_move_insert_iterator<C>(x);
}

//////////////////////////////////////////////////////////////////////////////
//
//                         insert_move_iterator
//
//////////////////////////////////////////////////////////////////////////////
template <typename C> // C models Container
class move_insert_iterator
{
   C* container_m;
   typename C::iterator pos_;

   public:
   typedef C                           container_type;
   typedef typename C::value_type      value_type;
   typedef typename C::reference       reference;
   typedef typename C::pointer         pointer;
   typedef typename C::difference_type difference_type;
   typedef std::output_iterator_tag    iterator_category;

   explicit move_insert_iterator(C& x, typename C::iterator pos)
      : container_m(&x), pos_(pos)
   {}

   move_insert_iterator& operator=(reference x)
   {
      pos_ = container_m->insert(pos_, ::boost::move(x));
      ++pos_;
      return *this;
   }

   move_insert_iterator& operator=(BOOST_RV_REF(value_type) x)
   {  reference rx = x; return this->operator=(rx);  }

   move_insert_iterator& operator*()     { return *this; }
   move_insert_iterator& operator++()    { return *this; }
   move_insert_iterator& operator++(int) { return *this; }
};

//!
//! <b>Returns</b>: move_insert_iterator<C>(x, it).
template <typename C> // C models Container
inline move_insert_iterator<C> move_inserter(C& x, typename C::iterator it)
{
   return move_insert_iterator<C>(x, it);
}

}  //namespace boost {

#include <boost/move/detail/config_end.hpp>

#endif //#ifndef BOOST_MOVE_ITERATOR_HPP

/* iterator.hpp
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
*/