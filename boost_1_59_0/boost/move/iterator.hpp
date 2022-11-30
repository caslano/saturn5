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
BOOST_MOVE_FORCEINLINE move_iterator<It> make_move_iterator(const It &it)
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